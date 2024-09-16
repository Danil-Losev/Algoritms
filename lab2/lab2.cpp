
#include <iostream>

// Структура узла, которая хранит значение и указатель на следующий элемент
struct Node
{
    int value;  // Значение узла
    Node *next; // Указатель на следующий узел
};

// Прототипы функций для работы с односвязным списком
void posroenie(Node *&fPHead);                           // Функция построения списка
void vstavka(Node *&fPHead, int preIndex, int fElement); // Вставка нового элемента в список
void udalenie(Node *&fPHead, int preIndex);              // Удаление элемента из списка

void printList(Node *fPHead);                          // Печать списка
int findNode(Node *fPHead, int fEllement);             // Поиск элемента в списке
int countOfNodes(Node *fPHead);                        // Подсчёт количества узлов в списке
void makeARingList(Node *&fPHead);                     // Создание кольцевого списка
void printRingList(Node *fPHead, int countOfRing = 1); // Печать кольцевого списка

int main()
{
    // Объявляю указатели на начало списка и кольцевого списка
    Node *HeadOfOneConnectedList;     // Указатель на односвязный список
    Node *HeadOfOneConnectedRingList; // Указатель на кольцевой список

    int index = 0;                 // Индекс для вставки или удаления элемента
    int element = 0;               // Элемент, который буду вставлять
    int findEllement = 0;          // Элемент для поиска
    int countOfFoundEllements = 0; // Количество найденных элементов

    // Построение односвязного списка
    posroenie(HeadOfOneConnectedList);
    printList(HeadOfOneConnectedList); // Печать списка

    // Вставка нового элемента после определённого индекса
    std::cout << "Enter the index of the element after which you want to insert a new element: ";
    std::cin >> index;
    std::cout << "Enter the element you want to insert: ";
    std::cin >> element;
    vstavka(HeadOfOneConnectedList, index, element); // Вставка элемента
    printList(HeadOfOneConnectedList);               // Печать списка

    // Удаление элемента после определённого индекса
    std::cout << "Enter the index of the element after which you want to delete element: ";
    std::cin >> index;
    udalenie(HeadOfOneConnectedList, index);                    // Удаление элемента
    printList(HeadOfOneConnectedList);                          // Печать списка после удаления
    int countOfElements = countOfNodes(HeadOfOneConnectedList); // Подсчёт узлов

    // Вывод количества узлов в списке
    std::cout << "Count of nodes in the array: " << countOfElements << std::endl;

    // Поиск элемента в списке
    std::cout << "Which number do you want to find: ";
    std::cin >> findEllement;
    countOfFoundEllements = findNode(HeadOfOneConnectedList, findEllement); // Поиск элемента
    std::cout << "Count of found ellements: " << countOfFoundEllements << std::endl;

    std::cout << std::endl;

    // Построение кольцевого списка
    makeARingList(HeadOfOneConnectedRingList);
    printRingList(HeadOfOneConnectedRingList, 3); // Печать кольцевого списка
    return 0;
}

// Функция построения односвязного списка
void posroenie(Node *&fPHead)
{
    std::cout << "**Building a one connected linked list**" << std::endl;
    fPHead = new (Node);    // Создаю первый узел
    Node *curNode = fPHead; // Текущий узел для итерации
    (*curNode).next = NULL; // Инициализация указателя на следующий узел
    int ellement;           // Переменная для ввода значения узла
    std::cout << "Enter the values of the information fields of the list links (0 = end):" << '\n' << "> ";
    std::cin >> ellement;

    // Цикл для ввода элементов списка до тех пор, пока не введу 0
    while (ellement != 0)
    {
        (*curNode).next = new (Node); // Создаю новый узел
        curNode = (*curNode).next;    // Перехожу на следующий узел
        (*curNode).value = ellement;  // Записываю значение узла
        (*curNode).next = NULL;       // Указатель на следующий узел равен NULL
        std::cout << "> ";
        std::cin >> ellement; // Ввожу следующий элемент
    }
}

