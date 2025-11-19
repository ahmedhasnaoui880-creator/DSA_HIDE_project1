#include "LoanList.h"
#include "trStack.h"
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
using namespace std;
struct Customer
{
    string account_number;
    string account_type;
    string IBAN;
    string branch_code;
    string account_holder_name;
    string opening_date;
    string status;
    double balance;
    LoanList loans;
    TransactionStack transactions;

};

#endif