#include <iostream>
using namespace std;
#include <regex>
#include <fstream>
#include <bits/stdc++.h>
int fine_per_day= 5;
int damage_per_day=0.5;
float discount_to_employee=0.85;
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a month
int daysInMonth(int month, int year) {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}
bool isValidDateFormat(const std::string& date) {
    // Regular expression to match DDMMYYYY format
    std::regex pattern(R"(\b(0[1-9]|[12][0-9]|3[01])(0[1-9]|1[0-2])(19|20)\d\d\b)");

    // Check if the input matches the pattern
    if (!std::regex_match(date, pattern)) {
        return false; // If format doesn't match, return false
    }

    // Extract day, month, and year from the input string
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(2, 2));
    int year = std::stoi(date.substr(4, 4));

    // Check if the month is valid (1-12)
    if (month < 1 || month > 12) {
        return false;
    }

    // Check if the day is valid for the given month
    if ((day < 1) || (day > 31)) {
        return false;
    }

    // Adjust February days for leap years
    bool isLeapYear = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
    if (month == 2) {
        if (isLeapYear) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    }

    // Check if the day is valid for the given month (considering months with 30 days)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) {
        return false;
    }

    return true; // If all checks passed, return true
}

bool dates_compare(string date1,string date2){
    reverse(date1.begin(),date2.end());
    reverse(date1.begin(),date2.end());
    int num1=stoi(date1);
    int num2=stoi(date2);
    return num2>num1;
}
int daysBetweenDates(const std::string& startDateStr, const std::string& endDateStr) {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;

    std::istringstream(startDateStr.substr(0, 2)) >> startDay;
    std::istringstream(startDateStr.substr(2, 2)) >> startMonth;
    std::istringstream(startDateStr.substr(4, 4)) >> startYear;

    std::istringstream(endDateStr.substr(0, 2)) >> endDay;
    std::istringstream(endDateStr.substr(2, 2)) >> endMonth;
    std::istringstream(endDateStr.substr(4, 4)) >> endYear;

    int totalDays = 0;

    for (int year = startYear; year <= endYear; ++year) {
        int endMonthLoop = (year == endYear) ? endMonth : 12;
        int startMonthLoop = (year == startYear) ? startMonth : 1;

        for (int month = startMonthLoop; month <= endMonthLoop; ++month) {
            int daysInThisMonth = daysInMonth(month, year);
            int startDayLoop = (year == startYear && month == startMonth) ? startDay : 1;
            int endDayLoop = (year == endYear && month == endMonth) ? endDay : daysInThisMonth;

            totalDays += endDayLoop - startDayLoop+1;
        }
    }

    return (totalDays-1);
}

// Function to add 7 days to a date string in DDMMYYYY format
std::string add7Days(const std::string& date) {
    // Extract day, month, and year from the input date string
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(2, 2));
    int year = std::stoi(date.substr(4, 4));

    // Increment the day by 7 days
    day += 7;

    // Check if the day exceeds the number of days in the month
    while (day > daysInMonth(month, year)) {
        // Subtract the number of days in the current month
        day -= daysInMonth(month, year);

        // Move to the next month
        ++month;

        // If the month exceeds 12, move to the next year
        if (month > 12) {
            month = 1;
            ++year;
        }
    }

    // Format the resulting date string
    std::string result;
    if (day < 10) {
        result += "0";
    }
    result += std::to_string(day);
    if (month < 10) {
        result += "0";
    }
    result += std::to_string(month);
    result += std::to_string(year);
    
    return result;
}

