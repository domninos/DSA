#include <iostream>
#include <string>
#include <unistd.h>
#include <iomanip>

#include "sections.hpp"

using namespace std;

struct Node
{
    // Node datas
    int nodeNumber = -1;
    int studentID;

    string name;
    string subject;

    SectionNode sectionNode;

    Node *next;
};

void validate(string &temp)
{
    while (temp.empty() || temp == "")
    {
        cout << "Please enter a valid input." << endl;
        cin >> temp;
    }
}

bool isAlreadyID(int id, Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->studentID == id)
            return true;
        current = current->next;
    }
    return false;
}

void addStudentData(Node **head, SectionNode *sectionHead)
{
    sleep(1);

    // Adds a new node
    Node *newNode;
    newNode = new Node();
    newNode->next = NULL;

    // Checks if the head is NULL
    if (*head == NULL)
    {
        *head = newNode;
        newNode->nodeNumber = 1;
    }
    else
    {
        // Traverses the list until it reaches the last node
        Node *last = *head;
        while (last->next != NULL)
            last = last->next;

        // Adds current node number and sets new node as the last node
        newNode->nodeNumber = last->nodeNumber + 1;
        last->next = newNode;
    }

    // Adds node data
    cout << "Enter student ID: ";
    string temp = "";
    cin >> temp;

    int tempInt = 0;
    bool valid = false;

    while (!valid || tempInt <= -1)
    {
        try
        {
            tempInt = stoi(temp);
            valid = true;
        }
        catch (invalid_argument const &e)
        {
            cout << "Invalid input. Please try again." << endl;
            cout << "Enter student ID: ";
            cin >> temp;
        }
    }

    if (isAlreadyID(tempInt, *head))
    {
        cout << "Student ID already exists. Please try again." << endl;
        sleep(1);
        return;
    }

    string name = "", section = "", subject = "";
    cout << "\nEnter student name: ";
    cin.ignore();
    getline(cin, name);
    validate(name);

    cout << "\nEnter section: ";
    getline(cin, section);
    validate(section);

    while (!isSectionValid(sectionHead, section))
    {
        cout << "Section does not exist. Please try again. (Type cancel if you want to cancel)" << endl;
        cout << "Available Sections:\n";
        displaySections(sectionHead);

        getline(cin, section);
        validate(section);

        if (section == "cancel")
        {
            cout << "\nCancelling..." << endl;
            sleep(1);
            return;
        }
    }

    SectionNode *sectionNode = getSectionNode(sectionHead, section);

    if (sectionNode == nullptr)
    {
        cout << "Error! Section not found." << endl;
        return;
    }

    cout << "\nEnter student subject/s: ";
    getline(cin, subject);
    validate(subject);

    newNode->studentID = tempInt;
    newNode->name = name;
    newNode->sectionNode.sectionName = sectionNode->sectionName;
    newNode->subject = subject;

    // done

    cout << "\n\n"
         << "Student #: " << newNode->studentID << "\n"
         << "Name: " << newNode->name << "\n"
         << "Section: " << newNode->sectionNode.sectionName << "\n"
         << "Subject/s: " << newNode->subject
         << endl;

    sleep(1);
}

void printList(Node **head)
{
    sleep(1);

    Node *current = *head;

    if (current == NULL)
    {
        cout << "\n\nList is empty, no data to output." << endl;
        sleep(1);
        return;
    }

    // Prints the linked list of chosen section
    cout << "\nSTUDENT LIST\n"
         << endl;
    cout << left << setw(15) << "NODE NUMBER"
         << left << setw(15) << "STUDENT ID"
         << left << setw(20) << "NAME"
         << left << setw(20) << "SECTION"
         << left << setw(20) << "SUBJECT/S"
         << endl;
    cout << string(84, '-') << endl; // Separator line

    while (current != NULL)
    {
        cout << left << setw(15) << current->nodeNumber
             << left << setw(15) << current->studentID
             << left << setw(20) << current->name
             << left << setw(20) << current->sectionNode.sectionName
             << left << setw(20) << current->subject
             << endl;

        current = current->next;
    }
}

bool isValidChoice(int choice) { return choice || choice == 0 || choice == 1 || choice == 2 || choice == 3; }

int main()
{
    // Initializing a head node
    Node *head = NULL;
    SectionNode *sectionHead = NULL;

    // Temporary menu for testing
    int choice = 0, loop = 0;

    do
    {
        cout << "\n\nSTUDENT LINKED LIST\n"
             << endl;
        cout << "[0] Exit\n[1] Add Students\n[2] Add Section\n[3] Display Sections\n[4] Print Student List\n"
             << endl;
        cout << "Select your action: ";
        cin >> choice;

        bool valid = isValidChoice(choice);

        while (!valid)
        {
            cout << "Invalid choice! Please select a valid choice: ";
            cin >> choice;
        }

        cout << endl;

        switch (choice)
        {
        case 1: // add student
            addStudentData(&head, sectionHead);
            break;

        case 2: // add section
            addSection(sectionHead);
            break;

        case 3: // display sections
            displaySections(sectionHead);
            break;

        case 4: // print students
            printList(&head);
            break;

        default:
            if (choice == 0 || !choice)
                continue;

            cout << "Select Again? [1] Yes | [0] No: ";

            while (loop != 0 && loop != 1)
            {
                cout << "Only 1 and 0 is accepted. Please try again.\n";
                cin >> loop;
            }

            if (loop = 0)
                choice = 0;
        }
    } while (choice != 0);

    cout << "Exiting program...";

    return 0;
}