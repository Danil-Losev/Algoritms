#include <cstddef>
#include <iostream>

// Структура, представляющая узел двусвязного списка
struct Node
{
    int element;    // Элемент, хранящийся в узле
    Node *next;     // Указатель на следующий узел
    Node *previous; // Указатель на предыдущий узел
};

// Структура для представления самого двусвязного списка
struct List
{
    Node *start; // Указатель на начало списка
    Node *end;   // Указатель на конец списка
};

// Прототипы функций для работы со списком
void buildingList(Node *&startNode, Node *&endNode); // Построение списка
void outputForward(Node *startNode);                 // Вывод списка с начала до конца
void outputBackward(Node *endNode);                  // Вывод списка с конца до начала
void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement); // Вставка узла после заданного индекса
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement); // Вставка узла перед заданным индексом
void deleteNode(Node *&startNode, Node *&endNode, int fIndex); // Удаление узла по индексу
void deletingList(Node *&startNode, Node *&endNode);           // Удаление всего списка
Node *searchForward(Node *startNode, int fElement); // Поиск элемента с начала списка
Node *searchBackward(Node *endNode, int fElement);  // Поиск элемента с конца списка

// Главная функция программы
int main()
{
    int index, element; // Переменные для хранения индекса и элемента
    List myList;        // Объявление списка
    Node *searchNode;   // Указатель для хранения результата поиска

    // Построение двусвязного списка
    buildingList(myList.start, myList.end);

    // Вывод списка по порядку
    std::cout << "Forward output: ";
    outputForward(myList.start);

    // Вывод списка в обратном порядке
    std::cout << "Backward output: ";
    outputBackward(myList.end);

    // Вставка узла после указанного индекса
    std::cout << "Enter the index of node after insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertAfter(myList.start, myList.end, index, element);
    std::cout << "List: \n";
    outputForward(myList.start);

    // Вставка узла перед указанным индексом
    std::cout << "Enter the index of node before insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertBefore(myList.start, myList.end, index, element);
    std::cout << "List: \n";
    outputForward(myList.start);

    // Удаление узла по индексу
    std::cout << "Enter the index of element which you want ot delete: ";
    std::cin >> index;
    deleteNode(myList.start, myList.end, index);
    std::cout << "List: \n";
    outputForward(myList.start);

    // Поиск элемента с начала списка
    std::cout << "Enter the element which you want to find (from start): ";
    std::cin >> element;
    searchNode = searchForward(myList.start, element);

    // Поиск элемента с конца списка
    std::cout << "Enter the element which you want to find (from end): ";
    std::cin >> element;
    searchNode = searchBackward(myList.end, element);

    // Удаление всего списка
    deletingList(myList.start, myList.end);
    return 0;
}

// Функция для построения списка
void buildingList(Node *&startNode, Node *&endNode)
{
    int element;            // Переменная для хранения вводимого элемента
    Node *curNode;          // Текущий узел списка
    startNode = new (Node); // Инициализация первого узла
    curNode = startNode;    // Присваивание текущему узлу начальный узел
    (*startNode).next = NULL; // Указатель на следующий узел у первого узла равен NULL
    (*startNode).previous = NULL; // Указатель на предыдущий узел у первого узла равен NULL
    (*startNode).element = 0; // Начальный элемент списка равен 0 (служебное значение)
    std::cout << "Enter the elements of list (0 = end):" << '\n' << "> ";
    std::cin >> element;
    while (element != 0) // Пока введённый элемент не равен 0
    {
        (*curNode).next = new (Node); // Создание нового узла и привязка его к текущему
        (*((*curNode).next)).previous = curNode; // Присваивание предыдущего узла новому узлу
        curNode = (*curNode).next;               // Переход на следующий узел
        (*curNode).next = NULL;                  // Указатель на следующий узел равен NULL
        (*curNode).element = element; // Присваивание элементу текущего узла введённое значение
        endNode = curNode; // Обновление указателя на последний узел
        std::cout << "> ";
        std::cin >> element; // Ввод следующего элемента списка
    }
}

// Функция для вывода списка с начала до конца
void outputForward(Node *startNode)
{
    Node *curNode = (*startNode).next; // Начинаю с первого узла после служебного
    while (curNode != NULL)            // Пока не достигнут конец списка
    {
        std::cout << (*curNode).element << '\t'; // Вывод значения элемента узла
        curNode = (*curNode).next;               // Переход к следующему узлу
    }
    std::cout << std::endl;
}

// Функция для вывода списка с конца к началу
void outputBackward(Node *endNode)
{
    Node *curNode = endNode;            // Начинаю с последнего узла списка
    while ((*curNode).previous != NULL) // Пока не достигнут первый узел
    {
        std::cout << (*curNode).element << '\t'; // Вывод значения элемента узла
        curNode = (*curNode).previous;           // Переход к предыдущему узлу
    }
    std::cout << std::endl;
}

