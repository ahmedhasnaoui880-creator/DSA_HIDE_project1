#include "Employee.h"
#include "Customer.h"
#include "LoanMeth.h"
#include "CompletedLoansMeth.h"
#include "TransactionMeth.h"
#include "EndTransactionMeth.h"
#include "Input_Validation.h"
#include <iostream>
using namespace std;
// Forward declarations for functions implemented later in this file
int displayloan(const Customer &c);
int changeLoanStatus(Loan &l, string s);
// Implementations required by the header (wrappers / simple helpers)
void SortByAlpha(Employee employees[], int empcount);
void SortByBB(Employee employees[], int empcount);

int addEmployee(Employee emp, Employee employees[], int &empcount)
{
    if (empcount >= 100) {
        cout << "✗ Error: Maximum number of employees reached!" << endl;
        return 1;
    }
    employees[empcount] = emp;
    empcount++;
    cout << "✓ Employee added successfully!" << endl;
    return 0;
}

int removeEmployee(Employee employees[], int &empcount, int empID)
{
    int index = 0;
    while (index < empcount && employees[index].employeeID != empID)
    {
        index++;
    }
    if (index == empcount)
    {
        cout << "✗ Employee not found!" << endl;
        return 1;
    }
    else
    {
        for (int i = index; i < empcount - 1; i++)
        {
            employees[i] = employees[i + 1];
        }
        empcount--;
        cout << "✓ Employee removed successfully!" << endl;
    }
    return 0;
}

int updateEmployee(Employee employees[], int empcount, int empID, Employee updatedEmp)
{
    int index = 0;
    while (index < empcount && employees[index].employeeID != empID)
    {
        index++;
    }
    if (index == empcount)
    {
        cout << "✗ Employee not found!" << endl;
        return 1;
    }
    else
    {
        employees[index] = updatedEmp;
        cout << "✓ Employee information updated successfully!" << endl;
    }
    return 0;
}

