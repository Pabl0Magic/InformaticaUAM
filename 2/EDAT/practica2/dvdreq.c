#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

int main(int argc,char *argv[]) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;
    SQLLEN rowCount;
    SQLINTEGER x;
    SQLCHAR query[2048], y[512] /* used as an auxiliary string */, name1[512] = "", name2[512] = "";

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <your_input>\n\n", argv[0]);
        fprintf(stderr, "$ %s customer -n <First Name> -a <Last Name>\n", argv[0]);
        fprintf(stderr, "\t-Prints info about a list of customers with matching first name and/or last name\n");
        fprintf(stderr, "$ %s film <title>\n", argv[0]);
        fprintf(stderr, "\t-Prints info about movie whose titles match\n");
        fprintf(stderr, "$ %s rent <customer_id> <init date> <end date>\n", argv[0]);
        fprintf(stderr, "\t-Prints the rentals carried out by a customer between init date and end date, sorted by rental date\n");
        fprintf(stderr, "$ %s recommend <customer_id>\n", argv[0]);
        fprintf(stderr, "\t-Print a list of the three most rented movies that belong to the customer’s favorite (most often rented) category, but which he or she has not rented before.\n");
        odbc_disconnect(env, dbc);
        return EXIT_FAILURE;
    }
    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    /* print the name of each column */

    if (strcmp(argv[1], "customer") == 0) { 
        if(argc == 2){
            fprintf(stderr, "Usage:\n$ %s customer -n <First Name> -a <Last Name>\n", argv[0]);
            fprintf(stderr, "\t-Prints info about a list of customers with matching first name and/or last name\n");
            fprintf(stderr, "Where:\n\t\"-a <First Name>\" is the first name\n\t\"-a <Last Name>\" is the last name");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        for(i = 2; i < argc; i++){
            if(strcmp(argv[i], "-n") == 0) {
                if(i+1 < argc){
                    i++;
                    strcpy((char*) name1, argv[i]);
                } 
                else fprintf(stderr, "No name found after argument -n, skipping...\n");
                
            }
            else if (strcmp(argv[i], "-a") == 0) {
                if(i+1 < argc){
                    i++;
                    strcpy((char*) name2, argv[i]);
                }
                else fprintf(stderr, "No name found after argument -a, skipping...\n");
            }
            else fprintf(stderr, "Unknown argument: %s\n", argv[i]);
        }
        if (strcmp((char*) name1, "") == 0 && strcmp((char*) name2, "") == 0){
            fprintf(stderr, "Usage:\n$ %s customer -n <First Name> -a <Last Name>\n", argv[0]);
            fprintf(stderr, "\t-Prints info about a list of customers with matching first name and/or last name\n");
            fprintf(stderr, "Where:\n\t\"-a <First Name>\" is the first name\n\t\"-a <Last Name>\" is the last name");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        else if (strcmp((char*) name1, "") == 0){
            sprintf((char*) query, "SELECT customer_id, first_name, last_name, create_date, address FROM customer JOIN address ON address.address_id = customer.address_id WHERE customer.last_name = '%s'", name2);
        }
        else if (strcmp((char*) name2, "") == 0){
            sprintf((char*) query, "SELECT customer_id, first_name, last_name, create_date, address FROM customer JOIN address ON address.address_id = customer.address_id WHERE customer.first_name = '%s'", name1);
        }
        else sprintf((char*) query, "SELECT customer_id, first_name, last_name, create_date, address FROM customer JOIN address ON address.address_id = customer.address_id WHERE customer.first_name = '%s' OR customer.last_name = '%s'", name1, name2);
        SQLExecDirect(stmt, query, SQL_NTS);

        /* Check if any row was found */
        SQLRowCount(stmt, &rowCount);
        if (rowCount <= 0) {
            fprintf(stderr, "No customers found.\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        /* How many columns are there */
        SQLNumResultCols(stmt, &columns);
        /* print the name of each column */
        for (i = 1; i <= columns; i++) {
            SQLCHAR buf[512];
            SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
            printf("%s\t", buf);
        }
        printf("\n");

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
            ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%d\t%s\t", x, y);
            ret = SQLGetData(stmt, 3, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%s\t", y);
            ret = SQLGetData(stmt, 4, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%s\t", y);
            ret = SQLGetData(stmt, 5, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%s\n", y);
        }
    } else if (strcmp(argv[1], "film") == 0) {
        if(argc < 3) {
            fprintf(stderr, "Usage:\n$ %s film <title>\n", argv[0]);
            fprintf(stderr, "\t-Prints info about the film you want");
            fprintf(stderr, "Where: \n\t\"<title>\" is the title or the partial title of the film\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        strcpy((char*) name1, argv[2]);
        for(i = 3; i < argc; i++) {
            strcat((char*) name1, " "); 
            strcat((char*) name1, argv[i]);
        }
        
        sprintf((char*) query, "SELECT film.film_id, title, release_year, length, language.name, description, group_concat(CONCAT(actor.first_name, ' ', actor.last_name)) as actors\
                        FROM film, actor, language, film_actor\
                        WHERE film.language_id = language.language_id AND film.film_id = film_actor.film_id AND film_actor.actor_id = actor.actor_id AND film.title LIKE '%%%s%%'\
                        GROUP BY film.film_id, language.name", name1);
        SQLExecDirect(stmt, query, SQL_NTS);
        /* Check if any row was found */
        SQLRowCount(stmt, &rowCount);
        if (rowCount <= 0) {
            fprintf(stderr, "No films found.\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        /* How many columns are there */
        SQLNumResultCols(stmt, &columns);

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            for (i = 1; i <= columns; i++) {
                SQLCHAR buf[512];
                SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
                printf("%s:\n", buf);
                ret = SQLGetData(stmt, i, SQL_C_CHAR, y, sizeof(y), NULL);
                printf("- %s\n", y); 
            }
            printf("\n");
        }
    } else if (strcmp(argv[1], "rent") == 0) {
        if(argc != 5) {
            fprintf(stderr, "Usage:\n$ %s rent <customer_id> <init date> <end date>\n", argv[0]);
            fprintf(stderr, "\t-Prints the rentals carried out by a customer between init date and end date, sorted by rental date.\n");
            fprintf(stderr, "Where: \n\t\"<customer_id>\" is the id of the customer\n");
            fprintf(stderr, "\t\"<init date> and <end date>\" are the initial and the end date (format: YYYY-MM-DD)\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        x = atoi(argv[2]);
        sprintf((char*) query, 
            "SELECT rental.rental_id, rental.rental_date,\
                film.film_id, film.title,\
                staff.staff_id, staff.first_name as employee_name,\
                staff.store_id, sales_by_store.store,\
                payment.amount\
            FROM rental, film, staff,\
                sales_by_store, payment, customer, inventory\
            WHERE rental.customer_id = %d\
              AND rental.rental_date between '%s 00:00:00' and '%s 23:59:59'\
              AND rental.inventory_id = inventory.inventory_id\
              AND inventory.film_id = film.film_id\
              AND rental.staff_id = staff.staff_id\
              AND rental.rental_id = payment.rental_id\
            GROUP BY rental.rental_id, rental.rental_date,\
                     film.film_id, film.title,\
                     staff.staff_id, staff.first_name,\
                     staff.store_id, sales_by_store.store,\
                     payment.amount", x, argv[3], argv[4]);
        SQLExecDirect(stmt, query, SQL_NTS);
        /* Check if any row was found */
        SQLRowCount(stmt, &rowCount);
        if (rowCount <= 0) {
            fprintf(stderr, "No rents found for that period of time (%s - %s) or invalid format, or no customer found with that ID (%d).\n", argv[3], argv[4], x);
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        
        /* How many columns are there */
        SQLNumResultCols(stmt, &columns);
        printf("\n");

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            for (i = 1; i <= columns; i++) {
                SQLCHAR buf[512];
                SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
                printf("%s:\n", buf);
                ret = SQLGetData(stmt, i, SQL_C_CHAR, y, sizeof(y), NULL);
                printf("- %s\n", y); 
            }
            printf("\n");
        }
    } else if(!strcmp(argv[1], "recommend")) {
        if(argc != 3) {
            fprintf(stderr, "Usage:\n$ %s recommend <customer_id>\n", argv[0]);
            fprintf(stderr, "\t-Print a list of the three most rented movies that belong to the customer’s favorite (most often rented) category, but which he or she has not rented before. For each of the three recommended movies.\n");
            fprintf(stderr, "Where: \n\t\"<customer_id>\" is the id of the customer who you want to recommend a movie to.\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        sprintf((char*) query, "SELECT film.film_id, film.title, category.name\
                FROM rental, inventory, film, film_category, category\
                WHERE inventory.inventory_id = rental.inventory_id\
                AND inventory.film_id = film.film_id\
                AND film_category.film_id = film.film_id\
                AND category.category_id = film_category.category_id\
                AND film.film_id NOT IN (SELECT film.film_id\
                FROM rental, inventory, film\
                WHERE rental.customer_id = %s\
                AND inventory.inventory_id = rental.inventory_id\
                AND inventory.film_id = film.film_id)\
                AND film_category.category_id IN (SELECT film_category.category_id\
                            FROM rental, inventory, film, film_category\
                            WHERE rental.customer_id = %s\
                            AND inventory.inventory_id = rental.inventory_id\
                            AND inventory.film_id = film.film_id\
                            AND film_category.film_id = film.film_id\
                            GROUP BY category_id\
                            ORDER BY count(*) DESC LIMIT 1)\
                group by film.film_id, category.name\
                ORDER BY count(*) DESC\
                LIMIT 3", argv[2], argv[2]);
        SQLExecDirect(stmt, query, SQL_NTS);
        /* Check if any row was found */
        SQLRowCount(stmt, &rowCount);
        if (rowCount <= 0) {
            fprintf(stderr, "Customer with ID (%s) not found or hasn't rented any movie.\n", argv[2]);
            odbc_disconnect(env, dbc); 
            return EXIT_FAILURE;
        }
        
        /* How many columns are there */
        SQLNumResultCols(stmt, &columns);
        /* print the name of each column */
        for (i = 1; i <= columns; i++) {
            SQLCHAR buf[512];
            SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
            printf("%s\t", buf);
        }
        printf("\n");

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            ret = SQLGetData(stmt, 1, SQL_C_SLONG, &x, sizeof(SQLINTEGER), NULL);
            ret = SQLGetData(stmt, 2, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%d\t%s\t", x, y);
            ret = SQLGetData(stmt, 3, SQL_C_CHAR, y, sizeof(y), NULL);
            printf("%s\t", y);
            printf("\n");
        }
    }

    /* Free statement handle */

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    /* DISCONNECT */

    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}