#ifndef LOAN_H
#define LOAN_H
#include <iostream>
#include <string>
using namespace std;
struct Loan
{
    int loanID;
    string loanType;
    double principalAmount;
    double interestRate;
    double amountPaid;
    double remainingBalance;
    string startDate;
    string endDate;
    string status;
    string account_number; 
};
#endif