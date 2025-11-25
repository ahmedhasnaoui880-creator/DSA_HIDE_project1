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
        cust.loans = new LoanList();
        *cust.loans = initializeLoanList(cust.loans);
        cust.transactions = new TransactionStack();
        *cust.transactions = initTransactionStack(cust.transactions);
        customers[customerCount++] = cust;
    }
    return 0;
}