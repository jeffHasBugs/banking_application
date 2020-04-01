#include <iostream>
#include <vector>
#include "../include/account.h"

// *****
// Function declarations
// *****
void wait(); // wait for user after output
void create_account(std::vector<Account>&);
void deposit(Account&);
void withdraw(Account&);
Account &prompt_account(std::vector<Account>&);
int get_choice(std::string&, std::vector<std::string>&);

int main()
{
    std::vector<Account> accounts;
    std::string prompt = "****MENU****";
    std::vector<std::string> choices = {"CREATE ACCOUNT", "MODIFY ACCOUNT", "SHOW ACCOUNT", "DEPOSIT", "WITHDRAW", "EXIT"};
    int choice = 0;
    do {
        // list choices and ask for choice
        if (!prompt.empty() ) {
            std::cout << prompt << std::endl;
        }
        int i = 1;
        for (auto ch : choices) {
            std::cout << i << " " << ch << std::endl;
            ++i;
        }
        std::cin >> choice;
        // process choice
        if (choice == 1) // create account
            create_account(accounts);
        else if (choice == 2) // modify account
            prompt_account(accounts).modify();
        else if (choice == 3) // show account
            print(std::cout, prompt_account(accounts) );
        else if (choice == 4) // deposit
            deposit(prompt_account(accounts) );
        else if (choice == 5) // withdraw
            withdraw(prompt_account(accounts) );
        wait(); // wait for user
    } while (choice < 6);
    return 0;
}

// *****
// Function definitions
// *****
void wait()
{
    std::cout << "Enter to continue ..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void create_account(std::vector<Account> &accounts)
{
    Account acc;
    int account_num = acc.initialize();
    std::cout << "Account number: " << account_num << std::endl;
    accounts.push_back(acc);
}

void deposit(Account &account)
{
    double amount = 0;
    std::cout << "Amount to deposit:" << std::endl;
    std::cin >> amount;
    account.deposit(amount);
}

void withdraw(Account &account)
{
    double amount = 0;
    std::cout << "Amount to withdraw:" << std::endl;
    std::cin >> amount;
    account.withdraw(amount);
}

Account &prompt_account(std::vector<Account> &accounts)
{
    int account_num;
    std::cout << "Account number:" << std::endl;
    std::cin >> account_num;
    try {
        Account &acc = search(account_num, accounts);
        return acc;
    }
    catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
}