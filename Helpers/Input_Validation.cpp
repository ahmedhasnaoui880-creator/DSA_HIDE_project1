#include "Input_Validation.h"
// ========== Input Control ==========
// Validate integer input with range
int getValidInteger(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "✗ Invalid input! Please enter a number." << endl;
        } else if (value < min || value > max) {
            cin.ignore(10000, '\n');
            cout << "✗ Please enter a number between " << min << " and " << max << "." << endl;
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

// Validate double input (positive numbers)
double getValidDouble(string prompt, double min) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "✗ Invalid input! Please enter a valid number." << endl;
        } else if (value < min) {
            cin.ignore(10000, '\n');
            cout << "✗ Amount must be at least " << min << "." << endl;
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

// Validate account number (must be unique)
string getValidAccountNumber(Customer customers[], int custCount, bool checkUnique) {
    string accountNum;
    while (true) {
        cout << "Enter Account Number (numeric): ";
        getline(cin, accountNum);
        
        if (accountNum.empty()) {
            cout << "✗ Account number cannot be empty!" << endl;
            continue;
        }
        
        // Check if all characters are digits
        bool isNumeric = true;
        for (size_t i = 0; i < accountNum.length(); i++) {
            if (!isdigit(accountNum[i])) {
                isNumeric = false;
                break;
            }
        }
        
        if (!isNumeric) {
            cout << "✗ Account number must contain only digits!" << endl;
            continue;
        }
        
        // Check uniqueness if required
        if (checkUnique) {
            bool exists = false;
            for (int i = 0; i < custCount; i++) {
                if (customers[i].account_number == accountNum) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                cout << "✗ Account number already exists! Please use a unique number." << endl;
                continue;
            }
        }
        
        return accountNum;
    }
}

// Validate employee ID (must be unique)
int getValidEmployeeID(Employee employees[], int empCount, bool checkUnique) {
    int empID;
    while (true) {
        empID = getValidInteger("Enter Employee ID (positive number): ", 1, 999999);
        
        if (checkUnique) {
            bool exists = false;
            for (int i = 0; i < empCount; i++) {
                if (employees[i].employeeID == empID) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                cout << "✗ Employee ID already exists! Please use a unique ID." << endl;
                continue;
            }
        }
        
        return empID;
    }
}

// Validate loan ID (must be unique)
int getValidLoanID(LoanList* globalLoans, Customer customers[], int custCount) {
    int loanID;
    while (true) {
        loanID = getValidInteger("Enter Loan ID (positive number): ", 1, 999999);
        
        // Check in global loan applications
        bool exists = false;
        if (globalLoans && globalLoans->head) {
            LoanNode* current = globalLoans->head;
            while (current) {
                if (current->data.loanID == loanID) {
                    exists = true;
                    break;
                }
                current = current->next;
            }
        }
        
        // Check in all customer loans
        if (!exists) {
            for (int i = 0; i < custCount; i++) {
                if (customers[i].loans && customers[i].loans->head) {
                    LoanNode* current = customers[i].loans->head;
                    while (current) {
                        if (current->data.loanID == loanID) {
                            exists = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (exists) break;
                }
            }
        }
        
        if (exists) {
            cout << "✗ Loan ID already exists! Please use a unique ID." << endl;
            continue;
        }
        
        return loanID;
    }
}

// Validate date format (DD/MM/YYYY)
string getValidDate(string prompt) {
    string date;
    while (true) {
        cout << prompt;
        getline(cin, date);
        
        if (date.length() != 10) {
            cout << "✗ Invalid format! Use DD/MM/YYYY (e.g., 15/12/2024)" << endl;
            continue;
        }
        
        if (date[2] != '/' || date[5] != '/') {
            cout << "✗ Invalid format! Use DD/MM/YYYY with slashes" << endl;
            continue;
        }
        
        // Extract day, month, year
        string dayStr = date.substr(0, 2);
        string monthStr = date.substr(3, 2);
        string yearStr = date.substr(6, 4);
        
        // Check if all are digits
        bool valid = true;
        for (int i = 0; i < 2; i++) {
            if (!isdigit(dayStr[i]) || !isdigit(monthStr[i])) {
                valid = false;
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (!isdigit(yearStr[i])) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            cout << "✗ Date must contain only numbers!" << endl;
            continue;
        }
        
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        
        if (day < 1 || day > 31) {
            cout << "✗ Day must be between 1 and 31!" << endl;
            continue;
        }
        if (month < 1 || month > 12) {
            cout << "✗ Month must be between 1 and 12!" << endl;
            continue;
        }
        if (year < 1900 || year > 2100) {
            cout << "✗ Year must be between 1900 and 2100!" << endl;
            continue;
        }
        
        return date;
    }
}

// Validate account status
string getValidStatus() {
    string status;
    while (true) {
        cout << "Enter Status (active/inactive/closed): ";
        getline(cin, status);
        
        // Convert to lowercase
        for (size_t i = 0; i < status.length(); i++) {
            status[i] = tolower(status[i]);
        }
        
        if (status == "active" || status == "inactive" || status == "closed") {
            return status;
        }
        
        cout << "✗ Invalid status! Must be: active, inactive, or closed" << endl;
    }
}

// Validate loan type
string getValidLoanType() {
    string type;
    while (true) {
        cout << "Enter Loan Type (car/home/student/business): ";
        getline(cin, type);
        
        // Convert to lowercase
        for (size_t i = 0; i < type.length(); i++) {
            type[i] = tolower(type[i]);
        }
        
        if (type == "car" || type == "home" || type == "student" || type == "business") {
            return type;
        }
        
        cout << "✗ Invalid type! Must be: car, home, student, or business" << endl;
    }
}

// Validate interest rate (0.0 to 1.0)
double getValidInterestRate() {
    double rate;
    while (true) {
        cout << "Enter Interest Rate (0-100%): ";
        cin >> rate;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "✗ Invalid input! Please enter a number." << endl;
        } else if (rate < 0 || rate > 100) {
            cin.ignore(10000, '\n');
            cout << "✗ Interest rate must be between 0 and 100!" << endl;
        } else {
            cin.ignore(10000, '\n');
            return rate / 100.0;  // Convert percentage to decimal
        }
    }
}

// Validate non-empty string
string getValidString(string prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        
        if (value.empty()) {
            cout << "✗ This field cannot be empty!" << endl;
            continue;
        }
        
        return value;
    }
}

// Validate bank branch (1 for head office, 101+ for branches)
int getValidBankBranch() {
    int branch;
    while (true) {
        cout << "Enter Bank Branch (1=Head Office, 101+=Branches): ";
        cin >> branch;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "✗ Invalid input! Please enter a number." << endl;
        } else if (branch != 1 && branch < 101) {
            cin.ignore(10000, '\n');
            cout << "✗ Branch must be 1 (Head Office) or 101+ (Branches)!" << endl;
        } else {
            cin.ignore(10000, '\n');
            return branch;
        }
    }
}

// Validate IBAN format (TN + 20 digits)
string getValidIBAN() {
    string iban;
    while (true) {
        cout << "Enter IBAN (Format: TN + 20 digits): ";
        getline(cin, iban);
        
        if (iban.length() != 22) {
            cout << "✗ IBAN must be exactly 22 characters!" << endl;
            continue;
        }
        
        if (iban[0] != 'T' || iban[1] != 'N') {
            cout << "✗ IBAN must start with 'TN'!" << endl;
            continue;
        }
        
        bool valid = true;
        for (int i = 2; i < 22; i++) {
            if (!isdigit(iban[i])) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            cout << "✗ IBAN must have 20 digits after 'TN'!" << endl;
            continue;
        }
        
        return iban;
    }
}