#include <iostream>
#include <string>
#include "veritabani/veritabani.h"

using namespace std;

void uyeMenusu(Veritabani &db) {
    int secim;
    do {
        cout << "\n--- UYE ISLEMLERI ---\n";
        cout << "1. Uye Ekle\n";
        cout << "2. Uye Sil\n";
        cout << "3. Uyeleri Listele\n";
        cout << "0. Geri Don\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            string ad, soyad, cinsiyet, telefon, baslangic, bitis;
            int yas;
            cout << "Ad: "; cin >> ad;
            cout << "Soyad: "; cin >> soyad;
            cout << "Yas: "; cin >> yas;
            cout << "Cinsiyet (Erkek/Kadin): "; cin >> cinsiyet;
            cout << "Telefon: "; cin >> telefon;
            cout << "Uyelik Baslangic (YYYY-MM-DD): "; cin >> baslangic;
            cout << "Uyelik Bitis (YYYY-MM-DD): "; cin >> bitis;
            db.uyeEkle(ad, soyad, yas, cinsiyet, telefon, baslangic, bitis);
        }
        else if (secim == 2) {
            int id;
            cout << "Silinecek Uye ID: "; cin >> id;
            db.uyeSil(id);
        }
        else if (secim == 3) {
            db.uyeListele();
        }
    } while (secim != 0);
}

void dolapMenusu(Veritabani &db) {
    int secim;
    do {
        cout << "\n--- DOLAP ISLEMLERI ---\n";
        cout << "1. Dolap Ekle\n";
        cout << "2. Dolabi Uyeye Ata\n";
        cout << "3. Dolabi Bosalt\n";
        cout << "4. Dolaplari Listele\n";
        cout << "0. Geri Don\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            int dolapNo;
            string bolum;
            cout << "Dolap No: "; cin >> dolapNo;
            cout << "Bolum (Erkek/Kadin): "; cin >> bolum;
            db.dolapEkle(dolapNo, bolum);
        }
        else if (secim == 2) {
            int dolapId, uyeId;
            cout << "Dolap ID: "; cin >> dolapId;
            cout << "Uye ID: "; cin >> uyeId;
            db.dolapAtaUye(dolapId, uyeId);
        }
        else if (secim == 3) {
            int dolapId;
            cout << "Bosaltilacak Dolap ID: "; cin >> dolapId;
            db.dolapBosalt(dolapId);
        }
        else if (secim == 4) {
            db.dolapListele();
        }
    } while (secim != 0);
}

void makineMenusu(Veritabani &db) {
    int secim;
    do {
        cout << "\n--- MAKINE ISLEMLERI ---\n";
        cout << "1. Makine Ekle\n";
        cout << "2. Makineyi Kullanima Al (Sensor: 1)\n";
        cout << "3. Makineyi Bosalt (Sensor: 0)\n";
        cout << "4. Makineleri Listele\n";
        cout << "0. Geri Don\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            string ad;
            cout << "Makine Adi: ";
            cin.ignore();
            getline(cin, ad);
            db.makineEkle(ad);
        }
        else if (secim == 2) {
            int id;
            cout << "Makine ID: "; cin >> id;
            db.makineKullanBasla(id);
        }
        else if (secim == 3) {
            int id;
            cout << "Makine ID: "; cin >> id;
            db.makineBosalt(id);
        }
        else if (secim == 4) {
            db.makineListele();
        }
    } while (secim != 0);
}

void calisanMenusu(Veritabani &db) {
    int secim;
    do {
        cout << "\n--- CALISAN ISLEMLERI ---\n";
        cout << "1. Calisan Ekle\n";
        cout << "2. Calisan Sil\n";
        cout << "3. Calisana Uye Ata\n";
        cout << "4. Calisandan Uye Cikar\n";
        cout << "5. Calisanlari Listele\n";
        cout << "6. Calisan Sorumlu Uyeleri Goster\n";
        cout << "0. Geri Don\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            string ad, soyad, pozisyon;
            cout << "Ad: "; cin >> ad;
            cout << "Soyad: "; cin >> soyad;
            cout << "Pozisyon (Antrenor/Resepsiyonist/Temizlik): "; cin >> pozisyon;
            db.calisanEkle(ad, soyad, pozisyon);
        }
        else if (secim == 2) {
            int id;
            cout << "Silinecek Calisan ID: "; cin >> id;
            db.calisanSil(id);
        }
        else if (secim == 3) {
            int calisanId, uyeId;
            cout << "Calisan ID: "; cin >> calisanId;
            cout << "Atanacak Uye ID: "; cin >> uyeId;
            db.calisanaUyeAta(calisanId, uyeId);
        }
        else if (secim == 4) {
            int calisanId, uyeId;
            cout << "Calisan ID: "; cin >> calisanId;
            cout << "Cikarilacak Uye ID: "; cin >> uyeId;
            db.calisandanUyeCikar(calisanId, uyeId);
        }
        else if (secim == 5) {
            db.calisanListele();
        }
        else if (secim == 6) {
            int id;
            cout << "Calisan ID: "; cin >> id;
            db.calisanUyeleriGoster(id);
        }
    } while (secim != 0);
}

int main() {
    Veritabani db;

    if (!db.baglan()) {
        cout << "Program kapatiliyor...\n";
        return 1;
    }

    int secim;
    do {
        cout << "\n========================================\n";
        cout << "     SPOR SALONU TAKIP SISTEMI\n";
        cout << "========================================\n";
        cout << "1. Uye Islemleri\n";
        cout << "2. Dolap Islemleri\n";
        cout << "3. Makine Islemleri\n";
        cout << "4. Calisan Islemleri\n";
        cout << "5. Genel Durum Raporu\n";
        cout << "0. Cikis\n";
        cout << "========================================\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: uyeMenusu(db); break;
            case 2: dolapMenusu(db); break;
            case 3: makineMenusu(db); break;
            case 4: calisanMenusu(db); break;
            case 5: db.genelRapor(); break;
            case 0: cout << "Cikis yapiliyor...\n"; break;
            default: cout << "Gecersiz secim!\n";
        }
    } while (secim != 0);

    db.baglantiKes();
    return 0;
}
