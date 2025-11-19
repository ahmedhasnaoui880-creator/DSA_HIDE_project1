#include "LoanMeth.h"
#include <iostream>
using namespace std;
LoanList initializeLoanList(LoanList* list) {
    return LoanList{nullptr, nullptr, 0};
}
LoanNode* createLoanNode(Loan loan) {
    LoanNode* newNode = new (nothrow) LoanNode{{}, nullptr, nullptr};
    if (!newNode){
        cout<<"Memory allocation failed for LoanNode."<<endl;
    }
    return newNode;
}
bool isEmpty(const LoanList& list) {
    return list.size == 0;
}
int insertLoan(LoanList* list, Loan loan, int position) {
    if (!list) return 0;
    if (position < 0 || position > list->size) {
        position = list->size;
    }
    LoanNode* node=createLoanNode(loan);
    if (!node) return 0;
    if (isEmpty(*list)){
        list->head =node;
        list->tail=node;
    }
    else if (position == 1){
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    else if (position == list->size+1){
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    else{
        LoanNode* current = list->head;
        for (int i = 1; i < position; i++) {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        current->prev->next = node;
        current->prev = node;
    }
    list->size++;
    return 1;
    
}
int removeLoan(LoanList* list, string loan_id) {
    if (!list ||isEmpty(*list)) {
        cout <<"Invalid operation: List is empty or null."<< endl;
        return 0;
    }
    LoanNode* current = list->head;
    while (current != nullptr && current->data.loan_id != loan_id) {
        current = current->next;
    }
    if (current != nullptr) {
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            list->head = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            list->tail = current->prev;
        }
        delete current;
        list->size--;
        return 1;
    }
    return 0;
}
Loan* findLoan(const LoanList& list, string loan_id) {
    LoanNode* current = list.head;
    while (current != nullptr) {
        if (current->data.loan_id == loan_id) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}
void displayAllLoans(const LoanList& list) {
    LoanNode* current = list.head;
    while (current != nullptr) {
        cout << "Loan ID: " << current->data.loan_id << ", Amount Paid: " << current->data.principal_amount << ", Status: " << current->data.status << endl;
        current = current->next;
    }
}
void clearLoanList(LoanList* list) {
    LoanNode* current = list->head;
    while (current != nullptr) {
        LoanNode* next = current->next;
        delete current;
        current = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}