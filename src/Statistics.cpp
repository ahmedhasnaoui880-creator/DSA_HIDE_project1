#include "StatisticsMeth.h"
#include <iostream>
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

void NumberofEmployeesbyBB(const Employee arr[], int size, int branches) {
    if (branches <= 0) {
        cout << "Invalid number of branches" << endl;
        return;
    }
    
    if (size == 0) {
        cout << "There are no employees" << endl;
        return;
    }
    
    // Use simple array instead of vector
    int* employeesbyBB = new int[branches];
    for (int i = 0; i < branches; i++) {
        employeesbyBB[i] = 0;
    }
    
    for (int i = 0; i < size; i++) {
        int branch = arr[i].BankBranch;
        if (branch >= 1 && branch <= branches) {
            employeesbyBB[branch - 1]++;
        }
    }
    
    cout << "Number of employees by branch:" << endl;
    for (int i = 0; i < branches; i++) {
        cout << "  Branch " << (i + 1) << ": " << employeesbyBB[i] << " employees" << endl;
    }
    
    delete[] employeesbyBB;
}