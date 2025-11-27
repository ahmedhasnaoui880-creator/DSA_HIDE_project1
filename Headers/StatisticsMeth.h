#ifndef STATISTICSMETH_H
#define STATISTICSMETH_H
#include <iostream>
#include "Customer.h"
#include "Employee.h"
#include "LoanMeth.h"
#include <string>
void totalnumofloans(const Customer arr[],int size);
void numofloansbytype(const Customer arr[],int size);
void numofloansbystatus(const Customer arr[],int size);
void highestloanamount(const Customer arr[],int size);
void highestbalance(const Customer arr[],int size);
void lowestbalance(const Customer arr[],int size);
void NumberofEmployees(const Employee employeeArr[],int size);
void NumberofEmployeesbyBB(const Employee arr[],int size,int branches);
#endif // STATISTICSMETH_H