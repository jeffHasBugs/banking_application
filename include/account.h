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
    Account(std::string& name, char type, int balance): _name(name),
    _type(type), _balance(balance), _account_no(get_random()) { }
    void initialize();
    void modify();
    void deposit(double amount);
    void withdraw(double amount);
    int get_number() const { return _account_no; } // get account number
    int get_balance() const { return _balance; } // get account balance
    std::string get_type() const; // get account type
    std::string get_holder() const { return _name; } // get name of account holder
    
private:
    int _account_no;
    char _type;
    std::string _name;
    double _balance;
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
    std::getline(std::cin, _name);
    std::cout << "[C]urrent account" << "\n[S]avings account" << "\nEnter account type [C/S]:" << std::endl;
    std::cin >> _type;
    _type = toupper(_type);
    std::cout << "Enter initial balance (>=500 for saving and >=1000 for current):" << std::endl;
    std::cin >> _balance;
    _account_no = get_random();
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
            std::getline(std::cin, _name);
            break;
        case 't':
            std::cout << "New account type: " << std::endl;
            std::cin.ignore(256, '\n');
            std::cin >> _type;
            break;
        case 'b':
            std::cout << "New account balance: " << std::endl;
            std::cin.ignore(256, '\n');
            std::cin >> _balance;
            break;
        default:
            modify();
            break;
    }
}

void Account::deposit(double amount)
{
    _balance = _balance + amount;
}

void Account::withdraw(double amount)
{
    _balance = _balance - amount;
}

std::string Account::get_type() const
{
    if (_type == 'C')
        return "Current";
    else 
        return "Savings";
}