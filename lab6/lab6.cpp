#include <cstddef>
#include <iostream>

// Определение структуры узла для двусвязного списка
struct Node
{
    int element;    // Значение, которое хранится в узле
    Node *next;     // Указатель на следующий узел в списке
    Node *previous; // Указатель на предыдущий узел
};

// Структура для управления началом и концом списка
struct List
{
    Node *start; // Указатель на первый узел списка
    Node *end;   // Указатель на последний узел списка
};

// Прототипы функций для работы с двусвязным списком
void buildingList(Node *&startNode, Node *&endNode); // Функция для создания списка
void outputForward(Node *startNode);                 // Вывод списка от начала к концу
void outputBackward(Node *endNode);                  // Вывод списка от конца к началу
void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement); // Вставка узла после заданного индекса
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement); // Вставка узла перед заданным индексом
void deleteNode(Node *&startNode, Node *&endNode, int fIndex); // Удаление узла по индексу
void deletingList(Node *&startNode, Node *&endNode);           // Удаление всех узлов списка
Node *searchForward(Node *startNode, int fElement); // Поиск элемента с начала списка
Node *searchBackward(Node *endNode, int fElement);  // Поиск элемента с конца списка

int main()
{
    int index, element; // Переменные для хранения индекса и значения элемента
    List myList;        // Создание структуры списка
    Node *searchNode; // Указатель для хранения найденного узла

    // Построение двусвязного списка
    buildingList(myList.start, myList.end);

    // Вывод списка в прямом порядке
    std::cout << "Forward output: ";
    outputForward(myList.start);

    // Вывод списка в обратном порядке
    std::cout << "Backward output: ";
    outputBackward(myList.end);

    // Ввод данных для вставки узла после заданного индекса
    std::cout << "Enter the index of node after insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertAfter(myList.start, myList.end, index, element); // Вставка узла
    std::cout << "List: \n";
    outputForward(myList.start); // Вывод обновленного списка

    // Ввод данных для вставки узла перед заданным индексом
    std::cout << "Enter the index of node before insert: ";
    std::cin >> index;
    std::cout << "Enter the element: ";
    std::cin >> element;
    insertBefore(myList.start, myList.end, index, element); // Вставка узла
    std::cout << "List: \n";
    outputForward(myList.start); // Вывод обновленного списка

    // Ввод индекса для удаления узла
    std::cout << "Enter the index of element which you want ot delete: ";
    std::cin >> index;
    deleteNode(myList.start, myList.end, index); // Удаление узла
    std::cout << "List: \n";
    outputForward(myList.start); // Вывод обновленного списка

    // Ввод элемента для поиска с начала списка
    std::cout << "Enter the element which you want to find (from start): ";
    std::cin >> element;
    searchNode = searchForward(myList.start, element); // Поиск узла

    // Ввод элемента для поиска с конца списка
    std::cout << "Enter the element which you want to find (from end): ";
    std::cin >> element;
    searchNode = searchBackward(myList.end, element); // Поиск узла

    // Удаление всего списка
    deletingList(myList.start, myList.end);
    return 0;
}

// Функция для построения двусвязного списка
void buildingList(Node *&startNode, Node *&endNode)
{
    int element;            // Вводимый элемент списка
    Node *curNode;          // Текущий узел
    startNode = new (Node); // Создание начального узла
    curNode = startNode;
    (*startNode).next = NULL;
    (*startNode).previous = NULL;
    (*startNode).element = 0; // Начальное значение
    std::cout << "Enter the elements of list (0 = end):" << '\n' << "> ";
    std::cin >> element;
    while (element != 0) // Продолжается до ввода 0
    {
        (*curNode).next = new (Node);            // Создание нового узла
        (*((*curNode).next)).previous = curNode; // Связь с предыдущим узлом
        curNode = (*curNode).next;               // Переход к следующему узлу
        (*curNode).next = NULL;
        (*curNode).element = element; // Присвоение значения новому узлу
        endNode = curNode;            // Обновление конца списка
        std::cout << "> ";
        std::cin >> element; // Ввод следующего элемента
    }
}

// Функция вывода списка в прямом порядке
void outputForward(Node *startNode)
{
    Node *curNode = (*startNode).next; // Переход к первому реальному узлу
    while (curNode != NULL)            // Проход по всему списку
    {
        std::cout << (*curNode).element << '\t'; // Вывод значения текущего узла
        curNode = (*curNode).next;               // Переход к следующему узлу
    }
    std::cout << std::endl;
}