class User{
    public:
        string name;
        string ID;
        string  password;
};
class Car{
    public:
        string model;
        int condition;
        int minimum_requirement;
        int rent;
        bool isRented=false;
        User* renter;
        bool Check_if_car_exists(string filename, Car* c);
        void Push_New_Car(string filename,Car* c);

};
class Customer:public User{
    private:
        int avg_customer_record;
    public:
        Customer(int avg_customer_record=15){
            this->avg_customer_record=avg_customer_record;
        }
        int get_customer_record(){
            return avg_customer_record;
        }
        void set_customer_record(int avg_customer_record){
            this->avg_customer_record=avg_customer_record;
        }
        void check_available(void);
        void check_mine_rented(Customer* c);
        void rent_a_car(Customer* c, string model,string date_today);
        int check_current_dues(Customer* c,string current_date);
        void clear_dues(Customer* c,string date,int health);
            

};
void Customer::clear_dues(Customer* c,string date, int health){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    vector <vector <string>> data;
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==0 || iteration==1 ||iteration==2) temp.push_back(cell);
            else if(iteration==3){
                if(cell=="0"){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back("0");
                    marker=1;
                }
            }
            else if(iteration==4){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!=c->name){
                        temp[3]="1";
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("0");
                    }
                    
                }
            }
            else if(iteration==5){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!=c->ID){
                        temp[3]="1";
                        temp[4]=c->name;
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("0");
                    }
                }
            }
            else if(iteration==6){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!="c"){
                        temp[3]="1";
                        temp[4]=c->name;
                        temp[5]=c->ID;
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("n");
                    }
                }
            }
            else if(iteration==7){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back("0");
                }
            }
            
            else if(iteration==8){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back(to_string(health));
                }
            }
            
            iteration++;
            
        }
        data.push_back(temp);
    }
    file.close();
    ofstream outfile("car_database.csv");
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
    
}
int Customer::check_current_dues(Customer* c,string current_date){
    ifstream file("car_database.csv");
    int total_cost=0;
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return -1;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        int iteration=0;
        string model;
        int price=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                if(stoi(cell)>this->avg_customer_record){
                    break;
                }
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="0"){
                    break;
                }
            }
            else if(iteration==4){
                if(cell!=c->name){
                    break;
                }
            }
            else if(iteration==5){
                if(cell!=c->ID){
                    break;
                }
            }
            else if(iteration==6){
                if(cell!="c"){
                    break;
                }
            }
            else if(iteration==7){
                if(dates_compare(cell,current_date)){
                    total_cost+=daysBetweenDates(cell,current_date)*fine_per_day;
                
                }
            }
            iteration++;
        }
    }
    return total_cost;
}
void Customer::rent_a_car(Customer* c, string model,string date_today){
    ifstream file("car_database.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    vector <vector <string>> data;
    string line;
    int check=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        
        while(getline(ss,cell,',')){
            if(iteration==0){
                if(cell==model){
                    check++;
                    temp.push_back(model);
                    marker=1;
                }
                else{
                    temp.push_back(cell);
                }
            }
            else if(marker==0){
                temp.push_back(cell);
            }
            else if(marker==1){
                if(iteration==1){
                    if(stoi(cell)>this->avg_customer_record){
                        std::cout<<"Car cannot be rented due to your low customer record"<<endl;
                        marker=0;
                        check=1;
                    }
                    temp.push_back(cell);
                }
                else if(iteration==2){
                    temp.push_back(cell);

                }
                else if(iteration==3){
                    if(cell=="1"){
                        std::cout<<"Car is already rented"<<endl;
                        marker=0;
                        check=1;
                    }
                    temp.push_back("1");
                }
                else if(iteration==4){
                    temp.push_back(c->name);
                }
                else if(iteration==5){
                    temp.push_back(c->ID);
                }
                else if(iteration==6){
                    temp.push_back("c");
                }
                else if(iteration==7){
                    string due_date=add7Days(date_today);
                    temp.push_back(due_date);
                }
                else if(iteration==8){
                    temp.push_back(cell);
                }
            }
            iteration++;
        }
        data.push_back(temp);
        
    }
    if(check==0) std::cout<<"Car not found"<<endl;
    
    file.close();
    ofstream outfile("car_database.csv");
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
void Customer::check_mine_rented(Customer* c){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    int check=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        string model;
        int price;
        string due_date;
        int iteration=0;
        int health;
        string final_date="";
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="0") break;
            }
            else if(iteration==4){
                if(cell!=c->name) break;
            }
            else if(iteration==5){
                if(cell!=c->ID) break;
            }
            else if(iteration==6){
                if(cell!="c") break;
            }
            else if(iteration==7){
                due_date=cell;
                check++;
                
                for(int i=0;i<8;i++){
                    final_date+=due_date[i];
                    if(i==1 || i==3) final_date+="-";
                }
                
            }   
            else if(iteration==8){
                health=stoi(cell);
                std::cout<<"Model: "<<model<<" Price: "<<(price/100)*health<<" Due Date: "<<final_date<<endl;
                break;
            }
            iteration++;
            
        }
    }
    if(check==0) std::cout<<"No cars rented"<<endl;
}



void Customer::check_available(void){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        string model;
        int price;
        int iteration=0;
        int health=0;
        while(getline(ss,cell,',')){
            
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                if(stoi(cell)>this->avg_customer_record){
                    break;
                }
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="1"){
                    break;
                }
            }
            else if(iteration==8){
                if(cell=="0"){
                    break;
                }
                health=stoi(cell);
                std::cout<<"Model: "<<model<<" Price: "<<(price/100)*health<<endl;
            }
            iteration++;
        }
    }
}


