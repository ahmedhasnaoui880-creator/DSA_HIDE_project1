#include "StatisticsMeth.h"
#include <iostream>
#include "Input_Validation.h"
using namespace std;

void totalnumofloans(const Customer arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].loans) {
            sum += arr[i].loans->size;
        }
    }
    cout << "Total number of loans: " << sum << endl;
}

void numofloansbytype(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    int carN = 0, homeN = 0, studentN = 0, businessN = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i].loans && !isEmpty(*arr[i].loans)) {
            LoanNode* n = arr[i].loans->head;
            while (n) {
                if (n->data.loanType == "car") carN++;
                else if (n->data.loanType == "home") homeN++;
                else if (n->data.loanType == "student") studentN++;
                else if (n->data.loanType == "business") businessN++;
                n = n->next;
            }
        }
    }
    
    cout << "Number of loans by type:" << endl;
    cout << "  Car loans: " << carN << endl;
    cout << "  Home loans: " << homeN << endl;
    cout << "  Student loans: " << studentN << endl;
    cout << "  Business loans: " << businessN << endl;
}

void numofloansbystatus(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    int activeN = 0, completedN = 0, overdueN = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i].loans && !isEmpty(*arr[i].loans)) {
            LoanNode* n = arr[i].loans->head;
            while (n) {
                if (n->data.status == "active") activeN++;
                else if (n->data.status == "completed") completedN++;
                else if (n->data.status == "overdue") overdueN++;
                n = n->next;
            }
        }
    }
    
    cout << "Number of loans by status:" << endl;
    cout << "  Active loans: " << activeN << endl;
    cout << "  Completed loans: " << completedN << endl;
    cout << "  Overdue loans: " << overdueN << endl;
}

void highestloanamount(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    double higher = 0.0;
    string customerName = "";
    
    for (int i = 0; i < size; i++) {
        if (arr[i].loans && !isEmpty(*arr[i].loans)) {
            LoanNode* n = arr[i].loans->head;
            while (n) {
                if (n->data.principalAmount > higher) {
                    higher = n->data.principalAmount;
                    customerName = arr[i].account_holder_name;
                }
                n = n->next;
            }
        }
    }
    
    if (higher > 0) {
        cout << "Highest loan amount: " << higher << " TND" << endl;
        cout << "Customer: " << customerName << endl;
    } else {
        cout << "No loans found" << endl;
    }
}

void highestbalance(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    double higher = arr[0].balance;
    int index = 0;
    
    for (int i = 1; i < size; i++) {
        if (arr[i].balance > higher) {
            higher = arr[i].balance;
            index = i;
        }
    }
    
    cout << "Highest balance: " << higher << " TND" << endl;
    cout << "Customer: " << arr[index].account_holder_name 
         << " (Account: " << arr[index].account_number << ")" << endl;
}

void lowestbalance(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    double lowest = arr[0].balance;
    int index = 0;
    
    for (int i = 1; i < size; i++) {
        if (arr[i].balance < lowest) {
            lowest = arr[i].balance;
            index = i;
        }
    }
    
    cout << "Lowest balance: " << lowest << " TND" << endl;
    cout << "Customer: " << arr[index].account_holder_name 
         << " (Account: " << arr[index].account_number << ")" << endl;
}

void NumberofEmployees(const Employee employeeArr[], int size) {
    cout << "Total number of employees: " << size << endl;
}

void NumberofEmployeesbyBB(const Employee arr[], int size) {
    if (size == 0) {
        cout << "There are no employees" << endl;
        return;
    }
    
    // Auto-detect unique bank branches
    int uniqueBranches[100];
    int branchCount = 0;
    
    // Find all unique branches
    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < branchCount; j++) {
            if (uniqueBranches[j] == arr[i].BankBranch) {
                found = true;
                break;
            }
        }
        if (!found) {
            uniqueBranches[branchCount] = arr[i].BankBranch;
            branchCount++;
        }
    }
    
    // Sort branches
    for (int i = 0; i < branchCount - 1; i++) {
        for (int j = i + 1; j < branchCount; j++) {
            if (uniqueBranches[i] > uniqueBranches[j]) {
                int temp = uniqueBranches[i];
                uniqueBranches[i] = uniqueBranches[j];
                uniqueBranches[j] = temp;
            }
        }
    }
    
    // Display counts
    cout << "\n===== EMPLOYEES BY BANK BRANCH =====" << endl;
    for (int i = 0; i < branchCount; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[j].BankBranch == uniqueBranches[i]) {
                count++;
            }
        }
        
        if (uniqueBranches[i] == 1) {
            cout << "  Head Office (1): " << count << " employee(s)" << endl;
        } else {
            cout << "  Branch " << uniqueBranches[i] << ": " << count << " employee(s)" << endl;
        }
    }
}
bool isDateInRange(string date, string start, string end) {
    // Convert DD/MM/YYYY to YYYYMMDD for proper comparison
    string d = date.substr(6,4) + date.substr(3,2) + date.substr(0,2);
    string s = start.substr(6,4) + start.substr(3,2) + start.substr(0,2);
    string e = end.substr(6,4) + end.substr(3,2) + end.substr(0,2);
    return (d >= s && d <= e);
}
void activeLoansInDateRange(const Customer arr[], int size) {
    string startDate = getValidDate("Enter start date (DD/MM/YYYY): ");
    string endDate = getValidDate("Enter end date (DD/MM/YYYY): ");
    
    int count = 0;
    cout << "\n===== ACTIVE LOANS IN DATE RANGE =====" << endl;
    cout << "Range: " << startDate << " to " << endDate << endl;
    
    for (int i = 0; i < size; i++) {
        if (arr[i].loans && !isEmpty(*arr[i].loans)) {
            LoanNode* n = arr[i].loans->head;
            while (n) {
                if (isDateInRange(n->data.startDate,startDate,endDate) && isDateInRange(n->data.endDate,startDate,endDate)) {
                    cout << "\nLoan ID: " << n->data.loanID << endl;
                    cout << "Customer: " << arr[i].account_holder_name << endl;
                    cout << "Type: " << n->data.loanType << endl;
                    cout << "Amount: " << n->data.principalAmount << " TND" << endl;
                    cout << "Start Date: " << n->data.startDate << endl;
                    count++;
                }
                n = n->next;
            }
        }
    }
    cout << "\nTotal active loans in range: " << count << endl;
}
void customerWithMostLoans(const Customer arr[], int size) {
    if (size == 0) {
        cout << "There are no customers" << endl;
        return;
    }
    
    int maxLoans = 0;
    int customerIndex = -1;
    
    for (int i = 0; i < size; i++) {
        int loanCount = (arr[i].loans) ? arr[i].loans->size : 0;
        if (loanCount > maxLoans) {
            maxLoans = loanCount;
            customerIndex = i;
        }
    }
    
    if (customerIndex != -1 && maxLoans > 0) {
        cout << "Customer with most loans:" << endl;
        cout << "  Name: " << arr[customerIndex].account_holder_name << endl;
        cout << "  Account: " << arr[customerIndex].account_number << endl;
        cout << "  Number of loans: " << maxLoans << endl;
    } else {
        cout << "No loans found in the system" << endl;
    }
}