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

// Include libcurl headers
#include <curl/curl.h>

// Include nlohmann/json
#include "nlohmann/json.hpp" // Make sure this is in your project directory or adjust the path accordingly

using json = nlohmann::json;
using namespace std;

// Helper functions
void clear_screen();
void pause_execution();

// Function to fetch crypto price
double fetch_crypto_price(const string& symbol, const string& api_key);

// Function to update all crypto prices
map<string, double> update_crypto_prices(const vector<string>& symbols, const string& api_key);

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
};

class checking : public login_trading {
public:
    void loadings();
    void showrandom();
    void showquantity(); // Changed to void
    void showquant();    // Changed to void
};

#endif