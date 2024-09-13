
#include <iostream>
#include <fstream>
#include <iomanip>   
#include <cstring>  
using namespace std;
class person
{
    protected:
        int student_age;
        char student_name[50], student_gender[50], student_city[50];

    public:
        void display_info()         //Method for displaying personal information of student
        {
            cout<<"\t Personal  details of student are:           "<<endl;
            cout<<"\t Name of student is:                         "<<student_name<<endl;
            cout<<"\t Age of student is:                          "<<student_age<<endl;
            cout<<"\t Gender of student is:                       "<<student_gender<<endl;
            cout<<"\t City of student is:                         "<<student_city<<endl;
        }
};

class  student : public person
{
    protected:
    int roll_number, semester_number;
    char student_stream[50];
   
    public:
    
    int getRoll_Number()                                //getter method for protected attribute roll_number
    {
        return roll_number;
    }
    
    int getSemester_Number()                         //getter method for protected attribute semester_number
    {
        return semester_number;
    }
    
    char* getStream_Name()                          //getter method for protected attribute student_stream
    {
        return student_stream;
    }
    
    char* getGender_Name()                          //getter method for protected attribute student_stream
    {
        return student_gender;
    }
    void setRoll_Number(int rollnumber)             //setter method for protected attribute roll_number
    {
        roll_number=rollnumber;
    }

    void setSemester_Number(int semester)           //setter method for protected attribute semester_number
    {
        semester_number=semester;
    }
    
    void setStream_Name(char student_branch[50])     //setter method for protected attribute student_stream
    {
        strcpy(student_stream, student_branch);
    }
    
    void setGender_Name(char student_Gender[50])     //setter method for protected attribute student_stream
    {
        strcpy(student_gender, student_Gender);
    }
    
    
    void display_info()                             //Method for displaying academic data of student
    {
        cout<<"\t\t Academic  details of student are:           "<<endl;
        cout<<"\t\t Roll_ number of student is:                 "<<roll_number<<endl;
        cout<<"\t\t Stream of student is:                       "<<student_stream<<endl;
        cout<<"\t\t Semester of student is:                     "<<semester_number<<endl;
    }
};

class  result : public student
{
    int marks_cse, marks_math, marks_chemistry;
    char Grade;
    float percentage; // By deafault, memeber data of class is private
    
    public:
    
    void enter_info()                           // Method for entering data of students
    {
        cout<<"\t Enter the name of student:                          ";
        cin.ignore();
        cin.getline(person::student_name,50);
        cout<<"\t Enter the gender of student:                        ";
        cin.getline(student_gender,50);
        cout<<"\t Enter the city of student:                          ";
        cin.getline(student_city,50);
        cout<<"\t Enter the age of student:                           ";
        cin>>student_age;
        cout<<"\t Enter the marks of Object Oriented Programming :    ";
        cin>>marks_cse;
        cout<<"\t Enter the marks of Mathematics:                     ";
        cin>>marks_math;
        cout<<"\t Enter the marks of Chemistry:                       ";
        cin>>marks_chemistry;
        calculate_grade();
    }
    
    void display_info()
    {
        person::display_info();
        cout<<"\t Academic  details of student are:  "<<endl;
        cout<<"\t Roll_ number of student is:                 "<<roll_number<<endl;
        cout<<"\t Stream of student is:                       "<<student_stream<<endl;
        cout<<"\t Semester of student is:                     "<<semester_number<<endl;
        cout<<"\t Marks obtained in Computer:                 "<<marks_cse<<endl;
        cout<<"\t Marks obtained in Mathematics:              "<<marks_math<<endl;
        cout<<"\t Marks obtained in Chemistry:                "<<marks_chemistry<<endl;
        cout<<"\t Percentage:                                 "<<percentage<<endl;
        cout<<"\t Overall Grade:                              "<<Grade<<endl;
    }

