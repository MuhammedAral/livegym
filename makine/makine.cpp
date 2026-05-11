#include "makine.h"
#include <iostream>
#include <string>

using namespace std;

void Makine::listele(Veritabani& db) {
    if (!db.getBagliMi()) return;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "SELECT m.MakineID, m.MakineAdi, m.Durum, ISNULL(u.Ad + ' ' + u.Soyad, '') FROM Makineler m LEFT JOIN Uyeler u ON m.KullananUyeID = u.UyeID";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id, durum;
        SQLCHAR ad[50], kullanan[100];
        SQLLEN ind;

        cout << "\n--- MAKINELER ---\n";
        cout << "ID\tDurum\tMakine Adi\t\tKullanan\n";
        cout << "--------------------------------------------------------\n";
        SQLRETURN fetchRet;
        while ((fetchRet = SQLFetch(hStmt)) == SQL_SUCCESS || fetchRet == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_LONG, &durum, 0, &ind);
            SQLGetData(hStmt, 4, SQL_C_CHAR, kullanan, 100, &ind);

            string durumStr = (durum == 1) ? "[DOLU]" : "[BOS] ";
            string kullananStr = (durum == 1) ? (char*)kullanan : "-";

            cout << id << "\t" << durumStr << "\t" << ad;
            if (string((char*)ad).length() < 12) cout << "\t";
            cout << "\t" << kullananStr << "\n";
        }
        cout << "--------------------------------------------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

bool Makine::kullan(Veritabani& db, Uye& aktifUye, int makineId) {
    if (!db.getBagliMi() || aktifUye.getId() == 0) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "UPDATE Makineler SET Durum = 1, KullananUyeID = " + to_string(aktifUye.getId()) + " WHERE MakineID = " + to_string(makineId) + " AND Durum = 0";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (rowCount > 0);
}

bool Makine::birak(Veritabani& db, Uye& aktifUye, int makineId) {
    if (!db.getBagliMi() || aktifUye.getId() == 0) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string adminSarti = (aktifUye.getRol() == "admin") ? "" : " AND KullananUyeID = " + to_string(aktifUye.getId());
    string sorgu = "UPDATE Makineler SET Durum = 0, KullananUyeID = NULL WHERE MakineID = " + to_string(makineId) + adminSarti;
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (rowCount > 0);
}
