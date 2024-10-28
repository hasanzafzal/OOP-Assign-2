#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolderName;
    double balance;
    static int totalAccounts;
public:
    BankAccount(int accNum, const string& accHolderName, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = accHolderName;
        balance = initialBalance;
        totalAccounts++;
    }
    ~BankAccount() {
        totalAccounts--;
        cout << "Object destroyed for account number: " << accountNumber << endl;
    }
    friend void displayAccountDetails(const BankAccount& account);

    BankAccount operator+(const BankAccount& other) {
        return BankAccount(accountNumber + other.accountNumber,
            accountHolderName,
            balance + other.balance);
    }
    static void displayTotalAccounts() {
        cout << "Total Bank Accounts: " << totalAccounts << endl;
    }
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << ", New Balance: " << balance << endl;
        }
        else {
            cout << "Invalid deposit amount!" << endl;
        }
    }
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << ", New Balance: " << balance << endl;
        }
        else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }
    void transferTo(BankAccount& other, double amount) {
        if (amount > 0 && amount <= balance) {
            withdraw(amount);
            other.deposit(amount);
            cout << "Transfer of " << amount << " successful!" << endl;
        }
        else {
            cout << "Transfer failed: Invalid amount!" << endl;
        }
    }
    void checkBalanceComparison(BankAccount& other) {
        if (balance == other.balance) {
            cout << "Both accounts have the same balance." << endl;
        }
        else {
            cout << "Accounts have different balances." << endl;
        }
    }
    void displayDetails() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};
int BankAccount::totalAccounts = 0;

void displayAccountDetails(const BankAccount& account) {
    account.displayDetails();
}

int main() {
    int accNum1, accNum2;
    string accHolderName1, accHolderName2;
    double initialBalance1, initialBalance2;
    char transferChoice;
    double transferAmount;
    cout << "Enter details for Account 1:" << endl;
    cout << "Account Number: ";
    cin >> accNum1;
    cout << "Account Holder Name: ";
    cin.ignore();
    getline(cin, accHolderName1);
    cout << "Initial Balance: ";
    cin >> initialBalance1;
    cout << "Enter details for Account 2:" << endl;
    cout << "Account Number: ";
    cin >> accNum2;
    cout << "Account Holder Name: ";
    cin.ignore();
    getline(cin, accHolderName2);
    cout << "Initial Balance: ";
    cin >> initialBalance2;
    BankAccount* acc1 = new BankAccount(accNum1, accHolderName1, initialBalance1);
    BankAccount* acc2 = new BankAccount(accNum2, accHolderName2, initialBalance2);
    BankAccount::displayTotalAccounts();
    displayAccountDetails(*acc1);
    displayAccountDetails(*acc2);
    cout << "Do you want to transfer money from Account 1 to Account 2? (y/n): ";
    cin >> transferChoice;
    if (transferChoice == 'y' || transferChoice == 'Y') {
        cout << "Enter amount to transfer: ";
        cin >> transferAmount;
        acc1->transferTo(*acc2, transferAmount);
    }
    acc1->checkBalanceComparison(*acc2);
    BankAccount::displayTotalAccounts();
    delete acc1;
    delete acc2;

    return 0;
}