    string convertToString(char* a)
    {
        string s(a);
        return s;
    }
   
   void calculate_grade()
   {
       percentage = (marks_cse+marks_math+marks_chemistry)/3.0;
       
        if(percentage>80)
        {
                Grade='A';
        }
        else if(percentage>60 && percentage<=80)
        {
                Grade='B';
        }
        else if(percentage>40 && percentage<=60)
        {
                Grade='C';
        }
        else
        {
                Grade='D';
        }
               
   }
	    
	    
	    
	int operator ==(result x) 
	{
	    string a=student_stream;
	    string b=x.getStream_Name();
        if(roll_number==x.getRoll_Number() && semester_number==x.getSemester_Number() && a==b)
		    return 1;
		 else
		    return 0;
	
	}
	/*int operator !=(result x) 
	{
	    string a=student_stream;
	    string b=x.getStream_Name();
        if(roll_number!=x.getRoll_Number() || semester_number!=x.getSemester_Number() || a!=b)
		    return 1;
		 else
		    return 0;
	
	}*/
};

void create_student(int roll_number, int semester, char branch[50])
{
    result s,s1;
    bool flag=true;
    fstream file;
    file.open("student.dat", ios::binary|ios::app|ios::in);  //open file in write mode
    if(!file)
        cout<<"Error in creating file.."<<endl;
    
    s1.setStream_Name(branch);
    s1.setSemester_Number(semester);
    s1.setRoll_Number(roll_number);
    file.seekg(0,ios::end);                              //moves the get pointer to the end of file
    int endposition=file.tellg();                //returns current position of get or put pointer in bytes
    int n=endposition/sizeof(s);
   
    if(n==0)
    {
        s.setRoll_Number(roll_number);
        s.setStream_Name(branch);
        s.setSemester_Number(semester);
        s.enter_info();    
        file.write((char*)&s,sizeof(s));    //write into file
        file.seekg(0,ios::end);                              //moves the get pointer to the end of file
        int endposition=file.tellg();                //returns current position of get or put pointer in bytes
        int n=endposition/sizeof(s); 
        cout<<"\n\tEntered Record Number is: "<<n;
        goto next;
        
    }
    else
    {
        file.seekg(0,ios::beg);
        while(!file.eof()) 
        {
            file.read(reinterpret_cast<char *> (&s), sizeof(result));
            if(s==s1)
            flag=false;
            
        }
     }
    file.close();
    file.open("student.dat", ios::binary|ios::app|ios::in);
    if(flag==true)
    {
        s.setRoll_Number(roll_number);
        s.setStream_Name(branch);
        s.setSemester_Number(semester);
        s.enter_info();    
        file.write((char*)&s,sizeof(s));    //write into file
        file.seekg(0,ios::end);             //moves the get pointer to the end of file
        int endposition=file.tellg();       //returns current position of get or put pointer in bytes
        int n=endposition/sizeof(s);
        cout<<"\n\tEntered Record Number is: "<<n;
    }
    next:
    file.close(); 
    cout<<"\n\tPress any key to go back to Main Menu"<<endl;
    cin.ignore();
    cin.get();//close the file
}


    //function declaration
void create__new_student_record();                // Function to create new student record
void display_specific_student_record(int);    //Function to display specific student record
void display_specific_student_stream_record(int,int,char[50]);
void display_specific_student_stream_record(int,char[50]);
void display_specific_student_stream_record(char[50],char[50]);
void display_specific_student_stream_record(char[50]);   

void display_all_records();                          // Function to display all student records

void delete_student(int,int,char[50]);               // Function to delete specific student record
void change_student(int,int,char[50]);              //Function to edit specific student record


