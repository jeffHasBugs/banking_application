#include <iostream>
#include <vector>
#include "include/account.h"

// *****
// Function declarations
// *****
void wait(); // wait for user after output
void create_account(std::vector<Account>&);
Account &prompt_account(std::vector<Account>&);
int get_choice(std::string&, std::vector<std::string>&);

int main()
{
    std::vector<Account> accounts;
    std::string prompt = "****MENU****";
    std::vector<std::string> choices = {"CREATE ACCOUNT", "MODIFY ACCOUNT", "SHOW ACCOUNT", "DEPOSIT", "WITHDRAW", "EXIT"};
    int choice = 0;
    do {
        if (!prompt.empty() ) {
            std::cout << prompt << std::endl;
        }
        int i = 1;
        for (auto ch : choices) {
            std::cout << i << " " << ch << std::endl;
            ++i;
        }
        std::cin >> choice;
        if (choice < 6) {
            if (choice == 1) { // create account
                create_account(accounts);
                wait(); //wait for user
                continue;
            }
            else { // subsequent actions require a reference to an account
                Account &account = prompt_account(accounts);
                if (choice == 2) // modify account
                    account.modify();
                else if (choice == 3) // show account
                    print(std::cout, account);
                else if (choice == 4) { // deposit
                    double amount = 0;
                    std::cout << "Amount to deposit:" << std::endl;
                    std::cin >> amount;
                    account.deposit(amount);
                }
                else if (choice == 5) { // withdraw
                    double amount = 0;
                    std::cout << "Amount to withdraw:" << std::endl;
                    std::cin >> amount;
                    account.withdraw(amount);
                }
                wait(); // wait for user
            }
        }
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
    acc.initialize();
    accounts.push_back(acc);
    std::cout << "Account number: " << acc.get_number() << std::endl;
}

Account &prompt_account(std::vector<Account> &accounts)
{
    int account_num;
    std::cout << "Account number:" << std::endl;
    std::cin >> account_num;
    /*
    search for an account in accounts that has a matching account number
    for account in accounts:
        if account.number matches account_number
            return account
    */
    for (auto &acc : accounts) {
        if (account_num == acc.get_number())
            return acc;
    }
    std::cerr << "No account with matching number found" << std::endl;
    throw std::invalid_argument("Invalid account number");
}