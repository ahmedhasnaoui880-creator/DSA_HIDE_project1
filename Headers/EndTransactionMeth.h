#ifndef ENDTRANSACTIONMETH_H
#define ENDTRANSACTIONMETH_H
#include "EndTransactionsList.h"
EndTransactionList* createEndTransactionList();
bool isEndTransactionEmpty(const EndTransactionList list);
EndTransactionNode* createEndTransactionNode(const Transaction& transaction);
int addEndTransaction(EndTransactionList* list, const Transaction& transaction);
#endif