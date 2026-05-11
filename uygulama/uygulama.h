#pragma once
#include "../veritabani/veritabani.h"
#include "../uye/uye.h"

class Uygulama {
private:
    Veritabani db;
    Uye aktifUye;

    void uyeMenusu();
    void adminMenusu();
    void anaMenu();

public:
    Uygulama();
    void baslat();
};
