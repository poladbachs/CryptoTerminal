#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <chrono>
#include <limits>
#include <map>
#include <vector>

#include <curl/curl.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void clear_screen();
void pause_execution();

double fetch_crypto_price(const string& symbol, const string& api_key);

class user {
protected:
    string username;
    string password;
    string susername;
    string spassword;
    ifstream infile;
    ofstream outfile;
    fstream file;
    ofstream ofs;
};

class login_trading : public user {
public:
    login_trading();

    void home();
    void registration();
    void login();
    void forgot();
    void clear_file();
    void menu();
    void checkbalance();             
    void checkbalance(int amo);      
    void checkcoins();
    void withdrawal();
    void deposit();
    void buycoins();
    void sellcoins();
    void save();
    void load();

protected:
    map<string, int> coin_balances;
    int balance;
    int amo;
};

#endif