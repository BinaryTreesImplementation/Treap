#include <iostream>
#include <utility>


class Counter
{
protected:
	size_t& Count() { static size_t counter = 0; return counter; }
public:
	Counter() { ++Count(); }
	~Counter() { --Count(); }
};

template<typename T>
class Treap
{
private:
	class Node: public Counter
	{
	public:
		Node *left, *right;
		T key;
		int priority;

		Node(const T& _key, const int& _priority, Node *_left = nullptr, Node *_right = nullptr) : key(_key), left(_left), right(_right), priority(_priority) {}
		size_t getCounter()
		{
			return Count();
		}
		
	} *root;
	

public:
	typedef std::pair<Node *, Node *> NodePair;

	Treap() : root(nullptr) {}
	
	void deleteNode(Node* temp)
	{
		if (temp != nullptr)
		{
			deleteNode(temp->left);
			deleteNode(temp->right);
			delete temp;
		}
		if (root->getCounter() == 0)
			root = nullptr;
	}

	~Treap()
	{
		deleteNode(root);
	}
		
	NodePair Split(const T& value, Node *localRoot)
	{
		if (!localRoot)
		{
			return NodePair(nullptr, nullptr);
		}

		else if (value > localRoot->key)
		{
			NodePair splited = Split(value, localRoot->right);
			localRoot->right = splited.first;
			return NodePair(localRoot, splited.second);
		}
		else
		{
			NodePair splited = Split(value, localRoot->left);
			localRoot->left = splited.second;
			return NodePair(splited.first, localRoot);
		}
	}

	void Display(const Node* temp, unsigned int level)const
	{
		if (temp)
		{
			Display(temp->left, level + 1);
			for (int i = 0; i < level; i++)
				std::cout << "__";
			std::cout << temp->key << "\t" << temp <<"\n";
			Display(temp->right, level + 1);
		}
	}


	Node *Merge(Node *Left, Node *Right)
	{
		if (!Right)
			return Left;
		if (!Left)
			return Right;
		if (Left->priority > Right->priority)
		{
			Left->right = Merge(Left->right, Right);
			return Left;
		}
		else
		{
			Right->left = Merge(Left, Right->left);
			return Right;
		}
	}

	void Insert(const T& value)
	{
		NodePair splited = Split(value, root);
		Node *inserting = new Node(value, rand()%100);
		splited.first = Merge(splited.first, inserting);
		root = Merge(splited.first, splited.second);
	}

	
	Node *Search(const T& value)const
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

	void Remove(const T& value)
	{
		if (Search(value) != nullptr)
		{
			NodePair splited = Split(value, root);
			Node *removing = splited.second;
			Node *preRemoving = nullptr;
			while (removing->left != nullptr)
			{
				preRemoving = removing;
				removing = removing->left;
			}

			if (removing == root)
				splited.second = removing->right;
			Node * nextRemoving = removing->right;
			delete removing;

			if (preRemoving != nullptr)
				preRemoving->left = nextRemoving;
			root = Merge(splited.first, splited.second);
		}
	}

	int* getPriority(const T&  value)const
	{
		Node *searchedNode = Search(value);
		if (searchedNode)
			return new int(searchedNode->priority);
		return nullptr;
	}

	Node *getRoot()
	{
		return root;
	}

	T* getKey(const T& value)const
	{
		Node *node = Search(value);
		if (node != nullptr)
			return new T(node->key);
		else
			return nullptr;
	}

	T* getRightKey(const T& key)
	{
		Node *node = Search(key);
		if (node != nullptr && node->right != nullptr)
			return new T(node->right->key);
		else
			return nullptr;
	}

	T* getKeyRoot()
	{
		if (root)
			return new T(root->key);
		else
			return nullptr;
	}
	
	T* getLeftKey(const T& key)
	{
		Node *node = Search(key);
		if (node != nullptr && node->left != nullptr)
			return new T(node->left->key);
		else
			return nullptr;
	}

	size_t getCount()
	{
		return root->getCounter();
	}
};
