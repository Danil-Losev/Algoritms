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

int PRINT_MAX_SIZE = 1000;
int TEST_STEP_SIZE = 50;


int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime);


void FillArrayBestCase(int *&fArray, int fSize);


void FillArrayMiddleCase(int *&fArray, int fSize);


void FillArrayBadCase(int *&fArray, int fSize);


int *PartQuickSort(int *&fArray, int fSize, int fStart, int fEnd);


int *QuickSort(int *&fArray, int fSize);


int *InsertionSort(int *&fArray, int fSize, int fStart, int fEnd);


int *PartShellSort(int *&fArray, int fSize, int fStart, int fEnd, int interval);


int *ShellSort(int *&fArray, int fSize);


int *ArrayToHeap(int *&fArray, int fSize, int fIndex);


int *PyramidSort(int *&fArray, int fSize);


int *ShakerSort(int *&fArray, int fSize);


void PrintArray(int *fArray, int fSize);


void arrayAutoTest(int fMaxSize);


long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize);

int main()
{
    int programm = 1; 
    int choose = 1;   
    int size = 1;     
    long long sortTime = 0; 

    while (programm != 0) 
    {
        system("cls"); 
        cout << "Enter the size of array: ";
        cin >> size; 
        Sleep(500);       
        system("cls");

        int *array = new int[size]{}; 

        system("cls");
        cout << "Enter the type of filling array\n";
        cout << "  1) Best case\n";   
        cout << "  2) Middle case\n"; 
        cout << "  3) Bad case\n";    
        cout << "\n> ";
        std::cin >> choose;

        switch (choose) 
        {
        case 1:
            FillArrayBestCase(array, size);
            break;
        case 2:
            FillArrayMiddleCase(array, size);
            break;
        case 3:
            FillArrayBadCase(array, size);
            break;
        }

        if (size <= PRINT_MAX_SIZE) 
        {
            cout << "Array: ";
            PrintArray(array, size); 
        }

        getch(); 
        system("cls");

        cout << "Enter the sort for array:\n";
        cout << "  1) Quick Sort\n";
        cout << "  2) Shell Sort\n";
        cout << "  3) Pyramid Sort\n";
        cout << "  4) Shaker Sort\n> ";
        cin >> choose;

        switch (choose)
        {
        case 1:
            array = ArraySort(QuickSort, array, size, sortTime);
            break;
        case 2:
            array = ArraySort(ShellSort, array, size, sortTime);
            break;
        case 3:
            array = ArraySort(PyramidSort, array, size, sortTime);
            break;
        case 4:
            array = ArraySort(ShakerSort, array, size, sortTime);
            break;
        }

        if (size <= PRINT_MAX_SIZE)
        {
            cout << "Sorted array: ";
            PrintArray(array, size);
        }
        cout << "Sort time: " << sortTime << std::endl;

        getch();
        system("cls");

        delete[] array; 
        array = NULL;

        int choose1 = 0;
        cout << "Do you want to do auto test? (1=yes 0=no) : ";
        cin >> choose1;

        if (choose1 == 1)
        {
            system("cls");
            int sizeOfTest;
            cout << "Enter the size of test: ";
            cin >> sizeOfTest;
            arrayAutoTest(sizeOfTest); 
            getch();
        }

        system("cls");
        cout << "Go to start? (1=yes 0=no)\n> ";
        cin >> programm; 
    }
    return 0;
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

int *PartQuickSort(int *&fArray, int fSize, int fStart, int fEnd)
{

    if (fStart >= fEnd)
    {
        return fArray; 
    }

    int fSupportingElement = fArray[fEnd]; 
    int fIndexOfSupportingElement = fStart;

 
    for (int i = fStart; i < fEnd; i++)
    {
        if (fArray[i] <= fSupportingElement)
        {
            swap(fArray[i], fArray[fIndexOfSupportingElement]);
            fIndexOfSupportingElement++;
        }
    }
    swap(fArray[fIndexOfSupportingElement], fArray[fEnd]); 


    PartQuickSort(fArray, fSize, fStart, fIndexOfSupportingElement - 1);
    PartQuickSort(fArray, fSize, fIndexOfSupportingElement + 1, fEnd);

    return fArray;
}

int *QuickSort(int *&fArray, int fSize)
{
    fArray = PartQuickSort(fArray, fSize, 0, fSize - 1);
    return fArray;
}

int *InsertionSort(int *&fArray, int fSize, int fStart, int fEnd)
{
    for (int i = fStart; i < fEnd; i++) 
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

int *PartShellSort(int *&fArray, int fSize, int fStart, int fEnd, int interval)
{
    interval = interval / 2; 
    if (interval <= 0)
    {
        return fArray; 
    }


    fArray = InsertionSort(fArray, fSize, fStart, interval);
    fArray = InsertionSort(fArray, fSize, interval, fEnd);


    fArray = PartShellSort(fArray, fSize, fStart, interval, interval);
    fArray = PartShellSort(fArray, fSize, interval, fEnd, interval);

    return fArray;
}

int *ShellSort(int *&fArray, int fSize)
{

    fArray = PartShellSort(fArray, fSize, 0, fSize, fSize);
    return fArray; 
}

int *ArrayToHeap(int *&fArray, int fSize, int fIndex)
{
    int temp;                        
    int fTreeRoot = fIndex;          
    int fLeftTree = 2 * fIndex + 1;  
    int fRightTree = 2 * fIndex + 2;


    if (fLeftTree < fSize && fArray[fLeftTree] > fArray[fTreeRoot])
    {
        fTreeRoot = fLeftTree; 
    }


    if (fRightTree < fSize && fArray[fRightTree] > fArray[fTreeRoot])
    {
        fTreeRoot = fRightTree; 
    }


    if (fTreeRoot != fIndex)
    {
        temp = fArray[fIndex];              
        fArray[fIndex] = fArray[fTreeRoot]; 
        fArray[fTreeRoot] = temp; 


        fArray = ArrayToHeap(fArray, fSize, fTreeRoot);
    }

    return fArray; 
}

int *PyramidSort(int *&fArray, int fSize)
{

    for (int i = fSize / 2 - 1; i >= 0; i--)
    {
        ArrayToHeap(fArray, fSize, i); 
    }

    int temp; 


    for (int i = fSize - 1; i >= 0; i--)
    {
        temp = fArray[0];
        fArray[0] = fArray[i]; 
        fArray[i] = temp; 


        ArrayToHeap(fArray, i, 0);
    }

    return fArray; 
}

int *ShakerSort(int *&fArray, int fSize)
{
    int LeftSide = 1, RightSide = fSize - 1, temp; 
    bool sorted = true; 

    do
    {
        sorted = true; 


        for (int i = LeftSide; i <= RightSide; i++)
        {
            if (fArray[i - 1] > fArray[i]) 
            {
                temp = fArray[i - 1]; 
                fArray[i - 1] = fArray[i]; 
                fArray[i] = temp;
                sorted = false; 
            }
        }
        RightSide--; 


        for (int i = RightSide; i >= LeftSide; i--)
        {
            if (fArray[i] < fArray[i - 1]) 
            {
                temp = fArray[i]; 
                fArray[i] = fArray[i - 1]; 
                fArray[i - 1] = temp; 
                sorted = false; 
            }
        }
        LeftSide++; 

    } while (sorted == false);

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
    cout << std::endl; 
}

void arrayAutoTest(int fMaxSize)
{
    cout << "\n Array Time Auto Test\n"; 
    const int width = 12;                    

    cout << string(width * 15 + 8, '-') << endl; 

    cout << setw(width / 2) << ' ' << " | " << setw(width) << ' ' << "   " << setw(width * 2)
              << "Best case      " << "      " << setw(width) << ' ' << " | " << setw(width) << ' ' << "   "
              << setw(width * 2) << "Average case      " << "      " << setw(width) << ' ' << " | "
              << setw(width) << ' ' << "   " << setw(width * 2) << "Worst case      " << "      "
              << setw(width) << ' ' << " | " << endl;

    
    cout << setw(width / 2) << "Count" << " | " << setw(width) << "Quick" << " | " << setw(width)
              << "Shell" << " | " << setw(width) << "Pyramid" << " | " << setw(width) << "Shaker" << " | "
              << setw(width) << "Quick" << " | " << setw(width) << "Shell" << " | " << setw(width)
              << "Pyramid" << " | " << setw(width) << "Shaker" << " | " << setw(width) << "Quick" << " | "
              << setw(width) << "Shell" << " | " << setw(width) << "Pyramid" << " | " << setw(width)
              << "Shaker" << " | " << endl;

   
    cout << string(width * 15 + 8, '-') << endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE) 
    {
        int size = i; 
        cout << setw(width / 2) << i << " | " << setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayBestCase, size) << " | " << setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayMiddleCase, size) << " | " << setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayBadCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayBadCase, size) << " | " << setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayBadCase, size) << " | " << setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayBadCase, size) << " | " << endl;
    }
    cout << string(width * 15 + 8, '-') << endl; 
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
