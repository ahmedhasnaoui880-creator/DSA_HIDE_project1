#include "LoanMeth.h"
#include "Customer.h"
#include <iostream>
using namespace std;
int ViewLoans(Customer client)
{
    LoanList *loans = client.loans;
    if (!loans || loans->size == 0)
    {
        cout << "U have no loan for the moment." << endl;
        return 1;
    }
    LoanNode *current = loans->head;
    while (current != nullptr)
    {
        cout << "Loan ID: " << current->data.loanID << endl;
        cout << "Amount: " << current->data.principalAmount << endl;
        cout << "Type: " << current->data.loanType << endl;
        cout << "Status: " << current->data.status << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
    return 0;
}

int SubmitLoanApplication(Loan loan, LoanList *loansapplications)
{
    LoanNode *appliedloan = createLoanNode(loan);
    if (!appliedloan)
    {
        cout << "Space error please contact your agency";
        return 1;
    }
    if (loansapplications->size == 0)
    {
        loansapplications->head = appliedloan;
        loansapplications->tail = appliedloan;
    }
    else
    {
        loansapplications->tail->next = appliedloan;
        appliedloan->prev = loansapplications->tail;
        loansapplications->tail = appliedloan;
    }
    return 0;
}
int Withdraw(Customer &client, double withdrawamount)
{
    if (withdrawamount > client.balance)
    {
        cout << "Sorry u don't have enough to withdraw";
        return 1;
    }
    else
    {
        client.balance = client.balance - withdrawamount;
        cout << "with draw is seccessful";
    }
    return 0;
}
int Deposit(Customer &client, double depositamout)
{
    client.balance = client.balance + depositamout;
    cout << "Your deposit is seccessful";
    return 0;
}
int ViewTransactionHistory(const TransactionStack &t)
{
    if (t.top == nullptr)
    {
        cout << "Empty stack !! " << endl;
        return 1;
    }
    TransactionStackNode *current = t.top;
    cout << "Transaction history: " << endl;
    while (current != nullptr)
    {
        cout << "Transaction ID: " << current->data.transaction_id << endl;
        cout << "Account Number: " << current->data.account_number << endl;
        cout << "Type: " << current->data.type << endl;
        cout << "Amount: " << current->data.amount << endl;
        cout << "Date: " << current->data.date << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
    return 0;
}
int UndoLastTransaction(TransactionStack *t)
{
    if (t->top == nullptr)
    {
        cout << "No transactions to undo." << endl;
        return 1;
    }
    TransactionStackNode *temp = t->top;
    t->top = t->top->next;
    delete temp;
    return 0;
}
