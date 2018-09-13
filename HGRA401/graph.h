
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include "typedef.h"

//��ͼ�������Ϊ���¼������裺
//1.��ȡ�����ļ��е�ͼ��ϵ����ʼ��ͼ����ӱ���ӱ��Ǵ洢�ö�����ȸ���������
//2.����ÿһ�������������Ϣ����������������������
//3.����ÿһ���������ȸ�����Ϊ0��ʱ��ͽ��ö�����õ����������ȥ������ɾ���ö���͸ö����Ӧ����ӱ��иö�������г���
//4.����������һ������


using namespace std;


class Graph
{
private:
	int V;             // �������
	list<int> *adj;    // �ڽӱ�
	queue<int> q;      
	vector<int> q1;
	int* indegree;     // ��¼ÿ����������
	vector<pe_line_int> pe_config_int_sorted;
	
	
public:
	Graph(int V);                   
	~Graph();  
	//vector<pair<int, int>> return_tmp;//�洢�ߵĹ�ϵ
	void addEdge(int v, int w);
	bool topological_sort();
	vector<int> returnRlt();
	int peNum2index(int);
	vector<pe_line_int> get_config_sorted(vector<pe_line_int> vec_pe_config);
	vector<pair<int, int>> edgeConstruct(vector<vector<int>> vec_config_parsed);

};