int displayEmployeeAlpha(Employee employees[], int empcount)
{
    if (empcount == 0) {
        cout << "✗ No employees to display!" << endl;
        return 1;
    }
    
    SortByAlpha(employees, empcount);
    cout << "\n===== EMPLOYEES (Alphabetical Order) =====" << endl;
    for (int i = 0; i < empcount; i++)
    {
        cout << "\nEmployee #" << (i+1) << ":" << endl;
        cout << "  ID: " << employees[i].employeeID << endl;
        cout << "  Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout << "  Address: " << employees[i].adress << endl;
        cout << "  Salary: " << employees[i].salary << " TND" << endl;
        cout << "  Hire Date: " << employees[i].hireDate << endl;
        cout << "  Bank Branch: " << employees[i].BankBranch << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}

int displayEmployeeByBB(Employee employees[], int empcount)
{
    if (empcount == 0) {
        cout << "✗ No employees to display!" << endl;
        return 1;
    }
    
    SortByBB(employees, empcount);
    cout << "\n===== EMPLOYEES (By Bank Branch) =====" << endl;
    for (int i = 0; i < empcount; i++)
    {
        cout << "\nEmployee #" << (i+1) << ":" << endl;
        cout << "  ID: " << employees[i].employeeID << endl;
        cout << "  Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout << "  Address: " << employees[i].adress << endl;
        cout << "  Salary: " << employees[i].salary << " TND" << endl;
        cout << "  Hire Date: " << employees[i].hireDate << endl;
        cout << "  Bank Branch: " << employees[i].BankBranch << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}

// Simple implementations for sorting helpers declared in the header
void SortByAlpha(Employee employees[], int empcount)
{
    for (int i = 0; i < empcount - 1; i++) {
        for (int j = i + 1; j < empcount; j++) {
            bool shouldSwap = false;
            
            if (employees[i].lastName > employees[j].lastName) {
                shouldSwap = true;
            } else if (employees[i].lastName == employees[j].lastName && 
                       employees[i].name > employees[j].name) {
                shouldSwap = true;
            }
            
            if (shouldSwap) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}

void SortByBB(Employee employees[], int empcount)
{
    for (int i = 0; i < empcount - 1; i++) {
        for (int j = i + 1; j < empcount; j++) {
            if (employees[i].BankBranch > employees[j].BankBranch) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}
int findcustomerbyID(Customer customers[], int custcount, string custID){
    for (int i = 0; i < custcount; i++){
        if (customers[i].account_number == custID){
            return i;
        }
    }
    return -1;
}

int changeStatusofaccount(Customer customers[], int custmcount, string custID, string newStat)
{
    int index = findcustomerbyID(customers, custmcount, custID);
    if (index == (-1)){
        cout << "✗ Customer doesn't exist!" << endl;
        return 1;
    }
    customers[index].status = newStat;
    if (newStat == "closed"){
        customers[index].balance = 0;
    }
    cout << "✓ Account status changed to '" << newStat << "' successfully!" << endl;
    return 0;
}

int displayloansbycustomer(Customer customers[], int custmcount)
{
    if (custmcount == 0) {
        cout << "✗ No customers in the system!" << endl;
        return 0;
    }
    
    cout << "\n===== LOANS BY CUSTOMER =====" << endl;
    for (int i = 0; i < custmcount; ++i) {
        displayloan(customers[i]);
        cout << endl;
    }
    return 0;
}
bool CompareDates(string date1,string date2){
    string d1 = date1.substr(6,4) + date1.substr(3,2) + date1.substr(0,2);
    string d2 = date2.substr(6,4) + date2.substr(3,2) + date2.substr(0,2);
    return d1>d2;
}
int earliestHireDate(Employee employees[], int empcount)
{
    if (empcount == 0) {
        cout << "✗ No employees available." << endl;
        return 1;
    }
    
    string earliest = employees[0].hireDate;
    int earliestIndex = 0;
    
    for (int i = 1; i < empcount; i++) {
        if (CompareDates(earliest,employees[i].hireDate)) {
            earliest = employees[i].hireDate;
            earliestIndex = i;
        }
    }
    
    cout << "✓ Earliest hired employee: " << employees[earliestIndex].name 
         << " " << employees[earliestIndex].lastName 
         << " (Hired on: " << earliest << ")" << endl;
    return 0;
}

int latestHireDate(Employee employees[], int empcount)
{
    if (empcount == 0)
    {
        cout << "✗ No employees available." << endl;
        return 1;
    }
    
    string latest = employees[0].hireDate;
    int latestIndex = 0;
    
    for (int i = 1; i < empcount; i++)
    {
        if (CompareDates(employees[i].hireDate,latest))
        {
            latest = employees[i].hireDate;
            latestIndex = i;
        }
    }
    
    cout << "✓ Latest hired employee: " << employees[latestIndex].name 
         << " " << employees[latestIndex].lastName 
         << " (Hired on: " << latest << ")" << endl;
    return 0;
}

int addCustomer(Customer c, Customer customers[], int& custmcount)
{
    if (custmcount >= 100) {
        cout << "✗ Maximum number of customers reached!" << endl;
        return 1;
    }
    
    // Initialize customer's loans and transactions
    c.loans = createLoanList();
    c.transactions = createTransactionStack();
    
    customers[custmcount] = c;
    custmcount++;
    cout << "✓ Customer added successfully!" << endl;
    return 0;
}

int displayCustomers(Customer customers[], int empcount)
{
    if (empcount == 0)
    {
        cout << "✗ No customers available." << endl;
        return 1;
    }
    
    cout << "\n===== CUSTOMER ACCOUNTS =====" << endl;
    for (int i = 0; i < empcount; i++)
    {
        cout << "\nCustomer #" << (i+1) << ":" << endl;
        cout << "  Account Number: " << customers[i].account_number << endl;
        cout << "  Account Type: " << customers[i].account_type << endl;
        cout << "  IBAN: " << customers[i].IBAN << endl;
        cout << "  Branch Code: " << customers[i].branch_code << endl;
        cout << "  Account Holder: " << customers[i].account_holder_name << endl;
        cout << "  Opening Date: " << customers[i].opening_date << endl;
        cout << "  Status: " << customers[i].status << endl;
        cout << "  Balance: " << customers[i].balance << " TND" << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}

int DeleteClosedAccounts(Customer customers[], int &custcount, Customer archived[], int &archcount)
{
    int deletedCount = 0;
    int i = 0;
    
    while (i < custcount)
    {
        if (customers[i].status == "closed")
        {
            if (archcount >= 100) {
                cout << "✗ Archive is full! Cannot delete more accounts." << endl;
                break;
            }
            
            archived[archcount] = customers[i];
            archcount++;
            deletedCount++;
            
            for (int j = i; j < custcount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            custcount--;
        }
        else
        {
            i++;
        }
    }
    
    if (deletedCount > 0) {
        cout << "✓ Deleted " << deletedCount << " closed account(s)." << endl;
    } else {
        cout << "✓ No closed accounts found." << endl;
    }
    return 0;
}
int displayloan(const Customer &c)
{
    if (!c.loans || c.loans->size == 0)
    {
        cout << "  Customer " << c.account_holder_name << " has no loans." << endl;
    }
    else
    {
        cout << "  Loans for " << c.account_holder_name << " (Account: " << c.account_number << "):" << endl;
        LoanNode *current = c.loans->head;
        int loanNum = 1;
        while (current != nullptr)
        {
            cout << "    Loan #" << loanNum++ << ":" << endl;
            cout << "      ID: " << current->data.loanID << endl;
            cout << "      Type: " << current->data.loanType << endl;
            cout << "      Principal Amount: " << current->data.principalAmount << " TND" << endl;
            cout << "      Amount Paid: " << current->data.amountPaid << " TND" << endl;
            cout << "      Remaining Balance: " << current->data.remainingBalance << " TND" << endl;
            cout << "      Status: " << current->data.status << endl;
            current = current->next;
        }
    }
    return 0;
}

int changeLoanStatus(LoanList* l,int id, string s)
{
    LoanNode* n=l->head;
    while (n && n->data.loanID!=id){
        n=n->next;
    }
    if (!n){
        cout << "Loan doesn't exsist!";
        return -1;
    }
    n->data.status=s;
    if (n->data.status == "completed")
    {
        n->data.remainingBalance = 0;
        cout << "✓ Loan status changed to 'completed' and remaining balance set to 0." << endl;
    }
    else
    {
        cout << "✓ Loan status updated to '" << s << "'." << endl;
    }
    return 0;
}

int deleteloan(CompletedLoansList* completed_loans, Customer customers[], int custcount)
{
    int deletedCount = 0;
    
    for (int i = 0; i < custcount; i++) {
        LoanList* custloan = customers[i].loans;
        LoanNode *current = custloan->head;
        
        while (current != nullptr)
        {
            if (current->data.status == "completed")
            {
                int result = insertIntoCompletedLoans(completed_loans, current->data, completed_loans->size);
                if (result == 0) {  // 0 = success
                    deletedCount++;
                }
                
                int loanID = current->data.loanID;
                current = current->next;
                removeLoan(customers[i].loans, loanID);
            }
            else {
                current = current->next;
            }
        }
    }
    
    if (deletedCount > 0) {
        cout << "✓ Moved " << deletedCount << " completed loan(s) to archive." << endl;
    } else {
        cout << "✓ No completed loans found." << endl;
    }
    return 0;
}

int Manageloans(LoanList* appliedloans, Customer customers[], int custcount)
{
    if (appliedloans->size == 0){
        cout << "✗ No loan applications for the moment. Please check again later." << endl;
        return 1;
    }
    
    cout << "\n===== LOAN APPLICATION =====" << endl;
    cout << "Customer Account: " << appliedloans->head->data.account_number << endl;
    cout << "Loan ID: " << appliedloans->head->data.loanID << endl;
    cout << "Loan Type: " << appliedloans->head->data.loanType << endl;
    cout << "Principal Amount: " << appliedloans->head->data.principalAmount << " TND" << endl;
    cout << "Interest Rate: " << (appliedloans->head->data.interestRate * 100) << "%" << endl;
    cout << "Amount Paid in Advance: " << appliedloans->head->data.amountPaid << " TND" << endl;
    cout << "Remaining Balance: " << appliedloans->head->data.remainingBalance << " TND" << endl;
    cout << "Start Date: " << appliedloans->head->data.startDate << endl;
    cout << "End Date: " << appliedloans->head->data.endDate << endl;
    cout << "============================" << endl;
    
    cout << "\nWould you accept this application?" << endl;
    cout << "1. Yes (Accept)" << endl;
    cout << "0. No (Decline)" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(10000, '\n');
    do{

        if (choice == 1) {
            int index = findcustomerbyID(customers, custcount, appliedloans->head->data.account_number);
            if (index != -1) {
                appliedloans->head->data.status = "active";
                insertLoan(customers[index].loans, appliedloans->head->data, customers[index].loans->size + 1);
                removeLoan(appliedloans, appliedloans->head->data.loanID);
                cout << "✓ Loan application ACCEPTED and added to customer's account!" << endl;
            } else {
                cout << "✗ Error: Customer not found!" << endl;
            }
        } else if (choice == 0) {
            removeLoan(appliedloans, appliedloans->head->data.loanID);
            cout << "✓ Loan application DECLINED and removed." << endl;
        } else {
            cout << "✗ Invalid choice! No action taken." << endl;
        }
        
    }while (choice !=1 && choice !=0);
    if (appliedloans->size > 0) {
        cout << "\n" << appliedloans->size << " loan application(s) remaining." << endl;
        cout << "Would you like to process another loan request?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        
        int continueChoice = getValidInteger("Choice: ", 1, 2);
        
        if (continueChoice == 1) {
            return Manageloans(appliedloans, customers, custcount);
        }
    } else {
        cout << "✓ All loan applications have been processed!" << endl;
    }
    
    return 0;
}

EndTransactionList* ManageTransactions(Customer customers[], int custcount)
{
    cout << "\n===== DAILY TRANSACTION MANAGEMENT =====" << endl;
    cout << "This will archive all daily transactions." << endl;
    cout << "Is it the end of the day?" << endl;
    cout << "1. Yes - Finalize and archive transactions" << endl;
    cout << "2. No - Cancel operation" << endl;
    cout << "Choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(10000, '\n');
    
    if (choice != 1) {
        cout << "✓ Operation cancelled. Transactions remain active." << endl;
        return nullptr;
    }
    
    cout << "\n===== FINALIZING DAILY TRANSACTIONS =====" << endl;
    EndTransactionList* EndTransactions = createEndTransactionList();
    int totalTransactions = 0;
    
    for (int i = 0; i < custcount; i++) {
        int custTransCount = 0;
        
        // COPY transactions
        TransactionStackNode* current = customers[i].transactions->top;
        while (current != nullptr) {
            addEndTransaction(EndTransactions, current->data);
            custTransCount++;
            totalTransactions++;
            current = current->next;
        }
        if (custTransCount > 0) {
            cout << "  Customer " << customers[i].account_number 
                 << ": " << custTransCount << " transaction(s) archived." << endl;
        }
    }
    
    cout << "✓ Total of " << totalTransactions << " transaction(s) finalized for the day." << endl;
    cout << "✓ Customers can no longer undo these transactions." << endl;
    cout << "==========================================" << endl;
    
    return EndTransactions;
}
