#include "makine.h"
#include <iostream>

Makine::Makine(int _id, std::string _ad) {
    id = _id;
    ad = _ad;
    doluMu = false;
}

void Makine::kullanilmayaBaslandi() {
    doluMu = true;
    std::cout << ad << " makinesi su an kullaniliyor (Sensor: 1)\n";
}

void Makine::bosaCikti() {
    doluMu = false;
    std::cout << ad << " makinesi bosaldi (Sensor: 0)\n";
}

int Makine::getSensorDurumu() {
    return doluMu ? 1 : 0;
}

int Makine::getId() { return id; }
std::string Makine::getAd() { return ad; }
