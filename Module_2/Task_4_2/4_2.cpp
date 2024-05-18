/*«адача 4.2. ѕор€дковые статистики

ƒано число N и N строк.  ажда€ строка содержит команду добавлени€ или удалени€ натуральных чисел, 
а также запрос на получение k-ой пор€дковой статистики. 
 оманда добавлени€ числа A задаетс€ положительным числом A, 
команда удалени€ числа A задаетс€ отрицательным числом У-AФ. 
«апрос на получение k-ой пор€дковой статистики задаетс€ числом k.
“ребовани€: скорость выполнени€ запроса - O(log n).

*/

#include <iostream>
#include <stack>
#include <queue>
#include <cassert>
#include <fstream>

template <typename T>
struct Node
{
public:
	Node(const T& data) :
		data(data),
		left(nullptr),
		right(nullptr),
		height(1),
		count(1){}
	T data;
	Node* left;
	Node* right;
	size_t height;
	size_t count;
};

template <typename T>
class NodeComparator
{
public:
	NodeComparator()
	{
	}
	bool operator()(const Node<T>* node, const T& data, bool operation)
	{
		return operation ? data < node->data : data > node->data;
	}
};

template <typename T, typename Comparator = NodeComparator<T>>
class AVLTree
{
public:
	AVLTree() :
		root(nullptr) {}
	~AVLTree()
	{
		DestroyTree(root);
	}

	void Add(const T& data)
	{
		root = AddInternal(root, data);
	}

	bool Has(const T& data)
	{
		Node<T>* tmp = root;
		while (tmp)
		{
			if (tmp->data == data)
			{
				return true;
			}
			else if (tmp->data < data)
			{
				tmp = tmp->right;
			}
			else
			{
				tmp = tmp->left;
			}
		}
		return true;
	}

	void Delete(const T& data)
	{
		root = DeleteInternal(root, data);
	}

	T KthStat(int k)
	{

		Node<T>* node = root;
		size_t cur_stat = GetCount(root->left); //k-€ статистика текущей ноды

		while (cur_stat != k)
		{
			if (k > cur_stat) 
			{
				node = node->right;
				cur_stat += 1 + GetCount(node->left);
			}
			else 
			{
				node = node->left;
				cur_stat -= 1 + GetCount(node->right);
			}
		}

		return node->data;
	}

	void Print()
	{
		if (root == nullptr) {
			return;
		}
		std::queue<Node<T>*> queue;
		queue.push(root);
		Node<T>* tmp = root;
		while (!queue.empty())
		{
			Node<T>* node = queue.front();
			queue.pop();
			if (node)
			{
				std::cout << node->data << "|" << node->count << " ";
				if (tmp->right == node || node == root)
				{
					tmp = node;
					std::cout << "\n";
				}
				queue.push(node->left);
				queue.push(node->right);
			}
		}
	}

private:
	Node<T>* root;
	Comparator cmp = Comparator();

	void DestroyTree(Node<T>* node)
	{
		if (node)
		{
			DestroyTree(node->left);
			DestroyTree(node->right);
			delete node;
		}
	}

	Node<T>* AddInternal(Node<T>* node, const T& data)
	{
		if (!node)
			return new Node<T>(data);
		if (cmp(node, data, 1))
		{
			node->left = AddInternal(node->left, data);
			FixCount(node);
		}
		else
		{
			node->right = AddInternal(node->right, data);
			FixCount(node);
		}
		return DoBalance(node);
	}

