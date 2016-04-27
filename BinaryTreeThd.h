# BinaryTreeThd
二叉树的线索化
#pragma once
#include<iostream>
#include<assert.h>

using namespace std;

enum PointerTag
{
	THREAD,//需要线索化
	LINK//不需要线索化
};

template<class T>
struct BinaryTreeNodeThd
{
public:
	BinaryTreeNodeThd(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
public:
	T _data;//数据
	BinaryTreeNodeThd* _left;//左孩子
	BinaryTreeNodeThd* _right;//右孩子
	PointerTag _leftTag;//左孩子的线索化标志
	PointerTag _rightTag;//右孩子的线索化标志
};



template<class T>
class BinaryTreeThd
{
public:
	typedef BinaryTreeNodeThd<T> Node;
public:
	BinaryTreeThd(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;//当前子树根节点的下标
		_root= _CreateBinaryTree(a, size,invalid, index);
	}
public:
	void PrevOrderThreading()//先序线索化
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}
	void InOrderThreading()//中序线索化
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}
	void PosOrderThreading()//后序线索化
	{
		Node* prev = NULL;
		_PosOrderThreading(_root,prev);
	}
	void PrevOrderThd()//先序遍历
	{
		_PrevOrderThd(_root);
	}
	void InOrderThd()//中序遍历
	{
		_InOrderThd(_root);
	}
	void PosOrderThd()//后序遍历
	{
		_PosOrderThd(_root);
	}
protected:
	Node* _CreateBinaryTree(const T*a, size_t size, const T& invalid, size_t& index);
	void _PrevOrderThreading(Node* root, Node* &prev);
	void _InOrderThreading(Node* root, Node* &prev);
	void _PosOrderThreading(Node* root,Node* &prev);
	void _PrevOrderThd(Node* root);
	void _InOrderThd(Node* root);
	void _PosOrderThd(Node* root);
	
private:
	Node* _root;
};

//创建二叉树
template<class T>
BinaryTreeNodeThd<T>* BinaryTreeThd<T>::_CreateBinaryTree(const T*a, size_t size, const T& invalid, size_t& index)
{
	assert(a);
	Node* root = NULL;
	if (index < size&&a[index] != invalid)
	{
		root = new Node(a[index]);//创建根节点
		root->_left = _CreateBinaryTree(a, size, invalid, ++index);//递归创建左子树
		root->_right = _CreateBinaryTree(a, size, invalid, ++index);//递归创建右子树
	}
	return root;
}

//先序线索化
template<class T>
void BinaryTreeThd<T>::_PrevOrderThreading(Node*  root, Node* &prev)
{
	Node* cur = root;
	if (cur == NULL)
	{
		return;
	}
	
	//线索化-left
	if (cur->_left == NULL)
	{
		cur->_left = prev;
		cur->_leftTag = THREAD;
	}
	
	//线索化_right
	if (prev && prev->_right == NULL)
	{
		prev->_right = cur;
		prev->_rightTag = THREAD;
	}
	//更新prev
	prev = cur;

	if (cur->_leftTag == LINK)
	{
		_PrevOrderThreading(cur->_left, prev);//递归遍历并线索化左子树
	}
	if (cur->_rightTag == LINK)
	{	
		_PrevOrderThreading(cur->_right, prev);//递归遍历并线索化右子树
	}
	
}

//先序遍历二叉树
template<class T>
void BinaryTreeThd<T>::_PrevOrderThd(Node* root)
{
	Node* cur = root;
	while (cur)
	{
		cout << cur->_data << " ";
		if (cur->_leftTag == LINK)
		{
			cur = cur->_left;
			continue;//结束本次循环
		}

		cur = cur->_right;
		
	}
}

//中序线索化
template<class T>
void BinaryTreeThd<T>::_InOrderThreading(Node* root, Node* &prev)
{
	Node* cur = root;
	if (cur == NULL)
	{
		return;
	}

	
	_InOrderThreading(cur->_left, prev);
	

	//线索化-left
	if(cur->_left == NULL)
	{
		cur->_left = prev;
		cur->_leftTag = THREAD;
	}

	//线索化_right
	if (prev && prev->_right == NULL)
	{
		prev->_right = cur;
		prev->_rightTag = THREAD;
	}
	//更新prev
	prev = cur;

	_InOrderThreading(cur->_right, prev);
	
}

//中序遍历二叉树
template<class T>
void BinaryTreeThd<T>::_InOrderThd(Node*root)
{
	Node* cur = root;
	while (cur)
	{
		//找到最左下角的节点
		while (cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}

		cout << cur->_data << " ";

		//当cur的右孩子标志域为THREAD时，直接访问其后继，可能有多个连续的后继
		while (cur->_rightTag == THREAD)
		{
			cur = cur->_right;
			cout << cur->_data << " ";
		}
		//右孩子为LINK时，转换为子问题
		cur = cur->_right;
	}
}

//后序线索化
template<class T>
void BinaryTreeThd<T>::_PosOrderThreading(Node* root, Node* &prev)
{
	Node* cur = root;
	if (cur == NULL)
	{
		return;
	}

	if (cur->_leftTag == LINK)
	{
		_PosOrderThreading(cur->_left, prev);//递归遍历并线索化左子树
	}
	if (cur->_rightTag == LINK)
	{
		_PosOrderThreading(cur->_right, prev);//递归遍历并线索化右子树
	}

	//线索化-left
	if (cur->_left == NULL)
	{
		cur->_left = prev;
		cur->_leftTag = THREAD;
	}

	//线索化_right
	if (prev && prev->_right == NULL)
	{
		prev->_right = cur;
		prev->_rightTag = THREAD;
	}
	//更新prev
	prev = cur;
}

//后续遍历二叉线索树
template<class T>
void BinaryTreeThd<T>::_PosOrderThd(Node* root)
{
	Node* cur = root;
	Node* prev = NULL;
	while (cur)
	{
		while (cur->_leftTag == LINK&&cur->_left!=prev)
		{
			cur = cur->_left;
		}
		
		if (cur->_left == LINK || prev == cur->_right)
		{
			cout << cur->_data << " ";
			cur = prev;
		}
		else
		{
			cur = cur->_right;
		}	
	}	
}
