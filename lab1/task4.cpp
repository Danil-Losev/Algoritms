#include <cstdlib>
#include <ctime>
#include <iostream>

int MATRIX_SIZE = 6;
int MAX_NUMBER = 15;

int **arrayReplacingFunc(int **fArray, int sizeLine, int sizeColumn);
int **fillArray(int **fArray, int sizeLine, int sizeColumn);
void showArray(int **fArray, int sizeLine, int sizeColumn);

int main()
{
    int **Array = new int *[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        Array[i] = new int[MATRIX_SIZE];
    }
    std::cout << "Array:" << std::endl;
    Array = fillArray(Array, MATRIX_SIZE, MATRIX_SIZE);
    showArray(Array, MATRIX_SIZE, MATRIX_SIZE);
    std::cout << std::endl;
    std::cout << "Replaceing elements:" << std::endl;
    Array = arrayReplacingFunc(Array, MATRIX_SIZE, MATRIX_SIZE);
    showArray(Array, MATRIX_SIZE, MATRIX_SIZE);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        delete[] Array[i];
    }
    delete[] Array;
    return 0;
}

int **arrayReplacingFunc(int **fArray, int sizeLine, int sizeColumn)
{
    if (sizeLine != sizeColumn)
    {
        std::cout << "The matrix is not square" << std::endl;
        return fArray;
    }
    else
    {
        int maxInLine = 0;
        int maxInLineIndex = 0;
        for (int i = 0; i < sizeLine; i++)
        {
            maxInLine = fArray[i][maxInLineIndex];
            for (int j = 0; j < sizeColumn; j++)
            {
                if (fArray[i][j] > maxInLine)
                {
                    maxInLine = fArray[i][j];
                    maxInLineIndex = j;
                }
            }
            int temp = fArray[i][i];
            fArray[i][i] = maxInLine;
            fArray[i][maxInLineIndex] = temp;
        }
        return fArray;
    }
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
            if (i == j)
            {
                std::cout << '[' << fArray[i][j] << ']' << '\t';
            }
            else
            {
                std::cout << fArray[i][j] << '\t';
            }
        }
        std::cout << std::endl;
    }
}
