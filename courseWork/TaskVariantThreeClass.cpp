#include <cstdlib> // Подключение библиотеки для выполнения системных команд, например, очистки консоли
#include <fstream> // Подключение библиотеки для работы с файлами
#include <iostream> // Подключение библиотеки для работы с вводом и выводом в консоль
#include <limits> // Подключение библиотеки для определения пределов чисел, используется в проверке ввода
#include <regex> // Подключение библиотеки для работы с регулярными выражениями
#include <sstream> // Подключение библиотеки для работы с потоками строк, преобразование строк в числа
#include <string>  // Подключение библиотеки для работы со строками
#include <thread> // Подключение библиотеки для использования функции sleep_for для пауз в выполнении
#include <chrono> // Подключение библиотеки для работы с функциями времени

// Объявление глобальных констант для ограничения размеров массива и записи данных
const int MAX_NUMBER = 1000000000; // Ограничение на максимальное значение элементов массива
const int MAX_ARRAY_SIZE = 100; // Ограничение на максимальный размер массива
const int MIN_ARRAY_SIZE = 1;   // Ограничение на минимальный размер массива
const std::string FILE_NAME = "output.txt"; // Название файла для записи данных




// Определение класса для работы с динамическими массивами
class DYNAMIC_ARRAY
{
  private:
    bool isError = false; // Флаг ошибок, возникающих при работе с массивом
    bool isSorted = true; // Флаг проверки упорядоченности массива
    int *cArray;          // Указатель на динамический массив
    int cSize;            // Текущий размер массива

  public:
    DYNAMIC_ARRAY(int fSize); // Конструктор для выделения памяти под массив
    ~DYNAMIC_ARRAY();         // Деструктор для очистки памяти
    void deleteArray();       // Метод для удаления динамического массива
    int get(int fIndex);      // Метод для получения элемента по индексу
    void set(int fIndex, int fElement); // Метод для установки элемента по индексу
    bool getError();                    // Метод для проверки наличия ошибок
    void isSort(); // Метод для проверки массива на упорядоченность
    void fillTheArray(const std::string& fInput); // Метод для заполнения массива из строки
    void insertionSortArray(); // Метод для сортировки массива вставками
    void printArray(char fOpen = ' ', char fClose = ' '); // Метод для вывода массива в консоль
    void printArrayInSort(int fIndexOfInsertElement, int fStart); // Метод для вывода отсортированного массива
    void printArrayInSortToFile(
        int fIndexOfInsertElement, int fStart,
        const std::string &fFileName = FILE_NAME); // Метод для записи отсортированного массива в файл
};

// Основная функция программы
int main()
{
    bool isProgram = true, sizeError = false; // Флаги продолжения программы и ошибок размера
    while (isProgram)                         // Главный цикл программы
    {
        int arraySize = 0; // Переменная для хранения размера массива
        do
        {
            std::cout << "\033[2J\033[1;1H"; // Очистка консоли перед вводом
            sizeError = false;  // Сброс флага ошибок
            std::cout << "Enter the size of array ( 1 <= size <= 100 ): "; // Запрос размера массива
            std::cin >> arraySize;                                         // Ввод размера массива
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода

            // Проверка корректности ввода размера массива
            if (arraySize > MAX_ARRAY_SIZE || arraySize < MIN_ARRAY_SIZE || std::cin.fail())
            {
                std::cin.clear();  // Сброс флага ошибки ввода
                std::cin.ignore(); // Очистка оставшегося ввода
                std::cout << "  ERROR: You entered the wrong size!!! \n  Please try again\n"; // Сообщение об ошибке
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Задержка перед повторным вводом
                sizeError = true; // Установка флага ошибки
            }
        } while (sizeError); // Повтор запроса до корректного ввода

        DYNAMIC_ARRAY array(arraySize); // Создание объекта класса с заданным размером массива

        std::string input; // Переменная для строки ввода значений массива
        std::regex pattern(R"(^\d+(\s+\d+)*$)"); // Регулярное выражение для проверки формата ввода
        bool isSymbol = false; // Флаг корректности ввода
        do
        {
            std::cout << "\033[2J\033[1;1H"; // Очистка консоли перед вводом
            std::cout << "The size of array: " << arraySize << std::endl
                      << "Enter the array ( natural numbers not exceeding 10^9 ): "; // Запрос значений массива
            std::getline(std::cin, input);               // Ввод строки значений массива
            array.fillTheArray(input);                   // Заполнение массива
            isSymbol = std::regex_match(input, pattern); // Проверка строки на соответствие формату

            // Проверка корректности ввода или наличия ошибок
            if (array.getError() || !isSymbol)
            {
                std::cout
                    << "  ERROR: Invalid input (e.g., number exceeds the limit or wrong format)!!!\n"; // Сообщение об
                                                                                                       // ошибке
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Задержка перед повторным вводом
            }
        } while (array.getError() || !isSymbol); // Повтор, пока ввод некорректен

        array.insertionSortArray(); // Сортировка массива методом вставок
        std::cout << std::endl;
        std::cout << "Sorted array: ";
        array.printArray('[', ']'); // Вывод отсортированного массива в консоль
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Задержка перед завершением цикла
        array.deleteArray();        // Удаление динамического массива
        std::cout << "\nTry again? ( 1=yes , 0=no ): "; // Запрос продолжения программы
        std::cin >> isProgram;                          // Чтение решения пользователя
    }
    return 0; // Возврат успешного завершения программы
}

