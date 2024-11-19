#include <chrono>     // Подключение библиотеки для работы со временем
#include <conio.h>    // Библиотека для ввода-вывода в консоли
#include <cstddef>    // Заголовочный файл для определения размера объектов
#include <cstdio>     // Стандартный ввод-вывод на уровне C
#include <cstdlib>    // Стандартные утилиты, включая случайные числа
#include <ctime>      // Для генерации текущего времени
#include <iomanip>    // Манипуляторы для форматирования вывода
#include <iostream>   // Основная библиотека для ввода-вывода в C++
#include <synchapi.h> // Для работы с функциями синхронизации в Windows
#include <windows.h>  // Основные функции Windows API

int PRINT_MAX_SIZE = 1000;
int TEST_STEP_SIZE = 50;

int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime);

void FillArrayBestCase(int *&fArray, int fSize);
void FillArrayMiddleCase(int *&fArray, int fSize);
void FillArrayBadCase(int *&fArray, int fSize);

int *PartQuickSort(int *&fArray, int fSize, int fStart, int fEnd);
int *QuickSort(int *&fArray, int fSize);

int *InsertionSort(int *&fArray, int fSize, int fStart, int fEnd);
int *PartShellSort(int *&fArray, int fSize, int fStart, int fEnd, int interval);
int *ShellSort(int *&fArray, int fSize);

int *ArrayToHeap(int *&fArray, int fSize, int fIndex);
int *PyramidSort(int *&fArray, int fSize);

int *ShakerSort(int *&fArray, int fSize);

void PrintArray(int *fArray, int fSize);

void arrayAutoTest(int fMaxSize);

long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize);

int main()
{
    int programm = 1; // Переменная для контроля основного цикла программы
    int choose = 1;   // Выбор пользователем типа заполнения и сортировки
    int size = 1;     // Размер массива
    long long sortTime = 0; // Переменная для хранения времени сортировки

    while (programm != 0) // Основной цикл программы, завершается при вводе 0
    {
        std::system("cls"); // Очистка экрана перед вводом размера
        std::cout << "Enter the size of array: ";
        std::cin >> size; // Ввод размера массива
        Sleep(500);       // Пауза для плавности работы интерфейса
        std::system("cls");

        int *array = new int[size]{}; // Создание массива с заданным размером

        std::system("cls");
        std::cout << "Enter the type of filling array\n";
        std::cout << "  1) Best case\n";   // Лучший случай заполнения
        std::cout << "  2) Middle case\n"; // Средний случай заполнения
        std::cout << "  3) Bad case\n";    // Худший случай заполнения
        std::cout << "\n> ";
        std::cin >> choose;

        switch (choose) // Заполнение массива на основе выбранного случая
        {
        case 1:
            FillArrayBestCase(array, size);
            break;
        case 2:
            FillArrayMiddleCase(array, size);
            break;
        case 3:
            FillArrayBadCase(array, size);
            break;
        }

        if (size <= PRINT_MAX_SIZE) // Проверка на размер для вывода массива
        {
            std::cout << "Array: ";
            PrintArray(array, size); // Вывод элементов массива
        }

        getch(); // Ожидание нажатия клавиши для продолжения
        std::system("cls");

        std::cout << "Enter the sort for array:\n";
        std::cout << "  1) Quick Sort\n";
        std::cout << "  2) Shell Sort\n";
        std::cout << "  3) Pyramid Sort\n";
        std::cout << "  4) Shaker Sort\n> ";
        std::cin >> choose;

        switch (choose) // Сортировка массива выбранным алгоритмом
        {
        case 1:
            array = ArraySort(QuickSort, array, size, sortTime);
            break;
        case 2:
            array = ArraySort(ShellSort, array, size, sortTime);
            break;
        case 3:
            array = ArraySort(PyramidSort, array, size, sortTime);
            break;
        case 4:
            array = ArraySort(ShakerSort, array, size, sortTime);
            break;
        }

        if (size <= PRINT_MAX_SIZE) // Вывод отсортированного массива
        {
            std::cout << "Sorted array: ";
            PrintArray(array, size);
        }
        std::cout << "Sort time: " << sortTime << std::endl;

        getch();
        std::system("cls");

        delete[] array; // Удаление динамического массива после использования
        array = NULL;

        int choose1 = 0; // Переменная для автотеста
        std::cout << "Do you want to do auto test? (1=yes 0=no) : ";
        std::cin >> choose1;

        if (choose1 == 1)
        {
            std::system("cls");
            int sizeOfTest; // Размер данных для автотеста
            std::cout << "Enter the size of test: ";
            std::cin >> sizeOfTest;
            arrayAutoTest(sizeOfTest); // Запуск автотеста для массива
            getch();
        }

        std::system("cls");
        std::cout << "Go to start? (1=yes 0=no)\n> ";
        std::cin >> programm; // Проверка на повтор программы
    }
    return 0;
}

