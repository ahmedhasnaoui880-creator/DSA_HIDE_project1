#ifndef EMPLOYEE_SPACE_H
#define EMPLOYEE_SPACE_H
#include <iostream>
#include <string>
#include "Employee.h"
#include "Customer.h"
#include "Loan.h"
#include "LoanList.h"
#include "CompletedLoansList.h"
#include "EndTransactionsList.h"
void SortByAlpha(Employee employees[],int empcout);
void SortByBB(Employee employees[],int empcount);
int addEmployee(Employee emp,Employee employees[],int& empcount);
int removeEmployee(Employee employees[],int& empcount,int empID);
int updateEmployee(Employee employees[],int empcount,int empID,Employee updatedEmp);
int displayEmployeeAlpha(Employee employees[],int empcount);
int displayEmployeeByBB(Employee employees[],int empcount);
int earliestHireDate(Employee employees[],int empcount);
int latestHireDate(Employee employees[], int empcount);
int addCustomer(Customer c, Customer customers[], int custmcount);
int displayCustomers(Customer customers[], int custmcount);
int changeStatusofaccount(Customer customers[], int custmcount,string custId,string newStat);
int DeleteClosedAccounts(Customer customers[], int &empcount, Customer archived[], int &archcount);
int displayloansbycustomer(Customer customers[], int custmcount);
int changeLoanStatus(LoanList* loans, int loanID, string newStatus);
int deleteloan(CompletedLoansList* completed_loans);
int Manageloans(LoanList* appliedloans,Customer customers[],int custcount);
EndTransactionList* ManageTransactions(Customer customers[],int custcount);
#endif // EMPLOYEE_SPACE_H