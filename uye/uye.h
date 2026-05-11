#pragma once
#include <string>
#include "../veritabani/veritabani.h"

using namespace std;

class Uye {
private:
    int id;
    string adSoyad;
    string rol;
    string cinsiyet;

public:
    Uye();
    bool girisYap(Veritabani& db, string kAdi, string sifre);
    bool kayitOl(Veritabani& db, string kAdi, string sifre, string ad, string soyad, string telefon, string cinsiyet);
    void cikisYap();

    int getId();
    string getAdSoyad();
    string getRol();
    string getCinsiyet();
};