// Функция вывода списка в обратном порядке
void outputBackward(Node *endNode)
{
    Node *curNode = endNode;            // Начало с конца списка
    while ((*curNode).previous != NULL) // Проход по узлам до начала
    {
        std::cout << (*curNode).element << '\t'; // Вывод значения текущего узла
        curNode = (*curNode).previous;           // Переход к предыдущему узлу
    }
    std::cout << std::endl;
}

// Вставка узла после заданного индекса
void insertAfter(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;   // Поиск начального узла
    Node *newNode = new (Node);          // Создание нового узла
    for (int i = 0; i < fIndex - 1; i++) // Поиск нужного индекса
    {
        if ((*curNode).next == NULL) // Проверка на конец списка
        {
            break;
        }
        curNode = (*curNode).next; // Переход к следующему узлу
    }
    (*newNode).element = fElement; // Присвоение значения новому узлу
    if ((*curNode).next != NULL)   // Проверка наличия следующего узла
    {
        (*newNode).next = (*curNode).next; // Перепривязка следующего узла
        (*newNode).previous = (*(*curNode).next).previous;
        (*(*curNode).next).previous = newNode;
        (*curNode).next = newNode;
    }
    else
    {
        (*newNode).next = NULL; // Присвоение нового конца списка
        (*newNode).previous = curNode;
        endNode = newNode;
        (*curNode).next = newNode;
    }
}

// Вставка узла перед заданным индексом
void insertBefore(Node *&startNode, Node *&endNode, int fIndex, int fElement)
{
    Node *curNode = (*startNode).next;   // Поиск начального узла
    Node *newNode = new (Node);          // Создание нового узла
    for (int i = 0; i < fIndex - 1; i++) // Поиск нужного индекса
    {
        if ((*curNode).next == NULL) // Проверка на конец списка
        {
            break;
        }
        curNode = (*curNode).next; // Переход к следующему узлу
    }
    (*newNode).element = fElement;                 // Присвоение значения новому узлу
    (*newNode).next = (*(*curNode).previous).next; // Перепривязка узлов
    (*newNode).previous = (*curNode).previous;
    (*(*curNode).previous).next = newNode;
    (*curNode).previous = newNode;
}

// Удаление узла по индексу
void deleteNode(Node *&startNode, Node *&endNode, int fIndex)
{

    Node *curNode = (*startNode).next;
    for (int i = 0; i < fIndex - 1; i++)
    {
        if ((*curNode).next == NULL)
        {
            break;
        }
        curNode = (*curNode).next;
    }
    if ((*curNode).next != NULL)
    {
        (*(*curNode).next).previous = (*curNode).previous;
        (*(*curNode).previous).next = (*curNode).next;
        delete curNode;
    }
    else
    {
        (*(*curNode).previous).next = NULL;
        endNode = (*endNode).previous;
        delete curNode;
    }
}

Node *searchForward(Node *startNode, int fElement)
{
    Node *curNode = (*startNode).next;
    Node *foundNode = NULL;
    while ((curNode != NULL) && (foundNode == NULL))
    {
        std::cout << (*curNode).element << "  ";
        if ((*curNode).element == fElement)
        {
            std::cout << "\nElement found";
            foundNode = curNode;
        }
        else
        {
            curNode = (*curNode).next;
        }
    }
    if (foundNode == NULL)
    {
        std::cout << "\nElement not found";
    }
    std::cout << std::endl;
    return foundNode;
}
Node *searchBackward(Node *endNode, int fElement)
{
    Node *curNode = endNode;
    Node *foundNode = NULL;
    while (((*curNode).previous != NULL) && (foundNode == NULL))
    {
        std::cout << (*curNode).element << "  ";
        if ((*curNode).element == fElement)
        {
            std::cout << "\nElement found";
            foundNode = curNode;
        }
        else
        {
            curNode = (*curNode).previous;
        }
    }
    if (foundNode == NULL)
    {
        std::cout << "\nElement not found";
    }
    std::cout << std::endl;
    return foundNode;
}

void deletingList(Node *&startNode, Node *&endNode)
{
    Node *curNode = startNode;
    Node *nextNode = (*curNode).next;
    while ((*curNode).next != NULL)
    {
        delete curNode;
        curNode = nextNode;
        nextNode = (*curNode).next;
    }
    delete curNode;
    startNode = endNode = NULL;
}
