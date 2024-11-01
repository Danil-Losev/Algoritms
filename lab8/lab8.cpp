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

int PRINT_MAX_SIZE = 10000; // Максимальное количество элементов для вывода
int TEST_STEP_SIZE = 50;    // Шаг для тестирования алгоритмов сортировки

// Определение структуры узла списка
struct Node
{
    int value;  // Значение, хранящееся в узле
    Node *next; // Указатель на следующий узел
};

// Функция для сортировки списка и измерения времени
Node *ListSort(Node *(*sort)(Node *), Node *fHead, long long &fTime);

// Функции для заполнения списка разными случаями
void FillListBestCase(Node *&fHead, int fSize);
void FillListMiddleCase(Node *&fHead, int fSize);
void FillListBadCase(Node *&fHead, int fSize);

// Различные алгоритмы сортировки для односвязного списка
Node *BubbleSortList(Node *fHead);
Node *SelectionSortList(Node *fHead);
Node *InsertionSortList(Node *fHead);

// Удаление всего списка
Node *DeleteList(Node *&fHead);

// Функция для вывода содержимого списка
void PrintList(Node *fHead);

// Функция для сортировки массива с измерением времени
int *ArraySort(int *(*sort)(int *&, int), int *&fArray, int fSize, long long &fTime);

// Функции для заполнения массива в разных случаях
void FillArrayBestCase(int *&fArray, int fSize);
void FillArrayMiddleCase(int *&fArray, int fSize);
void FillArrayBadCase(int *&fArray, int fSize);

// Алгоритмы сортировки для массивов
int *BubbleSortArray(int *&fArray, int fSize);
int *SelectionSortArray(int *&fArray, int fSize);
int *InsertionSortArray(int *&fArray, int fSize);

// Функция для вывода содержимого массива
void PrintArray(int *fArray, int fSize);

// Автотесты для списка и массива
void listAutoTest(int fMaxSize);
void arrayAutoTest(int fMaxSize);

// Функции для автоматического тестирования сортировки списков и массивов
long long autoSortTestForList(Node *(*sort)(Node *), void (*fill)(Node *&, int), int fSize);
long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize);

