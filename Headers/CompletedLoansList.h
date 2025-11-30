#ifndef COMPLETEDLOANSLIST_H
#define COMPLETEDLOANSLIST_H
#include "Loan.h"
struct CompletedLoansListNode
{
    Loan data;
    CompletedLoansListNode* next;
};
struct CompletedLoansList
{
    CompletedLoansListNode* head;
    int size;
};

#endif // COMPLETEDLOANSLIST_H