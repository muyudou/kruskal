/************************************************************
 ALGraph: 图的结构 图的操作
 存储为邻接表，多加了一个边的集合arcs
 Date: 2013/12/29
 Author: searchop
************************************************************/

#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include <functional>
#include "ArraySet.h"
using namespace std;

struct ArcLine          //每条边的结构
{
	int source;         //边的源结点
	int dest;           //边的目的结点
	int weight;         //边的权重
};

//一般将关系运算符重载为非成员函数
bool operator==(const ArcLine& arc1, const ArcLine& arc2)
{
	return arc1.source == arc2.dest && arc1.dest == arc2.source;
	/*&& weight == arc.weight;*/
}

//一般将关系运算符重载为非成员函数
bool operator!=(const ArcLine& arc1, const ArcLine& arc2)
{
	return !(arc1 == arc2);
	/*&& weight == arc.weight;*/
}

//一般将关系运算符重载为非成员函数
bool operator<(const ArcLine& arc1, const ArcLine& arc2)
{
     return arc1.weight < arc2.weight;
}

/*******************************************************/
/*暂时没用到
//比较仿函数
class ArcLineCompare
{
public:
	bool operator()(const ArcLine& arc1, const ArcLine& arc2)
	{
         return arc1.weight < arc2.weight;
	}
};

//相等仿函数
class equalArcLine
{
public:
	bool operator()(const ArcLine& arc1, const ArcLine& arc2)
	{
		return arc1.source == arc2.dest && arc1.dest == arc2.source;
	}
};

//弧的排序准则，用于sort
bool lessArcLine(const ArcLine &arc1, const ArcLine &arc2)
{
	return arc1.weight < arc2.weight;
}
*/
/*****************************************************************/

//邻接表的结构
struct ArcNode          //表结点
{
	int source;        //图中该弧的源节点
	int adjvex;        //该弧所指向的顶点的位置
	ArcNode *nextarc;  //指向下一条弧的指针
	int weight;         //每条边的权重
};

template <typename VertexType>
struct VertexNode           //头结点
{
	VertexType data;    //顶点信息
	ArcNode *firstarc;  //指向第一条依附于该顶点的弧的指针
	int key;            //Prim:保存连接该顶点和树中结点的所有边中最小边的权重; 
                        //BellmanFord:记录从源结点到该结点的最短路径权重的上界
	VertexNode *p;      //指向在树中的父节点
	int indegree;       //记录每个顶点的入度
};

template <typename VertexType>
bool operator< (const VertexNode<VertexType>& vn1, const VertexNode<VertexType> &vn2)
{
	return vn1.key < vn2.key;
}

template <typename VertexType>
bool operator> (const VertexNode<VertexType>& vn1, const VertexNode<VertexType> &vn2)
{
	return vn1.key > vn2.key;
}

template <typename VertexType>
bool operator== (const VertexNode<VertexType>& vn1, const VertexNode<VertexType> &vn2)
{
	return vn1.data == vn2.data && vn1.firstarc == vn2.firstarc
		&& vn1.key == vn2.key && vn1.p == vn2.p;
}

