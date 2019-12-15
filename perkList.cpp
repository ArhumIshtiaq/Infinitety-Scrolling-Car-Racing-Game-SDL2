#include "perkList.hpp"

perkList::perkList()
{
    head = nullptr;
}

int perkList::size()
{
    Node *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

void perkList::append(perk *data)
{
    Node *newnode = new Node(data);
    Node *temp = head;
    if (head == nullptr)
    {
        head = newnode;
        return;
    }
    int count = 0;

    while (temp->next != nullptr)
    {
        temp = temp->next;
        count++;
    }
    newnode->next = temp->next;
    temp->next = newnode;
}

void perkList::remove()
{
    Node *temp = head;
    if (head->next == nullptr)
        head = NULL;
    for (int i = 0; i < this->size() - 2; i++)
    {
        temp = temp->next;
    }
    temp->next = NULL;
}

void perkList::removeAt(int idx)
{
    if (idx == 0)
    {
        head = head->next;
        return;
    }
    Node *temp = head;
    int count = 0;
    while (count < idx - 1 and temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    if (temp == NULL)
    {
        cout << "invalid index\n";
    }
    else
    {
        temp->next = temp->next->next;
    }
}

perk *perkList::at(int idx)
{ //gets the index of the node
    Node *temp = head;
    int count = 0;
    while (count < idx and temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        return temp->data;
    }
}
