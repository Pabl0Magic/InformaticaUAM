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
    SQLLEN rowCount;
    SQLRETURN ret; /* ODBC API return status */
    SQLCHAR query[512], name1[512] = "", customerid[512] = "", filmid[512] = "", staffid[512] = "", storeid[512] = "", amount[512] = "", invID[128] = "", lastRental[128] = "";

    if (argc < 2) {
        fprintf(stderr, "$ %s new <customer_id> <film_id> <staff_id> <store_id> <amount>\n", argv[0]);
            fprintf(stderr, "\t-Adds a new rental");
            fprintf(stderr, "Where: \n\t\"<customer_id>\" is the customer that is renting\n \"<film_id>\" is the film rented\n\"<staff_id>\" is the member of the staff that serves the customer\n\"<store_id>\" is the store where the customer rents the film\n\"<amount>\" is the amount paid");
            return EXIT_FAILURE;
    }
    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    
    if (strcmp(argv[1], "new") == 0) {
        if(argc < 7){
            fprintf(stderr, "$ %s new <customer_id> <film_id> <staff_id> <store_id> <amount>\n", argv[0]);
            fprintf(stderr, "\t-Adds a new rental");
            fprintf(stderr, "Where: \n\t\"<customer_id>\" is the customer that is renting\n \"<film_id>\" is the film rented\n\"<staff_id>\" is the member of the staff that serves the customer\n\"<store_id>\" is the store where the customer rents the film\n\"<amount>\" is the amount paid\n");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        strcpy((char*) customerid, argv[2]);
        strcpy((char*) filmid, argv[3]);
        strcpy((char*) staffid, argv[4]);
        strcpy((char*) storeid, argv[5]);
        strcpy((char*) amount, argv[6]);
        sprintf((char*)query, "SELECT inventory.inventory_id FROM inventory WHERE inventory.film_id = %s AND inventory.store_id = %s", filmid, storeid);
        ret = SQLExecDirect(stmt, query, SQL_NTS);
        SQLRowCount(stmt, &rowCount);
        if (rowCount > 0) {
            SQLFetch(stmt);
            SQLGetData(stmt, 1, SQL_C_CHAR, &invID, sizeof(SQL_C_CHAR), NULL);
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            sprintf((char*) query, "SELECT * FROM rental WHERE inventory_id = %s AND return_date IS null", invID);
            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
            ret = SQLExecDirect(stmt, query, SQL_NTS);
            SQLRowCount(stmt, &rowCount);
            if (rowCount > 0) {
                printf("The film with ID %s and store ID %s has already been rented.\n", filmid, storeid);
                SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                odbc_disconnect(env, dbc);
                return EXIT_FAILURE;
            }
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            sprintf((char*) query, "SELECT customer_id FROM customer WHERE customer_id = %s", customerid);
            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
            ret = SQLExecDirect(stmt, query, SQL_NTS);
            SQLRowCount(stmt, &rowCount);
            if (rowCount > 0) {
                SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                sprintf((char*) query, "SELECT staff_id FROM staff WHERE staff_id = %s", staffid);
                SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
                ret = SQLExecDirect(stmt, query, SQL_NTS);
                SQLRowCount(stmt, &rowCount);
                if (rowCount > 0) {
                    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                    sprintf((char*) query, "SELECT store_id FROM store WHERE store_id = %s", storeid);
                    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
                    ret = SQLExecDirect(stmt, query, SQL_NTS);
                    SQLRowCount(stmt, &rowCount);
                    if (rowCount > 0) {
                        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                        sprintf((char*) query, "INSERT INTO rental VALUES (default, now(), %s, %s, NULL, %s, now())", invID, customerid, staffid);
                        SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
                        ret = SQLExecDirect(stmt, query, SQL_NTS);
                        if (SQL_SUCCEEDED(ret)) {
                            SQLFreeHandle(SQL_HANDLE_STMT, stmt);

                            /* Get the last rental, the last one you inserted */
                            sprintf((char*) query, "SELECT MAX(rental_id) from rental");
                            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
                            SQLExecDirect(stmt, query, SQL_NTS);
                            SQLFetch(stmt);
                            SQLGetData(stmt, 1, SQL_C_CHAR, &lastRental, sizeof(SQL_C_CHAR), NULL);
                            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                            sprintf((char*) query, "INSERT INTO payment VALUES (default, %s, %s, %s, %s, now())", customerid, staffid, lastRental, amount);
                            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
                            ret = SQLExecDirect(stmt, query, SQL_NTS);
                            if(SQL_SUCCEEDED(ret)) {
                                printf("Rental added successfully.\n");
                            } else {
                                printf("Error inserting values into payment table.\nMake sure your input uses X.XX as the amount, and not X,XX.\n"); 
                                odbc_disconnect(env, dbc);
                                return EXIT_FAILURE;
                            }
                        } else {
                            printf("Error inserting values into rental table.\n");
                            odbc_disconnect(env, dbc);
                            return EXIT_FAILURE;
                        }
                    } else {
                        printf("The store id (%s) doesn't exist.\n", storeid);
                        odbc_disconnect(env, dbc);
                        return EXIT_FAILURE;
                    }
                } else {
                    printf("The staff id (%s) doesn't exist.\n", staffid);
                    odbc_disconnect(env, dbc);
                    return EXIT_FAILURE;
                }
            } else {
                printf("The customer id (%s) doesn't exist.\n", customerid);
                odbc_disconnect(env, dbc);
                return EXIT_FAILURE;
            }
        } else {
            printf("The film id (%s) doesn't exist or the store with id %s doesn't have it.\n", filmid, storeid);
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
    }
    else if(strcmp(argv[1], "remove") == 0) {
        if(argc < 3) {
            fprintf(stderr, "Usage: \n$ %s remove <rental_id>\n>", argv[0]);
            fprintf(stderr, "\t -Removes the rental that you want");
            fprintf(stderr, "Where: \n\t\"<rental_id>\" is the id of the rental to be removed");
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        strcpy((char*) name1, argv[2]);
        sprintf((char*)query, "DELETE FROM payment WHERE payment.rental_id = %s", name1);
        ret = SQLExecDirect(stmt, query, SQL_NTS);
        if (SQL_SUCCEEDED(ret)) {
            sprintf((char*)query,"DELETE FROM rental WHERE rental_id = %s;",name1);
            ret = SQLExecDirect(stmt, query, SQL_NTS);
            if (SQL_SUCCEEDED(ret)) {
                printf("Rental removed successfully.\n");
            } else {
                printf("It doesn't exist that rental id (%s) in rental.\n", name1);
                odbc_disconnect(env, dbc);
                return EXIT_FAILURE;    
            }
        } else {
            printf("The rental id (%s) doesn't exist in payment or has already been removed.\n", name1);
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "$ %s new <customer_id> <film_id> <staff_id> <store_id> <amount>\n", argv[0]);
        fprintf(stderr, "\t-Adds a new rental");
        fprintf(stderr, "Where: \n\t\"<customer_id>\" is the customer that is renting\n \"<film_id>\" is the film rented\n\"<staff_id>\" is the member of the staff that serves the customer\n\"<store_id>\" is the store where the customer rents the film\n\"<amount>\" is the amount paid");
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        odbc_disconnect(env, dbc);
        return EXIT_FAILURE;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
