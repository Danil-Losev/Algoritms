#include <chrono>
#include <conio.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <synchapi.h>
#include <windows.h>

int PRINT_MAX_SIZE = 10000;

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

int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime);
void FillArrayBestCase(int *&fArray, int fSize);
void FillArrayMiddleCase(int *&fArray, int fSize);
void FillArrayBadCase(int *&fArray, int fSize);
int *BubbleSortArray(int *&fArray, int fSize);
int *SelectionSortArray(int *&fArray, int fSize);
int *InsertionSortArray(int *&fArray, int fSize);
void PrintArray(int *fArray, int fSize);

void listAutoTest(int fMaxSize);
void arrayAutoTest(int fMaxSize);

long long autoSortTestForList(Node *(*sort)(Node *), void (*fill)(Node *&, int), int fSize);
long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize);

int main()
{
    int programm = 1;
    int choose = 1;
    int size = 1;
    long long sortTime;
    while (programm != 0)
    {
        std::system("cls");
        std::cout << "Enter the size of list / array: ";
        std::cin >> size;
        Sleep(500);
        std::system("cls");
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
        getch();
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
            array = ArraySort(BubbleSortArray, array, size, sortTime);
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
        int choose1 = 0;
        std::cout << "Do you want to do auto test? (1=yes 0=no) : ";
        std::cin >> choose1;
        if (choose1 == 1)
        {
            std::system("cls");
            int sizeOfTest;
            std::cout << "Enter the size of test: ";
            std::cin >> sizeOfTest;
            listAutoTest(sizeOfTest);
            std::cout << std::endl;
            arrayAutoTest(sizeOfTest);
            getch();
        }
        std::system("cls");
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

Node *InsertionSortList(Node *fHead)
{
    Node *curNode, *searchNode;
    Node *sortedList = (*fHead).next;
    (*fHead).next = (*(*fHead).next).next;
    (*sortedList).next = NULL;
    while (fHead != NULL)
    {
        curNode = fHead;
        fHead = (*fHead).next;
        if ((*curNode).value < (*sortedList).value)
        {
            (*curNode).next = sortedList;
            sortedList = curNode;
        }
        else
        {
            searchNode = sortedList;
            while ((*searchNode).next != NULL)
            {
                if ((*(*searchNode).next).value > (*curNode).value)
                {
                    break;
                }
                searchNode = (*searchNode).next;
            }
            (*curNode).next = (*searchNode).next;
            (*searchNode).next = curNode;
        }
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

int *BubbleSortArray(int *&fArray, int fSize)
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
    for (int i = 1; i < fSize; i++)
    {
        int curInt = fArray[i];
        int j;
        for (j = i - 1; j >= 0 && fArray[j] > curInt; j--)
        {
            fArray[j + 1] = fArray[j];
        }
        fArray[j + 1] = curInt;
    }
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

void listAutoTest(int fMaxSize)
{
    std::cout << "\n List Time Auto Test\n";
    const int width = 12;

    std::cout << std::setw(width / 2) << ' ' << " | " << std::setw(width) << ' ' << "   " << std::setw(width)
              << "Best case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width) << ' ' << "   "
              << std::setw(width) << "Average case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width)
              << ' ' << "   " << std::setw(width) << "Worst case" << "   " << std::setw(width) << ' ' << " | "
              << std::endl;

    // Sort type headers
    std::cout << std::setw(width / 2) << "Count" << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width)
              << "Selection" << " | " << std::setw(width) << "Insertion" << " | " << std::setw(width) << "Bubble"
              << " | " << std::setw(width) << "Selection" << " | " << std::setw(width) << "Insertion"
              << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width) << "Selection" << " | "
              << std::setw(width) << "Insertion" << " | " << std::endl;

    // Отделитель
    std::cout << std::string(width * 11 + 11, '-') << std::endl;
    for (int i = 100; i <= fMaxSize; i += 100)
    {
        int size = i;
        std::cout << std::setw(width / 2) << i << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBadCase, size) << " | " << std::endl;
    }
}
void arrayAutoTest(int fMaxSize)
{
    std::cout << "\n Array Time Auto Test\n";
    const int width = 12;

    std::cout << std::setw(width / 2) << ' ' << " | " << std::setw(width) << ' ' << "   " << std::setw(width)
              << "Best case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width) << ' ' << "   "
              << std::setw(width) << "Average case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width)
              << ' ' << "   " << std::setw(width) << "Worst case" << "   " << std::setw(width) << ' ' << " | "
              << std::endl;

    // Sort type headers
    std::cout << std::setw(width / 2) << "Count" << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width)
              << "Selection" << " | " << std::setw(width) << "Insertion" << " | " << std::setw(width) << "Bubble"
              << " | " << std::setw(width) << "Selection" << " | " << std::setw(width) << "Insertion"
              << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width) << "Selection" << " | "
              << std::setw(width) << "Insertion" << " | " << std::endl;

    // Отделитель
    std::cout << std::string(width * 11 + 11, '-') << std::endl;
    for (int i = 100; i <= fMaxSize; i += 100)
    {
        int size = i;
        std::cout << std::setw(width / 2) << i << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBadCase, size) << " | " << std::endl;
    }
}

long long autoSortTestForList(Node *(*sort)(Node *), void (*fill)(Node *&, int), int fSize)
{
    Node *testHead = NULL;
    fill(testHead, fSize);
    long long sortTime = 0;
    testHead = ListSort(sort, testHead, sortTime);
    DeleteList(testHead);
    return sortTime;
}
long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize)
{
    int *testArray = new int[fSize]{};
    fill(testArray, fSize);
    long long sortTime = 0;
    testArray = ArraySort(sort, testArray, fSize, sortTime);
    delete[] testArray;
    testArray = NULL;
    return sortTime;
}
