#include "trStack.h"
#ifndef TRANSACTIONMETH_H
#define TRANSACTIONMETH_H
TransactionStack* createTransactionStack();
bool isTransactionStackEmpty(const TransactionStack& stack);
void pushTransaction(TransactionStack* stack, const Transaction& transaction);
Transaction popTransaction(TransactionStack* stack);
void clearTransactionStack(TransactionStack* stack);
int getTransactionStackSize(const TransactionStack& stack);
bool compareTransactions(const TransactionStack& t1, const TransactionStack& t2);
void destroyTransactionStack(TransactionStack* stack);
#endif