	Node<T>* DeleteInternal(Node<T>* node, const T& data)
	{
		if (!node)
		{
			return nullptr;
		}
		if (cmp(node, data, 1)) // 1 - data < node->data
		{
			node->left = DeleteInternal(node->left, data);
		}
		else if (cmp(node, data, 0)) // 0 - data > node->data
		{
			node->right = DeleteInternal(node->right, data);
		}
		else
		{
 			Node<T>* left = node->left;
			Node<T>* right = node->right; 
			
			if (!right && !left) //≈сли удал€ема€ нода - лист
			{
				return nullptr;
			}
			

			Node<T>* new_node = FindAndRemove(left, right);	
			return DoBalance(new_node);
		}
		return DoBalance(node);
	}
	Node<T>* FindAndRemove(Node<T>* left, Node<T>* right)
	{
		std::stack<Node<T>*> stack;
		if (GetHeight(left) >= GetHeight(right)) //√лубина левого поддерева больше глубины правого
		{
			Node<T>* find_node = left;
			stack.push(find_node); // ладЄм в стек все встречающиесе по пути к замещающей ноде, чтобы можно было провести балансировку дл€ них 
			while (find_node->right)
			{
				find_node = find_node->right;
				stack.push(find_node);
			}
			stack.pop(); //ѕоследний элемент в стеке - нода, которую ставим на место удал€емой
			Node<T>* tmp = nullptr;

			find_node->right = right;

			if (stack.size() > 0) //≈сли в стеке нет элементов, то нода left - замещающа€ нода 
			{
				tmp = stack.top();
				stack.pop();
				tmp->right = find_node->left;

				while (stack.size() > 0)
				{
					stack.top()->right = DoBalance(tmp);
					tmp = stack.top();
					stack.pop();
				}
				tmp = DoBalance(tmp);
			}
			else
			{
				find_node->right = right;
				return find_node;
			}
			find_node->left = tmp;
			return find_node;
		}
		else //√лубина правого поддерева больше глубины левого
		{
			{
				Node<T>* find_node = right;
				stack.push(find_node); // ладЄм в стек все встречающиесе ноды по пути к замещающей, чтобы можно было провести балансировку дл€ них 
				while (find_node->left)
				{
					find_node = find_node->left;
					stack.push(find_node);
				}
				stack.pop(); //ѕоследний элемент в стеке - нода, которую ставим на место удал€емой
				Node<T>* tmp = nullptr;

				find_node->left = left;

				if (stack.size() > 0) //≈сли в стеке нет элементов, то нода left - замещающа€ нода 
				{
					tmp = stack.top();
					stack.pop();
					tmp->left = find_node->right;

					while (stack.size() > 0)
					{
						stack.top()->left = DoBalance(tmp);
						tmp = stack.top();
						stack.pop();
					}
					tmp = DoBalance(tmp);
				}
				else
				{
					find_node->left = left;
					return find_node;
				}
				find_node->right = tmp;
				return find_node;
			}
		}
	}

	Node<T>* FindMin(Node<T>* node)
	{
		while (node->left)
			node = node->left;
		return node; 
	}

	Node<T>* RemoveMin(Node<T>* node)
	{
		if (!node->left)
			return node->right;
		node->left = RemoveMin(node->left);
		return DoBalance(node);
	}

	void FixCount(Node<T>* node)
	{
		size_t left_count = GetCount(node->left);
		size_t right_count = GetCount(node->right);
		node->count = left_count + right_count + 1;
	}

	size_t GetCount(Node<T>* node)
	{
		return node ? node->count : 0;
	}

	void FixHeight(Node<T>* node)
	{
		node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
	}

	size_t GetHeight(Node<T>* node)
	{
		return node ? node->height : 0;
	}

	int GetBalance(Node<T>* node)
	{
		return GetHeight(node->left) - GetHeight(node->right);
	}

	Node<T>* RotateLeft(Node<T>* node)
	{
		Node<T>* tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;
		FixHeight(node);
		FixHeight(tmp);
		FixCount(node);
		FixCount(tmp);
		return tmp;
	}

	Node<T>* RotateRight(Node<T>* node)
	{
		Node<T>* tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;
		FixHeight(node);
		FixHeight(tmp);
		FixCount(node);
		FixCount(tmp);
		return tmp;
	}