int main()                       //Main function 
{
    
    cout<<"\n\t Welcome to Login panel of Student Database Management System of IIT Ropar";
    cout<<"\n\t  Available options are:";
    cout<<"\n\t 1. Administrative View";
    cout<<"\n\t 2. Student View";
    cout<<"\n\t Kindly enter your Choice (1/2) \n";
    char ch;
    cin>>ch;
    bool flag=false;
    string admin_pass = "admin";
    char password[25];
            
    if (ch=='1')
        {
            cout << "\n\t Enter the admin password: ";
            cin >> password;
            if (strcmp(password, admin_pass.c_str()) == 0) 
            {
                char option;
                do
                {
                    int student_roll_number,semester_number;
                    char branch_name[50];
                    cout<<"\n\t Welcome to Student Database Management System of IIT Ropar";
                    cout<<"\n\t  Available options are:";
                    cout<<"\n\t 1. Create student record";
                    cout<<"\n\t 2. Locate particular student record";
                    cout<<"\n\t 3. Delete particular student record";
                    cout<<"\n\t 4. Modify specific student record";
                    cout<<"\n\t 5. Exit";
                    cout<<"\n\t Kindly enter your Choice (1/2/3/4/5) ";
                    
                    cin>>option;
                    switch(option)
                    {   
                    case '1': 
                        cout<<"\t Enter the roll number of student:                   ";
                        cin>>student_roll_number;
                        cout<<"\t Enter the branch of student:                        "; 
                        cin.ignore();
                        cin.getline(branch_name,50);
                        cout<<"\t Enter the semester of student:                      "; 
                        cin>>semester_number;
                        create_student(student_roll_number,semester_number,branch_name); 
                        break;
            
                    case '2': 
                        do
                        {
                            cout <<"\n\t Available operations: ";
                            cout<<"\n\t 1. View particular student record ";
                            cout<<"\n\t 2. View students branch wise ";
                            cout<<"\n\t 3. View students semester wise ";
                            cout<<"\n\t 4. View students semester and branch wise ";
                            cout<<"\n\t 5. View students gender and branch wise ";
                            cout<<"\n\t 6. View all the students ";      
                            cout<<"\n\t Kindly enter your Choice (1/2/3/4/5/6) ";
                            cin>>option;
                            int student_roll_number,semester_number;
                            char branch_name[50], gender_name[50];
            
                            switch(option)
                            {   
                            case '1': 
                                cout<<"\n\t Enter the roll number of student: "; 
                                cin>>student_roll_number;
                                cout<<"\t Enter the branch of student:";
                                cin.ignore();
                                cin.getline(branch_name,50);
                                cout<<"\t Enter the semester of student: "; 
                                cin>>semester_number;
                                cout<<"Information details of student having roll_number "<<student_roll_number<<", branch_name "<<branch_name<<", and semester "<<semester_number<<" are"<<endl;
                                display_specific_student_stream_record(student_roll_number,semester_number, branch_name);
                                break;

                            case '2': 
                                cout<<"\n\t Enter the branch of student: "; 
                                cin.ignore();
                                cin.getline(branch_name,50);
                                display_specific_student_stream_record(branch_name)   ;
                                break;
            
                            case '3':
                                cout<<"\n\t Enter the semester of student: "; 
                                cin>>semester_number;
                                display_specific_student_record(semester_number); 
                                break;
             
                            case '4': 
                                cout<<"\n\t Enter the semester of student: "; 
                                cin>>semester_number;
                                cout<<"\t Enter the branch of student:";
                                cin.ignore();
                                cin.getline(branch_name,50);
                                display_specific_student_stream_record(semester_number, branch_name);
                                break;

                            case '5':
                                cout<<"\n\t Enter the branch of student:";
                                cin.ignore();
                                cin.getline(branch_name,50);
                                cout<<"\t Enter the gender of student:";
                                cin.getline(gender_name,50);
                                display_specific_student_stream_record(branch_name,gender_name);
                                break;
               
                            case '6':
                                display_all_records(); 
                                break;
                            }
                        } 
                        while(option!='6');
                        break;
                    case '3':
                        cout<<"\n\t Enter the roll number of student: "; 
                        cin>>student_roll_number;
                        cout<<"\t Enter the branch of student: "; 
                        cin.ignore();
                        cin.getline(branch_name,50);
                        cout<<"\t Enter the semester of student: "; 
                        cin>>semester_number;
                        delete_student(student_roll_number,semester_number,branch_name);  
                        break;
            
                    case '4': 
                        cout<<"\n\t Enter the roll number of student: "; 
                        cin>>student_roll_number;
                        cout<<"\t Enter the branch of student: "; 
                        cin.ignore();
                        cin.getline(branch_name,50);
                        cout<<"\t Enter the semester of student: "; 
                        cin>>semester_number;
                        change_student(student_roll_number,semester_number,branch_name);  
                        break;
            
                    case '5': cout<<"Exiting, Thank you!"; exit(0);
                    }
                }
                while(option!='5');
                return 0;
        }
        else
        cout<<"jlklk";
    }
    else
    {
        int student_roll_number,semester_number;
        char branch_name[50];
        cout<<"\n\t Enter the roll number of student: "; 
        cin>>student_roll_number;
        cout<<"\t Enter the branch of student:";
        cin.ignore();
        cin.getline(branch_name,50);
        cout<<"\t Enter the semester of student: "; 
        cin>>semester_number;
           
        result s,s1;
        s1.setRoll_Number(student_roll_number);
        s1.setStream_Name(branch_name);
        s1.setSemester_Number(semester_number);
        ifstream file;             //Read from file
        file.open("student.dat",ios::binary);           //open file in write mode
        if(!file)
        {
            cout<<"Error in opening file.. Press any Key to exit "<<endl;
            cin.get();
            return 0;
        }
       
        while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
        {
            if(s1==s)
            {
                char option1;
               flag=true;
                do
                {
                    cout <<"\n\t Available operations: ";
                    cout<<"\n\t 1. View particular student record ";
                    cout<<"\n\t 2. View students branch wise ";
                    cout<<"\n\t 3. View students semester wise ";
                    cout<<"\n\t 4. View students semester and branch wise ";
                    cout<<"\n\t 5. View students gender and branch wise ";
                    cout<<"\n\t 6. View all the students ";      
                    cout<<"\n\t Kindly enter your Choice (1/2/3/4/5/6/7) ";
                    cin>>option1;
                    int student_roll_number,semester_number;
                    char branch_name[50], gender_name[50];
            
                    switch(option1)
                    {   
                    case '1': 
                        cout<<"\n\t Enter the roll number of student: "; 
                        cin>>student_roll_number;
                        cout<<"\t Enter the branch of student: ";
                        cin.ignore();
                        cin.getline(branch_name,50);
                        cout<<"\t Enter the semester of student: "; 
                        cin>>semester_number;
                        cout<<"Information details of student having roll_number "<<student_roll_number<<", branch_name "<<branch_name<<", and semester "<<semester_number<<" are"<<endl;
                        display_specific_student_stream_record(student_roll_number,semester_number, branch_name);
                    break;

                    case '2': 
                        cout<<"\n\t Enter the branch of student: "; 
                        cin.ignore();
                        cin.getline(branch_name,50);
                        display_specific_student_stream_record(branch_name)   ;
                    break;
            
                    case '3':
                        cout<<"\n\t Enter the semester of student: "; 
                        cin>>semester_number;
                        display_specific_student_record(semester_number); 
                    break;
             
                    case '4': 
                        cout<<"\n\t Enter the semester of student: "; 
                        cin>>semester_number;
                        cout<<"\t Enter the branch of student:";
                        cin.ignore();
                        cin.getline(branch_name,50);
                        display_specific_student_stream_record(semester_number, branch_name);
                    break;

                    case '5':
                        cout<<"\n\t Enter the branch of student:";
                        cin.ignore();
                        cin.getline(branch_name,50);
                        cout<<"\t Enter the gender of student:";
                        cin.getline(gender_name,50);
                        display_specific_student_stream_record(branch_name,gender_name);
                    break;
               
                    case '6':
                        display_all_records(); 
                    break;
                     
                    }
                } 
                while(option1!='7');
                break;
            
             
            }
        }
    
    }
    if(flag==false)
        cout<<"\n\tInvalid Password";
        cout<<"\t Press any key to exit"<<endl;
    cin.get();
}





