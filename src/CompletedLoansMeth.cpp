#include "CompletedLoansList.h"
CompletedLoansListNode* createNode(Loan loan){
    CompletedLoansListNode* node= new (nothrow) CompletedLoansListNode;
    if (!node){
        cout<<"Storage Error Please Try Again Later";
        return nullptr;
    }
    node->next=nullptr;
    node->data=loan;
    return node;
}
void destroyNode(CompletedLoansListNode* node){
    delete node;
}

CompletedLoansList* createCompletedLoanList(){
    CompletedLoansList* list= new (nothrow) CompletedLoansList;
    if (!list){
        cout <<"Storage Error Please Try Again Later";
        return nullptr;
    }
    list->head=nullptr;
    list->size=0;
    return list;
}
void destroyList(CompletedLoansList* L){
    CompletedLoansListNode* current=L->head;
    while (current){
        CompletedLoansListNode* temp=current;
        current=current->next;
        delete(temp);
    }
    L->head=nullptr;
    L->size=0;
}
bool isEmpty(const CompletedLoansList& L){
    return L.size==0;
}
bool isFull(const CompletedLoansList& L){
    Loan l;
    CompletedLoansListNode* temp=createNode(l);
    return temp==nullptr;
}
int listSize(const CompletedLoansList& L){
    return L.size;
}

int insertIntoConpletedLoans(CompletedLoansList* L, Loan loan, int pos){
    if (pos < 0 || pos > L->size) {
        return -1; // Invalid position
    }
    CompletedLoansListNode* newNode = createNode(loan);
    if (pos == 0) {
        newNode->next = L->head;
        L->head = newNode;
    } else {
        CompletedLoansListNode* current = L->head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    L->size++;
    return 0; // Success
}
int removeAt(CompletedLoansList* L, int pos){
    if (pos < 0 || pos >= L->size) {
        return -1; // Invalid position
    }
    CompletedLoansListNode* toDelete;
    if (pos == 0) {
        toDelete = L->head;
        L->head = L->head->next;
    } else {
        CompletedLoansListNode* current = L->head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
    }
    return 0;
}
Loan getElement(const CompletedLoansList& L, int pos){
    Loan l; 
    if (pos < 0 || pos >= L.size) {
        return l;
    }
    CompletedLoansListNode* current = L.head;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }
    return current->data;
}