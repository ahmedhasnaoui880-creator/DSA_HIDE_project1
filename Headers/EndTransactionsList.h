#ifndef ENDTRANSACTIONLSIT_H
#define ENDTRANSACTIONLSIT_H
#include "Transaction.h"
struct EndTransactionNode
{
    Transaction data;
    EndTransactionNode* next;
};
struct EndTransactionList
{
    EndTransactionNode* head;
    int size;
};
#endif