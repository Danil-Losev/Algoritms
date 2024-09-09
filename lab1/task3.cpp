#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_OF_ARRAY = 20;

float sumOfMAxAndMin(int *fArray, int size);
int countOfNegativeElem(int *fArray, int size);
int *deleteNegativeElem(int *fArray, int &newArraySize, int size);
int *fillingAnArray(int *fArray, int size);

int main()
{
    int *Array = new int[SIZE_OF_ARRAY]{};
    Array = fillingAnArray(Array, SIZE_OF_ARRAY);
    int *NoNegativeArray = new int[SIZE_OF_ARRAY];
    int sumMAXMIN = sumOfMAxAndMin(Array, SIZE_OF_ARRAY);
    int countOfNegativeHonestElem = countOfNegativeElem(Array, SIZE_OF_ARRAY);
    int newArraySize = 0;
    NoNegativeArray = deleteNegativeElem(Array, newArraySize, SIZE_OF_ARRAY);
    std::cout << "Array: " << std::endl;
    for (int i = 0; i < SIZE_OF_ARRAY; i++)
    {
        std::cout << "Element [" << i << "]:  " << Array[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Sum of max and min ellements of array: " << sumMAXMIN << std::endl;
    std::cout << "Count of negative honest elements of array: " << countOfNegativeHonestElem << std::endl;
    std::cout << std::endl;
    std::cout << "Array without negative elements: " << std::endl;
    for (int i = 0; i < newArraySize; i++)
    {
        std::cout << "Element [" << i << "]:  " << NoNegativeArray[i] << std::endl;
    }
    delete[] Array;
    delete[] NoNegativeArray;
    return 0;
}

float sumOfMAxAndMin(int *fArray, int size)
{
    int min = fArray[0];
    int max = fArray[0];
    for (int i = 0; i < size; i++)
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
    return min + max;
}
int countOfNegativeElem(int *fArray, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if ((fArray[i] < 0) && (i % 2 == 0))
        {
            count++;
        }
    }
    return count;
}
int *deleteNegativeElem(int *fArray, int &newArraySize, int size)
{
    int negCount = 0;
    for (int i = 0; i < size; i++)
    {
        if (fArray[i] < 0)
        {
            negCount++;
        }
    }
    newArraySize = size - negCount;
    int *NoNegativeArray = new int[newArraySize];
    int point = 0;
    for (int i = 0; i < size; i++)
    {
        if (fArray[i] >= 0)
        {
            NoNegativeArray[point] = fArray[i];
            point++;
        }
    }
    return NoNegativeArray;
}
int *fillingAnArray(int *fArray, int size)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        fArray[i] = rand() % 201 - 100;
    }
    return fArray;
}
