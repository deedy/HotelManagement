//
//  HospitalManagement.cpp
//  HotelManagement
//
//  Created by Debarghya Das on 07/07/12.
//  Copyright 2012 Cornell University. All rights reserved.
//

#include <iostream>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <fstream.h>
#include <vector>
#include <sstream>
#include <stdio.h>
using namespace std;
struct appointment;
struct doctor;
struct patient;
struct date;
struct logindata
{
    char username[10];
    char password[10];
};
struct doctor
{
    int id;
    string name;
    char gender;
    string address;
    string phone;
    string special;
    int fee;
    int pat_no;
    string toString() {
        ostringstream convert;   // stream used for the conversion
        convert << fee;
        ostringstream convert1;   // stream used for the conversion
        convert1 << id;
        ostringstream convert2;   // stream used for the conversion
        convert2 << pat_no;
        string a=""+convert1.str()+"|"+name+"|"+&gender+"|"+address+"|"+phone+"|"+special+"|"+convert.str()+"|"+convert2.str();
        return a;
    }
};

struct patient
{
    int id;
    string name;
    char gender;
    string address;
    string phone;
    string sympt;
    string toString() { 
        ostringstream convert;   // stream used for the conversion
        convert << id;
        string a=""+convert.str()+"|"+name+"|"+&gender+"|"+address+"|"+phone+"|"+sympt;
        return a;
    }
};
struct date {
    int day;
    int month;
    int year;
    string toString() {
        ostringstream convert;   // stream used for the conversion
        convert << day;
        ostringstream convert1;   // stream used for the conversion
        convert1 << month;
        ostringstream convert2;   // stream used for the conversion
        convert2 << year;
        string a=""+convert.str()+"|"+convert1.str()+"|"+convert2.str();
        return a;
    }
};
struct appointment 
{
    patient pat;
    date dat;
    doctor doc;
    string toString() {
        ostringstream convert;   // stream used for the conversion
        convert << pat.id;
        ostringstream convert1;   // stream used for the conversion
        convert1 << doc.id;
        string a=""+convert1.str()+"|"+convert.str()+"|"+dat.toString();
        return a;
    }
    string toDetailString() {
        string a="Doctor: "+doc.name+"\tPatient: "+pat.name+"\tDate: "+doc.toString();
        return a;
    }
};
struct logindata l[6]=
{
	{"Ankeet","Ankeet"},{"Neel","Neel"},{"Subodh","Subodh"},{"Teacher","Teacher"},{"Admin","12345"}
};
doctor getDocByID(int id);
patient getPatByID(int id);
void addPatient();
void addDoctor();
vector<doctor> loadDoctors ();
void split(const string& str, const string& delimiters , vector<string>& tokens);
vector<patient> loadPatients ();
void printPatients();
void printDoctors();
int generateDocID();
void updateDoctorDatabase(vector<doctor> docs);
void removeDoctor();
void updatePatientDatabase(vector<patient> pats);
void removePatient();
int generatePatID();
bool isValidDate (date d);
void addAppointment();
vector<appointment> loadAppointments();
void updateAppointmentDatabase(vector<appointment> apps);
void printAppointments();
void makeBill();
void makeReport();

void makeReport() {
    cout<<"\n________________________________________________________________________________";
    cout<<"\n*************************   SANMITA HOSPITAL DOCTOR REPORT ***********************";
    cout<<"\n                         --------------------------------                       ";
    cout<<"\n                          V.L.Mehta Road,Dahisar(E),Mumbai-92.                        ";
    cout<<"\n                                   Tel :- 4545454                               ";
    cout<<"\n--------------------------------------------------------------------------------";
    vector<doctor> docs=loadDoctors();
    cout << "\nDOCTOR NAME\tNUMBER OF PATIENTS" << endl;
    int count=0;
    for (int i=0;i<docs.size();i++) {
        cout << docs[i].name << "\t" << docs[i].pat_no << endl;
        count+=docs[i].pat_no;
    }
    cout << "TOTAL NUMBER OF PATIENTS: "<<count << endl;
    
}

