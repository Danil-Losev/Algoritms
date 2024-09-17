#include <cstddef>
#include <iostream>

struct Node
{
    int value;
    Node *next;
};

void fillUserStack(Node *&fStack);
void deleteUserStack(Node *&fStack);
void push(Node *&fStack, int fValue);
void pop(Node *&fStack);
void printStack(Node *fStack);
int findValueOfStack(Node *fStack, int fValue);
int countOfNodesInStack(Node *fStack);
int maxValueOfStack(Node *fStack);

int main()
{
    int value;
    Node *stack = NULL;

    fillUserStack(stack);
    printStack(stack);

    std::cout << "\nAdding element to the stack: ";
    std::cin >> value;
    push(stack, value);
    printStack(stack);

    std::cout << "\nRemoving an element from a stack" << std::endl;
    pop(stack);
    printStack(stack);

    int countOfNodes = countOfNodesInStack(stack);
    std::cout << "\nNumber of elements in the stack: " << countOfNodes << std::endl;

    std::cout << "\nWhat element do you want to find: ";
    std::cin >> value;
    int countOfFoundElement = findValueOfStack(stack, value);
    std::cout << "Count of found element: " << countOfFoundElement << std::endl;

    int MaxValue = maxValueOfStack(stack);
    std::cout << "\nMax element of stack: " << MaxValue << std::endl;

    deleteUserStack(stack);
    printStack(stack);
    delete stack;
    return 0;
}

void fillUserStack(Node *&fStack)
{
    std::cout << "**Building a stack: **" << std::endl;
    int value;
    std::cout << "Enter the values of the information fields of the stack nodes (0 = end):" << '\n' << "> ";
    std::cin >> value;
    while (value != 0)
    {
        push(fStack, value);
        std::cout << "> ";
        std::cin >> value;
    }
    std::cout << "Stack built" << std::endl;
}
void deleteUserStack(Node *&fStack)
{
    std::cout << "\n**Stack removal**" << std::endl;
    while (fStack != NULL)
    {
        pop(fStack);
    }
}
void push(Node *&fStack, int fValue)
{
    Node *curNode = new (Node);
    (*curNode).value = fValue;
    (*curNode).next = fStack;
    fStack = curNode;
}
void pop(Node *&fStack)
{
    if (fStack != NULL)
    {
        Node *curNode = fStack;
        fStack = (*fStack).next;
        delete curNode;
    }
}
void printStack(Node *fStack)
{
    if (fStack == NULL)
    {
        std::cout << "Stack is empty" << std::endl;
    }
    else
    {
        Node *curNode = fStack;
        std::cout << "Stack: ";
        while (curNode != NULL)
        {
            std::cout << '\t' << (*curNode).value;
            curNode = (*curNode).next;
        }
        std::cout << std::endl;
    }
}
int findValueOfStack(Node *fStack, int fValue)
{
    int count = 0;
    Node *curNode = fStack;
    while (curNode != NULL)
    {
        if ((*curNode).value == fValue)
        {
            count++;
        }
        curNode = (*curNode).next;
    }
    return count;
}
int countOfNodesInStack(Node *fStack)
{
    int count = 0;
    Node *curNode = fStack;
    while (curNode != NULL)
    {
        count++;
        curNode = (*curNode).next;
    }
    return count;
}
int maxValueOfStack(Node *fStack)
{
    Node *curNode = fStack;
    int maxValue = (*curNode).value;
    while (curNode != NULL)
    {
        if ((*curNode).value > maxValue)
        {
            maxValue = (*curNode).value;
        }
        curNode = (*curNode).next;
    }
    return maxValue;
}
