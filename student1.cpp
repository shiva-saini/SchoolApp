#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
// #include "./headerfiles/myfunctions.h"
using namespace std;

//  to automatically update the id of a student when deleted we can use index as id in vector of StudentRecord
//  if we are using string for id we have to make a function to increase or decrease string by one
class StudentRecord
{
private:
    string Id;
    string FirstName;
    string LastName;
    int Age;
    string PhoneNumber;
    double Gpa;

public:
    StudentRecord()
    {
    }
    StudentRecord(string id, string firstName, string lastName, int age, string phone, double gpa)
    {
        this->Id = id;
        this->FirstName = firstName;
        this->LastName = lastName;
        this->Age = age;
        this->PhoneNumber = phone;
        this->Gpa = gpa;
    }
    string getFirst_name()
    {
        return this->FirstName;
    }
    void setFirst_name(string first_name)
    {
        this->FirstName = first_name;
    }
    string getLast_name()
    {
        return this->LastName;
    }

    void setLast_name(string last_name)
    {
        this->LastName = last_name;
    }

    string getId()
    {
        return this->Id;
    }

    void setId(string id)
    {
        this->Id = id;
    }
    int getAge()
    {
        return this->Age;
    }

    void setAge(int age)
    {
        this->Age = age;
    }
    string getPhone()
    {
        return this->PhoneNumber;
    }

    void setPhone(string phone)
    {
        this->PhoneNumber = phone;
    }

    double getGpa()
    {
        return this->Gpa;
    }

    void setGpa(double gpa)
    {
        this->Gpa = gpa;
    }
    void display()
    {
        cout << " Student ID : " << this->getId() << endl;
        cout << " First Name : " << this->getFirst_name() << endl;
        cout << " Last Name : " << this->getLast_name() << endl;
        cout << " Age :" << this->getAge() << endl;
        cout << " Phone Number : " << this->getPhone() << endl;
        cout << " Gpa : " << this->getGpa() << endl;
        cout << endl;
    }
};
void writeStudentToCSV(const std::string &filename, StudentRecord &student)
{
    std::ofstream file(filename, std::ios::app); // Open the file in append mode
    // if(opn == false){
    //     file<<"\n";
    //     opn = true;
    // }
    if (file.is_open())
    {
        // Write student details to the CSV file
        file << student.getId() << "," << student.getLast_name() << "," << student.getFirst_name() << "," << student.getAge() << "," << student.getPhone() << "," << student.getGpa() << "\n";

        // Close the file
        file.close();
        std::cout << "Student details written to " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open the file " << filename << std::endl;
    }
}
vector<StudentRecord> giveAllStudentsDetails()
{
    ifstream inputFile;
    inputFile.open("data.csv");
    string line;
    vector<StudentRecord> allStudents;
    while (getline(inputFile, line))
    {
        string studentId;
        string firstName;
        string lastName;
        int age;
        string phoneNumber;
        double gpa;
        string tempString;
        stringstream inputString(line);
        getline(inputString, studentId, ',');
        getline(inputString, lastName, ',');
        getline(inputString, firstName, ',');
        getline(inputString, tempString, ',');
        age = atoi(tempString.c_str());
        getline(inputString, phoneNumber, ',');
        tempString = "";
        getline(inputString, tempString, ',');
        gpa = atof(tempString.c_str());
        StudentRecord student(studentId, firstName, lastName, age, phoneNumber, gpa);
        allStudents.push_back(student);
        line = "";
    }

    return allStudents;
}

void showStudentDetails()
{
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    for (auto student : allStudents)
    {
        student.display();
    }
}

void addStudentDetails(StudentRecord student)
{
    std::string filename = "data.csv";
    // addStudent(student,filename);
    writeStudentToCSV(filename, student);
}

void deleteStudentById(string id)
{
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    vector<StudentRecord> allUpdatedStudents;

    for (auto student : allStudents)
    {
        if (student.getId() == id)
        {
            continue;
        }
        if (student.getId() < id)
        {
            allUpdatedStudents.push_back(student);
        }
        else
        {
            int x = atoi(student.getId().c_str());
            x -= 1;
            student.setId(to_string(x));
            allUpdatedStudents.push_back(student);
        }
    }

    std::string filename = "data.csv";
    std::ofstream file(filename, std::ios::out);
    for (auto student : allUpdatedStudents)
    {
        addStudentDetails(student);
    }
}

