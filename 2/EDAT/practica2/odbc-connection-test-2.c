#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/* test database connection */

int main(void) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret; /* ODBC API return status */

    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
      fprintf(stderr, "Failed to connect\n");
      odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
      return EXIT_FAILURE;
    }
    
    fprintf(stderr,"Successful connection\n");
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        fprintf(stderr,"Error when disconnecting\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
