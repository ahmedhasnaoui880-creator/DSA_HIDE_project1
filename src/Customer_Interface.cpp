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
    int choice = 0;
    double withdrawamount = 0;
    cout << "Choose a withdraw amount:" << endl;
    cout << "1. 10TND" << endl;
    cout << "2. 20TND" << endl;
    cout << "3. 50TND" << endl;
    cout << "4. Another amount" << endl;
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            withdrawamount = 10;
            break;
        case 2:
            withdrawamount = 20;
            break;
        case 3:
            withdrawamount = 50;
            break;
        case 4:
            cout << "Enter amount: ";
            cin >> withdrawamount;
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }
    
    if (withdrawamount > client.balance || withdrawamount < 10)
    {
        cout << "Sorry, you cannot withdraw that amount. Please try another!" << endl;
        return 1;
    }
    
    // Create transaction record
    Transaction tr;
    tr.transaction_id = to_string(rand() % 1000000000);
    tr.account_number = client.account_number;
    tr.type = "withdrawal";
    tr.amount = withdrawamount;
    time_t now = time(0);
    tr.date = ctime(&now);
    
    pushTransaction(client.transactions, tr);
    client.balance = client.balance - withdrawamount;
    cout << "Withdrawal successful! New balance: " << client.balance << " TND" << endl;
    return 0;
}
int Deposit(Customer &client)
{
    double depositamount;
    do {
        cout << "Enter your deposit amount: ";
        cin >> depositamount;
        if (depositamount <= 0) {
            cout << "Invalid amount! Please retry!" << endl;
        }
    } while (depositamount <= 0);
    
    // Create transaction record
    Transaction tr;
    tr.transaction_id = to_string(rand() % 1000000000);
    tr.account_number = client.account_number;
    tr.type = "deposit";
    tr.amount = depositamount;
    time_t now = time(0);
    tr.date = ctime(&now);
    
    pushTransaction(client.transactions, tr);
    client.balance = client.balance + depositamount;
    cout << "Your deposit is successful! New balance: " << client.balance << " TND" << endl;
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
int UndoLastTransaction(Customer &client)
{
    if (isTransactionStackEmpty(*client.transactions)) {
        cout << "No transactions to undo!" << endl;
        return 1;
    }
    
    Transaction undoTransaction = popTransaction(client.transactions);
    
    // Reverse the transaction effect
    if (undoTransaction.type == "deposit") {
        client.balance -= undoTransaction.amount;
        cout << "Deposit of " << undoTransaction.amount << " TND has been undone." << endl;
    } else if (undoTransaction.type == "withdrawal") {
        client.balance += undoTransaction.amount;
        cout << "Withdrawal of " << undoTransaction.amount << " TND has been undone." << endl;
    }
    
    cout << "New balance: " << client.balance << " TND" << endl;
    return 0;
}
