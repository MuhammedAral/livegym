#pragma once
#include "../veritabani/veritabani.h"
#include "../uye/uye.h"

class Dolap {
public:
    static void listele(Veritabani& db, Uye& aktifUye);
    static bool kullan(Veritabani& db, Uye& aktifUye, int dolapId);
    static bool birak(Veritabani& db, Uye& aktifUye, int dolapId);
};