class Employee:public User{
    private:
        int employee_record;
    public:
        int get_employee_record(){
            return employee_record;
        }
        void set_employee_record(int record){
            this->employee_record=record;
        }
        void check_available(void);
        void check_mine_rented(Employee* c);
        void rent_a_car(Employee* c, string model,string date_today);
        int check_current_dues(Employee* c,string current_date);
        void clear_dues(Employee* c,string date,int health);
};
void Employee::check_available(void){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        string model;
        int price;
        int iteration=0;
        int health=0;
        while(getline(ss,cell,',')){
            
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                if(stoi(cell)>this->employee_record){
                    break;
                }
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="1"){
                    break;
                }
            }
            else if(iteration==8){
                if(cell=="0"){
                    break;
                }
                health=stoi(cell);
                std::cout<<"Model: "<<model<<" Price: "<<(price/100)*health*discount_to_employee<<endl;
            }
            iteration++;
        }
    }
}
void Employee::check_mine_rented(Employee* c){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    int check=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        string model;
        int price;
        string due_date;
        int iteration=0;
        int health;
        string final_date="";
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="0") break;
            }
            else if(iteration==4){
                if(cell!=c->name) break;
            }
            else if(iteration==5){
                if(cell!=c->ID) break;
            }
            else if(iteration==6){
                if(cell!="e") break;
            }
            else if(iteration==7){
                due_date=cell;
                check++;
                
                for(int i=0;i<8;i++){
                    final_date+=due_date[i];
                    if(i==1 || i==3) final_date+="-";
                }
                
            }   
            else if(iteration==8){
                health=stoi(cell);
                std::cout<<"Model: "<<model<<" Price: "<<(price/100)*health*discount_to_employee<<" Due Date: "<<final_date<<endl;
                break;
            }
            iteration++;
            
        }
    }
    if(check==0) std::cout<<"No cars rented"<<endl;
}
void Employee::rent_a_car(Employee* c, string model,string date_today){
    ifstream file("car_database.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    vector <vector <string>> data;
    string line;
    int check=0;
    int checker=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        
        
        while(getline(ss,cell,',')){
            if(iteration==0){
                if(cell==model){
                    check++;
                    temp.push_back(model);
                    marker=1;
                }
                else{
                    temp.push_back(cell);
                }
            }
            else if(marker==0){
                temp.push_back(cell);
            }
            else if(marker==1){
                if(iteration==1){
                    if(stoi(cell)>this->employee_record){
                        std::cout<<"Car cannot be rented due to your low customer record"<<endl;
                        marker=0;
                        check=1;
                    }
                    temp.push_back(cell);
                }
                else if(iteration==2){
                    temp.push_back(cell);

                }
                else if(iteration==3){
                    if(cell=="1"){
                        std::cout<<"Car is already rented"<<endl;
                        marker=0;
                        check=1;
                    }
                    temp.push_back("1");
                    checker++;
                }
                else if(iteration==4){
                    temp.push_back(c->name);
                }
                else if(iteration==5){
                    temp.push_back(c->ID);
                }
                else if(iteration==6){
                    temp.push_back("e");
                }
                else if(iteration==7){
                    string due_date=add7Days(date_today);
                    temp.push_back(due_date);
                }
                else if(iteration==8){
                    temp.push_back(cell);
                }
            }
            iteration++;
        }
        data.push_back(temp);
        
    }
    if(check==0) std::cout<<"Car not found"<<endl;
    if(checker) std::cout<<"Car has been rented"<<endl;

    
    file.close();
    ofstream outfile("car_database.csv");
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
int Employee::check_current_dues(Employee*c, string current_date){
    ifstream file("car_database.csv");
    int total_cost=0;
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return -1;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        int iteration=0;
        string model;
        int price=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                if(stoi(cell)>this->employee_record){
                    break;
                }
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="0"){
                    break;
                }
            }
            else if(iteration==4){
                if(cell!=c->name){
                    break;
                }
            }
            else if(iteration==5){
                if(cell!=c->ID){
                    break;
                }
            }
            else if(iteration==6){
                if(cell!="e"){
                    break;
                }
            }
            else if(iteration==7){
                if(dates_compare(cell,current_date)){
                    
                    total_cost+=daysBetweenDates(cell,current_date)*fine_per_day*discount_to_employee;
                    
                
                }
            }
            iteration++;
        }
    }
    return total_cost;
}
void Employee::clear_dues(Employee* c,string date, int health){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    vector <vector <string>> data;
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==0 || iteration==1 ||iteration==2) temp.push_back(cell);
            else if(iteration==3){
                if(cell=="0"){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back("0");
                    marker=1;
                }
            }
            else if(iteration==4){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!=c->name){
                        temp[3]="1";
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("0");
                    }
                    
                }
            }
            else if(iteration==5){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!=c->ID){
                        temp[3]="1";
                        temp[4]=c->name;
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("0");
                    }
                }
            }
            else if(iteration==6){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    if(cell!="e"){
                        temp[3]="1";
                        temp[4]=c->name;
                        temp[5]=c->ID;
                        temp.push_back(cell);
                        marker=0;
                    }
                    else{
                        temp.push_back("n");
                    }
                }
            }
            else if(iteration==7){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back("0");
                }
            }
            
            else if(iteration==8){
                if(marker==0){
                    temp.push_back(cell);
                }
                else{
                    temp.push_back(to_string(health));
                }
            }
            
            iteration++;
            
        }
        data.push_back(temp);
    }
    file.close();
    ofstream outfile("car_database.csv");
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
    
}
class Manager:public User{
    public:        
        void check_current_status();
        void remove_user(string filename,string ID);
        void remove_car(string filename, string model);
        void user_removed_car(string filename, string ID,string type);
        void user_update_cars(string filename, string ID, string quantity,int number, string type);
        void user_update(string filename, string ID,string quantity, int number,string type);
        void car_update(string filename, string model, string quantity, int number);

        
};
bool check_if_user_exists(string filename,string ID){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int iteration=0;
        while(getline(ss,cell,',')){
            if(iteration==1){
                if(cell==ID){
                    return true;
                }
                break;
            }
            iteration++;
        }
    }
}
void Push_New(string filename,string name, string ID, string password,int customer_record=15){
    ofstream outfile(filename,ios::app);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    outfile<<endl;
    outfile<<name<<","<<ID<<","<<password;
    if(filename=="customer_database.csv" || filename=="employee_database.csv") outfile<<","<<customer_record;
    
    outfile.close();
    return;
}
bool CheckValid_Customer(string filename, Customer* c) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int limit=2;
        int check=0;
        
        while (getline(ss, cell, ',')) {
            if(check==0){
                if(cell==c->name){
                    check=1;
                }
                else{
                    break;
                }
            }
            else if(check==1){
                if(cell==c->ID){
                    check=2;
                }
                else{
                    break;
                }
            }
            else if(check==2){
                if(cell==c->password){
                    check=3;
                }
                else{
                    break;
                }
            }else if(check==3){
                c->set_customer_record(stoi(cell));
                return true;
            }            
        }
    }

    file.close();
    return false;
}
bool CheckValid_Employee(string filename, Employee* c) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int limit=2;
        int check=0;
        
        while (getline(ss, cell, ',')) {
            if(check==0){
                if(cell==c->name){
                    check=1;
                }
                else{
                    break;
                }
            }
            else if(check==1){
                if(cell==c->ID){
                    check=2;
                }
                else{
                    break;
                }
            }
            else if(check==2){
                if(cell==c->password){
                    check=3;
                }
                else{
                    break;
                }
            }else if(check==3){
                c->set_employee_record(stoi(cell));
                return true;
            }            
        }
    }

    file.close();
    return false;
}
bool CheckValid_Manager(string filename, Manager* c) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        int limit=2;
        int check=0;
        
        while (getline(ss, cell, ',')) {
            if(check==0){
                if(cell==c->name){
                    check=1;
                }
                else{
                    break;
                }
            }
            else if(check==1){
                if(cell==c->ID){
                    check=2;
                }
                else{
                    break;
                }
            }
            else if(check==2){
                if(cell==c->password){
                    return true;
                }
                else{
                    break;
                }
            }     
        }
    }

    file.close();
    return false;
}
void UpdateRecord_Customer(string filename,Customer* c,int health,int fine){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    
    int decrease=0;
    if(health<20) decrease=decrease+0.5;
    if(health<40) decrease=decrease+0.5;
    if(health<60) decrease=decrease+0.5;
    if(health<80) decrease=decrease+0.5;
    if(health<100) decrease=decrease+0.5;
    if(fine>0) decrease=decrease+1;
    
    
    while(getline(file,line)){
        int iteration=0;
        int marker=0;
        stringstream ss(line);
        string cell;
        vector <string> temp;
        while(getline(ss,cell,',')){
            if(iteration==0){
                temp.push_back(cell);
            }
            else if(iteration==1){
                if(cell!=c->ID) marker=1;
                temp.push_back(cell);
            }
            else if(iteration==2) temp.push_back(cell);
            else if(iteration==3){
                if(marker==1) temp.push_back(cell);
                else {temp.push_back(to_string(stof(cell)-decrease));
                c->set_customer_record(stof(cell)-decrease);
                }
            }
            iteration++;
        }
        data.push_back(temp);

        
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
void UpdateRecord_Employee(string filename,Employee* c,int health,int fine){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    
    int decrease=0;
    if(health<20) decrease=decrease+0.5;
    if(health<40) decrease=decrease+0.5;
    if(health<60) decrease=decrease+0.5;
    if(health<80) decrease=decrease+0.5;
    if(health<100) decrease=decrease+0.5;
    if(fine>0) decrease=decrease+1;
    
    
    while(getline(file,line)){
        int iteration=0;
        int marker=0;
        stringstream ss(line);
        string cell;
        vector <string> temp;
        while(getline(ss,cell,',')){
            if(iteration==0){
                temp.push_back(cell);
            }
            else if(iteration==1){
                if(cell!=c->ID) marker=1;
                temp.push_back(cell);
            }
            else if(iteration==2) temp.push_back(cell);
            else if(iteration==3){
                if(marker==1) temp.push_back(cell);
                else {temp.push_back(to_string(stof(cell)-decrease));
                c->set_employee_record(stof(cell)-decrease);
                }
            }
            iteration++;
        }
        data.push_back(temp);

        
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
bool Car::Check_if_car_exists(string filename, Car* c){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return false;
    }
    string line;

    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        int iteration=0;
        int check=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                if(cell==c->model){
                    check++;
                }
            }
            else if(iteration==1){
                if(cell==to_string(c->minimum_requirement)){
                    check++;
                }
            }
            else if(iteration==2){
                if(cell==to_string(c->rent)){
                    check++;
                }
            }
            else if(iteration==8){
                if(cell==to_string(c->condition)){
                    check++;
                }
            }
            iteration++;
        }
        if(check==4){
            return true;
        }
    }
    
    file.close();
    return false;
}
void Car::Push_New_Car(string filename,Car* c){
    ofstream outfile(filename,ios::app);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    outfile<<endl;
    outfile<<c->model<<","<<to_string(c->minimum_requirement)<<","<<to_string(c->rent)<<","<<"0"<<","<<"0"<<","<<"0"<<","<<"n"<<","<<"0"<<","<<to_string(c->condition);
    outfile.close();
    return;

}
void LoginEmployee(Employee* c){
    system("cls");
    std::cout<<"Welcome, "<<c->name<<endl;
    bool exit=true;
    string model1;
    string date;
    int a;
    int health;
    int sample;
    while(exit){
        
        std::cout<<"Press"<<endl;
        std::cout<<"1 for Seeing All Available Cars"<<endl;
        std::cout<<"2 for Seeing Your Rented Cars"<<endl;
        std::cout<<"3 for Renting a Car"<<endl;
        std::cout<<"4 to check current dues"<<endl;
        std::cout<<"5 to clear dues"<<endl;
        std::cout<<"6 for checking your customer record"<<endl;
        std::cout<<"7 for logout"<<endl;
        int choice;
        std::cin>>choice;
        switch(choice){
            case 1:
                c->check_available();
                break; 
            case 2:
                c->check_mine_rented(c);
                break;
            case 3: 
                
                std::cout<<"Enter the model of the car you want to rent"<<endl;
                std::cin>>model1;
                
                std::cout<<"Enter the date today in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else c->rent_a_car(c,model1,date);
                break;
            case 4:

                std::cout<<"Enter the current date in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else a=c->check_current_dues(c,date);
                
                std::cout<<"Your current dues are: "<<a<<endl;
                break;
            case 5:
                std::cout<<"Enter the current date in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else{
                std::cout<<"On a scale of 1 to 100, enter the health of the car"<<endl;
                std::cin>>health;
                sample=c->check_current_dues(c,date);
                c->clear_dues(c,date,health);
                
                std::cout<<"Dues cleared, due amount payed: "<<sample<<endl;
                UpdateRecord_Employee("employee_database.csv",c,health,sample);
                std::cout<<"Employee Record Updated"<<endl;
                }
                

                break;
            case 6:
                std::cout<<"Employee Record: "<<c->get_employee_record()<<endl;
                break;
            case 7:
                std::cout<<"Logging Out"<<endl;
                exit=false;
                break;
            default:
                std::cout<<"Invalid Choice"<<endl;
                break;
        }
    }
}
void LoginCustomer(Customer* c){
    
    system("cls");
    std::cout<<"Welcome, "<<c->name<<endl;
    bool exit=true;
    string model1;
    string date;
    int a;
    int health;
    int sample;
    while(exit){
        
        std::cout<<"Press"<<endl;
        std::cout<<"1 for Seeing All Available Cars"<<endl;
        std::cout<<"2 for Seeing Your Rented Cars"<<endl;
        std::cout<<"3 for Renting a Car"<<endl;
        std::cout<<"4 to check current dues"<<endl;
        std::cout<<"5 to clear dues"<<endl;
        std::cout<<"6 for checking your customer record"<<endl;
        std::cout<<"7 for logout"<<endl;
        int choice;
        std::cin>>choice;
        switch(choice){
            case 1:
                c->check_available();
                break; 
            case 2:
                c->check_mine_rented(c);
                break;
            case 3: 
                
                std::cout<<"Enter the model of the car you want to rent"<<endl;
                std::cin>>model1;
                
                std::cout<<"Enter the date today in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else c->rent_a_car(c,model1,date);
                break;
            case 4:

                std::cout<<"Enter the current date in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else a=c->check_current_dues(c,date);
                
                std::cout<<"Your current dues are: "<<a<<endl;
                break;
            case 5:
                std::cout<<"Enter the current date in DDMMYYYY format"<<endl;
                std::cin>>date;
                if(isValidDateFormat(date)==false) cout<<"Invalid Date"<<endl;
                else{
                std::cout<<"On a scale of 1 to 100, enter the health of the car"<<endl;
                std::cin>>health;
                sample=c->check_current_dues(c,date);
                c->clear_dues(c,date,health);
                
                std::cout<<"Dues cleared, due amount payed: "<<sample<<endl;
                UpdateRecord_Customer("customer_database.csv",c,health,sample);
                std::cout<<"Customer Record Updated"<<endl;
                }
                

                break;
            case 6:
                std::cout<<"Customer Record: "<<c->get_customer_record()<<endl;
                break;
            case 7:
                std::cout<<"Logging Out"<<endl;
                exit=false;
                break;
            default:
                std::cout<<"Invalid Choice"<<endl;
                break;
        }
    }
    
    

}

