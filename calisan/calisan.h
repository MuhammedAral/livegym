#pragma once
#include "../veritabani/veritabani.h"
#include "../uye/uye.h"

class Calisan {
public:
    static bool cagir(Veritabani& db, Uye& aktifUye);
    static void cagrilarGoster(Veritabani& db);
    static bool cagriTamamla(Veritabani& db, int cagriId);
};
