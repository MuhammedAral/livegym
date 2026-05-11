#include "uygulama.h"
#include "../makine/makine.h"
#include "../dolap/dolap.h"
#include "../calisan/calisan.h"
#include <iostream>
#include <string>

using namespace std;

Uygulama::Uygulama() {
}

void Uygulama::baslat() {
    if (!db.baglan()) {
        cout << "Veritabani baglantisi basarisiz!\nProgram kapatiliyor...\n";
        return;
    }
    cout << "Veritabanina basariyla baglandi!\n";
    anaMenu();
}

void Uygulama::uyeMenusu() {
    int secim;
    do {
        cout << "\n========================================\n";
        cout << "   SPOR SALONU PANELI - HOS GELDIN " << aktifUye.getAdSoyad() << "\n";
        cout << "========================================\n";
        cout << "1. Makineleri Goruntule\n";
        cout << "2. Makineyi Kullanima Al\n";
        cout << "3. Makineyi Birak\n";
        cout << "4. Soyunma Dolaplarini Goruntule (" << aktifUye.getCinsiyet() << ")\n";
        cout << "5. Dolabi Kullanima Al\n";
        cout << "6. Dolabi Bosalt\n";
        cout << "7. Calisan Cagir (Yardim Iste)\n";
        cout << "0. Cikis Yap (Oturumu Kapat)\n";
        cout << "========================================\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            Makine::listele(db);
        }
        else if (secim == 2) {
            int id;
            cout << "Kullanmak istediginiz Makine ID: "; cin >> id;
            if(Makine::kullan(db, aktifUye, id)) cout << "Makine basariyla size tahsis edildi!\n";
            else cout << "HATA: Makine bulunamadi veya su an mesgul!\n";
        }
        else if (secim == 3) {
            int id;
            cout << "Birakmak istediginiz Makine ID: "; cin >> id;
            if(Makine::birak(db, aktifUye, id)) cout << "Makine basariyla bosaltildi!\n";
            else cout << "HATA: Makine size ait degil veya bulunamadi!\n";
        }
        else if (secim == 4) {
            Dolap::listele(db, aktifUye);
        }
        else if (secim == 5) {
            int id;
            cout << "Kullanmak istediginiz Dolap ID: "; cin >> id;
            if(Dolap::kullan(db, aktifUye, id)) cout << "Dolap basariyla size tahsis edildi!\n";
            else cout << "HATA: Dolap bulunamadi, su an dolu veya cinsiyetinize uygun degil!\n";
        }
        else if (secim == 6) {
            int id;
            cout << "Bosaltmak istediginiz Dolap ID: "; cin >> id;
            if(Dolap::birak(db, aktifUye, id)) cout << "Dolap basariyla bosaltildi!\n";
            else cout << "HATA: Dolap size ait degil veya bulunamadi!\n";
        }
        else if (secim == 7) {
            if(Calisan::cagir(db, aktifUye)) cout << "Calisan cagrildi. Lutfen bekleyin...\n";
            else cout << "HATA: Cagri basarisiz oldu!\n";
        }

    } while (secim != 0);
    
    aktifUye.cikisYap();
    cout << "Oturum kapatildi.\n";
}

void Uygulama::adminMenusu() {
    int secim;
    do {
        cout << "\n========================================\n";
        cout << "        ADMIN YONETIM PANELI\n";
        cout << "========================================\n";
        cout << "1. Tum Makineleri ve Doluluklarini Gor\n";
        cout << "2. Bir Makineyi Zorla Bosalt\n";
        cout << "3. Tum Dolaplari Gor (Kadin/Erkek Karma)\n";
        cout << "4. Bir Dolabi Zorla Bosalt\n";
        cout << "5. Gelen Calisan Cagrilarini Gor\n";
        cout << "6. Calisan Cagrisini Tamamlandi Isaretle\n";
        cout << "0. Cikis Yap (Oturumu Kapat)\n";
        cout << "========================================\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            Makine::listele(db);
        }
        else if (secim == 2) {
            int id;
            cout << "Bosaltilacak Makine ID: "; cin >> id;
            if(Makine::birak(db, aktifUye, id)) cout << "Makine admin tarafindan bosaltildi!\n";
            else cout << "HATA: Islem basarisiz!\n";
        }
        else if (secim == 3) {
            Dolap::listele(db, aktifUye);
        }
        else if (secim == 4) {
            int id;
            cout << "Bosaltilacak Dolap ID: "; cin >> id;
            if(Dolap::birak(db, aktifUye, id)) cout << "Dolap admin tarafindan bosaltildi!\n";
            else cout << "HATA: Islem basarisiz!\n";
        }
        else if (secim == 5) {
            Calisan::cagrilarGoster(db);
        }
        else if (secim == 6) {
            int id;
            cout << "Tamamlanacak Cagri ID: "; cin >> id;
            if(Calisan::cagriTamamla(db, id)) cout << "Cagri tamamlandi olarak isaretlendi!\n";
            else cout << "HATA: Cagri bulunamadi!\n";
        }
    } while (secim != 0);

    aktifUye.cikisYap();
    cout << "Oturum kapatildi.\n";
}

void Uygulama::anaMenu() {
    int secim;
    do {
        cout << "\n========================================\n";
        cout << "       SPOR SALONU GIRIS SISTEMI\n";
        cout << "========================================\n";
        cout << "1. Giris Yap\n";
        cout << "2. Kayit Ol\n";
        cout << "0. Programi Kapat\n";
        cout << "========================================\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            string kAdi, sifre;
            cout << "Kullanici Adi: "; cin >> kAdi;
            cout << "Sifre: "; cin >> sifre;

            if (aktifUye.girisYap(db, kAdi, sifre)) {
                cout << "\nBasariyla giris yapildi!\n";
                if (aktifUye.getRol() == "admin") {
                    adminMenusu();
                } else {
                    uyeMenusu();
                }
            } else {
                cout << "HATA: Kullanici adi veya sifre yanlis!\n";
            }
        }
        else if (secim == 2) {
            string kAdi, sifre, ad, soyad, telefon, cinsiyet;
            cout << "Kullanici Adi: "; cin >> kAdi;
            cout << "Sifre: "; cin >> sifre;
            cout << "Ad: "; cin >> ad;
            cout << "Soyad: "; cin >> soyad;
            cout << "Telefon: "; cin >> telefon;
            cout << "Cinsiyet (Erkek/Kadin): "; cin >> cinsiyet;

            if (aktifUye.kayitOl(db, kAdi, sifre, ad, soyad, telefon, cinsiyet)) {
                cout << "Kayit basarili! Simdi giris yapabilirsiniz.\n";
            } else {
                cout << "HATA: Kayit olusturulamadi. Kullanici adi zaten alinmis olabilir.\n";
            }
        }
    } while (secim != 0);

    cout << "Program kapatiliyor...\n";
}