void Manager::check_current_status(){
    ifstream file("car_database.csv");
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        int iteration=0;
        string model;
        int price;
        string name;
        string ID;
        string type;
        string due_date;
        int condition;
        int check=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
            }
            else if(iteration==1){
                
            }
            else if(iteration==2){
                price=stoi(cell);
            }
            else if(iteration==3){
                if(cell=="0"){
                    check++;
                }
            }
            else if(iteration==4){
                name=cell;
            }
            else if(iteration==5){
                ID=cell;
            }
            else if(iteration==6){
                type=cell;
            }
            else if(iteration==7){
                due_date=cell;
            }
            else if(iteration==8){
                condition=stoi(cell);
                if(type=="c") type="customer";
                else type="employee";


                if(check) {std::cout<<"Model: "<<model<<" Price: "<<price<<" Condition: "<<condition <<" Currently Not Rented"<<endl;}
                else {std::cout<<"Model: "<<model<<" Price: "<<price<<" Rented by: "<<name<<" ID: "<<ID<<" Type: "<<type<<" Due Date: "<<due_date<<" Condition: "<<condition<<endl;}
            }
            iteration++;
        }
    }

}
void Manager::remove_user(string filename, string ID){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    int check=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==1){
                if(cell!=ID){
                    temp.push_back(cell);
                }
                else{
                    marker=1;
                }
            }
            else{
                temp.push_back(cell);
            }
            iteration++;
        }
        if(marker==1) check++;
        else data.push_back(temp);
    }
    file.close();
    if(check){
        std::cout<<"User removed"<<endl;
    }
    else{
        std::cout<<"User not found"<<endl;
        return;
    }
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();

}
void Manager::remove_car(string filename, string model){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    int check=0;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                if(cell!=model){
                    temp.push_back(cell);
                }
                else{
                    marker=1;
                }
            }
            else{
                if(marker==1);
                else temp.push_back(cell);
            }
            iteration++;
        }
        if(marker) {check++;}
        else data.push_back(temp);
    }
    file.close();
    if(check){
        std::cout<< "Car removed"<<endl;
    }
    else{
        std::cout<<"Car not found"<<endl;
        return;
    }
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
void Manager::user_removed_car(string filename, string ID, string type){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    while(getline(file,line)){
        vector <string> temp;
        stringstream ss(line);
        string cell;
        
        int iteration=0;
        string model;
        string minimum_requirement;
        string price;

        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                model=cell;
                temp.push_back(cell);
            }
            else if(iteration==1){
                temp.push_back(cell);
            }
            else if(iteration==2){
                temp.push_back(cell);
            }
            else if(iteration==3){
                temp.push_back(cell);
            }
            else if(iteration==4){
                temp.push_back(cell);
            }
            else if(iteration==5){
                if(cell==ID){
                    marker=1;
                    temp.push_back("0");
                }
                else temp.push_back(cell);
                
            }
            else if(iteration==6){
                if(marker==0){
                    temp.push_back(cell);
                }
                else if(cell!=type){
                    temp[5]=ID;
                    temp.push_back(cell);
                    marker=0;
                }
                
                if(cell==type && marker==1){
                    temp[3]="0";
                    temp[4]="0";
                    temp.push_back("n");
                    marker=1;
                    
                }
                
            }
            else if(iteration==7){
                if(marker==0)temp.push_back(cell);
                else temp.push_back("0");
            }
            else if(iteration==8){
                temp.push_back(cell);
            }
            iteration++;
        }
    data.push_back(temp);
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
    
    

}

