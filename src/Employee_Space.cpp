#include "Employee.h"
#include "Customer.h"
#include "iostream"
using namespace std;
void SortByAlpha(Employee employees[], int empcout);
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
int changeStatusofaccount(string s, Customer &c)
{
    c.status = s;
    if (s == "closed")
    {
        c.balance = 0;
    }
    else
    {
        cout << "Account status updated to " << s << endl;
    }
    return 0;
}
int deleteClosedAccounts(Customer customers[], int &empcount, Customer archived[], int &archcount)
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
int Main()
{
    return 0;
}
