/************************************************************
ArraySet.h: ���ཻ���ϵĲ���
�������ͼ��arrayset��DataTypeΪͼ�Ľ��VertexNode<char>
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
	ArrayNode *p;           //���ĸ���
	int rank;        //���ĸ߶�
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

	//ʹÿ������Ϊһ�������ļ���
	void MakeSet()
	{
		cout << "������ " << number << "�����ݣ�" << endl;
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

	//��·��ѹ�����ҵ�x���ڵļ���
	Node* FindSet(Node *x)
	{
		if (x->p != x)
			x->p = FindSet(x->p);
		return x->p;
	}

	//�ϲ����ϣ���rankֵ��С�ļ��Ϻϲ���rankֵ�ϴ�ļ���
	void UnionSet(Node *nx, Node *ny)
	{
		Node *x = FindSet(nx);
		Node *y = FindSet(ny);
		if (x->rank > y->rank)
			y->p = x; 
		else
		{
			x->p = y;
			if (x->rank == y->rank)   //�����ߵ�rank��ͬ����ʹ������rank����1
				(y->rank)++;
		}
	}

	void display()
	{
		for (int i = 0; i < number; i++)
		{
			cout << "�� " << i+1 << " ����������Ϊ��" << vec[i]->data 
				<< " ���ڵ�Ϊ��" << vec[i]->p->data << " ��Ϊ��" << vec[i]->rank << endl;
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
