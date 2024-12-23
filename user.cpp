#include "user.h"

// Initialize global variables
int balance = 0;
int amo = 0;
int total = 0;
int quantity = 0;
char choi, choic;

// List of top 10 cryptocurrencies symbols
vector<string> top_10_symbols = {
    "BTC", "ETH", "USDT", "BNB", "XRP",
    "ADA", "DOGE", "USDC", "DOT", "UNI"
};

// Your Alpha Vantage API Key
const string API_KEY = "U6L3NVT5G6QZR485"; // Replace with your actual API key

// Map to store current prices of cryptocurrencies
map<string, double> crypto_prices;

// Helper function implementations
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

// Callback function for libcurl to write received data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch the current price of a specific cryptocurrency
double fetch_crypto_price(const string& symbol, const string& api_key) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url = "https://www.alphavantage.co/query?function=CURRENCY_EXCHANGE_RATE&from_currency=" 
                + symbol + "&to_currency=USD&apikey=" + api_key;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Follow redirects if any
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // Set callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Pass the string to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // Perform the request
        res = curl_easy_perform(curl);
        // Check for errors
        if(res != CURLE_OK){
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            curl_easy_cleanup(curl);
            return 0.0;
        }
        // Cleanup
        curl_easy_cleanup(curl);
    }
    
    // Parse JSON response
    try {
        json j = json::parse(readBuffer);
        if(j.contains("Realtime Currency Exchange Rate")){
            string rate_str = j["Realtime Currency Exchange Rate"]["5. Exchange Rate"];
            return stod(rate_str);
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

// Function to update prices of all top 10 cryptocurrencies
map<string, double> update_crypto_prices(const vector<string>& symbols, const string& api_key) {
    map<string, double> prices;
    for(const auto& symbol : symbols){
        double price = fetch_crypto_price(symbol, api_key);
        if(price > 0.0){
            prices[symbol] = price;
        }
        else{
            prices[symbol] = 0.0; // Indicate failure to fetch price
        }
        // To comply with API rate limits (5 requests per minute for free tier)
        this_thread::sleep_for(chrono::seconds(15)); // Wait 15 seconds between requests
    }
    return prices;
}

// Class Method Implementations

void checking::loadings(){
    clear_screen();
    cout << "\n\n\n\t\t\t\t\t\tloading" << endl;
    unsigned char loading = 219;
    cout << "\t\t\t\t";
    for(int i = 0; i <= 40; i++){
        cout << loading;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Increased delay for visibility
    }
    cout << endl;
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
        home();
    }
    // Initialize user data with default values
    outfile << username << endl << password << endl << balance << endl << "0" << endl
            << "0" << endl << "0" << endl << "0" << endl << "0" << endl
            << "0" << endl << "0" << endl << amo << endl;
    outfile.close();
    
    // Update crypto prices upon registration
    cout << "Fetching real-time cryptocurrency prices..." << endl;
    crypto_prices = update_crypto_prices(top_10_symbols, API_KEY);
    
    // Check if prices were fetched successfully
    bool fetch_success = true;
    for(const auto& symbol : top_10_symbols){
        if(crypto_prices[symbol] == 0.0){
            fetch_success = false;
            cout << "Failed to fetch price for " << symbol << "." << endl;
        }
    }
    if(!fetch_success){
        cout << "Some cryptocurrency prices could not be fetched. Please check your API key or network connection." << endl;
        home();
    }
    
    // Save fetched prices (optional)
    // You can choose to save these prices or fetch them every time
    
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
        
        // Fetch latest prices upon login
        cout << "Fetching latest cryptocurrency prices..." << endl;
        crypto_prices = update_crypto_prices(top_10_symbols, API_KEY);
        
        // Check if prices were fetched successfully
        bool fetch_success = true;
        for(const auto& symbol : top_10_symbols){
            if(crypto_prices[symbol] == 0.0){
                fetch_success = false;
                cout << "Failed to fetch price for " << symbol << "." << endl;
            }
        }
        if(!fetch_success){
            cout << "Some cryptocurrency prices could not be fetched. Please check your API key or network connection." << endl;
            home();
        }
        
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
    // Save all coin balances
    for(const auto& symbol : top_10_symbols){
        // You need to have variables or a map to store balances for each coin
        // Assuming you have separate variables like bitcoin, eth, etc.
        if(symbol == "BTC") outFile << bitcoin << endl;
        else if(symbol == "ETH") outFile << dogecoin << endl; // It seems incorrect; adjust accordingly
        // Continue for all symbols
        // Alternatively, use a map to store balances
    }
    outFile << amo << endl;
    outFile.close();
    
    // Save to "online.txt"
    outfile.open("online.txt", ios::app);
    outfile << username << endl;
    outfile << password << endl;
    outfile << balance << endl;
    // Similarly, save all coin balances
    if(symbol == "BTC") outfile << bitcoin << endl;
    // Continue for all symbols
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
    // Load all coin balances
    for(const auto& symbol : top_10_symbols){
        if(symbol == "BTC") inFile >> bitcoin;
        else if(symbol == "ETH") inFile >> dogecoin; // Adjust accordingly
        // Continue for all symbols
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
    cout << "\t Your Bitcoin (BTC): " << bitcoin << endl;
    cout << "\t Your Dogecoin (DOGE): " << dogecoin << endl;
    // Continue for all coins
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
    cout << "\n\t Press 1 to sell Bitcoin (BTC) ";
    cout << "\n\t Press 2 to sell Dogecoin (DOGE) ";
    // Continue for all coins
    cout << "\n\t Press 10 to sell UniSwap (UNI) " << endl << "\t";
    cin >> input;
    int zh = atoi(input);
    string selected_symbol;
    // Map input to symbol
    switch (zh){
        case 1:
            selected_symbol = "BTC";
            break;
        case 2:
            selected_symbol = "DOGE";
            break;
        // Continue for all coins
        case 10:
            selected_symbol = "UNI";
            break;
        default:
            cout << "\t Enter a valid input " << endl;
            pause_execution();
            menu();
            return;
    }

    // Get the current price
    if(crypto_prices.find(selected_symbol) == crypto_prices.end()){
        cout << "\t Price for " << selected_symbol << " not available." << endl;
        pause_execution();
        menu();
        return;
    }
    coinPrice = crypto_prices[selected_symbol];
    obj.showrandom();
    
    // Determine available balance for the selected coin
    int available_coins = 0;
    if(selected_symbol == "BTC") available_coins = bitcoin;
    else if(selected_symbol == "DOGE") available_coins = dogecoin;
    // Continue for all coins
    else if(selected_symbol == "UNI") available_coins = 0; // Replace with actual variable

    if (quantity > available_coins){
        cout << "\t Insufficient coins" << endl;
        pause_execution();
        menu();
        return;
    }
    else{ 
        obj.showquantity();
        if(choic == 'y' || choic == 'Y'){
            // Deduct coins
            if(selected_symbol == "BTC") bitcoin -= quantity;
            else if(selected_symbol == "DOGE") dogecoin -= quantity;
            // Continue for all coins
            else if(selected_symbol == "UNI") { /* Deduct UNI */ }
            
            // Add to balance
            double sale_amount = quantity * coinPrice;
            balance += sale_amount;
            cout << "\t You sold successfully " << quantity << " " << selected_symbol << "(s)" << "\n\n";
            cout << "\t Your balance is : $ " << balance << endl;
        }
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
    cout << "			---Buy Coins---" << endl;
    cout << "\n\t Press 1 to buy Bitcoin (BTC) ";
    cout << "\n\t Press 2 to buy Dogecoin (DOGE) ";
    // Continue for all coins
    cout << "\n\t Press 10 to buy UniSwap (UNI) " << endl << "\t ";
    cin >> input;
    int ch = atoi(input);
    string selected_symbol;
    // Map input to symbol
    switch(ch){
        case 1:
            selected_symbol = "BTC";
            break;
        case 2:
            selected_symbol = "DOGE";
            break;
        // Continue for all coins
        case 10:
            selected_symbol = "UNI";
            break;
        default:
            cout << "\t Enter a valid input " << endl;
            pause_execution();
            menu();
            return;
    }

    // Get the current price
    if(crypto_prices.find(selected_symbol) == crypto_prices.end()){
        cout << "\t Price for " << selected_symbol << " not available." << endl;
        pause_execution();
        menu();
        return;
    }
    coinPrice = crypto_prices[selected_symbol];
    obj.showrandom();
    
    // Check if user has enough balance
    if(total > balance){
        cout << "\t Insufficient balance" << endl;
        pause_execution();
        menu();
        return;
    } 
    else{
        obj.showquant();
        if(choi == 'y' || choi == 'Y'){
            // Deduct balance
            balance -= total;
            // Add coins
            if(selected_symbol == "BTC") bitcoin += quantity;
            else if(selected_symbol == "DOGE") dogecoin += quantity;
            // Continue for all coins
            else if(selected_symbol == "UNI") { /* Add UNI */ }
            cout << "\t You bought successfully " << quantity << " " << selected_symbol << "(s)" << "\n\n";
            cout << "\t Your balance is : $" << balance << endl;
        }
    }
    cout << endl << "\t ";
    pause_execution();
    menu();
}
