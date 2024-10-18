#include <cstddef>
#include <iostream>

// Объявление глобальной переменной, представляющей количество вершин в графе.
int COUNT_OF_NODES = 6;

// Структура для описания узла списка смежности графа.
struct Node
{
    int key;    // Ключ узла, который указывает на другую вершину.
    Node *next; // Указатель на следующий узел в списке смежности.
};

// Прототипы функций для работы с графом.
void makeGraph(Node **&fAdjacencyList, int fCountOfNodes); // Функция для создания графа.
void addArc(int fX, int fY, Node **&fAdjacencyList); // Функция для добавления дуги между вершинами.
void printGraph(Node **fAdjacencyList, int fCountOfNodes); // Функция для вывода графа на экран.
void deleteArc(int fX, int fY, Node **&fAdjacencyList); // Функция для удаления дуги между вершинами.
void deleteNode(Node *&fAdjacencyList, Node *&fNode); // Функция для удаления конкретного узла из списка.
Node *search(Node *fAdjacencyListX, int fElement); // Функция для поиска узла в списке по ключу.

// Главная функция программы, реализующая меню для управления графом.
int main()
{
    int x, y, choice; // Переменные для хранения выбора и ввода вершин.
    Node **adjacencyList =
        new Node *[COUNT_OF_NODES]; // Создание массива указателей на списки смежности для каждой вершины.

    // Инициализация списка смежности: все элементы массива инициализируются как NULL.
    for (int i = 0; i < COUNT_OF_NODES; i++)
    {
        adjacencyList[i] = NULL; // Каждый узел графа изначально пуст.
    }

    // Организация меню для пользователя.
    do
    {
        std::cout << "Menu:\n";
        std::cout << "1. Create graph\n";
        std::cout << "2. Add arc\n";
        std::cout << "3. Delete arc\n";
        std::cout << "4. Show graph\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose action: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            makeGraph(adjacencyList, COUNT_OF_NODES); // Создание графа.
            break;
        case 2:
            std::cout << "Enter start and end nodes to add an arc: "; // Ввод узлов для добавления дуги.
            std::cin >> x >> y;
            addArc(x, y, adjacencyList); // Добавление дуги.
            break;
        case 3:
            std::cout << "Enter start and end nodes to delete an arc: "; // Ввод узлов для удаления дуги.
            std::cin >> x >> y;
            deleteArc(x, y, adjacencyList); // Удаление дуги.
            break;
        case 4:
            printGraph(adjacencyList, COUNT_OF_NODES); // Вывод графа на экран.
            break;
        case 5:
            std::cout << "Exiting program.\n"; // Завершение программы.
            break;
        default:
            std::cout << "Invalid choice, try again.\n"; // Сообщение об ошибочном вводе.
        }
    } while (choice != 5); // Программа будет продолжать работать, пока не выбрана опция выхода.

    return 0;
}

// Реализация функции для создания графа.
void makeGraph(Node **&fAdjacencyList, int fCountOfNodes)
{
    int x, y;
    std::cout << "\" 0 = end \"\n"; // Подсказка для пользователя о завершении ввода.
    std::cout << "Enter the start of arc: ";
    std::cin >> x;
    while (x != 0) // Пока пользователь не введет 0, продолжается создание дуг.
    {
        std::cout << "Enter the end of arc: ";
        std::cin >> y;
        addArc(x, y, fAdjacencyList); // Добавление новой дуги между вершинами x и y.
        std::cout << "Enter the start of arc: ";
        std::cin >> x;
    }
}

