#ifndef LOANMETH_H
#define LOANMETH_H
#include "Loan.h"
#include "LoanList.h"
using namespace std;
LoanList* createLoanList();
LoanNode* createLoanNode(Loan loan);
bool isEmpty(const LoanList& list);
int insertLoan(LoanList* list, Loan loan, int position);
int removeLoan(LoanList* list, int loanID);
Loan* findLoan(const LoanList& list,int loanID);
void displayAllLoans(const LoanList& list);
void clearLoanList(LoanList* list);

#endif