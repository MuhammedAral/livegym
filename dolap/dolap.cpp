#include "dolap.h"
#include <iostream>
#include <string>

using namespace std;

void Dolap::listele(Veritabani& db, Uye& aktifUye) {
    if (!db.getBagliMi()) return;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string filtre = "";
    if (aktifUye.getRol() != "admin" && aktifUye.getCinsiyet() != "") {
        filtre = " WHERE d.Bolum = '" + aktifUye.getCinsiyet() + "'";
    }
    string sorgu = "SELECT d.DolapID, d.DolapNo, d.Bolum, d.Durum, ISNULL(u.Ad + ' ' + u.Soyad, '') FROM Dolaplar d LEFT JOIN Uyeler u ON d.KullananUyeID = u.UyeID" + filtre;
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id, no, durum;
        SQLCHAR bolum[20], kullanan[100];
        SQLLEN ind;

        cout << "\n--- SOYUNMA ODASI DOLAPLARI ---\n";
        cout << "ID\tDolap No\tBolum\tDurum\tKullanan\n";
        cout << "--------------------------------------------------------\n";
        SQLRETURN fetchRet;
        while ((fetchRet = SQLFetch(hStmt)) == SQL_SUCCESS || fetchRet == SQL_SUCCESS_WITH_INFO) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_LONG, &no, 0, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, bolum, 20, &ind);
            SQLGetData(hStmt, 4, SQL_C_LONG, &durum, 0, &ind);
            SQLGetData(hStmt, 5, SQL_C_CHAR, kullanan, 100, &ind);

            string durumStr = (durum == 1) ? "[DOLU]" : "[BOS] ";
            string kullananStr = (durum == 1) ? (char*)kullanan : "-";

            cout << id << "\t" << no << "\t\t" << bolum << "\t" << durumStr << "\t" << kullananStr << "\n";
        }
        cout << "--------------------------------------------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

bool Dolap::kullan(Veritabani& db, Uye& aktifUye, int dolapId) {
    if (!db.getBagliMi() || aktifUye.getId() == 0) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "UPDATE Dolaplar SET Durum = 1, KullananUyeID = " + to_string(aktifUye.getId()) + " WHERE DolapID = " + to_string(dolapId) + " AND Durum = 0 AND Bolum = '" + aktifUye.getCinsiyet() + "'";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (rowCount > 0);
}

bool Dolap::birak(Veritabani& db, Uye& aktifUye, int dolapId) {
    if (!db.getBagliMi() || aktifUye.getId() == 0) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string adminSarti = (aktifUye.getRol() == "admin") ? "" : " AND KullananUyeID = " + to_string(aktifUye.getId());
    string sorgu = "UPDATE Dolaplar SET Durum = 0, KullananUyeID = NULL WHERE DolapID = " + to_string(dolapId) + adminSarti;
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (rowCount > 0);
}
