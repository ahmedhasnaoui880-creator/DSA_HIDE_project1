#include "LoanMeth.h"
#include "Customer.h"
#include "TransactionMeth.h"
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
int Withdraw(Customer &client)
{
    int choice=0;
    int withdrawamount;
    cout <<"Choose a withdraw amount:"<<endl;
    cout <<"1. 10TND"<<endl;
    cout <<"2. 20TND"<<endl;
    cout <<"3. 50TND"<<endl;
    cout <<"4. Another amount"<<endl;
    cin >> choice;
    do{

        switch (choice)
        {
            case 1:
            withdrawamount=10;
            break;
            case 2:
            withdrawamount=20;
            break;
            case 3:
            withdrawamount=50;
            break;
            case 4:
        cout << "Choose an amount:"<<endl;
        cin >> choice;
        
        default:
        cout << "Invalide choice!";
        break;
    }
}while (choice!=1 && choice!=2 && choice!=3 && choice!=4 );
    if (withdrawamount > client.balance || withdrawamount<10)
    {
        cout << "Sorry u Cannot withdraw that amount please try another!"<<endl;
        return 1;
    }
    else
    {
        client.balance = client.balance - withdrawamount;
        cout << "with draw is seccessful";
    }
    return 0;
}
int Deposit(Customer &client)
{
    float depositamount;
    do{
        cout<<"Enter Your Deposit amount";
        cin >> depositamount;
        if (depositamount<=0){
            cout <<"Invalide Amout Please Retry!";
        }
    }while (depositamount<=0);
    client.balance = client.balance + depositamount;
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
    Transaction undoTransaction=popTransaction(t);
    return 0;
}
