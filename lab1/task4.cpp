
#include <cstdlib>
#include <ctime>
#include <iostream>

int MATRIX_SIZE = 6; // размер массива
int MAX_NUMBER = 15; // максимальное число

int **arrayReplacingFunc(int **fArray, int sizeLine, int sizeColumn);
int **fillArray(int **fArray, int sizeLine, int sizeColumn);
void showArray(int **fArray, int sizeLine, int sizeColumn);

int main()
{
    int **Array = new int *[MATRIX_SIZE]; // создание массива
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        Array[i] = new int[MATRIX_SIZE];
    }
    std::cout << "Array:" << std::endl;
    Array = fillArray(Array, MATRIX_SIZE, MATRIX_SIZE); // заполнение массива
    showArray(Array, MATRIX_SIZE, MATRIX_SIZE);         // вывод массива
    std::cout << std::endl;
    std::cout << "Replaceing elements:" << std::endl;
    Array = arrayReplacingFunc(Array, MATRIX_SIZE, MATRIX_SIZE); // перестановка элементов
    showArray(Array, MATRIX_SIZE, MATRIX_SIZE);                  // вывод нового массива
    // удаление массива
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        delete[] Array[i];
    }
    delete[] Array;
    return 0;
}

int **arrayReplacingFunc(int **fArray, int sizeLine, int sizeColumn)
{
    if (sizeLine != sizeColumn) // проверка является ли матрица квадратной
    {
        std::cout << "The matrix is not square" << std::endl;
        return fArray; // если нет во выход из функции
    }
    else // если да то выполнение функции
    {
        int maxInLine = 0;      // максимальный элемент
        int maxInLineIndex = 0; // индекс максимального элемента
        for (int i = 0; i < sizeLine; i++)
        {
            maxInLine = fArray[i][maxInLineIndex];
            for (int j = 0; j < sizeColumn; j++) // поиск макимального элемента в строке
            {
                if (fArray[i][j] > maxInLine)
                {
                    maxInLine = fArray[i][j];
                    maxInLineIndex = j;
                }
            }
            int temp = fArray[i][i];          // временная переменная
            fArray[i][i] = maxInLine;         // замена на максимальное число
            fArray[i][maxInLineIndex] = temp; // замена на число в главной диагонали
        }
        return fArray; // возврат массива
    }
}
int **fillArray(int **fArray, int sizeLine, int sizeColumn)
{
    srand(time(0));
    for (int i = 0; i < sizeLine; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            fArray[i][j] = rand() % MAX_NUMBER; // заполнение массива случайными числами
        }
    }
    return fArray;
}
void showArray(int **fArray, int sizeLine, int sizeColumn) // функция выводит массив на экран
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
