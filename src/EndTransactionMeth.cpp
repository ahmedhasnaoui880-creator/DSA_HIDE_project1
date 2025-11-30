#include "EndTransactionsList.h"
EndTransactionList* createEndTransactionList(){
    EndTransactionList* list= new (nothrow) EndTransactionList;
    if (!list){
        cout <<"Storage Error Please Try Again Later";
        return nullptr;
    }
    list->head=nullptr;
    list->size=0;
    return list;
}
bool isEndTransactionEmpty(const EndTransactionList list){
    return list.size==0;
}
EndTransactionNode* createEndTransactionNode(const Transaction& transaction){
    EndTransactionNode* node= new (nothrow) EndTransactionNode;
    if (!node){
        cout <<"Storage Error Please Try Again Later";
        return nullptr;
    }
    node->data=transaction;
    node->next=nullptr;
    return node;
}
int addEndTransaction(EndTransactionList* list, const Transaction& transaction)
{
    EndTransactionNode* node = createEndTransactionNode(transaction);
    if (node == nullptr) {
        return 1;
    }
    
    if (list->size == 0) {  // Changed from = to ==
        list->head = node;
    } else {
        EndTransactionNode* current = list->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
    list->size++;
    return 0;
}