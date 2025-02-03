#include <cstdlib> 
#include <fstream> 
#include <iostream> 
#include <limits> 
#include <regex> 
#include <sstream> 
#include <string>  
#include <synchapi.h> 
#include <windows.h>

using namespace std;

const int MAX_NUMBER = 1000000000; 
const int MAX_ARRAY_SIZE = 100; 
const int MIN_ARRAY_SIZE = 1;   
const string FILE_NAME = "output.txt"; 


class DYNAMIC_ARRAY
{
  private:
    bool isError = false; 
    bool isSorted = true; 
    int *cArray;          
    int cSize;            

  public:
    DYNAMIC_ARRAY(int fSize); 
    ~DYNAMIC_ARRAY();         
    void deleteArray();       
    int get(int fIndex);      
    void set(int fIndex, int fElement); 
    bool getError();                    
    void isSort(); 
    void fillTheArray(const string fInput); 
    void insertionSortArray(); 
    void printArray(char fOpen = ' ', char fClose = ' '); 
    void printArrayInSort(int fIndexOfInsertElement, int fStart); 
    void printArrayInSortToFile(int fIndexOfInsertElement, int fStart,
                                string fFileName = FILE_NAME); 
};


int main()
{
    bool isProgram = true, sizeError = false; 
    while (isProgram)                        
    {
        int arraySize = 0; 
        do
        {
            system("cls"); 
            sizeError = false;  
            cout << "Enter the size of array ( 1 <= size <= 100 ): "; 
            cin >> arraySize;                                         
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


            if (arraySize > MAX_ARRAY_SIZE || arraySize < MIN_ARRAY_SIZE || cin.fail())
            {
                cin.clear(); 
                cin.ignore(); 
                cout << "  ERROR: You entered the wrong size!!! \n  Please try again\n"; 
                Sleep(2000);    
                sizeError = true; 
            }
        } while (sizeError);

        DYNAMIC_ARRAY array(arraySize); 

        string input; 
        regex pattern("^\\d+(\\s+\\d+)*$");
        bool isSymbol = false; 

        do
        {
            system("cls"); 
            cout << "The size of array: " << arraySize << endl
                      << "Enter the array ( natural numbers not exceeding 10^9 ): "; 
            getline(cin, input);       
            array.fillTheArray(input);
            isSymbol = regex_match(input, pattern); 

            if (array.getError() || !isSymbol)
            {
                cout << "  ERROR: Invalid input (e.g., number exceeds the limit or wrong format)!!!\n"; 
                Sleep(2000);
            }
        } while (array.getError() || !isSymbol); 

        array.insertionSortArray();
        cout << endl;
        cout << "Sorted array: ";
        array.printArray('[', ']'); 
        Sleep(2000);                
        array.deleteArray();      
        cout << "\nTry again? ( 1=yes , 0=no ): "; 
        cin >> isProgram;          
    }
    return 0; 
}


DYNAMIC_ARRAY::DYNAMIC_ARRAY(int fSize) : cSize(fSize)
{
    cArray = new int[cSize]{};
};


DYNAMIC_ARRAY::~DYNAMIC_ARRAY()
{
    delete[] cArray;  
    cArray = nullptr; 
}


void DYNAMIC_ARRAY::deleteArray()
{
    delete[] cArray;
    cArray = nullptr; 
}


int DYNAMIC_ARRAY::get(int fIndex)
{
    isError = false;                  
    if (fIndex >= 0 && fIndex < cSize) 
    {
        return cArray[fIndex]; 
    }
    else
    {
        cout << "\n  ERROR: You entered the wrong size!!! \n  "; 
        isError = true;                                             
        return 0;                                                   
    }
}


void DYNAMIC_ARRAY::set(int fIndex, int fElement)
{
    isError = false;                  
    if (fIndex >= 0 && fIndex < cSize) 
    {
        cArray[fIndex] = fElement; 
    }
    else
    {
        cout << "\n  ERROR: You entered the wrong size!!! \n  Please try again\n"; 
        isError = true; 
    }
}


bool DYNAMIC_ARRAY::getError()
{
    return isError; 
}


void DYNAMIC_ARRAY::isSort()
{
    for (int i = 0; i < cSize - 1; i++) 
    {
        if (cArray[i] > cArray[i + 1]) 
        {
            isSorted = false; 
        }
    }
}

void DYNAMIC_ARRAY::fillTheArray(const string fInput)
{
    isError = false;           
    if (!cArray || cSize <= 0) 
    {
        isError = true; 
    }
    else
    {
        istringstream numberStream(fInput); 
        int number;   
        int index = 0;

        while (numberStream >> number)
        {
            if (number > MAX_NUMBER || index >= cSize || number <= 0)
            {
                isError = true; 
                break;         
            }
            cArray[index] = number; 
            ++index;               
        }

        if (!isError)
        {
            for (int i = index; i < cSize; i++)
            {
                cArray[i] = 0; 
            }
        }
    }
}

void DYNAMIC_ARRAY::insertionSortArray()
{
    isSort();              
    if (isSorted == false) 
    {
        cout << "\nYour array: ";
        printArray('[', ']'); 
        cout << "\nSorting...\n";

        for (int i = 1; i < cSize; i++) 
        {
            int curInt = cArray[i]; 
            int j;                 

            
            for (j = i - 1; j >= 0 && cArray[j] > curInt; j--)
            {
                cArray[j + 1] = cArray[j]; 
            }
            cArray[j + 1] = curInt; 

            printArrayInSort(j + 1, i + 1); 
            printArrayInSortToFile(j + 1, i + 1); 
        }
    }

    ofstream fileStream(FILE_NAME, ios::app | ios::ate);
    if (isSorted == true)
    {
        cout << "\nArray is sorted" << endl;  
        fileStream << "\nArray is sorted" << endl; 
    }
    fileStream << endl;
    fileStream.close(); 
}

void DYNAMIC_ARRAY::printArray(char fOpen, char fClose)
{
    for (int i = 0; i < cSize; i++)
    {
        cout << fOpen << get(i) << fClose << ' '; 
    }
    cout << endl; 
}

void DYNAMIC_ARRAY::printArrayInSort(int fIndexOfInsertElement, int fStart)
{
    for (int i = 0; i < cSize; i++) 
    {
        if (i < fIndexOfInsertElement) 
        {
            cout << get(i) << "    ";
        }
        else if (i == fIndexOfInsertElement) 
        {
            cout << '[' << get(i) << ']';
        }
        else if (i > fIndexOfInsertElement && i < fStart) 
        {
            cout << " <- " << get(i);
        }
        else
        {
            cout << "    " << get(i);
        }
    }
    cout << endl; 
}

void DYNAMIC_ARRAY::printArrayInSortToFile(int fIndexOfInsertElement, int fStart, string fFileName)
{
    ofstream fileStream(fFileName, ios::app | ios::ate); 
    if (fileStream.is_open())
    {
        fileStream << "Insertion step: " << fStart - 1 << ":   "; 

        for (int i = 0; i < cSize; i++) 
        {
            if (i < fIndexOfInsertElement)
            {
                fileStream << get(i) << "    "; 
            }
            else if (i == fIndexOfInsertElement) 
            {
                fileStream << '[' << get(i) << ']'; 
            }
            else if (i > fIndexOfInsertElement && i < fStart) 
            {
                fileStream << " <- " << get(i); 
            }
            else 
            {
                fileStream << "    " << get(i); 
            }
        }
        fileStream << endl; 
    }
    fileStream.close(); 
}