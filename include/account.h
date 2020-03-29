#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

// random number generator
int get_random()
{
    srand( (unsigned)time(NULL) );
    return rand();
}

// account class for managing accounts
class Account {
public:
    Account() = default;
    Account(std::string& name, char type, int balance): account_no_(get_random()),
    type_(type), name_(name), balance_(balance) { }
    void initialize();
    void modify();
    void deposit(double amount);
    void withdraw(double amount);
    int get_number() const { return account_no_; } // get account number
    int get_balance() const { return balance_; } // get account balance
    std::string get_type() const; // get account type
    std::string get_holder() const { return name_; } // get name of account holder
    
private:
    int account_no_;
    char type_;
    std::string name_;
    double balance_;
};

// nonmember functions
std::ostream &print(std::ostream &os, const Account &acc)
{
    std::cout << "Account number: " << acc.get_number() << std::endl
              << "Account holder: " << acc.get_holder() << std::endl
              << "Account type: " << acc.get_type() << std::endl
              << "Account balance: " << acc.get_balance() << std::endl;
    return os;
}

// member functions
void Account::initialize()
{
    std::cout << "Enter name of account holder:" << std::endl;
    std::cin.ignore(256, '\n');
    std::getline(std::cin, name_);
    std::cout << "[C]urrent account" << "\n[S]avings account" << "\nEnter account type [C/S]:" << std::endl;
    std::cin >> type_;
    type_ = toupper(type_);
    std::cout << "Enter initial balance (>=500 for saving and >=1000 for current):" << std::endl;
    std::cin >> balance_;
    account_no_ = get_random();
}

void Account::modify()
{
    char attribute = 0;
    std::cout << "Account holder [n]ame" << std::endl
              << "Account [t]ype" << std::endl
              << "Account [b]alance" << std::endl
              << "Attribute to modify?" << std::endl;
    std::cin.clear();
    std::cin >> attribute;
    attribute = tolower(attribute);
    switch (attribute) {
        case 'n':
            std::cout << "New account holder name: " << std::endl;
            std::cin.ignore(256, '\n');
            std::getline(std::cin, name_);
            break;
        case 't':
            std::cout << "New account type: " << std::endl;
            std::cin.ignore(256, '\n');
            std::cin >> type_;
            break;
        case 'b':
            std::cout << "New account balance: " << std::endl;
            std::cin.ignore(256, '\n');
            std::cin >> balance_;
            break;
        default:
            modify();
            break;
    }
}

void Account::deposit(double amount)
{
    balance_ = balance_ + amount;
}

void Account::withdraw(double amount)
{
    balance_ = balance_ - amount;
}

std::string Account::get_type() const
{
    if (type_ == 'C')
        return "Current";
    else 
        return "Savings";
}