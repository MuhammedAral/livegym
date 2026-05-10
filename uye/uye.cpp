#include "uye.h"
#include <iostream>

Uye::Uye(int _id, std::string _ad, std::string _soyad, int _yas, std::string _cinsiyet, std::string _telefon, std::string _baslangic, std::string _bitis) {
    id = _id;
    ad = _ad;
    soyad = _soyad;
    yas = _yas;
    cinsiyet = _cinsiyet;
    telefon = _telefon;
    uyelikBaslangic = _baslangic;
    uyelikBitis = _bitis;
    aktifMi = true;
}

void Uye::bilgiGoster() {
    std::cout << "ID: " << id << " | " << ad << " " << soyad
              << " | Yas: " << yas << " | " << cinsiyet
              << " | Tel: " << telefon
              << " | Uyelik: " << uyelikBaslangic << " - " << uyelikBitis
              << " | " << (aktifMi ? "Aktif" : "Pasif") << "\n";
}

int Uye::getId() { return id; }
std::string Uye::getAd() { return ad; }
std::string Uye::getSoyad() { return soyad; }
int Uye::getYas() { return yas; }
std::string Uye::getCinsiyet() { return cinsiyet; }
std::string Uye::getTelefon() { return telefon; }
std::string Uye::getBaslangic() { return uyelikBaslangic; }
std::string Uye::getBitis() { return uyelikBitis; }
bool Uye::isAktif() { return aktifMi; }
void Uye::pasifYap() { aktifMi = false; }
void Uye::aktifYap() { aktifMi = true; }
