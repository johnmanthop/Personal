#ifndef KTREE_H_INCLUDED
#define KTREE_H_INCLUDED

#include <functional>
#include <algorithm>
#include <queue>
#include <deque>
#include <initializer_list>

template<typename T>
class KTree
{
protected:

	struct KTreeNode
	{
	public:
		std::deque<T> keys;//Here only 1 key is used as the sole value
		//But the a-b tree that derives from KTree used more than 1 key
		std::deque<KTreeNode*> children;
		
		KTreeNode *parent;
	public:
		KTreeNode(KTreeNode *_parent): parent(_parent) {}
		KTreeNode(std::initializer_list<T> list, KTreeNode *_parent): keys(list), parent(_parent) {}
		
	};
private:
	bool delete_leaf(KTreeNode *node);
	bool delete_node(KTreeNode *node, const T& _child);
protected:
	static KTreeNode *create_node(const T& _value, KTreeNode *parent);
	
	virtual KTreeNode *search_mem(const T& _value) const;
	
	template<typename... Args>
	void traverse(KTreeNode *node, std::function<void(T, Args...)> f, Args... args);
	
	void delete_tree(KTreeNode *node);
protected:
	KTreeNode *root;
	int size;
public:
	KTree();
	KTree(const T& _value);
	~KTree();

	T get_parent(const T& _value);
	
	std::deque<T> get_children(const T& _value);
	
	bool replace_value (const T& _current, const T& _value);
	bool add_leaf      (const T& _current, const T& _value);
	
	bool set_root      (const T& _value);
	bool create_root   (const T& _value);
	bool search        (const T& _value) const;
	
	bool delete_element(const T& _value, const T& _child);//When the user does not know weather the to delete node is a leaf or not
	bool delete_leaf   (const T& _value);          //If it is a leaf, the _child is ignored
	bool delete_node   (const T& _value, const T& _child);
	
	template<typename... Args>
	void traverse(std::function<void(T, Args...)> f, Args... args);
	//I think this is called Euler traversal (?)
	int get_size() const;
};

template<typename T>
typename KTree<T>::KTreeNode *KTree<T>::create_node(const T& _value, typename KTree<T>::KTreeNode *parent)
{
	return new KTree<T>::KTreeNode({_value}, parent);
}

template<typename T>
KTree<T>::KTree():
	root(nullptr),
	size(0)
{  }

template<typename T>
KTree<T>::KTree(const T& _value):
	size(1)
{
	this->root = create_node(_value, nullptr);
}

template<typename T>
KTree<T>::~KTree()
{
	delete_tree(this->root);
}

template<typename T>
template<typename... Args>
void KTree<T>::traverse(std::function<void(T, Args... args)> f, Args... args)
{
	traverse(root, f, args...);
}

template<typename T>
template<typename... Args>
void KTree<T>::traverse(KTree<T>::KTreeNode *node,
	std::function<void(T, Args...)> f, Args... args)
{
	if (!node) return;
	
	f(node->keys[0], args...);
	for (auto i : node->children) traverse(i, f, args...);
}

template<typename T>
bool KTree<T>::replace_value(const T& _current, const T& _value)
{
	KTreeNode *node = search_mem(_current);
	if (!node) return false;
	
	node->keys[0] = _value;
	return true;
}

template<typename T>
T KTree<T>::get_parent(const T& _value)
{
	return search_mem(_value)->parent->keys[0];
}

template<typename T>
bool KTree<T>::search(const T& _value) const
{
	return search_mem(_value);
}

template<typename T>
bool KTree<T>::add_leaf(const T& _current, const T& _value)
{
	KTreeNode *parent = search_mem(_current);
	
	if (!parent) return false;
	
	++size;
	parent->children.push_back(new KTreeNode({_value}, parent));
	return true;
}

template<typename T>
typename KTree<T>::KTreeNode *KTree<T>::search_mem(const T& _value) const
{
	std::queue<KTreeNode*> Q;
	Q.push(this->root);//insert the first node in the Q
	
	while (!Q.empty())
	{
		const auto &top = Q.front();//If the element is not on the top of the Q
		if (top->keys[0] == _value) return Q.front();
		for (auto i : Q.front()->children)
		{//Insert all of it's children at the end of the Q
			Q.push(i);
		}
		Q.pop();//And pop it
	}
	return nullptr;
}

template<typename T>
bool KTree<T>::set_root(const T& _value)
{
	if (!this->root) return false;
	
	this->root->keys[0] = _value;
	return true;
}

template<typename T>
bool KTree<T>::create_root(const T& _value)
{
	if (this->root) return false;
	
	this->root = create_node(_value, nullptr);
	return true;
}

template<typename T>
bool KTree<T>::delete_element(const T& _value, const T& _child)
{//Used if the user does not know weather a node is a leaf or not.
	KTreeNode *node = search_mem(_value);
	if (!node) return false;
	
	if (node->children.size()) return delete_node(_value, _child);
	else return delete_leaf(_value);
}

template<typename T>
bool KTree<T>::delete_leaf(const T& _value)
{
	return delete_leaf(search_mem(_value));
}

template<typename T>
bool KTree<T>::delete_node(const T& _value, const T& _child)
{
	return delete_node(search_mem(_value), _child);
}

template<typename T>
bool KTree<T>::delete_leaf(KTreeNode *node)
{
	if (!node || node->children.size()) return false;// if pointer is null or node is not a leaf
	
	auto pos = std::find(node->parent->children.begin(), node->parent->children.end(), node);
	if (pos == node->parent->children.end()) return false;
	
	node->parent->children.erase(pos);
	delete node;
	
	return true;
}


template<typename T>
bool KTree<T>::delete_node(KTreeNode *node, const T& _child)
{//Replaces a node with one if it's children
	if (!node || !node->children.size()) return false;// if pointer is null or node is a leaf
	
	auto node_pos = std::find(node->parent->children.begin(), node->parent->children.end(), node);
	if (node_pos == node->parent->children.end()) return false;//Find the node's position in it's parent's list
	
	auto child_pos = std::find_if(node->children.begin(), node->children.end(),
		[_child](KTreeNode *a) { return a->keys[0] == _child; });
	if (child_pos == node->children.end()) return false;//Find the child's position in the node's list
	
	for (auto i : node->children) 
	{//Add the node's children to the to-replace child
		i->parent = *child_pos;
		if (i->keys[0] != _child) (*child_pos)->children.push_back(i);
	}//Without adding the child itself
	(*child_pos)->parent = node->parent;//Fix the parent pointers
	node->parent->children.erase(node_pos);//Dump the node from the parent list
	node->parent->children.push_back(*child_pos);//Add the to-replace child to the parent list
	delete node;//Delete the node
	
	return true;
}

template<typename T>
std::deque<T> KTree<T>::get_children(const T& _value)
{
	auto n = search_mem(_value);
	
	if (n) 
	{
		std::deque<T> temp;
		for (auto i : n->children) temp.push_back(i->keys[0]);
		return temp;
	}
	else return {};
}

template<typename T>
int KTree<T>::get_size() const
{
	return this->size;
}

template<typename T>
void KTree<T>::delete_tree(KTreeNode *node)
{
	if (!node) return;
	
	for (auto i : node->children) delete_tree(i);
	delete node;
}

#endif