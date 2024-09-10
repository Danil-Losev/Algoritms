#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_LINE = 6;
int SIZE_COLUMN = 6;

/**
 * @brief функция заполняет исходный массив случайными элементами
 *
 * @param fArray исходный массив
 * @param sizeLine колличество строк
 * @param sizeColumn колличество столбцов
 * @return возвращает заполненый массив
 */
int **defineArray(int **fArray, int sizeLine, int sizeColumn);

/**
 * @brief суммирует каждую строку массива
 *
 * @param fArray исходный массив
 * @param sizeLine колличество строк
 * @param sizeColumn колличество столбцов
 * @return возвращает массив где каждый эллемент это сумма строки
 */
int *sumOfLineArray(int **fArray, int sizeLine, int sizeColumn);

int biggestLineOfArray(int *fArray, int sizeLine);

int main()
{
    int **Array = new int *[SIZE_LINE];
    int *sArray = new int[SIZE_LINE];
    int numberOfBiggestLine = 0;
    for (int i = 0; i < SIZE_LINE; i++)
    {
        Array[i] = new int[SIZE_COLUMN];
    }
    Array = defineArray(Array, SIZE_LINE, SIZE_COLUMN);
    sArray = sumOfLineArray(Array, SIZE_LINE, SIZE_COLUMN);
    numberOfBiggestLine = biggestLineOfArray(sArray, SIZE_LINE);
    std::cout << "LINE WITH THE BIGGEST SUM: " << numberOfBiggestLine << " + 1 = " << numberOfBiggestLine + 1;
    for (int i = 0; i < SIZE_LINE; i++)
    {
        delete[] Array[i];
    }
    delete[] Array;
    delete[] sArray;
    return 0;
}

int **defineArray(int **fArray, int sizeLine, int sizeColumn)
{
    srand(time(0));
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            fArray[i][j] = rand() % 20;
            std::cout << fArray[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    return fArray;
}
int *sumOfLineArray(int **fArray, int sizeLine, int sizeColumn)
{
    int *sArray = new int[sizeLine];
    std::cout << std::endl;
    for (int i = 0; i < sizeLine; i++)
    {
        sArray[i] = 0;
        for (int j = 0; j < sizeColumn; j++)
        {
            sArray[i] += fArray[i][j];
        }
        std::cout << "Sum of line " << i + 1 << " = " << sArray[i] << std::endl;
    }
    return sArray;
}
int biggestLineOfArray(int *fArray, int sizeLine)
{
    int biggestNum = 0;
    for (int i = 0; i < sizeLine; i++)
    {
        if (fArray[i] > fArray[biggestNum])
        {
            biggestNum = i;
        }
    }
    return biggestNum;
}
