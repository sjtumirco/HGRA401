
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <random>

using namespace std;

class MemoryInt
{
private:
	vector<int> mem;
	queue<unsigned int> addr_cache;
	vector<bool> mem_state;		//�Ƿ񱻳�ʼ��
	
	pair<unsigned int, int> p;	//mem��ȡ�ķ���ֵ
	bool isInitialized(unsigned int& addr) { return mem_state[addr]; }
	void setInitialized(unsigned int& addr) { mem_state[addr] = 1; }

public:
	MemoryInt();
	MemoryInt(unsigned int depth);
	~MemoryInt();
	unsigned int depth_;		//mem�����
	pair<unsigned int, int> read(unsigned int& addr);
	void write(unsigned int& addr, int& dst);
	void readFromFile(ifstream& infile);
	void writeToFile(ofstream& outfile);
	int random_int(unsigned int min, unsigned int max, unsigned int seed );
	//void readFromIostream(istream& in);	
};
