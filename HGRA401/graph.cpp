#include <iostream>
#include <string>

#include "typedef.h"

#include "graph.h"

//#include "stringConvert.h"

using namespace std;

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	indegree = new int[V];  // ���ȫ����ʼ��Ϊ0
	for (int i = 0; i<V; ++i)
		indegree[i] = 0;
}

Graph::~Graph()
{
	delete[] adj;
	delete[] indegree;
}

void Graph::addEdge(int v, int w)  //v -> w��v �Ƕ���
{
	adj[v].push_back(w);
	++indegree[w];
}

bool Graph::topological_sort()
{
	for (int i = 0; i<V; ++i)
		if (indegree[i] == 0)
			q.push(i);         // ���������Ϊ0�Ķ������

	int count = 0;             // ��������¼��ǰ�Ѿ�����Ķ����� 
	
	while (!q.empty())
	{
		int v = q.front();      // �Ӷ�����ȡ��һ������
		q1.push_back(v);
		q.pop();

		cout << v << " ";      // ����ö���
		++count;
		// ������vָ��Ķ������ȼ�1��������ȼ�Ϊ0�Ķ�����ջ
		list<int>::iterator beg = adj[v].begin();
		for (; beg != adj[v].end(); ++beg)
			if (!(--indegree[*beg]))
				q.push(*beg);   // �����Ϊ0������ջ
	}

	if (count < V)
		return false;           // û�����ȫ�����㣬����ͼ���л�·
	else
		return true;            // ��������ɹ�
}



vector<pe_line_int> Graph::get_config_sorted(vector<pe_line_int> vec_pe_config)
{
	for (unsigned int it = 0; it<q1.size(); it++)
	{
		for (unsigned int j = 0; j < vec_pe_config.size(); j++)
		{
			if (vec_pe_config[j][0] == q1[it])
				pe_config_int_sorted.push_back(vec_pe_config[j]);

		}
	}
	return pe_config_int_sorted;
}

vector<int> Graph::returnRlt()
{
	return q1;
}


int Graph::peNum2index(int peNum)
{
	for (unsigned int i = 0; i <q1.size(); i++)
	{
		if (q1[i] == peNum)
			return i;
		else
			continue;
	}
}

