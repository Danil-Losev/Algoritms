#include <cstdlib> // Для вызова системных команд, таких как очистка консоли
#include <fstream>  // Для работы с файлами ввода-вывода
#include <iostream> // Для работы с вводом-выводом через консоль
#include <limits> // Для определения числовых границ, используется в проверке ввода
#include <regex> // Для проверки строки на соответствие регулярному выражению
#include <sstream> // Для работы с потоками строк, используется для преобразования строки в числа
#include <string>  // Для работы со строками
#include <synchapi.h> // Для функции Sleep, задерживающей выполнение
#include <windows.h> // Для работы с системными функциями Windows, например, системного времени

// Установка глобальных переменных для задания ограничений и конфигурации программы
const int MAX_NUMBER = 1000000000; // Максимально допустимое значение элемента массива
const int MAX_ARRAY_SIZE = 100;             // Максимальный размер массива
const int MIN_ARRAY_SIZE = 1;               // Минимальный размер массива
const std::string FILE_NAME = "output.txt"; // Имя файла для записи данных

// Объявление функций с их прототипами
int *stringToArray(int *&fArray, int fSize, const std::string fInput, bool &fError); // Преобразование строки в массив
int *insertionSortArray(int *&fArray, int fSize); // Сортировка массива методом вставки

void printArrayInSort(int *fArray, int fSize, int fIndexOfInsertElement,
                      int fStart); // Вывод текущего состояния сортировки
void printArray(int *fArray, int fSize, char fOpen = ' ', char fClose = ' '); // Вывод массива с обрамлением
void printArrayInSortToFile(int *fArray, int fSize, int fIndexOfInsertElement, int fStart,
                            std::string fFileName); // Запись сортировки в файл

bool checkForSort(int *fArray, int fSize); // Проверка, отсортирован ли массив

int main()
{
    // Основной цикл программы
    bool isProgramm = true, isError = false; // Флаги для управления программой
    while (isProgramm)
    {
        int arraySize = 0; // Переменная для хранения размера массива
        do
        {
            std::system("cls"); // Очистка экрана перед вводом
            isError = false;    // Сбрасываем ошибку
            std::cout << "Enter the size of array ( 1 <= size <= 100 ): "; // Запрос размера массива
            std::cin >> arraySize;                                         // Ввод размера массива
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода

            // Проверка корректности введенного размера
            if (arraySize > MAX_ARRAY_SIZE || arraySize < MIN_ARRAY_SIZE || std::cin.fail())
            {
                std::cin.clear();  // Сброс флага ошибки потока
                std::cin.ignore(); // Игнорирование оставшегося ввода
                std::cout << "  ERROR: You entered the wrong size!!! \n  Please try again\n"; // Вывод ошибки
                Sleep(2000);    // Задержка для отображения сообщения
                isError = true; // Установка флага ошибки
            }
        } while (isError); // Повторяем, пока есть ошибка

        int *array = new int[arraySize]{};       // Создание динамического массива
        std::string input;                       // Строка для ввода значений массива
        std::regex pattern("^\\d+(\\s+\\d+)*$"); // Регулярное выражение для проверки ввода
        bool isSymbol = false;                   // Флаг корректности формата ввода

        do
        {
            std::system("cls"); // Очистка экрана перед вводом
            isError = false;    // Сброс флага ошибки
            std::cout << "The size of array: " << arraySize << std::endl
                      << "Enter the array ( natural numbers not exceeding 10^9 ): "; // Запрос массива
            std::getline(std::cin, input);                                           // Ввод строки
            array = stringToArray(array, arraySize, input, isError); // Преобразование строки в массив
            isSymbol = std::regex_match(input, pattern);             // Проверка формата ввода

            // Если формат некорректный или произошла ошибка
            if (isError || !isSymbol)
            {
                memset(array, 0, arraySize * sizeof(int)); // Очистка массива
                std::cout
                    << "  ERROR: Invalid input (e.g., number exceeds the limit or wrong format)!!!\n"; // Сообщение об
                                                                                                       // ошибке
                Sleep(2000); // Задержка для отображения
            }
        } while (isError || !isSymbol); // Повторяем, пока есть ошибка

        array = insertionSortArray(array, arraySize); // Сортировка массива методом вставки

        std::cout << std::endl;
        std::cout << "Sorted array: ";
        printArray(array, arraySize, '[', ']');         // Вывод отсортированного массива
        Sleep(2000);                                    // Задержка перед продолжением
        delete[] array;                                 // Удаление динамического массива
        std::cout << "\nTry again? ( 1=yes , 0=no ): "; // Запрос продолжения программы
        std::cin >> isProgramm;                         // Пользовательский ввод
    }
    return 0; // Завершение программы
}

