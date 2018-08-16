#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
//#include "configMan.h"
#include "configParse.h"
//#include "exeMan.h"
#include "processingElement.h"
//#include "load.h"
//#include "store.h"
#include "fineGrain.h"
#include "tagAttach.h"
#include "memoryInt.h"
#include "paraParse.h"
#include "graph.h"
#include "define.h"
#include "unitSimFunc.h"
//#include "LSUnit.h"


//test for github branch.
template<typename T>
void connector(bool source_v, T source, bool destination_v, T destination);
template<typename T> void connector(bool source_v, T source, bool destination_v, T destination)
{
	destination_v = source_v;
	destination = source;
}
//Global variable declare
using HGRA::Load;
using HGRA::Store;
ProcessingElement ** pe = new ProcessingElement*[peNums];
Load** le = new Load*[leNums];
Store** se = new Store*[seNums];
LoopBegin** lbegin = new LoopBegin*[lbeginNums];
LoopEnd** lend = new LoopEnd*[lendNums];
Switch** switch_ = new Switch*[switchNums];
Join** join = new Join*[joinNums];
Break** break_ = new Break*[breakNums];
LoopEnds** lends = new LoopEnds*[lendsNums];
TagAttach** ta = new TagAttach*[taNums];
JoinBp** joinbp = new JoinBp*[joinbpNums];
//TagIssue* tagissue = new TagIssue;

//Memory init
MemoryInt memory(memoryDepth);
MemoryInt memory2(memory2depth);//memory that store the result
//Config Files
vector<vector<int>> vec_config_parsed_tmp;
vector<vector<int>> pe_port_fanout;//pe_port_fanout[i],first element is index of PE,the next element are fanout of each port of every PE
bool begin_signal = 1;

ofstream outfile("DEBUG.txt");
ofstream outfile2("DEBUG2.txt");
//no push

void power_callback(double a, double b, double c, double d) {}

