#include "Employee.h"
#include "Customer.h"
#include "LoanList.h"
#include "CompletedLoansListMeth.h"
#include <iostream>
using namespace std;

// Forward declarations for functions implemented later in this file
int displayloansbycustomer(const Customer &c);
int changeLoanStatus(Loan &l, string s);

// Implementations required by the header (wrappers / simple helpers)
void SortByAlpha(Employee employees[], int empcount);
void SortByBB(Employee employees[], int empcount);
int addEmployee(Employee emp, Employee employees[], int &empcount)
{
    employees[empcount] = emp;
    empcount++;
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
        cout << "Employee not found";
        return 1;
    }
    else
    {
        for (int i = index; i < empcount - 1; i++)
        {
            employees[i] = employees[i + 1];
        }
        empcount--;
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
        cout << "Employee not found";
        return 1;
    }
    else
    {
        employees[index] = updatedEmp;
    }
    return 0;
}
int displayEmployeeAlpha(Employee employees[], int empcount)
{
    SortByAlpha(employees, empcount);
    for (int i = 0; i < empcount; i++)
    {
        cout << "Employee ID: " << employees[i].employeeID << endl;
        cout << "Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout << "Address: " << employees[i].adress << endl;
        cout << "Salary: " << employees[i].salary << endl;
        cout << "Hire Date: " << employees[i].hireDate << endl;
        cout << "Bank Branch: " << employees[i].BankBranch << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}
int displayEmployeeByBB(Employee employees[], int empcount)
{
    SortByBB(employees, empcount);
    for (int i = 0; i < empcount; i++)
    {
        cout << "Employee ID: " << employees[i].employeeID << endl;
        cout << "Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout << "Address: " << employees[i].adress << endl;
        cout << "Salary: " << employees[i].salary << endl;
        cout << "Hire Date: " << employees[i].hireDate << endl;
        cout << "Bank Branch: " << employees[i].BankBranch << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}

// Simple implementations for sorting helpers declared in the header
void SortByAlpha(Employee employees[], int empcount)
{
    bool test=true;
    do{
        for (int i=0;i<empcount-1;i++){
            if (employees[i].name>employees[i].name){
                Employee aux=employees[i];
                employees[i]=employees[i+1];
                employees[i+1]=aux;
                test=false;
            }
            else if (employees[i].name==employees[i].name){
                if (employees[i].lastName>employees[i].lastName){
                    Employee aux=employees[i];
                employees[i]=employees[i+1];
                employees[i+1]=aux;
                test=false;
                }
            }
        }
    }while (test==false);
    
    }

void SortByBB(Employee employees[], int empcount)
{
    bool test=true;
    do{
        for (int i=0;i<empcount-1;i++){
            if (employees[i].BankBranch>employees[i].BankBranch){
                Employee aux=employees[i];
                employees[i]=employees[i+1];
                employees[i+1]=aux;
                test=false;
            }
            }
        }while (test==false);
    }

// Wrapper functions to match signatures declared in the header file
int findcustomerbyID(Customer custoemrs[],int custcount,string custID){
    for (int i=0;i<custcount;i++){
        if (custoemrs[i].account_number==custID){
            return i;
        }
    }
    return -1;
}
int changeStatusofaccount(Customer customers[], int custmcount,string custID,string newStat)
{
    int index=findcustomerbyID(customers,custmcount,custID);
    if (index==(-1)){
        cout << "Customer doesn't exist!";
        return 1;
    }
    customers[index].status=newStat;
    if (newStat=="closed"){
        customers[index].balance=0;
    }
    return 0;
}


int displayloansbycustomer(Customer customers[], int custmcount)
{
    if (custmcount == 0) return 0;
    for (int i = 0; i < custmcount; ++i) {
        // call the existing per-customer function
        displayloansbycustomer(customers[i]);
    }
    return 0;
}

int changeLoanStatus(LoanList* loans, int loanID, string newStatus)
{
    if (!loans) return 1;
    LoanNode* cur = loans->head;
    while (cur) {
        if (cur->data.loanID == loanID) {
            // use existing helper that updates a Loan reference
            changeLoanStatus(cur->data, newStatus);
            return 0;
        }
        cur = cur->next;
    }
    return 1;
}

int deleteloan(CompletedLoansList* /*completed_loans*/)
{
    // Placeholder wrapper: provide a minimal no-op wrapper to satisfy linker.
    return 0;
}
int earliestHireDate(Employee employees[], int empcount)
{
    string maxdate = employees[0].hireDate;
    for (int i = 1; i < empcount; i++)
    {
    }
    return 0;
}
int latestHireDate(Employee employees[], int empcount)
{
    if (empcount == 0)
    {
        cout << "No employees available." << endl;
        return 1;
    };
    string latest = employees[0].hireDate;
    for (int i = 1; i < empcount; i++)
    {
        if (employees[i].hireDate > latest)
        {
            latest = employees[i].hireDate;
        }
    }
    cout << "The latest hire date is: " << latest << endl;
    return 0;
}
int addCustomer(Customer c, Customer customers[], int custmcount)
{
    if (custmcount >= 100)
    {
        cout << "No space available to add customer." << endl;
        return 1;
    }
    customers[custmcount] = c;
    custmcount++;
    return 0;
}
int displayCustomers(Customer customers[], int empcount)
{
    if (empcount == 0)
    {
        cout << "No customers available." << endl;
        return 1;
    }
    for (int i = 0; i < empcount; i++)
    {
        cout << "Account Number: " << customers[i].account_number << endl;
        cout << "Account Type: " << customers[i].account_type << endl;
        cout << "IBAN: " << customers[i].IBAN << endl;
        cout << "Branch Code: " << customers[i].branch_code << endl;
        cout << "Account Holder Name: " << customers[i].account_holder_name << endl;
        cout << "Opening Date: " << customers[i].opening_date << endl;
        cout << "Status: " << customers[i].status << endl;
        cout << "Balance: " << customers[i].balance << endl;
        cout << "------------------------" << endl;
    }
    return 0;
}
int DeleteClosedAccounts(Customer customers[], int &empcount, Customer archived[], int &archcount)
{
    int i = 0;
    while (i < empcount)
    {
        if (customers[i].status == "closed")
        {
            archived[archcount] = customers[i];
            archcount++;
            for (int j = i; j < empcount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            empcount--;
        }
        else
        {
            i++;
        }
    }
    return 0;
}
int displayloansbycustomer(const Customer &c)
{
    if (c.loans->size == 0)
    {
        cout << "No loans available for this customer." << endl;
    }
    else
    {
        cout << "Loans for customer " << c.account_holder_name << ":" << endl;
        LoanNode *current = c.loans->head;
        while (current != nullptr)
        {
            cout << "Loan ID: " << current->data.loanID << endl;
            cout << "Amount: " << current->data.principalAmount << endl;
            cout << "Type: " << current->data.loanType << endl;
            cout << "Status: " << current->data.status << endl;
            cout << "------------------------" << endl;
            current = current->next;
        }
    }
    return 0;
}
int changeLoanStatus(Loan &l, string s)
{
    l.status = s;
    if (l.status == "closed")
    {
        l.remainingBalance = 0;
        cout << "Loan status changed to closed and remaining balance set to 0." << endl;
    }
    else
    {
        cout << "Loan status updated to " << l.status << endl;
    }
    return 0;
}
int deleteloan(LoanNode *completed_loans, LoanNode *head)
{
    LoanNode *prev = nullptr;
    LoanNode *current = head;
    while (current != nullptr)
    {
        if (current->data.status == "completed")
        {
            LoanNode *archivedNode = new LoanNode{current->data, completed_loans};
            completed_loans = archivedNode;
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            LoanNode *temp = current;
            current = current->next;
            delete temp;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    return 0;
}
int Manageloans()
{
    return 0;
}
int ManageTransactions()
{
    return 0;
}
