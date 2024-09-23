#include <cstddef>
#include <iostream>

// Это структура узла, здесь я храню данные и указатель на следующий узел.
struct Node
{
    int elem;   // Здесь храню сам элемент (значение).
    Node *next; // Указатель на следующий узел в очереди.
};

// Структура очереди, здесь у меня два указателя — на начало и конец очереди.
struct Queue
{
    Node *start; // Указатель на первый узел очереди.
    Node *end;   // Указатель на последний узел очереди.
};

// Объявляю функции для работы с очередью
void buildingQueue(Node *&fStart, Node *&fEnd); // Эта функция строит очередь
void addNode(Node *&fEnd, int fElement);        // Добавляю узел в конец очереди
int deleteNode(Node *&fStart);                  // Удаляю узел из начала очереди

void printQueue(Node *fStart);                  // Печатаю всю очередь
int findNode(Node *fStart, int fElement);       // Ищу узел с нужным элементом
int countOfNodes(Node *fStart);                 // Считаю количество узлов в очереди
void deletingQueue(Node *&fStart, Node *&fEnd); // Удаляю всю очередь

int main()
{
    Queue queue; // Создаю очередь
    int element;
    buildingQueue(queue.start, queue.end); // Строю очередь через пользовательский ввод
    printQueue(queue.start); // Печатаю очередь, чтобы убедиться, что она правильно построена

    std::cout << "Enter the element which you want to add: ";
    std::cin >> element;
    addNode(queue.end, element); // Добавляю новый элемент в конец
    printQueue(queue.start);     // Печатаю очередь после добавления

    std::cout << "Deleting 1st node " << std::endl;
    element = deleteNode(queue.start); // Удаляю первый узел
    printQueue(queue.start);           // Печатаю очередь после удаления

    std::cout << "Which element you want to find: ";
    std::cin >> element;
    int index = findNode(queue.start, element); // Ищу элемент, который ввел пользователь
    std::cout << "Index of found element (0 = not found): " << index << std::endl;

    std::cout << "Count of nodes in queue: " << countOfNodes(queue.start)
              << std::endl; // Показываю количество узлов в очереди

    std::cout << "Deleting queue" << std::endl;
    deletingQueue(queue.start, queue.end); // Полностью очищаю очередь
    printQueue(queue.start); // Печатаю пустую очередь для подтверждения

    return 0;
}

// Строю очередь через пользовательский ввод
void buildingQueue(Node *&fStart, Node *&fEnd)
{
    Node *fQueue = new (Node); // Создаю новый узел для начала очереди
    int element = 0;
    std::cout << "Enter the element of queue (0 = end):" << '\n' << "> ";
    std::cin >> element;
    (*fQueue).elem = element; // Сохраняю первый элемент
    (*fQueue).next = NULL;    // Пока других узлов нет, следующий — NULL
    fStart = fQueue;          // Начало очереди — это мой первый узел
    fEnd = fQueue;            // Конец очереди пока тоже этот узел
    std::cout << "> ";
    std::cin >> element;
    while (element != 0) // Продолжаю строить очередь, пока не введут 0
    {
        addNode(fEnd, element); // Добавляю новый элемент в конец
        std::cout << "> ";
        std::cin >> element;
    }
}

// Добавляю новый узел в конец очереди
void addNode(Node *&fEnd, int fElement)
{
    Node *fQueue = new (Node); // Создаю новый узел
    (*fQueue).elem = fElement; // Присваиваю ему значение
    (*fQueue).next = NULL;     // Этот узел последний, поэтому следующий — NULL
    (*fEnd).next = fQueue;     // Связываю текущий конец очереди с новым узлом
    fEnd = fQueue;             // Обновляю указатель на конец очереди
}

// Удаляю первый узел очереди
int deleteNode(Node *&fStart)
{
    Node *fQueue; // Временный указатель для удаляемого узла
    int klad = 0;
    klad = (*fStart).elem;   // Сохраняю значение удаляемого элемента
    fQueue = fStart;         // Запоминаю первый узел
    fStart = (*fStart).next; // Передвигаю указатель на следующий узел
    delete fQueue;           // Удаляю первый узел
    return klad;             // Возвращаю удаленное значение
}

// Печатаю очередь
void printQueue(Node *fStart)
{
    if (fStart == NULL) // Если очередь пуста, показываю сообщение
    {
        std::cout << "Queue is empty" << std::endl;
    }
    else
    {
        Node *curNode = fStart; // Начинаю с первого узла
        std::cout << "Queue: ";
        while (curNode != NULL) // Прохожу по всей очереди
        {
            std::cout << (*curNode).elem << '\t'; // Вывожу значение текущего узла
            curNode = (*curNode).next;            // Перехожу к следующему узлу
        }
        std::cout << std::endl;
    }
}

// Ищу элемент в очереди
int findNode(Node *fStart, int fElement)
{
    int index = 0;         // Счетчик для нахождения индекса элемента
    Node *fQueue = fStart; // Временный указатель для прохода по очереди
    while (fQueue != NULL) // Пока не дойду до конца очереди
    {
        if ((*fQueue).elem != fElement) // Если элемент не тот, продолжаю искать
        {
            index++;
            fQueue = (*fQueue).next; // Переход к следующему узлу
        }
        else if ((*fQueue).elem == fElement) // Если элемент нашелся, возвращаю индекс
        {
            index++;
            return index;
        }
    }
    return 0; // Если элемент не найден, возвращаю 0
}

// Подсчитываю количество узлов в очереди
int countOfNodes(Node *fStart)
{
    int count = 0;         // Счетчик узлов
    Node *fQueue = fStart; // Временный указатель для прохода по очереди
    while (fQueue != NULL) // Прохожу по всем узлам
    {
        count++;                 // Увеличиваю счетчик на каждый узел
        fQueue = (*fQueue).next; // Перехожу к следующему узлу
    }
    return count; // Возвращаю общее количество узлов
}

// Удаляю всю очередь
void deletingQueue(Node *&fStart, Node *&fEnd)
{
    Node *fQueue;
    fQueue = fStart;    // Начинаю с первого узла
    if (fStart != NULL) // Проверяю, есть ли вообще элементы в очереди
    {
        while (fStart != fEnd) // Удаляю все узлы, кроме последнего
        {
            fStart = (*fQueue).next; // Перемещаю указатель на следующий узел
            delete fQueue;           // Удаляю текущий узел
            fQueue = fStart;         // Переход к следующему узлу
        }
        delete fStart;        // Удаляю последний узел
        fStart = fEnd = NULL; // Обнуляю указатели на начало и конец очереди
    }
}
