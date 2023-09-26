#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

int main(int argc,char *argv[]) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT payStmt, rentStmt, invStmt, actorStmt, catStmt, filmStmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLCHAR query[512], name1[512] = "";

    if (argc < 2) {
        
    }
    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate all statement handles */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &payStmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &rentStmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &invStmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &actorStmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &catStmt);
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &filmStmt);

    if (strcmp(argv[1], "remove") == 0) {
        if(argc < 3){
            fprintf(stderr, "Usage: \n$ %s remove <film_id>\n>", argv[0]);
            fprintf(stderr, "\t -Removes the film that you want");
            fprintf(stderr, "Where: \n\t\"<film_id>\" is the id of the film to be removed");
            SQLCloseCursor(payStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
            
            SQLCloseCursor(rentStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
            
            SQLCloseCursor(invStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
            
            SQLCloseCursor(actorStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
            
            SQLCloseCursor(catStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
            
            SQLCloseCursor(filmStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }
        strcpy((char*) name1, argv[2]);
        sprintf((char*) query, "DELETE FROM payment\
                    USING (SELECT rental.rental_id FROM rental, inventory\
                    WHERE inventory.film_id = %s \
                    AND rental.inventory_id = inventory.inventory_id\
                    ) as t2 WHERE payment.rental_id = t2.rental_id;", name1);
        ret = SQLExecDirect(payStmt, query, SQL_NTS);
        if (SQL_SUCCEEDED(ret)) {
            sprintf((char*)query,"DELETE FROM rental\
                    USING (SELECT inventory_id\
                    FROM inventory\
                    WHERE inventory.film_id = %s\
                    ) as t2 WHERE rental.inventory_id = t2.inventory_id;", name1);
            ret = SQLExecDirect(rentStmt, query, SQL_NTS);
            if (SQL_SUCCEEDED(ret)) {
                sprintf((char*)query, "DELETE FROM inventory WHERE film_id = %s;", name1);
                ret = SQLExecDirect(invStmt, query, SQL_NTS);
                if(SQL_SUCCEEDED(ret)) {
                    sprintf((char*)query, "DELETE FROM film_actor WHERE film_id = %s;", name1);
                    ret = SQLExecDirect(actorStmt, query, SQL_NTS);
                    if (SQL_SUCCEEDED(ret)) {
                        sprintf((char*)query, "DELETE FROM film_category WHERE film_id = %s;", name1);
                        ret = SQLExecDirect(catStmt, query, SQL_NTS);
                        if (SQL_SUCCEEDED(ret)) {
                            sprintf((char*)query, "DELETE FROM film WHERE film_id = %s;", name1);
                            ret = SQLExecDirect(filmStmt, query, SQL_NTS);
                            if (SQL_SUCCEEDED(ret)) {
                                printf("Film removed successfully.\n");
                            } else {
                                printf("The film id (%s) doesn't exist in film.\n", name1);
                                SQLCloseCursor(payStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
                                
                                SQLCloseCursor(rentStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
                                
                                SQLCloseCursor(invStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
                                
                                SQLCloseCursor(actorStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
                                
                                SQLCloseCursor(catStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
                                
                                SQLCloseCursor(filmStmt);
                                SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

                                odbc_disconnect(env, dbc);
                                return EXIT_FAILURE;
                            }
                        } else {
                            printf("The film id (%s) doesn't exist in film_category.\n", name1);
                            SQLCloseCursor(payStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
                            
                            SQLCloseCursor(rentStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
                            
                            SQLCloseCursor(invStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
                            
                            SQLCloseCursor(actorStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
                            
                            SQLCloseCursor(catStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
                            
                            SQLCloseCursor(filmStmt);
                            SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

                            odbc_disconnect(env, dbc);
                            return EXIT_FAILURE;
                        }
                    } else {
                        printf("The film id (%s) doesn't exist in film_actor.\n", name1);
                        SQLCloseCursor(payStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
                        
                        SQLCloseCursor(rentStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
                        
                        SQLCloseCursor(invStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
                        
                        SQLCloseCursor(actorStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
                        
                        SQLCloseCursor(catStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
                        
                        SQLCloseCursor(filmStmt);
                        SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

                        odbc_disconnect(env, dbc);
                        return EXIT_FAILURE;
                    }
                } else {
                    printf("The film id (%s) doesn't exist in inventory.\n", name1);
                    SQLCloseCursor(payStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
                    
                    SQLCloseCursor(rentStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
                    
                    SQLCloseCursor(invStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
                    
                    SQLCloseCursor(actorStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
                    
                    SQLCloseCursor(catStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
                    
                    SQLCloseCursor(filmStmt);
                    SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

                    odbc_disconnect(env, dbc);
                    return EXIT_FAILURE;
                }
            } else {
                printf("The film id (%s) doesn't exist in rental.\n", name1);
                SQLCloseCursor(payStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
                
                SQLCloseCursor(rentStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
                
                SQLCloseCursor(invStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
                
                SQLCloseCursor(actorStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
                
                SQLCloseCursor(catStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
                
                SQLCloseCursor(filmStmt);
                SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

                odbc_disconnect(env, dbc);
                return EXIT_FAILURE;
            }
        } else {
            SQLCloseCursor(payStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
            
            SQLCloseCursor(rentStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
            
            SQLCloseCursor(invStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
            
            SQLCloseCursor(actorStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
            
            SQLCloseCursor(catStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
            
            SQLCloseCursor(filmStmt);
            SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

            printf("The film id (%s) doesn't exist in payment or it has already been removed.\n", name1);
            odbc_disconnect(env, dbc);
            return EXIT_FAILURE;
        }

        
    }
    /* Free everything */
    SQLCloseCursor(payStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, payStmt);
    
    SQLCloseCursor(rentStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, rentStmt);
    
    SQLCloseCursor(invStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, invStmt);
    
    SQLCloseCursor(actorStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, actorStmt);
    
    SQLCloseCursor(catStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, catStmt);
    
    SQLCloseCursor(filmStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, filmStmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
