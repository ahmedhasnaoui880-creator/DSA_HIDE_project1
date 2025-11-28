#ifndef CUSTOMER_INTERFACE_H
#define CUSTOMER_INTERFACE_H
#include <iostream>
#include "Customer.h"
int ViewLoans(Customer client);
int SubmitLoanApplication(Loan loan,LoanList* loansapplications);
int Withdraw(Customer& client,double withdrawamount);
int Deposit(Customer& client, double depositamout);
int ViewTransactionHistory(const TransactionStack &t);
int UndoLastTransaction(TransactionStack *t);
#endif // CUSTOMER_INTERFACE_H