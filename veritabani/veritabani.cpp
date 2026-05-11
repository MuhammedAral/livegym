#include "veritabani.h"
#include <iostream>

using namespace std;

Veritabani::Veritabani() {
    hEnv = NULL;
    hDbc = NULL;
    bagliMi = false;
}

Veritabani::~Veritabani() {
    if (bagliMi) baglantiKes();
}

bool Veritabani::baglan() {
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    SQLCHAR connStr[] = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost\\SQLEXPRESS;DATABASE=SporSalonuDB;Trusted_Connection=yes;";
    SQLCHAR outStr[1024];
    SQLSMALLINT outLen;

    SQLRETURN ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, outStr, 1024, &outLen, SQL_DRIVER_NOPROMPT);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        bagliMi = true;
        return true;
    }
    return false;
}

void Veritabani::baglantiKes() {
    if (bagliMi) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        bagliMi = false;
    }
}

bool Veritabani::getBagliMi() {
    return bagliMi;
}

SQLHDBC Veritabani::getHDbc() {
    return hDbc;
}
