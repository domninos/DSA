#pragma once

#include <iostream>
#include <unistd.h>
#include <algorithm>

using namespace std;

struct SectionNode
{
    string sectionName;
    SectionNode *next;
};

string toLower(const string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

SectionNode *getSectionNode(SectionNode *head, string sectionName)
{
    SectionNode *temp = head;
    while (temp != NULL)
    {
        if (toLower(temp->sectionName) == toLower(sectionName))
            return temp;
        temp = temp->next;
    }
    return temp;
}

SectionNode *createSectionNode(string sectionName)
{
    SectionNode *newNode = new SectionNode;
    newNode->sectionName = sectionName;
    newNode->next = NULL;
    return newNode;
}

void addSection(SectionNode *&head)
{
    string sectionName = "";

    cout << "\nPlease enter the section name: ";
    cin >> sectionName;

    if (sectionName.empty())
    {
        cout << "Error! Something went wrong adding section." << endl;
        return;
    }

    SectionNode *newNode = createSectionNode(sectionName);

    if (head == NULL)
        head = newNode;
    else
    {
        SectionNode *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    cout << "Section '" << sectionName << "' added successfully." << endl;
    sleep(1);
}

bool isSectionValid(SectionNode *head, string sectionName)
{
    if (head == NULL)
        return false;

    SectionNode *temp = head;
    while (temp != NULL)
    {
        if (toLower(temp->sectionName) == toLower(sectionName))
            return true;
        temp = temp->next;
    }

    return false;
}

void displaySections(SectionNode *head)
{
    if (head == NULL)
    {
        cout << "No sections available." << endl;
        sleep(1);
        return;
    }

    cout << "Sections available:" << endl;
    SectionNode *temp = head;
    int count = 1;
    while (temp != NULL)
    {
        cout << count << ". " << temp->sectionName << endl;
        temp = temp->next;
        count++;
    }

    sleep(1);
}