int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime)
{
    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени
    int *Temp = sort(fArray, fSize);                        // Вызов функции сортировки
    auto end = std::chrono::high_resolution_clock::now();   // Конец замера времени
    fTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Вычисление времени выполнения
    return Temp; // Возвращение отсортированного массива
}

void FillArrayBestCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++) // Заполнение массива отсортированными значениями
    {
        fArray[i] = i + 1; // Присвоение значения, увеличивающегося на 1
    }
}

void FillArrayMiddleCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++) // Заполнение массива случайными значениями
    {
        fArray[i] = (rand() % fSize) + 1; // Присвоение случайного значения
    }
}

void FillArrayBadCase(int *&fArray, int fSize)
{
    for (int i = 0; i < fSize; i++) // Заполнение массива значениями в порядке убывания
    {
        fArray[i] = fSize - i; // Присвоение значения, уменьшающегося на 1
    }
}

int *PartQuickSort(int *&fArray, int fSize, int fStart, int fEnd)
{

    if (fStart >= fEnd)
    {
        return fArray; // Условие выхода, если массив из одного элемента или пуст
    }

    int fSupportingElement = fArray[fEnd]; // Опорный элемент - последний элемент подмассива
    int fIndexOfSupportingElement = fStart; // Индекс разделения

    // Перестановка элементов
    for (int i = fStart; i < fEnd; i++)
    {
        if (fArray[i] <= fSupportingElement)
        {
            std::swap(fArray[i], fArray[fIndexOfSupportingElement]);
            fIndexOfSupportingElement++;
        }
    }
    std::swap(fArray[fIndexOfSupportingElement], fArray[fEnd]); // Размещение опорного элемента

    // Рекурсивные вызовы для левой и правой части массива
    PartQuickSort(fArray, fSize, fStart, fIndexOfSupportingElement - 1);
    PartQuickSort(fArray, fSize, fIndexOfSupportingElement + 1, fEnd);

    return fArray;
}

int *QuickSort(int *&fArray, int fSize)
{
    fArray = PartQuickSort(fArray, fSize, 0, fSize - 1);
    return fArray;
}

int *InsertionSort(int *&fArray, int fSize, int fStart, int fEnd)
{
    for (int i = fStart; i < fEnd;
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
    }
    return fArray; // Возврат отсортированного массива
}

int *PartShellSort(int *&fArray, int fSize, int fStart, int fEnd, int interval)
{
    interval = interval / 2;
    if (interval <= 0)
    {
        return fArray;
    }
    fArray = InsertionSort(fArray, fSize, fStart, interval);
    fArray = InsertionSort(fArray, fSize, interval, fEnd);
    fArray = PartShellSort(fArray, fSize, fStart, interval, interval);
    fArray = PartShellSort(fArray, fSize, interval, fEnd, interval);
    return fArray;
}

int *ShellSort(int *&fArray, int fSize)
{
    fArray = PartShellSort(fArray, fSize, 0, fSize, fSize);
    return fArray;
}

int *ArrayToHeap(int *&fArray, int fSize, int fIndex)
{
    int temp;
    int fTreeRoot = fIndex;
    int fLeftTree = 2 * fIndex + 1;
    int fRightTree = 2 * fIndex + 2;
    if (fLeftTree < fSize && fArray[fLeftTree] > fArray[fTreeRoot])
    {
        fTreeRoot = fLeftTree;
    }
    if (fRightTree < fSize && fArray[fRightTree] > fArray[fTreeRoot])
    {
        fTreeRoot = fRightTree;
    }
    if (fTreeRoot != fIndex)
    {
        temp = fArray[fIndex];
        fArray[fIndex] = fArray[fTreeRoot];
        fArray[fTreeRoot] = temp;
        fArray = ArrayToHeap(fArray, fSize, fTreeRoot);
    }
    return fArray;
}

