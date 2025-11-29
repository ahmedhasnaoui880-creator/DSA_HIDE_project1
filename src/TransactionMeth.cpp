#include "trStack.h"
#include <iostream>
using namespace std;
TransactionStack* createTransactionStack() {
    TransactionStack* stack = new (nothrow) TransactionStack();
    if (!stack){
        cout<<"Memory allocation failed for TransactionStack."<<endl;
        return nullptr;
    }
    stack->top = nullptr;
    return stack;
    
}
bool isTransactionStackEmpty(const TransactionStack& stack) {
    return stack.top == nullptr;
}
void pushTransaction(TransactionStack* stack, const Transaction& transaction) {
    TransactionStackNode* newNode = new TransactionStackNode();
    newNode->data = transaction;
    newNode->next = stack->top;
    stack->top = newNode;
}
Transaction popTransaction(TransactionStack* stack, Transaction& transaction) {
    if (isTransactionStackEmpty(*stack)) {
        cout <<"No Transactions to undo!";
        return Transaction{};
    }
    TransactionStackNode* temp = stack->top;
    transaction = stack->top->data;
    stack->top = stack->top->next;
    delete temp;
    cout <<"Undo is Completed!";
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
}
int getTransactionStackSize(const TransactionStack& stack) {
    int size=0;
    TransactionStackNode* node = stack.top;
    while (node != nullptr) {
        size++;
        node = node->next;
    }
    return size;
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