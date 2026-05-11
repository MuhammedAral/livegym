#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

using namespace std;

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
    bool getBagliMi();
    SQLHDBC getHDbc();
};
