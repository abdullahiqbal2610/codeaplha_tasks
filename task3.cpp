//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <sstream>
//#include <iomanip>
//#include <ctime>      // for time/date
//#include <limits>
//
//using namespace std;
//
//// ---------------------------------------------------------
////  Configuration / Constants
//// ---------------------------------------------------------
//const int TERMINAL_WIDTH = 80;
//
//// File names
//const string CUSTOMER_FILE = "customers.txt";
//const string ACCOUNT_FILE = "accounts.txt";
//const string TRANS_FILE = "transactions.txt";
//
//// ---------------------------------------------------------
////  Utility Functions
//// ---------------------------------------------------------
//string center(const string& s, int width = TERMINAL_WIDTH) {
//    int pad = (width - s.size()) / 2;
//    return (pad > 0 ? string(pad, ' ') : "") + s;
//}
//
//void clearInputBuffer() {
//    cin.clear();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//}
//
//// Returns current date/time string (e.g., "2025-03-05_14:23:59")
//string getCurrentDateTime() {
//    time_t now = time(nullptr);
//    tm localTime;  // a stack-based tm struct
//    localtime_s(&localTime, &now);  // safe call on MSVC
//
//    ostringstream oss;
//    oss << (1900 + localTime.tm_year) << "-"
//        << setw(2) << setfill('0') << (1 + localTime.tm_mon) << "-"
//        << setw(2) << setfill('0') << localTime.tm_mday << "_"
//        << setw(2) << setfill('0') << localTime.tm_hour << ":"
//        << setw(2) << setfill('0') << localTime.tm_min << ":"
//        << setw(2) << setfill('0') << localTime.tm_sec;
//
//    // rest of your function...
//
//
//    return oss.str();
//}
//
//// Generate a new ID by reading a file and returning maxID + 1
//int generateNewID(const string& filename) {
//    ifstream file(filename);
//    if (!file.is_open()) {
//        return 1001;
//    }
//    int maxID = 0;
//    while (!file.eof()) {
//        string line;
//        getline(file, line);
//        if (line.empty()) continue;
//        istringstream iss(line);
//        int id;
//        iss >> id;
//        if (!iss.fail() && id > maxID) {
//            maxID = id;
//        }
//    }
//    file.close();
//    return maxID + 1;
//}
//
//// ---------------------------------------------------------
////  Class: Customer
//// ---------------------------------------------------------
//class Customer {
//private:
//    int customerID;
//    string firstName;
//    string lastName;
//    string password;  // For demo, stored as plain text
//
//public:
//    Customer() : customerID(0), firstName(""), lastName(""), password("") {}
//    Customer(int id, const string& fn, const string& ln, const string& pw)
//        : customerID(id), firstName(fn), lastName(ln), password(pw) {
//    }
//
//    int getCustomerID() const { return customerID; }
//    string getFirstName() const { return firstName; }
//    string getLastName() const { return lastName; }
//    string getPassword() const { return password; }
//
//    void saveToFile() {
//        ofstream ofs(CUSTOMER_FILE, ios::app);
//        if (!ofs) {
//            cerr << "Error opening customer file for writing!\n";
//            return;
//        }
//        ofs << customerID << " " << firstName << " " << lastName << " " << password << "\n";
//        ofs.close();
//    }
//
//    // Static login: find matching firstName and password
//    static Customer login(const string& fName, const string& pw) {
//        ifstream ifs(CUSTOMER_FILE);
//        if (!ifs) {
//            cerr << "Error opening customer file for reading!\n";
//            return Customer();
//        }
//        while (!ifs.eof()) {
//            int cID;
//            string fn, ln, pass;
//            ifs >> cID >> fn >> ln >> pass;
//            if (ifs.fail()) break;
//            if (fn == fName && pass == pw) {
//                return Customer(cID, fn, ln, pass);
//            }
//        }
//        return Customer();
//    }
//};
//
//// ---------------------------------------------------------
////  Class: Account
//// ---------------------------------------------------------
//class Account {
//private:
//    int accountID;
//    int customerID;
//    string accountType;  // e.g., "Checking" or "Savings"
//    double balance;
//
//public:
//    Account() : accountID(0), customerID(0), accountType(""), balance(0.0) {}
//    Account(int accID, int custID, const string& type, double bal)
//        : accountID(accID), customerID(custID), accountType(type), balance(bal) {
//    }
//
//    int getAccountID() const { return accountID; }
//    int getCustomerID() const { return customerID; }
//    string getAccountType() const { return accountType; }
//    double getBalance() const { return balance; }
//
//    void setBalance(double bal) { balance = bal; }
//
//    void saveToFile() {
//        ofstream ofs(ACCOUNT_FILE, ios::app);
//        if (!ofs) {
//            cerr << "Error opening account file for writing!\n";
//            return;
//        }
//        ofs << accountID << " " << customerID << " " << accountType << " " << balance << "\n";
//        ofs.close();
//    }
//
//    static vector<Account> loadAccountsByCustomer(int custID) {
//        vector<Account> accounts;
//        ifstream ifs(ACCOUNT_FILE);
//        if (!ifs) {
//            cerr << "Error opening account file for reading!\n";
//            return accounts;
//        }
//        while (!ifs.eof()) {
//            int aID, cID;
//            string aType;
//            double bal;
//            ifs >> aID >> cID >> aType >> bal;
//            if (ifs.fail()) break;
//            if (cID == custID) {
//                accounts.push_back(Account(aID, cID, aType, bal));
//            }
//        }
//        return accounts;
//    }
//
//    static Account loadAccountByID(int accID) {
//        ifstream ifs(ACCOUNT_FILE);
//        if (!ifs) {
//            cerr << "Error opening account file for reading!\n";
//            return Account();
//        }
//        while (!ifs.eof()) {
//            int aID, cID;
//            string aType;
//            double bal;
//            ifs >> aID >> cID >> aType >> bal;
//            if (ifs.fail()) break;
//            if (aID == accID) {
//                return Account(aID, cID, aType, bal);
//            }
//        }
//        return Account();
//    }
//
//    static void updateBalanceInFile(const Account& acc) {
//        ifstream ifs(ACCOUNT_FILE);
//        vector<Account> allAccounts;
//        if (ifs) {
//            while (!ifs.eof()) {
//                int aID, cID;
//                string aType;
//                double bal;
//                ifs >> aID >> cID >> aType >> bal;
//                if (ifs.fail()) break;
//                allAccounts.push_back(Account(aID, cID, aType, bal));
//            }
//            ifs.close();
//        }
//        // Update the matching account
//        for (auto& a : allAccounts) {
//            if (a.getAccountID() == acc.getAccountID()) {
//                a.setBalance(acc.getBalance());
//                break;
//            }
//        }
//        ofstream ofs(ACCOUNT_FILE, ios::trunc);
//        for (const auto& a : allAccounts) {
//            ofs << a.getAccountID() << " "
//                << a.getCustomerID() << " "
//                << a.getAccountType() << " "
//                << a.getBalance() << "\n";
//        }
//        ofs.close();
//    }
//};
//
//// ---------------------------------------------------------
////  Class: Transaction
//// ---------------------------------------------------------
//class Transaction {
//private:
//    int transactionID;
//    int accountID;
//    string dateTime;
//    string type;      // "Deposit", "Withdraw", "Transfer"
//    double amount;
//
//public:
//    Transaction() : transactionID(0), accountID(0), dateTime(""), type(""), amount(0.0) {}
//    Transaction(int tID, int aID, const string& dt, const string& tp, double amt)
//        : transactionID(tID), accountID(aID), dateTime(dt), type(tp), amount(amt) {
//    }
//
//    int getTransactionID() const { return transactionID; }
//    int getAccountID() const { return accountID; }
//    string getDateTime() const { return dateTime; }
//    string getType() const { return type; }
//    double getAmount() const { return amount; }
//
//    void saveToFile() {
//        ofstream ofs(TRANS_FILE, ios::app);
//        if (!ofs) {
//            cerr << "Error opening transaction file!\n";
//            return;
//        }
//        ofs << transactionID << " " << accountID << " " << dateTime
//            << " " << type << " " << amount << "\n";
//        ofs.close();
//    }
//
//    static vector<Transaction> loadTransactionsByAccount(int accID) {
//        vector<Transaction> txns;
//        ifstream ifs(TRANS_FILE);
//        if (!ifs) {
//            cerr << "Error opening transaction file!\n";
//            return txns;
//        }
//        while (!ifs.eof()) {
//            int tID, aID;
//            string dt, tp;
//            double amt;
//            ifs >> tID >> aID >> dt >> tp >> amt;
//            if (ifs.fail()) break;
//            if (aID == accID) {
//                txns.push_back(Transaction(tID, aID, dt, tp, amt));
//            }
//        }
//        return txns;
//    }
//};
//
//// ---------------------------------------------------------
////  Class: BankController
////     This class acts as the controller for the system.
//// ---------------------------------------------------------
//class BankController {
//public:
//    void run() {
//        // Print welcome header
//        cout << "\033[1;32m" << center("WELCOME TO THE OOP BANKING SYSTEM") << "\033[0m\n";
//        cout << "\033[1;33m" << center("by Muhammad Abdullah Iqbal") << "\033[0m\n\n";
//
//        while (true) {
//            cout << "\033[1;35m" << center("MAIN MENU") << "\033[0m\n";
//            cout << center("1. Register  2. Login  3. Quit") << "\n";
//            cout << center("Enter your choice: ");
//            int choice;
//            cin >> choice;
//            clearInputBuffer();
//
//            if (cin.fail()) {
//                cout << "\033[1;31m" << center("Invalid input!") << "\033[0m\n\n";
//                continue;
//            }
//
//            if (choice == 1) {
//                registerCustomer();
//            }
//            else if (choice == 2) {
//                loginUser();
//            }
//            else if (choice == 3) {
//                cout << "\033[1;33m" << center("Exiting the system... Goodbye!") << "\033[0m\n";
//                break;
//            }
//            else {
//                cout << "\033[1;31m" << center("Invalid choice!") << "\033[0m\n\n";
//            }
//        }
//    }
//
//private:
//    // Registration function
//    void registerCustomer() {
//        cout << "\n\033[1;36m" << center("REGISTER NEW CUSTOMER") << "\033[0m\n\n";
//
//        string firstName, lastName, password;
//        cout << center("Enter First Name: ");
//        cin >> firstName;
//        clearInputBuffer();
//
//        cout << center("Enter Last Name: ");
//        cin >> lastName;
//        clearInputBuffer();
//
//        cout << center("Enter Password: ");
//        cin >> password;
//        clearInputBuffer();
//
//        int newCustID = generateNewID(CUSTOMER_FILE);
//        Customer c(newCustID, firstName, lastName, password);
//        c.saveToFile();
//
//        cout << "\033[1;32m" << center("Registration Successful!") << "\033[0m\n";
//        cout << "\033[1;32m" << center("Your Customer ID: " + to_string(newCustID)) << "\033[0m\n\n";
//    }
//
//    // Login function; upon success, call the banking menu.
//    void loginUser() {
//        cout << "\n\033[1;36m" << center("LOGIN") << "\033[0m\n\n";
//        cout << center("Enter First Name: ");
//        string fname;
//        cin >> fname;
//        clearInputBuffer();
//
//        cout << center("Enter Password: ");
//        string pw;
//        cin >> pw;
//        clearInputBuffer();
//
//        Customer c = Customer::login(fname, pw);
//        if (c.getCustomerID() == 0) {
//            cout << "\033[1;31m" << center("Login Failed! Incorrect credentials.") << "\033[0m\n\n";
//        }
//        else {
//            cout << "\033[1;32m" << center("Login Successful!") << "\033[0m\n\n";
//            bankingMenu(c);
//        }
//    }
//
//    // Banking menu (after login)
//    void bankingMenu(const Customer& cust) {
//        bool loggedIn = true;
//        while (loggedIn) {
//            cout << "\033[1;35m" << center("BANKING MENU") << "\033[0m\n";
//            cout << center("1. Create New Account  2. Deposit  3. Withdraw") << "\n";
//            cout << center("4. Transfer           5. View Accounts  6. View Transactions") << "\n";
//            cout << center("7. Logout") << "\n";
//            cout << center("Enter choice: ");
//            int opt;
//            cin >> opt;
//            clearInputBuffer();
//
//            switch (opt) {
//            case 1: createNewAccount(cust); break;
//            case 2: depositMoney(cust); break;
//            case 3: withdrawMoney(cust); break;
//            case 4: transferMoney(cust); break;
//            case 5: viewAccounts(cust); break;
//            case 6: viewTransactions(cust); break;
//            case 7:
//                loggedIn = false;
//                cout << "\033[1;33m" << center("Logging out...") << "\033[0m\n\n";
//                break;
//            default:
//                cout << "\033[1;31m" << center("Invalid option!") << "\033[0m\n\n";
//            }
//        }
//    }
//
//    // ---------------------
//    // Banking Operations:
//    // ---------------------
//    void createNewAccount(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("CREATE NEW ACCOUNT") << "\033[0m\n\n";
//        cout << center("Enter Account Type (Checking/Savings): ");
//        string type;
//        cin >> type;
//        clearInputBuffer();
//
//        cout << center("Enter initial deposit amount: ");
//        double amount;
//        cin >> amount;
//        clearInputBuffer();
//        if (amount < 0) {
//            cout << "\033[1;31m" << center("Invalid deposit amount!") << "\033[0m\n";
//            return;
//        }
//        int newAccID = generateNewID(ACCOUNT_FILE);
//        Account acc(newAccID, cust.getCustomerID(), type, amount);
//        acc.saveToFile();
//
//        int newTxnID = generateNewID(TRANS_FILE);
//        Transaction txn(newTxnID, newAccID, getCurrentDateTime(), "Deposit", amount);
//        txn.saveToFile();
//
//        cout << "\033[1;32m" << center("Account created successfully!") << "\033[0m\n";
//        cout << "\033[1;32m" << center("Account ID: " + to_string(newAccID)) << "\033[0m\n\n";
//    }
//
//    void depositMoney(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("DEPOSIT MONEY") << "\033[0m\n\n";
//        vector<Account> accounts = Account::loadAccountsByCustomer(cust.getCustomerID());
//        if (accounts.empty()) {
//            cout << "\033[1;31m" << center("No accounts found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Your Accounts:") << "\n";
//        for (const auto& a : accounts) {
//            cout << center("AccountID: " + to_string(a.getAccountID()) + " (" + a.getAccountType() + ") Balance: " + to_string(a.getBalance())) << "\n";
//        }
//        cout << center("Enter Account ID to deposit into: ");
//        int accID;
//        cin >> accID;
//        clearInputBuffer();
//
//        bool found = false;
//        Account chosen;
//        for (const auto& a : accounts) {
//            if (a.getAccountID() == accID) {
//                chosen = a;
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            cout << "\033[1;31m" << center("Invalid account ID!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Enter deposit amount: ");
//        double amt;
//        cin >> amt;
//        clearInputBuffer();
//        if (amt <= 0) {
//            cout << "\033[1;31m" << center("Invalid deposit amount!") << "\033[0m\n";
//            return;
//        }
//        chosen.setBalance(chosen.getBalance() + amt);
//        Account::updateBalanceInFile(chosen);
//
//        int newTxnID = generateNewID(TRANS_FILE);
//        Transaction txn(newTxnID, chosen.getAccountID(), getCurrentDateTime(), "Deposit", amt);
//        txn.saveToFile();
//
//        cout << "\033[1;32m" << center("Deposit successful!") << "\033[0m\n\n";
//    }
//
//    void withdrawMoney(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("WITHDRAW MONEY") << "\033[0m\n\n";
//        vector<Account> accounts = Account::loadAccountsByCustomer(cust.getCustomerID());
//        if (accounts.empty()) {
//            cout << "\033[1;31m" << center("No accounts found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Your Accounts:") << "\n";
//        for (const auto& a : accounts) {
//            cout << center("AccountID: " + to_string(a.getAccountID()) + " (" + a.getAccountType() + ") Balance: " + to_string(a.getBalance())) << "\n";
//        }
//        cout << center("Enter Account ID to withdraw from: ");
//        int accID;
//        cin >> accID;
//        clearInputBuffer();
//
//        bool found = false;
//        Account chosen;
//        for (const auto& a : accounts) {
//            if (a.getAccountID() == accID) {
//                chosen = a;
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            cout << "\033[1;31m" << center("Invalid account ID!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Enter withdrawal amount: ");
//        double amt;
//        cin >> amt;
//        clearInputBuffer();
//        if (amt <= 0) {
//            cout << "\033[1;31m" << center("Invalid withdrawal amount!") << "\033[0m\n";
//            return;
//        }
//        if (amt > chosen.getBalance()) {
//            cout << "\033[1;31m" << center("Insufficient balance!") << "\033[0m\n";
//            return;
//        }
//        chosen.setBalance(chosen.getBalance() - amt);
//        Account::updateBalanceInFile(chosen);
//
//        int newTxnID = generateNewID(TRANS_FILE);
//        Transaction txn(newTxnID, chosen.getAccountID(), getCurrentDateTime(), "Withdraw", amt);
//        txn.saveToFile();
//
//        cout << "\033[1;32m" << center("Withdrawal successful!") << "\033[0m\n\n";
//    }
//
//    void transferMoney(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("TRANSFER MONEY") << "\033[0m\n\n";
//        vector<Account> accounts = Account::loadAccountsByCustomer(cust.getCustomerID());
//        if (accounts.empty()) {
//            cout << "\033[1;31m" << center("No accounts found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Your Accounts:") << "\n";
//        for (const auto& a : accounts) {
//            cout << center("AccountID: " + to_string(a.getAccountID()) + " (" + a.getAccountType() + ") Balance: " + to_string(a.getBalance())) << "\n";
//        }
//        cout << center("Enter source Account ID: ");
//        int srcID;
//        cin >> srcID;
//        clearInputBuffer();
//
//        cout << center("Enter destination Account ID: ");
//        int destID;
//        cin >> destID;
//        clearInputBuffer();
//
//        if (srcID == destID) {
//            cout << "\033[1;31m" << center("Cannot transfer to the same account!") << "\033[0m\n";
//            return;
//        }
//        Account srcAcc = Account::loadAccountByID(srcID);
//        Account destAcc = Account::loadAccountByID(destID);
//        if (srcAcc.getAccountID() == 0 || destAcc.getAccountID() == 0) {
//            cout << "\033[1;31m" << center("Invalid source or destination account!") << "\033[0m\n";
//            return;
//        }
//        if (srcAcc.getCustomerID() != cust.getCustomerID()) {
//            cout << "\033[1;31m" << center("You do not own the source account!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Enter transfer amount: ");
//        double amt;
//        cin >> amt;
//        clearInputBuffer();
//        if (amt <= 0) {
//            cout << "\033[1;31m" << center("Invalid transfer amount!") << "\033[0m\n";
//            return;
//        }
//        if (amt > srcAcc.getBalance()) {
//            cout << "\033[1;31m" << center("Insufficient balance in source account!") << "\033[0m\n";
//            return;
//        }
//        srcAcc.setBalance(srcAcc.getBalance() - amt);
//        destAcc.setBalance(destAcc.getBalance() + amt);
//        Account::updateBalanceInFile(srcAcc);
//        Account::updateBalanceInFile(destAcc);
//
//        int newTxnID1 = generateNewID(TRANS_FILE);
//        Transaction txn1(newTxnID1, srcAcc.getAccountID(), getCurrentDateTime(), "Transfer", amt);
//        txn1.saveToFile();
//
//        int newTxnID2 = generateNewID(TRANS_FILE);
//        Transaction txn2(newTxnID2, destAcc.getAccountID(), getCurrentDateTime(), "Transfer", amt);
//        txn2.saveToFile();
//
//        cout << "\033[1;32m" << center("Transfer successful!") << "\033[0m\n\n";
//    }
//
//    void viewAccounts(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("VIEW ACCOUNTS") << "\033[0m\n\n";
//        vector<Account> accounts = Account::loadAccountsByCustomer(cust.getCustomerID());
//        if (accounts.empty()) {
//            cout << "\033[1;31m" << center("No accounts found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Your Accounts:") << "\n";
//        for (const auto& a : accounts) {
//            ostringstream oss;
//            oss << "AccountID: " << a.getAccountID()
//                << " | Type: " << a.getAccountType()
//                << " | Balance: " << a.getBalance();
//            cout << center(oss.str()) << "\n";
//        }
//        cout << "\n";
//    }
//
//    void viewTransactions(const Customer& cust) {
//        cout << "\n\033[1;36m" << center("VIEW TRANSACTIONS") << "\033[0m\n\n";
//        vector<Account> accounts = Account::loadAccountsByCustomer(cust.getCustomerID());
//        if (accounts.empty()) {
//            cout << "\033[1;31m" << center("No accounts found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Your Accounts:") << "\n";
//        for (const auto& a : accounts) {
//            ostringstream oss;
//            oss << "AccountID: " << a.getAccountID()
//                << " | Type: " << a.getAccountType()
//                << " | Balance: " << a.getBalance();
//            cout << center(oss.str()) << "\n";
//        }
//        cout << center("Enter Account ID to view transactions: ");
//        int accID;
//        cin >> accID;
//        clearInputBuffer();
//
//        bool found = false;
//        for (const auto& a : accounts) {
//            if (a.getAccountID() == accID) {
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            cout << "\033[1;31m" << center("Invalid account ID!") << "\033[0m\n";
//            return;
//        }
//        vector<Transaction> txns = Transaction::loadTransactionsByAccount(accID);
//        if (txns.empty()) {
//            cout << "\033[1;31m" << center("No transactions found!") << "\033[0m\n";
//            return;
//        }
//        cout << center("Transaction History for AccountID: " + to_string(accID)) << "\n\n";
//        for (const auto& t : txns) {
//            ostringstream oss;
//            oss << "TxnID: " << t.getTransactionID()
//                << " | Date: " << t.getDateTime()
//                << " | Type: " << t.getType()
//                << " | Amount: " << t.getAmount();
//            cout << center(oss.str()) << "\n";
//        }
//        cout << "\n";
//    }
//};
//
//// ---------------------------------------------------------
////  Main: Instantiate and run the controller
//// ---------------------------------------------------------
//int main() {
//    BankController controller;
//    controller.run();
//    return 0;
//}