int main()
{
    int programm = 1;   // Переменная для контроля основного цикла программы
    int choose = 1;     // Выбор пользователем типа заполнения и сортировки
    int size = 1;       // Размер списка или массива
    long long sortTime; // Переменная для хранения времени сортировки

    while (programm != 0) // Основной цикл программы, завершается при вводе 0
    {
        std::system("cls"); // Очистка экрана перед вводом размера
        std::cout << "Enter the size of list / array: ";
        std::cin >> size; // Ввод размера массива или списка
        Sleep(500);       // Пауза для плавности работы интерфейса
        std::system("cls");

        Node *head;                   // Указатель на начало списка
        int *array = new int[size]{}; // Создание массива с заданным размером

        std::system("cls");
        std::cout << "Enter the type of filling list / array\n";
        std::cout << "  1) Best case\n";   // Лучший случай заполнения
        std::cout << "  2) Middle case\n"; // Средний случай заполнения
        std::cout << "  3) Bad case\n";    // Худший случай заполнения
        std::cout << "\n> ";
        std::cin >> choose;

        switch (choose) // Заполнение списка и массива на основе выбранного случая
        {
        case 1:
            FillListBestCase(head, size);
            FillArrayBestCase(array, size);
            break;
        case 2:
            FillListMiddleCase(head, size);
            FillArrayMiddleCase(array, size);
            break;
        case 3:
            FillListBadCase(head, size);
            FillArrayBadCase(array, size);
            break;
        }

        if (size <= PRINT_MAX_SIZE) // Проверка на размер для вывода списка и массива
        {
            std::cout << "\nList: ";
            PrintList(head); // Вывод элементов списка
            std::cout << "Array: ";
            PrintArray(array, size); // Вывод элементов массива
        }

        getch(); // Ожидание нажатия клавиши для продолжения
        std::system("cls");

        std::cout << "Enter the sort for list:\n";
        std::cout << "  1) Bubble Sort\n";      // Пузырьковая сортировка для списка
        std::cout << "  2) Selection Sort\n";   // Сортировка выбором для списка
        std::cout << "  3) Insertion Sort\n> "; // Сортировка вставками для списка
        std::cin >> choose;

        switch (choose) // Сортировка списка на основе выбранного алгоритма
        {
        case 1:
            head = ListSort(BubbleSortList, head, sortTime);
            break;
        case 2:
            head = ListSort(SelectionSortList, head, sortTime);
            break;
        case 3:
            head = ListSort(InsertionSortList, head, sortTime);
            break;
        }

        if (size <= PRINT_MAX_SIZE) // Вывод отсортированного списка
        {
            std::cout << "Sorted list: ";
            PrintList(head);
        }
        std::cout << "Sort time: " << sortTime << std::endl;

        getch();
        std::system("cls");

        std::cout << "Enter the sort for array:\n";
        std::cout << "  1) Bubble Sort\n";      // Пузырьковая сортировка для массива
        std::cout << "  2) Selection Sort\n";   // Сортировка выбором для массива
        std::cout << "  3) Insertion Sort\n> "; // Сортировка вставками для массива
        std::cin >> choose;

        switch (choose) // Сортировка массива выбранным алгоритмом
        {
        case 1:
            array = ArraySort(BubbleSortArray, array, size, sortTime);
            break;
        case 2:
            array = ArraySort(SelectionSortArray, array, size, sortTime);
            break;
        case 3:
            array = ArraySort(InsertionSortArray, array, size, sortTime);
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
        head = DeleteList(head); // Удаление элементов списка
        head = NULL;

        int choose1 = 0; // Переменная для автотеста
        std::cout << "Do you want to do auto test? (1=yes 0=no) : ";
        std::cin >> choose1;

        if (choose1 == 1)
        {
            std::system("cls");
            int sizeOfTest; // Размер данных для автотеста
            std::cout << "Enter the size of test: ";
            std::cin >> sizeOfTest;
            listAutoTest(sizeOfTest); // Запуск автотеста для списка
            std::cout << std::endl;
            arrayAutoTest(sizeOfTest); // Запуск автотеста для массива
            getch();
        }

        std::system("cls");
        std::cout << "Go to start? (1=yes 0=no)\n> ";
        std::cin >> programm; // Проверка на повтор программы
    }
    return 0;
}

Node *ListSort(Node *(*sort)(Node *), Node *fHead, long long &fTime)
{
    auto start = std::chrono::high_resolution_clock::now(); // Фиксация времени начала сортировки
    Node *Temp = sort(fHead); // Сортировка списка с использованием переданной функции
    auto end = std::chrono::high_resolution_clock::now(); // Фиксация времени окончания сортировки
    fTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count(); // Вычисление времени сортировки в микросекундах
    return Temp;          // Возврат отсортированного списка
}

void FillListBestCase(Node *&fHead, int fSize)
{
    fHead = new (Node); // Создание начального узла списка
    Node *curNode = fHead; // Указатель на текущий узел, инициализация начальным узлом
    (*curNode).next = NULL;
    (*curNode).value = 0; // Задание начального значения узла

    for (int i = 0; i < fSize; i++) // Заполнение списка по порядку, для наилучшего случая
    {
        (*curNode).next = new (Node); // Создание нового узла
        curNode = (*curNode).next;    // Переход к следующему узлу
        (*curNode).value = i + 1; // Присвоение значения, увеличенного на единицу
        (*curNode).next = NULL;   // Указатель на следующий элемент равен NULL
    }
}

void FillListMiddleCase(Node *&fHead, int fSize)
{
    fHead = new (Node);    // Создание начального узла списка
    Node *curNode = fHead; // Указатель на текущий узел
    (*curNode).next = NULL;
    (*curNode).value = 0; // Начальное значение узла

    for (int i = 0; i < fSize; i++) // Заполнение списка случайными значениями
    {
        (*curNode).next = new (Node);            // Создание нового узла
        curNode = (*curNode).next;               // Переход к следующему узлу
        (*curNode).value = (rand() % fSize) + 1; // Присвоение случайного значения
        (*curNode).next = NULL; // Указатель на следующий элемент равен NULL
    }
}

void FillListBadCase(Node *&fHead, int fSize)
{
    fHead = new (Node);    // Создание начального узла списка
    Node *curNode = fHead; // Инициализация указателя на текущий узел
    (*curNode).next = NULL;
    (*curNode).value = 0; // Установка начального значения
    for (int i = 0; i < fSize; i++) // Заполнение списка от большего к меньшему значению
    {
        (*curNode).next = new (Node); // Создание нового узла
        curNode = (*curNode).next;    // Переход к следующему узлу
        (*curNode).value = fSize - i; // Присвоение значения в порядке убывания
        (*curNode).next = NULL;       // Указатель на следующий элемент равен NULL
    }
}

Node *BubbleSortList(Node *fHead)
{
    Node *curNode;
    Node *lastSort = NULL; // Указатель на последний отсортированный элемент
    int temp;
    while (lastSort != (*fHead).next) // Повторение, пока весь список не будет отсортирован
    {
        curNode = (*fHead).next; // Установка начального узла для текущего прохода
        while ((*curNode).next != lastSort) // Проход по неотсортированной части списка
        {
            if ((*curNode).value > (*(*curNode).next).value) // Проверка и обмен значений
            {
                temp = (*curNode).value;
                (*curNode).value = (*(*curNode).next).value;
                (*(*curNode).next).value = temp;
            }
            curNode = (*curNode).next; // Переход к следующему узлу
        }
        lastSort = curNode; // Обновление указателя на последний отсортированный узел
    }
    return fHead; // Возвращение отсортированного списка
}

Node *SelectionSortList(Node *fHead)
{
    Node *curNode = (*fHead).next; // Указатель на текущий узел
    Node *searchNode, *minNode;
    int temp;
    while (curNode != NULL) // Итерация по списку для нахождения минимального элемента
    {
        minNode = curNode;            // Установка текущего узла как минимального
        searchNode = (*curNode).next; // Поиск узла с наименьшим значением
        while (searchNode != NULL)
        {
            if ((*searchNode).value < (*minNode).value)
            {
                minNode = searchNode; // Обновление минимального узла
            }
            searchNode = (*searchNode).next;
        }
        if (minNode != curNode) // Обмен значений, если найден новый минимум
        {
            temp = (*minNode).value;
            (*minNode).value = (*curNode).value;
            (*curNode).value = temp;
        }
        curNode = (*curNode).next; // Переход к следующему узлу
    }
    return fHead; // Возвращение отсортированного списка
}

Node *InsertionSortList(Node *fHead)
{
    Node *curNode, *searchNode;
    Node *sortedList = (*fHead).next; // Начало отсортированной части списка
    (*fHead).next = (*(*fHead).next).next;
    (*sortedList).next = NULL;
    while (fHead != NULL) // Проход по неотсортированной части списка
    {
        curNode = fHead;                            // Текущий элемент для вставки
        fHead = (*fHead).next;                      // Переход к следующему элементу
        if ((*curNode).value < (*sortedList).value) // Вставка в начало, если значение меньше
        {
            (*curNode).next = sortedList;
            sortedList = curNode;
        }
        else
        {
            searchNode = sortedList; // Поиск позиции для вставки в отсортированном списке
            while ((*searchNode).next != NULL)
            {
                if ((*(*searchNode).next).value > (*curNode).value)
                {
                    break;
                }
                searchNode = (*searchNode).next;
            }
            (*curNode).next = (*searchNode).next; // Вставка элемента в найденное место
            (*searchNode).next = curNode;
        }
    }
    return sortedList; // Возвращение отсортированного списка
}

Node *DeleteList(Node *&fHead)
{
    Node *curNode = (*fHead).next; // Указатель для прохода и удаления элементов списка
    while ((*curNode).next != NULL) // Удаление узлов списка до последнего элемента
    {
        Node *temp = curNode;      // Временный указатель на текущий узел
        curNode = (*curNode).next; // Переход к следующему узлу
        delete temp;               // Освобождение памяти текущего узла
    }
    delete fHead;           // Удаление начального узла списка
    delete curNode;         // Удаление последнего узла
    curNode = fHead = NULL; // Обнуление указателей на голову списка
    return fHead;           // Возврат пустого списка
}

void PrintList(Node *fHead)
{
    if (fHead == 0) // Проверка, является ли список пустым
    {
        return;
    }
    Node *curNode = fHead;          // Указатель для прохода по узлам списка
    while ((*curNode).next != NULL) // Перебор узлов до конца списка
    {
        curNode = (*curNode).next;            // Переход к следующему узлу
        std::cout << (*curNode).value << ' '; // Вывод значения текущего узла
    }
    std::cout << std::endl; // Переход на новую строку после вывода списка
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

int *BubbleSortArray(int *&fArray, int fSize)
{
    int temp; // Временная переменная для обмена значениями
    for (int i = 0; i < fSize - 1; i++) // Внешний цикл для проходов по массиву
    {
        for (int j = 0; j < fSize - i - 1; j++) // Внутренний цикл для сравнения соседних элементов
        {
            if (fArray[j] > fArray[j + 1]) // Проверка порядка элементов
            {
                temp = fArray[j]; // Обмен значениями, если порядок неправильный
                fArray[j] = fArray[j + 1];
                fArray[j + 1] = temp;
            }
        }
    }
    return fArray; // Возвращение отсортированного массива
}

int *SelectionSortArray(int *&fArray, int fSize)
{
    int minIndex, temp; // Индекс минимального элемента и временная переменная
    for (int i = 0; i < fSize; i++) // Внешний цикл по массиву
    {
        minIndex = i; // Инициализация минимального индекса текущей позиции
        for (int j = i + 1; j < fSize; j++) // Поиск минимального элемента в оставшейся части массива
        {
            if (fArray[j] < fArray[minIndex]) // Обновление минимального индекса
            {
                minIndex = j;
            }
        }
        temp = fArray[i]; // Обмен текущего элемента с минимальным
        fArray[i] = fArray[minIndex];
        fArray[minIndex] = temp;
    }
    return fArray; // Возвращение отсортированного массива
}

int *InsertionSortArray(int *&fArray, int fSize)
{
    for (int i = 1; i < fSize; i++) // Начинаем со второго элемента, так как первый элемент считается отсортированным
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

void listAutoTest(int fMaxSize)
{
    std::cout << "\n List Time Auto Test\n"; // Заголовок теста
    const int width = 12;                    // Ширина столбцов вывода

    std::cout << std::string(width * 11 + 11, '-') << std::endl; // Отделитель

    std::cout << std::setw(width / 2) << ' ' << " | " << std::setw(width) << ' ' << "   " << std::setw(width)
              << "Best case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width) << ' ' << "   "
              << std::setw(width) << "Average case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width)
              << ' ' << "   " << std::setw(width) << "Worst case" << "   " << std::setw(width) << ' ' << " | "
              << std::endl;

    // Заголовки типов сортировки
    std::cout << std::setw(width / 2) << "Count" << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width)
              << "Selection" << " | " << std::setw(width) << "Insertion" << " | " << std::setw(width) << "Bubble"
              << " | " << std::setw(width) << "Selection" << " | " << std::setw(width) << "Insertion"
              << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width) << "Selection" << " | "
              << std::setw(width) << "Insertion" << " | " << std::endl;

    // Отделитель
    std::cout << std::string(width * 11 + 11, '-') << std::endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE) // Цикл по размерам массива
    {
        int size = i; // Установка размера массива
        std::cout << std::setw(width / 2) << i << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(BubbleSortList, FillListBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(SelectionSortList, FillListBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForList(InsertionSortList, FillListBadCase, size) << " | " << std::endl;
    }
    std::cout << std::string(width * 11 + 11, '-') << std::endl; // Завершение теста
}

void arrayAutoTest(int fMaxSize)
{
    std::cout << "\n Array Time Auto Test\n"; // Заголовок теста для массивов
    const int width = 12;                     // Ширина столбцов вывода

    std::cout << std::string(width * 11 + 11, '-') << std::endl; // Отделитель

    std::cout << std::setw(width / 2) << ' ' << " | " << std::setw(width) << ' ' << "   " << std::setw(width)
              << "Best case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width) << ' ' << "   "
              << std::setw(width) << "Average case" << "   " << std::setw(width) << ' ' << " | " << std::setw(width)
              << ' ' << "   " << std::setw(width) << "Worst case" << "   " << std::setw(width) << ' ' << " | "
              << std::endl;

    // Заголовки типов сортировки
    std::cout << std::setw(width / 2) << "Count" << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width)
              << "Selection" << " | " << std::setw(width) << "Insertion" << " | " << std::setw(width) << "Bubble"
              << " | " << std::setw(width) << "Selection" << " | " << std::setw(width) << "Insertion"
              << " | " << std::setw(width) << "Bubble" << " | " << std::setw(width) << "Selection" << " | "
              << std::setw(width) << "Insertion" << " | " << std::endl;

    // Отделитель
    std::cout << std::string(width * 11 + 11, '-') << std::endl;
    for (int i = 100; i <= fMaxSize; i += TEST_STEP_SIZE) // Цикл по размерам массива
    {
        int size = i; // Установка размера массива
        std::cout << std::setw(width / 2) << i << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBestCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayMiddleCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(BubbleSortArray, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(SelectionSortArray, FillArrayBadCase, size) << " | " << std::setw(width)
                  << autoSortTestForArray(InsertionSortArray, FillArrayBadCase, size) << " | " << std::endl;
    }
    std::cout << std::string(width * 11 + 11, '-') << std::endl; // Завершение теста
}

long long autoSortTestForList(Node *(*sort)(Node *), void (*fill)(Node *&, int), int fSize)
{
    Node *testHead = NULL;                         // Указатель на начало списка
    fill(testHead, fSize);                         // Заполнение списка
    long long sortTime = 0;                        // Переменная для времени сортировки
    testHead = ListSort(sort, testHead, sortTime); // Сортировка списка
    DeleteList(testHead);                          // Удаление списка после сортировки
    return sortTime;                               // Возврат времени сортировки
}

long long autoSortTestForArray(int *(*sort)(int *&, int), void (*fill)(int *&, int), int fSize)
{
    int *testArray = new int[fSize]{}; // Создание массива заданного размера
    fill(testArray, fSize);            // Заполнение массива
    long long sortTime = 0;            // Переменная для времени сортировки
    testArray = ArraySort(sort, testArray, fSize, sortTime); // Сортировка массива
    delete[] testArray;                                      // Освобождение памяти
    testArray = NULL;                                        // Обнуление указателя
    return sortTime;                                         // Возврат времени сортировки
}
