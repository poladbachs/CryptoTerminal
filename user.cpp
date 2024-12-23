#include "user.h"

vector<string> top_10_symbols = {
    "BTC", "ETH", "USDT", "SOL", "XRP",
    "ADA", "AVAX", "LINK", "SUI", "DOT"
};

map<string, double> crypto_prices;

login_trading::login_trading() {
    balance = 0;
    amo = 0;
    for(const auto& sym : top_10_symbols){
        coin_balances[sym] = 0;
    }
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_execution() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string read_api_key(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open API key file at " << filepath << endl;
        exit(1);
    }
    string api_key;
    getline(file, api_key);
    file.close();
    return api_key;
}

double fetch_crypto_price(const string& symbol) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string api_key = read_api_key("api_key.txt");
    string url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?symbol=" + symbol;
    
    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        string header = "X-CMC_PRO_API_KEY: " + api_key;
        headers = curl_slist_append(headers, header.c_str());
        headers = curl_slist_append(headers, "Accept: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return 0.0;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    
    try {
        json j = json::parse(readBuffer);
        if(j.contains("data") && j["data"].contains(symbol) && j["data"][symbol].contains("quote") &&
           j["data"][symbol]["quote"].contains("USD") && j["data"][symbol]["quote"]["USD"].contains("price")){
            double price = j["data"][symbol]["quote"]["USD"]["price"];
            return price;
        }
        else{
            cerr << "Error: " << j.dump() << endl;
            return 0.0;
        }
    }
    catch(json::parse_error& e){
        cerr << "JSON Parse Error: " << e.what() << endl;
        return 0.0;
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
        infile >> existingUsername;
        if(username == existingUsername){
            clear_screen();
            cout << "\n";
            cout << "						 ---Username already exists---" << "\n\n";
            infile.close();
            home();
            return;
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
        home();
    }
    outfile << username << endl << password << endl << balance << endl;
    for(const auto& sym : top_10_symbols){
        outfile << "0" << endl;
    }
    outfile << amo << endl;
    outfile.close();
    
    for(const auto& sym : top_10_symbols){
        coin_balances[sym] = 0;
    }
    
    cout << "Registration successful." << endl;
    pause_execution();
    home();
}

void login_trading::login(){
    clear_screen();
    cout << "\n";
    cout << "						    ---Login Page---" << "\n\n";
    cin.ignore();
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
        return;
    }
    bool login_success = false;
    infile >> susername >> spassword;
    if(username == susername && password == spassword){
        login_success = true;
    }
    infile.close();
    if(login_success){
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
    cout << "\t Enter your username : \t ";
    getline(cin, username);
    string fi = "trad_" + username + ".txt";
    file.open(fi.c_str());
    if(!file) {
        clear_screen();
        cout << "\n\n";
        cout << "\t Error opening file." << "\n\n";
        home();
        return;
    }
    bool user_found = false;
    file >> susername >> spassword;
    if(username == susername){
        user_found = true;
    }
    file.close();
    if(user_found){
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
            if(remove(filename.c_str()) == 0){
                clear_screen();
                cout << "\n";
                cout << "						---Your account is deleted---" << "\n\n";
            }
            else{
                clear_screen();
                cout << "\n";
                cout << "						---Failed to delete account---" << "\n\n";
            }
        } 
        else{
            clear_screen();
            cout << "\n";
            cout << "						---Account does not exist---" << "\n\n";
        }
    } 
    else if(ch == 'n' || ch == 'N'){
        clear_screen();
    }
    home();
}

void login_trading::save(){
    string xc = "trad_" + username + ".txt";
    ofstream outFile(xc.c_str());
    if(!outFile){
        cerr << "Error opening file for saving." << endl;
        return;
    }
    outFile << username << endl;
    outFile << password << endl;
    outFile << balance << endl;
    for(const auto& sym : top_10_symbols){
        outFile << coin_balances[sym] << endl;
    }
    outFile << amo << endl;
    outFile.close();
}

void login_trading::load(){
    string zx = "trad_" + username + ".txt";
    ifstream inFile(zx.c_str());
    if(!inFile){
        cout << "Error opening file." << endl;
        menu();
        return;
    }
    inFile >> username;
    inFile >> password;
    inFile >> balance;
    for(const auto& sym : top_10_symbols){
        double coin_balance;
        inFile >> coin_balance;
        coin_balances[sym] = coin_balance;
    }
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
            cout << "Exiting program. Goodbye!" << endl;
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
    cout << "\t Your total withdrawal amount is : $" << amo << endl;
    cout << endl << "\t ";
    pause_execution();
    save();
    menu();
}

