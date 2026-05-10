#include "veritabani.h"
#include <iostream>

Veritabani::Veritabani() {
    hEnv = NULL;
    hDbc = NULL;
    bagliMi = false;
}

Veritabani::~Veritabani() {
    if (bagliMi) baglantiKes();
}

bool Veritabani::baglan() {
    // ortam handle olustur
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // baglanti handle olustur
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // mssql baglanti stringi
    SQLCHAR connStr[] = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;DATABASE=SporSalonuDB;Trusted_Connection=yes;";
    SQLCHAR outStr[1024];
    SQLSMALLINT outLen;

    SQLRETURN ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, outStr, 1024, &outLen, SQL_DRIVER_NOPROMPT);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        bagliMi = true;
        std::cout << "Veritabanina basariyla baglandi.\n";
        return true;
    }
    std::cout << "Veritabani baglantisi basarisiz!\n";
    return false;
}

void Veritabani::baglantiKes() {
    if (bagliMi) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        bagliMi = false;
        std::cout << "Veritabani baglantisi kesildi.\n";
    }
}

// ===================== UYE ISLEMLERI =====================

bool Veritabani::uyeEkle(std::string ad, std::string soyad, int yas, std::string cinsiyet, std::string telefon, std::string baslangic, std::string bitis) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "INSERT INTO Uyeler (Ad, Soyad, Yas, Cinsiyet, TelefonNo, UyelikBaslangic, UyelikBitis, AktifMi) VALUES ('"
        + ad + "', '" + soyad + "', " + std::to_string(yas) + ", '" + cinsiyet + "', '"
        + telefon + "', '" + baslangic + "', '" + bitis + "', 1)";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Uye basariyla eklendi.\n";
        return true;
    }
    std::cout << "Uye eklenemedi!\n";
    return false;
}

bool Veritabani::uyeSil(int uyeId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "DELETE FROM Uyeler WHERE UyeID = " + std::to_string(uyeId);
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Uye silindi.\n";
        return true;
    }
    std::cout << "Uye silinemedi!\n";
    return false;
}

void Veritabani::uyeListele() {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)"SELECT UyeID, Ad, Soyad, Yas, Cinsiyet, TelefonNo, UyelikBaslangic, UyelikBitis, AktifMi FROM Uyeler", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id, yas, aktif;
        SQLCHAR ad[50], soyad[50], cinsiyet[10], telefon[15], baslangic[20], bitis[20];
        SQLLEN ind;

        std::cout << "\n--- UYE LISTESI ---\n";
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, soyad, 50, &ind);
            SQLGetData(hStmt, 4, SQL_C_LONG, &yas, 0, &ind);
            SQLGetData(hStmt, 5, SQL_C_CHAR, cinsiyet, 10, &ind);
            SQLGetData(hStmt, 6, SQL_C_CHAR, telefon, 15, &ind);
            SQLGetData(hStmt, 7, SQL_C_CHAR, baslangic, 20, &ind);
            SQLGetData(hStmt, 8, SQL_C_CHAR, bitis, 20, &ind);
            SQLGetData(hStmt, 9, SQL_C_LONG, &aktif, 0, &ind);

            std::cout << "ID: " << id << " | " << ad << " " << soyad
                      << " | Yas: " << yas << " | " << cinsiyet
                      << " | Tel: " << telefon
                      << " | " << baslangic << " - " << bitis
                      << " | " << (aktif ? "Aktif" : "Pasif") << "\n";
        }
        std::cout << "-------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

// ===================== DOLAP ISLEMLERI =====================

bool Veritabani::dolapEkle(int dolapNo, std::string bolum) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "INSERT INTO Dolaplar (DolapNo, Durum, KullananUyeID, Bolum) VALUES ("
        + std::to_string(dolapNo) + ", 0, NULL, '" + bolum + "')";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Dolap eklendi.\n";
        return true;
    }
    std::cout << "Dolap eklenemedi!\n";
    return false;
}

