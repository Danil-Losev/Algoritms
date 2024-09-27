#include <cstddef>
#include <iostream>

struct Node
{
    int element;
    Node *next;
    Node *previous;
};

struct List
{
    Node *start;
    Node *end;
};

void buildingList(Node *&startNode, Node *&endNode);
void outputForward(Node *startNode);
void outputBackward(Node *endNode);
void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement);
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement);
void deleteNode(Node *&startNode, Node *&endNode, int fIndex);
void deletingList(Node *&startNode, Node *&endNode);
Node *searchForward(Node *startNode, int fElement);
Node *searchBackward(Node *endNode, int fElement);

int main()
{
    int index, element;
    List myList;
    Node *searchNode;

    buildingList(myList.start, myList.end);

    std::cout << "Forward output: ";
    outputForward(myList.start);

    std::cout << "Backward output: ";
    outputBackward(myList.end);

    std::cout << "Enter the index of node after insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertAfter(myList.start, myList.end, index, element);
    std::cout << "List: \n";
    outputForward(myList.start);

    std::cout << "Enter the index of node before insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertBefore(myList.start, myList.end, index, element);
    std::cout << "List: \n";
    outputForward(myList.start);

    std::cout << "Enter the index of element which you want ot delete: ";
    std::cin >> index;
    deleteNode(myList.start, myList.end, index);
    std::cout << "List: \n";
    outputForward(myList.start);

    std::cout << "Enter the element which you want to find (from start): ";
    std::cin >> element;
    searchNode = searchForward(myList.start, element);

    std::cout << "Enter the element which you want to find (from end): ";
    std::cin >> element;
    searchNode = searchBackward(myList.end, element);

    deletingList(myList.start, myList.end);
    return 0;
}

void buildingList(Node *&startNode, Node *&endNode)
{
    int element;
    Node *curNode;
    startNode = new (Node);
    curNode = startNode;
    (*startNode).next = NULL;
    (*startNode).previous = NULL;
    (*startNode).element = 0;
    std::cout << "Enter the elements of list (0 = end):" << '\n' << "> ";
    std::cin >> element;
    while (element != 0)
    {
        (*curNode).next = new (Node);
        (*((*curNode).next)).previous = curNode;
        curNode = (*curNode).next;
        (*curNode).next = NULL;
        (*curNode).element = element;
        endNode = curNode;
        std::cout << "> ";
        std::cin >> element;
    }
}

void outputForward(Node *startNode)
{
    Node *curNode = (*startNode).next;
    while (curNode != NULL)
    {
        std::cout << (*curNode).element << '\t';
        curNode = (*curNode).next;
    }
    std::cout << std::endl;
}
void outputBackward(Node *endNode)
{
    Node *curNode = endNode;
    while ((*curNode).previous != NULL)
    {
        std::cout << (*curNode).element << '\t';
        curNode = (*curNode).previous;
    }
    std::cout << std::endl;
}

void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;
    Node *newNode = new (Node);
    for (int i = 0; i < fIndex - 1; i++)
    {
        if ((*curNode).next == NULL)
        {
            break;
        }
        curNode = (*curNode).next;
    }
    (*newNode).element = fElement;
    if ((*curNode).next != NULL)
    {
        (*newNode).next = (*curNode).next;
        (*newNode).previous = (*(*curNode).next).previous;
        (*(*curNode).next).previous = newNode;
        (*curNode).next = newNode;
    }
    else
    {
        (*newNode).next = NULL;
        (*newNode).previous = curNode;
        endNode = newNode;
        (*curNode).next = newNode;
    }
}
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;
    Node *newNode = new (Node);
    for (int i = 0; i < fIndex - 1; i++)
    {
        if ((*curNode).next == NULL)
        {
            break;
        }
        curNode = (*curNode).next;
    }
    (*newNode).element = fElement;
    (*newNode).next = (*(*curNode).previous).next;
    (*newNode).previous = (*curNode).previous;
    (*(*curNode).previous).next = newNode;
    (*curNode).previous = newNode;
}

void deleteNode(Node *&startNode, Node *&endNode, int fIndex)
{

    Node *curNode = (*startNode).next;
    for (int i = 0; i < fIndex - 1; i++)
    {
        if ((*curNode).next == NULL)
        {
            break;
        }
        curNode = (*curNode).next;
    }
    if ((*curNode).next != NULL)
    {
        (*(*curNode).next).previous = (*curNode).previous;
        (*(*curNode).previous).next = (*curNode).next;
        delete curNode;
    }
    else
    {
        (*(*curNode).previous).next = NULL;
        endNode = (*endNode).previous;
        delete curNode;
    }
}

Node *searchForward(Node *startNode, int fElement)
{
    Node *curNode = (*startNode).next;
    Node *foundNode = NULL;
    while ((curNode != NULL) && (foundNode == NULL))
    {
        std::cout << (*curNode).element << "  ";
        if ((*curNode).element == fElement)
        {
            std::cout << "\nElement found";
            foundNode = curNode;
        }
        else
        {
            curNode = (*curNode).next;
        }
    }
    if (foundNode == NULL)
    {
        std::cout << "\nElement not found";
    }
    std::cout << std::endl;
    return foundNode;
}
Node *searchBackward(Node *endNode, int fElement)
{
    Node *curNode = endNode;
    Node *foundNode = NULL;
    while (((*curNode).previous != NULL) && (foundNode == NULL))
    {
        std::cout << (*curNode).element << "  ";
        if ((*curNode).element == fElement)
        {
            std::cout << "\nElement found";
            foundNode = curNode;
        }
        else
        {
            curNode = (*curNode).previous;
        }
    }
    if (foundNode == NULL)
    {
        std::cout << "\nElement not found";
    }
    std::cout << std::endl;
    return foundNode;
}

void deletingList(Node *&startNode, Node *&endNode)
{
    Node *curNode = startNode;
    Node *nextNode = (*curNode).next;
    while ((*curNode).next != NULL)
    {
        delete curNode;
        curNode = nextNode;
        nextNode = (*curNode).next;
    }
    delete curNode;
    startNode = endNode = NULL;
}
