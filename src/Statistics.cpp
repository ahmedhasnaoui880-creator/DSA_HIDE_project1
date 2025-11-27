 #include "StatisticsMeth.h"
using namespace std;

void totalnumofloans(const Customer arr[],int size){
    int sum=0;
    for (int i=0; i<size;i++){
        if(arr[i].loans){
        sum+= arr[i].loans->size;
        }
    }
    cout<< sum;
}
void numofloansbytype(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
    int carN=0,homeN=0,studentN=0, businessN=0;
    LoanNode* n;
    for (int i=0;i<size;i++){
        if(arr[i].loans && !isEmpty(*arr[i].loans)){
        n=arr[i].loans->head;
        while(n){
            if (n->data.loanType=="car") carN++;
            else if(n->data.loanType=="home") homeN++;
            else if(n->data.loanType=="student") studentN++;
            else if(n->data.loanType=="business") businessN++;
            n=n->next; 
        }

    }
}
    cout<<carN<<endl;
    cout<<homeN<<endl;
    cout<<studentN<<endl;
    cout<<businessN<<endl;
}

}
void numofloansbystatus(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
    int activeN=0,completedN=0,overdueN=0;
    LoanNode* n;
    for (int i=0;i<size;i++){
        if(arr[i].loans && !isEmpty(*arr[i].loans)){
        n=arr[i].loans->head;
        while(n){
            if (n->data.status=="active") activeN++;
            else if(n->data.status=="completed") completedN++;
            else if(n->data.status=="overdue") overdueN++;
            n=n->next; 
        }
    }

    }
    cout<< activeN<<endl;
    cout<< completedN<<endl;
    cout<< overdueN<<endl;
}
}
string normalize(string date){
    // Refolmelate the date into YYYYMMDD
    if (date.size() < 10) return "";
    return date.substr(6,4)+date.substr(3,2)+date.substr(0,2);
}
bool isInDate(string startDateR,string endDateR,string startDate,string endDate){
    // Return true if the loan [startDate,endDate] overlaps the range [startDateR,endDateR]
    if (startDate.empty() || endDate.empty() || startDateR.empty() || endDateR.empty()) return false;
    return !(endDate < startDateR || startDate > endDateR);
}
void activeloanindate(const Customer arr[],int size,string startDateR,string endDateR){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        int number=0;
        LoanNode* n;
        for (int i=0;i<size;i++){
            if(arr[i].loans && !isEmpty(*arr[i].loans)){
            n=arr[i].loans->head;
            while(n){
                if(n->data.status=="active" && isInDate(normalize(startDateR),normalize(endDateR),normalize(n->data.startDate),normalize(n->data.endDate))){
                    number++;
                }
                n=n->next; 
            }
        }

    }
    cout<< number;
}
}
void highestloanamount(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double higher=0.0;
        LoanNode* n;
        for (int i=0;i<size;i++){
            if(arr[i].loans && !isEmpty(*arr[i].loans)){
            n=arr[i].loans->head;
            while(n){
                if(n->data.principalAmount>higher){
                    higher=n->data.principalAmount;
                }
                n=n->next; 
            }
        }
    }
    cout << higher;
}
}
void highestbalance(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double higher=arr[0].balance;
        for (int i=1;i<size;i++){
                if(arr[i].balance>higher){
                    higher=arr[i].balance;
                }
        }
        cout << higher;
    }
}
void lowestbalance(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double lowest=arr[0].balance;
        for (int i=1;i<size;i++){
                if(arr[i].balance<lowest){
                    lowest=arr[i].balance;
                }
        }
        cout << lowest;
    }
}

void NumberofEmployees(const Employee employeeArr[],int size){
    cout<< size;
}
void NumberofEmployeesbyBB(const Employee arr[],int size,int branches){
    if (branches <= 0) {
        cout << "Invalid number of branches" << endl;
        return;
    }
    vector<int> employeesbyBBarr(branches, 0);
    if(size==0){
        cout<<"There are no employees";
    }
    else{
        for(int i=0;i<size;i++){
            int branch = arr[i].BankBranch;
            if (branch >= 1 && branch <= branches) {
                employeesbyBBarr[branch - 1]++;
            }
        }

    }
    for(int i=0;i<branches;i++){
        cout<<"Number of employees in branch: "<<i+1<<" --> "<<employeesbyBBarr[i]<<endl;
    }
}
int Main(){
    return 0;
}
#include "StatisticsMeth.h"
#include <vector>
using namespace std;

