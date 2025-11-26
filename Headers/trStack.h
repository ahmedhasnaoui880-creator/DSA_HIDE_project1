#ifndef TRSTACK_H
#define TRSTACK_H
#include <iostream>
#include "Transaction.h"
using namespace std;
struct TransactionStackNode
{
    Transaction data;
    TransactionStackNode* next;
};
struct TransactionStack
{
    TransactionStackNode* top;
};
#endif