#include "trafficList.hpp"

#include "textureManager.hpp"
#include "game.hpp"
#include "gameObjects.hpp"
#include "traffic.hpp"

trafficList::trafficList()
{
    head = nullptr;
}

int trafficList::size()
{
    NodeObstacle *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

void trafficList::append(Traffic *data)
{
    NodeObstacle *newnode = new NodeObstacle(data);
    NodeObstacle *temp = head;
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

void trafficList::remove()
{
    NodeObstacle *temp = head;
    if (head->next == nullptr)
        head = NULL;
    for (int i = 0; i < this->size() - 2; i++)
    {
        temp = temp->next;
    }
    temp->next = NULL;
}

void trafficList::removeAt(int idx)
{
    if (idx == 0)
    {
        head = head->next;
        return;
    }
    NodeObstacle *temp = head;
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

Traffic *trafficList::at(int idx)
{ //gets the index of the node
    NodeObstacle *temp = head;
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
