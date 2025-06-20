#include <iostream>
#include<fstream>
#include <vector>
#include <string>
using namespace std;

class Account {
protected:
    int accountnumber;
    string name;

public:
    int balance;
    string accounttype;

    virtual void createAccount() {
        cout << "\n                            === Create New Account ===\n";
        cout << "                            Enter user/Employee name: ";
        cin.ignore();
        getline(cin, name);
        cout << "                            Enter account number: ";
        cin >> accountnumber;
       
    }

    virtual void showAccount() {
        cout << "\n                            --- Account Details ---\n";
        cout << "                            Account Number: " << accountnumber << endl;
        cout << "                            Username      : " << name << endl;
    }

    virtual string getName() const {
        return name;
    }

    virtual ~Account() {}
};

class userAccount : public Account {
private:
    int password;
    string location;
    long long CNIC;

public:
    vector<int> depositHistory;
    vector<int> withdrawHistory;
    string getLocation() const {
        return location;
    }

    int getBalance() const {
        return balance;
    }

    int getPassword() const {
        return password;
    }

    long long getCNIC() const {
        return CNIC;
    }
    void createAccount() override {
        ofstream file("createuserAccounts.txt", ios::app);
        if (file.is_open()) {
            Account::createAccount(); 
            cout << "                            Enter initial balance: ";
            cin >> balance;
            cout << "                            Enter the password of your account: ";
            cin >> password;
            cout << "                            Enter your location: ";
            cin.ignore();
            getline(cin, location);
            cout << "                            Enter your CNIC: ";
            cin >> CNIC;
            file << "                            Enter the name       :" << name << endl;
            file << "                            Enter initial balance: " << balance << endl;
            file << "                            Enter the password of your account: " << password << endl;
            file << "                            Enter your location: " << location << endl;
            file << "                            Enter your CNIC: " << CNIC << endl;
            file << "                            -----------------------------" << endl;
            file.close();
        }
    }



    void showAccount() override {
        Account::showAccount();
        cout << "                            Balance       : PKR " << balance << endl;
        cout << "                            Location      : " << location << endl;
        cout << "                            CNIC          : " << CNIC << endl;
        ofstream file("showuserAccounts.txt", ios::app);
        if (file.is_open()) {
            file << "                            Balance       : PKR " << balance << endl;
            file << "                            Location      : " << location << endl;
            file << "                            CNIC          : " << CNIC << endl;
            file << "                            -----------------------------" << endl;
            file.close();
        }
    }
    void loan() {
        int loanAmount, date;
            cout << "                            Enter the loan amount: ";
            cin >> loanAmount;
            cout << "                            Enter the payback date (months): ";
            cin >> date;
        ofstream file("loan.txt", ios::app);
        if (file.is_open()) {
            file << "                            Enter the loan amount: " << loanAmount << endl;
            file << "                            Enter the payback date (months): " << endl;
            if (date >= 3 && loanAmount == 50000) {
                file << "                            Total Payback: " << date * 1000 << " PKR\n";
            }
            else if (date >= 3 && loanAmount >= 100000) {
                file << "                            Total Payback: " << date * 2500 << " PKR\n";
            }
        }
        file.close();
    }

    void depositMoney() {
        int depositAmount;
        cout << "                            Enter amount to deposit: ";
        cin >> depositAmount;
        balance += depositAmount;
        depositHistory.push_back(depositAmount);
        ofstream file("deposit.txt", ios::app);
        if (file.is_open()) {
            file << "Deposited: " << depositAmount
                << " | New Balance: " << balance << endl;
            file.close();
        }
    }

    void withdrawMoney() {
        int withdrawAmount;
        cout << "                            Enter amount to withdraw: ";
        cin >> withdrawAmount;

        if (withdrawAmount <= balance) {
            balance -= withdrawAmount;
            withdrawHistory.push_back(withdrawAmount);
            ofstream file("withdraw.txt", ios::app);
            if (file.is_open()) {
                file << "Withdraw: " << withdrawAmount
                    << " | New Balance: " << balance << endl;
                file.close();
            }
            }
        else {
            cout << "                            Insufficient balance!\n";
        }
    }

