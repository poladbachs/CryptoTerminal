![ezgif-3-3f2ba8cd07](https://github.com/user-attachments/assets/dc483d06-572e-4fda-a2e9-0547c98e57cc)
<img width="400" alt="cmcHomepageLogo" src="https://github.com/user-attachments/assets/2917fb6f-7c2f-447e-908e-0f6abc177032" />

# CryptoSoftware 
Crypto Trading Platform

A C++ console-based crypto trading application that uses the CoinMarketCap API to fetch live top 10 cryptocurrency prices such as BTC, ETH, Solana and Avalanche. Users can register, log in, buy, sell, and check their coin balances securely.

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

