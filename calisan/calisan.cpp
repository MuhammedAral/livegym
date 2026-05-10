#include "calisan.h"
#include <iostream>

Calisan::Calisan(int _id, std::string _ad, std::string _soyad, std::string _pozisyon) {
    id = _id;
    ad = _ad;
    soyad = _soyad;
    pozisyon = _pozisyon;
}

void Calisan::uyeAta(int uyeId) {
    // once kontrol et, zaten atanmis mi
    for (int i = 0; i < sorumluUyeler.size(); i++) {
        if (sorumluUyeler[i] == uyeId) {
            std::cout << "Bu uye zaten bu calisana atanmis!\n";
            return;
        }
    }
    sorumluUyeler.push_back(uyeId);
    std::cout << "Uye " << uyeId << " calisana atandi (" << ad << " " << soyad << ")\n";
}

void Calisan::uyeCikar(int uyeId) {
    for (int i = 0; i < sorumluUyeler.size(); i++) {
        if (sorumluUyeler[i] == uyeId) {
            sorumluUyeler.erase(sorumluUyeler.begin() + i);
            std::cout << "Uye " << uyeId << " calisandan cikarildi.\n";
            return;
        }
    }
    std::cout << "Bu uye bu calisana atanmamis!\n";
}

void Calisan::sorumluListele() {
    std::cout << ad << " " << soyad << " - Sorumlu Uyeler: ";
    if (sorumluUyeler.empty()) {
        std::cout << "Yok\n";
        return;
    }
    for (int i = 0; i < sorumluUyeler.size(); i++) {
        std::cout << sorumluUyeler[i];
        if (i < sorumluUyeler.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";
}

void Calisan::bilgiGoster() {
    std::cout << "ID: " << id << " | " << ad << " " << soyad
              << " | Pozisyon: " << pozisyon
              << " | Sorumlu Uye Sayisi: " << sorumluUyeler.size() << "\n";
}

int Calisan::getId() { return id; }
std::string Calisan::getAd() { return ad; }
std::string Calisan::getSoyad() { return soyad; }
std::string Calisan::getPozisyon() { return pozisyon; }
int Calisan::getSorumluSayisi() { return sorumluUyeler.size(); }
