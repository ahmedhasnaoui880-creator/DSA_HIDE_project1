#include "trStack.h"
#include <iostream>
using namespace std;
TransactionStack initTransactionStack(TransactionStack* stack) {
    return TransactionStack{nullptr, -1};
    
}
bool isTransactionStackEmpty(const TransactionStack& stack) {
    return stack.top == nullptr;
}
void pushTransaction(TransactionStack* stack, const Transaction& transaction) {
    TransactionStackNode* newNode = new TransactionStackNode();
    newNode->data = transaction;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->topindex++;
}
Transaction popTransaction(TransactionStack* stack, Transaction& transaction) {
    if (isTransactionStackEmpty(*stack)) {
        return Transaction{};
    }
    TransactionStackNode* temp = stack->top;
    transaction = stack->top->data;
    stack->top = stack->top->next;
    delete temp;
    stack->topindex--;
    return transaction;
}
void clearTransactionStack(TransactionStack* stack) {
    TransactionStackNode* current = stack->top;
    while (current != nullptr) {
        TransactionStackNode* temp = current;
        current = current->next;
        delete temp;
    }
    stack->top = nullptr;
    stack->topindex = -1;
}
int getTransactionStackSize(const TransactionStack& stack) {
    return stack.topindex + 1;
}
bool compareTransactions(const TransactionStack& t1, const TransactionStack& t2) {
    if (getTransactionStackSize(t1) != getTransactionStackSize(t2)) {
        return false;
    }
    TransactionStackNode* current1 = t1.top;
    TransactionStackNode* current2 = t2.top;
    while (current1 != nullptr && current2 != nullptr) {
        if (current1->data.transaction_id != current2->data.transaction_id ||
            current1->data.account_number != current2->data.account_number ||
            current1->data.type != current2->data.type ||
            current1->data.amount != current2->data.amount ||
            current1->data.date != current2->data.date) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}