vector<pair<int, int>> Graph::edgeConstruct(vector<vector<int>> vec_config_parsed)
{
	vector<pair<int, int>> return_tmp;
	pair<int, int> edge_tmp;
	unsigned int index;
	for (unsigned int i = 0; i < vec_config_parsed.size(); i++)
	{
		vec_config_parsed[i].push_back(i);
	}
	for (unsigned int i = 0; i < vec_config_parsed.size(); i++)	
	{
		//��ǰ���ڴ������PE
		if (vec_config_parsed[i][0] == 8)
		{
			

			//in1_from
			//in1 from LE
			if (vec_config_parsed[i][5] == 1)
			{
				index = vec_config_parsed[i][3];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 9)//found le
					{
						if (vec_config_parsed[j][1] == index)//found le index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in1 from PE
			else if (vec_config_parsed[i][5] == 2)
			{
				index = vec_config_parsed[i][3];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found pe
					{
						if (vec_config_parsed[j][1] == index)//found pe index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}

			//in1 from fg1
			else if (vec_config_parsed[i][5] == 3)
			{
				index = vec_config_parsed[i][3];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 1)//found fg1
					{
						if (vec_config_parsed[j][1] == index)//found fg1 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in1 from fg2
			else if (vec_config_parsed[i][5] == 4)
			{
				index = vec_config_parsed[i][3];
				if (vec_config_parsed[i][4] == 1)//from port2,��������port1�ķ�����ȥ��
				{
					for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
					{
						if (vec_config_parsed[j][0] == 2)//found fg2
						{
							if (vec_config_parsed[j][1] == index)//found fg2 index
							{
								edge_tmp.first = j;
								edge_tmp.second = i;
								return_tmp.push_back(edge_tmp);
							}
						}
					}
				}

			}
			//in1 from fg3
			else if (vec_config_parsed[i][5] == 5)
			{
				index = vec_config_parsed[i][3];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 3)//found fg3
					{
						if (vec_config_parsed[j][1] == index)//found fg3 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in1 from fg4
			else if (vec_config_parsed[i][5] == 6)
			{
				index = vec_config_parsed[i][3];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 4)//found fg4
					{
						if (vec_config_parsed[j][1] == index)//found fg4 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in1 from fg5
			else if (vec_config_parsed[i][5] == 7)
			{
			}
			//in1 from fg6
			else if (vec_config_parsed[i][5] == 8)
			{
			}
			//in1 from fg7
			else if (vec_config_parsed[i][5] == 9)
			{
			}

			//in2 from
			//in2 from LE
			if (vec_config_parsed[i][8] == 1)
			{
				index = vec_config_parsed[i][6];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 9)//found le
					{
						if (vec_config_parsed[j][1] == index)//found le index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from PE
			if (vec_config_parsed[i][8] == 2)
			{
				index = vec_config_parsed[i][6];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found pe
					{
						if (vec_config_parsed[j][1] == index)//found pe index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from fg1
			if (vec_config_parsed[i][8] == 3)
			{
				index = vec_config_parsed[i][6];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 1)//found fg1
					{
						if (vec_config_parsed[j][1] == index)//found fg1 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from fg2
			if (vec_config_parsed[i][8] == 4)
			{
				index = vec_config_parsed[i][6];
				if (vec_config_parsed[i][7] == 1)//from port2,��������port1�ķ�����ȥ��
				{
					for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
					{
						if (vec_config_parsed[j][0] == 2)//found fg2
						{
							if (vec_config_parsed[j][1] == index)//found fg2 index
							{
								edge_tmp.first = j;
								edge_tmp.second = i;
								return_tmp.push_back(edge_tmp);
							}
						}
					}
				}

			}
			//in2 from fg3
			if (vec_config_parsed[i][8] == 5)
			{
				index = vec_config_parsed[i][6];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 3)//found fg3
					{
						if (vec_config_parsed[j][1] == index)//found fg3 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from fg4
			if (vec_config_parsed[i][8] == 6)
			{
				index = vec_config_parsed[i][6];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 4)//found fg4
					{
						if (vec_config_parsed[j][1] == index)//found fg4 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from fg5
			if (vec_config_parsed[i][8] == 7)
			{

			}

			//in3 from
			//in3 from LE
			if (vec_config_parsed[i][11] == 1)
			{
				index = vec_config_parsed[i][9];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 9)//found le
					{
						if (vec_config_parsed[j][1] == index)//found le index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in3 from PE
			if (vec_config_parsed[i][11] == 2)
			{
				index = vec_config_parsed[i][9];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found pe
					{
						if (vec_config_parsed[j][1] == index)//found pe index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in3 from fg1
			if (vec_config_parsed[i][11] == 3)
			{
				index = vec_config_parsed[i][9];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 1)//found fg1
					{
						if (vec_config_parsed[j][1] == index)//found fg1 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in3 from fg2
			if (vec_config_parsed[i][11] == 4)
			{
				index = vec_config_parsed[i][9];
				if (vec_config_parsed[i][10] == 1)//from port2,��������port1�ķ�����ȥ��
				{
					for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
					{
						if (vec_config_parsed[j][0] == 2)//found fg2
						{
							if (vec_config_parsed[j][1] == index)//found fg2 index
							{
								edge_tmp.first = j;
								edge_tmp.second = i;
								return_tmp.push_back(edge_tmp);
							}
						}
					}
				}
			}
			//in3 from fg3
			if (vec_config_parsed[i][11] == 5)
			{
				index = vec_config_parsed[i][9];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 3)//found fg3
					{
						if (vec_config_parsed[j][1] == index)//found fg3 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in3 from fg4
			if (vec_config_parsed[i][11] == 6)
			{
				index = vec_config_parsed[i][9];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 4)//found fg4
					{
						if (vec_config_parsed[j][1] == index)//found fg4 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in3 from fg5
			if (vec_config_parsed[i][11] == 7)
			{

			}
		}
		//��ǰ���ڴ������LE
		else if (vec_config_parsed[i][0] == 9)
		{
			//LE������Դֻ����PE
			index = vec_config_parsed[i][2];
			for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
			{
				if (vec_config_parsed[j][0] == 8)//found pe
				{
					if (vec_config_parsed[j][1] == index)//found pe index
					{
						edge_tmp.first = j;
						edge_tmp.second = i;
						return_tmp.push_back(edge_tmp);
					}
				}
			}
		}
		//��ǰ���ڴ������SE
		else if (vec_config_parsed[i][0] == 0)
		{
			//SE������Դֻ����PE
			//addr from
			if (vec_config_parsed[i][4])
			{
				index = vec_config_parsed[i][2];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found pe
					{
						if (vec_config_parsed[j][1] == index)//found pe index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}

			//data from
			if (vec_config_parsed[i][7])
			{
				index = vec_config_parsed[i][5];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found pe
					{
						if (vec_config_parsed[j][1] == index)//found pe index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			

		}
		//��ǰ���ڴ������FG1
		else if (vec_config_parsed[i][0] == 1)
		{
			//ֻ���������룬һ��������begin��һ������fg2�ķ������������Ҫ��Ϊ��ȵı�
		}
		//��ǰ���ڴ������FG2
		else if (vec_config_parsed[i][0] == 2)
		{
			//in1 from
			if (vec_config_parsed[i][4] == 1)//in1 from PE
			{
				index = vec_config_parsed[i][2];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)// found PE
					{
						if (vec_config_parsed[j][1] == index)//found PE index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			else if (vec_config_parsed[i][4] == 2)//in1 from fg1
			{
			}
			else if (vec_config_parsed[i][4] == 3)//in1 from fg2
			{
				index = vec_config_parsed[i][2];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 2)//found fg2
					{
						if (vec_config_parsed[j][1] == index)//found fg2 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			//in2 from
			if (vec_config_parsed[i][7] == 1)//in2 from PE
			{
				index = vec_config_parsed[i][5];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found PE
					{
						if (vec_config_parsed[j][1] == index)//found PE index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			else if (vec_config_parsed[i][7] == 2)//in2 from fg1
			{
			}
			else if (vec_config_parsed[i][7] == 3)//in2 from fg2
			{
				index = vec_config_parsed[i][5];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 2)//found fg2
					{
						if (vec_config_parsed[j][1] == index)//found fg2 index
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			
		}
		//��ǰ���ڴ������FG3
		else if (vec_config_parsed[i][0] == 3)
		{
			//fg3�����붼��������PE������������˿ڵĸ����ǲ�����
		}
		//��ǰ���ڴ������FG4
		else if (vec_config_parsed[i][0] == 4)
		{
			//in1 from
			if (vec_config_parsed[i][4] == 1)//in1 from PE
			{
				index = vec_config_parsed[i][2];
				for (unsigned int j = 0; j < vec_config_parsed.size(); j++)
				{
					if (vec_config_parsed[j][0] == 8)//found PE
					{
						if (vec_config_parsed[j][1] == index)
						{
							edge_tmp.first = j;
							edge_tmp.second = i;
							return_tmp.push_back(edge_tmp);
						}
					}
				}
			}
			else if (vec_config_parsed[i][4] == 2)//in1 from fg1
			{
				//
			}
			else if (vec_config_parsed[i][4] == 3)//in1 from fg2
			{
				//��Դ��fg2�ķ�������ıߺ���
			}
			else if (vec_config_parsed[i][4] == 4)//in1 from fg3
			{
			}
		}
		else if (vec_config_parsed[i][0] == 5)//���ڴ������fg5
		{
		}

		
	}
	return return_tmp;
}




//Config2graph::Config2graph(int v)  //���캯��
//{
//	this->v = v;
//	li = new list<int>[v];
//	indegree = new int[v];
//	for (int i = 0; i < v; i++)
//	{
//		indegree[i] = 0;
//
//	}
//}
//Config2graph::~Config2graph()	//��������
//{
//	delete[] li;
//	delete[]indegree;
//}
//
//void Config2graph::addEdge(int v, int w)	//v-->w �ı�
//{
//	li[v].push_back(w);
//	indegree[w]++;
//}
//
//
//bool Config2graph::topoSort()
//{
//	for (int i = 0; i < v; i++)
//	{
//		if (indegree[i] == 0)
//			q.push(i);
//	}
//
//	int count = 0;				//��¼��ǰ��������Ķ�����Ŀ
//	while (!q.empty())
//	{
//		int u = q.front();
//		q1.push_back(u);
//		q.pop();
//		count++;
//		cout << "��ǰ������Ķ����ǣ� " << u << "..." << endl;
//		//������uָ��Ķ������ȼ�ȥ1���������Ϊ0�Ķ�����ջ
//		list<int>::iterator it = li[u].begin();
//		for (; it != li[u].end(); it++)
//		{
//			indegree[*it]--;
//			if (!(indegree[*it]))
//				q.push(*it);
//		}
//		if (count < v)
//			return false;
//		else
//			return true;
//		
//
//	}
//
//}






