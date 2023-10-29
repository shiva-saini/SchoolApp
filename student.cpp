#include<iostream>
#include<fstream> // to read our file
#include<sstream> // to read string word by word
#include<string> 
#include<vector>
using namespace std;

class StudentRecord{
   public:
   string Id;
   string FirstName;
   string LastName;
   string PhoneNumber;
   int Age;
   double Gpa;
   StudentRecord(string id,string firstName,string lastName,int age,string phone,double gpa){
    Id = id;
    FirstName = firstName;
    LastName = lastName;
    PhoneNumber = phone;
    Age = age;
    Gpa = gpa;
   }
   void display(){
    cout<<" Student ID : " << Id << endl;
    cout<<" First Name : " << FirstName << endl; 
    cout<<" Last Name : " << LastName << endl; 
    cout<<" Phone Number : " << PhoneNumber << endl; 
    cout<<" Age          : " << Age << endl;
    cout<<" Gpa          : " << Gpa << endl;
    cout<<endl;
   }
};


int main(){
    cout<<"Hello World here"<<endl;
    vector<StudentRecord> studentRecodrs;
    ifstream inputFile;
    inputFile.open("data.csv");
    string line;
    getline(inputFile,line);
    line = "";
    while(getline(inputFile,line)){
        string studentId;
        string firstname;
        string lastname;
        int age;
        string phone;
        double gpa;
        string tempString = "";
        stringstream inputString(line);
        getline(inputString,studentId,',');
        getline(inputString,lastname,',');
        getline(inputString,firstname,',');
        getline(inputString,tempString,',');
        age = atoi(tempString.c_str());
        getline(inputString,phone,',');
        tempString = "";
        getline(inputString,tempString,',');
        gpa = atof(tempString.c_str());
        StudentRecord student(studentId,firstname,lastname,age,phone,gpa);
        studentRecodrs.push_back(student);
    }
    for(auto student:studentRecodrs){
        student.display();
    }
    return 0;
}