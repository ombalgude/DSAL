#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_NAME_LENGTH = 50; // Maximum length for employee name

class EMP_CLASS
{
private:
    struct EMPLOYEE
    {
        char name[MAX_NAME_LENGTH];
        int emp_id;
        int salary;
    };

    struct INDEX
    {
        int emp_id;
        int position;
    };

    EMPLOYEE Records;
    INDEX Ind_Records;

public:
    EMP_CLASS()
    {
        Ind_Records.emp_id = -1;
    }
    void Create();
    void Display();
    void Delete();
    void Add();
    void Search();
};

void EMP_CLASS::Create()
{
    ofstream seqfile("EMP.DAT", ios::out | ios::binary | ios::app);
    ofstream indexfile("IND.DAT", ios::out | ios::binary | ios::app);

    char ch = 'y';

    while (ch == 'y' || ch == 'Y')
    {
        cout << "\n Enter Name: ";
        cin >> Records.name;
        cout << "\n Enter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "\n Enter Salary: ";
        cin >> Records.salary;

        seqfile.write((char *)&Records, sizeof(Records));
        Ind_Records.emp_id = Records.emp_id;
        Ind_Records.position = seqfile.tellp() / sizeof(EMPLOYEE) - 1;
        indexfile.write((char *)&Ind_Records, sizeof(Ind_Records));

        cout << "\nDo you want to add more records?";
        cin >> ch;
    }

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Display()
{
    ifstream seqfile("EMP.DAT", ios::in | ios::binary);
    ifstream indexfile("IND.DAT", ios::in | ios::binary);

    cout << "\n The Contents of file are ..." << endl;

    while (indexfile.read((char *)&Ind_Records, sizeof(Ind_Records)))
    {
        if (Ind_Records.emp_id != -1)
        {
            seqfile.seekg(Ind_Records.position * sizeof(Records), ios::beg);
            seqfile.read((char *)&Records, sizeof(Records));

            cout << "\nName: " << Records.name;
            cout << "\nEmp_ID: " << Records.emp_id;
            cout << "\nSalary: " << Records.salary;
            cout << "\n";
        }
    }

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Delete()
{
    int id;
    cout << "\n For deletion,";
    cout << "\n Enter the Emp_ID for for searching ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    while (indexfile.read((char *)&Ind_Records, sizeof(Ind_Records)))
    {
        if (id == Ind_Records.emp_id)
        {
            Ind_Records.emp_id = -1;
            seqfile.seekp(Ind_Records.position * sizeof(Records), ios::beg);
            seqfile.write((char *)&Records, sizeof(Records));
            indexfile.seekp(-sizeof(Ind_Records), ios::cur);
            indexfile.write((char *)&Ind_Records, sizeof(Ind_Records));

            cout << "\n The record is Deleted!!!";
            return;
        }
    }

    cout << "\n The record is not present in the file";

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Add()
{
    ofstream seqfile("EMP.DAT", ios::out | ios::binary | ios::app);
    ofstream indexfile("IND.DAT", ios::out | ios::binary | ios::app);

    cout << "\n Enter the record for appending";
    cout << "\nName: ";
    cin >> Records.name;
    cout << "\nEmp_ID: ";
    cin >> Records.emp_id;
    cout << "\nSalary: ";
    cin >> Records.salary;

    seqfile.write((char *)&Records, sizeof(Records));

    Ind_Records.emp_id = Records.emp_id;
    Ind_Records.position = seqfile.tellp() / sizeof(EMPLOYEE) - 1;
    indexfile.write((char *)&Ind_Records, sizeof(Ind_Records));

    seqfile.close();
    indexfile.close();

    cout << "\n The record is Appended!!!";
}

void EMP_CLASS::Search()
{
    int id;
    cout << "\n Enter the Emp_ID for searching the record ";
    cin >> id;

    ifstream seqfile("EMP.DAT", ios::in | ios::binary);
    ifstream indexfile("IND.DAT", ios::in | ios::binary);

    while (indexfile.read((char *)&Ind_Records, sizeof(Ind_Records)))
    {
        if (id == Ind_Records.emp_id)
        {
            seqfile.seekg(Ind_Records.position * sizeof(Records), ios::beg);
            seqfile.read((char *)&Records, sizeof(Records));

            cout << "\n The Record is present in the file and it is...";
            cout << "\n Name: " << Records.name;
            cout << "\n Emp_ID: " << Records.emp_id;
            cout << "\n Salary: " << Records.salary;

            seqfile.close();
            indexfile.close();
            return;
        }
    }

    cout << "\n Record is not present in the file";

    seqfile.close();
    indexfile.close();
}

int main()
{
    EMP_CLASS List;
    char ans = 'y';
    int choice;

    do
    {
        cout << "\n             Main Menu             " << endl;
        cout << "\n 1.Create";
        cout << "\n 2.Display";
        cout << "\n 3.Delete";
        cout << "\n 4.Add";
        cout << "\n 5.Search";
        cout << "\n 6.Exit";
        cout << "\n Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            List.Create();
            break;
        case 2:
            List.Display();
            break;
        case 3:
            List.Delete();
            break;
        case 4:
            List.Add();
            break;
        case 5:
            List.Search();
            break;
        case 6:
            exit(0);
        }

        cout << "\n\t Do you want to go back to Main Menu?";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
