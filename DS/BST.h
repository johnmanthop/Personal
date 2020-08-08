#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <functional>
#include <iostream>
#include <tuple>
#include <vector>
#include <memory>

template<typename T>
class BinarySearchTree
{
protected:
	struct BinarySearchTreeNode
	{
	public:
		T value;
		BinarySearchTreeNode *left;
		BinarySearchTreeNode *right;
		int count;
		int depth;
	public:
		BinarySearchTreeNode(T _value): value(_value), left(nullptr), right(nullptr), count(1), depth(1) {}
	};
protected:
	BinarySearchTreeNode *root;
	int size;
	
	template<typename... Args>
	void inorder  (BinarySearchTreeNode *node, std::function<void(T value, Args...)> f, Args... args);
	template<typename... Args>
	void preorder (BinarySearchTreeNode *node, std::function<void(T value, Args...)> f, Args... args);
	template<typename... Args>
	void postorder(BinarySearchTreeNode *node, std::function<void(T value, Args...)> f, Args... args);
	
	
	void delete_tree(BinarySearchTree<T>::BinarySearchTreeNode *node);
	
	std::tuple<std::shared_ptr<std::vector<BinarySearchTree<T>::BinarySearchTreeNode**>>, bool>
		insert_hidden(T _value);
	std::tuple<std::shared_ptr<std::vector<BinarySearchTree<T>::BinarySearchTreeNode**>>, bool>
		delete_hidden(T _value);
	
	static BinarySearchTreeNode *create_node(T _value);
	static int get_height (BinarySearchTreeNode *node);
	
	BinarySearchTreeNode *search_mem(T _value);

public:
	BinarySearchTree();
	BinarySearchTree(T _value);
	~BinarySearchTree();
	
	template<typename... Args>
	void inorder  (std::function<void(T value, Args...)> f, Args... args);
	template<typename... Args>
	void preorder (std::function<void(T value, Args...)> f, Args... args);
	template<typename... Args>
	void postorder(std::function<void(T value, Args...)> f, Args... args);
	
	bool search_element(T _value);
	
	virtual bool insert_element(T _value);
	virtual bool delete_element(T _value);
	
