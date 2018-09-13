#pragma once
#include "processingElement.h"
#include "load.h"
#include "store.h"
#include "fineGrain.h"
#include "tagAttach.h"
#include <fstream>
#include <map>
#include <iomanip>
#include "LSUnit.h"


using namespace std;
//using namespace DRAMSim;
//namespace DRAMSim
//{
//	class LSUnit;
//}
using DRAMSim::LSUnit;
using HGRA::Load;
using HGRA::Store;
//using LSUnit;
extern bool begin_signal;
extern ProcessingElement ** pe;
extern Load** le;
extern Store** se;
//extern LSUnit* lsunit;
extern LoopBegin** lbegin;
extern LoopEnd** lend ;
extern Switch** switch_;
extern Join** join;
extern JoinBp** joinbp;
extern Break** break_ ;
extern LoopEnds** lends;
extern TagAttach** ta ;
//extern TagIssue* tagissue;
extern MemoryInt memory;
extern MemoryInt memory2;//д�����memory
extern bool begin_signal;
extern ofstream outfile;
extern ofstream outfile2;
extern vector<vector<int>> vec_config_parsed_tmp;
extern vector<vector<int>> port_fanout;

void PeSimProcess(ProcessingElement* pe_current);//index ��vec_config_parsed������ֵ��������ʾ��ǰ����ľ������  transmit bypass taģʽû��123������ֱ�����
void LeSimProcess(Load* le_current, LSUnit* lsunit);
void SeSimProcess(Store* se_current,LSUnit* lsunit);
//Finegrained
void LbeginSimProcess(LoopBegin* lbegin_current);
void LendSimProcess(LoopEnd* lend_current);
void JoinSimProcess(Join* join_current);
void JoinBpSimProcess(JoinBp* joinbp_current);
void SwitchSimProcess(Switch* switch_current);
void BreakSimProcess(Break* break_current);
void LendsSimProcess(LoopEnds* lends_current);
void TaSimProcess(TagAttach* ta_current);
//for tag
void pe_sim_step1(ProcessingElement* pe_current);   //��PE���������   ��̬ʱ�������tagֱ���õ�ob��tag�ϣ� ���ܴ�������
void pe_sim_step2(ProcessingElement* pe_current);   //������ƥ����ɵ����ݷ���alu����������table��Ӧ�У�lr��from alu��ִ��
void pe_sim_step3(ProcessingElement* pe_current);   //����ob,ob������->ob�������PE�����  ��̬ʱ��tag��step1��ֱ�ӷŵ���ob��
void pe_sim_step1_mux(ProcessingElement* pe_current);
void pe_sim_step2_mux(ProcessingElement* pe_current);
void pe_sim_step3_mux(ProcessingElement* pe_current);
//for no tag
void pe_sim_step1_no_tag(ProcessingElement* pe_current);//ֻ��Լ���ģʽ
void pe_sim_step2_no_tag(ProcessingElement* pe_current);//ֻ��Լ���ģʽ   local_reg THRESHOLD
void pe_sim_step3_no_tag(ProcessingElement* pe_current);//ֻ��Լ���ģʽ

//void le_sim_step1(Load* le_current);
//void le_sim_step2(Load* le_current);

//void se_sim_step1(Store* se_current);
//void se_sim_step2(Store* se_current);


//find fanout for each PE port
void port_fanout_collect();
