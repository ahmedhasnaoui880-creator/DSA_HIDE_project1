#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <iostream>
#include <string>
#include "Customer.h"
#include "Employee.h"
using namespace std;
int getValidInteger(string prompt, int min, int max);
double getValidDouble(string prompt, double min);
string getValidAccountNumber(Customer customers[], int custCount, bool checkUnique);
int getValidEmployeeID(Employee employees[], int empCount, bool checkUnique);
int getValidLoanID(LoanList* globalLoans, Customer customers[], int custCount);
string getValidDate(string prompt);
string getValidStatus();
string getValidLoanType();
double getValidInterestRate();
string getValidString(string prompt);
int getValidBankBranch();
string getValidIBAN();
#endif