/************************************************************
ArraySet.h: 不相交集合的操作
对于这个图，arrayset的DataType为图的结点VertexNode<char>
Date: 2013/12/29
Author: searchop
************************************************************/

#ifndef ARRAYSET_H
#define ARRAYSET_H

#include <iostream>
#include <vector>
using namespace std;

template <typename DataType>
struct ArrayNode  
{
	DataType data;
	ArrayNode *p;           //结点的父亲
	int rank;        //结点的高度
	ArrayNode() : p(NULL), rank(0) {}
};

template <typename DataType>
class ArraySet
{
public:
	typedef ArrayNode<DataType> Node;
	ArraySet(int num) : number(num)
	{

	}

	//使每个结点成为一个单独的集合
	void MakeSet()
	{
		cout << "请输入 " << number << "个数据：" << endl;
		for (int i = 0; i < number; i++)
		{
			DataType val;
			cin >> val;
			Node *nd = new Node;
			nd->p = nd;
			nd->rank = 0;
			nd->data = val;
			vec.push_back(nd);
		}       
	}

	void MakeSet1(DataType &data)
	{
		Node *nd = new Node;
		nd->p = nd;
		nd->rank = 0;
		nd->data = data;
		vec.push_back(nd);           
	}

	Node *getNode(int i)
	{
		return vec[i];
	}

	//带路径压缩的找到x所在的集合
	Node* FindSet(Node *x)
	{
		if (x->p != x)
			x->p = FindSet(x->p);
		return x->p;
	}

	//合并集合，将rank值较小的集合合并到rank值较大的集合
	void UnionSet(Node *nx, Node *ny)
	{
		Node *x = FindSet(nx);
		Node *y = FindSet(ny);
		if (x->rank > y->rank)
			y->p = x; 
		else
		{
			x->p = y;
			if (x->rank == y->rank)   //当两者的rank相同，则使树根的rank增加1
				(y->rank)++;
		}
	}

	void display()
	{
		for (int i = 0; i < number; i++)
		{
			cout << "第 " << i+1 << " 个结点的数据为：" << vec[i]->data 
				<< " 父节点为：" << vec[i]->p->data << " 秩为：" << vec[i]->rank << endl;
		}
		cout << "*************************************************" << endl;
	}

	~ArraySet()
	{
		for (int i = 0; i < number; i++)
		{
			delete vec[i];
			vec[i] = NULL;
		}
	}

private:
	vector<Node *> vec;
	int number;
};

#endif
