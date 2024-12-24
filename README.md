![ezgif-4-2bb16ef510](https://github.com/user-attachments/assets/94dba493-d932-48b4-a838-e7d124c1e4e5)
# CryptoSoftware 
Crypto Trading Platform

A C++ console-based crypto trading application that uses the CoinMarketCap API to fetch live cryptocurrency prices. Users can register, log in, buy, sell, and check their coin balances securely.

---

![cryptosoft](https://github.com/user-attachments/assets/14c84604-15b6-4ddf-b611-3ae99ac60e8f)

## Features

- **User Management**:
  - Registration with username and password.
  - Login and account recovery options.
  - Secure storage for user data.

- **Crypto Trading**:
  - Fetches real-time prices from CoinMarketCap API.
  - Supports buying and selling full coins and fractional amounts.
  - Maintains user balances and transaction history.

- **Menu Options**:
  - Deposit and withdraw funds.
  - View current balance and owned cryptocurrencies.
 
  

- **Secure API Key Management**:
  - Reads API key from `api_key.txt` (ignored in `.gitignore`).

## 1. Add API Key

Create a file named `api_key.txt` in the root directory.  
Add your CoinMarketCap API key in the txt file.

## 2. Install Dependencies
Ensure libcurl is installed on your system.

## 3. Build and Run the Application
`g++ main.cpp user.cpp -o main -lcurl -std=c++11`

`./main`

