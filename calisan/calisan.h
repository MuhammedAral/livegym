#pragma once
#include <string>
#include <vector>

class Calisan {
private:
    int id;
    std::string ad;
    std::string soyad;
    std::string pozisyon; // Antrenor, Resepsiyonist, Temizlik
    std::vector<int> sorumluUyeler; // atanan uyelerin id listesi

public:
    Calisan(int _id, std::string _ad, std::string _soyad, std::string _pozisyon);
    void uyeAta(int uyeId);
    void uyeCikar(int uyeId);
    void sorumluListele();
    void bilgiGoster();
    int getId();
    std::string getAd();
    std::string getSoyad();
    std::string getPozisyon();
    int getSorumluSayisi();
};
