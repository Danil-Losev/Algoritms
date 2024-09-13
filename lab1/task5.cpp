#include <cstdlib>
#include <ctime>
#include <iostream>

int SIZE_N = 5;      // Количество строк
int SIZE_M = 4;      // Количество столбцов
int MAX_NUMBER = 10; // Максимальное случайное число

int minColumnSumIndex(int **fArray, int sizeLine, int sizeColumn);
void showArray(int **fArray, int sizeLine, int sizeColumn);
int **fillArray(int **fArray, int sizeLine, int sizeColumn);

int main()
{
    int minColumn = 0;
    int **Array = new int *[SIZE_N]; // Создание двумерного массива
    for (int i = 0; i < SIZE_N; i++)
    {
        Array[i] = new int[SIZE_M]; // Выделение памяти для каждой строки
    }
    std::cout << "Array:" << std::endl;
    Array = fillArray(Array, SIZE_N, SIZE_M); // Заполнение массива случайными числами
    showArray(Array, SIZE_N, SIZE_M);         // Вывод массива на экран
    minColumn = minColumnSumIndex(Array, SIZE_N, SIZE_M); // Поиск столбца с минимальным количеством кратных элементов
    std::cout << std::endl;
    std::cout << "Column with minimum number of elements that are multiples of the sum of indices: " << minColumn
              << std::endl;
    for (int i = 0; i < SIZE_N; i++)
    {
        delete[] Array[i]; // Освобождение памяти для каждой строки
    }
    delete[] Array; // Освобождение памяти для массива
    return 0;
}

int minColumnSumIndex(int **fArray, int sizeLine, int sizeColumn)
{
    int *ColumnMultiplesCount = new int[sizeColumn]{}; // Массив для хранения количества кратных элементов
    int MinIndex = 0;
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (fArray[i][j] % (i + j + 2) == 0) // Проверка на кратность сумме индексов
            {
                ColumnMultiplesCount[j]++; // Увеличение счетчика для столбца
            }
        }
    }
    std::cout << "\nCount of multiplies in each column:" << std::endl;
    for (int i = 0; i < sizeColumn; i++)
    {
        std::cout << ColumnMultiplesCount[i] << '\t'; // Вывод количества кратных элементов
        if (ColumnMultiplesCount[i] < ColumnMultiplesCount[MinIndex])
        {
            MinIndex = i; // Поиск столбца с минимальным количеством кратных элементов
        }
    }
    return MinIndex + 1; // Возврат индекса столбца
}

int **fillArray(int **fArray, int sizeLine, int sizeColumn)
{
    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            fArray[i][j] = rand() % MAX_NUMBER; // Заполнение массива случайными числами
        }
    }
    return fArray; // Возврат заполненного массива
}

void showArray(int **fArray, int sizeLine, int sizeColumn)
{
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            std::cout << fArray[i][j] << '\t'; // Вывод массива на экран
        }
        std::cout << std::endl;
    }
}
