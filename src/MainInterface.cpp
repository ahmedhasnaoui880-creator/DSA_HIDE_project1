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
LoanList* globalLoanApplications = nullptr;
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
    // DON'T open files yet - first check if we have data
    
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
        cin >> choice;
        cin.ignore(10000, '\n');  // Moved here - AFTER menu display

        switch (choice)
        {
            case 1:
                ViewLoans(client);
                break;
            case 2:
            {
                Loan loan;
                cout << "Enter Loan ID: ";
                cin >> loan.loanID;
                cin.ignore(10000, '\n');
                cout << "Enter Loan Type (car/home/student/business): ";
                cin >> loan.loanType;
                cin.ignore(10000, '\n');
                cout << "Enter Principal Amount: ";
                cin >> loan.principalAmount;
                cin.ignore(10000, '\n');
                cout << "Enter Interest Rate: ";
                cin >> loan.interestRate;
                cin.ignore(10000, '\n');
                cout << "Enter Start Date (DD/MM/YYYY): ";
                cin >> loan.startDate;
                cin.ignore(10000, '\n');
                cout << "Enter End Date (DD/MM/YYYY): ";
                cin >> loan.endDate;
                cin.ignore(10000, '\n');
                loan.account_number = client.account_number;
                loan.amountPaid = 0.0;
                loan.remainingBalance = loan.principalAmount;
                loan.status = "pending";
                SubmitLoanApplication(loan, globalLoanApplications);  // Use global
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
                cout <<"Please select an option: " << endl;
                cout <<"1. Add Employee" << endl;
                cout <<"2. Remove Employee" << endl;
                cout <<"3. Update Employee" << endl;
                cout <<"4. Display Employees Alphabetically" << endl;
                cout <<"5. Display Employees by Bank Branch" << endl;
                cout <<"6. Earliest Hire Date" << endl;
                cout <<"7. Display Statistics" << endl;
                cout <<"8. Exit" << endl;
                cin >> choice;
                cin.ignore(10000, '\n');
                switch (choice)
                {
                    case 1:
                    {
                        Employee newEmp;
                        cout <<"Enter Employee ID: ";
                        cin >> newEmp.employeeID;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Name: ";
                        cin >> newEmp.name;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Last Name: ";
                        cin >> newEmp.lastName;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Address: ";
                        cin >> newEmp.adress;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Salary: ";
                        cin >> newEmp.salary;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Hire Date: ";
                        cin >> newEmp.hireDate;
                        cin.ignore(10000, '\n');
                        cout <<"Enter Bank Branch: ";
                        cin >> newEmp.BankBranch;
                        cin.ignore(10000, '\n');
                        addEmployee(newEmp,employees,empcount);
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
                        cout <<"Enter Employee ID to update: ";
                        cin >> empID;
                        cin.ignore(10000, '\n');
                        Employee updatedEmp;
                        cout <<"Enter New Name: ";
                        cin >> updatedEmp.name;
                        cin.ignore(10000, '\n');
                        cout <<"Enter New Last Name: ";
                        cin >> updatedEmp.lastName;
                        cin.ignore(10000, '\n');
                        cout <<"Enter New Address: ";
                        cin >> updatedEmp.adress;
                        cin.ignore(10000, '\n');
                        cout <<"Enter New Salary: ";
                        cin >> updatedEmp.salary;
                        cin.ignore(10000, '\n');
                        cout <<"Enter New Hire Date: ";
                        cin >> updatedEmp.hireDate;
                        cin.ignore(10000, '\n');
                        cout <<"Enter New Bank Branch: ";
                        cin >> updatedEmp.BankBranch;
                        cin.ignore(10000, '\n');
                        updatedEmp.employeeID=empID;
                        updateEmployee(employees,empcount,empID,updatedEmp);
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
                    cout <<"Displaying statistics." << endl;
                    displayStatistics(employees,empcount,customers,customerCount);
                    break;
                    case 8:
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
                cin >> choice;
                cin.ignore(10000, '\n');
                int loanID;
                string CustomerID;
                string newStatus;
                Customer newCust;
                Customer ClosedAccounts[100];
                int closedaccnum;
                switch (choice)
                {
                    case 1:
                    addCustomer(newCust, customers, customerCount);
                    break;
                    case 2:
                    displayCustomers(customers,customerCount);
                    break;
                    case 3:{
                        cout<<"Enter the customer's Id";
                        string custId;
                        cin >> custId;
                        cin.ignore(10000, '\n');
                        cout <<"Enter The new Status";
                        string newstat;
                        cin >> newstat;
                        cin.ignore(10000, '\n');
                        changeStatusofaccount(customers,customerCount,custId,newstat);
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
                    cout<<"Enter Loan ID: ";
                    cin>>loanID;
                    cin.ignore(10000, '\n');
                    cout<<"Enter Customer Account Number: ";
                    cin>>CustomerID;
                    cin.ignore(10000, '\n');
                    int custIndex=findCustomerByAccountNumber(customers,customerCount,CustomerID);
                    LoanList* loans=customers[custIndex].loans;
                    cout<<"Enter New Status: ";
                    cin>>newStatus;
                    cin.ignore(10000, '\n');
                    changeLoanStatus(loans, loanID, newStatus);
                    break;
                    }
                    case 7:
                    {
                    CompletedLoansList* completed_loans = loadCompletedLoans("../Data/CompletedLoans.txt");
                    deleteloan(completed_loans);
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
void mainInterface(){
    ifstream file("../Data/Customers.txt");
    if (!file) {
        cout << "Error opening file." << endl;
        return ;
    }
    Customer customers[100];
    int customerCount = 0;
    string line;
    while (getline(file, line) && customerCount < 100) {
        Customer cust=Split_line_to_customer(line);
        cust.loans = getCustomerLoans(cust.account_number);
        cust.transactions = getCustomerTransactions(cust.account_number);
        customers[customerCount] = cust;
        customerCount++;
    }
    file.close();
    ifstream empfile("../Data/Employees.txt");
    if (!empfile) {
        cout << "Error opening employee file." << endl;
        return ;
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
    cin >> choice;
    cin.ignore(10000, '\n');
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
        cout << "Exiting the system. Goodbye!" << endl;
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

}
void displayStatistics(Employee employees[], int empcount,Customer customers[], int customerCount){
    cout <<"Statistics Menu:" << endl;
    int choice;
    do{

        cout<<"1. Total Number of Loans"<<endl;
        cout<<"2. Number of Loans by Type"<<endl;
        cout<<"3. Number of Loans by Status"<<endl;
        cout<<"4. Highest Loan Amount"<<endl;
        cout<<"5. Highest Balance"<<endl;
        cout<<"6. Lowest Balance"<<endl;
        cout<<"7. Number of Employees"<<endl;
        cout<<"8. Number of Employees by Bank Branch"<<endl;
        cout<<"9. Exit Statistics Menu"<<endl;
        cin >> choice;
        cin.ignore(10000, '\n');
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
            highestloanamount(customers,customerCount);
            break;
            case 5:
            highestbalance(customers,customerCount);
            break;
            case 6:
            lowestbalance(customers,customerCount);
            break;
            case 7:
            NumberofEmployees(employees,empcount);
            break;
            case 8:
            {
                int branches;
                cout <<"Enter number of bank branches: ";
                cin >> branches;
                cin.ignore(10000, '\n');
                NumberofEmployeesbyBB(employees,empcount,branches);
            }
            break;
            case 9:
            cout << "Exiting Statistics Menu." << endl;
            break;
            default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }while (choice!=9);
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
            if (!insertIntoConpletedLoans(list,completedloan,pos)){
                cout <<"Insertion failed for loan num"<<pos+1<<"please check your data file";
            }
    }
    return list;
}

void bakcupcompletedloans(CompletedLoansList* list){
    CompletedLoansListNode* current=list->head;
    if (list->size>0){
        ofstream clfile ("CompletedLoans.txt");
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