void Manager::user_update_cars(string filename, string ID, string quantity,int number, string type){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    while (getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==5){
                if(cell==ID){
                    marker=1;
                }
            }
            temp.push_back(cell);
            iteration++;
        }
        if(marker==1){
            if(number==0){
                temp[4]=quantity;
            }
            
        }
        data.push_back(temp);
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
}
void Manager::user_update(string filename, string ID,string quantity, int number,string type){
    //number 0-> name
    //number 1-> password
    //number 2-> customer record
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    while (getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==1){
                if(cell==ID){
                    marker++;
                }
            }
            
            temp.push_back(cell);
            iteration++;
        }
        if(marker==1){
            if(number==0){
                temp[0]=quantity;
            }
            else if(number==1){
                temp[2]=quantity;
            }
            else if(number==2){
                temp[3]=quantity;
            }
        }
        data.push_back(temp);
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
    if(number==0) {
        std::cout<<"Name Updated"<<endl;
        user_update_cars("car_database.csv",ID,quantity,0,type);
    }
    else if(number==1) std::cout<<"Password Updated"<<endl;
    else if(number==2) std::cout<<"Customer Record Updated"<<endl;
}
void Manager::car_update(string filename, string model, string quantity, int number){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    string line;
    vector <vector <string>> data;
    while(getline(file,line)){
        stringstream ss(line);
        string cell;
        vector <string> temp;
        int iteration=0;
        int marker=0;
        while(getline(ss,cell,',')){
            if(iteration==0){
                if(cell==model){
                    marker++;
                }
            }
            temp.push_back(cell);
            iteration++;
        }
        if(marker==1){
            if(number==0){
                temp[1]=quantity;
            }
            else if(number==1){
                temp[2]=quantity;
            }
            else if(number==2){
                temp[8]=quantity;
            }
        }
        data.push_back(temp);
    }
    file.close();
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr<<"Error: Unable to open file."<<endl;
        return;
    }
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[i].size();j++){
            outfile<<data[i][j];
            if(j!=data[i].size()-1) outfile<<",";
        }
        if(i!=data.size()-1) outfile<<endl;
    }
    outfile.close();
    if(number==0) std::cout<<"Minimum Requirement Updated"<<endl;
    else if(number==1) std::cout<<"Rent Updated"<<endl;
    else if(number==2) std::cout<<"Condition Updated"<<endl;

}
void Login_Manager(Manager* c){
    system("cls");
    std::cout<<"Welcome, "<<c->name<<endl;
    bool exit = true;
    while(exit){
        std::cout<<"Press"<<endl;
        std::cout<<"1 for seeing the current status for all cars"<<endl;
        std::cout<<"2 for adding customer/employee/car"<<endl;
        std::cout<<"3 for removing customer/employee/car"<<endl;
        std::cout<<"4 for updating customer/employee/car"<<endl;
        std::cout<<"5 for logout"<<endl;
        int choice;
        std::cin>>choice;
        int choice1;
        
        switch(choice){
            case 1:
                c->check_current_status();
                break;
            case 2:
                std::cout<<"Press"<<endl;
                std::cout<<"1 for adding customer"<<endl;
                std::cout<<"2 for adding employee"<<endl;
                std::cout<<"3 for adding car"<<endl;
                std::cout<<"4 to go back"<<endl;
                std::cin>>choice1;
                if(choice1==1){
                    Customer c;
                    std::cout<<"Enter Customer name"<<endl;
                    std::cin>>c.name;
                    std::cout<<"Enter Customer ID"<<endl;
                    std::cin>>c.ID;
                    std::cout<<"Enter Customer password"<<endl;
                    std::cin>>c.password;
                    if(check_if_user_exists("customer_database.csv",c.ID)==false){
                        Push_New("customer_database.csv",c.name,c.ID,c.password,c.get_customer_record());
                        std::cout<<"Customer Pushed"<<endl;
                    }
                    else std::cout<<"User already exists"<<endl;
                }
                else if(choice1==2){
                    Employee e;
                    std::cout<<"Enter Employee name"<<endl;
                    std::cin>>e.name;
                    std::cout<<"Enter Employee ID"<<endl;
                    std::cin>>e.ID;
                    std::cout<<"Enter Employee password"<<endl;
                    std::cin>>e.password;
                    if(check_if_user_exists("employee_database.csv",e.ID)==false){
                        Push_New("employee_database.csv",e.name,e.ID,e.password);
                        std::cout<<"Employee Pushed"<<endl;
                    }
                    else std::cout<<"User already exists"<<endl;
                }
                
                else if(choice1==3){
                    Car c;
                    std::cout<<"Enter the model of the car"<<endl;
                    std::cin>>c.model;
                    std::cout<<"Enter the minimum customer record required for the car"<<endl;
                    std::cin>>c.minimum_requirement;
                    std::cout<<"Enter the rent of the car"<<endl;
                    std::cin>>c.rent;
                    std::cout<<"Entet the condition of the car on a scale of 1 to 100"<<endl;
                    std::cin>>c.condition;
                    if(c.Check_if_car_exists("car_database.csv",&c)==false){
                        c.Push_New_Car("car_database.csv",&c);
                        std::cout<<"Car pushed"<<endl;
                    }
                    else std::cout<<"Car already exists"<<endl;
                }
                else if(choice1==4){
                    std::cout<<"Going back"<<endl;
                    break;
                }
                else{
                    std::cout<<"Invalid input"<<endl;
                }
                break; 
            case 3:
                std::cout<<"Press"<<endl;
                std::cout<<"1 for removing customer"<<endl;
                std::cout<<"2 for removing employee"<<endl;
                std::cout<<"3 for removing car"<<endl;
                std::cout<<"4 to go back"<<endl;
                std::cin>>choice1;
                if(choice1==1){
                    std::cout<<"Enter the ID of the customer you want to remove"<<endl;
                    string ID;
                    std::cin>>ID;
                    c->remove_user("customer_database.csv",ID);
                    c->user_removed_car("car_database.csv",ID,"c");


                }
                else if(choice1==2){
                    std::cout<<"Enter the ID of the employee you want to remove"<<endl;
                    string ID;
                    std::cin>>ID;
                    c->remove_user("employee_database.csv",ID);
                    c->user_removed_car("car_database.csv",ID,"e");
                }
                else if(choice1==3){
                    std::cout<<"Enter the model of the car you want to remove"<<endl;
                    string model;
                    std::cin>>model;
                    
                    c->remove_car("car_database.csv",model);  
                                     
                }
                else if(choice1==4){
                    std::cout<<"Going back"<<endl;
                    break;
                }
                else{
                    std::cout<<"Invalid input"<<endl;
                }
                break;
                
            case 4:
                std::cout<<"Press"<<endl;
                std::cout<<"1 for updating a customer"<<endl;
                std::cout<<"2 for updating an employee"<<endl;
                std::cout<<"3 for updating car"<<endl;
                std::cout<<"4 for going back"<<endl;
                std::cin>>choice1;
                if(choice1==1){
                    std::cout<<"Enter the ID of the customer you want to update"<<endl;
                    string ID;
                    std::cin>>ID;
                    std::cout<<"Press"<<endl;
                    bool exit2=true;
                    while(exit2){
                        std::cout<<"1 for updating name"<<endl;
                        std::cout<<"2 for updating password"<<endl;
                        std::cout<<"3 for updating customer record"<<endl;
                        std::cout<<"4 for going back"<<endl;
                        int choice2;
                        std::cin>>choice2;
                        if(choice2==1){
                            std::cout<<"Enter the new name"<<endl;
                            string name;
                            std::cin>>name;
                            c->user_update("customer_database.csv",ID,name,0,"c");
                            
                        }
                        else if(choice2==2){
                            std::cout<<"Enter the new password"<<endl;
                            string password;
                            std::cin>>password;
                            c->user_update("customer_database.csv",ID,password,1,"c");
                            
                        }
                        else if(choice2==3){
                            std::cout<<"Enter the new customer record"<<endl;
                            string record;
                            std::cin>>record;
                            c->user_update("customer_database.csv",ID,record,2,"c");

                        }
                        else if(choice2==4){
                            std::cout<<"Going back"<<endl;
                            exit2=false;
                            break;
                        }
                        
                    }
                }
                else if(choice1==2){
                    std::cout<<"Enter the ID of the employee you want to update"<<endl;
                    string ID;
                    std::cin>>ID;
                    std::cout<<"Press"<<endl;
                    bool exit2=true;
                    while(exit2){
                        std::cout<<"1 for updating name"<<endl;
                        std::cout<<"2 for updating password"<<endl;
                        std::cout<<"3 for updating customer record"<<endl;
                        std::cout<<"4 for going back"<<endl;
                        int choice2;
                        std::cin>>choice2;
                        if(choice2==1){
                            std::cout<<"Enter the new name"<<endl;
                            string name;
                            std::cin>>name;
                            c->user_update("employee_database.csv",ID,name,0,"e");
                            
                        }
                        else if(choice2==2){
                            std::cout<<"Enter the new password"<<endl;
                            string password;
                            std::cin>>password;
                            c->user_update("employee_database.csv",ID,password,1,"e");
                            
                        }
                        else if(choice2==3){
                            std::cout<<"Enter the new customer record"<<endl;
                            string record;
                            std::cin>>record;
                            c->user_update("employee_database.csv",ID,record,2,"e");

                        }
                        else if(choice2==4){
                            std::cout<<"Going back"<<endl;
                            exit2=false;
                            break;
                        }
                        else{
                            std::cout<<"Invalid input"<<endl;
                            // break;
                            exit2=false;
                            break;
                        }
                        
                    }
                }
                else if(choice1==3){
                    std::cout<<"Enter the model of the car you want to update"<<endl;
                    string model;
                    std::cin>>model;
                    std::cout<<"Press"<<endl;
                    bool exit2=true;
                    while(exit2){
                        std::cout<<"1 for updating minimum customer record"<<endl;
                        std::cout<<"2 for updating rent"<<endl;
                        std::cout<<"3 for updating condition"<<endl;
                        std::cout<<"4 for going back"<<endl;
                        int choice2;
                        std::cin>>choice2;
                        if(choice2==1){
                            std::cout<<"Enter the new minimum customer record"<<endl;
                            string record;
                            std::cin>>record;
                            c->car_update("car_database.csv",model,record,0);
                        }
                        else if(choice2==2){
                            std::cout<<"Enter the new rent"<<endl;
                            string rent;
                            std::cin>>rent;
                            c->car_update("car_database.csv",model,rent,1);
                        }
                        else if(choice2==3){
                            std::cout<<"Enter the new condition"<<endl;
                            string condition;
                            std::cin>>condition;
                            c->car_update("car_database.csv",model,condition,2);
                        }
                        else if(choice2==4){
                            std::cout<<"Going back"<<endl;
                            exit2=false;
                            break;
                        }
                        else{
                            std::cout<<"Invalid input"<<endl;
                            // break;
                            exit2=false;
                            break;
                        
                        }
                    }
                }
                else if(choice1==4){
                    std::cout<<"Going back"<<endl;
                    break;
                }
                
                else{
                    std::cout<<"Invalid input"<<endl;
                }
                break;
                
            case 5:
                std::cout<<"Logging Out"<<endl;
                exit=false;
                break;
            default:
                std::cout<<"Invalid Choice"<<endl;
                break;
        }
    }

}