void display_all_records()          //Function for viewing all the records 
{
    result s;
    ifstream file;
    file.open("student.dat",ios::binary);  //open file in binary mode
    
    if(!file)
    {
        cout<<"\t File could not be opened. Press any Key to exit";
        cout<<"\t Press any key to go back to Search Menu:"<<endl;
        cin.ignore();
        cin.get();
        return;
    }

    cout<<"\t Viewing the records stored in the student database \n";
    int count=1;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        cout<<"\tRecord Number  "<<count<<" is:    "<<endl;
        s.display_info();
        cout<<endl;
        count++;
    }

    file.close();
    cout<<"\t Press any key to go back to Search Menu:"<<endl;
    cin.ignore();
    cin.get();
}











void display_specific_student_record(int semester_number)   //read specific record based on semester number
    {
    result s;
    ifstream file;
    file.open("student.dat",ios::binary);
    if(!file)
    {
        cout<<"Error in opening file.. Press any Key to exit "<<endl;
        cin.get();
        return;
    }
    bool flag=false;
    int count=1;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        if(s.getSemester_Number()==semester_number)
        {
            cout<<"\t Record Number  "<<count<<" is:    "<<endl;
            s.display_info();
            flag=true;
            count++; 
        }
    }
    file.close();
    if(flag==false)
        cout<<"\n\nRecord does not exist";
    cout<<"\t Press any key to go back to Search Menu:"<<endl;
    cin.ignore();
    cin.get();
}


