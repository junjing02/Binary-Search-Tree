#include	<iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "BST.h"
#include "Student.h"
#include <iomanip>

using namespace std;

bool readFile(const char *, BST *);
int menu();


bool duplicate(BST *, int);
bool duplicate2(BTNode*, int);


int main() 
{
	bool next = true;
	const char filename[] = "student.txt";
	BST t1, t2;
	int source, order;
	Student student;

	cout << "BINARY SEARCH TREE" << endl;

	do 
	{
		switch (menu())
		{
		case 1:

			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tREAD DATA TO BST" << endl;
			cout << "*****************************************************" << endl << endl;
			
			if (!readFile(filename, &t1))
			{
				cout << "Failed to read data" << endl << endl;
			}
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");
			break;

		case 2:

			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tPRINT DEEPEST NODES" << endl;
			cout << "*****************************************************" << endl << endl;

			cout << "Deepest Node(s): ";
			if (!t1.deepestNodes())
			{
				cout << "Failed to print nodes" << endl << endl;
			}
			cout << endl;
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");
			break;

		case 3:

			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tDISPLAY STUDENT" << endl;
			cout << "*****************************************************" << endl << endl;
			cout << "\tSource:" << endl;
			cout << "\t1. Display to screen" << endl;
			cout << "\t2. Print to file" << endl;

			cout << endl << "\tOrder:" << endl;
			cout << "\t1. Ascending Order" << endl;
			cout << "\t2. Descending Order" << endl << endl;
			cout << "*****************************************************" << endl << endl;


			while (true)
			{
				cout << "Enter the source: ";
				cin >> source;

				if (cin.fail() || source < 1 || source > 2)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid input! Please enter between 1 - 2." << endl << endl;
					continue;
				}

				cout << "Enter the order : ";
				cin >> order;

				if (cin.fail() || order < 1 || order > 2)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid input! Please enter between 1 - 2" << endl << endl;
					continue;
				}
				break;
			}

			if (!t1.display(order, source))
			{
				cout << "Failed to display" << endl << endl;
			}
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");

			break;

		case 4:

			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tCLONE SUBTREE" << endl;
			cout << "*****************************************************" << endl << endl;

			cout << "Enter student id: ";
			cin >> student.id;

			if (t2.CloneSubtree(t1, student))
			{
				cout << "Successfully clone the subtree" << endl << endl;
				cout << "*****************************************************" << endl << endl;
				cout << endl;
				system("pause");
				system("cls");

				cout << endl << endl << "*****************************************************" << endl;
				cout << "\tTREE in PreOrder" << endl;
				cout << "*****************************************************" << endl << endl;
				t1.preOrderPrint();

				cout << endl << endl << "*****************************************************" << endl;
				cout << "\t\tCLONE SUBTREE in PreOrder" << endl;
				cout << "*****************************************************" << endl << endl;
				t2.preOrderPrint();

				t2.clear();
			}
			else
			{
				cout << "Cannot clone subtree" << endl << endl;
			}
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");
			break;

		case 5:

			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tPRINT LEVEL NODES" << endl;
			cout << "*****************************************************" << endl << endl;

			if (!t1.printLevelNodes())
			{
				cout << "Failed to print nodes" << endl << endl;
			}
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");
			break;

		case 6:
			system("cls");
			cout << endl << endl << "*****************************************************" << endl;
			cout << "\t\tPRINT PATH" << endl;
			cout << "*****************************************************" << endl << endl;

			if (!t1.printPath())
			{
				cout << "Failed to print path" << endl << endl;
			}
			cout << "*****************************************************" << endl << endl;
			cout << endl;
			system("pause");
			break;

		case 7:
			cout << endl << "Exiting..." << endl;
			next = false;
			break;
		}
	} while (next);

	system("pause");
	return 0;
}

int menu()
{
	int choice;

	//Display menu
	system("cls");
	cout << endl << endl << "*****************************************************" << endl;
	cout << "\t\tMENU" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
	cout << "\t1. Read data to BST" << endl;
	cout << "\t2. Print deepest nodes" << endl;
	cout << "\t3. Display student" << endl;
	cout << "\t4. Clone Subtree" << endl;
	cout << "\t5. Print Level Nodes" << endl;
	cout << "\t6. Print Path" << endl;
	cout << "\t7. Exit" << endl;
	cout << endl;
	cout << "*****************************************************" << endl << endl;


	//Input Validation
	while (true)
	{
		cout << "Enter your choice: ";
		cin >> choice;

		// Input validation for incompatible data type & out of range
		if (cin.fail() || choice < 1 || choice > 7)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input! Please enter between 1 - 7." << endl << endl;
			continue;
		}
		return choice;
	}
}

bool readFile(const char* filename, BST* t1)
{
	Student student;
	ifstream infile(filename);
	string s;
	int count = 0;

	if (!infile.is_open())
	{
		cout << "Error opening " << filename << " file" << endl;
		return false;
	}
	else
	{
		while (!infile.eof())
		{
			for (int i = 0; i < 3; i++)
			{
				infile >> s;
			}
			infile >> student.id;

			for (int i = 0; i < 2; i++)
			{
				infile >> s;
			}
			infile.ignore(1);
			infile.getline(student.name, 30);

			for (int i = 0; i < 2; i++)
			{
				infile >> s;
			}
			infile.ignore(1);
			infile.getline(student.address, 100);

			for (int i = 0; i < 2; i++)
			{
				infile >> s;
			}
			infile.ignore(1);
			infile.getline(student.DOB, 20);

			for (int i = 0; i < 3; i++)
			{
				infile >> s;
			}
			infile.ignore(1);
			infile.getline(student.phone_no, 10);

			for (int i = 0; i < 2; i++)
			{
				infile >> s;
			}
			infile.ignore(1);
			infile.getline(student.course, 5);

			for (int i = 0; i < 2; i++)
			{
				infile >> s;
			}
			infile >> student.cgpa;

			if (!duplicate(t1, student.id))
			{
				t1->insert(student);
				count++;
			}
			else
			{
				cout << student.id << " already existed in tree" << endl;
			}
		}
		cout << endl << count << "  NEW student record(s) have been successfully read" << endl << endl;
	}
}

bool duplicate(BST* t1, int id)
{
	if (t1->root == NULL)
	{
		return false;
	}
	return duplicate2(t1->root, id);
}

bool duplicate2(BTNode* cur, int id)
{
	if (cur == NULL)
	{
		return false;
	}
	if (cur->item.compare3(id))
	{
		return true;
	}
	if (id < cur->item.id)
	{
		return duplicate2(cur->left, id);
	}
	return duplicate2(cur->right, id);
}

