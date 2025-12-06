#include "trStack.h"
#include "Customer.h"
#include "LoanList.h"
#include "Employee.h"
#include "LoanMeth.h"
#include "TransactionMeth.h"
#include "trStack.h"
#include "Customer_Interface.h"
#include "Employee_Space.h"
#include "StatisticsMeth.h"
#include <fstream>
#include <iostream>
#include <string>
#include "CompletedLoansMeth.h"
#include "EndTransactionMeth.h"
#include <ctime>
#include <cstdlib>
#include "Input_Validation.h"
LoanList* globalLoanApplications=createLoanList();
using namespace std;
void displayStatistics(Employee employees[], int empcount,Customer* customers,int customerCount);
void bakcupcompletedloans(CompletedLoansList* clist);
CompletedLoansList* loadCompletedLoans(string clfile);
void displayHeader(string title);
void pauseScreen();
void mainInterface();
void displayHeader(string title) {
    cout << "\n========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================\n" << endl;
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
Customer Split_line_to_customer(string line){
    Customer cust;
    string linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_number = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_type = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.IBAN = linepart;
    linepart = line.substr(0, line.find(',')); 
    line.erase(0, line.find(',') + 1);
    cust.branch_code = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_holder_name = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.opening_date = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.status = linepart;
    linepart = line.substr(0, line.find(','));
    cust.balance = stod(linepart);
    return cust;
    }
LoanList* getCustomerLoans(string account_number){
    ifstream file("../Data/Loans.txt");
    if (!file) {
        return nullptr;
    }
    LoanList* loans = createLoanList();
    string line;
    while (getline(file, line)){
        string linepart = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (linepart == account_number){
            Loan loan;
            loan.account_number = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanID = stoi(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanType = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.principalAmount = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.interestRate = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.amountPaid = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.remainingBalance = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.startDate = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.endDate = linepart;
            linepart = line.substr(0, line.find(','));
            loan.status = linepart;
            LoanNode* newNode = createLoanNode(loan);
            if (loans->size == 0) {
                loans->head = newNode;
                loans->tail = newNode;
            } else {
                loans->tail->next = newNode;
                newNode->prev = loans->tail;
                loans->tail = newNode;
            }
            loans->size++;
        }
    }
    file.close();
    return loans;
}
LoanList* loadLoanApplications() {
    ifstream file("../Data/LoanApplications.txt");
    LoanList* apps = createLoanList();
    if (!file) return apps;  // Return empty list if file doesn't exist
    
    string line;
    while (getline(file, line)) {
            // Parse loan data
            Loan loan;
            string linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.account_number = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanID = stoi(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanType = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.principalAmount = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.interestRate = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.amountPaid = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.remainingBalance = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.startDate = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.endDate = linepart;
            linepart = line.substr(0, line.find(','));
            loan.status = linepart;
        if (loan.status == "pending") {
            SubmitLoanApplication(loan, apps);
        }
    }
    file.close();
    return apps;
}

TransactionStack* getCustomerTransactions(string account_number){
    ifstream file("../Data/Transactions.txt");
    if (!file) {
        cout << "Warning: Could not open transactions file." << endl;
        return createTransactionStack();
    }
    
    TransactionStack* trStack = createTransactionStack();
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip empty lines
        
        string originalLine = line;  // Keep original for debugging
        Transaction transaction;
        
        // Read transaction_id
        string linepart = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        transaction.transaction_id = linepart;
        
        // Read account_number
        linepart = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        string txAccountNum = linepart;
        
        // Only process if this transaction belongs to this customer
        if (txAccountNum == account_number) {
            transaction.account_number = txAccountNum;
            
            // Read type
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            transaction.type = linepart;
            
            // Read amount
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            transaction.amount = stod(linepart);
            
            // Read date (rest of line, remove trailing comma if present)
            transaction.date = line;
            if (!transaction.date.empty() && transaction.date[transaction.date.length()-1] == ',') {
                transaction.date.erase(transaction.date.length()-1);
            }
            
            pushTransaction(trStack, transaction);
        }
    }
    
    file.close();
    return trStack;
}
void BackupData(const Customer customers[],int customerCount,const Employee employees[],int empcount){
    if (customerCount <= 0) {
        cout << "Warning: No customers to backup." << endl;
        return;
    }
    
    // NOW open files - after we know we have data
    ofstream custfile("../Data/Customers.txt");
    ofstream loanfile("../Data/Loans.txt");
    ofstream transfile("../Data/Transactions.txt");
    
    if (!custfile || !loanfile || !transfile) {
        cout << "Error opening file for backup." << endl;
        return;
    }
    
    // Backup customers
    for (int i = 0; i < customerCount; i++) {
        custfile << customers[i].account_number << "," 
                 << customers[i].account_type << "," 
                 << customers[i].IBAN << "," 
                 << customers[i].branch_code << "," 
                 << customers[i].account_holder_name << "," 
                 << customers[i].opening_date << "," 
                 << customers[i].status << "," 
                 << customers[i].balance << "," << endl;
        
        // Backup loans for this customer
        if (customers[i].loans && customers[i].loans->head) {
            LoanNode* currentLoan = customers[i].loans->head;
            while (currentLoan != nullptr) {
                loanfile << currentLoan->data.account_number << "," 
                        << currentLoan->data.loanID << "," 
                        << currentLoan->data.loanType << "," 
                        << currentLoan->data.principalAmount << "," 
                        << currentLoan->data.interestRate << "," 
                        << currentLoan->data.amountPaid << "," 
                        << currentLoan->data.remainingBalance << "," 
                        << currentLoan->data.startDate << "," 
                        << currentLoan->data.endDate << "," 
                        << currentLoan->data.status << "," << endl;
                currentLoan = currentLoan->next;
            }
        }
        
        // Backup transactions for this customer
        if (customers[i].transactions && customers[i].transactions->top) {
            TransactionStackNode* currentTransaction = customers[i].transactions->top;
            while (currentTransaction != nullptr) {
                transfile << currentTransaction->data.transaction_id << "," 
                        << currentTransaction->data.account_number << "," 
                        << currentTransaction->data.type << "," 
                        << currentTransaction->data.amount << "," 
                        << currentTransaction->data.date << endl;
                currentTransaction = currentTransaction->next;
            }
        }
    }
    // Backup Loan Applications
    ofstream appfile("../Data/LoanApplications.txt");
    LoanNode* appNode = globalLoanApplications->head;
    while (appNode) {
    appfile <<appNode->data.account_number << ","
            <<appNode->data.loanID << "," 
            <<appNode->data.loanType <<","
            <<appNode->data.principalAmount <<","
            <<appNode->data.interestRate <<","
            <<appNode->data.amountPaid <<","
            <<appNode->data.remainingBalance <<","
            <<appNode->data.startDate <<","
            <<appNode->data.endDate <<","
            <<appNode->data.status <<","
            << endl;
            appNode = appNode->next;
}
    
    custfile.close();
    loanfile.close();
    transfile.close();
    
    // Backup employees
    if (empcount > 0 && employees != nullptr) {
        ofstream empfile("../Data/Employees.txt");
        if (!empfile) {
            cout << "Error opening employee file for backup." << endl;
            return;
        }
        
        for (int i = 0; i < empcount; i++) {
            empfile << employees[i].employeeID << "," 
                   << employees[i].name << "," 
                   << employees[i].lastName << "," 
                   << employees[i].adress << "," 
                   << employees[i].salary << "," 
                   << employees[i].hireDate << "," 
                   << employees[i].BankBranch << "," << endl;
        }
        empfile.close();
    }
    
    cout << "✓ Data backup completed successfully." << endl;
}
void loginCustomerInterface(Customer customers[], int customerCount)
{
    string account_number;
    cout << "Please enter your account number: ";
    cin >> account_number;
    cin.ignore(10000, '\n');
    
    int index = 0;
    while (index < customerCount && customers[index].account_number != account_number) {
        index++;
    }
    
    if (index == customerCount) {
        cout << "Account not found" << endl;
        return;
    }
    
    Customer& client = customers[index];
    cout << "Welcome " << client.account_holder_name << endl;
    int choice;
    
    do {
        cout << "\nPlease select an option: " << endl;
        cout << "1. View Loans" << endl;
        cout << "2. Submit Loan Application" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "6. Undo Last Transaction" << endl;
        cout << "7. Exit" << endl;
        cout << "Choice: ";
        choice = getValidInteger("Choice: ", 1, 7);
        switch (choice)
        {
            case 1:
                ViewLoans(client);
                break;
            case 2:
            {
                Loan loan;
                // Validate Loan ID (must be unique)
                loan.loanID = getValidLoanID(globalLoanApplications, customers, customerCount);
                // Validate Loan Type
                loan.loanType = getValidLoanType();
                // Validate Principal Amount
                loan.principalAmount = getValidDouble("Enter Principal Amount (TND): ", 100.0);
                // Validate Interest Rate
                loan.interestRate = getValidInterestRate();
                // Validate Start Date
                loan.startDate = getValidDate("Enter Start Date (DD/MM/YYYY): ");
                // Validate End Date
                loan.endDate = getValidDate("Enter End Date (DD/MM/YYYY): ");
                loan.account_number = client.account_number;
                loan.amountPaid = 0.0;
                loan.remainingBalance = loan.principalAmount;
                loan.status = "pending";
                SubmitLoanApplication(loan, globalLoanApplications);
            }
            break;
            case 3:
                Withdraw(client);
                break;
            case 4:
                Deposit(client);
                break;
            case 5:
                ViewTransactionHistory(*client.transactions);
                break;
            case 6:
                UndoLastTransaction(client);
                break;
            case 7:
                cout << "Exiting customer interface." << endl;
                BackupData(customers, customerCount, nullptr, 0);
                mainInterface();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 7);
}
int findCustomerByAccountNumber(Customer customers[], int customerCount, string account_number){
    for (int i = 0; i < customerCount; i++){
        if (customers[i].account_number == account_number){
            return i;
        }
    }
    return -1;
}
void loginEmployeeInterface(Employee employees[],int empcount,Customer customers[],int customerCount){
    int employeeID;
    cout <<"Please enter your Employee ID: ";
    cin >> employeeID;
    cin.ignore(10000, '\n');
    int index=0;
    while (index<empcount && employees[index].employeeID!=employeeID){
        index++;
    }
    if (index==empcount){
        cout <<"Employee not found";
        return;
    }
    else{
        Employee& emp=employees[index];
        cout <<"Welcome " << emp.name << " " << emp.lastName << endl;
        if (emp.BankBranch==1){
            cout <<"Head Office Manager:" << endl;
            int choice;
            do{
                pauseScreen();
                cout <<"Please select an option: " << endl;
                cout <<"1. Add Employee" << endl;
                cout <<"2. Remove Employee" << endl;
                cout <<"3. Update Employee" << endl;
                cout <<"4. Display Employees Alphabetically" << endl;
                cout <<"5. Display Employees by Bank Branch" << endl;
                cout <<"6. Earliest Hire Date" << endl;
                cout <<"7. Latest Hire Date" << endl;
                cout <<"8. Display Statistics" << endl;
                cout <<"9. Exit" << endl;
                choice = getValidInteger("Choice: ", 1, 9);
                switch (choice)
                {
                    case 1:
                    {
                        Employee newEmp;
                        newEmp.employeeID = getValidEmployeeID(employees, empcount, true);
                        newEmp.name = getValidString("Enter Name: ");
                        newEmp.lastName = getValidString("Enter Last Name: ");
                        newEmp.adress = getValidString("Enter Address: ");
                        newEmp.salary = getValidDouble("Enter Salary (TND): ", 0.01);
                        newEmp.hireDate = getValidDate("Enter Hire Date (DD/MM/YYYY): ");
                        newEmp.BankBranch = getValidBankBranch();
                        addEmployee(newEmp, employees, empcount);
                    }
                    break;
                    case 2:
                    {
                        int empID;
                        cout <<"Enter Employee ID to remove: ";
                        cin >> empID;
                        cin.ignore(10000, '\n');
                        removeEmployee(employees,empcount,empID);
                    }
                    break;
                    case 3:
                    {
                        int empID;
                        cout << "Enter Employee ID to update: ";
                        cin >> empID;
                        cin.ignore(10000, '\n');
                        
                        // Check if employee exists
                        int index = -1;
                        for (int i = 0; i < empcount; i++) {
                            if (employees[i].employeeID == empID) {
                                index = i;
                                break;
                            }
                        }
                        
                        if (index == -1) {
                            cout << "✗ Employee ID " << empID << " not found!" << endl;
                            break;
                        }
    
                        // Display current employee info
                        cout << "\n===== CURRENT EMPLOYEE INFO =====" << endl;
                        cout << "Name: " << employees[index].name << " " << employees[index].lastName << endl;
                        cout << "Address: " << employees[index].adress << endl;
                        cout << "Salary: " << employees[index].salary << " TND" << endl;
                        cout << "Hire Date: " << employees[index].hireDate << endl;
                        cout << "Bank Branch: " << employees[index].BankBranch << endl;
                        cout << "================================\n" << endl;
                        
                        Employee updatedEmp;
                        updatedEmp.employeeID = empID;
                        
                        // Use validation functions
                        updatedEmp.name = getValidString("Enter New Name: ");
                        updatedEmp.lastName = getValidString("Enter New Last Name: ");
                        updatedEmp.adress = getValidString("Enter New Address: ");
                        updatedEmp.salary = getValidDouble("Enter New Salary (TND): ", 0.01);
                        updatedEmp.hireDate = getValidDate("Enter New Hire Date (DD/MM/YYYY): ");
                        updatedEmp.BankBranch = getValidBankBranch();
                        
                        updateEmployee(employees, empcount, empID, updatedEmp);
}
                    break;
                    case 4:
                    displayEmployeeAlpha(employees,empcount);
                    break;
                    case 5:
                    displayEmployeeByBB(employees,empcount);
                    break;
                    case 6:
                    earliestHireDate(employees,empcount);
                    break;
                    case 7:
                    latestHireDate(employees,empcount);
                    break;
                    case 8:
                    cout <<"Displaying statistics." << endl;
                    displayStatistics(employees,empcount,customers,customerCount);
                    break;
                    case 9:
                    cout <<"Exiting employee interface." << endl;
                    BackupData(customers,customerCount,employees,empcount);
                    mainInterface();
                    break;
                    default:
                    cout <<"Invalid choice. Please try again." << endl;
                    break;
                }
            }while (choice!=8);
        }
        else{
            cout <<"Employee Space:" << endl;
            int choice;
            do{
                pauseScreen();
                displayHeader("Employee Menu");
                cout<<"1. Add Customer Account"<<endl;
                cout <<"2. Display List of Accounts"<<endl;
                cout<<"3. Change Status of an Account"<<endl;
                cout<<"4. Delete All Closed Accounts"<<endl;
                cout<<"5. Display The Loans of a Customer"<<endl;
                cout<<"6. Change The Status of a Loan"<<endl;
                cout<<"7. Delete completed Loans from Records"<<endl;
                cout<<"8. Manage Loans Applications"<<endl;
                cout<<"9. Manage Transactions"<<endl;
                cout<<"10. Display Statistics"<<endl;
                cout<<"11. Exit"<<endl;
                choice = getValidInteger("Choice: ", 1, 11);
                int loanID;
                string CustomerID;
                string newStatus;
                Customer ClosedAccounts[100];
                int closedaccnum;
                switch (choice)
                {
                    case 1:
                    {
                        Customer newCust;
                        // Validate Account Number (must be unique and numeric)
                        newCust.account_number = getValidAccountNumber(customers, customerCount, true);
                        // Validate Account Type
                        newCust.account_type = getValidString("Enter Account Type (e.g., Savings, Checking): ");
                        // Validate IBAN
                        newCust.IBAN = getValidIBAN();
                        // Validate Branch Code
                        newCust.branch_code = getValidString("Enter Branch Code: ");
                        // Validate Account Holder Name
                        newCust.account_holder_name = getValidString("Enter Account Holder Name: ");
                        // Validate Opening Date
                        newCust.opening_date = getValidDate("Enter Opening Date (DD/MM/YYYY): ");
                        // Validate Status
                        newCust.status = getValidStatus();
                        // Validate Initial Balance
                        newCust.balance = getValidDouble("Enter Initial Balance (TND): ", 0.0);
                        addCustomer(newCust, customers, customerCount);
                    }
                    break;
                    case 2:
                    displayCustomers(customers,customerCount);
                    break;
                    case 3:{
                        // Get account number
                        string custId = getValidString("Enter Customer Account Number: ");
                        
                        // Check if customer exists
                        int index = findCustomerByAccountNumber(customers, customerCount, custId);
                        if (index == -1) {
                            cout << "✗ Customer with account number '" << custId << "' not found!" << endl;
                            break;
                        }
                        
                        // Display current status
                        cout << "\nCustomer: " << customers[index].account_holder_name << endl;
                        cout << "Current Status: " << customers[index].status << endl;
                        cout << "Current Balance: " << customers[index].balance << " TND" << endl;
                        
                        // Get new status with validation
                        string newstat = getValidStatus();
                        
                        // Confirm if changing to closed
                        if (newstat == "closed" && customers[index].status != "closed") {
                            cout << "\n⚠ WARNING: Closing this account will:" << endl;
                            cout << "  - Set balance to 0 TND" << endl;
                            cout << "  - Mark account as permanently closed" << endl;
                            cout << "\nAre you sure you want to continue?" << endl;
                            cout << "1. Yes" << endl;
                            cout << "2. No" << endl;
                            
                            int confirm = getValidInteger("Choice: ", 1, 2);
                            if (confirm != 1) {
                                cout << "✓ Operation cancelled. Status unchanged." << endl;
                                break;
                            }
                        }
    
                        changeStatusofaccount(customers, customerCount, custId, newstat);
                    }
                    break;
                    case 4:{
                    DeleteClosedAccounts(customers,customerCount,ClosedAccounts,closedaccnum);
                    }
                    break;
                    case 5:
                    displayloansbycustomer(customers,customerCount);
                    break;
                    case 6:
                    {
                        cout << "\n===== CHANGE LOAN STATUS =====" << endl;
                        
                        // Get and validate customer account
                        string CustomerID = getValidString("Enter Customer Account Number: ");
                        int custIndex = findCustomerByAccountNumber(customers, customerCount, CustomerID);
                        
                        if (custIndex == -1) {
                            cout << "✗ Customer not found!" << endl;
                            break;
                        }
                        
                        // Check if customer has loans
                        if (!customers[custIndex].loans || customers[custIndex].loans->size == 0) {
                            cout << "✗ This customer has no loans!" << endl;
                            break;
                        }
                        
                        // Display customer loans
                        cout << "\nLoans for " << customers[custIndex].account_holder_name << ":" << endl;
                        LoanNode* current = customers[custIndex].loans->head;
                        while (current) {
                            cout << "  Loan ID: " << current->data.loanID 
                                << " | Type: " << current->data.loanType 
                                << " | Status: " << current->data.status << endl;
                            current = current->next;
                        }
                        
                        // Get loan ID
                        int loanID = getValidInteger("\nEnter Loan ID to modify: ", 1, 999999);
                        
                        // Find the loan
                        Loan* loan = findLoan(*customers[custIndex].loans, loanID);
                        if (!loan) {
                            cout << "✗ Loan ID " << loanID << " not found!" << endl;
                            break;
                        }
                        
                        cout << "\nCurrent status: " << loan->status << endl;
                        cout << "Choose new status:" << endl;
                        cout << "1. active" << endl;
                        cout << "2. completed" << endl;
                        cout << "3. overdue" << endl;
                        cout << "4. closed" << endl;
                        
                        int statusChoice = getValidInteger("Choice: ", 1, 4);
                        string newStatus;
                        
                        switch (statusChoice) {
                            case 1: newStatus = "active"; break;
                            case 2: newStatus = "completed"; break;
                            case 3: newStatus = "overdue"; break;
                            case 4: newStatus = "closed"; break;
                        }
                        
                        changeLoanStatus(customers[custIndex].loans, loanID, newStatus);
                    }
                    break;
                    case 7:
                    {
                    CompletedLoansList* completed_loans = loadCompletedLoans("../Data/CompletedLoans.txt");
                    deleteloan(completed_loans,customers,customerCount);
                    bakcupcompletedloans(completed_loans);
                    break;
                    }
                    // In loginEmployeeInterface, employee space section:
                case 8:
                    {
                        Manageloans(globalLoanApplications, customers, customerCount);  // Use global
                        break;
                    }
                case 9:
                {
                    EndTransactionList* EndTransactions = ManageTransactions(customers, customerCount);
                    cout << "All transactions have been finalized for the day." << endl;
                    break;
                }
                case 10:
                    cout << "Displaying statistics." << endl;
                    displayStatistics(employees, empcount, customers, customerCount);
                    break;
                case 11:
                    cout << "Exiting employee interface." << endl;
                    BackupData(customers, customerCount, employees, empcount);
                    mainInterface();
                    break;
                default:{
                        cout <<"Invalide Choice";
                        break;
                    }
                    }
        }while (choice!=11);
    }
}
}

// In mainInterface(), before the menu:
bool validateCustomerData(const Customer& cust) {
    if (cust.account_number.empty()) return false;
    if (cust.account_holder_name.empty()) return false;
    if (cust.balance < 0) return false;
    if (cust.status != "active" && cust.status != "inactive" && cust.status != "closed") return false;
    return true;
}
void mainInterface(){
    LoanList* globalLoanApplications = loadLoanApplications();
    ifstream file("../Data/Customers.txt");
    if (!file) {
        cout << "✗ ERROR: Could not open ../Data/Customers.txt" << endl;
        cout << "Please ensure:" << endl;
        cout << "  1. The Data folder exists" << endl;
        cout << "  2. The Customers.txt file exists" << endl;
        cout << "  3. You're running from the correct directory" << endl;
        return;
    }
    Customer customers[100];
    int customerCount = 0;
    string line;
    while (getline(file, line) && customerCount < 100) {
        Customer cust=Split_line_to_customer(line);
        if (!validateCustomerData(cust)) {
        cout << "⚠ Warning: Invalid customer data on line " << (customerCount + 1) << ", skipping..." << endl;
        continue;
        }
        cust.loans = getCustomerLoans(cust.account_number);
        cust.transactions = getCustomerTransactions(cust.account_number);
        customers[customerCount] = cust;
        customerCount++;
    }
    file.close();
    ifstream empfile("../Data/Employees.txt");
    if (!empfile) {
        cout << "✗ ERROR: Could not open ../Data/Employees.txt" << endl;
        cout << "Please ensure:" << endl;
        cout << "  1. The Data folder exists" << endl;
        cout << "  2. The Customers.txt file exists" << endl;
        cout << "  3. You're running from the correct directory" << endl;
    }
    Employee employees[100];
    int empcount=0;
    string empline;
    while (getline(empfile, empline) && empcount < 100) {
        Employee emp;
        string linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.employeeID = stoi(linepart);
        linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.name = linepart;
        linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.lastName = linepart;
        linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.adress = linepart;
        linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.salary = stod(linepart);
        linepart = empline.substr(0, empline.find(','));
        empline.erase(0, empline.find(',') + 1);
        emp.hireDate = linepart;
        emp.BankBranch = stoi(empline);
        employees[empcount] = emp;
        empcount++;
    }
    empfile.close();
    cout << "✓ Loaded " << customerCount << " customer(s)" << endl;
    cout << "✓ Loaded " << empcount << " employee(s)" << endl;
    if (!globalLoanApplications) {
    globalLoanApplications = createLoanList();
    }
    int choice;
    cout <<"         Welcome to HideBank Management System         " << endl;
    cout <<"--------------------------------------------------------" << endl;
    cout <<"Please select your role: " << endl;
    cout <<"1. Customer" << endl;
    cout <<"2. Employee" << endl;
    cout <<"3. Exit" << endl;
    cout <<"--------------------------------------------------------" << endl;
    choice = getValidInteger("Choice: ", 1, 3);
    switch (choice)
    {
    case 1:
        loginCustomerInterface(customers,customerCount);
        break;
    
    case 2:
        loginEmployeeInterface(employees,empcount,customers,customerCount);
        break;
    case 3:
        BackupData(customers,customerCount,employees,empcount);
        for (int i = 0; i < customerCount; i++) {
            destroyLoanList(customers[i].loans);
            destroyTransactionStack(customers[i].transactions);
        }
        cout << "Exiting the system. Goodbye!" << endl;
        break;
    }
    if (choice != 3) {
    cout << "\nReturning to main menu..." << endl;
    mainInterface();  // Return to main menu
}

}
void displayStatistics(Employee employees[], int empcount,Customer customers[], int customerCount){
    cout <<"Statistics Menu:" << endl;
    int choice;
    do{
        cout<<"1. Total Number of Loans"<<endl;
        cout<<"2. Number of Loans by Type"<<endl;
        cout<<"3. Number of Loans by Status"<<endl;
        cout<< "4. Active Loans in Date Range" << endl;
        cout<< "5. Customer with Highest Number of Loans" << endl;
        cout<< "6. Highest Balance" << endl;
        cout<<"7. Lowest Balance"<<endl;
        cout<<"8. Number of Employees"<<endl;
        cout<<"9. Number of Employees by Bank Branch"<<endl;
        cout<<"10. Exit Statistics Menu"<<endl;
        choice = getValidInteger("Choice: ", 1, 10);
        switch (choice){
            case 1:
            totalnumofloans(customers,customerCount);
            break;
            case 2:
            numofloansbytype(customers,customerCount);
            break;
            case 3:
            numofloansbystatus(customers,customerCount);
            break;
            case 4:
            activeLoansInDateRange(customers,customerCount);
            break;
            case 5:
            customerWithMostLoans(customers,customerCount);
            break;
            case 6:
            highestloanamount(customers,customerCount);
            break;
            case 7:
            lowestbalance(customers,customerCount);
            break;
            case 8:
            NumberofEmployees(employees,empcount);
            break;
            case 9:
            {
                int branches;
                cout <<"Enter number of bank branches: ";
                cin >> branches;
                cin.ignore(10000, '\n');
                NumberofEmployeesbyBB(employees,empcount,branches);
            }
            break;
            case 10:
            cout << "Exiting Statistics Menu." << endl;
            break;
        }
    }while (choice!=10);
    return;
}

// Minimal implementations for completed loans helpers (prevent linker errors)
CompletedLoansList* loadCompletedLoans(string path){
    CompletedLoansList* list = createCompletedLoanList();
    ifstream clfile (path);
    string line;
    string linepart;
    int pos=0;
    while (getline(clfile,line)){
        Loan completedloan;
        linepart = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        completedloan.account_number = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.loanID = stoi(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.loanType = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.principalAmount = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.interestRate = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.amountPaid = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.remainingBalance = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.startDate = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            completedloan.endDate = linepart;
            completedloan.status = line;
            if (!insertIntoCompletedLoans(list,completedloan,pos)){
                cout <<"Insertion failed for loan num"<<pos+1<<"please check your data file";
            }
    }
    return list;
}

void bakcupcompletedloans(CompletedLoansList* list){
    CompletedLoansListNode* current=list->head;
    if (list->size>0){
        ofstream clfile ("../Data/CompletedLoans.txt");
        while (current!=nullptr){
            clfile << current->data.account_number << "," << current->data.loanID << "," << current->data.loanType << "," << current->data.principalAmount << "," << current->data.interestRate << "," << current->data.amountPaid << "," << current->data.remainingBalance << "," << current->data.startDate << "," << current->data.endDate << "," << current->data.status << endl;
            current = current->next;
        }
    }
    return;
}
int main()
{
    mainInterface();
    return 0;
}