#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class ParaParse
{
public:
	vector<vector<int>> para_parsed;  //������ɵĲ���

public:
	ParaParse();
	~ParaParse();
	void parsePara(ifstream& infile);
};