	int get_size();
	int get_count(T _value);
	int get_depth(T _value);
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree():
	root(nullptr),
	size (0)
{  }

template<typename T>
BinarySearchTree<T>::BinarySearchTree(T _value):
	size(1)
{
	root = create_node(_value);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	delete_tree(root);
}

template<typename T>
typename BinarySearchTree<T>::BinarySearchTreeNode *BinarySearchTree<T>::create_node(T _value)
{
	return new BinarySearchTreeNode(_value);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::inorder(std::function<void(T value, Args... args)> f, Args... args)
{
	inorder(root, f, args...);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::inorder(BinarySearchTree<T>::BinarySearchTreeNode *node,
	std::function<void(T value, Args...)> f, Args... args)
{
	if (!node) return;
	
	inorder(node->left, f, args...);
	f(node->value, args...);
	inorder(node->right, f, args...);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::preorder(std::function<void(T value, Args... args)> f, Args... args)
{
	preorder(root, f, args...);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::preorder(BinarySearchTree<T>::BinarySearchTreeNode *node,
	std::function<void(T value, Args...)> f, Args... args)
{
	if (!node) return;
	
	f(node->value, args...);
	preorder(node->left, f, args...);
	preorder(node->right, f, args...);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::postorder(std::function<void(T value, Args... args)> f, Args... args)
{
	postorder(root, f, args...);
}

template<typename T>
template<typename... Args>
void BinarySearchTree<T>::postorder(BinarySearchTree<T>::BinarySearchTreeNode *node,
	std::function<void(T value, Args...)> f, Args... args)
{
	if (!node) return;
	
	postorder(node->left,  f, args...);
	postorder(node->right, f, args...);
	f(node->value, args...);
}

template<typename T>
int BinarySearchTree<T>::get_height(typename BinarySearchTree<T>::BinarySearchTreeNode *node)
{
	return (node)?(node->depth):0;
}

template<typename T>
bool BinarySearchTree<T>::search_element(T _value)
{
	return search_mem(_value);
}

template<typename T>
std::tuple<std::shared_ptr<std::vector<typename BinarySearchTree<T>::BinarySearchTreeNode**>>, bool>
	BinarySearchTree<T>::delete_hidden(T _value)
{
	BinarySearchTreeNode **del_node = &root;
	
	auto path = std::make_shared<std::vector<BinarySearchTreeNode**>>();
	auto dir_path = std::vector<bool>();
	
	path->   reserve(this->size);
	dir_path.reserve(this->size);

	while (*del_node && (*del_node)->value != _value)
	{
		if ((*del_node)->value > _value)
		{
			path->   push_back(del_node);
			dir_path.push_back(false);
			del_node = &((*del_node)->left);
		}
		else if ((*del_node)->value < _value)
		{
			path->   push_back(del_node);
			dir_path.push_back(true);
			del_node = &((*del_node)->right);
		}
	}
	path->push_back(del_node);
	
	if (!(*del_node)) return { path, false };
	
	if ((*del_node)->count > 1)
	{
		--(*del_node)->count;
		return { path, true };
	}
	
	--this->size;
	
	if (!(*del_node)->left || (!(*del_node)->right))
	{
		BinarySearchTreeNode *temp = *del_node;
		*del_node = ((*del_node)->left)?((*del_node)->left):((*del_node)->right);
		delete temp;
	}
	else
	{
		BinarySearchTreeNode **max = &((*del_node)->left);
		
		path->push_back(max);
		
		while ((*max)->right)
		{
			max = &((*max)->right);
			path->push_back(max);
		}
		
		(*del_node)->value = (*max)->value;
		(*del_node)->count = (*max)->count;
		
		BinarySearchTreeNode *temp = *max;
		*max = ((*max)->left)?((*max)->left):((*max)->right);
		delete temp;
	}
	
	for (auto it = path->rbegin() + 1; it != path->rend(); ++it)
	{
		(**it)->depth = std::max(get_height((**it)->left), get_height((**it)->right)) + 1;
	}	
	
	return { path, true };
}

template<typename T>
std::tuple<std::shared_ptr<std::vector<typename BinarySearchTree<T>::BinarySearchTreeNode**>>, bool>
	BinarySearchTree<T>::insert_hidden(T _value)
{
	BinarySearchTreeNode **node = &(this->root);
	
	auto path     = std::make_shared<std::vector<BinarySearchTreeNode**>>();
	//Use a pointer to prevent copying the vector when returning
	
	auto dir_path = std::vector<bool>();//Where left = false, right = true
	//It saves the directions took by the root to the inserted node
	//Could be done with comparing the node->left, right to the next node in the path
	//But we are trading memory for performance.
	
	path->   reserve(this->size);
	dir_path.reserve(this->size);
	
	while (*node)
	{
		path->push_back(node);
		
		if ((*node)->value > _value)      
		{
			node = &((*node)->left);
			dir_path.push_back(false);
		}
		else if ((*node)->value < _value) 
		{
			node = &((*node)->right);
			dir_path.push_back(true);
		}
		else 
		{
			++(*node)->count;
			return { path, false };
		}
	}
	++this->size;
	*node = create_node(_value);
	
	if (*node == root) return { path, true };
	
	auto parent = **(path->rbegin());
	if (!parent->left || !parent->right)
	{
		auto it = path->rbegin();
		int i   = path->size() - 1;
		bool stop = false;
		for (; it != path->rend() && !stop; ++it, --i)
		{
			if ( !(**it)->left || !(**it)->right )
			{
				++(**it)->depth;
			}
			else 
			{
				auto traversed_child      = ((dir_path[i])?((**it)->right):((**it)->left));
				auto non_traversed_child = (!(dir_path[i])?((**it)->right):((**it)->left));
				if ( traversed_child->depth > non_traversed_child->depth )
				{	
					++(**it)->depth;
				}
				else if ( traversed_child->depth <= non_traversed_child->depth )
				{
					stop = !stop; 
				}
			}
		}
	}
	
	return { path, true };
}

template<typename T>
bool BinarySearchTree<T>::insert_element(T _value)
{
	return std::get<1>(insert_hidden(_value));
}

template<typename T>
bool BinarySearchTree<T>::delete_element(T _value)
{
	return std::get<1>(delete_hidden(_value));
}

template<typename T>
void BinarySearchTree<T>::delete_tree(BinarySearchTree<T>::BinarySearchTreeNode *node)
{
	if (!node) return;
	
	delete_tree(node->left);
	delete_tree(node->right);
	delete node;	
}

template<typename T>
int BinarySearchTree<T>::get_size() { return this->count; }

template<typename T>
int BinarySearchTree<T>::get_count(T _value)
{
	auto result = search_mem(_value);
	return result?(result->count):(-1);
}

template<typename T>
int BinarySearchTree<T>::get_depth(T _value)
{
	auto result = search_mem(_value);
	return result?(result->depth):(-1);
}

template<typename T>
typename BinarySearchTree<T>::BinarySearchTreeNode *BinarySearchTree<T>::search_mem(T _value)
{
	BinarySearchTreeNode *node = this->root;
	
	while (node)
	{
		if (node->value > _value)      node = node->left;
		else if (node->value < _value) node = node->right;
		else return node;
	}
	
	return nullptr;
}

#endif