int main(int argc,char* argv[])
{

	using namespace DRAMSim;
	bool end = 0;
	uint cnt = 0;
	/*string str_;
	ifstream noti("notification.txt");
	while (getline(noti, str_))
	{
		cout << str_ << endl;
	}
	system("pause");*/

	//hardware generate
	/*ConfigMan configMan;
	ExeMan exeMan;*/
	//unit definition
	if (1)
	{
		for (int i = 0; i < peNums; i++)
		{
			pe[i] = new ProcessingElement;
		}
		for (int i = 0; i < leNums; i++)
		{
			le[i] = new ::Load;
		}
		for (int i = 0; i < seNums; i++)
		{
			se[i] = new ::Store;
		}
		for (int i = 0; i < taNums; i++)
		{
			ta[i] = new TagAttach;
		}
		for (int i = 0; i < lbeginNums; i++)
		{
			lbegin[i] = new LoopBegin;
		}
		for (int i = 0; i < lendNums; i++)
		{
			lend[i] = new LoopEnd;
		}		
		for (int i = 0; i < switchNums; i++)
		{
			switch_[i] = new Switch;
		}
		for (int i = 0; i < joinNums; i++)
		{
			join[i] = new Join;
		}
		for (int i = 0; i < breakNums; i++)
		{
			break_[i] = new Break;
		}
		for (int i = 0; i < lendsNums; i++)
		{
			lends[i] = new LoopEnds;
		}
		for (int i = 0; i < joinbpNums; i++)
		{
			joinbp[i] = new JoinBp;
		}
	}
	
	//memory 
	ifstream memoryInFile;
	memoryInFile.open("memoryInFile.txt");
	memory.readFromFile(memoryInFile);

	//GET DRAM INSTANCE
	
	
	DRAMSim::LSUnit *lsunit = new DRAMSim::LSUnit(le, se);
	DRAMSim::MultiChannelMemorySystem *mem = new DRAMSim::MultiChannelMemorySystem("ini/DDR2_micron_16M_8b_x8_sg3E.ini", "system.ini", ".", "example_app", 16384);
	TransactionCompleteCB *read_cb = new Callback<DRAMSim::LSUnit, void, unsigned, uint64_t, uint64_t>(&(*lsunit), &DRAMSim::LSUnit::mem_read_complete);
	TransactionCompleteCB *write_cb = new Callback<DRAMSim::LSUnit, void, unsigned, uint64_t, uint64_t>(&(*lsunit), &DRAMSim::LSUnit::mem_write_complete);
	mem->RegisterCallbacks(read_cb, write_cb, power_callback);
	lsunit->AttachMem(mem);      //attach
	
	

	//Config file parse
	//Config config;
	ConfigParse cp;

	vector<pe_line_int> vec_pe_config_;
	////handwrite config file parse to auto-generated config file////
	ifstream config_infile;
	config_infile.open(argv[1]);//config files path ,such as config_ori.txt,config_ori_s.txt
	cp.configFile2vec(config_infile);
	cp.configVec2parsed();
	vec_config_parsed_tmp = cp.vec_config_parsed;//parsed config vector,use in this main function
	//

	////
	//
	//Graph graph(peNums + leNums + seNums + fgNums);
	//vector<pair<int, int>> edge = graph.edgeConstruct(vec_config_parsed_tmp);
	//for (vector<pair<int,int>>::iterator it = edge.begin();it != edge.end();it++)
	//{
	//	graph.addEdge((*it).first, (*it).second);
	//}
	//graph.topological_sort();
	//


	//find fanout for each PE port
	pe_port_fanout_collect();
	
	//
	int idx_config;
	for (unsigned int i = 0; i < vec_config_parsed_tmp.size(); i++)
	{
		idx_config = vec_config_parsed_tmp[i][1];
		if (vec_config_parsed_tmp[i][0] == 8)//import PE'S config
		{			
			pe[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 9)//import KE'S config
		{
			le[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 0)//import SE'S config
		{
			se[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		//import FG'S config
		else if(vec_config_parsed_tmp[i][0] == 1)//lbegin												 
		{
			lbegin[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 2)//lend												 
		{
			lend[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 3)//join												 
		{
			join[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 4)//switch												 
		{
			switch_[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 5)//break												 
		{
			break_[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 6)//lends												 
		{
			lends[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if (vec_config_parsed_tmp[i][0] == 7)//ta												 
		{
			ta[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		else if(vec_config_parsed_tmp[i][0] == 10)//joinbp
		{ 
			joinbp[idx_config]->config_reg.push(vec_config_parsed_tmp[i]);
		}
		cout << endl;
		cout << endl;
		cout << endl;

	}

	//parameter import,only for PE
	ifstream para_file;
	para_file.open(argv[2]);//argument files path,such as parameter_file.txt
	ParaParse paraparse;
	paraparse.parsePara(para_file);
	vector<int> v_tmp;
	int pe_idx;
	for (unsigned int i = 0; i < paraparse.para_parsed.size(); i++)
	{
		v_tmp = paraparse.para_parsed[i];
		pe_idx = v_tmp[0];
		pe[pe_idx]->loc_reg = v_tmp[1];	
		pe[pe_idx]->loc_reg_v = 1;
	}


	//extract execute order info from config file

	//decide similating order

	//start simulation
	//ofstream outfile("debug.txt");
	
	while(1)
	{
		outfile << "------------" << endl;
		outfile << "clock--" << cnt <<"|||||" << endl;
		outfile << "------------" << endl;
		outfile2 << "====CLOCK-" << cnt << "======================================================================================" << endl;
		//traverse vector for sim
		for (int i = vec_config_parsed_tmp.size() - 1; i >= 0; i--)//int i = vec_config_parsed_tmp.size()-1;i>=0; i--)
		{
			//PE sim-ing
			if (vec_config_parsed_tmp[i][0] == 8)
			{
				outfile << "                " << endl;
				outfile << "Processing PE......" << endl;
				PeSimProcess(pe[vec_config_parsed_tmp[i][1]]);
				//for debug
				outfile2 << "PE[" << vec_config_parsed_tmp[i][1] << "]中间值1" << endl;
				outfile2 << setw(15) << "ib1_out_t" << setw(15) << "ib1_out_v" << setw(15) << "ib1_out" << setw(15) << "ib2_out_t" << setw(15) << "ib2_out_v"
					<< setw(15) << "ib2_out" << setw(15) << "ib3_out_t" << setw(15) << "ib3_out_v" << setw(15) << "ib3_out" << endl;
				outfile2 << setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer1_out_tag << setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer1_out_v 
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer1_out << setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer2_out_tag 
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer2_out_v << setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer2_out 
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer3_out_tag << setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer3_out_v 
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->inbuffer3_out << endl;
				outfile2 << "PE[" << vec_config_parsed_tmp[i][1] << "]中间值2" << endl;
				outfile2 << setw(15) << "alu_out_v" << setw(15) << "alu_out" << setw(15) << "alu_out_b_v" << setw(15) << "alu_out_b" << endl;
				outfile2 << setw(15) << pe[vec_config_parsed_tmp[i][1]]->alu_out_v << setw(15) << pe[vec_config_parsed_tmp[i][1]]->alu_out 
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->alu_out_b_v << setw(15) << pe[vec_config_parsed_tmp[i][1]]->alu_out_b << endl;
				outfile2 << "CLOCK" << cnt << "-PE[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "dout1_t" << setw(15) << "dout1_v" << setw(15) << "dout1" << setw(15) << "dout2_t" << setw(15) << "dout2_v"
					<< setw(15) << "dout" << setw(15) << "bout_t" << setw(15) << "bout_v" << setw(15) << "bout" << endl;
				outfile2 << setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout1_tag << setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout1_v
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout1 << setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout2_tag
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout2_v << setw(15) << pe[vec_config_parsed_tmp[i][1]]->dout2
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->bout_tag << setw(15) << pe[vec_config_parsed_tmp[i][1]]->bout_v
					<< setw(15) << pe[vec_config_parsed_tmp[i][1]]->bout << endl;
				outfile << "CLOCK" << cnt << "-PE" << vec_config_parsed_tmp[i][1] << endl;
				outfile << "----------------------------------------------------------------" << endl;
			}
			//LE sim-ing
			else if (vec_config_parsed_tmp[i][0] == 9)
			{
				outfile << "                " << endl;
				outfile << "Processing LE......" << endl;

				LeSimProcess(le[vec_config_parsed_tmp[i][1]],lsunit);
				//for debug
				outfile2 << "CLOCK" << cnt << "-LE[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "data_out_t" << setw(15) << "data_out_v" << setw(15) << "data_out" << endl;
				outfile2 << setw(15) << le[vec_config_parsed_tmp[i][1]]->data_out_tag << setw(15) << le[vec_config_parsed_tmp[i][1]]->data_out_v 
					<< setw(15) << le[vec_config_parsed_tmp[i][1]]->data_out << endl;
				outfile << "CLOCK" << cnt << "-LE" << vec_config_parsed_tmp[i][1] << endl;
			}
			//SE sim-ing
			else if (vec_config_parsed_tmp[i][0] == 0)
			{
				outfile << "                " << endl;
				outfile << "Processing SE......" << endl;
				SeSimProcess(se[vec_config_parsed_tmp[i][1]],lsunit);
				//for debug
				outfile2 << "CLOCK" << cnt << "-SE[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "out4end_v" << setw(15) << "out4end" << endl;
				outfile2 << setw(15) << se[vec_config_parsed_tmp[i][1]]->se_extra_out_for_end_v << setw(15) << se[vec_config_parsed_tmp[i][1]]->se_extra_out_for_end << endl;
				outfile << "CLOCK" << cnt << "-SE" << vec_config_parsed_tmp[i][1] << endl;
			}
			//FG
			else if (vec_config_parsed_tmp[i][0] == 1)//lbegin
			{
				outfile << "                " << endl;
				outfile << "Processing lbegin......" << endl;
				LbeginSimProcess(lbegin[vec_config_parsed_tmp[i][1]]);
				//for debug
				outfile2 << "CLOCK" << cnt << "-lbegin[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "out_v" << setw(15) << "out" << endl;
				outfile2 << setw(15) << lbegin[vec_config_parsed_tmp[i][1]]->out_v << setw(15) << lbegin[vec_config_parsed_tmp[i][1]]->out << endl;
			}
			else if (vec_config_parsed_tmp[i][0] == 2)//lend
			{
				outfile << "                " << endl;
				outfile << "Processing lend......" << endl;
				LendSimProcess(lend[vec_config_parsed_tmp[i][1]]);
				//for debug
				outfile2 << "CLOCK" << cnt << "-lend[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "out2back" << setw(15) << "out2end" << endl;
				outfile2 << setw(15) << lend[vec_config_parsed_tmp[i][1]]->out2back << setw(15) << lend[vec_config_parsed_tmp[i][1]]->out2end << endl;
			}
			else if (vec_config_parsed_tmp[i][0] == 3)//join
			{
				outfile << "                " << endl;
				outfile << "Processing join......" << endl;
				JoinSimProcess(join[vec_config_parsed_tmp[i][1]]);
			}
			else if (vec_config_parsed_tmp[i][0] == 4)//switch
			{
				outfile << "                " << endl;
				outfile << "Processing switch......" << endl;
				SwitchSimProcess(switch_[vec_config_parsed_tmp[i][1]]);
			}
			else if (vec_config_parsed_tmp[i][0] == 5)//break
			{
				outfile << "                " << endl;
				outfile << "Processing break......" << endl;
				BreakSimProcess(break_[vec_config_parsed_tmp[i][1]]);
			}
			else if (vec_config_parsed_tmp[i][0] == 6)//lends
			{
				outfile << "                " << endl;
				outfile << "Processing lends......" << endl;
				LendsSimProcess(lends[vec_config_parsed_tmp[i][1]]);
			}
			else if (vec_config_parsed_tmp[i][0] == 10)//joinbp
			{
				outfile << "                " << endl;
				outfile << "Processing joinbp......" << endl;
				JoinBpSimProcess(joinbp[vec_config_parsed_tmp[i][1]]);
			}
			//TA sim-ing
			else if (vec_config_parsed_tmp[i][0] == 7)//ta
			{
				outfile << "                " << endl;
				outfile << "Processing TA......" << endl;
				TaSimProcess(ta[vec_config_parsed_tmp[i][1]]);
				//for debug
				outfile2 << "CLOCK" << cnt << "-TA[" << vec_config_parsed_tmp[i][1] << "]输出值" << endl;
				outfile2 << setw(15) << "out_tag" << setw(15) << "out_v" << setw(15) << "out" << endl;
				outfile2 << setw(15) << ta[vec_config_parsed_tmp[i][1]]->out_tag << setw(15) << ta[vec_config_parsed_tmp[i][1]]->out_v 
					<< setw(15) << ta[vec_config_parsed_tmp[i][1]]->out << endl;
			}		
			
		}
		//memmory update
		lsunit->update();
		
		if (cnt == 0)
		{
			begin_signal = 0;
		}
		
		//for debug
		//----------------------------------------

		//ATTENTION! lend0 and lend1 can both be the end nodes in different situations
		uint lend_end_index = vec_config_parsed_tmp[vec_config_parsed_tmp.size() - 1][1];
		end = lend[lend_end_index]->out2end;

		if (end)
			break;
		if (cnt == 50)
			break;

		cnt++;
	}
	//ALU clock cycle print 
	outfile << "||||||||||||||||||||||||||" << endl;
	outfile << "PE alu clock cycle" << endl;
	outfile << cnt << endl;

	//int cycle_max = 0;
	//int	cycle_tmp;
	//for (vector<vector<int>>::size_type i_ = 0; i_ < vec_config_parsed_tmp.size(); i_++)
	//{				
	//	if (vec_config_parsed_tmp[i_][0] == 8)//pe
	//	{
	//		cycle_tmp = pe[vec_config_parsed_tmp[i_][1]]->cycle;
	//		outfile << "pe[" << vec_config_parsed_tmp[i_][1] << "] ALUÔËÐÐÁ¿»¯Ê±ÖÓÊýÊÇ£º " << cycle_tmp << endl;
	//		outfile << " " << endl;
	//		if (cycle_max < cycle_tmp)
	//		{
	//			cycle_max = cycle_tmp;
	//		}
	//	}		
	//}
	ofstream ofile("memoryOutFile.txt");
	memory2.writeToFile(ofile);

	system("pause");
	return 0;
}
