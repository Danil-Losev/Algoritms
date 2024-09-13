
#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_LINE = 6;   // количество строк
int SIZE_COLUMN = 6; // количество столбцов

/**
 * @brief функция заполняет исходный массив случайными элементами
 *
 * @param fArray исходный массив
 * @param sizeLine количество строк
 * @param sizeColumn количество столбцов
 * @return возвращает заполненный массив
 */
int **defineArray(int **fArray, int sizeLine, int sizeColumn);

/**
 * @brief суммирует каждую строку массива
 *
 * @param fArray исходный массив
 * @param sizeLine количество строк
 * @param sizeColumn количество столбцов
 * @return возвращает массив где каждый элемент это сумма строки
 */
int *sumOfLineArray(int **fArray, int sizeLine, int sizeColumn);

/**
 * @brief функция ищет наибольший элемент
 *
 * @param fArray исходный массив
 * @param sizeLine размер массива
 * @return возвращает индекс наибольшего элемента
 */
int biggestLineOfArray(int *fArray, int sizeLine);

int main()
{
    int **Array = new int *[SIZE_LINE]; // объявление исходного массива
    int *sArray = new int[SIZE_LINE];   // массив сум каждой строки
    int numberOfBiggestLine = 0;        // индекс наибольшей суммы
    for (int i = 0; i < SIZE_LINE; i++)
    {
        Array[i] = new int[SIZE_COLUMN]; // объявление исходного массива
    }
    Array = defineArray(Array, SIZE_LINE, SIZE_COLUMN);
    sArray = sumOfLineArray(Array, SIZE_LINE, SIZE_COLUMN);
    numberOfBiggestLine = biggestLineOfArray(sArray, SIZE_LINE);
    std::cout << "LINE WITH THE BIGGEST SUM: " << numberOfBiggestLine << " + 1 = " << numberOfBiggestLine + 1;
    // удаление массивов
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
    srand(time(0)); // задание рандомного сида
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            fArray[i][j] = rand() % 20; // заполнение массива случайными элементами
            std::cout << fArray[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    return fArray; // возврат заполненного массива
}
int *sumOfLineArray(int **fArray, int sizeLine, int sizeColumn)
{
    int *sArray = new int[sizeLine];
    std::cout << std::endl;
    for (int i = 0; i < sizeLine; i++) // суммирование каждой строки
    {
        sArray[i] = 0;
        for (int j = 0; j < sizeColumn; j++)
        {
            sArray[i] += fArray[i][j]; // суммирование каждого элемента строки
        }
        std::cout << "Sum of line " << i + 1 << " = " << sArray[i] << std::endl;
    }
    return sArray; // возврат массива сум
}
int biggestLineOfArray(int *fArray, int sizeLine)
{
    int biggestNum = 0;
    for (int i = 0; i < sizeLine; i++) // поиск наибольшего элемента
    {
        if (fArray[i] > fArray[biggestNum])
        {
            biggestNum = i; // сохранение индекса наибольшего элемента
        }
    }
    return biggestNum;
}
