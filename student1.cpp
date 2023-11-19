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










//back-end part





























#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class StudentRecord
{
private:
	string Id;
	string FirstName;
	string LastName;
	int Age;
	string PhoneNumber;
	double Gpa = 0.0;


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

class StudentRepo {
		public:
		void writeStudentToCSV(const std::string& filename, StudentRecord& student)
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
		void addStudentDetails(StudentRecord student) {

			std::string filename = "data.csv";
			//StudentRecord student = inputDetails(); // student details will come from front-middle ware
			//and we will take that input here as argument and then pass to writeStudentToCSV file
			// addStudent(student,filename);
			writeStudentToCSV(filename, student);

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
		void deleteStudentById(string id)
		{
			if (id == "")
			{
				cout << "Enter a valid id" << endl;
				return;
			}
			vector<StudentRecord> allStudents = giveAllStudentsDetails();
			vector<StudentRecord> allUpdatedStudents;

			for (StudentRecord student : allStudents)
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
			for (StudentRecord student : allUpdatedStudents)
			{
				addStudentDetails(student);
			}
		}
		void updateStudentInfo(std::vector<StudentRecord>& students, StudentRecord& updatedStudent)
		{
			for (StudentRecord& student : students)
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
			for (StudentRecord student : students)
			{
				addStudentDetails(student);
			}
		}
		void updateStudent(StudentRecord updatedStudent)
		{
			
			vector<StudentRecord> allStudents = giveAllStudentsDetails();
			cout << allStudents.size() << endl;
			bool f = false;
			for (StudentRecord& student : allStudents)
			{
				cout << student.getId() << endl;
				if (student.getId() == updatedStudent.getId())
				{
					updateStudentInfo(allStudents, updatedStudent);
					f = true;
					break;
				}

			}

			if (f == false) {

				cout << "Student with this id doesn't exist in our databse" << endl;
				return;

			}else 
				cout << "Student updated successfully" << endl;
		}
		void findStudent(string& first_name, string& last_name)
		{


			if (first_name == "" || last_name == "")
			{
				cout << "Name cannot be empty!!" << endl;
				return;
			}
			vector<StudentRecord> allStudents = giveAllStudentsDetails();
			string fName = "", lName = "";
			for (int i = 0; i < first_name.size(); i++)
			{
				fName += tolower(first_name[i]);
			}
			for (int i = 0; i < last_name.size(); i++)
			{
				lName += tolower(last_name[i]);
			}

			vector<StudentRecord> searchedStudents;
			int flag = 0;
			for (StudentRecord student : allStudents)
			{
				string fNameDb = "";
				string lNameDb = "";
				for (int i = 0; i < student.getFirst_name().size(); i++)
				{
					fNameDb += tolower(student.getFirst_name()[i]);
				}
				for (int i = 0; i < student.getLast_name().size(); i++)
				{
					lNameDb += tolower(student.getLast_name()[i]);
				}

				if (fNameDb == fName && lNameDb == lName)
				{
					/*searchedStudents.push_back(student);*/
					flag = 1;

					student.display();
					cout << endl;

				}
			}

			if (!flag)
			{
				cout << "No student found with such name" << endl;
				return;
			}
			/*
			* front-end will check this
			if (!flag)
			{
				cout << "No student found with such name" << endl;
				return ;
			}
			else {

			}
			*/
		}
		void showStudentDetails()
		{
			vector<StudentRecord> allStudents = giveAllStudentsDetails();
			if (allStudents.size() == 0)
			{
				cout << "No records found!!" << endl;
			}
			else
			{
				for (StudentRecord student : allStudents)
				{
					student.display();
				}
			}

		}
};
//this is front-end part

StudentRecord inputDetailsToUpdate()
	{
		string id;
		string first_name;
		string last_name;
		int age;
		string phone = "";
		double gpa = 0.00;
		cout << "Enter student Id : " << endl;
		cin >> id;
		cout << "Enter First Name : " << endl;
		cin >> first_name;
		cout << "Enter Last Name : " << endl;
		cin >> last_name;
		cout << "Enter age : " << endl;
		cin >> age;
		StudentRecord student(id, last_name, first_name, age, phone,gpa);
		return student;
	}
void deleteStudentById1() {

	string id;
	cout << "Enter student id : " << endl;
	cin >> id;
	StudentRepo studentrepo;
	// here middle ware pass the student's id and we will call  deleteStudentById(id) function
	studentrepo.deleteStudentById(id);
	cout << "Student Deleted successfully" << endl;
}
string generateId()
{
	StudentRepo studentrepo;
	vector<StudentRecord> allStudents = studentrepo.giveAllStudentsDetails();
	long long int n = allStudents.size();
	int id = n > 0 ? stoi(allStudents[n - 1].getId()) : 0;
	return to_string(id + 1);
}

StudentRecord inputDetails()
{
	string id = generateId();
	string first_name;
	string last_name;
	int age;
	string phone;
	double gpa;
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


// Main function
int main()
{
	bool f = false;
	StudentRecord student;
	StudentRepo studentrepo;
	while (1) {

		cout << "-------------------------------------Welcome to School App-----------------------------------" << endl;
		cout << endl;
		cout << endl;
		cout << "Enter 0 to enter the help menu" << endl;
		cout << endl;
		int help;
		cin >> help;
		if (help == 0)
		{
			cout << "----HELP MENU-----" << endl;
			cout << "1 . Add Student " << endl;
			cout << "2 . Delete Student by id" << endl;
			cout << "3 . Modify Student by Name and Age " << endl;
			cout << "4 . Search Student by name " << endl;
			cout << "5 . Show all the students " << endl;
			cout << "6 . Exit " << endl;
			cout << "Enter your choice" << endl;
			int choice;
			cin >> choice;
			switch (choice)
			{
			case 1:
				//this input details will be called at the front - end side and front - end will send this to middleware and then middle ware will call it and pass student object
				studentrepo.addStudentDetails(inputDetails());
				break;
			case 2:
			{
				//first front-end will take id , which has to be deleted and then front-end will pass this id to middle ware the middle ware will call the function and pass this id to that function
				deleteStudentById1();
				cout << "Student Deleted successfully" << endl;
			}

			break;
			case 3:
			{   
				// front - end will take the data to be updated and then pass it to middle ware then middle ware will call this function and pass the student's data which has to be updated
				studentrepo.updateStudent(inputDetailsToUpdate());
				
			}
			break;
			case 4:
			{
				// front-end will take data from the user and pass it to middleware and then middle ware will pass this data to back-end and back-end will return valid students
				string first_name;
				string last_name;
				cout << "Enter first name" << endl;
				cin >> first_name;
				cout << "Enter last name" << endl;
				cin >> last_name;
				studentrepo.findStudent(first_name, last_name);
			}
			break;
			case 5:
				// this funtion will be called by front end and then middlware will call this function and back-end will return all the data to middle ware and middleware will pass this data to front-end and then front - end will show this data or we can show this data in middleware it self
				studentrepo.showStudentDetails();
				break;
			case 6:
				f = true;
				exit(0);
				break;
			default:
				break;
			}
		}
		if (f) {
			break;
		}

		
	}
}










