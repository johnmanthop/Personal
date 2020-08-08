#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "BST.h"

template<typename T>
class AVLTree : public BinarySearchTree<T>
{
private:
	bool balance(typename AVLTree<T>::BinarySearchTreeNode *& node, 
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
	
	int get_balance(typename AVLTree<T>::BinarySearchTreeNode *node);
	
	void balance_parent_tree(typename AVLTree<T>::BinarySearchTreeNode *brake_point,
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
	
	void RR(typename AVLTree<T>::BinarySearchTreeNode *& node,
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
	void RL(typename AVLTree<T>::BinarySearchTreeNode *& node,
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
	void LL(typename AVLTree<T>::BinarySearchTreeNode *& node,
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
	void LR(typename AVLTree<T>::BinarySearchTreeNode *& node,
		std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path);
public:
	AVLTree();
    AVLTree(T _value);
    ~AVLTree();
	
	bool insert_element(T _value);
	bool delete_element(T _value);
};

template<typename T>
AVLTree<T>::AVLTree():BinarySearchTree<T>()
{  }

template<typename T>
AVLTree<T>::AVLTree(T _value): BinarySearchTree<T>(_value)
{  }

template<typename T>
AVLTree<T>::~AVLTree() {}

template<typename T>
bool AVLTree<T>::insert_element(T _value)
{
	auto tuple  = BinarySearchTree<T>::insert_hidden(_value);
	auto path   = std::get<0>(tuple);
	auto result = std::get<1>(tuple);
	
	bool balanced = false;
	for (auto it = path->rbegin(); it != path->rend() && !balanced; ++it)
	{
		if (balance(**it, path)) 
		{
			balanced = true;
		}
	}

	return result;
}

template<typename T>
bool AVLTree<T>::delete_element(T _value)
{
	auto tuple  = BinarySearchTree<T>::delete_hidden(_value);
	auto path   = std::get<0>(tuple);
	auto result = std::get<1>(tuple);
	
	for (auto it = path->rbegin(); it != path->rend(); ++it)
	{
		balance(**it, path);
	}
	
	return result;
}

template<typename T>
bool AVLTree<T>::balance(typename AVLTree<T>::BinarySearchTreeNode *& node, 
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	int b_factor = get_balance(node);

	if (b_factor == -2)
	{
		if (get_balance(node->right) <= 0)
		{//RR rotation
			RR(node, path);
		}
		else
		{//RL rotation
			RL(node, path);
		}
		return true;
	}
	else if (b_factor == 2)
	{
		if (get_balance(node->left) >= 0)
		{//LL rotation
			LL(node, path);
		}
		else
		{//LR rotation
			LR(node, path);
		}
		return true;
	}
	
	return false;
}

template<typename T>
void AVLTree<T>::balance_parent_tree(typename AVLTree<T>::BinarySearchTreeNode *brake_point,
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	auto it = path->rbegin();   
	for (; **it != brake_point; ++it); //Set the iterator to the parent of the first unbalanced node
	++it;
	
	for (; it != path->rend(); ++it)
	{
		(**it)->depth = std::max(BinarySearchTree<T>::get_height((**it)->left), BinarySearchTree<T>::get_height((**it)->right)) + 1;
	}
}

template<typename T>
int AVLTree<T>::get_balance(typename AVLTree<T>::BinarySearchTreeNode *node)
{
	return (node)?(BinarySearchTree<T>::get_height(node->left) - BinarySearchTree<T>::get_height(node->right)):0;
}

template<typename T>
void AVLTree<T>::RR(typename AVLTree<T>::BinarySearchTreeNode *& node,
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	typename AVLTree<T>::BinarySearchTreeNode *a = node;
    typename AVLTree<T>::BinarySearchTreeNode *b = node->right;

    a->right = b->left;
    b->left = a;
    node = b;
	
	a->depth = std::max(BinarySearchTree<T>::get_height(a->left), BinarySearchTree<T>::get_height(a->right)) + 1;
	b->depth = std::max(BinarySearchTree<T>::get_height(b->left), BinarySearchTree<T>::get_height(b->right)) + 1;
	
	balance_parent_tree(node, path);
}

template<typename T>
void AVLTree<T>::LL(typename AVLTree<T>::BinarySearchTreeNode *& node,
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	typename AVLTree<T>::BinarySearchTreeNode *a = node;
    typename AVLTree<T>::BinarySearchTreeNode *b = node->left;

    a->left = b->right;
    b->right = a;
    node = b;
	
	a->depth = std::max(BinarySearchTree<T>::get_height(a->left), BinarySearchTree<T>::get_height(a->right)) + 1;
	b->depth = std::max(BinarySearchTree<T>::get_height(b->left), BinarySearchTree<T>::get_height(b->right)) + 1;
	
	balance_parent_tree(node, path);
}

template<typename T>
void AVLTree<T>::RL(typename AVLTree<T>::BinarySearchTreeNode *& node,
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	typename AVLTree<T>::BinarySearchTreeNode *a = node;
    typename AVLTree<T>::BinarySearchTreeNode *b = node->right;
    typename AVLTree<T>::BinarySearchTreeNode *c = node->right->left;

    b->left = c->right;
    a->right = c->left;
    c->right = b;
    c->left = a;
    node = c;
	
	a->depth = std::max(BinarySearchTree<T>::get_height(a->left), BinarySearchTree<T>::get_height(a->right)) + 1;
	b->depth = std::max(BinarySearchTree<T>::get_height(b->left), BinarySearchTree<T>::get_height(b->right)) + 1;
	c->depth = std::max(BinarySearchTree<T>::get_height(c->left), BinarySearchTree<T>::get_height(c->right)) + 1;
	
	balance_parent_tree(node, path);
}

template<typename T>
void AVLTree<T>::LR(typename AVLTree<T>::BinarySearchTreeNode *& node,
	std::shared_ptr<std::vector<typename AVLTree<T>::BinarySearchTreeNode**>> path)
{
	typename AVLTree<T>::BinarySearchTreeNode *a = node;
    typename AVLTree<T>::BinarySearchTreeNode *b = node->left;
    typename AVLTree<T>::BinarySearchTreeNode *c = node->left->right;

    b->right = c->left;
    a->left = c->right;
    c->left = b;
    c->right = a;
    node = c;
	
	a->depth = std::max(BinarySearchTree<T>::get_height(a->left), BinarySearchTree<T>::get_height(a->right)) + 1;
	b->depth = std::max(BinarySearchTree<T>::get_height(b->left), BinarySearchTree<T>::get_height(b->right)) + 1;
	c->depth = std::max(BinarySearchTree<T>::get_height(c->left), BinarySearchTree<T>::get_height(c->right)) + 1;
	
	balance_parent_tree(node, path);
}

#endif