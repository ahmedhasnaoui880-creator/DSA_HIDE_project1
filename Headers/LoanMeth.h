#ifndef LOANMETH_H
#define LOANMETH_H
#include "Loan.h"
#include "LoanList.h"
using namespace std;
LoanList initializeLoanList(LoanList* list);
LoanNode* createLoanNode(Loan loan);
bool isEmpty(const LoanList& list);
int insertLoan(LoanList* list, Loan loan, int position);
int removeLoan(LoanList* list, string loan_id);
Loan* findLoan(const LoanList& list,string loan_id);
void displayAllLoans(const LoanList& list);
void clearLoanList(LoanList* list);

#endif