	Node<T>* DoBalance(Node<T>* node)
	{
		FixHeight(node);
		FixCount(node);
		switch (GetBalance(node))
		{
			case 2:
			{
				if (GetBalance(node->left) < 0)
				{
					node->left = RotateLeft(node->left);
				}
				return RotateRight(node);
			}
			case -2:
			{
				if (GetBalance(node->right) > 0)
				{
					node->right = RotateRight(node->right);
				}
				return RotateLeft(node);
			}
			default:
				return node;
		}
	}
};

void Test0_1()
{
	AVLTree<int> tree;
	int commands[3] = { 1, 2, -1 };
	int k[3] = {0, 0, 0};
	int answers[3] = { 1, 1, 2 };
	for (int i = 0; i < 3; ++i)
	{
		if (commands[i] > 0)
		{
			tree.Add(commands[i]);
		}
		else
		{
			tree.Delete(-1 * commands[i]);
		}
		assert(answers[i] == tree.KthStat(k[i]));
	}
}

void Test0_2()
{
	AVLTree<int> tree;
	int commands[5] = { 40, 10, 4, -10, 50 };
	int k[5] = { 0, 1, 1, 0, 2 };
	int answers[5] = { 40, 40, 10, 4, 50};
	for (int i = 0; i < 5; ++i)
	{
		if (commands[i] > 0)
		{
			tree.Add(commands[i]);
		}
		else
		{
			tree.Delete(-1 * commands[i]);
		}
		assert(answers[i] == tree.KthStat(k[i]));
	}
}

void Test1()
{
	AVLTree<int> tree;
	int commands[13] = { 9, 10, 4, 3, 2, 7, 8, 5, 1, 6, -5, -7, -4 };
	int k[13] = { 0, 1, 2, 1, 0, 5, 6, 6, 3, 1, 0, 5, 6 };
	int answers[13] = { 9, 10, 10, 4, 2, 10, 10, 9, 4, 2, 1, 8, 10 };
	for (int i = 0; i < 13; ++i)
	{
		if (commands[i] > 0)
		{
			tree.Add(commands[i]);
		}
		else
		{
			tree.Delete(-1 * commands[i]);
		}
		assert(answers[i] == tree.KthStat(k[i]));
	}
}

void Test2()
{
	AVLTree<int> tree;
	int commands[16] = { 9, 10, 4, -9, 3, 3, -10, 10, -3, 5, 5, 7, 8, 1, -7, 9 };
	int k[16] = { 0, 0, 1, 1, 1, 2, 1, 2, 0, 3, 3, 1, 6, 0, 6, 7 };
	int answers[16] = { 9, 9, 9, 10, 4, 4, 3, 4, 3, 10, 5, 4, 10, 1, 10, 10 };
	for (int i = 0; i < 16; ++i)
	{
		if (commands[i] > 0)
		{
			tree.Add(commands[i]);
		}
		else
		{
			tree.Delete(-1 * commands[i]);
		}
		assert(answers[i] == tree.KthStat(k[i]));
	}
}

void Test3()
{
	AVLTree<int> tree;
	int commands[6] = { 2, 3, 1, -3, -1, 4 };
	int k[6] = { 0, 1, 1, 0, 0, 1 };
	int answers[6] = { 2, 3, 2, 1, 2, 4 };
	for (int i = 0; i < 6; ++i)
	{
		if (commands[i] > 0)
		{
			tree.Add(commands[i]);
		}
		else
		{
			tree.Delete(-1 * commands[i]);
		}
		assert(answers[i] == tree.KthStat(k[i]));
	}
}

int main()
{
	Test0_1();
	Test0_2();
	Test1();
	Test2();
	Test3();
	int n = 0;
	std::cin >> n;
	AVLTree<int> tree;
	//std::ofstream output_file("output.txt");
	for (int i = 0; i < n; ++i)
	{
		int element = 0;
		size_t k = 0;
		std::cin >> element >> k;
		if (element > 0)
		{
			tree.Add(element);
			
		}
		else
		{
			tree.Delete(-1 * element);
		}
		std::cout << tree.KthStat(k) << "\n";
	}	
	//output_file.close();
}