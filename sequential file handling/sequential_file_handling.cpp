#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

class student {
    string name, div, address;
    int roll;

public:
    void getdata();
    void displayAll();
    void insert_record();
    void delete_record();
    void search_record();
};

void student::getdata() {
    cout << "\nEnter Roll No, Division, Name and Address of Student= ";
    cin >> roll >> div >> name >> address;
}

void student::insert_record() {
    ofstream out("Record11.txt", ios::app | ios::binary);
    getdata();
    out.write(reinterpret_cast<char*>(this), sizeof(*this));
    out.close();
}

void student::displayAll() {
    ifstream in("Record11.txt", ios::binary);
    cout << "\nThe Contents of file are.......\n\n";
    cout << "\nROLL" << setw(15) << "Division" << setw(15) << "NAME" << setw(15) << "ADDRESS\n";

    while (in.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        cout << "\n" << roll << setw(15) << div << setw(15) << name << setw(15) << address;
    }
    cout << "\n";
    in.close();
}

void student::delete_record() {
    ifstream in("Record11.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    int item;

    cout << "\nEnter Roll_No :";
    cin >> item;

    while (in.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (roll != item) {
            temp.write(reinterpret_cast<char*>(this), sizeof(*this));
        }
    }
    in.close();
    temp.close();
    
    remove("Record11.txt");
    rename("temp.txt", "Record11.txt");
}

void student::search_record() {
    int item, flag = 0;
    ifstream in("Record11.txt", ios::binary);
    
    cout << "\nEnter Roll_No :";
    cin >> item;
    
    while (in.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (roll == item) {
            cout << "\n Record is Present in the File....\n ";
            cout << "\n" << roll << "\t" << div << "\t" << name << "\t" << address;
            flag = 1;
            break;
        }
    }
    
    if (flag == 0)
        cout << endl << "Sorry. No such Record Present" << endl;
    in.close();
}

int main() {
    student t1;
    int ch;
    
    ofstream out("Record11.txt");
    out.close();
    
    while (true) {
        cout << "\n*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** \n\n";
        cout << "\n1.INSERT RECORD\n2.DISPLAY All Records \n3.SEARCH\n4.Delete\n5.EXIT.";
        cout << "\nEnter UR Choice : ";
        cin >> ch;
        
        switch (ch) {
            case 1:
                t1.insert_record();
                cout << "\n\nRecord is Inserted..\n\n";
                break;
            case 2:
                t1.displayAll();
                break;
            case 3:
                t1.search_record();
                break;
            case 4:
                t1.delete_record();
                break;
            case 5:
                exit(0);
        }
    }
    
    return 0;
}