// Добавление дуги в граф между вершинами fX и fY.
void addArc(int fX, int fY, Node **&fAdjacencyList)
{
    Node *currentPointer, *newNode;
    if (fAdjacencyList[fX] != NULL) // Проверка на наличие существующих дуг у вершины.
    {
        currentPointer = search(fAdjacencyList[fX], fY); // Поиск дуги между fX и fY.
        if (currentPointer == NULL) // Если дуга не найдена, создается новая.
        {
            newNode = new (Node);
            newNode->key = fY;    // Присвоение ключа новой вершины.
            newNode->next = NULL; // Новый узел будет последним в списке.
            currentPointer = fAdjacencyList[fX];
            while (currentPointer->next != NULL) // Перебор до конца списка смежности.
            {
                currentPointer = currentPointer->next;
            }
            currentPointer->next = newNode; // Добавление нового узла в конец списка.
        }
    }
    else // Если дуг у вершины нет, создается первая дуга.
    {
        fAdjacencyList[fX] = new (Node);
        fAdjacencyList[fX]->key = fY;    // Присваивается ключ новой дуги.
        fAdjacencyList[fX]->next = NULL; // Устанавливается конец списка.
    }
}

// Вывод графа на экран в виде списка смежности.
void printGraph(Node **fAdjacencyList, int fCountOfNodes)
{
    Node *curNode;
    std::cout << "\nAdjacency list representation of a graph\n"; // Заголовок для вывода списка смежности.
    for (int i = 1; i < fCountOfNodes; i++)                      // Перебор всех вершин графа.
    {
        std::cout << "  " << i << " ...";
        curNode = fAdjacencyList[i]; // Получение списка смежности для текущей вершины.
        if (curNode == NULL)         // Проверка на наличие дуг.
        {
            std::cout << "List is empty! \n"; // Если дуг нет, выводится сообщение о пустом списке.
        }
        else
        {
            while (curNode != NULL) // Перебор всех дуг текущей вершины.
            {
                std::cout << curNode->key << ' '; // Вывод ключа дуги.
                curNode = curNode->next;          // Переход к следующему узлу в списке.
            }
            std::cout << std::endl;
        }
    }
}

// Удаление дуги между вершинами fX и fY.
void deleteArc(int fX, int fY, Node **&fAdjacencyList)
{
    Node *curNode;
    if (fAdjacencyList[fX] != NULL) // Проверка на наличие дуг у вершины fX.
    {
        curNode = search(fAdjacencyList[fX], fY); // Поиск дуги для удаления.
        if (curNode != NULL)                      // Если дуга найдена, она удаляется.
        {
            deleteNode(fAdjacencyList[fX], curNode); // Удаление узла.
        }
        else
        {
            std::cout << "\nThere is no such arc in the graph\n"; // Сообщение об отсутствии дуги.
        }
    }
    else
    {
        std::cout << "\nList is empty\n"; // Если список смежности пуст, выводится соответствующее сообщение.
    }
}

// Удаление узла из списка смежности вершины.
void deleteNode(Node *&fAdjacencyList, Node *&fNode)
{
    Node *curNode, *temp;
    if ((fAdjacencyList->next == NULL) && (fNode = fAdjacencyList)) // Если удаляется единственная дуга.
    {
        fAdjacencyList = NULL; // Список становится пустым.
        delete fNode;          // Удаление узла.
    }
    else
    {
        if (fNode == fAdjacencyList) // Если удаляется первый узел в списке.
        {
            fAdjacencyList = fAdjacencyList->next; // Сдвиг указателя на следующий узел.
            delete fNode;                          // Удаление узла.
        }
        else
        {
            temp = fAdjacencyList; // Инициализация временного указателя.
            curNode = fAdjacencyList->next;
            while (curNode != fNode) // Поиск узла, который нужно удалить.
            {
                temp = curNode;
                curNode = curNode->next;
            }
            temp->next = fNode->next; // Сдвиг указателей для удаления узла.
            delete fNode;             // Удаление узла.
        }
    }
}

// Поиск узла в списке смежности.
Node *search(Node *fAdjacencyListX, int fElement)
{
    Node *curNode;
    Node *searchNode = NULL; // Инициализация указателя для хранения результата поиска.
    curNode = fAdjacencyListX;
    while ((curNode != NULL) && (searchNode == NULL)) // Перебор всех узлов в списке.
    {
        if (curNode->key == fElement) // Если найден узел с искомым ключом.
        {
            searchNode = curNode; // Сохранение найденного узла.
        }
        curNode = curNode->next; // Переход к следующему узлу.
    }
    return searchNode; // Возврат найденного узла или NULL, если узел не найден.
}
