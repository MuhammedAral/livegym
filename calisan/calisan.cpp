#include "calisan.h"
#include <iostream>
#include <string>

using namespace std;

bool Calisan::cagir(Veritabani& db, Uye& aktifUye) {
    if (!db.getBagliMi() || aktifUye.getId() == 0) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "INSERT INTO CalisanCagri (UyeID) VALUES (" + to_string(aktifUye.getId()) + ")";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

void Calisan::cagrilarGoster(Veritabani& db) {
    if (!db.getBagliMi()) return;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "SELECT c.CagriID, u.Ad + ' ' + u.Soyad, c.CagriZamani, c.Durum FROM CalisanCagri c JOIN Uyeler u ON c.UyeID = u.UyeID WHERE c.Durum = 'Bekliyor'";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id;
        SQLCHAR uye[100], zaman[50], durum[20];
        SQLLEN ind;

        cout << "\n--- BEKLEYEN CALISAN CAGRILARI ---\n";
        bool cagriVar = false;
        SQLRETURN fetchRet;
        while ((fetchRet = SQLFetch(hStmt)) == SQL_SUCCESS || fetchRet == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, uye, 100, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, zaman, 50, &ind);
            SQLGetData(hStmt, 4, SQL_C_CHAR, durum, 20, &ind);
            cout << "Cagri ID: " << id << " | Uye: " << uye << " | Zaman: " << zaman << " | Durum: " << durum << "\n";
            cagriVar = true;
        }
        if (!cagriVar) cout << "Bekleyen cagri bulunmamaktadir.\n";
        cout << "----------------------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

bool Calisan::cagriTamamla(Veritabani& db, int cagriId) {
    if (!db.getBagliMi()) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "UPDATE CalisanCagri SET Durum = 'Tamamlandi' WHERE CagriID = " + to_string(cagriId);
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (rowCount > 0);
}
