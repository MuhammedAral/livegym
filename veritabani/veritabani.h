#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

class Veritabani {
private:
    SQLHENV hEnv;
    SQLHDBC hDbc;
    bool bagliMi;

public:
    Veritabani();
    ~Veritabani();
    bool baglan();
    void baglantiKes();

    // uye islemleri
    bool uyeEkle(std::string ad, std::string soyad, int yas, std::string cinsiyet, std::string telefon, std::string baslangic, std::string bitis);
    bool uyeSil(int uyeId);
    void uyeListele();

    // dolap islemleri
    bool dolapEkle(int dolapNo, std::string bolum);
    bool dolapAtaUye(int dolapId, int uyeId);
    bool dolapBosalt(int dolapId);
    void dolapListele();

    // makine islemleri
    bool makineEkle(std::string ad);
    bool makineKullanBasla(int makineId);
    bool makineBosalt(int makineId);
    void makineListele();

    // calisan islemleri
    bool calisanEkle(std::string ad, std::string soyad, std::string pozisyon);
    bool calisanSil(int calisanId);
    bool calisanaUyeAta(int calisanId, int uyeId);
    bool calisandanUyeCikar(int calisanId, int uyeId);
    void calisanListele();
    void calisanUyeleriGoster(int calisanId);

    // rapor
    void genelRapor();
};