//图的操作
template <typename VertexType>
class ALGraph
{
public:
	typedef VertexNode<VertexType> VNode;
	ALGraph(int verNum) : vexnum(verNum), arcnum(0)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vertices[i].firstarc = NULL;
			vertices[i].key = INT_MAX/2;
			vertices[i].p = NULL;
			vertices[i].indegree = 0;
		}
	}

	//构造图，进行选择
	void Create()
	{
		InitVertics();
	}

	//构造算法导论367页图，带权无向图
	void CreateWUDG()
	{
		cout << "构造算法导论367页图，带权无向图: " << endl;
        for (int i = 0; i < vexnum; i++)
        {
			vertices[i].data = 'a'+i;
        }

		insertArc(0, 1, 4);
		insertArc(0, 7, 8);
		insertArc(1, 2, 8);
		insertArc(1, 7, 11);
		insertArc(2, 3, 7);
		insertArc(2, 8, 2);
		insertArc(2, 5, 4);
		insertArc(3, 4, 9);
		insertArc(3, 5, 14);
		insertArc(4, 5, 10);
		insertArc(5, 6, 2);
		insertArc(6, 7, 1);
		insertArc(6, 8, 6);
		insertArc(7, 8, 7);

		insertArc(1, 0, 4);
		insertArc(7, 0, 8);
		insertArc(2, 1, 8);
		insertArc(7, 1, 11);
		insertArc(3, 2, 7);
		insertArc(8, 2, 2);
		insertArc(5, 2, 4);
		insertArc(4, 3, 9);
		insertArc(5, 3, 14);
		insertArc(5, 4, 10);
		insertArc(6, 5, 2);
		insertArc(7, 6, 1);
		insertArc(8, 6, 6);
		insertArc(8, 7, 7);

		initArcs();
		/*displayArcs();*/
		/*displayArcs1();*/
	}

	//构造算法导论379页图（带权有向图）
	void createWDG()
	{
		cout << "构造算法导论379页图（带权有向图）：" << endl;
		int i;
		for (i = 0; i < 2; i++)
            vertices[i].data = 's' + i;
		for (i = 2; i < vexnum; i++)
		    vertices[i].data = 'x'+i-2;

		insertArc(0, 1, 6);
		insertArc(0, 3, 7);
		insertArc(1, 2, 5);
		insertArc(1, 3, 8);
		insertArc(1, 4, -4);
		insertArc(2, 1, -2);
		insertArc(3, 2, -3);
		insertArc(3, 4, 9);
		insertArc(4, 2, 7);
		insertArc(4, 0, 2);
	}

	//构造算法导论382页图（带权有向图）
	void createWDG1()
	{
		cout << "构造算法导论382页图（带权有向图）：" << endl;
		int i;
		for (i = 0; i < 3; i++)
			vertices[i].data = 'r' + i;
		for (i = 3; i < vexnum; i++)
			vertices[i].data = 'x'+i-3;

		insertArc(0, 1, 5);
		insertArc(0, 2, 3);
		insertArc(1, 2, 2);
		insertArc(1, 3, 6);
		insertArc(2, 3, 7);
		insertArc(2, 4, 4);
		insertArc(2, 5, 2);
		insertArc(3, 4, -1);
		insertArc(3, 5, 1);
		insertArc(4, 5, -2);
	}

	//构造算法导论384页图（带权有向图）
	void createWDG2()
	{
		cout << "构造算法导论384页图（带权有向图）：" << endl;
		int i;
		for (i = 0; i < 2; i++)
			vertices[i].data = 's' + i;
		for (i = 2; i < vexnum; i++)
			vertices[i].data = 'x'+i-2;

		insertArc(0, 1, 10);
		insertArc(0, 3, 5);
		insertArc(1, 2, 1);
		insertArc(1, 3, 2);
		insertArc(2, 4, 4);
		insertArc(3, 1, 3);
		insertArc(3, 2, 9);
		insertArc(3, 4, 2);
		insertArc(4, 2, 6);
		insertArc(4, 0, 7);
	}

	//返回结点
	VNode* getVertexNode(int i)
	{
         return &vertices[i-1];
	}

	//返回边
	ArcLine* getArcLine(int i)
	{
         return &arcs[i-1];
	}

	//打印邻接链表
	virtual void displayGraph()
	{
		for (int i = 0; i < vexnum; i++)
		{
			cout << "第" << i+1 << "个顶点是：" << vertices[i].data
				<< " 顶点的入度为：" << vertices[i].indegree << " 邻接表为: ";
			ArcNode *arcNode = vertices[i].firstarc;
			while (arcNode != NULL)
			{
				cout << " -> " << vertices[arcNode->adjvex].data
					<< "(" << arcNode->weight << ")";
				arcNode = arcNode->nextarc;
			}
			cout << endl;
		}
		cout << "*******************************************************" << endl;
	}

	//打印图的边集
	void displayArcs()
	{
		cout << "图的边的集合为(按权重从小到大的顺序排列)：" << endl;
		vector<ArcLine>::iterator it;
		
		int i = 0;
		for (it = arcs.begin(); it != arcs.end(); it++)
		{
			cout << "第 " << i+1 << "条边源节点为：" << vertices[it->source].data 
				<< " 目的结点为：" << vertices[it->dest].data 
				<< "权重为：" << it->weight << endl;
			i++;
		}
		cout << "*******************************************************" << endl;
	}

	//kruskal算法构造最小生成树
	vector<ArcLine> &KRUSKAL()
	{
		//这个集合表示最后的生成树
		vector<ArcLine> arcvec;
		//这个不相交集合判断结点是否属于同一个集合
		ArraySet<VertexNode<char> > aset(9);

		//使每个结点成为一个单独的集合（变成一个aset中vec数组中的一个元素）
		for (int i = 0; i < vexnum; i++)
		{
			aset.MakeSet1(vertices[i]);
		}

		//依次遍历图的没条边，用aset判断边两边的结点是否属于一个集合，不属于则将其
		//加入最小生成树，并且使这两个结点并为一个集合
		for (int i = 0; i < arcnum/2; i++)
		{
			ArcLine *arc = &arcs[i];
			if (aset.FindSet(aset.getNode(arc->source)) 
				!= aset.FindSet(aset.getNode(arc->dest)))
			{
				arcvec.push_back(*arc);
				aset.UnionSet(aset.getNode(arc->source), aset.getNode(arc->dest));
			}
		}

		cout << "Kruskal生成的最小生成树的边依次为：" << endl;
		for (int i = 0; i < arcvec.size(); i++)
		{
			cout << "第 " << i+1 << "条边源节点为：" << vertices[arcvec[i].source].data 
				<< " 目的结点为：" << vertices[arcvec[i].dest].data
				<< "权重为：" << arcvec[i].weight << endl;
		} 
		cout << "*******************************************************" << endl;
		return arcvec;
	}

	//PVnode排序准则
	class PVNodeCompare
	{
	public:
		bool operator() (VNode *pvnode1, VNode *pvnode2)
		{
			return pvnode1->key > pvnode2->key;
		}
	};

	/***************************************************************************
	关于算法中优先队列的实现，队列中存放的是指向结点的指针，所以可以随着数组的改变而改变。
	因为顶点数组中的值，会一直变化，所以直接用priority_queue会产生invalid heap错误
	(可能是这个堆的实现要去内容能改变，除非当结点数组中有一个改变后，重新把队列清空，所有元素再进队列一次，
	这个应该可以，木有实现，但是根我的解决方法中思想是一致的，即原数组改变后，重新对堆调整一下)，
	但直接运用堆算法make_heap, pop_heap算法实现vector数组中保存的堆的内容，其实是一样的
	即虽然在pop时，原堆会重新调整，但调整只是将第一个元素与最后一个元素调换，然后调整第一个元素使其成为一个堆，
	但是此时堆中其他结点的内容已经改变了，它并没有调整其他结点使全部数组成为一个正确的堆，所以pop后调用一次
	make_heap算法，使这个内容已经改变的数组调整为一个堆！
	原来根本原因是pop中只调整了一个元素，并不管其他元素！dijkstra也一样！（T_T）终于明白了
	****************************************************************************/
	//Prim算法构造最小生成树
	void PRIM(int i)
	{
		vertices[i-1].key = 0;    //将选定结点的key设为0，以便选出第一个出队的元素

		//greater建立的是小顶堆，less即默认为大顶堆
		vector<VNode *> qvnode;   //应该建立以key为键的小顶堆
		for (int i = 0; i < vexnum; i++)
		{
			qvnode.push_back(&(vertices[i])); //将结点的指针依次进队，并形成一个小顶堆
		}
		make_heap(qvnode.begin(), qvnode.end(), PVNodeCompare());
		vector<VNode> vv;     //保存依次出队的结点
		int arci = 0;

		cout << "Prim构造的最小生成树：" << endl;
		while (qvnode.empty() == false)
		{
			VNode node = *(qvnode.front());     //选择一个队列中key最小的结点
			pop_heap(qvnode.begin(), qvnode.end(), PVNodeCompare());
			qvnode.pop_back();
			vv.push_back(node);         //将出队的结点放进数组，因为没有办法直接在pq中判断某一元素是否属于队列，
			//所以当一个元素不在vv中，即在pq中....

			//依次打印每条生成树的边

			if (node.p != NULL)
			{
				cout << "第 " << ++arci << "条边源结点为：" << (node.p)->data
					<< " 目的结点为：" << node.data
					<< " 边的权重为：" << node.key << endl;
			}

			ArcNode *arc = node.firstarc;    //开始遍历node的邻接点
			while (arc != NULL)
			{
				//当node结点的临界结点v不再Qzhong，并且v.key大于边的权重时，
				//更新v的key,并且将v的父结点设为node;整个过程将每个结点的key和p都更新了。
				if (find(vv.begin(), vv.end(), vertices[arc->adjvex]) == vv.end()
					&& arc->weight < vertices[arc->adjvex].key)
				{
					VNode pnode = node;
					vertices[arc->adjvex].p = &pnode;
					vertices[arc->adjvex].key = arc->weight;
				}
				arc = arc->nextarc;
			}
			make_heap(qvnode.begin(), qvnode.end(), PVNodeCompare());
		}
		cout << "*******************************************************" << endl;
	}

	//对每个结点的最短路径估计和前驱结点进行初始化，最短路径初始化为INT_MAX, p初始化为NULL
	//并将源节点的key初始化为0
	void InitalizeSingleSource(int index)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vertices[i].key = INT_MAX>>2;
			vertices[i].p = NULL;
		}
		vertices[index].key = 0;
	}

	//对边（u, v）进行松弛，将目前s到v的最短路径v.key与s到u的最短路径加上w(u, v)的值进行比较
	//如果比后面的值还大，则进行更新，将v.key缩短，并且将p置为u
	void relax(ArcNode *arc)
	{
		//竟然溢出了！！
		if (vertices[arc->adjvex].key > vertices[arc->source].key + arc->weight)
		{
			vertices[arc->adjvex].key = vertices[arc->source].key + arc->weight;
            vertices[arc->adjvex].p = &vertices[arc->source];
		}
	}

	//BellmanFord
	bool BellmanFord(int index)
	{
		InitalizeSingleSource(index-1);
		for (int i = 1; i < vexnum; i++)     //循环共进行vexnum-1次
		{
			//遍历所有的边，并对每个边进行一次松弛
			for (int j = 0; j < vexnum; j++)
			{
				for (ArcNode *arc = vertices[j].firstarc; arc != NULL; arc = arc->nextarc)
					relax(arc);
			}
		}
		//再次遍历所有的边，检查图中是否存在权重为负值的环路，如果存在，则返回false
		for (int j = 0; j < vexnum; j++)
		{
			for (ArcNode *arc = vertices[0].firstarc; arc != NULL; arc = arc->nextarc)
			{
				if (vertices[arc->adjvex].key > vertices[arc->source].key + arc->weight)
					return false;
			}
		}
		cout << "BellmanFord求出的单源最短路径：" << endl;
		for (int i = 1; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
		return true;
	}

	//用一个栈记录入度为0的结点，当栈不为空时，一个结点出栈，然后依次遍历这个结点
	//的邻接表，对每个邻接的结点的入度减一，邻接的结点入度变为0时进栈，循环直到栈为空
	//用count记录出栈的结点，如果等于vexnum，则图无环，拓扑排序正确，否则，图有环
	pair<bool, vector<int> > TopologicalSort()
	{
        stack<VNode> stk;
		vector<int> ivec;
		for (int i = 0; i < vexnum; i++)
		{
			if (vertices[i].indegree == 0)
			   stk.push(vertices[i]);
		}

		cout << "图的拓扑排序是：" << endl;
		int count = 0;
		while (stk.empty() == false)
		{
			cout << stk.top().data << "->";
            ArcNode *arc = stk.top().firstarc;
			if (arc != NULL)
			    ivec.push_back(arc->source);
			stk.pop();			
			count++;
            for (; arc != NULL; arc = arc->nextarc)
            {
                if (!--(vertices[arc->adjvex].indegree))
					stk.push(vertices[arc->adjvex]);
            }
		}
		cout << endl;
		if (count < vexnum)
		    return make_pair(false, ivec);
		else
			return make_pair(true, ivec);
	}

	//在有向无环图中，可以按照结点的拓扑顺序来对图的边进行松弛操作，可以带有负的权值
	//按照拓扑排序遍历结点，可以保证边全部被遍历一遍，因为如果有向无环图中有从u到v的一条路径，
	//则u在拓扑排序中的次序位于结点v的前面，
	void DagShortestPaths(int index)
	{
        vector<int> vv = TopologicalSort().second;
		InitalizeSingleSource(index-1);
		for (int i = 0; i < vv.size(); i++)
		{
            ArcNode* arc = vertices[vv[i]].firstarc;
			for (; arc != NULL; arc = arc->nextarc)
				relax(arc);
		}
		cout << "DagShortestPaths求出的单源最短路径：" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

	void Dijkstra(int index)
	{
        InitalizeSingleSource(index-1);
		vector<VNode> snode;       //保存已经找到最短路径的结点
        vector<VNode *> que;       //保存结点的指针的数组，用这个数组执行堆的算法

		//将结点指针进队列，形成以key为关键值的最小堆
		for (int i = 0; i < vexnum; i++)
			que.push_back(&(vertices[i]));
		//使que按照pvnodecompare准则构成一个最小堆
		make_heap(que.begin(), que.end(), PVNodeCompare());   
		
        while (que.empty() == false)
        {
			//将队列中拥有最小key的结点出队
			VNode *node = que.front();
			pop_heap(que.begin(), que.end(), PVNodeCompare());   //从堆中删除最小的结点，只是放到了vector的最后
			que.pop_back();      //将vector中的这个结点彻底删除，因为后面还要再排序一次，以免影响后面的堆排序，pop算法。
            snode.push_back(*node);
			for (ArcNode *arc = node->firstarc; arc != NULL; arc = arc->nextarc)
				relax(arc);
			make_heap(que.begin(), que.end(), PVNodeCompare());
        }
		cout << "Dijkstra求出的单源最短路径：" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

protected:
	//初始化邻接链表的表头数组
	void InitVertics()
	{
		cout << "请输入每个顶点的关键字：" << endl;
		VertexType val;
		for (int i = 0; i < vexnum; i++)
		{
			cin >> val;
			vertices[i].data = val;
		}
	}

	//插入一个表结点
	void insertArc(int vHead, int vTail, int weight)
	{
		//构造一个表结点
		ArcNode *newArcNode = new ArcNode;
		newArcNode->source = vHead;
		newArcNode->adjvex = vTail;
		newArcNode->nextarc = NULL;
		newArcNode->weight = weight;

		//arcNode 是vertics[vHead]的邻接表
		ArcNode *arcNode = vertices[vHead].firstarc;
		if (arcNode == NULL)
			vertices[vHead].firstarc = newArcNode;
		else
		{
			while (arcNode->nextarc != NULL)
			{
				arcNode = arcNode->nextarc;		
			}
			arcNode->nextarc = newArcNode;
		}
		arcnum++;
		vertices[vTail].indegree++;         //对弧的尾结点的入度加1
	}

	//依次遍历每个结点的邻接点，遍历每条边，因为无向图，所以每条边相当于在邻接表中出现了两次
	//所以插入时进行一次判断，判断是否已经在边集中，没有则插入，有则放弃
	void initArcs()
	{
		for (int i = 0; i < vexnum; i++)
		{
            ArcNode *node = vertices[i].firstarc;
			
			while (node != NULL)
			{
				ArcLine arc;
                arc.source = i;
				arc.dest = node->adjvex;
				arc.weight = node->weight;
				//判断由邻接表生成的边集是否已经加入数组中，ArcLine要重载==操作，定义什么是相等的边
				if (find_if(arcs.begin(), arcs.end(), bind2nd(equal_to<ArcLine>(), arc)) == arcs.end())
				{
					arcs.push_back(arc);
				}
				/*arcs2.insert(arc);*/
				node = node->nextarc;
			}		
		}
		//按照边的权重排序，ArcLine已经重载了<操作符
        sort(arcs.begin(), arcs.end());
	}


	//打印源节点到i的最短路径
	void printPath(int i, int j)
	{
		cout << "从源节点 " << vertices[i].data << " 到目的结点 "
			<< vertices[j].data << " 的最短路径是：" /*<< endl*/;
		__printPath(&vertices[i], &vertices[j]);
		cout << " 权重为：" << vertices[j].key << endl;
	}

	void __printPath(VNode* source, VNode* dest)
	{
		if (source == dest)
			cout << source->data << "->";
		else if (dest->p == NULL)
			cout << " no path！" << endl;
		else
		{
			__printPath(source, dest->p);
			cout << dest->data << "->";
		}
	}

private:
	//const数据成员必须在构造函数里初始化
	static const int MAX_VERTEX_NUM = 20;  //最大顶点个数

	VNode vertices[MAX_VERTEX_NUM];      //存放结点的数组
	vector<ArcLine> arcs;      //存放边的数组

	int vexnum;             //图的当前顶点数
	int arcnum;             //图的弧数
};

#endif