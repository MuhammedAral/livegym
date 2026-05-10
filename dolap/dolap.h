#pragma once
#include <string>

class Dolap {
private:
    int id;
    int dolapNo;
    bool doluMu;
    int kullananUyeId; // dolabi kullanan uyenin id'si, 0 ise bos
    std::string bolum; // "Erkek" veya "Kadin"

public:
    Dolap(int _id, int _dolapNo, std::string _bolum);
    bool uyeAta(int uyeId);   // dolabi bir uyeye atar
    void bosalt();             // dolabi bosaltir
    int getDurum();            // 1 dolu, 0 bos
    void durumGoster();
    int getId();
    int getDolapNo();
    std::string getBolum();
    int getKullananUyeId();
};