void display_specific_student_stream_record(char branch_student_name[50],char gender_student_name[50])   
{
    result s;
    ifstream file;
    file.open("student.dat",ios::binary);
    if(!file)
    {
        cout<<"Error in opening file.. Press any Key to exit "<<endl;
        cin.get();
        return;
    }
    bool flag=false;
    int count=1;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        int j1=strcmp(s.getStream_Name(),branch_student_name) ;
        int j2= strcmp(s.getGender_Name(),gender_student_name) ;
        if(j1==0 && j2==0)
        {
            cout<<"\tRecord Number  "<<count<<" is:    "<<endl;
            s.display_info();
            flag=true;
            count++;
        }
    }
    file.close();
    if(flag==false)
    cout<<"\n\t Record does not exist";
    cout<<"\t Press any key to go back to Search Menu:"<<endl;
    cin.get();
}



void display_specific_student_stream_record(int roll_number, int semester, char stream_student_name[50])
{
    result s,s1;
    s1.setRoll_Number(roll_number);
    s1.setStream_Name(stream_student_name);
    s1.setSemester_Number(semester);
    ifstream file;             //Read from file
    file.open("student.dat",ios::binary);           //open file in write mode
    if(!file)
    {
        cout<<"Error in opening file.. Press any Key to exit "<<endl;
        cin.get();
        return;
    }
    bool flag=false;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        if(s1==s )
        {
            s.display_info();
            flag=true;
        }
   }
    file.close();
    if(flag==false)
    cout<<"\n\tRecord does not exist";
    cout<<"\t Press any key to go back to Search Menu:"<<endl;
    cin.ignore();
    cin.get();
}

