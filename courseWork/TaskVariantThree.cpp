#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <synchapi.h>
#include <windows.h>

int MAX_NUMBER = 1000000000;
int MAX_ARRAY_SIZE = 100;
int MIN_ARRAY_SIZE = 1;
std::string FILE_NAME = "output.txt";

int *stringToArray(int *&fArray, int fSize, const std::string fInput, bool &fError);
int *insertionSortArray(int *&fArray, int fSize);

void printArrayInSort(int *fArray, int fSize, int fIndexOfInsertElement, int fStart);
void printArray(int *fArray, int fSize, char fOpen, char fClose);
void printArrayInSortToFile(int *fArray, int fSize, int fIndexOfInsertElement, int fStart, std::string fFileName);

bool checkForSort(int *fArray, int fSize);

int main()
{
    bool isProgramm = true, isError = false;
    while (isProgramm)
    {
        int arraySize = 0;
        do
        {
            std::system("cls");
            isError = false;
            std::cout << "Enter the size of array ( 1 <= size <= 100 ): ";
            std::cin >> arraySize;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (arraySize > MAX_ARRAY_SIZE || arraySize < MIN_ARRAY_SIZE)
            {
                std::cout << "  ERROR: You entered the wrong size!!! \n  Please try again\n";
                Sleep(2000);
                isError = true;
            }
        } while (isError);
        int *array = new int[arraySize]{};
        std::string input;
        do
        {
            std::system("cls");
            isError = false;
            std::cout << "The size of array: " << arraySize << std::endl
                      << "Enter the array ( natural numbers not exceeding 10^9 ): ";
            std::getline(std::cin, input);
            array = stringToArray(array, arraySize, input, isError);
            if (isError)
            {
                std::cout << "  ERROR: Invalid input (e.g., number exceeds the limit or wrong format)!!!\n";
                Sleep(2000);
            }
        } while (isError);

        array = insertionSortArray(array, arraySize);

        std::cout << std::endl;
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << array[i] << "  ";
        }
        Sleep(2000);
        delete[] array;
        std::cout << "\nTry again? ( 1=yes , 0=no): ";
        std::cin >> isProgramm;
    }
    return 0;
}

int *stringToArray(int *&fArray, const int fSize, const std::string fInput, bool &fError)
{
    if (!fArray || fSize <= 0)
    {
        fError = true; // Ошибка: массив не был выделен или размер некорректен
        return nullptr;
    }
    std::istringstream numberStream(fInput);
    int number;
    int index = 0;
    fError = false; // Изначально ошибки нет
    // Чтение чисел из потока
    while (numberStream >> number)
    {
        if (number > MAX_NUMBER || index >= fSize || number <= 0)
        {
            fError = true;
            return fArray;
        }
        fArray[index] = number;
        ++index; // Увеличиваем индекс
    }
    // Заполнение оставшихся элементов массива нулями
    for (int i = index; i < fSize; i++)
    {
        fArray[i] = 0;
    }

    return fArray;
}

int *insertionSortArray(int *&fArray, int fSize)
{
    bool isSorted = checkForSort(fArray, fSize);
    if (isSorted == false)
    {

        std::cout << "\nYour array: ";
        printArray(fArray, fSize, '[', ']');
        std::cout << "\nSorting...\n";
        for (int i = 1; i < fSize;
             i++) // Начинаем со второго элемента, так как первый элемент считается отсортированным
        {
            int curInt = fArray[i]; // Текущий элемент для вставки
            int j;                  // Индекс для перемещения элементов
            // Сдвигаем элементы, которые больше текущего элемента, вправо
            for (j = i - 1; j >= 0 && fArray[j] > curInt; j--)
            {
                fArray[j + 1] = fArray[j]; // Сдвиг элемента вправо
            }
            fArray[j + 1] = curInt; // Вставка текущего элемента на его место
            printArrayInSort(fArray, fSize, j + 1, i + 1);
            printArrayInSortToFile(fArray, fSize, j + 1, i + 1, FILE_NAME);
        }
    }
    std::ofstream fileStream(FILE_NAME, std::ios::app | std::ios::ate);
    if (isSorted == true)
    {
        std::cout << "\nArray is sorted" << std::endl;
        fileStream << "\nArray is sorted" << std::endl;
    }
    fileStream << std::endl;
    fileStream.close();
    return fArray; // Возврат отсортированного массива
}

void printArrayInSort(int *fArray, int fSize, int fIndexOfInsertElement, int fStart)
{
    for (int i = 0; i < fSize; i++)
    {
        if (i < fIndexOfInsertElement)
        {
            std::cout << fArray[i] << "    ";
        }
        else if (i == fIndexOfInsertElement)
        {
            std::cout << '[' << fArray[i] << ']';
        }
        else if (i > fIndexOfInsertElement && i < fStart)
        {
            std::cout << " <- " << fArray[i];
        }
        else
        {
            std::cout << "    " << fArray[i];
        }
    }
    std::cout << std::endl;
}

void printArrayInSortToFile(int *fArray, int fSize, int fIndexOfInsertElement, int fStart, std::string fFileName)
{
    std::ofstream fileStream(fFileName, std::ios::app | std::ios::ate);
    // fileStream.open(fFileName, std::ios::app | std::ios::ate);
    if (fileStream.is_open())
    {
        fileStream << "Inserction: " << fStart - 1 << ":   ";
        for (int i = 0; i < fSize; i++)
        {
            if (i < fIndexOfInsertElement)
            {
                fileStream << fArray[i] << "    ";
            }
            else if (i == fIndexOfInsertElement)
            {
                fileStream << '[' << fArray[i] << ']';
            }
            else if (i > fIndexOfInsertElement && i < fStart)
            {
                fileStream << " <- " << fArray[i];
            }
            else
            {
                fileStream << "    " << fArray[i];
            }
        }
        fileStream << std::endl;
    }
    fileStream.close();
}

void printArray(int *fArray, int fSize, char fOpen, char fClose)
{
    for (int i = 0; i < fSize; i++)
    {
        std::cout << fOpen << fArray[i] << fClose << ' ';
    }
    std::cout << std::endl;
}

bool checkForSort(int *fArray, int fSize)
{
    bool isSorted = true;
    for (int i = 0; i < fSize; i++)
    {
        if (fArray[i] > fArray[i + 1])
        {
            isSorted = false;
        }
    }
    return isSorted;
}