    void billpayment() {
        int n, billAmount;
        cout << "                            Enter 1 for Electric bill\n";
        cout << "                            Enter 2 for Gas bill\n";
        cout << "                            Enter 3 for School/University fee\n";
        cout << "                            Option: ";
        cin >> n;
        cout << "                            Enter bill amount: ";
        cin >> billAmount;

        ofstream file("billpayment.txt", ios::app);
        if (file.is_open()) {
            switch (n) {
            case 1:
                balance -= billAmount;
                file << "                            Electric bill paid. Remaining balance: " << balance << endl;
                break;
            case 2:
                balance -= billAmount;
                file << "                            Gas bill paid. Remaining balance: " << balance << endl;
                break;
            case 3:
                balance -= billAmount;
                file << "                            Education fee paid. Remaining balance: " << balance << endl;
                break;
            default:
                file << "                            Invalid bill option entered.\n";
                break;
            }
            file.close();
        }
    }

};

class employeeAccount : public Account {
private:
    int employeeid;
    string jobstatus;

public:
    int getEmployeeID() const {
        return employeeid;
    }

    void createAccount() override {
        Account::createAccount();
        cout << "                            Enter your Employee ID: ";
        cin >> employeeid;
        cout << "                            Enter your job status: ";
        cin.ignore();
        getline(cin, jobstatus);
        ofstream file("EmployeeAccounts.txt", ios::app);
        if (file.is_open()) {
        file << "                            Enter Employee name:    " << name << endl;
        file << "                            Enter Employee account number: " << accountnumber << endl;
        file << "                            Enter your Employee ID: " << employeeid << endl;
        file << "                            Enter your job status: " << jobstatus << endl;
        file << "                            -----------------------------" << endl;
        }
        file.close();
    }

    void showAccount() override {
        Account::showAccount();
        cout << "                            Employee ID   : " << employeeid << endl;
        cout << "                            Job Status    : " << jobstatus << endl;
        ofstream file("showEmployeeAccounts.txt", ios::app);
        if (file.is_open()) {
        file << "                            Employee ID   : " << employeeid << endl;
        file << "                            Job Status    : " << jobstatus << endl;
        file << "                            -----------------------------" << endl;
        }
        file.close();
    }

    void Customerdetails(vector<Account*>& accounts) {
        string searchName;
        int searchPassword;

        cin.ignore();
        cout << "                            Enter the username: ";
        getline(cin, searchName);
        cout << "                            Enter the password: ";
        cin >> searchPassword;

        for (Account* acc : accounts) {
            userAccount* user = dynamic_cast<userAccount*>(acc);
            if (user && user->getName() == searchName && user->getPassword() == searchPassword) {
                ofstream file("Customerdetails.txt", ios::app);
                if (file.is_open()) {
                    file << "                            Username      : " << user->getName() << endl;
                    file << "                            Password      : " << user->getPassword() << endl;
                    file << "                            Balance       : " << user->getBalance() << endl;
                    file << "                            Location      : " << user->getLocation() << endl;
                    file << "                            CNIC          : " << user->getCNIC() << endl;
                    file << "                            -----------------------------" << endl;
                    file.close();
                }

                return;
            }
        }
        cout << "                            No matching user found.\n";
    }

    void withdrawhistroy(vector<Account*>& accounts) {
        string searchName;
        int searchPassword;

        cin.ignore();
        cout << "                            Enter the username: ";
        getline(cin, searchName);
        cout << "                            Enter the password: ";
        cin >> searchPassword;

        for (Account* acc : accounts) {
            userAccount* user = dynamic_cast<userAccount*>(acc);
            if (user && user->getName() == searchName && user->getPassword() == searchPassword) {
                cout << "\n                            === Withdrawal History ===\n";
                ofstream file("withdrawhistroy.txt", ios::app);
                if (file.is_open()) {
                    for (int amount : user->withdrawHistory) {
                        cout << "                            Withdrawn: " << amount << " PKR\n";
                        file << "                            Withdrawn: " << amount << " PKR\n";
                    }
                    file << "                            -----------------------------\n";
                    file.close();
                }
                else {
                    cout << "                            Unable to open file.\n";
                }
                return;
            }
        }
        cout << "                            No matching user found.\n";
    }
    void Deposithistroy(vector<Account*>& accounts) {
        string searchName;
        int searchPassword;

        cin.ignore();
        cout << "                            Enter the username: ";
        getline(cin, searchName);
        cout << "                            Enter the password: ";
        cin >> searchPassword;

        for (Account* acc : accounts) {
            userAccount* user = dynamic_cast<userAccount*>(acc);
            if (user && user->getName() == searchName && user->getPassword() == searchPassword) {
                cout << "\n                            === Deposit History ===\n";
                ofstream file("Deposithistory.txt", ios::app);
                if (file.is_open()) {
                    for (int amount : user->depositHistory) {
                        cout << "                            Deposited: " << amount << " PKR\n";
                        file << "                            Deposited: " << amount << " PKR\n";
                    }
                    file << "                            -----------------------------\n";
                    file.close();
                }
                else {
                    cout << "                            Unable to open file.\n";
                }
                return;
            }
        }
        cout << "                            No matching user found.\n";
    }

};
class BankSystem {
private:
    vector<Account*> accounts;

public:
    void adduserAccount() {
        Account* a = new userAccount();
        a->createAccount();
        accounts.push_back(a);
        cout << "                            User Account added successfully!\n";
    }