void updateStudentInfo(std::vector<StudentRecord> &students, StudentRecord updatedStudent)
{
    for (StudentRecord &student : students)
    {
        if (student.getId() == updatedStudent.getId())
        {
            student.setId(updatedStudent.getId());
            student.setFirst_name(updatedStudent.getFirst_name());
            student.setLast_name(updatedStudent.getLast_name());
            student.setAge(updatedStudent.getAge());
            break;
        }
    }

    std::string filename = "data.csv";
    std::ofstream file(filename, std::ios::out);
    for (auto student : students)
    {
        addStudentDetails(student);
    }
}

void updateStudent(StudentRecord updatedStudent)
{
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    for (auto student : allStudents)
    {
        if (student.getId() == updatedStudent.getId())
        {
            updateStudentInfo(allStudents, updatedStudent);
            break;
        }
    }
}

void findStudent(string &first_name, string &last_name)
{
    cout << "Hello" << endl;
    vector<StudentRecord> allStudents = giveAllStudentsDetails();
    for (auto student : allStudents)
    {
        cout << student.getFirst_name() << " - " << student.getPhone() << endl;
        if (student.getFirst_name() == last_name && student.getLast_name() == first_name)
        {
            cout << "THis is the data searched student" << endl;
            cout << endl;
            student.display();
            cout << endl;
            break;
        }
    }
}

StudentRecord inputDetails()
{
    string id;
    string first_name;
    string last_name;
    int age;
    string phone;
    double gpa;
    cout << "Enter student Id : " << endl;
    cin >> id;
    cout << "Enter First Name : " << endl;
    cin >> first_name;
    cout << "Enter Last Name : " << endl;
    cin >> last_name;
    cout << "Enter age : " << endl;
    cin >> age;
    cout << "Enter Phone : " << endl;
    cin >> phone;
    cout << "Enter Gpa : " << endl;
    cin >> gpa;
    StudentRecord student(id, last_name, first_name, age, phone, gpa);
    return student;
}

StudentRecord inputDetailsToUpdate()
{
    string id;
    string first_name;
    string last_name;
    int age;
    cout << "Enter student Id : " << endl;
    cin >> id;
    cout << "Enter First Name : " << endl;
    cin >> first_name;
    cout << "Enter Last Name : " << endl;
    cin >> last_name;
    cout << "Enter age : " << endl;
    cin >> age;
    StudentRecord student(id, last_name, first_name, age, "", 0.00);
    return student;
}

int main()
{
   bool f = false;
   while(1){

 
    cout << "1 . Help Menu " << endl;
    cout << "2 . Add Student " << endl;
    cout << "3 . Delete Student by id" << endl;
    cout << "4 . Modify Student by Name and Age " << endl;
    cout << "5 . Search Student by name " << endl;
    cout << "6 . Show all the students " << endl;
    cout << "7 . Exit " << endl;
    cout << endl;
    cout << endl;
    cout << "Enter your choice" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        // help menu
        cout << "This is help menu" << endl;
        break;
    case 2:
        addStudentDetails(inputDetails());
        break;
    case 3:
    {
        string id;
        cout << "Enter student id : " << endl;
        cin >> id;
        deleteStudentById(id);
        cout << "Student Deleted successfully" << endl;
    }

    break;
    case 4:
    {
        updateStudent(inputDetailsToUpdate());
        cout << "Student updated successfully" << endl;
    }
    break;
    case 5:
    {
        string first_name;
        string last_name;
        cout << "Enter first name" << endl;
        cin >> first_name;
        cout << "Enter last name" << endl;
        cin >> last_name;
        findStudent(first_name, last_name);
    }
    break;

    case 6:
        showStudentDetails();
        break;
    case 7:
        f = true;
        exit(0);
        break;
    default:
        break;
    }

    if(f){
        break;
    }
    }
}