// Реализация конструктора класса для инициализации массива
DYNAMIC_ARRAY::DYNAMIC_ARRAY(int fSize) : cSize(fSize)
{
    cArray = new int[cSize]{}; // Выделение памяти для массива заданного размера
};

// Реализация деструктора для освобождения памяти
DYNAMIC_ARRAY::~DYNAMIC_ARRAY()
{
    delete[] cArray;  // Удаление массива
    cArray = nullptr; // Обнуление указателя
}

// Метод для удаления массива
void DYNAMIC_ARRAY::deleteArray()
{
    delete[] cArray;  // Освобождение памяти массива
    cArray = nullptr; // Обнуление указателя для предотвращения утечек
}

// Метод для получения элемента по индексу
int DYNAMIC_ARRAY::get(int fIndex)
{
    isError = false;                   // Сброс флага ошибки
    if (fIndex >= 0 && fIndex < cSize) // Проверка индекса на корректность
    {
        return cArray[fIndex]; // Возврат значения элемента
    }
    else
    {
        std::cout << "\n  ERROR: You entered the wrong size!!! \n  "; // Сообщение об ошибке
        isError = true;                                               // Установка флага ошибки
        return 0;                                                     // Возврат нуля при ошибке
    }
}

// Метод для установки элемента по индексу
void DYNAMIC_ARRAY::set(int fIndex, int fElement)
{
    isError = false;                   // Сброс флага ошибки
    if (fIndex >= 0 && fIndex < cSize) // Проверка индекса на корректность
    {
        cArray[fIndex] = fElement; // Установка значения элемента
    }
    else
    {
        std::cout << "\n  ERROR: You entered the wrong size!!! \n  Please try again\n"; // Сообщение об ошибке
        isError = true; // Установка флага ошибки
    }
}

// Метод для проверки наличия ошибок
bool DYNAMIC_ARRAY::getError()
{
    return isError; // Возврат состояния флага ошибок
}

// Метод для проверки массива на упорядоченность
void DYNAMIC_ARRAY::isSort()
{
    for (int i = 0; i < cSize - 1; i++) // Итерация по элементам массива
    {
        if (cArray[i] > cArray[i + 1]) // Проверка на нарушение порядка
        {
            isSorted = false; // Установка флага неупорядоченности
        }
    }
}

void DYNAMIC_ARRAY::fillTheArray(const std::string& fInput)
{
    isError = false;           // Инициализируется флаг ошибки
    if (!cArray || cSize <= 0) // Проверяется корректность инициализации массива
    {
        isError = true; // Устанавливается ошибка, если массив не выделен или размер некорректен
    }
    else
    {
        std::istringstream numberStream(fInput); // Создается поток для обработки входной строки
        int number;    // Объявляется переменная для хранения числа
        int index = 0; // Устанавливается начальный индекс

        while (numberStream >> number) // Чтение чисел из строки
        {
            // Проверка условий корректности числа и индекса
            if (number > MAX_NUMBER || index >= cSize || number <= 0)
            {
                isError = true; // Если данные некорректны, устанавливается ошибка
                break;          // Прерывается цикл обработки
            }
            cArray[index] = number; // Число сохраняется в массиве
            ++index;                // Переход к следующему элементу
        }

        // Если ошибок нет, заполняются оставшиеся элементы массива нулями
        if (!isError)
        {
            for (int i = index; i < cSize; i++)
            {
                cArray[i] = 0; // Остальные элементы заполняются нулями
            }
        }
    }
}

