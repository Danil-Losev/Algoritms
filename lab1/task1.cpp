#include <cstdlib>
#include <iostream>

// обьявление функций

/**
 * @brief функция возвращает ср. арф. между максимальным и минимальным елементом массива
 *
 * @param fArray получаемый массив
 * @param sizeAr размер массива
 * @param min ссылка на минимальный элемент
 * @param max ссылка на максимальный элемент
 * @return возвращает ср. арф
 */
float getMidleAndMaxMin(int *fArray, int sizeAr, int &min, int &max);

/**
 * @brief дает пользователю возможность заполнить массив
 *
 * @param fArray исходный массив
 * @param sizeAr размер массива
 * @return возвращает заполненый массив
 */
int *writeArray(int *fArray, int sizeAr);

/**
 * @brief функция выводит на экран массив
 *
 * @param fArray исходный массив
 * @param sizeAr размер массива
 */
void showArray(int *fArray, int sizeAr);

// точка входа в программу
int main()
{
    int size = 1, min = 0, max = 0; // обьявление переменных
    float midle = 0;
    std::cout << "Enter the size of array: ";
    std::cin >> size;                // получение размера массива
    int *Array = new int[size];      // создание динамического массива
    Array = writeArray(Array, size); // заполнение массивва
    midle = getMidleAndMaxMin(Array, size, min, max); // получение ср. арф. между макс. и мин. значениями
    std::cout << "\nArray:" << std::endl;
    showArray(Array, size); // вывод маасива
    std::cout << std::endl;
    std::cout << "Max: " << max << '\n' << "Min: " << min << std::endl; // вывод максимального и минимального елемента
    std::cout << "\nMidle of Max and Min element:" << midle << std::endl; // вывод ср. арф.
    return 0;
}

float getMidleAndMaxMin(int *fArray, int sizeAr, int &min, int &max)
{
    min = fArray[0]; // задание начальных значений
    max = fArray[0];
    for (int i = 0; i < sizeAr; i++) // поиск максимума и минимума
    {
        if (fArray[i] < min)
        {
            min = fArray[i];
        }
        if (fArray[i] > max)
        {
            max = fArray[i];
        }
    }
    return (static_cast<float>(min + max) / 2); // возврат среднего значения
}

int *writeArray(int *fArray, int sizeAr)
{
    for (int i = 0; i < sizeAr; i++) // цикл заполняющий массив
    {
        std::cout << "Ellement [" << i << "] = ";
        std::cin >> fArray[i]; // ввод елемента массива
    }
    return fArray; // возврат массива
}

void showArray(int *fArray, int sizeAr)
{
    for (int i = 0; i < sizeAr; i++) // цикл выводит кадый элемент массива
    {
        std::cout << fArray[i] << '\t';
    }
    std::cout << std::endl;
}
