#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <string>
using namespace std;
struct Employee {
    int employeeID;
    string name;
    string lastName;
    string adress;
    double salary;
    string hireDate;
    int BankBranch;
};
#endif