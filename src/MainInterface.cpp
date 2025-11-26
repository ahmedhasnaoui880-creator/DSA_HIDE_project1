#include "trStack.h"
#include "Customer.h"
#include "LoanList.h"
#include "Employee.h"
#include "LoanMeth.h"
#include "TransactionMeth.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
Customer Split_line_to_customer(string line){
    Customer cust;
    string linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_number = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_type = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.IBAN = linepart;
    linepart = line.substr(0, line.find(',')); 
    line.erase(0, line.find(',') + 1);
    cust.branch_code = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.account_holder_name = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.opening_date = linepart;
    linepart = line.substr(0, line.find(','));
    line.erase(0, line.find(',') + 1);
    cust.status = linepart;
    linepart = line.substr(0, line.find(','));
    cust.balance = stod(linepart);
    return cust;
    }
LoanList* getCustomerLoans(string account_number){
    ifstream file("Loans.txt");
    if (!file) {
        return nullptr;
    }
    LoanList* loans = createLoanList();
    string line;
    while (getline(file, line)){
        string linepart = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        if (linepart == account_number){
            Loan loan;
            loan.account_number = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanID = stoi(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.loanType = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.principalAmount = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.interestRate = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.amountPaid = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.remainingBalance = stod(linepart);
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.startDate = linepart;
            linepart = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1);
            loan.endDate = linepart;
            loan.status = line;
            LoanNode* newNode = createLoanNode(loan);
            if (loans->size == 0) {
                loans->head = newNode;
                loans->tail = newNode;
            } else {
                loans->tail->next = newNode;
                newNode->prev = loans->tail;
                loans->tail = newNode;
            }
            loans->size++;
        }
    }
    file.close();
    return loans;
}
TransactionStack* getCustomerTransactions(string account_number){
    ifstream file ("Transactions.txt");
    if (!file) {
        return nullptr;
    }
    TransactionStack* trStack=createTransactionStack();
    string line;
    while (getline(file,line)){
        string linepart=line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        if (linepart==account_number){
            Transaction transaction;
            transaction.account_number=linepart;
            linepart=line.substr(0,line.find(','));
            line.erase(0,line.find(',')+1);
            transaction.transaction_id=linepart;
            linepart=line.substr(0,line.find(','));
            line.erase(0,line.find(',')+1);
            transaction.type=linepart;
            linepart=line.substr(0,line.find(','));
            line.erase(0,line.find(',')+1);
            transaction.amount=stod(linepart);
            transaction.date=line;
            pushTransaction(trStack,transaction);
    }
    file.close();
    return trStack;
}
}
int mainInterface(){
    ifstream file("Customers.txt");
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }
    Customer customers[100];
    int customerCount = 0;
    string line;
    while (getline(file, line) && customerCount < 100) {
        Customer cust=Split_line_to_customer(line);
        cust.loans = getCustomerLoans(cust.account_number);
        cust.transactions = getCustomerTransactions(cust.account_number);
        customers[customerCount++] = cust;
    }
    return 0;
}