//�����ǽ����Ż��������ļ����������ֻ���������Ϣ�浽�ļ���ȥ������
//��Ϊ3�����֣���ΪPE���ý�����SE\LE���ý�����ϸ���Ȳ��ּ�TA���ý���
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "define.h"
typedef unsigned int uint;
using namespace std;
class ConfigParse
{private:
	pair<int,int> pefield1(string& str);		//PE�ֶ�1����[pe_index]
	int pefield2(string& str);					//PE�ֶ�2����[opcode]
	vector<int> pefield3_4_5(string& str);		//PE�ֶ���3,4,5����[in1_from+in1_port+in1_flag]																							
	int pefield6(string& str);					//PE�ֶ�6����[lr_from]
	int pefield7(string& str);					//PE�ֶ�7����[alu_in1_from]
	int pefield8(string& str);					//PE�ֶ�8����[alu_in2_from]
	int pefield9(string& str);					//PE�ֶ�9����[ob1_from]
	int pefield10(string& str);					//PE�ֶ�10����[ob2_from]
	int pefield11(string& str);					//PE�ֶ�11����[end_node]
	int pefield12(string& str);					//PE�ֶ�12����[pemode]
	bool pefield13(string& str);				//PE�ֶ�13����[tagMode]
	bool pefield14_15_16(string& str);			//PE�ֶ�14,15,16����
	//le
	pair<int,int> lefield1(string& str);		//LE�ֶ�1����[le_index]
	vector<int> lefield2(string& str);			//LE�ֶ�2����[in_from+in_port]
	bool lefield3(string& str);					//LE�ֶ�3����[tagMode]
	//se
	pair<int,int> sefield1(string& str);		//SE�ֶ�1����[category+index]
	vector<int> sefield2(string& str);			//SE�ֶ�2����[se_addr_from]
	vector<int> sefield3(string& str);			//SE�ֶ�3����[se_data_from]
	bool sefield4(string& str);					//LE�ֶ�4����[tagMode]
	//fg
	pair<int, int> fgfield1(string& str);		//FG�ֶ�1����
	vector<int> fgfield2(string& str);
	vector<int> fgfield3(string& str);
	vector<int> fgfieldo(string& str);			//FG�����ֶν�������Ҫ���join��ϸ���Ƚڵ�
	bool fgfield4(string& str);					//FG�ֶ�4����[tagMode]
	//ta
	pair<int, int> tafield1(string& str);		//ta�ֶ�1����
	vector<int> tafield2(string& str);			//ta�ֶ�2����

private:
	std::string::size_type get_num_pos(string& str);	//�ҵ��ַ����������ַ��״γ��ֵ�position
	std::string get_string(string& str);

public:
	ConfigParse();
	~ConfigParse();

	vector<vector<string>> vec_config_ori;			//����֮ǰ�ַ������뵽vector��ȥ
	vector<vector<int>> vec_config_parsed;			//����֮�������
	void configFile2vec(ifstream& config_ori);		//���ļ��ж�ȡ�����ַ�����vector��
	void configVec2parsed();						//��vector�е������ַ�������������

};
