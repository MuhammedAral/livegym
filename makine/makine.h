#pragma once
#include "../veritabani/veritabani.h"
#include "../uye/uye.h"

class Makine {
public:
    static void listele(Veritabani& db);
    static bool kullan(Veritabani& db, Uye& aktifUye, int makineId);
    static bool birak(Veritabani& db, Uye& aktifUye, int makineId);
};