// Функция для вставки узла после указанного индекса
void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;   // Начинаю с первого узла после служебного
    Node *newNode = new (Node);          // Создаю новый узел для вставки
    for (int i = 0; i < fIndex - 1; i++) // Перехожу на узел по указанному индексу
    {
        if ((*curNode).next == NULL) // Если достигнут конец списка, прекращаю
        {
            break;
        }
        curNode = (*curNode).next; // Переход на следующий узел
    }
    (*newNode).element = fElement; // Присваиваю новому узлу значение элемента
    if ((*curNode).next != NULL)   // Если узел не последний в списке
    {
        (*newNode).next = (*curNode).next; // Привязываю новый узел к следующему узлу
        (*newNode).previous = (*(*curNode).next).previous; // Присваиваю новый указатель на предыдущий узел
        (*(*curNode).next).previous = newNode; // Обновляю указатель на новый узел у следующего узла
        (*curNode).next = newNode; // Привязываю новый узел к текущему узлу
    }
    else // Если узел последний
    {
        (*newNode).next = NULL;        // У нового узла нет следующего узла
        (*newNode).previous = curNode; // Устанавливаю предыдущий узел как текущий
        endNode = newNode;             // Обновляю указатель на последний узел
        (*curNode).next = newNode;     // Привязываю новый узел к текущему
    }
}

// Функция для вставки узла перед указанным индексом
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;   // Начинаю с первого узла после служебного
    Node *newNode = new (Node);          // Создаю новый узел для вставки
    for (int i = 0; i < fIndex - 1; i++) // Перехожу на узел по указанному индексу
    {
        if ((*curNode).next == NULL) // Если достигнут конец списка, прекращаю
        {
            break;
        }
        curNode = (*curNode).next; // Переход на следующий узел
    }
    (*newNode).element = fElement; // Присваиваю новому узлу значение элемента
    (*newNode).next = (*(*curNode).previous).next; // Привязываю новый узел к предыдущему
    (*newNode).previous = (*curNode).previous;     // Привязываю новый узел к следующему
    (*(*curNode).previous).next = newNode; // Обновляю указатель у предыдущего узла
    (*curNode).previous = newNode;         // Привязываю новый узел к текущему
}

// Функция для удаления узла по индексу
void deleteNode(Node *&startNode, Node *&endNode, int fIndex)
{
    Node *curNode = (*startNode).next;   // Начинаю с первого узла после служебного
    for (int i = 0; i < fIndex - 1; i++) // Перехожу на узел по указанному индексу
    {
        if ((*curNode).next == NULL) // Если достигнут конец списка, прекращаю
        {
            break;
        }
        curNode = (*curNode).next; // Переход на следующий узел
    }
    if ((*curNode).next != NULL) // Если узел не последний
    {
        (*(*curNode).next).previous = (*curNode).previous; // Обновляю указатель предыдущего узла
        (*(*curNode).previous).next = (*curNode).next; // Обновляю указатель следующего узла
        delete curNode;                                // Удаляю текущий узел
    }
    else // Если узел последний
    {
        (*(*curNode).previous).next = NULL; // У предыдущего узла больше нет следующего
        endNode = (*endNode).previous;      // Обновляю указатель на последний узел
        delete curNode;                     // Удаляю текущий узел
    }
}

// Функция для поиска элемента с начала списка
Node *searchForward(Node *startNode, int fElement)
{
    Node *curNode = (*startNode).next; // Начинаю с первого узла после служебного
    Node *foundNode = NULL;            // Переменная для хранения результата поиска
    while ((curNode != NULL) && (foundNode == NULL)) // Пока не найден элемент и не достигнут конец списка
    {
        std::cout << (*curNode).element << "  "; // Вывод значения текущего узла
        if ((*curNode).element == fElement)      // Если элемент найден
        {
            std::cout << "\nElement found"; // Сообщение о нахождении элемента
            foundNode = curNode;            // Присваиваю найденный узел
        }
        else // Если элемент не найден
        {
            curNode = (*curNode).next; // Переход к следующему узлу
        }
    }
    if (foundNode == NULL) // Если элемент не найден
    {
        std::cout << "\nElement not found"; // Сообщение о ненахождении элемента
    }
    std::cout << std::endl;
    return foundNode; // Возвращаю найденный узел или NULL
}

// Функция для поиска элемента с конца списка
Node *searchBackward(Node *endNode, int fElement)
{
    Node *curNode = endNode; // Начинаю с последнего узла списка
    Node *foundNode = NULL;  // Переменная для хранения результата поиска
    while (((*curNode).previous != NULL) && (foundNode == NULL)) // Пока не найден элемент и не достигнут первый узел
    {
        std::cout << (*curNode).element << "  "; // Вывод значения текущего узла
        if ((*curNode).element == fElement)      // Если элемент найден
        {
            std::cout << "\nElement found"; // Сообщение о нахождении элемента
            foundNode = curNode;            // Присваиваю найденный узел
        }
        else // Если элемент не найден
        {
            curNode = (*curNode).previous; // Переход к предыдущему узлу
        }
    }
    if (foundNode == NULL) // Если элемент не найден
    {
        std::cout << "\nElement not found"; // Сообщение о ненахождении элемента
    }
    std::cout << std::endl;
    return foundNode; // Возвращаю найденный узел или NULL
}

// Функция для удаления всего списка
void deletingList(Node *&startNode, Node *&endNode)
{
    Node *curNode = startNode;        // Начинаю с начального узла списка
    Node *nextNode = (*curNode).next; // Переменная для хранения следующего узла
    while ((*curNode).next != NULL)   // Пока не достигнут конец списка
    {
        delete curNode;             // Удаляю текущий узел
        curNode = nextNode;         // Переход на следующий узел
        nextNode = (*curNode).next; // Обновляю указатель на следующий узел
    }
    delete curNode;             // Удаляю последний узел
    startNode = endNode = NULL; // Обнуляю указатели на начало и конец списка
}