// Функция вставки нового узла после заданного индекса
void vstavka(Node *&fPHead, int preIndex, int fElement)
{
    std::cout << "**Insert element after pre index element**" << std::endl;
    Node *curNode = fPHead; // Начинаю с первого узла
    // Прохожу по списку до узла с нужным индексом
    for (int i = 0; i < preIndex; i++)
    {
        curNode = (*curNode).next;
    }
    Node *newNode = new (Node);        // Создаю новый узел
    (*newNode).value = fElement;       // Заполняю его значение
    (*newNode).next = (*curNode).next; // Устанавливаю связь со следующим узлом
    (*curNode).next = newNode;         // Привязываю новый узел к текущему
}

// Функция удаления узла из списка
void udalenie(Node *&fPHead, int preIndex)
{
    std::cout << "**Delete element:**" << std::endl;
    Node *curNode = fPHead; // Начинаю с первого узла
    // Прохожу по списку до узла перед нужным для удаления
    for (int i = 0; i < preIndex; i++)
    {
        curNode = (*curNode).next;
    }
    // Проверяю, есть ли узел для удаления
    if ((*curNode).next != NULL)
    {
        Node *temp = (*curNode).next; // Временная переменная для хранения узла
        (*curNode).next = (*(*curNode).next).next; // Пропускаю удаляемый узел
        delete temp;                               // Удаляю узел
    }
    else
    {
        std::cout << "You can't delete a non-existent node" << std::endl; // Ошибка, если узла нет
    }
}

// Функция печати списка
void printList(Node *fPHead)
{
    Node *curNode = fPHead; // Начинаем с первого узла
    std::cout << "List: ";
    while ((*curNode).next != NULL) // Проходим по узлам, пока не дойдём до конца
    {
        curNode = (*curNode).next;
        std::cout << '\t' << (*curNode).value; // Выводим значение узла
    }
    std::cout << std::endl;
}

// Функция поиска количества элементов в списке
int findNode(Node *fPHead, int fEllement)
{
    Node *curNode = fPHead; // Начинаем с первого узла
    int counfOfEl = 0;      // Счётчик найденных элементов
    while ((*curNode).next != NULL)
    {
        curNode = (*curNode).next;
        if ((*curNode).value == fEllement) // Сравниваем значение узла с искомым
        {
            counfOfEl++; // Увеличиваем счётчик, если элемент найден
        }
    }
    return counfOfEl; // Возвращаем количество найденных элементов
}

// Функция подсчёта узлов в списке
int countOfNodes(Node *fPHead)
{
    Node *curNode = fPHead; // Начинаем с первого узла
    int count = 0;          // Счётчик узлов
    while ((*curNode).next != NULL)
    {
        curNode = (*curNode).next;
        count++; // Увеличиваем счётчик для каждого узла
    }
    return count; // Возвращаем количество узлов
}

// Функция создания кольцевого списка
void makeARingList(Node *&fPHead)
{
    std::cout << "**Building a one connected linked ring list**" << std::endl;
    fPHead = new (Node);    // Создаём первый узел
    Node *curNode = fPHead; // Текущий узел
    (*curNode).next = NULL;
    int ellement;
    std::cout << "Enter the values of the information fields of the list links (0 = end):" << '\n' << "> ";
    std::cin >> ellement;
    while (ellement != 0)
    {
        (*curNode).next = new (Node); // Создаём новый узел
        curNode = (*curNode).next;
        (*curNode).value = ellement;
        (*curNode).next = (*fPHead).next; // Ссылка на следующий узел кольцевого списка
        std::cout << "> ";
        std::cin >> ellement;
    }
}

// Функция печати кольцевого списка
void printRingList(Node *fPHead, int countOfRing)
{
    Node *curNode = fPHead; // Начинаем с первого узла
    std::cout << "Ring List:" << std::endl;
    for (int i = 0; i < countOfRing; i++)
    {
        do
        {
            curNode = (*curNode).next;
            std::cout << (*curNode).value << '\t'; // Выводим значения узлов
        } while ((*curNode).next != (*fPHead).next); // Цикл по узлам кольца
        std::cout << std::endl;
    }
}
