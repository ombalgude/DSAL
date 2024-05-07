#include <iostream>
#include <cstring>
using namespace std;

struct book_node
{
    char title[20];
    int chapt_count;
    book_node *down[10];
};

class book
{
public:
    book_node *root;
    void create_tree();
    void display(book_node *r);
    
    book()
    {
        root = NULL;
    }
};

void book::create_tree()
{
    int i, j, k;
    root = new book_node;
    cout << "Enter name of the book: " << endl;
    cin.ignore();
    cin.getline(root->title, 20);
    cout << "Enter total number of chapters in the book: " << endl;
    cin >> root->chapt_count;
    for (i = 0; i < root->chapt_count; i++)
    {
        root->down[i] = new book_node;
        cout << "Enter Name for chapter " << i + 1 << endl;
        cin.ignore();
        cin.getline(root->down[i]->title, 20);
        cout << "Enter no. of sections in  " << root->down[i]->title << endl;
        cin >> root->down[i]->chapt_count;
        for (j = 0; j < root->down[i]->chapt_count; j++)
        {
            root->down[i]->down[j] = new book_node;
            cout << "Enter title for section " << j + 1 << endl;
            cin.ignore();
            cin.getline(root->down[i]->down[j]->title, 20);
            cout << "Enter no. of sub sections in section " << j + 1 << endl;
            cin >> root->down[i]->down[j]->chapt_count;
            for (k = 0; k < root->down[i]->down[j]->chapt_count; k++)
            {
                root->down[i]->down[j]->down[k] = new book_node;
                cout << "Enter title for subsection " << k + 1 << endl;
                cin.ignore();
                cin.getline(root->down[i]->down[j]->down[k]->title, 20);
            }
        }
    }
}

void book::display(book_node *r)
{
    int i, j, k;
    if (r != NULL)
    {
        cout << "****index****" << endl;
        cout << "Book Title: " << r->title << endl
             << endl;

        for (i = 0; i < r->chapt_count; i++)
        {
            cout << "\t";
            cout << "Chapter " << i + 1 << ": " << r->down[i]->title << endl;

            for (j = 0; j < r->down[i]->chapt_count; j++)
            {
                cout << "\t\t";
                cout << "Section " << j + 1 << ": " << r->down[i]->down[j]->title << endl;

                for (k = 0; k < r->down[i]->down[j]->chapt_count; k++)
                {
                    cout << "\t\t\t";
                    cout << "Sub Section " << k + 1 << ": " << r->down[i]->down[j]->down[k]->title << endl;
                }
            }
        }
    }
}

int main()
{
    int choice;
    book myBook;
    while (1)
    {
        cout << "Menu:" << endl;
        cout << "Book tree structure" << endl;
        cout << "1. Create tree" << endl;
        cout << "2. Display tree" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            myBook.create_tree();
            break;

        case 2:
            myBook.display(myBook.root);
            break;
        case 3:
            exit(0);
        }
    }
    return 0;
}
