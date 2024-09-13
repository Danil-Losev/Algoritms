#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_OF_ARRAY = 20; // размер массива

float sumOfMAxAndMin(int *fArray, int size);
int countOfNegativeElem(int *fArray, int size);
int *deleteNegativeElem(int *fArray, int &newArraySize, int size);
int *fillingAnArray(int *fArray, int size);

int main()
{
    int *Array = new int[SIZE_OF_ARRAY]{};         // создание массива (каждый элемент = 0)
    Array = fillingAnArray(Array, SIZE_OF_ARRAY);  // заполнение массива
    int *NoNegativeArray = new int[SIZE_OF_ARRAY]; // создание нового массива
    int sumMAXMIN = sumOfMAxAndMin(Array, SIZE_OF_ARRAY); // сумма MAX и MIN элементов массива
    int countOfNegativeHonestElem =
        countOfNegativeElem(Array, SIZE_OF_ARRAY); // количество отрицательных элементов с чётным индексом
    int newArraySize = 0;
    NoNegativeArray =
        deleteNegativeElem(Array, newArraySize, SIZE_OF_ARRAY); // заполнение массива не отрицательными элементами
    std::cout << "Array: " << std::endl;
    for (int i = 0; i < SIZE_OF_ARRAY; i++) // вывод исходного массива
    {
        std::cout << "Element [" << i << "]:  " << Array[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Sum of max and min ellements of array: " << sumMAXMIN << std::endl;
    std::cout << "Count of negative honest elements of array: " << countOfNegativeHonestElem << std::endl;
    std::cout << std::endl;
    std::cout << "Array without negative elements: " << std::endl;
    for (int i = 0; i < newArraySize; i++) // вывод нового массива
    {
        std::cout << "Element [" << i << "]:  " << NoNegativeArray[i] << std::endl;
    }
    // удаление массивов
    delete[] Array;
    delete[] NoNegativeArray;
    return 0;
}

float sumOfMAxAndMin(int *fArray, int size)
{
    int min = fArray[0];
    int max = fArray[0];
    for (int i = 0; i < size; i++) // поиск максимального и минимального элементов
    {
        if (fArray[i] < fArray[min])
        {
            min = i;
        }
        if (fArray[i] > fArray[max])
        {
            max = i;
        }
    }
    return fArray[min] + fArray[max]; // возврат суммы
}
int countOfNegativeElem(int *fArray, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if ((fArray[i] < 0) && (i % 2 == 0)) // подсчёт количества отрицательных элементов с чётным индексом
        {
            count++;
        }
    }
    return count;
}
int *deleteNegativeElem(int *fArray, int &newArraySize, int size)
{
    int negCount = 0;
    for (int i = 0; i < size; i++) // подсчёт отрицательных элементов
    {
        if (fArray[i] < 0)
        {
            negCount++;
        }
    }
    newArraySize = size - negCount;               // получение нового размера массива
    int *NoNegativeArray = new int[newArraySize]; // создание нового массива
    int point = 0;
    for (int i = 0; i < size; i++)
    {
        if (fArray[i] >= 0) // поиск положительных элементов
        {
            NoNegativeArray[point] = fArray[i]; // заполнение нового массива
            point++;
        }
    }
    return NoNegativeArray; // возврат нового массива
}
int *fillingAnArray(int *fArray, int size)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        fArray[i] = rand() % 201 - 100; // заполнение массива элементами от -100 до 100
    }
    return fArray; // возврат заполненного массива
}