void login_trading::checkcoins(){
    clear_screen();
    cout << "\n\n";
    for(const auto& sym : top_10_symbols){
        cout << "\t Your " << sym << ": " << coin_balances[sym] << endl;
    }
    cout << "\t Your total withdrawals: $" << amo << endl << "\t ";
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
        return;
    }
    if(amoun > 10000000){
        cout << "Enter a lesser amount " << endl;
        pause_execution();
        menu();
        return;
    }
    balance -= amoun;
    amo += amoun;
    clear_screen();
    cout << "\n\n";
    cout << "\t Withdrawal successful " << endl;
    cout << "\t Your balance is : $" << balance << "\n\n" << "\t ";
    pause_execution();
    save();	
    menu();
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
        return;
    }
    balance += am;
    clear_screen();
    cout << "\n\n";
    cout << "\t Deposit successful " << endl;
    cout << "\t Your balance is : $" << balance << "\n\n" << "\t ";
    pause_execution();
    save();	
    menu();
}

void login_trading::buycoins(){
    clear_screen();
    cout << "\n\n";
    char input[10];
    cout << "			---Buy Coins---" << endl;
    for(int i = 0; i < top_10_symbols.size(); ++i){
        cout << "\n\t Press " << (i+1) << " to buy " << top_10_symbols[i];
    }
    cout << "\n\t Press " << (top_10_symbols.size()+1) << " to cancel" << endl << "\t ";
    cin >> input;
    int ch = atoi(input);
    if(ch < 1 || ch > top_10_symbols.size()+1){
        cout << "\t Enter a valid input " << endl;
        pause_execution();
        menu();
        return;
    }
    if(ch == top_10_symbols.size()+1){
        // Cancel operation
        cout << "\t Buy operation cancelled." << endl;
        pause_execution();
        menu();
        return;
    }
    string selected_symbol = top_10_symbols[ch-1];
    
    double latest_price = fetch_crypto_price(selected_symbol);
    if(latest_price == 0.0){
        cout << "\t Failed to fetch price for " << selected_symbol << "." << endl;
        pause_execution();
        menu();
        return;
    }
    double coinPrice = latest_price;
    cout << "\t Price of " << selected_symbol << " : $" << coinPrice << "\n\n";
    
    double quantity;
    cout << "\t Enter the quantity to buy : ";
    cin >> quantity;

    if(cin.fail() || quantity <= 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t Invalid quantity. Please enter a positive number." << endl;
        pause_execution();
        menu();
        return;
    }

    cout << "\n";
    double total = coinPrice * quantity;
    cout << "\t Total Price : $" << total << "\n\n";
    
    if(total > balance){
        cout << "\t Insufficient balance" << endl;
        pause_execution();
        menu();
        return;
    } 
    else{
        char choi;
        cout << "\t Would you like to buy coins (y/n) " << "\n" << "\t ";
        cin >> choi;
        if(choi == 'y' || choi == 'Y'){
            balance -= total;
            coin_balances[selected_symbol] += quantity;
            cout << "\t You bought successfully " << quantity << " " << selected_symbol << "(s)" << "\n\n";
            cout << "\t Your balance is : $" << balance << endl;
        }
    }
    cout << endl << "\t ";
    pause_execution();
    save();
    menu();
}

void login_trading::sellcoins(){
    clear_screen();
    cout << "\n\n";
    char input[10];
    cout << "			---Sell Coins---" << endl;
    for(int i = 0; i < top_10_symbols.size(); ++i){
        cout << "\n\t Press " << (i+1) << " to sell " << top_10_symbols[i];
    }
    cout << "\n\t Press " << (top_10_symbols.size()+1) << " to cancel" << endl << "\t";
    cin >> input;
    int zh = atoi(input);
    if(zh < 1 || zh > top_10_symbols.size()+1){
        cout << "\t Enter a valid input " << endl;
        pause_execution();
        menu();
        return;
    }
    if(zh == top_10_symbols.size()+1){
        cout << "\t Sell operation cancelled." << endl;
        pause_execution();
        menu();
        return;
    }
    string selected_symbol = top_10_symbols[zh-1];
    
    double latest_price = fetch_crypto_price(selected_symbol);
    if(latest_price == 0.0){
        cout << "\t Failed to fetch price for " << selected_symbol << "." << endl;
        pause_execution();
        menu();
        return;
    }
    double coinPrice = latest_price;
    cout << "\t Price of " << selected_symbol << " : $" << coinPrice << "\n\n";
    double quantity;
    cout << "\t Enter the quantity to sell : ";
    cin >> quantity;

    if(cin.fail() || quantity <= 0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t Invalid quantity. Please enter a positive number." << endl;
        pause_execution();
        menu();
        return;
    }

    cout << "\n";
    double total = coinPrice * quantity;
    cout << "\t Total Price : $" << total << "\n\n";
    
    double available_coins = coin_balances[selected_symbol];
    
    if (quantity > available_coins){
        cout << "\t Insufficient coins" << endl;
        pause_execution();
        menu();
        return;
    }
    else{ 
        char choic;
        cout << "\t Would you like to sell coins (y/n) " << "\n" << "\t ";
        cin >> choic;
        if(choic == 'y' || choic == 'Y'){
            coin_balances[selected_symbol] -= quantity;
            double sale_amount = total;
            balance += sale_amount;
            cout << "\t You sold successfully " << quantity << " " << selected_symbol << "(s)" << "\n\n";
            cout << "\t Your balance is : $" << balance << endl;
        }
    }    
    cout << endl << "\t ";
    pause_execution();
    save();
    menu();
}
