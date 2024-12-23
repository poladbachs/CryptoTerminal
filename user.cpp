#include "user.h"
#include <thread>
#include <chrono>

int balance = 0;
int bitcoin = 0;
int dogecoin = 0;
int educoin = 0;
int idcoin = 0;
int arbcoin = 0;
int bnbcoin = 0;
int adacoin = 0;
int amo = 0;
int total = 0;
int coinPrice = 0;
int price = 0;
int amoun = 0;
int quantity = 0;
char choi, choic;

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_execution() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}


void checking::loadings(){
    clear_screen();
    cout << "\n\n\n\t\t\t\t\t\tloading" << endl;
    unsigned char loading = 219;
    cout << "\t\t\t\t";
    for(int i = 0; i <= 40; i++){
        cout << loading;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void login_trading::home(){
    char input[10];
    cout << endl;
    cout << "							---Menu---" << "\n\n";
    cout << "\t ----Please enter your choice---- " << "\n\n";
    cout << "\t Press 1 for Registration " << endl;
    cout << "\t Press 2 for Login " << endl;
    cout << "\t Press 3 for Forgot Password " << endl;
    cout << "\t Press 4 for Delete Account " << endl;
    cout << "\t Press 5 for End Program " << endl << "\t ";
    cin >> input;
    int c = atoi(input);
    switch(c){
        case 1:
            registration();
            break;
        case 2:
            login();
            home(); 
            break;
        case 3:
            forgot();
            break;
        case 4:
            clear_file();
            break;
        case 5:
            clear_screen();
            cout << endl;
            cout << "						---Thanks for visiting our app---" << "\n\n";
            exit(0);
            break;
        default:
            clear_screen();
            cout << "\n\n";
            cout << "\t Invalid choice. Please try again " << "\n\n";
            home();
    }
}

void login_trading::registration(){
    clear_screen();
    cout << "\n";
    cout << "						 ---Registration page---" << "\n\n";
    cin.ignore();
    cout << "\t Spaces are not allowed " << "\n\n";
    cout << "\t Enter a username : \t ";
    getline(cin, username);
    cout << endl;
    if(username.find(' ') != string::npos){
        cout << "\t Spaces are not allowed " << endl;
        home();
    }
    string filename = "trad_" + username + ".txt";
    infile.open(filename.c_str());
    if(infile){
        string existingUsername;
        while(infile >> existingUsername){
            if(username == existingUsername){
                clear_screen();
                cout << "\n";
                cout << "						 ---Username already exists---" << "\n\n";
                infile.close();
                home();
            }
        }
        infile.close();
    }
    cout << "\t Enter a password : \t ";
    getline(cin, password);
    cout << endl;
    if(password.find(' ') != string::npos){
        cout << "\t Spaces are not allowed " << endl;
        home();
    }
    bool hasdigit = false;
    bool hasalpha = false;
    for(size_t i = 0; i < password.length(); i++){
        if(isdigit(password[i])){
            hasdigit = true;
        } else if(isalpha(password[i])){
            hasalpha = true;
        }
    }
    if (!hasdigit || !hasalpha){
        cout << "\t Password must contain both letters and numbers." << endl;
        home();
    }
    if(password.length() < 8){
        cout << "\t Password must be at least 8 characters long." << endl;
        home();
    }
    outfile.open(filename.c_str());
    if(!outfile) {
        clear_screen();
        cout << "\n\n";
        cout << "						 ---Error opening file---" << "\n\n";
    }
    outfile << username << endl << password << endl << balance << endl << bitcoin << endl
            << dogecoin << endl << educoin << endl << idcoin << endl << arbcoin << endl
            << bnbcoin << endl << adacoin << endl << amo << endl;
    outfile.close();
    checking obj;
    obj.loadings();
    clear_screen();
    cout << "\n\n";
    cout << "						 ---Registered Successfully---" << "\n\n";
    home();
}

void login_trading::login(){
    clear_screen();
    cout << "\n";
    cout << "						    ---Login Page---" << "\n\n";
    cin.ignore();
    cout << "\t Spaces are not allowed " << "\n\n";
    cout << "\t Enter your username : \t ";
    getline(cin, username);
    cout << endl;
    cout << "\t Enter your password : \t ";
    getline(cin, password);
    string f = "trad_" + username + ".txt";
    infile.open(f.c_str());
    if(!infile){
        clear_screen();
        cout << "\n\n";
        cout << "						---Error opening file---" << "\n\n";
        home();
    }
    bool login_success = false;
    while(infile >> susername >> spassword){
        if(username == susername && password == spassword){
            login_success = true;
            break;
        }
    }
    infile.close();
    if(login_success){
        checking obj;
        obj.loadings();
        load();
        menu();
    }
    else{
        clear_screen();
        cout << "\n\n";
        cout << "						---Invalid username or password---" << "\n\n";
        home();
    }
}

void login_trading::forgot(){
    clear_screen();
    cout << "\n";
    cout << " 							---Forgot Page---" << "\n\n";
    cin.ignore();
    cout << "\t Spaces are not allowed " << endl;
    cout << "\t Enter your username : \t ";
    getline(cin, username);
    string fi = "trad_" + username + ".txt";
    file.open(fi.c_str());
    if(!file) {
        clear_screen();
        cout << "\n\n";
        cout << "\t Error opening file." << "\n\n";
        home();
    }
    bool user_found = false;
    while(file >> susername >> spassword){
        if(username == susername){
            user_found = true;
            break;
        }
    }
    file.close();
    if(user_found){
        checking obj;
        obj.loadings();
        clear_screen();
        cout << "\n\n";
        cout << "\t Your password is : " << spassword << "\n\n";
    }
    else{
        clear_screen();
        cout << "\n\n";
        cout << "							---Username not found---" << "\n\n";
    }
    home();
}

void login_trading::clear_file(){
    clear_screen();
    cout << "\n";
    cout << " 							---Clear Account---" << "\n\n";
    char ch;
    cin.ignore();
    cout << "\t Spaces are not allowed " << endl;
    cout << "\t Enter your username : \t ";
    getline(cin, username);
    cout << endl;
    cout << "\t Do you want to delete your account? (y/n)" << endl << "\t ";
    cin >> ch;
    if(ch == 'y' || ch == 'Y'){
        string filename = "trad_" + username + ".txt";
        ifstream fileExists(filename.c_str());
        if(fileExists){
            fileExists.close();
            remove(filename.c_str());
            checking obj;
            obj.loadings();
            clear_screen();
            cout << "\n";
            cout << "						---Your account is deleted---" << "\n\n";
        } 
        else{
            clear_screen();
            cout << "\n";
            cout << "						---Account does not exist---" << "\n\n";
        }
    } 
    else if(ch == 'n'){
        clear_screen();
    }
    home();
}

void login_trading::save(){
    string xc = "trad_" + username + ".txt";
    ofstream outFile(xc.c_str());
    outFile << username << endl;
    outFile << password << endl;
    outFile << balance << endl;
    outFile << bitcoin << endl;
    outFile << dogecoin << endl;
    outFile << educoin << endl;
    outFile << idcoin << endl;
    outFile << arbcoin << endl;
    outFile << bnbcoin << endl;
    outFile << adacoin << endl;
    outFile << amo << endl;
    outFile.close();
    outfile.open("online.txt", ios::app);
    outfile << username << endl;
    outfile << password << endl;
    outfile << balance << endl;
    outfile << bitcoin << endl;
    outfile << dogecoin << endl;
    outfile << educoin << endl;
    outfile << idcoin << endl;
    outfile << arbcoin << endl;
    outfile << bnbcoin << endl;
    outfile << adacoin << endl;
    outfile << amo << endl;
    outfile.close();
}

void login_trading::load(){
    string zx = "trad_" + username + ".txt";
    ifstream inFile(zx.c_str());
    if(!inFile){
        cout << "Error opening file." << endl;
        menu();
    }
    inFile >> username;
    inFile >> password;
    inFile >> balance;
    inFile >> bitcoin;
    inFile >> dogecoin;
    inFile >> educoin;
    inFile >> idcoin;
    inFile >> arbcoin;
    inFile >> bnbcoin;
    inFile >> adacoin;
    inFile >> amo;
    inFile.close();
}

void login_trading::menu(){
    clear_screen();
    cout << "\n\n";
    char input[10];
    cout << "			---Trading Software Menu---" << endl;
    cout << "\t 1. Sell Coins " << endl;
    cout << "\t 2. Buy Coins " << endl;
    cout << "\t 3. Check Balance " << endl;
    cout << "\t 4. Check Coins " << endl;
    cout << "\t 5. Withdrawal Amount " << endl;
    cout << "\t 6. Deposit Amount " << endl;
    cout << "\t 7. Exit " << endl << "\t ";
    cout << "Enter your choice : ";
    cin >> input;
    int choice = atoi(input);
    switch(choice){
        case 1:
            sellcoins();
            break;
        case 2:
            buycoins();
            break;
        case 3:
            checkbalance();
            break;
        case 4:
            checkcoins();
            break;
        case 5:
            withdrawal();
            break;
        case 6:
            deposit();
            break;
        case 7:
            clear_screen();
            exit(0);	                				
            break;
        default:
            cout << "\t Enter a valid input" << endl << "\t ";
            pause_execution();
            menu();
            break;
    }
}

void login_trading::checkbalance(){
    clear_screen();
    cout << "\n\n";
    cout << "\t Your balance is : $" << balance << endl;
    checkbalance(amo);
    cout << endl << "\t ";
    pause_execution();
    save();
    menu();
}

void login_trading::checkbalance(int amo){
    cout << endl;
    cout << "\t Your total withdrawal amount is : $" << amo << endl;
}

void login_trading::checkcoins(){
    clear_screen();
    cout << "\n\n";
    cout << "\t Your bitcoin: " << bitcoin << endl;
    cout << "\t Your dogecoin: " << dogecoin << endl;
    cout << "\t Your educoin: " << educoin << endl;
    cout << "\t Your idcoin: " << idcoin << endl;
    cout << "\t Your arbcoin: " << arbcoin << endl;
    cout << "\t Your bnbcoin: " << bnbcoin << endl;
    cout << "\t Your adacoin: " << adacoin << endl << "\t ";
    pause_execution();
    save();	
    menu();
}

void login_trading::withdrawal(){
    int amoun;
    clear_screen();
    cout << "\n\n";
    cout << "\t Enter the amount of withdrawal : $";
    cin >> amoun;
    if(amoun > balance){
        cout << "\t Insufficient Balance " << endl << "\t ";
        pause_execution();
        menu();
    }
    if(amoun > 10000000){
        cout << "Enter a lesser amount " << endl;
        menu();
    }
    else{
        balance -= amoun;
        amo += amoun;
        checking obj;
        obj.loadings();
        clear_screen();
        cout << "\n\n";
        cout << "\t Withdrawal successful " << endl;
        cout << "\t Your balance is : $" << balance << "\n\n" << "\t ";
        pause_execution();
        save();	
        menu();
    }
}

void login_trading::deposit(){
    int am;
    clear_screen();
    cout << "\n\n" << "\t ";
    cout << "Enter the amount to deposit in your account : $";
    cin >> am;
    if(am > 10000000){
        cout << "Enter a lesser amount " << endl;
        pause_execution();
        menu();
    }
    else{
        balance += am;
        checking obj;
        obj.loadings();
        clear_screen();
        cout << "\n\n";
        cout << "\t Deposit successful " << endl;
        cout << "\t Your balance is : $" << balance << "\n\n" << "\t ";
        pause_execution();
        save();	
        menu();
    }
}

void checking::showrandom(){
    cout << "\t Price of coin : $" << coinPrice << "\n\n";
    cout << "\t Enter the coins quantity : ";
    cin >> quantity;
    cout << "\n";
    total = coinPrice * quantity;
    cout << "\t Total Price : " << total << "\n\n";
}

void checking::showquantity(){
    cout << "\t Would you like to sell coins (y/n) " << "\n" << "\t ";
    cin >> choic;
    if(choic == 'y' || choic == 'Y'){
        balance += total;  
    }
}

void login_trading::sellcoins(){
    clear_screen();
    cout << "\n\n";
    checking obj;
    char input[10];
    cout << "			---Sell Coins---" << endl;
    cout << "\n\t Press 1 to sell bitcoin ";
    cout << "\n\t Press 2 to sell dogecoin ";
    cout << "\n\t Press 3 to sell educoin ";
    cout << "\n\t Press 4 to sell idcoin ";
    cout << "\n\t Press 5 to sell arbcoin ";
    cout << "\n\t Press 6 to sell bnbcoin ";
    cout << "\n\t Press 7 to sell adacoin " << endl << "\t";
    cin >> input;
    int zh = atoi(input);
    switch (zh){
        case 1:{
            coinPrice = rand() % 30000 + 20000;
            obj.showrandom();
            if (quantity > bitcoin){
                cout << "\t Insufficient coins" << endl;
                break;
            }
            else{ 
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    bitcoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " bitcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }    
            break;
        }
        case 2:{
            coinPrice = rand() % 20000 + 10000;
            obj.showrandom();
            if(quantity > dogecoin){
                cout << "\t Insufficient coins " << endl;
                break;
            }
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    dogecoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " dogecoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        case 3:{
            coinPrice = rand() % 100 + 50;
            obj.showrandom();
            if(quantity > educoin){
                cout << "\t Insufficient coins " << endl;
                break;
            }
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    educoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " educoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        case 4:{
            coinPrice = rand() % 1000 + 500;
            obj.showrandom();
            if(quantity > idcoin){
                cout << "\t Insufficient coins" << endl;
                break;
            }
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    idcoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " idcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        case 5:{
            coinPrice = rand() % 3000 + 2000;
            obj.showrandom();
            if(quantity > arbcoin){
                cout << "\t Insufficient coins" << endl;
                break;
            } 
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    arbcoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " arbcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        case 6:{
            coinPrice = rand() % 10000 + 20000;
            obj.showrandom();
            if(quantity > bnbcoin){
                cout << "\t Insufficient coins" << endl;
                break;
            } 
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    bnbcoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " bnbcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        case 7:{
            coinPrice = rand() % 25 + 10;
            obj.showrandom();
            if(quantity > adacoin){
                cout << "\t Insufficient coins" << endl;
                break;
            }
            else{
                obj.showquantity();
                if(choic == 'y' || choic == 'Y'){
                    adacoin -= quantity;
                    cout << "\t You sold successfully " << quantity << " adacoin(s)" << "\n\n";
                    cout << "\t Your balance is : $ " << balance << endl;
                }
            }
            break;
        }
        default:
            cout << "\t Enter a valid input " << endl;
            break;
    }
    cout << endl << "\t ";
    pause_execution();
    menu();
}

void checking::showquant(){
    cout << "\t Would you like to buy coins (y/n) " << "\n" << "\t ";
    cin >> choi;
    if(choi == 'y' || choi == 'Y'){
        balance -= total;
    }
}

void login_trading::buycoins(){
    clear_screen();
    cout << "\n\n";
    checking obj;
    char input[10];
    cout << "\t Press 1 to buy bitcoin " << endl;
    cout << "\t Press 2 to buy dogecoin " << endl;
    cout << "\t Press 3 to buy educoin " << endl;
    cout << "\t Press 4 to buy idcoin " << endl;
    cout << "\t Press 5 to buy arbcoin " << endl;
    cout << "\t Press 6 to buy bnbcoin " << endl;
    cout << "\t Press 7 to buy adacoin " << endl << "\t ";
    cin >> input;
    int ch = atoi(input);
    switch(ch){
        case 1:{
            coinPrice = rand() % 30000 + 20000;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance" << endl;
                break;
            } 
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    bitcoin += quantity;
                    cout << "\t You bought successfully " << quantity << " bitcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 2:{
            coinPrice = rand() % 20000 + 10000;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance " << "\n";
                break;
            } 
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    dogecoin += quantity;
                    cout << "\t You bought successfully " << quantity << " dogecoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 3:{
            coinPrice = rand() % 100 + 50;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance " << endl;
                break;
            } 
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    educoin += quantity;
                    cout << "\t You bought successfully " << quantity << " educoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 4:{
            coinPrice = rand() % 1000 + 500;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance" << endl;
                break;
            }
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    idcoin += quantity;
                    cout << "\t You bought successfully " << quantity << " idcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 5:{
            coinPrice = rand() % 3000 + 2000;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance" << endl;
                break;
            } 
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    arbcoin += quantity;
                    cout << "\t You bought successfully " << quantity << " arbcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 6:{
            coinPrice = rand() % 10000 + 20000;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance" << endl;
                break;
            } 
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    bnbcoin += quantity;
                    cout << "\t You bought successfully " << quantity << " bnbcoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        case 7:{
            coinPrice = rand() % 25 + 10;
            obj.showrandom();
            if(total > balance){
                cout << "\t Insufficient balance" << endl;
                break;
            }
            else{
                obj.showquant();
                if(choi == 'y' || choi == 'Y'){
                    adacoin += quantity;
                    cout << "\t You bought successfully " << quantity << " adacoin(s)" << "\n\n";
                    cout << "\t Your balance is : $" << balance << endl;
                }
            }
            break;
        }
        default:
            cout << "\t Enter a valid input " << endl;
            break;
    }
    cout << endl << "\t ";
    pause_execution();
    menu();
}