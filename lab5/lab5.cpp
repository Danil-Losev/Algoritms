#include <cstddef>
#include <cstdlib>
#include <iostream>

// Узел дерева, который хранит ключ (Key), количество его добавлений (Count),
// а также указатели на левое (Left) и правое (Right) поддеревья.
struct Node
{
    int Key;     // Ключ узла
    int Count;   // Количество добавлений данного ключа
    Node *Left;  // Указатель на левое поддерево
    Node *Right; // Указатель на правое поддерево
};

// Класс для работы с бинарным деревом поиска.
class TREE
{
  private:
    Node *Tree; // Указатель на корень дерева
    // Функция для поиска места для нового элемента в дереве
    void Search(int, Node **);

  public:
    // Конструктор, инициализирующий дерево пустым
    TREE() : Tree(NULL)
    {
    }
    // Возвращает указатель на корень дерева
    Node **GetTree()
    {
        return &Tree;
    }
    // Построение дерева с элементами от пользователя
    void BuildTree();
    // Очистка дерева, удаление всех узлов
    void CleanTree(Node **);
    // Вывод дерева на экран
    void PrintTree(Node **, int = 0);
    // Прямой порядок обхода дерева (PreOrder)
    void PreOrder(Node **);
    // Симметричный порядок обхода дерева (InOrder)
    void InOrder(Node **);
    // Обратный порядок обхода дерева (PostOrder)
    void PostOrder(Node **);
    // Определение высоты дерева
    int Height(Node **);
};

int main()
{
    TREE myTree;    // Создание объекта дерева
    int choice = 0; // Переменная для хранения выбора пользователя

    do
    {
        // Отображение меню на экране для выбора действий
        std::cout << "\n=== Tree menu ===\n";
        std::cout << "1. Build a tree\n";         // Опция построения дерева
        std::cout << "2. Print the tree\n";       // Опция вывода дерева
        std::cout << "3. Pre-order traversal\n";  // Опция прямого обхода дерева
        std::cout << "4. In-order traversal\n";   // Опция симметричного обхода дерева
        std::cout << "5. Post-order traversal\n"; // Опция обратного обхода дерева
        std::cout << "6. Print the height of the tree\n"; // Опция вывода высоты дерева
        std::cout << "7. Clear the tree\n";               // Опция очистки дерева
        std::cout << "8. Exit\n";                         // Опция выхода из программы
        std::cout << "Choose an action: "; // Приглашение к вводу выбора действия
        std::cin >> choice;                // Ввод пользователем выбора

        switch (choice) // Обработка введённого пользователем выбора
        {
        case 1:
            myTree.BuildTree();           // Построение дерева
            std::cout << "Tree built.\n"; // Сообщение о завершении построения
            break;
        case 2:
            std::cout << "Tree output:\n";      // Вывод дерева на экран
            myTree.PrintTree(myTree.GetTree()); // Вызов функции для печати дерева
            break;
        case 3:
            std::cout << "Pre-order traversal: "; // Сообщение о начале прямого обхода
            myTree.PreOrder(myTree.GetTree());    // Вызов функции прямого обхода
            std::cout << "\n";                    // Переход на новую строку после вывода
            break;
        case 4:
            std::cout << "In-order traversal: "; // Сообщение о начале симметричного обхода
            myTree.InOrder(myTree.GetTree()); // Вызов функции симметричного обхода
            std::cout << "\n";                // Переход на новую строку после вывода
            break;
        case 5:
            std::cout << "Post-order traversal: "; // Сообщение о начале обратного обхода
            myTree.PostOrder(myTree.GetTree());    // Вызов функции обратного обхода
            std::cout << "\n"; // Переход на новую строку после вывода
            break;
        case 6:
            std::cout << "Tree height: " << myTree.Height(myTree.GetTree()) << "\n"; // Вывод высоты дерева
            break;
        case 7:
            myTree.CleanTree(myTree.GetTree()); // Очистка дерева
            std::cout << "Tree cleaned.\n";     // Сообщение об успешной очистке дерева
            break;
        case 8:
            std::cout << "Exiting program.\n"; // Сообщение о завершении работы программы
            break;
        default:
            std::cout << "Invalid choice, try again.\n"; // Сообщение о неверном выборе действия
        }
    } while (choice != 8); // Цикл продолжается до тех пор, пока пользователь не выберет выход

    return 0; // Завершение работы программы
}