bool Veritabani::dolapAtaUye(int dolapId, int uyeId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "UPDATE Dolaplar SET Durum = 1, KullananUyeID = " + std::to_string(uyeId)
        + " WHERE DolapID = " + std::to_string(dolapId) + " AND Durum = 0";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (rowCount > 0) {
        std::cout << "Dolap uyeye atandi.\n";
        return true;
    }
    std::cout << "Dolap atanamadi (dolu veya bulunamadi)!\n";
    return false;
}

bool Veritabani::dolapBosalt(int dolapId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "UPDATE Dolaplar SET Durum = 0, KullananUyeID = NULL WHERE DolapID = " + std::to_string(dolapId);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Dolap bosaltildi.\n";
        return true;
    }
    std::cout << "Dolap bosaltilamadi!\n";
    return false;
}

void Veritabani::dolapListele() {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)"SELECT DolapID, DolapNo, Durum, KullananUyeID, Bolum FROM Dolaplar", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id, dolapNo, durum, uyeId;
        SQLCHAR bolum[10];
        SQLLEN ind, uyeInd;

        std::cout << "\n--- DOLAP LISTESI ---\n";
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_LONG, &dolapNo, 0, &ind);
            SQLGetData(hStmt, 3, SQL_C_LONG, &durum, 0, &ind);
            SQLGetData(hStmt, 4, SQL_C_LONG, &uyeId, 0, &uyeInd);
            SQLGetData(hStmt, 5, SQL_C_CHAR, bolum, 10, &ind);

            std::cout << "ID: " << id << " | Dolap No: " << dolapNo
                      << " | Bolum: " << bolum
                      << " | Durum: " << (durum ? "DOLU" : "BOS");
            if (durum && uyeInd != SQL_NULL_DATA) std::cout << " | Uye ID: " << uyeId;
            std::cout << "\n";
        }
        std::cout << "---------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

// ===================== MAKINE ISLEMLERI =====================

bool Veritabani::makineEkle(std::string ad) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "INSERT INTO Makineler (MakineAdi, Durum) VALUES ('" + ad + "', 0)";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Makine eklendi.\n";
        return true;
    }
    std::cout << "Makine eklenemedi!\n";
    return false;
}

bool Veritabani::makineKullanBasla(int makineId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "UPDATE Makineler SET Durum = 1 WHERE MakineID = " + std::to_string(makineId) + " AND Durum = 0";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    SQLLEN rowCount = 0;
    SQLRowCount(hStmt, &rowCount);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (rowCount > 0) {
        std::cout << "Makine kullanima alindi (Sensor: 1)\n";
        return true;
    }
    std::cout << "Makine kullanilamadi (zaten dolu veya bulunamadi)!\n";
    return false;
}

bool Veritabani::makineBosalt(int makineId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "UPDATE Makineler SET Durum = 0 WHERE MakineID = " + std::to_string(makineId);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Makine bosaltildi (Sensor: 0)\n";
        return true;
    }
    std::cout << "Makine bosaltilamadi!\n";
    return false;
}

void Veritabani::makineListele() {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)"SELECT MakineID, MakineAdi, Durum FROM Makineler", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id, durum;
        SQLCHAR ad[50];
        SQLLEN ind;

        std::cout << "\n--- MAKINE LISTESI ---\n";
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_LONG, &durum, 0, &ind);

            std::cout << "ID: " << id << " | " << ad
                      << " | Sensor: " << durum
                      << " (" << (durum ? "MESGUL" : "BOS") << ")\n";
        }
        std::cout << "----------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

// ===================== CALISAN ISLEMLERI =====================

bool Veritabani::calisanEkle(std::string ad, std::string soyad, std::string pozisyon) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "INSERT INTO Calisanlar (Ad, Soyad, Pozisyon) VALUES ('"
        + ad + "', '" + soyad + "', '" + pozisyon + "')";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Calisan eklendi.\n";
        return true;
    }
    std::cout << "Calisan eklenemedi!\n";
    return false;
}

