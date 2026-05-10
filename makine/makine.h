#pragma once
#include <string>

class Makine {
private:
    int id;
    std::string ad;
    bool doluMu;

public:
    Makine(int _id, std::string _ad);
    void kullanilmayaBaslandi();
    void bosaCikti();
    int getSensorDurumu();
    int getId();
    std::string getAd();
};
