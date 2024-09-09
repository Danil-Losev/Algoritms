#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_N = 5;
int SIZE_M = 4;
int MAX_NUMBER = 10;

int minColumnSumIndex(int **fArray, int sizeLine, int sizeColumn);
void showArray(int **fArray, int sizeLine, int sizeColumn);
int **fillArray(int **fArray, int sizeLine, int sizeColumn);

int main()
{
    int minColumn = 0;
    int **Array = new int *[SIZE_N];
    for (int i = 0; i < SIZE_N; i++)
    {
        Array[i] = new int[SIZE_M];
    }
    std::cout << "Array:" << std::endl;
    Array = fillArray(Array, SIZE_N, SIZE_M);
    showArray(Array, SIZE_N, SIZE_M);
    minColumn = minColumnSumIndex(Array, SIZE_N, SIZE_M);
    std::cout << std::endl;
    std::cout << "Column with minimum number of elements that are multiples of the sum of indices: " << minColumn
              << std::endl;
    for (int i = 0; i < SIZE_N; i++)
    {
        delete[] Array[i];
    }
    delete[] Array;
    return 0;
}

int minColumnSumIndex(int **fArray, int sizeLine, int sizeColumn)
{
    int *ColumnMultiplesCount = new int[sizeColumn]{};
    int MinIndex = 0;
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (fArray[i][j] % (i + j + 2) == 0)
            {
                ColumnMultiplesCount[j]++;
            }
        }
    }
    std::cout << "\nCount of multiplies in each column:" << std::endl;
    for (int i = 0; i < sizeColumn; i++)
    {
        std::cout << ColumnMultiplesCount[i] << '\t';
        if (ColumnMultiplesCount[i] < ColumnMultiplesCount[MinIndex])
        {
            MinIndex = i;
        }
    }
    return MinIndex + 1;
}

int **fillArray(int **fArray, int sizeLine, int sizeColumn)
{
    srand(time(0));
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            fArray[i][j] = rand() % MAX_NUMBER;
        }
    }
    return fArray;
}

void showArray(int **fArray, int sizeLine, int sizeColumn)
{
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            std::cout << fArray[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}