int *PyramidSort(int *&fArray, int fSize)
{
    for (int i = fSize / 2 - 1; i >= 0; i--)
    {
        ArrayToHeap(fArray, fSize, i);
    }
    int temp;
    for (int i = fSize - 1; i >= 0; i--)
    {
        temp = fArray[0];
        fArray[0] = fArray[i];
        fArray[i] = temp;
        ArrayToHeap(fArray, i, 0);
    }
    return fArray;
}

int *ShakerSort(int *&fArray, int fSize)
{
    int LeftSide = 1, RightSide = fSize - 1, temp;
    bool sorted = true;
    do
    {
        sorted = true;
        for (int i = LeftSide; i <= RightSide; i++)
        {
            if (fArray[i - 1] > fArray[i])
            {
                temp = fArray[i - 1];
                fArray[i - 1] = fArray[i];
                fArray[i] = temp;
                sorted = false;
            }
        }
        RightSide--;
        for (int i = RightSide; i >= LeftSide; i--)
        {
            if (fArray[i] < fArray[i - 1])
            {
                temp = fArray[i];
                fArray[i] = fArray[i - 1];
                fArray[i - 1] = temp;
                sorted = false;
            }
        }
        LeftSide++;
    } while (sorted == false);
    return fArray;
}

void PrintArray(int *fArray, int fSize)
{
    if (fArray == 0) // Проверка на пустой массив
    {
        return; // Завершение функции, если массив пуст
    }
    for (int i = 0; i < fSize; i++) // Цикл для вывода элементов массива
    {
        std::cout << fArray[i] << ' '; // Вывод значения элемента массива
    }
    std::cout << std::endl; // Переход на новую строку после вывода массива
}

void arrayAutoTest(int fMaxSize)
{
    std::cout << "\n Array Time Auto Test\n"; // Заголовок теста для массивов
    const int width = 12;                     // Ширина столбцов вывода

    std::cout << std::string(width * 15 + 8, '-') << std::endl; // Отделитель

    std::cout << std::setw(width / 2) << ' ' << " | " << std::setw(width) << ' ' << "   " << std::setw(width * 2)
              << "Best case      " << "      " << std::setw(width) << ' ' << " | " << std::setw(width) << ' ' << "   "
              << std::setw(width * 2) << "Average case      " << "      " << std::setw(width) << ' ' << " | "
              << std::setw(width) << ' ' << "   " << std::setw(width * 2) << "Worst case      " << "      "
              << std::setw(width) << ' ' << " | " << std::endl;

    // Заголовки типов сортировки
    std::cout << std::setw(width / 2) << "Count" << " | " << std::setw(width) << "Quick" << " | " << std::setw(width)
              << "Shell" << " | " << std::setw(width) << "Pyramid" << " | " << std::setw(width) << "Shaker" << " | "
              << std::setw(width) << "Quick" << " | " << std::setw(width) << "Shell" << " | " << std::setw(width)
              << "Pyramid" << " | " << std::setw(width) << "Shaker" << " | " << std::setw(width) << "Quick" << " | "
              << std::setw(width) << "Shell" << " | " << std::setw(width) << "Pyramid" << " | " << std::setw(width)
              << "Shaker" << " | " << std::endl;

    // Отделитель
    std::cout << std::string(width * 15 + 8, '-') << std::endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE) // Цикл по размерам массива
    {
        int size = i; // Установка размера массива
        std::cout << std::setw(width / 2) << i << " | " << std::setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(QuickSort, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShellSort, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(PyramidSort, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(ShakerSort, FillArrayBadCase, size) << " | " << std::endl;
    }
    std::cout << std::string(width * 15 + 8, '-') << std::endl; // Завершение теста
}

long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize)
{
    int *testArray = new int[fSize]{}; // Создание массива заданного размера
    fill(testArray, fSize);            // Заполнение массива
    long long sortTime = 0;            // Переменная для времени сортировки
    testArray = ArraySort(sort, testArray, fSize, sortTime); // Сортировка массива
    delete[] testArray;                                      // Освобождение памяти
    testArray = NULL;                                        // Обнуление указателя
    return sortTime;
}