void totalnumofloans(const Customer arr[],int size){
    int sum=0;
    for (int i=0; i<size;i++){
        if(arr[i].loans){
        sum+= arr[i].loans->size;
        }
    }
    cout<< sum;
}
void numofloansbytype(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
    int carN=0,homeN=0,studentN=0, businessN=0;
    LoanNode* n;
    for (int i=0;i<size;i++){
        if(arr[i].loans && !isEmpty(*arr[i].loans)){
        n=arr[i].loans->head;
        while(n){
            if (n->data.loanType=="car") carN++;
            else if(n->data.loanType=="home") homeN++;
            else if(n->data.loanType=="student") studentN++;
            else if(n->data.loanType=="business") businessN++;
            n=n->next; 
        }

    }
}
    cout<<carN<<endl;
    cout<<homeN<<endl;
    cout<<studentN<<endl;
    cout<<businessN<<endl;
}

}
void numofloansbystatus(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
    int activeN=0,completedN=0,overdueN=0;
    LoanNode* n;
    for (int i=0;i<size;i++){
        if(arr[i].loans && !isEmpty(*arr[i].loans)){
        n=arr[i].loans->head;
        while(n){
            if (n->data.status=="active") activeN++;
            else if(n->data.status=="completed") completedN++;
            else if(n->data.status=="overdue") overdueN++;
            n=n->next; 
        }
    }

    }
    cout<< activeN<<endl;
    cout<< completedN<<endl;
    cout<< overdueN<<endl;
}
}
string normalize(string date){
    // Refolmelate the date into YYYYMMDD
    if (date.size() < 10) return "";
    return date.substr(6,4)+date.substr(3,2)+date.substr(0,2);
}
bool isInDate(string startDateR,string endDateR,string startDate,string endDate){
    // Return true if the loan [startDate,endDate] overlaps the range [startDateR,endDateR]
    if (startDate.empty() || endDate.empty() || startDateR.empty() || endDateR.empty()) return false;
    return !(endDate < startDateR || startDate > endDateR);
}
void activeloanindate(const Customer arr[],int size,string startDateR,string endDateR){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        int number=0;
        LoanNode* n;
        for (int i=0;i<size;i++){
            if(arr[i].loans && !isEmpty(*arr[i].loans)){
            n=arr[i].loans->head;
            while(n){
                if(n->data.status=="active" && isInDate(normalize(startDateR),normalize(endDateR),normalize(n->data.startDate),normalize(n->data.endDate))){
                    number++;
                }
                n=n->next; 
            }
        }

    }
    cout<< number;
}
}
void highestloanamount(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double higher=0.0;
        LoanNode* n;
        for (int i=0;i<size;i++){
            if(arr[i].loans && !isEmpty(*arr[i].loans)){
            n=arr[i].loans->head;
            while(n){
                if(n->data.principalAmount>higher){
                    higher=n->data.principalAmount;
                }
                n=n->next; 
            }
        }
    }
    cout << higher;
}
}
void highestbalance(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double higher=arr[0].balance;
        for (int i=1;i<size;i++){
                if(arr[i].balance>higher){
                    higher=arr[i].balance;
                }
        }
        cout << higher;
    }
}
void lowestbalance(const Customer arr[],int size){
    if(size==0){
        cout<<"There are no customers";
        return;
    }
    else{
        double lowest=arr[0].balance;
        for (int i=1;i<size;i++){
                if(arr[i].balance<lowest){
                    lowest=arr[i].balance;
                }
        }
        cout << lowest;
    }
}

void NumberofEmployees(const Employee employeeArr[],int size){
    cout<< size;
}
void NumberofEmployeesbyBB(const Employee arr[],int size,int branches){
    if (branches <= 0) {
        cout << "Invalid number of branches" << endl;
        return;
    }
    vector<int> employeesbyBBarr(branches, 0);
    if(size==0){
        cout<<"There are no employees";
    }
    else{
        for(int i=0;i<size;i++){
            int branch = arr[i].BankBranch;
            if (branch >= 1 && branch <= branches) {
                employeesbyBBarr[branch - 1]++;
            }
        }

    }
    for(int i=0;i<branches;i++){
        cout<<"Number of employees in branch: "<<i+1<<" --> "<<employeesbyBBarr[i]<<endl;
    }
}
int Main(){
    return 0;
}