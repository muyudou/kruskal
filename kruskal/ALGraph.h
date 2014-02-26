/************************************************************
 ALGraph: ͼ�Ľṹ ͼ�Ĳ���
 �洢Ϊ�ڽӱ������һ���ߵļ���arcs
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

struct ArcLine          //ÿ���ߵĽṹ
{
	int source;         //�ߵ�Դ���
	int dest;           //�ߵ�Ŀ�Ľ��
	int weight;         //�ߵ�Ȩ��
};

//һ�㽫��ϵ���������Ϊ�ǳ�Ա����
bool operator==(const ArcLine& arc1, const ArcLine& arc2)
{
	return arc1.source == arc2.dest && arc1.dest == arc2.source;
	/*&& weight == arc.weight;*/
}

//һ�㽫��ϵ���������Ϊ�ǳ�Ա����
bool operator!=(const ArcLine& arc1, const ArcLine& arc2)
{
	return !(arc1 == arc2);
	/*&& weight == arc.weight;*/
}

//һ�㽫��ϵ���������Ϊ�ǳ�Ա����
bool operator<(const ArcLine& arc1, const ArcLine& arc2)
{
     return arc1.weight < arc2.weight;
}

/*******************************************************/
/*��ʱû�õ�
//�ȽϷº���
class ArcLineCompare
{
public:
	bool operator()(const ArcLine& arc1, const ArcLine& arc2)
	{
         return arc1.weight < arc2.weight;
	}
};

//��ȷº���
class equalArcLine
{
public:
	bool operator()(const ArcLine& arc1, const ArcLine& arc2)
	{
		return arc1.source == arc2.dest && arc1.dest == arc2.source;
	}
};

//��������׼������sort
bool lessArcLine(const ArcLine &arc1, const ArcLine &arc2)
{
	return arc1.weight < arc2.weight;
}
*/
/*****************************************************************/

//�ڽӱ�Ľṹ
struct ArcNode          //����
{
	int source;        //ͼ�иû���Դ�ڵ�
	int adjvex;        //�û���ָ��Ķ����λ��
	ArcNode *nextarc;  //ָ����һ������ָ��
	int weight;         //ÿ���ߵ�Ȩ��
};

template <typename VertexType>
struct VertexNode           //ͷ���
{
	VertexType data;    //������Ϣ
	ArcNode *firstarc;  //ָ���һ�������ڸö���Ļ���ָ��
	int key;            //Prim:�������Ӹö�������н������б�����С�ߵ�Ȩ��; 
                        //BellmanFord:��¼��Դ��㵽�ý������·��Ȩ�ص��Ͻ�
	VertexNode *p;      //ָ�������еĸ��ڵ�
	int indegree;       //��¼ÿ����������
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

//ͼ�Ĳ���
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

	//����ͼ������ѡ��
	void Create()
	{
		InitVertics();
	}