// Функция преобразования строки в массив
int *stringToArray(int *&fArray, const int fSize, const std::string fInput, bool &fError)
{
    if (!fArray || fSize <= 0) // Проверяем корректность массива
    {
        fError = true;  // Устанавливаем флаг ошибки
        return nullptr; // Возвращаем пустое значение
    }
    std::istringstream numberStream(fInput); // Создаем поток для чтения строки
    int number;                              // Переменная для текущего числа
    int index = 0;                           // Индекс текущего элемента массива
    fError = false;                          // Изначально ошибок нет

    // Чтение чисел из строки
    while (numberStream >> number)
    {
        if (number > MAX_NUMBER || index >= fSize || number <= 0) // Проверка числа
        {
            fError = true; // Устанавливаем ошибку
            return fArray; // Возвращаем текущий массив
        }
        fArray[index] = number; // Записываем число в массив
        ++index;                // Переходим к следующему элементу
    }
    // Заполняем оставшиеся элементы массива нулями
    for (int i = index; i < fSize; i++)
    {
        fArray[i] = 0; // Заполняем нулями
    }

    return fArray; // Возвращаем массив
}

// Функция сортировки массива методом вставки
int *insertionSortArray(int *&fArray, int fSize)
{
    bool isSorted = checkForSort(fArray, fSize); // Проверка, отсортирован ли массив
    if (isSorted == false)                       // Если массив не отсортирован
    {
        std::cout << "\nYour array: ";
        printArray(fArray, fSize, '[', ']'); // Выводим исходный массив
        std::cout << "\nSorting...\n";

        // Начинаем с второго элемента, так как первый считается отсортированным
        for (int i = 1; i < fSize; i++)
        {
            int curInt = fArray[i]; // Текущий элемент, который нужно вставить
            int j;                  // Индекс для перемещения элементов

            // Перемещаем элементы, которые больше текущего элемента, вправо
            for (j = i - 1; j >= 0 && fArray[j] > curInt; j--)
            {
                fArray[j + 1] = fArray[j]; // Сдвигаем элемент вправо
            }
            fArray[j + 1] = curInt; // Вставляем текущий элемент на его место

            // Печать состояния массива в процессе сортировки
            printArrayInSort(fArray, fSize, j + 1, i + 1);
            // Записываем состояние массива в файл
            printArrayInSortToFile(fArray, fSize, j + 1, i + 1, FILE_NAME);
        }
    }

    // Если массив был отсортирован, записываем это в файл
    std::ofstream fileStream(FILE_NAME, std::ios::app | std::ios::ate);
    if (isSorted == true)
    {
        std::cout << "\nArray is sorted" << std::endl;
        fileStream << "\nArray is sorted" << std::endl;
    }
    fileStream << std::endl;
    fileStream.close();
    return fArray; // Возвращаем отсортированный массив
}

// Функция для вывода состояния массива в процессе сортировки
void printArrayInSort(int *fArray, int fSize, int fIndexOfInsertElement, int fStart)
{
    for (int i = 0; i < fSize; i++)
    {
        if (i < fIndexOfInsertElement)
        {
            std::cout << fArray[i] << "    "; // Выводим элементы до вставки
        }
        else if (i == fIndexOfInsertElement)
        {
            std::cout << '[' << fArray[i] << ']'; // Отображаем вставляемый элемент
        }
        else if (i > fIndexOfInsertElement && i < fStart)
        {
            std::cout << " <- " << fArray[i]; // Показываем элементы, которые были сдвинуты
        }
        else
        {
            std::cout << "    " << fArray[i]; // Оставшиеся элементы
        }
    }
    std::cout << std::endl; // Завершаем строку
}

// Функция для записи текущего состояния массива в файл в процессе сортировки
void printArrayInSortToFile(int *fArray, int fSize, int fIndexOfInsertElement, int fStart, std::string fFileName)
{
    std::ofstream fileStream(fFileName, std::ios::app | std::ios::ate); // Открываем файл для записи
    if (fileStream.is_open())
    {
        fileStream << "Inserction: " << fStart - 1 << ":   "; // Записываем шаг сортировки
        for (int i = 0; i < fSize; i++)
        {
            if (i < fIndexOfInsertElement)
            {
                fileStream << fArray[i] << "    "; // Записываем элементы до вставки
            }
            else if (i == fIndexOfInsertElement)
            {
                fileStream << '[' << fArray[i] << ']'; // Отображаем вставляемый элемент
            }
            else if (i > fIndexOfInsertElement && i < fStart)
            {
                fileStream << " <- " << fArray[i]; // Показываем сдвинутые элементы
            }
            else
            {
                fileStream << "    " << fArray[i]; // Записываем остальные элементы
            }
        }
        fileStream << std::endl; // Завершаем строку
    }
    fileStream.close(); // Закрываем файл
}

// Функция для вывода массива на экран
void printArray(int *fArray, int fSize, char fOpen, char fClose)
{
    for (int i = 0; i < fSize; i++)
    {
        std::cout << fOpen << fArray[i] << fClose << ' '; // Выводим каждый элемент с обрамлением
    }
    std::cout << std::endl; // Завершаем строку
}

// Функция для проверки, отсортирован ли массив
bool checkForSort(int *fArray, int fSize)
{
    bool isSorted = true; // По умолчанию считаем, что массив отсортирован
    for (int i = 0; i < fSize - 1; i++)
    {
        if (fArray[i] > fArray[i + 1]) // Если текущий элемент больше следующего
        {
            isSorted = false; // Массив не отсортирован
        }
    }
    return isSorted; // Возвращаем результат проверки
}
