#pragma once
#include <string>

class Uye {
private:
    int id;
    std::string ad;
    std::string soyad;
    int yas;
    std::string cinsiyet;
    std::string telefon;
    std::string uyelikBaslangic;
    std::string uyelikBitis;
    bool aktifMi;

public:
    Uye(int _id, std::string _ad, std::string _soyad, int _yas, std::string _cinsiyet, std::string _telefon, std::string _baslangic, std::string _bitis);
    void bilgiGoster();
    int getId();
    std::string getAd();
    std::string getSoyad();
    int getYas();
    std::string getCinsiyet();
    std::string getTelefon();
    std::string getBaslangic();
    std::string getBitis();
    bool isAktif();
    void pasifYap();
    void aktifYap();
};