	//�����㷨����367ҳͼ����Ȩ����ͼ
	void CreateWUDG()
	{
		cout << "�����㷨����367ҳͼ����Ȩ����ͼ: " << endl;
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

	//�����㷨����379ҳͼ����Ȩ����ͼ��
	void createWDG()
	{
		cout << "�����㷨����379ҳͼ����Ȩ����ͼ����" << endl;
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

	//�����㷨����382ҳͼ����Ȩ����ͼ��
	void createWDG1()
	{
		cout << "�����㷨����382ҳͼ����Ȩ����ͼ����" << endl;
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

	//�����㷨����384ҳͼ����Ȩ����ͼ��
	void createWDG2()
	{
		cout << "�����㷨����384ҳͼ����Ȩ����ͼ����" << endl;
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

	//���ؽ��
	VNode* getVertexNode(int i)
	{
         return &vertices[i-1];
	}

	//���ر�
	ArcLine* getArcLine(int i)
	{
         return &arcs[i-1];
	}

	//��ӡ�ڽ�����
	virtual void displayGraph()
	{
		for (int i = 0; i < vexnum; i++)
		{
			cout << "��" << i+1 << "�������ǣ�" << vertices[i].data
				<< " ��������Ϊ��" << vertices[i].indegree << " �ڽӱ�Ϊ: ";
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

	//��ӡͼ�ı߼�
	void displayArcs()
	{
		cout << "ͼ�ıߵļ���Ϊ(��Ȩ�ش�С�����˳������)��" << endl;
		vector<ArcLine>::iterator it;
		
		int i = 0;
		for (it = arcs.begin(); it != arcs.end(); it++)
		{
			cout << "�� " << i+1 << "����Դ�ڵ�Ϊ��" << vertices[it->source].data 
				<< " Ŀ�Ľ��Ϊ��" << vertices[it->dest].data 
				<< "Ȩ��Ϊ��" << it->weight << endl;
			i++;
		}
		cout << "*******************************************************" << endl;
	}

	//kruskal�㷨������С������
	vector<ArcLine> &KRUSKAL()
	{
		//������ϱ�ʾ����������
		vector<ArcLine> arcvec;
		//������ཻ�����жϽ���Ƿ�����ͬһ������
		ArraySet<VertexNode<char> > aset(9);

		//ʹÿ������Ϊһ�������ļ��ϣ����һ��aset��vec�����е�һ��Ԫ�أ�
		for (int i = 0; i < vexnum; i++)
		{
			aset.MakeSet1(vertices[i]);
		}

		//���α���ͼ��û���ߣ���aset�жϱ����ߵĽ���Ƿ�����һ�����ϣ�����������
		//������С������������ʹ��������㲢Ϊһ������
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

		cout << "Kruskal���ɵ���С�������ı�����Ϊ��" << endl;
		for (int i = 0; i < arcvec.size(); i++)
		{
			cout << "�� " << i+1 << "����Դ�ڵ�Ϊ��" << vertices[arcvec[i].source].data 
				<< " Ŀ�Ľ��Ϊ��" << vertices[arcvec[i].dest].data
				<< "Ȩ��Ϊ��" << arcvec[i].weight << endl;
		} 
		cout << "*******************************************************" << endl;
		return arcvec;
	}

	//PVnode����׼��
	class PVNodeCompare
	{
	public:
		bool operator() (VNode *pvnode1, VNode *pvnode2)
		{
			return pvnode1->key > pvnode2->key;
		}
	};

	/***************************************************************************
	�����㷨�����ȶ��е�ʵ�֣������д�ŵ���ָ�����ָ�룬���Կ�����������ĸı���ı䡣
	��Ϊ���������е�ֵ����һֱ�仯������ֱ����priority_queue�����invalid heap����
	(����������ѵ�ʵ��Ҫȥ�����ܸı䣬���ǵ������������һ���ı�����°Ѷ�����գ�����Ԫ���ٽ�����һ�Σ�
	���Ӧ�ÿ��ԣ�ľ��ʵ�֣����Ǹ��ҵĽ��������˼����һ�µģ���ԭ����ı�����¶Զѵ���һ��)��
	��ֱ�����ö��㷨make_heap, pop_heap�㷨ʵ��vector�����б���Ķѵ����ݣ���ʵ��һ����
	����Ȼ��popʱ��ԭ�ѻ����µ�����������ֻ�ǽ���һ��Ԫ�������һ��Ԫ�ص�����Ȼ�������һ��Ԫ��ʹ���Ϊһ���ѣ�
	���Ǵ�ʱ�����������������Ѿ��ı��ˣ�����û�е����������ʹȫ�������Ϊһ����ȷ�Ķѣ�����pop�����һ��
	make_heap�㷨��ʹ��������Ѿ��ı���������Ϊһ���ѣ�
	ԭ������ԭ����pop��ֻ������һ��Ԫ�أ�����������Ԫ�أ�dijkstraҲһ������T_T������������
	****************************************************************************/
	//Prim�㷨������С������
	void PRIM(int i)
	{
		vertices[i-1].key = 0;    //��ѡ������key��Ϊ0���Ա�ѡ����һ�����ӵ�Ԫ��

		//greater��������С���ѣ�less��Ĭ��Ϊ�󶥶�
		vector<VNode *> qvnode;   //Ӧ�ý�����keyΪ����С����
		for (int i = 0; i < vexnum; i++)
		{
			qvnode.push_back(&(vertices[i])); //������ָ�����ν��ӣ����γ�һ��С����
		}
		make_heap(qvnode.begin(), qvnode.end(), PVNodeCompare());
		vector<VNode> vv;     //�������γ��ӵĽ��
		int arci = 0;

		cout << "Prim�������С��������" << endl;
		while (qvnode.empty() == false)
		{
			VNode node = *(qvnode.front());     //ѡ��һ��������key��С�Ľ��
			pop_heap(qvnode.begin(), qvnode.end(), PVNodeCompare());
			qvnode.pop_back();
			vv.push_back(node);         //�����ӵĽ��Ž����飬��Ϊû�а취ֱ����pq���ж�ĳһԪ���Ƿ����ڶ��У�
			//���Ե�һ��Ԫ�ز���vv�У�����pq��....

			//���δ�ӡÿ���������ı�

			if (node.p != NULL)
			{
				cout << "�� " << ++arci << "����Դ���Ϊ��" << (node.p)->data
					<< " Ŀ�Ľ��Ϊ��" << node.data
					<< " �ߵ�Ȩ��Ϊ��" << node.key << endl;
			}

			ArcNode *arc = node.firstarc;    //��ʼ����node���ڽӵ�
			while (arc != NULL)
			{
				//��node�����ٽ���v����Qzhong������v.key���ڱߵ�Ȩ��ʱ��
				//����v��key,���ҽ�v�ĸ������Ϊnode;�������̽�ÿ������key��p�������ˡ�
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

	//��ÿ���������·�����ƺ�ǰ�������г�ʼ�������·����ʼ��ΪINT_MAX, p��ʼ��ΪNULL
	//����Դ�ڵ��key��ʼ��Ϊ0
	void InitalizeSingleSource(int index)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vertices[i].key = INT_MAX>>2;
			vertices[i].p = NULL;
		}
		vertices[index].key = 0;
	}

	//�Աߣ�u, v�������ɳڣ���Ŀǰs��v�����·��v.key��s��u�����·������w(u, v)��ֵ���бȽ�
	//����Ⱥ����ֵ��������и��£���v.key���̣����ҽ�p��Ϊu
	void relax(ArcNode *arc)
	{
		//��Ȼ����ˣ���
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
		for (int i = 1; i < vexnum; i++)     //ѭ��������vexnum-1��
		{
			//�������еıߣ�����ÿ���߽���һ���ɳ�
			for (int j = 0; j < vexnum; j++)
			{
				for (ArcNode *arc = vertices[j].firstarc; arc != NULL; arc = arc->nextarc)
					relax(arc);
			}
		}
		//�ٴα������еıߣ����ͼ���Ƿ����Ȩ��Ϊ��ֵ�Ļ�·��������ڣ��򷵻�false
		for (int j = 0; j < vexnum; j++)
		{
			for (ArcNode *arc = vertices[0].firstarc; arc != NULL; arc = arc->nextarc)
			{
				if (vertices[arc->adjvex].key > vertices[arc->source].key + arc->weight)
					return false;
			}
		}
		cout << "BellmanFord����ĵ�Դ���·����" << endl;
		for (int i = 1; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
		return true;
	}

	//��һ��ջ��¼���Ϊ0�Ľ�㣬��ջ��Ϊ��ʱ��һ������ջ��Ȼ�����α���������
	//���ڽӱ���ÿ���ڽӵĽ�����ȼ�һ���ڽӵĽ����ȱ�Ϊ0ʱ��ջ��ѭ��ֱ��ջΪ��
	//��count��¼��ջ�Ľ�㣬�������vexnum����ͼ�޻�������������ȷ������ͼ�л�
	pair<bool, vector<int> > TopologicalSort()
	{
        stack<VNode> stk;
		vector<int> ivec;
		for (int i = 0; i < vexnum; i++)
		{
			if (vertices[i].indegree == 0)
			   stk.push(vertices[i]);
		}

		cout << "ͼ�����������ǣ�" << endl;
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

	//�������޻�ͼ�У����԰��ս�������˳������ͼ�ı߽����ɳڲ��������Դ��и���Ȩֵ
	//�����������������㣬���Ա�֤��ȫ��������һ�飬��Ϊ��������޻�ͼ���д�u��v��һ��·����
	//��u�����������еĴ���λ�ڽ��v��ǰ�棬
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
		cout << "DagShortestPaths����ĵ�Դ���·����" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

	void Dijkstra(int index)
	{
        InitalizeSingleSource(index-1);
		vector<VNode> snode;       //�����Ѿ��ҵ����·���Ľ��
        vector<VNode *> que;       //�������ָ������飬���������ִ�жѵ��㷨

		//�����ָ������У��γ���keyΪ�ؼ�ֵ����С��
		for (int i = 0; i < vexnum; i++)
			que.push_back(&(vertices[i]));
		//ʹque����pvnodecompare׼�򹹳�һ����С��
		make_heap(que.begin(), que.end(), PVNodeCompare());   
		
        while (que.empty() == false)
        {
			//��������ӵ����Сkey�Ľ�����
			VNode *node = que.front();
			pop_heap(que.begin(), que.end(), PVNodeCompare());   //�Ӷ���ɾ����С�Ľ�㣬ֻ�Ƿŵ���vector�����
			que.pop_back();      //��vector�е������㳹��ɾ������Ϊ���滹Ҫ������һ�Σ�����Ӱ�����Ķ�����pop�㷨��
            snode.push_back(*node);
			for (ArcNode *arc = node->firstarc; arc != NULL; arc = arc->nextarc)
				relax(arc);
			make_heap(que.begin(), que.end(), PVNodeCompare());
        }
		cout << "Dijkstra����ĵ�Դ���·����" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

protected:
	//��ʼ���ڽ�����ı�ͷ����
	void InitVertics()
	{
		cout << "������ÿ������Ĺؼ��֣�" << endl;
		VertexType val;
		for (int i = 0; i < vexnum; i++)
		{
			cin >> val;
			vertices[i].data = val;
		}
	}

	//����һ������
	void insertArc(int vHead, int vTail, int weight)
	{
		//����һ������
		ArcNode *newArcNode = new ArcNode;
		newArcNode->source = vHead;
		newArcNode->adjvex = vTail;
		newArcNode->nextarc = NULL;
		newArcNode->weight = weight;

		//arcNode ��vertics[vHead]���ڽӱ�
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
		vertices[vTail].indegree++;         //�Ի���β������ȼ�1
	}

	//���α���ÿ�������ڽӵ㣬����ÿ���ߣ���Ϊ����ͼ������ÿ�����൱�����ڽӱ��г���������
	//���Բ���ʱ����һ���жϣ��ж��Ƿ��Ѿ��ڱ߼��У�û������룬�������
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
				//�ж����ڽӱ����ɵı߼��Ƿ��Ѿ����������У�ArcLineҪ����==����������ʲô����ȵı�
				if (find_if(arcs.begin(), arcs.end(), bind2nd(equal_to<ArcLine>(), arc)) == arcs.end())
				{
					arcs.push_back(arc);
				}
				/*arcs2.insert(arc);*/
				node = node->nextarc;
			}		
		}
		//���ձߵ�Ȩ������ArcLine�Ѿ�������<������
        sort(arcs.begin(), arcs.end());
	}


	//��ӡԴ�ڵ㵽i�����·��
	void printPath(int i, int j)
	{
		cout << "��Դ�ڵ� " << vertices[i].data << " ��Ŀ�Ľ�� "
			<< vertices[j].data << " �����·���ǣ�" /*<< endl*/;
		__printPath(&vertices[i], &vertices[j]);
		cout << " Ȩ��Ϊ��" << vertices[j].key << endl;
	}

	void __printPath(VNode* source, VNode* dest)
	{
		if (source == dest)
			cout << source->data << "->";
		else if (dest->p == NULL)
			cout << " no path��" << endl;
		else
		{
			__printPath(source, dest->p);
			cout << dest->data << "->";
		}
	}

private:
	//const���ݳ�Ա�����ڹ��캯�����ʼ��
	static const int MAX_VERTEX_NUM = 20;  //��󶥵����

	VNode vertices[MAX_VERTEX_NUM];      //��Ž�������
	vector<ArcLine> arcs;      //��űߵ�����

	int vexnum;             //ͼ�ĵ�ǰ������
	int arcnum;             //ͼ�Ļ���
};

#endif