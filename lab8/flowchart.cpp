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
int TEST_STEP_SIZE = 50;

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
        system("cls");
        cout << "Enter the size of list / array: ";
        cin >> size;
        Sleep(500);
        system("cls");
        Node *head;
        int *array = new int[size]{};
        system("cls");
        cout << "Enter the type of filling list / array\n";
        cout << "  1) Best case\n";
        cout << "  2) Middle case\n";
        cout << "  3) Bad case\n";
        cout << "\n> ";
        cin >> choose;
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
            cout << "\nList: ";
            PrintList(head);
            cout << "Array: ";
            PrintArray(array, size);
        }
        getch();
        system("cls");
        cout << "Enter the sort for list:\n";
        cout << "  1) Bubble Sort\n";
        cout << "  2) Selection Sort\n";
        cout << "  3) Insertion Sort\n> ";
        cin >> choose;
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
            cout << "Sorted list: ";
            PrintList(head);
        }
        cout << "Sort time: " << sortTime << endl;
        getch();
        system("cls");
        cout << "Enter the sort for array:\n";
        cout << "  1) Bubble Sort\n";
        cout << "  2) Selection Sort\n";
        cout << "  3) Insertion Sort\n> ";
        cin >> choose;
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
            cout << "Sorted array: ";
            PrintArray(array, size);
        }
        cout << "Sort time: " << sortTime << endl;
        getch();
        system("cls");
        delete[] array;
        array = NULL;
        head = DeleteList(head);
        head = NULL;
        int choose1 = 0;
        cout << "Do you want to do auto test? (1=yes 0=no) : ";
        cin >> choose1;
        if (choose1 == 1)
        {
            system("cls");
            int sizeOfTest;
            cout << "Enter the size of test: ";
            cin >> sizeOfTest;
            listAutoTest(sizeOfTest);
            cout << endl;
            arrayAutoTest(sizeOfTest);
            getch();
        }
        system("cls");
        cout << "Go to start? (1=yes 0=no)\n> ";
        cin >> programm;
    }
    return 0;
}

Node *ListSort(Node *(*sort)(Node *), Node *fHead, long long &fTime)
{
    auto start = chrono::high_resolution_clock::now();
    Node *Temp = sort(fHead);
    auto end = chrono::high_resolution_clock::now();
    fTime = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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
D{
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
        cout << (*curNode).value << ' ';
    }
    cout << endl;
}

int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime)
{
    auto start = chrono::high_resolution_clock::now();
    int *Temp = sort(fArray, fSize);
    auto end = chrono::high_resolution_clock::now();
    fTime = chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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
        cout << fArray[i] << ' ';
    }
    cout << endl;
}

void listAutoTest(int fMaxSize)
{
    cout << "\n List Time Auto Test\n";
    const int width = 12;

    cout << string(width * 11 + 11, '-') << endl;

    cout << setw(width / 2) << ' ' << " | " << setw(width) << ' ' << "   " << setw(width)
              << "Best case" << "   " << setw(width) << ' ' << " | " << setw(width) << ' ' << "   "
              << setw(width) << "Average case" << "   " << setw(width) << ' ' << " | " << setw(width)
              << ' ' << "   " << setw(width) << "Worst case" << "   " << setw(width) << ' ' << " | "
              << endl;

   
    cout << setw(width / 2) << "Count" << " | " << setw(width) << "Bubble" << " | " << setw(width)
              << "Selection" << " | " << setw(width) << "Insertion" << " | " << setw(width) << "Bubble"
              << " | " << setw(width) << "Selection" << " | " << setw(width) << "Insertion"
              << " | " << setw(width) << "Bubble" << " | " << setw(width) << "Selection" << " | "
              << ssetw(width) << "Insertion" << " | " << endl;

    
    cout << string(width * 11 + 11, '-') << endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE)
    {
        int size = i;
        cout << setw(width / 2) << i << " | " << setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBestCase, size) << " | " << setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBestCase, size) << " | " << setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBestCase, size) << " | " << setw(width)
                  << autoSortTestForList(BubbleSortList, FillListMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForList(SelectionSortList, FillListMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForList(InsertionSortList, FillListMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBadCase, size) << " | " << setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBadCase, size) << " | " << setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBadCase, size) << " | " << endl;
    }
    cout << string(width * 11 + 11, '-') << endl;
}
void arrayAutoTest(int fMaxSize)
{
    cout << "\n Array Time Auto Test\n";
    const int width = 12;

    cout << string(width * 11 + 11, '-') << endl;

    cout << setw(width / 2) << ' ' << " | " << setw(width) << ' ' << "   " << setw(width)
              << "Best case" << "   " << setw(width) << ' ' << " | " << setw(width) << ' ' << "   "
              << setw(width) << "Average case" << "   " << setw(width) << ' ' << " | " << setw(width)
              << ' ' << "   " << setw(width) << "Worst case" << "   " << setw(width) << ' ' << " | "
              << endl;

    
    cout << setw(width / 2) << "Count" << " | " << setw(width) << "Bubble" << " | " << setw(width)
              << "Selection" << " | " << setw(width) << "Insertion" << " | " << setw(width) << "Bubble"
              << " | " << setw(width) << "Selection" << " | " << setw(width) << "Insertion"
              << " | " << setw(width) << "Bubble" << " | " << setw(width) << "Selection" << " | "
              << setw(width) << "Insertion" << " | " << endl;

  
    cout << string(width * 11 + 11, '-') << endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE)
    {
        int size = i;
        cout << setw(width / 2) << i << " | " << setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBadCase, size) << " | " << setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBadCase, size) << " | " << setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBadCase, size) << " | " << endl;
    }
    std::cout << std::string(width * 11 + 11, '-') << std::endl;
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