// Функция для построения дерева на основе пользовательского ввода
void TREE::BuildTree()
{
    int element;
    std::cout << "Enter the keys of tree`s tops (0 = end): " << std::endl;
    std::cin >> element; // Ввод первого элемента
    while (element != 0) // Продолжаем, пока не введен 0
    {
        Search(element, &Tree); // Добавление элемента в дерево
        std::cin >> element;    // Ввод следующего элемента
    }
}

// Поиск места для нового элемента в дереве. Если элемент уже существует, увеличивается его счетчик.
void TREE::Search(int fElement, Node **fTree)
{
    if (*fTree == NULL)
    {
        *fTree = new (Node);      // Создание нового узла
        (**fTree).Key = fElement; // Присвоение ключа
        (**fTree).Count = 1;      // Установка начального значения счетчика
        (**fTree).Left = NULL;    // Левое поддерево пусто
        (**fTree).Right = NULL;   // Правое поддерево пусто
    }
    else
    {
        if (fElement < (**fTree).Key) // Если новый элемент меньше, идем влево
        {
            Search(fElement, &(**fTree).Left);
        }
        else if (fElement > (**fTree).Key) // Если больше, идем вправо
        {
            Search(fElement, &(**fTree).Right);
        }
        else
        {
            (**fTree).Count++; // Если элемент найден, увеличиваем его счетчик
        }
    }
}

// Вывод структуры дерева на экран с отступами для отображения уровней
void TREE::PrintTree(Node **fTree, int index)
{
    int i;
    if (*fTree != NULL) // Если узел существует
    {
        PrintTree(&(**fTree).Right, index + 1); // Вывод правого поддерева
        for (i = 1; i <= index; i++) // Добавление отступов для визуализации уровня
        {
            std::cout << "   ";
        }
        std::cout << (**fTree).Key << std::endl; // Вывод ключа узла
        PrintTree(&(**fTree).Left, index + 1);   // Вывод левого поддерева
    }
}

// Очистка дерева: рекурсивно удаляются все узлы дерева
void TREE::CleanTree(Node **fTree)
{
    if (*fTree != NULL) // Если узел существует
    {
        CleanTree(&(**fTree).Left);  // Очистка левого поддерева
        CleanTree(&(**fTree).Right); // Очистка правого поддерева
        delete *fTree;               // Удаление текущего узла
    }
}

// Прямой (PreOrder) обход дерева: корень, левое поддерево, правое поддерево
void TREE::PreOrder(Node **fTree)
{
    if (*fTree != NULL)
    {
        std::cout << (**fTree).Key << " "; // Вывод ключа узла
        PreOrder(&(**fTree).Left);         // Обход левого поддерева
        PreOrder(&(**fTree).Right);        // Обход правого поддерева
    }
}

// Симметричный (InOrder) обход дерева: левое поддерево, корень, правое поддерево
void TREE::InOrder(Node **fTree)
{
    if (*fTree != NULL)
    {
        InOrder(&(**fTree).Left);          // Обход левого поддерева
        std::cout << (**fTree).Key << " "; // Вывод ключа узла
        InOrder(&(**fTree).Right);         // Обход правого поддерева
    }
}

// Обратный (PostOrder) обход дерева: левое поддерево, правое поддерево, корень
void TREE::PostOrder(Node **fTree)
{
    if (*fTree != NULL)
    {
        PostOrder(&(**fTree).Left);        // Обход левого поддерева
        PostOrder(&(**fTree).Right);       // Обход правого поддерева
        std::cout << (**fTree).Key << " "; // Вывод ключа узла
    }
}

// Определение высоты дерева
int TREE::Height(Node **fTree)
{
    int heightRight, heightLeft;
    if (*fTree == NULL)
    {
        return -1; // Пустое дерево имеет высоту -1
    }
    else
    {
        heightLeft = Height(&(**fTree).Left);   // Высота левого поддерева
        heightRight = Height(&(**fTree).Right); // Высота правого поддерева
        if (heightLeft > heightRight)           // Возвращается максимальная высота
        {
            return (1 + heightLeft);
        }
        else
        {
            return (1 + heightRight);
        }
    }
}