void DYNAMIC_ARRAY::insertionSortArray()
{
    isSort();              // Проверяется, отсортирован ли массив
    if (isSorted == false) // Если массив не отсортирован
    {
        std::cout << "\nYour array: ";
        printArray('[', ']'); // Вывод исходного массива
        std::cout << "\nSorting...\n";

        for (int i = 1; i < cSize; i++) // Перебираются элементы массива
        {
            int curInt = cArray[i]; // Сохраняется текущий элемент
            int j;                  // Индекс для поиска позиции вставки

            // Сдвиг элементов вправо для освобождения места
            for (j = i - 1; j >= 0 && cArray[j] > curInt; j--)
            {
                cArray[j + 1] = cArray[j]; // Перемещение элементов
            }
            cArray[j + 1] = curInt; // Текущий элемент вставляется на правильное место

            printArrayInSort(j + 1, i + 1); // Отображение промежуточного состояния массива
            printArrayInSortToFile(j + 1, i + 1); // Сохранение состояния в файл
        }
    }

    // Проверка, если массив отсортирован
    std::ofstream fileStream(FILE_NAME, std::ios::app | std::ios::ate);
    if (isSorted == true)
    {
        std::cout << "\nArray is sorted" << std::endl;  // Вывод подтверждения сортировки
        fileStream << "\nArray is sorted" << std::endl; // Запись в файл
    }
    fileStream << std::endl;
    fileStream.close(); // Закрывается файл
}

void DYNAMIC_ARRAY::printArray(char fOpen, char fClose)
{
    for (int i = 0; i < cSize; i++) // Итерация по всем элементам массива
    {
        std::cout << fOpen << get(i) << fClose << ' '; // Вывод каждого элемента с указанными символами
    }
    std::cout << std::endl; // Завершение строки вывода
}

void DYNAMIC_ARRAY::printArrayInSort(int fIndexOfInsertElement, int fStart)
{
    for (int i = 0; i < cSize; i++) // Проход по массиву
    {
        if (i < fIndexOfInsertElement) // Элементы до вставки
        {
            std::cout << get(i) << "    ";
        }
        else if (i == fIndexOfInsertElement) // Текущий вставляемый элемент
        {
            std::cout << '[' << get(i) << ']';
        }
        else if (i > fIndexOfInsertElement && i < fStart) // Сдвинутые элементы
        {
            std::cout << " <- " << get(i);
        }
        else // Остальные элементы массива
        {
            std::cout << "    " << get(i);
        }
    }
    std::cout << std::endl; // Завершение строки
}

void DYNAMIC_ARRAY::printArrayInSortToFile(int fIndexOfInsertElement, int fStart, const std::string &fFileName)
{
    std::ofstream fileStream(fFileName, std::ios::app | std::ios::ate); // Открытие файла в режиме добавления данных
    if (fileStream.is_open()) // Проверка на успешное открытие файла
    {
        fileStream << "Insertion step: " << fStart - 1 << ":   "; // Запись текущего шага сортировки

        for (int i = 0; i < cSize; i++) // Обход всех элементов массива
        {
            if (i < fIndexOfInsertElement) // Элементы до вставляемого
            {
                fileStream << get(i) << "    "; // Запись без изменений
            }
            else if (i == fIndexOfInsertElement) // Вставляемый элемент
            {
                fileStream << '[' << get(i) << ']'; // Выделение скобками для наглядности
            }
            else if (i > fIndexOfInsertElement && i < fStart) // Сдвинутые элементы
            {
                fileStream << " <- " << get(i); // Указание стрелки для сдвинутых элементов
            }
            else // Остальные элементы массива
            {
                fileStream << "    " << get(i); // Обычная запись с отступом
            }
        }
        fileStream << std::endl; // Переход на новую строку после записи текущего состояния
    }
    fileStream.close(); // Закрытие файла для завершения операции
}
