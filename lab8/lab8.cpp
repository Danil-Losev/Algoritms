#include <chrono>
#include <conio.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <synchapi.h>
#include <windows.h>

int PRINT_MAX_SIZE = 50;

struct Node
{
    int value;
    Node *next;
};

Node *ListSort(Node *(*sort)(Node *), Node *fHead, long long &fTime);
void FillListBestCase(Node *&fHead, int fSize);
void FillListMiddleCase(Node *&fHead, int fSize);
void FillListBadCase(Node *&fHead, int fSize);
Node *BubbleSortList(Node *fHead);
Node *SelectionSortList(Node *fHead);
Node *InsertionSortList(Node *fHead);
Node *DeleteList(Node *&fHead);
void PrintList(Node *fHead);

Node *addNodeToSorted(Node *fSortedList, Node *fNewNode);
int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime);
void FillArrayBestCase(int *&fArray, int fSize);
void FillArrayMiddleCase(int *&fArray, int fSize);
void FillArrayBadCase(int *&fArray, int fSize);
int *BuabbleSortArray(int *&fArray, int fSize);
int *SelectionSortArray(int *&fArray, int fSize);
int *InsertionSortArray(int *&fArray, int fSize);
void PrintArray(int *fArray, int fSize);

int main()
{
    int programm = 1;
    int choose = 1;
    int size = 1;
    long long sortTime;
    std::system("cls");
    std::cout << "Enter the size of list / array: ";
    std::cin >> size;
    Sleep(500);
    std::system("cls");
    while (programm != 0)
    {
        Node *head;
        int *array = new int[size]{};
        std::system("cls");
        std::cout << "Enter the type of filling list / array\n";
        std::cout << "  1) Best case\n";
        std::cout << "  2) Middle case\n";
        std::cout << "  3) Bad case\n";
        std::cout << "\n> ";
        std::cin >> choose;
        switch (choose)
        {
        case 1:
            FillListBestCase(head, size);
            FillArrayBestCase(array, size);
            break;
        case 2:
            FillListMiddleCase(head, size);
            FillArrayMiddleCase(array, size);
            break;
        case 3:
            FillListBadCase(head, size);
            FillArrayBadCase(array, size);
            break;
        }
        if (size <= PRINT_MAX_SIZE)
        {
            std::cout << "\nList: ";
            PrintList(head);
            std::cout << "Array: ";
            PrintArray(array, size);
        }
        Sleep(1500);
        std::system("cls");
        std::cout << "Enter the sort for list:\n";
        std::cout << "  1) Bubble Sort\n";
        std::cout << "  2) Selection Sort\n";
        std::cout << "  3) Insertion Sort\n> ";
        std::cin >> choose;
        switch (choose)
        {
        case 1:
            head = ListSort(BubbleSortList, head, sortTime);
            break;
        case 2:
            head = ListSort(SelectionSortList, head, sortTime);
            break;
        case 3:
            head = ListSort(InsertionSortList, head, sortTime);
            break;
        }
        if (size <= PRINT_MAX_SIZE)
        {
            std::cout << "Sorted list: ";
            PrintList(head);
        }
        std::cout << "Sort time: " << sortTime << std::endl;
        getch();
        std::system("cls");
        std::cout << "Enter the sort for array:\n";
        std::cout << "  1) Bubble Sort\n";
        std::cout << "  2) Selection Sort\n";
        std::cout << "  3) Insertion Sort\n> ";
        std::cin >> choose;
        switch (choose)
        {
        case 1:
            array = ArraySort(BuabbleSortArray, array, size, sortTime);
            break;
        case 2:
            array = ArraySort(SelectionSortArray, array, size, sortTime);
            break;
        case 3:
            array = ArraySort(InsertionSortArray, array, size, sortTime);
            break;
        }
        if (size <= PRINT_MAX_SIZE)
        {
            std::cout << "Sorted array: ";
            PrintArray(array, size);
        }
        std::cout << "Sort time: " << sortTime << std::endl;
        getch();
        std::system("cls");
        delete[] array;
        array = NULL;
        head = DeleteList(head);
        head = NULL;
        std::cout << "Go to start? (1=yes 0=no)\n> ";
        std::cin >> programm;
    }
    return 0;
}

Node *ListSort(Node *(*sort)(Node *), Node *fHead, long long &fTime)
{
    auto start = std::chrono::high_resolution_clock::now();
    Node *Temp = sort(fHead);
    auto end = std::chrono::high_resolution_clock::now();
    fTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return Temp;
}