int main() {
    std::cout<<"Welcome to the Car Rental System"<<endl;
    bool exit=false;
    while(exit==false){    
    std::cout<<"Press 1 for Customer"<<endl;
    std::cout<<"Press 2 for Employee"<<endl;
    std::cout<<"Press 3 for Manager"<<endl; 
    std::cout<<"Press 4 for exiting"<<endl;  
    int choice;
    std::cin>>choice;
    if(choice==1){
        std::cout<<"Press 1 for New Customer"<<endl;
        std::cout<<"Press 2 for Existing Customer"<<endl;
        int choice1;
        std::cin>>choice1;
        if(choice1==1){
            Customer c;
            std::cout<<"Enter your name"<<endl;
            std::cin>>c.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>c.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>c.password;
            if(check_if_user_exists("customer_database.csv",c.ID)==false){
            Push_New("customer_database.csv",c.name,c.ID,c.password,c.get_customer_record());
            LoginCustomer(&c);
            }
            else std::cout<<"User already exists"<<endl;
        }
        else if(choice1==2){
            Customer c;
            std::cout<<"Enter your name"<<endl;
            std::cin>>c.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>c.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>c.password;
            if(CheckValid_Customer("customer_database.csv",&c)){
                LoginCustomer(&c);
                
            }
            else{
                std::cout<<"Invalid Credentials"<<endl;
                
            }
        }
    }
    else if(choice==2){
        std::cout<<"Press 1 for New Employee"<<endl;
        std::cout<<"Press 2 for Existing Employee"<<endl;
        int choice;
        std::cin>>choice;
        if(choice==1){
            Employee e;
            std::cout<<"Enter your name"<<endl;
            std::cin>>e.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>e.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>e.password;
            if(check_if_user_exists("employee_database.csv",e.ID)==false){
                Push_New("employee_database.csv",e.name,e.ID,e.password);
                LoginEmployee(&e);
            }
            else std::cout<<"User already exists"<<endl;
            
            
        }
        else if(choice==2){
            Employee e;
            std::cout<<"Enter your name"<<endl;
            std::cin>>e.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>e.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>e.password;
            if(CheckValid_Employee("employee_database.csv",&e)){
                LoginEmployee(&e);
                
            }
            else{
                std::cout<<"Invalid Credentials"<<endl;
                
            }
            
        }
    }
    else if(choice==3){
        std::cout<<"Press 1 for New Manager"<<endl;
        std::cout<<"Press 2 for Existing Manager"<<endl;
        int choice;
        std::cin>>choice;
        if(choice==1){
            Manager c;
            std::cout<<"Enter your name"<<endl;
            std::cin>>c.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>c.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>c.password;
            if(check_if_user_exists("manager_database.csv",c.ID)==false){
                Push_New("manager_database.csv",c.name,c.ID,c.password);
                Login_Manager(&c);
            }
            else std::cout<<"User already exists"<<endl;
            
        }
        else if(choice==2){
            Manager c;
            std::cout<<"Enter your name"<<endl;
            std::cin>>c.name;
            std::cout<<"Enter your ID"<<endl;
            std::cin>>c.ID;
            std::cout<<"Enter your password"<<endl;
            std::cin>>c.password;
            if(CheckValid_Manager("manager_database.csv",&c)){
                Login_Manager(&c);
                
            }
            else{
                std::cout<<"Invalid Credentials"<<endl;
                
            }
        }
        } 
    else if(choice==4){
        std::cout<<"Thank you for visiting the rental system"<<endl;
        exit=true;
    }
    else{
        std::cout<<"Invalid choice, try again"<<endl;
    }
    }
    return 0;
}