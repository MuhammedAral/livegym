#include "uye.h"
#include <iostream>

using namespace std;

Uye::Uye() {
    cikisYap();
}

bool Uye::girisYap(Veritabani& db, string kAdi, string sifre) {
    if (!db.getBagliMi()) return false;

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);

    string sorgu = "SELECT UyeID, Ad, Soyad, Rol, ISNULL(Cinsiyet, 'Erkek') FROM Uyeler WHERE KullaniciAdi = '" + kAdi + "' AND Sifre = '" + sifre + "' AND AktifMi = 1";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    bool basarili = false;
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        if (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLINTEGER uid;
            SQLCHAR ad[50], soyad[50], urol[10], ucinsiyet[10];
            SQLLEN ind;

            SQLGetData(hStmt, 1, SQL_C_LONG, &uid, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, soyad, 50, &ind);
            SQLGetData(hStmt, 4, SQL_C_CHAR, urol, 10, &ind);
            SQLGetData(hStmt, 5, SQL_C_CHAR, ucinsiyet, 10, &ind);

            id = uid;
            rol = (char*)urol;
            adSoyad = string((char*)ad) + " " + string((char*)soyad);
            cinsiyet = (char*)ucinsiyet;
            basarili = true;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return basarili;
}

bool Uye::kayitOl(Veritabani& db, string kAdi, string sifre, string ad, string soyad, string telefon, string cinsiyetStr) {
    if (!db.getBagliMi()) return false;
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getHDbc(), &hStmt);
    string sorgu = "INSERT INTO Uyeler (KullaniciAdi, Sifre, Ad, Soyad, Telefon, Cinsiyet) VALUES ('"
        + kAdi + "', '" + sifre + "', '" + ad + "', '" + soyad + "', '" + telefon + "', '" + cinsiyetStr + "')";
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
}

void Uye::cikisYap() {
    id = 0;
    rol = "";
    adSoyad = "";
    cinsiyet = "";
}

int Uye::getId() { return id; }
string Uye::getAdSoyad() { return adSoyad; }
string Uye::getRol() { return rol; }
string Uye::getCinsiyet() { return cinsiyet; }