void display_specific_student_stream_record(int semester_number, char stream_student_name[50])
{
    result s;
    ifstream file;
    file.open("student.dat",ios::binary);
    if(!file)
    {
        cout<<"Error in opening file.. Press any Key to exit "<<endl;
        cin.get();
    return;
    }
    bool flag=false;
    int count=1;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        if(strcmp(s.getStream_Name(),stream_student_name) == 0 && s.getSemester_Number()==semester_number)
        {
            cout<<"\tRecord Number  "<<count<<" is:    "<<endl;
            s.display_info();
            flag=true;
            count++;
        }
    }
    file.close();
    cout<<flag;
    if(flag==false)
    cout<<"\n\nRecord does not exist";
    cout<<"\tPress any key to go back to Search Menu:"<<endl;
    cin.ignore();
    cin.get();
}

void display_specific_student_stream_record(char stream_student_name[50])
{
    result s;
    ifstream file;
    file.open("student.dat",ios::binary);
    if(!file)
    {
        cout<<"Error in opening file.. Press any Key to exit "<<endl;
        cin.get();
        return;
    }

    bool flag=false;
    int count;
    while(file.read(reinterpret_cast<char *> (&s), sizeof(result)))
    {
        if(strcmp(s.getStream_Name(),stream_student_name) == 0)
        {
            cout<<"\tRecord Number  "<<count<<" is:    "<<endl;
            s.display_info();
            flag=true;
            count++;
        }
    }
    file.close();
    if(flag==false)
        cout<<"\n\nRecord does not exist";
    cout<<"\tPress any key to go back to Search Menu:"<<endl;
    cin.ignore();
    
}




// modify record for specified roll number
void change_student(int roll_number, int semester, char stream_student_name[50])
    {
    bool found=false;
    result s,s1;
    s1.setRoll_Number(roll_number);
    s1.setStream_Name(stream_student_name);
    s1.setSemester_Number(semester);
    fstream fl;
    fl.open("student.dat",ios::binary|ios::in|ios::out);
    if(!fl)
    {
        cout<<"File could not be opened. Press any Key to exit...";
    cin.ignore();
    cin.get();
    return;
    }
    while(!fl.eof() && found==false)
    {
        fl.read(reinterpret_cast<char *> (&s), sizeof(result));
        if(s==s1)
        {
            s.display_info();
            cout<<"\n\Enter new student details:"<<endl;
            s.enter_info();
            int pos=(-1)*static_cast<int>(sizeof(s));
            fl.seekp(pos,ios::cur);
            fl.write(reinterpret_cast<char *> (&s), sizeof(result));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
//iFile.close();
    if(found==false)
    {
    cout<<"\n\n Record Not Found ";
    cin.ignore();
    cin.get();
    }
        
}
//delete record with particular roll number
void delete_student(int roll_number, int semester, char stream_student_name[50])
{
result s,s1;
s1.setRoll_Number(roll_number);
    s1.setStream_Name(stream_student_name);
    s1.setSemester_Number(semester);
bool found=false;
ifstream iFile;
iFile.open("student.dat",ios::binary);
if(!iFile)
{
cout<<"File could not be opened... Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
ofstream oFile;
oFile.open("Temp.dat",ios::out);
iFile.seekg(0,ios::beg);

while(iFile.read(reinterpret_cast<char *> (&s), sizeof(result)))
{
  
/*int j1=(s.getRoll_Number()==roll_number) ;
int j2=(s.getSemester_Number()==semester) ;
int j3= (strcmp(s.getStream_Name(),stream_student_name) == 0);
cout<<"ppppppppp"<<j3;
int j4=j1&&j2&&j3;
   cout<<j4;
//if(!((s.getRoll_Number()==roll_number) && (s.getSemester_Number()==semester) && (strcmp(s.getStream_Name(),stream_student_name) == 0)))
*/
if(!(s==s1))

    
oFile.write(reinterpret_cast<char *> (&s), sizeof(result));
else
found=true;
}
oFile.close();
iFile.close();
remove("student.dat");
rename("Temp.dat","student.dat");

if(found==true)
cout<<"\n\n\tRecord Deleted ..";

else
cout<<"Record does not exist";
cin.ignore();
cin.get();
}

