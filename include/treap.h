#include <iostream>
#include <utility>

template<typename T>
class Treap
{
private:
	class Node
	{
	public:
		Node *left, *right;
		T key;
		int priority;

		Node(const T& _key, const int& _priority, Node *_left = nullptr, Node *_right = nullptr) : key(_key), left(_left), right(_right), priority(_priority) {}


	} *root;
public:
	Treap() : root(nullptr) {}

	Node *getRoot()const
	{
		return root;
	}

	T getKey(Node *_node)const
	{
		return _node->key;
	}
	int getPriority(Node *_node)const
	{
		return _node->priority;
	}

	typedef std::pair<Node *, Node *> NodePair;

	NodePair split(const T& value, Node *localRoot)
	{
		if (!localRoot)
		{
			return NodePair(nullptr, nullptr);
		}

		else if (value > localRoot->key)
		{
			NodePair splited = split(value, localRoot->right);
			localRoot->right = splited.first;
			return NodePair(localRoot, splited.second);
		}
		else
		{
			NodePair splited = split(value, localRoot->left);
			localRoot->left = splited.second;
			return NodePair(splited.first, localRoot);
		}
	}

	void display(const Node* temp, unsigned int level)const
	{
		if (temp)
		{
			display(temp->left, level + 1);
			for (int i = 0; i < level; i++)
				std::cout << "__";
			std::cout << temp->key << "\t" << temp <<"\n";
			display(temp->right, level + 1);
		}
	}


	Node *merge(Node *Left, Node *Right)
	{
		if (!Right)
		{
			return Left;
		}

		if (!Left)
		{
			return Right;
		}

		if (Left->priority > Right->priority)
		{
			Left->right = merge(Left->right, Right);
			return Left;
		}

		else
		{
			Right->left = merge(Left, Right->left);
			return Right;
		}
	}

	void insert(const T& value)
	{
		NodePair splited = split(value, root);
		Node *inserting = new Node(value, rand()%100);
		splited.first = merge(splited.first, inserting);
		root = merge(splited.first, splited.second);

	}

	Node *search(const T& value)
	{
		Node *searchedElement = root;

		while (searchedElement != nullptr)
		{
			if (searchedElement->key < value)
				searchedElement = searchedElement->right;
			else if (value < searchedElement->key)
				searchedElement = searchedElement->left;
			else if (searchedElement->key == value)
			{
				return searchedElement;
			}
		}

		return nullptr;
	}

	void remove(const T& value)
	{

		Node *removing = search(value);
		
		
		std::cout << "=======\n";
		std::cout << merge(removing->left, removing->right)->key;
		std::cout << "=======\n";
		std::cout << removing;
		std::cout << "=======\n";
		removing = merge(removing->left, removing->right);
		std::cout << "=======\n";
		std::cout << removing->key;
		std::cout << "=======\n";
		std::cout << removing;
		std::cout << "=======\n";
		
		
	}
};