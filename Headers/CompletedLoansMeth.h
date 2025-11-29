#ifndef COMPLETEDLOANSMETH_H
#define COMPLETEDLOANSMETH_H

#include "Loan.h"
#include "CompletedLoansList.h"


CompletedLoansListNode* createNode(Loan loan);
void destroyNode(CompletedLoansListNode* node);

CompletedLoansList createList();
void destroyList(CompletedLoansList* L);
bool isEmpty(const CompletedLoansList& L);
bool isFull(const CompletedLoansList& L);
int listSize(const CompletedLoansList& L);

int insert(CompletedLoansList* L, Loan loan, int pos);
int removeAt(CompletedLoansList* L, int pos);
int getElement(const CompletedLoansList& L, int pos);
void displayList(const CompletedLoansList& L);

CompletedLoansList CopyList(const CompletedLoansList& L);
bool CompareLists(const CompletedLoansList& L1, const CompletedLoansList& L2);

#endif