void makeBill() {
    vector<appointment> apps= loadAppointments();
    vector<doctor> docs= loadDoctors();
    printAppointments();
    int ID=-1;
    cout << "Enter ID of appointment you want to select?" << endl;
    do {
        if (!(ID==-1))
            cout <<"That is an invalid ID. Please reenter." << endl;
        string f;
        getline(cin,f);
        ID=atoi(f.c_str());
    } while (ID<1 || ID>apps.size());
    appointment curr=apps[ID-1];
    apps.erase(apps.begin()+ID-1);
    updateAppointmentDatabase(apps);
    int hours=-1;
    cout << "Enter duration of visit in hours" << endl;
    do {
        if (!(hours==-1)) 
            cout <<"That is an invalid number. Please reenter." << endl;
        string f;
        getline(cin,f);
        hours=atof(f.c_str());
    } while (hours<=0);
    for (int i=0;i<docs.size();i++) {
        if (docs[i].id==curr.doc.id) {
            docs[i].pat_no++;
        }
        
    }
    updateDoctorDatabase(docs);
    double amt=hours*curr.doc.fee;
    double tax=0.05*amt;
    cout<<"\n________________________________________________________________________________";
    cout<<"\n*************************        SANMITA HOSPITAL       ***********************";
    cout<<"\n                         --------------------------------                       ";
    cout<<"\n                          V.L.Mehta Road,Dahisar(E),Mumbai-92.                        ";
    cout<<"\n                                   Tel :- 4545454                               ";
    cout<<"\n--------------------------------------------------------------------------------";
    cout<<"\n      Patient's name : "<< curr.pat.name;
    cout<<"\n                              ";
    cout<<"\n      Doctor's Name "<<curr.doc.name;
    cout<<"\n      Number of hours    : "<<hours;
    cout<<"\n      Doctor's Hourly Rate    : "<<curr.doc.fee;
    cout<<"\n      Total charges    : "<<amt;
    cout<<"\n      Date : "<<curr.dat.toString();
    cout<<"\n      Ser.tax % = 5%";
    cout<<"\n      Ser.tax   ="<<tax;
    cout<<"\n      Bill Amount >>>>>> Rs "<<amt+tax;
    cout<<"\n                              ";
    cout<<"\n      THANK YOU !!!!!";
    cout<<"\n      Do Visit Us Again !";
    
}
doctor getDocByID(int id) {
    vector<doctor> docs=loadDoctors();
    for (int i=0;i<docs.size();i++) {
        if (docs[i].id==id) {
            return docs[i];
        }
        
    }
}

patient getPatByID(int id) {
    vector<patient> pats=loadPatients();
    for (int i=0;i<pats.size();i++) {
        if (pats[i].id==id) {
            return pats[i];
        }
        
    }
}

vector<appointment> loadAppointments () {
    
    vector<patient> pats=loadPatients();
    string line;
    vector<appointment> apps;
    ifstream myfile ("appointments.dat");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            appointment app;
            doctor  doc;
            patient pat;
            date d;
            getline (myfile,line);
            vector<string> v;
            split(line, "|" , v);
            if (v.size()!=0) {
                doc=getDocByID(atoi(v[0].c_str()));
                pat=getPatByID(atoi(v[1].c_str()));
                d.day=atoi(v[2].c_str());
                d.month=atoi(v[3].c_str());
                d.year=atoi(v[4].c_str());
                app.doc=doc;
                app.pat=pat;
                app.dat=d;
                apps.push_back(app);
   
            }
           
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    updateAppointmentDatabase(apps);
    return apps;
}

