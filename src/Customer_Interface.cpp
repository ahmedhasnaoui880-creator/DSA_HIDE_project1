#include "LoanMeth.h"
#include "Customer.h"
#include "TransactionMeth.h"
#include <iostream>
#include "Input_Validation.h"
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
        cout << "Space error please contact your agency" << endl;
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
    loansapplications->size++;  // ADD THIS LINE
    cout << "Loan application submitted successfully!" << endl;
    return 0;
}
int Withdraw(Customer &client)
{
    int choice = 0;
    double withdrawamount = 0;
    
    cout << "\n===== WITHDRAW MONEY =====" << endl;
    cout << "Current Balance: " << client.balance << " TND" << endl;
    cout << "\nChoose withdraw amount:" << endl;
    cout << "1. 10 TND" << endl;
    cout << "2. 20 TND" << endl;
    cout << "3. 50 TND" << endl;
    cout << "4. Another amount" << endl;
    
    choice = getValidInteger("Choice: ", 1, 4);
    
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
            withdrawamount = getValidDouble("Enter amount to withdraw (TND): ", 10.0);
            break;
    }
    
    if (withdrawamount > client.balance) {
        cout << "✗ Insufficient balance! Your balance is " << client.balance << " TND" << endl;
        return 1;
    }
    
    // Validate denominations (must be multiple of 10)
    if ((int)withdrawamount % 10 != 0) {
        cout << "✗ Amount must be a multiple of 10 TND!" << endl;
        return 1;
    }
    
    // Create transaction record
    Transaction tr;
    tr.transaction_id = to_string(rand() % 1000000000);
    tr.account_number = client.account_number;
    tr.type = "withdrawal";
    tr.amount = withdrawamount;
    time_t now = time(0);
    string dateStr = ctime(&now);
    if (!dateStr.empty() && dateStr[dateStr.length()-1] == '\n') {
        dateStr.erase(dateStr.length()-1);
    }
    tr.date = dateStr;
    
    pushTransaction(client.transactions, tr);
    client.balance = client.balance - withdrawamount;
    cout << "✓ Withdrawal successful! New balance: " << client.balance << " TND" << endl;
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
    string dateStr = ctime(&now);
    // Remove trailing newline from ctime
    if (!dateStr.empty() && dateStr[dateStr.length()-1] == '\n') {
        dateStr.erase(dateStr.length()-1);
    }
    tr.date = dateStr;
    
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
