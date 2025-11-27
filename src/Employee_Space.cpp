#include "Employee.h"
#include "Customer.h"
#include "iostream"
using namespace std;
void SortByAlpha(Employee employees[],int empcout);
void SortByBB(Employee employees[],int empcount);
int addEmployee(Employee emp,Employee employees[],int& empcount){
    employees[empcount]=emp;
    empcount++;
    return 0;
}
int removeEmployee(Employee employees[],int& empcount,int empID){
    int index=0;
    while (index<empcount && employees[index].employeeID!=empID){
        index++;
    }
    if (index==empcount){
        cout <<"Employee not found";
        return 1;
    }
    else{
        for (int i=index;i<empcount-1;i++){
            employees[i]=employees[i+1];
        }
        empcount--;
    }
    return 0;
}
int updateEmployee(Employee employees[],int empcount,int empID,Employee updatedEmp){
    int index=0;
    while (index<empcount && employees[index].employeeID!=empID){
        index++;
    }
    if (index==empcount){
        cout <<"Employee not found";
        return 1;
    }
    else{
        employees[index]=updatedEmp;
    }
    return 0;
}
int displayEmployeeAlpha(Employee employees[],int empcount){
    SortByAlpha(employees,empcount);
    for (int i=0;i<empcount;i++){
        cout <<"Employee ID: " << employees[i].employeeID << endl;
        cout <<"Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout <<"Address: " << employees[i].adress << endl;
        cout <<"Salary: " << employees[i].salary << endl;
        cout <<"Hire Date: " << employees[i].hireDate << endl;
        cout <<"Bank Branch: " << employees[i].BankBranch << endl;
        cout <<"------------------------" << endl;
    }
    return 0;
}
int displayEmployeeByBB(Employee employees[],int empcount){
    SortByBB(employees,empcount);
    for (int i=0;i<empcount;i++){
        cout <<"Employee ID: " << employees[i].employeeID << endl;
        cout <<"Name: " << employees[i].name << " " << employees[i].lastName << endl;
        cout <<"Address: " << employees[i].adress << endl;
        cout <<"Salary: " << employees[i].salary << endl;
        cout <<"Hire Date: " << employees[i].hireDate << endl;
        cout <<"Bank Branch: " << employees[i].BankBranch << endl;
        cout <<"------------------------" << endl;
    }
    return 0;
}
int earliestHireDate(Employee employees[],int empcount){
    string maxdate=employees[0].hireDate;
    for (int i=1;i<empcount;i++){
    }
    return 0;
}
int latestHireDate(){
    return 0;
}
int addCustomer(){
    return 0;
}
int displayCustomers(){
    return 0;
}
int changeStatusofaccount(){
    return 0;
}
int DeleteClosedAccounts(){
    return 0;
}
int displayloansbycustomer(){
    return 0;
}
int changeLoanStatus(){
    return 0;
}
int deleteloan(){
    return 0;
}
int Manageloans(){
    return 0;
}
int ManageTransactions(){
    return 0;
}
