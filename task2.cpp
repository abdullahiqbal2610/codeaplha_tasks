#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>    // for isdigit
#include <cstdlib>   // for system("CLS") or system("clear") if needed
#include <vector>

using namespace std;

const int TERMINAL_WIDTH = 80;
const string DATABASE_FILE = "users.txt";

// ------------- Utility: Center a string -------------
string center(const string& s, int width = TERMINAL_WIDTH) {
    int pad = (width - s.size()) / 2;
    if (pad > 0) {
        return string(pad, ' ') + s;
    }
    else {
        return s;  // If string is longer than width, just return it as-is
    }
}

// ------------- Utility: Clear input buffer -------------
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------- Validation Functions -------------
bool isValidAge(int age) {
    return (age > 0);
}

bool isValidContact(const string& contact) {
    // Basic check: ensure every character is a digit and not empty
    if (contact.empty()) return false;
    for (char c : contact) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool isValidEmail(const string& email) {
    // Very simple check: must contain '@'
    // Real-world validation would be more robust
    return (!email.empty() && (email.find('@') != string::npos));
}

// ------------- Display user info (center-aligned) -------------
void displayUserInfo(
    const string& firstName,
    const string& lastName,
    int age,
    const string& contact,
    const string& email
) {
    // Some margin to push table to the right
    string margin = "            "; // 12 spaces

    cout << "\n\033[1;32m" << center("***** USER INFORMATION *****") << "\033[0m\n\n";

    // Table-like display
    cout << margin << "\033[1;34m" << left << setw(20) << "First Name:" << "\033[0m"
        << firstName << "\n";
    cout << margin << "\033[1;34m" << left << setw(20) << "Last Name:" << "\033[0m"
        << lastName << "\n";
    cout << margin << "\033[1;34m" << left << setw(20) << "Age:" << "\033[0m"
        << age << "\n";
    cout << margin << "\033[1;34m" << left << setw(20) << "Contact:" << "\033[0m"
        << contact << "\n";
    cout << margin << "\033[1;34m" << left << setw(20) << "Email:" << "\033[0m"
        << email << "\n\n";
}

// ------------- Sign Up Function -------------
void signUp() {
    cout << "\033[1;36m" << center("SIGN UP") << "\033[0m\n\n";

    string firstName, lastName, contact, email, password;
    int age = 0;

    // First Name
    while (true) {
        cout << center("Enter First Name: ");
        cin >> firstName;
        if (!cin.fail() && !firstName.empty()) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid first name. Please try again.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Last Name
    while (true) {
        cout << center("Enter Last Name: ");
        cin >> lastName;
        if (!cin.fail() && !lastName.empty()) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid last name. Please try again.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Age
    while (true) {
        cout << center("Enter Age: ");
        cin >> age;
        if (!cin.fail() && isValidAge(age)) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid age. Must be a positive integer.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Contact
    while (true) {
        cout << center("Enter Contact Number: ");
        cin >> contact;
        if (!cin.fail() && isValidContact(contact)) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid contact number. Must be digits only.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Email
    while (true) {
        cout << center("Enter Email Address: ");
        cin >> email;
        if (!cin.fail() && isValidEmail(email)) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid email. Must contain '@'.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Password
    while (true) {
        cout << center("Enter Password: ");
        cin >> password;
        if (!cin.fail() && !password.empty()) {
            clearInputBuffer();
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid password. Cannot be empty.") << "\033[0m\n";
            clearInputBuffer();
        }
    }

    // Write to file
    ofstream outFile(DATABASE_FILE, ios::app); // append mode
    if (!outFile) {
        cout << "\033[1;31m" << center("Error opening database file!") << "\033[0m\n";
        return;
    }

    // Format: firstName lastName age contact email password
    outFile << firstName << " "
        << lastName << " "
        << age << " "
        << contact << " "
        << email << " "
        << password << "\n";
    outFile.close();

    cout << "\033[1;32m" << center("Registration successful!") << "\033[0m\n";
    cout << "\033[1;32m" << center("Use First Name + Password to log in.") << "\033[0m\n\n";
}

// ------------- Login Function -------------
void login() {
    cout << "\033[1;36m" << center("LOGIN") << "\033[0m\n\n";

    string firstName, password;
    cout << center("Enter First Name: ");
    cin >> firstName;
    clearInputBuffer();

    cout << center("Enter Password: ");
    cin >> password;
    clearInputBuffer();

    ifstream inFile(DATABASE_FILE);
    if (!inFile) {
        cout << "\033[1;31m" << center("Error opening database file!") << "\033[0m\n";
        return;
    }

    // We will read line by line and parse
    bool found = false;
    while (!inFile.eof()) {
        string fName, lName, contact, email, pass;
        int age = 0;

        // read one line
        inFile >> fName >> lName >> age >> contact >> email >> pass;
        if (inFile.fail()) break; // in case of any read error or EOF

        if (fName == firstName && pass == password) {
            // Found matching user
            found = true;
            // Display user info
            displayUserInfo(fName, lName, age, contact, email);
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "\033[1;31m" << center("Incorrect First Name or Password!") << "\033[0m\n\n";
    }
}

// ------------- Main Program -------------
int main() {
    // Title
    cout << "\033[1;32m" << center("WELCOME TO THE LOGIN & REGISTRATION SYSTEM") << "\033[0m\n\n";
    cout << "\033[1;33m" << center("by Muhammad Abdullah Iqbal") << "\033[0m\n\n";


    while (true) {
        cout << "\033[1;35m" << center("Please Choose an Option:") << "\033[0m\n";
        cout << center("1. Sign Up   2. Login   3. Quit") << "\n";

        int choice;
        cout << center("Enter your choice (1/2/3): ");
        cin >> choice;
        clearInputBuffer();

        if (cin.fail()) {
            cout << "\033[1;31m" << center("Invalid input, please enter 1, 2, or 3!") << "\033[0m\n\n";
            continue;
        }
        
        if (choice == 1) {
            signUp();
        }
        else if (choice == 2) {
            login();
        }
        else if (choice == 3) {
            cout << "\033[1;33m" << center("Exiting the program... Goodbye!") << "\033[0m\n";
            break;
        }
        else {
            cout << "\033[1;31m" << center("Invalid choice! Please enter 1, 2, or 3.") << "\033[0m\n\n";
        }
    }

    return 0;
}