bool Veritabani::calisanSil(int calisanId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // once atamalari sil
    std::string sorgu1 = "DELETE FROM CalisanUyeAtama WHERE CalisanID = " + std::to_string(calisanId);
    SQLExecDirect(hStmt, (SQLCHAR*)sorgu1.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // sonra calisani sil
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    std::string sorgu2 = "DELETE FROM Calisanlar WHERE CalisanID = " + std::to_string(calisanId);
    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu2.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Calisan silindi.\n";
        return true;
    }
    std::cout << "Calisan silinemedi!\n";
    return false;
}

bool Veritabani::calisanaUyeAta(int calisanId, int uyeId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "INSERT INTO CalisanUyeAtama (CalisanID, UyeID) VALUES ("
        + std::to_string(calisanId) + ", " + std::to_string(uyeId) + ")";

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Uye calisana atandi.\n";
        return true;
    }
    std::cout << "Atama yapilamadi!\n";
    return false;
}

bool Veritabani::calisandanUyeCikar(int calisanId, int uyeId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return false; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "DELETE FROM CalisanUyeAtama WHERE CalisanID = " + std::to_string(calisanId)
        + " AND UyeID = " + std::to_string(uyeId);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Uye calisandan cikarildi.\n";
        return true;
    }
    std::cout << "Cikarma islemi basarisiz!\n";
    return false;
}

void Veritabani::calisanListele() {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)"SELECT CalisanID, Ad, Soyad, Pozisyon FROM Calisanlar", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id;
        SQLCHAR ad[50], soyad[50], pozisyon[30];
        SQLLEN ind;

        std::cout << "\n--- CALISAN LISTESI ---\n";
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, soyad, 50, &ind);
            SQLGetData(hStmt, 4, SQL_C_CHAR, pozisyon, 30, &ind);

            std::cout << "ID: " << id << " | " << ad << " " << soyad
                      << " | Pozisyon: " << pozisyon << "\n";
        }
        std::cout << "-----------------------\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void Veritabani::calisanUyeleriGoster(int calisanId) {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    std::string sorgu = "SELECT u.UyeID, u.Ad, u.Soyad FROM CalisanUyeAtama ca "
        "INNER JOIN Uyeler u ON ca.UyeID = u.UyeID WHERE ca.CalisanID = " + std::to_string(calisanId);

    SQLRETURN ret = SQLExecDirect(hStmt, (SQLCHAR*)sorgu.c_str(), SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLINTEGER id;
        SQLCHAR ad[50], soyad[50];
        SQLLEN ind;
        bool bulundu = false;

        std::cout << "\nCalisan " << calisanId << " - Sorumlu Uyeler:\n";
        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_LONG, &id, 0, &ind);
            SQLGetData(hStmt, 2, SQL_C_CHAR, ad, 50, &ind);
            SQLGetData(hStmt, 3, SQL_C_CHAR, soyad, 50, &ind);
            std::cout << "  - Uye ID: " << id << " | " << ad << " " << soyad << "\n";
            bulundu = true;
        }
        if (!bulundu) std::cout << "  Hic uye atanmamis.\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

// ===================== GENEL RAPOR =====================

void Veritabani::genelRapor() {
    if (!bagliMi) { std::cout << "Baglanti yok!\n"; return; }

    SQLHSTMT hStmt;
    SQLINTEGER sayi;
    SQLLEN ind;

    std::cout << "\n========= GENEL DURUM RAPORU =========\n";

    // toplam uye sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Uyeler", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Toplam Uye       : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // dolu dolap sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Dolaplar WHERE Durum = 1", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Dolu Dolap       : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // bos dolap sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Dolaplar WHERE Durum = 0", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Bos Dolap        : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // mesgul makine sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Makineler WHERE Durum = 1", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Mesgul Makine    : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // bos makine sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Makineler WHERE Durum = 0", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Bos Makine       : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    // calisan sayisi
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    SQLExecDirect(hStmt, (SQLCHAR*)"SELECT COUNT(*) FROM Calisanlar", SQL_NTS);
    if (SQLFetch(hStmt) == SQL_SUCCESS) {
        SQLGetData(hStmt, 1, SQL_C_LONG, &sayi, 0, &ind);
        std::cout << "Toplam Calisan   : " << sayi << "\n";
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    std::cout << "======================================\n";
}