bool isValidDate (date d) {
    time_t t=time(NULL);
    int today_d=localtime(&t)->tm_mday;
    int today_m=1+(localtime(&t)->tm_mon);
    int today_y=1900+(localtime(&t)->tm_mday);
    
    if (d.year<today_d || d.year>3000)
        return false;
    if (d.year==today_y) {
        if (d.month<today_m) {
            return false;
        }
        if (d.month==today_m) {
            if (d.day<today_d)
                return false;
        }
    }
    if (d.month<=0 || d.month >12)
        return false;
    if (d.day<=0 && d.day>31)
        return false;
    if (d.month==4 || d.month==6 || d.month==9 || d.month==11) {
        if (d.day>30)
            return false;
    }
    if (d.month==2 && d.day>28) {
        return false;
    }
    return true;
}
void addAppointment() {
    vector<doctor> docs=loadDoctors();
    vector<patient> pats=loadPatients();
    vector<appointment> apps=loadAppointments();
    cout << "ADDING APPOINTMENT" << endl;
    string temp;
    getline(cin,temp);
    //CHOOSE DOCTOR
    printDoctors();
    int ID=-1;
    cout << "Enter ID of doctor you wish to set up an appointment with?" << endl;
    do {
        if (ID==0) 
            cout <<"That is an invalid ID. Please reenter." << endl;
        string f;
        getline(cin,f);
        ID=atoi(f.c_str());
    } while (ID==0);
    int pos=-1;
    for (int i=0;i<docs.size();i++) {
        if (ID==docs[i].id) {
            pos=i;
        }
        
    }
    if (pos==-1) {
        cout <<"ID not found." << endl;
        return;
    }
    doctor doc=docs[pos];
    //CHOOSE PATIENT
    printPatients();
    int ID1=-1;
    cout << "Are you already registered in the system?" << endl;
    do {
        if (ID1==0) 
            cout <<"That is an invalid ID. Please reenter." << endl;
        string f;
        getline(cin,f);
        ID1=atoi(f.c_str());
    } while (ID1==0);
    
    int pos1=-1;
    for (int i=0;i<pats.size();i++) {
        if (ID1==pats[i].id) {
            pos1=i;
        }
        
    }
    if (pos1==-1) {
        cout <<"ID not found. Please Register in the System" << endl;
        return;
    }
    patient pat=pats[pos1];
    //Choose Date
    date d={0,0,0};
    do {
        if (!(d.day ==0 && d.month==0 && d.year==0))
            cout <<"That is an invalid ID. Please reenter." << endl;
        cout << "Enter Day: " << endl;
        string D;
        getline(cin,D);
        d.day=atoi(D.c_str());
        cout << "Enter Month: " << endl;
        string M;
        getline(cin,M);
        d.month=atoi(M.c_str());
        cout << "Enter Year: " << endl;
        string Y;
        getline(cin,Y);
        d.year=atoi(Y.c_str());
    } while (!isValidDate(d));
    appointment A;
    A.pat=pat;
    A.dat=d;
    A.doc=doc;
    apps.push_back(A);
    updateAppointmentDatabase(apps);
    
}
void addPatient() {
    cout << "ADDING PATIENT" << endl;
    string temp;
    getline(cin,temp);
    vector<patient> pats=loadPatients();
    patient a;
    cout << "Please Enter Name:" << endl;
    string name;
    getline(cin,a.name);
    cout << "Please Enter Gender:" << endl;
    cin.get(a.gender);
    cin.ignore(80,'\n');
    cout << "Please Enter Address:" << endl;
    getline(cin,a.address);
    cout << "Please Enter Phone Number:" << endl;
    getline(cin,a.phone);
    cout << "Please Enter Symptoms:" << endl;
    getline(cin,a.sympt);
    ofstream myfile ("patients.dat", ios::out | ios::app);
    a.id= generatePatID();
    pats.push_back(a);
    updatePatientDatabase(pats);
};
void removeDoctor() {
    vector<doctor> docs=loadDoctors();
    printDoctors();
    int deleteID=-1;
    cout << "Enter ID of doctor you wish to delete?" << endl;
    do {
        if (!(deleteID==-1))
            cout <<"That is an invalid ID. Please reenter." << endl;
        string f;
        getline(cin,f);
        deleteID=atoi(f.c_str());
    } while (deleteID==0);
    for (int i=0;i<docs.size();i++) {
        if (deleteID==docs[i].id) {
            docs.erase(docs.begin()+i);
            updateDoctorDatabase(docs);
        }
        
    }
    cout << "No such ID found" << endl;
}
void updateDoctorDatabase(vector<doctor> docs) {
    ofstream myfile ("doctors.dat", ios::out);
    if (myfile.is_open())
    {
        for (int i=0;i<docs.size();i++) {
            myfile << docs[i].toString() << endl;
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
}
void updateAppointmentDatabase(vector<appointment> apps) {
    ofstream myfile ("appointments.dat", ios::out);
    if (myfile.is_open())
    {
        for (int i=0;i<apps.size();i++) {
            myfile << apps[i].toString() << endl;
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
}
void removePatient() {
    vector<patient> pats=loadPatients();
    printPatients();
    int deleteID=-1;
    cout << "Enter ID of patient you wish to delete?" << endl;
    do {
        if (!(deleteID==-1))
            cout <<"That is an invalid ID. Please reenter." << endl;
        string f;
        getline(cin,f);
        deleteID=atoi(f.c_str());
    } while (deleteID==0);
    for (int i=0;i<pats.size();i++) {
        if (deleteID==pats[i].id) {
            pats.erase(pats.begin()+i);
            updatePatientDatabase(pats);
        }
        
    }
    cout << "No such ID found" << endl;
}
void updatePatientDatabase(vector<patient> pats) {
    ofstream myfile ("patients.dat", ios::out);
    if (myfile.is_open())
    {
        for (int i=0;i<pats.size();i++) {
            myfile << pats[i].toString()<< endl;
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    
    
}
void addDoctor() {
    cout << "ADDING DOCTOR" << endl;
    string temp;
    getline(cin,temp);
    vector<doctor> docs=loadDoctors();
    doctor a;
    cout << "Please Enter Name:" << endl;
    getline(cin,a.name);
    cout << "Please Enter Gender:" << endl;
    cin.get(a.gender);
    cin.ignore(80,'\n');
    cout << "Please Enter Address:" << endl;
    getline(cin,a.address);
    cout << "Please Enter Phone Number:" << endl;
    getline(cin,a.phone);
    cout << "Please Enter Specialization:" << endl;
    getline(cin,a.special);
    cout << "Please Enter Fee:" << endl;
    a.fee=-1;
    a.pat_no=0;
    do {
        if (a.fee==0) 
            cout <<"That is not a valid fee. Please reenter." << endl;
        string f;
        getline(cin,f);
        a.fee=atoi(f.c_str());
    } while (a.fee==0);
    a.id= generateDocID();
    docs.push_back(a);
    updateDoctorDatabase(docs);
    
};
int generateDocID() {
    vector<doctor> doclist=loadDoctors();
    while (true) {
        bool found=false;
        srand ( time(NULL) );
        int id= rand() % 90 + 10;
        for (int i=0;i<doclist.size();i++) {
            if (doclist[i].id==id) {
                found=true;
                break;
            }
        }
        if (!found)
            return id;
    }
    
}
int generatePatID() {
    vector<patient> patlist=loadPatients();
    while (true) {
        bool found=false;
        srand ( time(NULL) );
        int id= rand() % 90 + 10;
        for (int i=0;i<patlist.size();i++) {
            if (patlist[i].id==id) {
                found=true;
                break;
            }
        }
        if (!found)
            return id;
    }
    
}
void split(const string& str, const string& delimiters , vector<string>& tokens)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
vector<patient> loadPatients () {
    string line;
    vector<patient> pats;
    ifstream myfile ("patients.dat");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            vector<string> v;
            split(line, "|" , v);
            if (v.size()!=0) {
                patient a;
                a.id=atoi(v[0].c_str());
                a.name=v[1];
                a.gender=v[2].at(0);
                a.address=v[3];
                a.phone=v[4];
                a.sympt=v[5];
                pats.push_back(a);
            }
        }
        myfile.close();
        
    }
    
    else cout << "Unable to open file"; 
    return pats;
}
void printAppointments() {
    cout << "APPOINTMENT DATABASE: " << endl;
    vector<appointment> apps=loadAppointments();
    for (int i=0;i<apps.size();i++) {
        cout << (i+1) << "\t" << apps[i].toDetailString() << endl;
    }
}
void printPatients() {
    vector<patient> pats=loadPatients();
    cout << "PATIENT DATABASE: " << endl;
    for (int i=0;i<pats.size();i++) {
        string temp="|";
        cout << pats[i].id << "\t" << string(strstr(pats[i].toString().c_str(),temp.c_str())).substr(1)<< endl;
        
    }
}
vector<doctor> loadDoctors () {
    string line;
    vector<doctor> docs;
    ifstream myfile ("doctors.dat");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            vector<string> v;
            split(line, "|" , v);
            if (v.size()!=0) {
                doctor a;
                a.id=atoi(v[0].c_str());
                a.name=v[1];
                a.gender=v[2].at(0);
                a.address=v[3];
                a.phone=v[4];
                a.special=v[5];
                a.fee=atoi(v[6].c_str());
                a.pat_no=atoi(v[7].c_str());
                docs.push_back(a);
            }
        }
        myfile.close();
        
    }
    
    else cout << "Unable to open file"; 
    return docs;
}

void printDoctors() {
    vector<doctor> docs=loadDoctors();
    cout << "DOCTOR DATABASE: " << endl;
    for (int i=0;i<docs.size();i++) {
        string temp="|";
        cout << docs[i].id << "\t" << string(strstr(docs[i].toString().c_str(),temp.c_str())).substr(1)<< endl;
        
    }
}

void login();
void login() {
    cout << "Welcome to the Sanmita Hospital Management System" << endl;
    cout << "Please Enter your username" << endl;
    cin>>l[5].username;
    cout<<"\n";
    cout<<"Please enter your password" << endl;
    cin>>l[5].password;
    char* temp5=l[5].username;
    char* temp6=l[5].password;
    string userentry=string(temp5)+" "+string(temp6);
    ofstream fout ("loginid.dat", ios::out);
    int i=0;
    for(i=0;i<5;i++) {
        fout << (char*)&l[i].username << " " << (char*)&l[i].password << endl;
    }
    fout.close();
    string usr;
    bool found=false;
    ifstream fin ("loginid.dat", ios::in);
    if (fin.is_open()){
        while ( fin.good() ) {
            getline (fin,usr);
            cout << usr << endl;
            if (userentry==usr) {
                found=true;
                break;
            }
        }
        fin.close();
    }
    if (!found) {
        cout<<"The entered usernames and passwords do not match ........please contact the administrator";
        exit(1);
    }
    return;

}
void PressEnterToContinue()
{
    string c;
    printf( "Press ENTER to continue... " );
    getline(cin,c);
    cin.ignore(80,'\n');
    cin.ignore(80,'\n');
}

int main() {
    //login();
    int ch;
    time_t t=time(NULL);
    cout<<"\n                                                        "<<ctime(&t);
    t -= 24L*60L*60L; //Subtract a day
    cout<<"\n--------------------------------------------------------------------------------";
    cout<<"\n--------------------------------------------------------------------------------";
    cout<<"\n*************************** WELCOME TO HOSPITAL Sanmita ************************";
    cout<<"\n--------------------------------------------------------------------------------";
    cout<<"\n--------------------------------------------------------------------------------";
    xyz:
        cout<<"\n--------------------------------------------------------------------------------";
        cout<<"\n**********************        Sanmita Hospital        **************************";
        cout<<"\n                      ________________________________                          ";
        cout<<"\n                        V.L.Mehta Road,Dahisar(E),Mumbai-68.                          ";
        cout<<"\n                                Tel-45454545.                                   ";
        cout<<"\n--------------------------------------------------------------------------------";
        cout<<"\n                                                              ";
        cout<<"\n 1.PATIENT REGISTRATION                          2.DOCTOR REGISTRATION";
        cout<<"\n                                                              ";
        cout<<"\n 3.SET UP APPOINTMENT                            4.CHECK THE APPOINTMENTS    ";
        cout<<"\n                                                              ";
        cout<<"\n 5.CREATE BILL                                   6.DOCTOR INFORMATION                ";
        cout<<"\n                                                              ";
        cout<<"\n 7.GET REPORT                                    8.PATIENT INFOMATION                 ";
        cout<<"\n                                                              ";
        cout<<"\n 9.REMOVE DOCTOR                                 10.REMOVE PATIENT     "; 
        cout<<"\n                                                              ";
        cout<<"\n 11.EXIT     "; 
        cout<<"\n\n Enter your choice : ";
    cin >> ch;
    if (ch>11) {
        cout <<"\n Wrong choice...";
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==1) {
        addPatient();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==2) {
        addDoctor();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==3) {
        addAppointment();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==4) {
        printAppointments();
        goto xyz;
    }
    if (ch==5) {
        makeBill();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==6) {
        printDoctors();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==7) {
        makeReport();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==8) {
        printPatients();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==9) {
        removeDoctor();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==10) {
        removePatient();
        PressEnterToContinue();
        goto xyz;
    }
    if (ch==11) {
        goto mno;
    }
mno:
    return 0;
}