void FillListBestCase(Node *&fHead, int fSize)
{
    fHead = new (Node);
    Node *curNode = fHead;
    (*curNode).next = NULL;
    (*curNode).value = 0;
    for (int i = 0; i < fSize; i++)
    {
        (*curNode).next = new (Node);
        curNode = (*curNode).next;
        (*curNode).value = i + 1;
        (*curNode).next = NULL;
    }
}
void FillListMiddleCase(Node *&fHead, int fSize)
{
    fHead = new (Node);
    Node *curNode = fHead;
    (*curNode).next = NULL;
    (*curNode).value = 0;
    for (int i = 0; i < fSize; i++)
    {
        (*curNode).next = new (Node);
        curNode = (*curNode).next;
        (*curNode).value = (rand() % fSize) + 1;
        (*curNode).next = NULL;
    }
}
void FillListBadCase(Node *&fHead, int fSize)
{
    fHead = new (Node);
    Node *curNode = fHead;
    (*curNode).next = NULL;
    (*curNode).value = 0;
    for (int i = 0; i < fSize; i++)
    {
        (*curNode).next = new (Node);
        curNode = (*curNode).next;
        (*curNode).value = fSize - i;
        (*curNode).next = NULL;
    }
}

Node *BubbleSortList(Node *fHead)
{
    Node *curNode;
    Node *lastSort = NULL;
    int temp;
    while (lastSort != (*fHead).next)
    {
        curNode = (*fHead).next;
        while ((*curNode).next != lastSort)
        {
            if ((*curNode).value > (*(*curNode).next).value)
            {
                temp = (*curNode).value;
                (*curNode).value = (*(*curNode).next).value;
                (*(*curNode).next).value = temp;
            }
            curNode = (*curNode).next;
        }
        lastSort = curNode;
    }
    return fHead;
}
Node *SelectionSortList(Node *fHead)
{
    Node *curNode = (*fHead).next;
    Node *searchNode, *minNode;
    int temp;
    while (curNode != NULL)
    {
        minNode = curNode;
        searchNode = (*curNode).next;
        while (searchNode != NULL)
        {
            if ((*searchNode).value < (*minNode).value)
            {
                minNode = searchNode;
            }
            searchNode = (*searchNode).next;
        }
        if (minNode != curNode)
        {
            temp = (*minNode).value;
            (*minNode).value = (*curNode).value;
            (*curNode).value = temp;
        }
        curNode = (*curNode).next;
    }
    return fHead;
}

Node *addNodeToSorted(Node *fSortedList, Node *fNewNode)
{
    if (fSortedList == NULL || (*fNewNode).value < (*fSortedList).value)
    {
        (*fNewNode).next = fSortedList;
        return fNewNode;
    }
    Node *curNode = fSortedList;
    while ((*curNode).next != NULL && (*(*curNode).next).value < (*fNewNode).value)
    {
        curNode = (*curNode).next;
    }
    (*fNewNode).next = (*curNode).next;
    (*curNode).next = fNewNode;
    return fSortedList;
}

Node *InsertionSortList(Node *fHead)
{
    Node *sortedList = NULL;
    Node *curNode = (*fHead).next;
    while (curNode != NULL)
    {
        Node *nextNode = (*curNode).next;
        sortedList = addNodeToSorted(sortedList, curNode);
        curNode = nextNode;
    }
    return sortedList;
}

Node *DeleteList(Node *&fHead)
{
    Node *curNode = (*fHead).next;
    while ((*curNode).next != NULL)
    {
        Node *temp = curNode;
        curNode = (*curNode).next;
        delete temp;
    }
    delete fHead;
    delete curNode;
    curNode = fHead = NULL;
    return fHead;
}

void PrintList(Node *fHead)
{
    if (fHead == 0)
    {
        return;
    }
    Node *curNode = fHead;
    while ((*curNode).next != NULL)
    {
        curNode = (*curNode).next;
        std::cout << (*curNode).value << ' ';
    }
    std::cout << std::endl;
}

int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime)
{
    auto start = std::chrono::high_resolution_clock::now();
    int *Temp = sort(fArray, fSize);
    auto end = std::chrono::high_resolution_clock::now();
    fTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return Temp;
}

void FillArrayBestCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++)
    {
        fArray[i] = i + 1;
    }
}
void FillArrayMiddleCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++)
    {
        fArray[i] = (rand() % fSize) + 1;
    }
}
void FillArrayBadCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++)
    {
        fArray[i] = fSize - i;
    }
}

int *BuabbleSortArray(int *&fArray, int fSize)
{
    int temp;
    for (int i = 0; i < fSize - 1; i++)
    {
        for (int j = 0; j < fSize - i - 1; j++)
        {
            if (fArray[j] > fArray[j + 1])
            {
                temp = fArray[j];
                fArray[j] = fArray[j + 1];
                fArray[j + 1] = temp;
            }
        }
    }
    return fArray;
}
int *SelectionSortArray(int *&fArray, int fSize)
{
    int minIndex, temp;
    for (int i = 0; i < fSize; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < fSize; j++)
        {
            if (fArray[j] < fArray[minIndex])
            {
                minIndex = j;
            }
        }
        temp = fArray[i];
        fArray[i] = fArray[minIndex];
        fArray[minIndex] = temp;
    }
    return fArray;
}
int *InsertionSortArray(int *&fArray, int fSize)
{
    return fArray;
}
void PrintArray(int *fArray, int fSize)
{
    if (fArray == 0)
    {
        return;
    }
    for (int i = 0; i < fSize; i++)
    {
        std::cout << fArray[i] << ' ';
    }
    std::cout << std::endl;
}
