#ifndef EMPLOYEE_SPACE_H
#define EMPLOYEE_SPACE_H
#include <iostream>
#include <string>
#include "Employee.h"
#include "Customer.h"
#include "Loan.h"
#include "LoanList.h"
void SortByAlpha(Employee employees[],int empcout);
void SortByBB(Employee employees[],int empcount);
int addEmployee(Employee emp,Employee employees[],int& empcount);
int removeEmployee(Employee employees[],int& empcount,int empID);
int updateEmployee(Employee employees[],int empcount,int empID,Employee updatedEmp);
int displayEmployeeAlpha(Employee employees[],int empcount);
int displayEmployeeByBB(Employee employees[],int empcount);
int earliestHireDate(Employee employees[],int empcount);
int latestHireDate();
int addCustomer();
int displayCustomers();
int changeStatusofaccount();
int DeleteClosedAccounts();
int displayloansbycustomer();
int changeLoanStatus();
int deleteloan();
int Manageloans();
int ManageTransactions();
#endif // EMPLOYEE_SPACE_H