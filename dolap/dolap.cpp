#include "dolap.h"
#include <iostream>

Dolap::Dolap(int _id, int _dolapNo, std::string _bolum) {
    id = _id;
    dolapNo = _dolapNo;
    doluMu = false;
    kullananUyeId = 0;
    bolum = _bolum;
}

bool Dolap::uyeAta(int uyeId) {
    if (doluMu) {
        std::cout << "Dolap " << dolapNo << " zaten dolu!\n";
        return false;
    }
    kullananUyeId = uyeId;
    doluMu = true;
    std::cout << "Dolap " << dolapNo << " uyeye atandi (Uye ID: " << uyeId << ")\n";
    return true;
}

void Dolap::bosalt() {
    if (!doluMu) {
        std::cout << "Dolap " << dolapNo << " zaten bos!\n";
        return;
    }
    std::cout << "Dolap " << dolapNo << " bosaltildi (Eski Uye ID: " << kullananUyeId << ")\n";
    kullananUyeId = 0;
    doluMu = false;
}

int Dolap::getDurum() {
    return doluMu ? 1 : 0;
}

void Dolap::durumGoster() {
    std::cout << "Dolap No: " << dolapNo << " | Bolum: " << bolum
              << " | Durum: " << (doluMu ? "DOLU" : "BOS");
    if (doluMu) std::cout << " | Uye ID: " << kullananUyeId;
    std::cout << "\n";
}

int Dolap::getId() { return id; }
int Dolap::getDolapNo() { return dolapNo; }
std::string Dolap::getBolum() { return bolum; }
int Dolap::getKullananUyeId() { return kullananUyeId; }
