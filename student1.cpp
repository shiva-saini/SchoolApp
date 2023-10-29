#include<string> 
#include<fstream>
#include<iostream>
#include<vector> 
#include<sstream>

using namespace std;


bool opn = false;

class StudentRecord{
    public:
    string Id;
    string FirstName;
    string LastName;
    int Age;
    string PhoneNumber;
    double Gpa;
    StudentRecord(string id,string firstName,string lastName,int age,string phone,double gpa){
        Id = id;
        FirstName = firstName;
        LastName = lastName;
        Age = age;
        PhoneNumber = phone;
        Gpa = gpa;
    }
    
    void display(){
        cout<<" Student ID : " << Id << endl;
        cout<<" First Name : " << FirstName << endl;
        cout<<" Last Name : " << LastName << endl;
        cout<<" Age :" << Age << endl;
        cout<<" Phone Number : " << PhoneNumber << endl;
        cout<<" Gpa : " << Gpa << endl;
        cout<<endl;
    }
};



void writeStudentToCSV(const std::string& filename, const StudentRecord& student) {
    std::ofstream file(filename, std::ios::app); // Open the file in append mode
    // if(opn == false){
    //     file<<"\n";
    //     opn = true;
    // }
    if (file.is_open()) {
        // Write student details to the CSV file
        file << student.Id << "," << student.LastName << "," << student.FirstName << "," << student.Age << "," << student.PhoneNumber << "," << student.Gpa << "\n";

        // Close the file
        file.close();
        std::cout << "Student details written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open the file " << filename << std::endl;
    }
}



vector<StudentRecord> giveAllStudentsDetails(){
    ifstream inputFile;
    inputFile.open("data.csv");
    string line;
    vector<StudentRecord> allStudents;
    while(getline(inputFile,line)){
         string studentId;
         string firstName;
         string lastName;
         int age;
         string phoneNumber;
         double gpa;
         string tempString;
        stringstream inputString(line);
        getline(inputString,studentId,',');
        getline(inputString,lastName,',');
        getline(inputString,firstName,',');
        getline(inputString,tempString,',');
        age = atoi(tempString.c_str());
        getline(inputString,phoneNumber,',');
        tempString = "";
        getline(inputString,tempString,',');
        gpa = atof(tempString.c_str());
        StudentRecord student(studentId,firstName,lastName,age,phoneNumber,gpa);
        allStudents.push_back(student);
        line = "";  
    }

   return allStudents;
}

void showStudentDetails(){
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    for(auto student : allStudents){
        student.display();
    }
}


void addStudentDetails(StudentRecord student){
    std::string filename = "data.csv";
    // StudentRecord student1("10000005","Shiva","Saini",23,"9384756123",7.82);
    // StudentRecord student2("10000006","Kartik","Saini",15,"9384756124",7);
    // StudentRecord student3("1000007","Chintu","Saini",15,"9384756125",9);
    writeStudentToCSV(filename, student);
    // writeStudentToCSV(filename, student2);
    // writeStudentToCSV(filename, student3);
}

void deleteStudentById(string id){
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    vector<StudentRecord> allUpdatedStudents;
     
    for(auto student:allStudents){
        if(student.Id != id){
         allUpdatedStudents.push_back(student);
        }
    }

    std::string filename = "data.csv";
    std::ofstream file(filename, std::ios::out);
    for(auto student:allUpdatedStudents){
        addStudentDetails(student);
    }
}
int main(){
    showStudentDetails();
    StudentRecord student("1000008","Donald","Trump",70,"0478367452",9.00);
    addStudentDetails(student);
    showStudentDetails();
    deleteStudentById("10000001");
    showStudentDetails();
}