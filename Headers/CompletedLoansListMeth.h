#ifndef COMPLETEDLOANSLISTMETH_H
#define COMPLETEDLOANSLISTMETH_H
#include "CompletedLoansList.h"
CompletedLoansList* createCompletedLoansList();
bool isCompletedLoansListEmpty(const CompletedLoansList& list);
CompletedLoansListNode* createCompletedLoansListNode(const Loan& loan);
int addCompletedLoan(CompletedLoansList* list, const Loan& loan);
#endif // COMPLETEDLOANSLISTMETH_H