    void addemployeeAccount() {
        Account* b = new employeeAccount();
        b->createAccount();
        accounts.push_back(b);
        cout << "                            Employee Account added successfully!\n";
    }

    void showAllAccounts() {
        for (auto acc : accounts) {
            acc->showAccount();
            cout << "                            --------------------------\n";
        }
    }

    vector<Account*>& getAccounts() {
        return accounts;
    }

    ~BankSystem() {
        for (auto acc : accounts) delete acc;
    }
};

int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n                            ========== BANK MENU ==========\n";
        cout << "                            1. Add User Account\n";
        cout << "                            2. Add Employee Account\n";
        cout << "                            3. Show All Accounts (Employee Only)\n";
        cout << "                            4. User Login\n";
        cout << "                            5. Employee Login\n";
        cout << "                            6. Exit\n";
        cout << "                            Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: bank.adduserAccount(); break;
        case 2: bank.addemployeeAccount(); break;
        case 3: {
            string name;
            int id;
            bool found = false;
            cin.ignore();
            cout << "                            Enter your name: ";
            getline(cin, name);
            cout << "                            Enter your Employee ID: ";
            cin >> id;

            for (auto acc : bank.getAccounts()) {
                employeeAccount* emp = dynamic_cast<employeeAccount*>(acc);
                if (emp && emp->getName() == name && emp->getEmployeeID() == id) {
                    found = true;
                    break;
                }
            }

            if (found) bank.showAllAccounts();
            else cout << "                            Access denied.\n";
            break;
        }
        case 4: {
            string name;
            int pass;
            bool found = false;
            cin.ignore();
            cout << "                            Enter username: ";
            getline(cin, name);
            cout << "                            Enter password: ";
            cin >> pass;

            for (auto acc : bank.getAccounts()) {
                userAccount* user = dynamic_cast<userAccount*>(acc);
                if (user && user->getName() == name && user->getPassword() == pass) {
                    found = true;
                    int opt;
                    do {
                        cout << "\n                            -- User Menu --\n";
                        cout << "                            1: Deposit Money\n";
                        cout << "                            2: Withdraw Money\n";
                        cout << "                            3: Bill Payment\n";
                        cout << "                            4: Loan\n";
                        cout << "                            5: Show Account\n";
                        cout << "                            6: Logout\n";
                        cout << "                            Enter option: ";
                        cin >> opt;

                        if (opt == 1) user->depositMoney();
                        else if (opt == 2) user->withdrawMoney();
                        else if (opt == 3) user->billpayment();
                        else if (opt == 4) user->loan();
                        else if (opt == 5) user->showAccount();

                    } while (opt != 6);
                    break;
                }
            }

            if (!found) cout << "                            Login failed.\n";
            break;
        }
        case 5: {
            string name;
            int id;
            bool found = false;
            cin.ignore();
            cout << "                            Enter name: ";
            getline(cin, name);
            cout << "                            Enter Employee ID: ";
            cin >> id;

            for (auto acc : bank.getAccounts()) {
                employeeAccount* emp = dynamic_cast<employeeAccount*>(acc);
                if (emp && emp->getName() == name && emp->getEmployeeID() == id) {
                    found = true;
                    int opt;
                    do {
                        cout << "\n                            -- Employee Menu --\n";
                        cout << "                            1: Customer Details\n";
                        cout << "                            2: Withdrawal History\n";
                        cout << "                            3: Deposit History\n";
                        cout << "                            4: Show Own Account\n";
                        cout << "                            5: Logout\n";
                        cout << "                            Enter option: ";
                        cin >> opt;

                        if (opt == 1) emp->Customerdetails(bank.getAccounts());
                        else if (opt == 2) emp->withdrawhistroy(bank.getAccounts());
                        else if (opt == 3) emp->Deposithistroy(bank.getAccounts());
                        else if (opt == 4) emp->showAccount();

                    } while (opt != 5);
                    break;
                }
            }

            if (!found) cout << "                            Login failed.\n";
            break;
        }
        case 6:
            cout << "                            Exiting program...\n";
            break;
        default:
            cout << "                            Invalid choice. Try again.\n";
        }
    } while (choice != 6);
    return 0;
}
