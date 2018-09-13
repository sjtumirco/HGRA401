#include "processingElement.h"


ProcessingElement::ProcessingElement():dout1_v(0),dout2_v(0),bout_v(0),loc_reg_v(0) {}
ProcessingElement::~ProcessingElement() {}
void ProcessingElement::ALU(int opcode, int in1, int in2 ,bool for_mux)//ALU��ΪMUX��ʱ��Ҫ��in3���źŶ�ֵ��Ϊ�������ݸ��ú���
{
	if (opcode == 8)//MUX
	{
		if (for_mux == 0)
		{
			alu_out = in2;
			alu_out_v = 1;
		}
		else if (for_mux == 1)
		{
			alu_out = in1;
			alu_out_v = 1;
		}
		else
		{
		}
	}
	else
	{
		switch (opcode)
		{
		case 0:
			break;

		case 1://signed add
			alu_out = in1 + in2;
			alu_out_v = 1;
			break;

		case 2://signed mul
			alu_out = in1 * in2;
			alu_out_v = 1;
			break;
		case 3://sub
			alu_out = in1 - in2;
			alu_out_v = 1;
			break;

		case 5://mod
			alu_out = in1 % in2;
			alu_out_v = 1;
			break;

		case 6: //�ж�������Ĵ�С
			alu_out_b = in1 < in2 ? 1 : 0;
			alu_out_b_v = 1;
			break;
		case  7:
			alu_out = in1 == in2 ? 1 : 0;//�����С��ֵ
			alu_out_v = 1;
			break;
		case 8:

			break;

		case 9://MAC
			alu_out = in1 * in2 + loc_reg;
			alu_out_v = 1;
		}
	}
	
	alu_ack();
	

}

bool ProcessingElement::tableBuffer_fifo_full1()
{
	if (tableBuffer_fifo1.size() < intablebuffer_depth)
		return 0;
	else if (tableBuffer_fifo1.size() == intablebuffer_depth)
		return 1;
}

bool ProcessingElement::tableBuffer_fifo_full2()
{
	if (tableBuffer_fifo2.size() < intablebuffer_depth)
		return 0;
	else if (tableBuffer_fifo2.size() == intablebuffer_depth)
		return 1;
}

void ProcessingElement::peExportCtr1()
{
	if (!bp1)
	{
		outBuffer1.dataOut();
		dout1 = outBuffer1.out;
		dout1_v = 1;
	}
	else
	{
		dout1_v = 0;
	}
	
}
void ProcessingElement::peExportCtr2()
{
	

	if (!bp2)
	{
		outBuffer2.dataOut();
		dout2 = outBuffer2.out;
		dout2_v = 1;

	}
	else
		dout2_v = 0;
}

void ProcessingElement::peInportCtr1()
{	//in1 data get into the buffer1
	inBuffer1.in = din1;
	inBuffer1.in_v = din1_v;
	inBuffer1.dataIn();

}
void ProcessingElement::peInportCtr2()
{
	//in2 data get into the buffer2
	inBuffer2.in = din2;
	inBuffer2.in_v = din2_v;
	inBuffer2.dataIn();
}

//void ProcessingElement::peInportCtr()
//{	//in data get into the buffer class 
//	inBuffer.in1 = din1;
//	inBuffer.in1_v = din1_v;
//	inBuffer.in1_t = din1_tag;
//	inBuffer.in2 = din2;
//	inBuffer.in2_v = din2_v;
//	inBuffer.in2_t = din2_tag;
//	inBuffer.in3 = bin;
//	inBuffer.in3_v = bin_v;
//	inBuffer.in3_t = bin_tag;
//
//	inBuffer.dataIn();
//	
//}


void ProcessingElement::inBufferOutCtr1()
{
	if (inBuffer1.inputBuffer.size() != 0)//��֤inputBuffer������ʱ���ǿյ�
	{				
		inBuffer1.dataOut();
		inbuffer1_out = inBuffer1.out;		
	}
	else
		cout << "inputBuffer1�ǿյ�" << endl;

	

}

void ProcessingElement::inBufferOutCtr2()
{
	if (inBuffer2.inputBuffer.size() != 0)//��֤inputBuffer������ʱ���ǿյ�
	{		
		inBuffer2.dataOut();
		inbuffer2_out = inBuffer2.out;		
	}
	else
		cout << "inputBuffer2�ǿյ�" << endl;
	

}

void ProcessingElement::outBuffer1In()
{
	outBuffer1.in = outbuffer1_in;
	outBuffer1.dataIn();
}
void ProcessingElement::outBuffer2In()
{
	outBuffer2.in = outbuffer2_in;
	outBuffer2.dataIn();
}

void ProcessingElement::cycle_alu(int opcode)
{
	if (opcode == 2 || opcode == 9)//�˷��ͳ��ۼ���Ҫ����ʱ������
	{
		cycle += 2;
	}
	else
		cycle++;
}
void ProcessingElement::cycle_entryLogic()
{
	cycle++;
}

void ProcessingElement::cycle_outLogic()
{
	cycle++;
}

void ProcessingElement::alu_ack()
{
	if (ack_outbuffer12alu | ack_outbuffer22alu)
	{
		ack_alu2in1 = 1; ack_alu2in2 = 1;
	}
	
}

//buffer
//for tag operate
//InTableBuffer::InTableBuffer() {}
InTableBuffer::InTableBuffer(const int bufDpth) :bp2lastPe_1(0), bp2lastPe_2(0), bp2lastPe_3(0),last_tag_1(16),last_tag_2(16),last_tag_3(16)
{
	InTableBufferEntity.resize(intablebuffer_depth); /*line_ready_order.resize(intablebuffer_depth);*/
}
InTableBuffer::~InTableBuffer() {}

bool InTableBuffer::isDin1BufferReady(short& in1_tag)
{
	//table���Ƿ���ͬ��tag���Ƿ����ˣ��Ƿ�����������ͬһ��tag����ʹ�øú����ķ���ֵ��ʾ,��bp2lastPe
	if (in1_tag == last_tag_1)
	{
		bp2lastPe_1 = 0;
		return bp2lastPe_1;
	}
	bool interspace = 0, same_tag = 0;
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in1_tag & InTableBufferEntity[i].valid1 == 0)//tag match and valid1 == 0
		{
			interspace = 1;
			break;
		}
		else if (InTableBufferEntity[i].tag != in1_tag & InTableBufferEntity[i].valid1 == 0 & InTableBufferEntity[i].valid2 == 0 & InTableBufferEntity[i].valid3 == 0 & InTableBufferEntity[i].tag == 0)   //?
		{
			interspace = 1;
			break;
		}		
		else
		{
			continue;
		}
		//interspace = 0;
	}
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in1_tag && InTableBufferEntity[i].valid1 == 1)
		{
			same_tag = 1;
			break;
		}
		else
		{
			continue;
		}
		//same_tag = 0;
	}

	if (interspace & !same_tag)//buffer���п�λ����ͬ��tag
	{
		bp2lastPe_1 = 1;
	}
	else
	{
		bp2lastPe_1 = 0;
	}
	return bp2lastPe_1;
}

bool InTableBuffer::isDin2BufferReady(short& in2_tag)
{
	if (in2_tag == last_tag_2)
	{
		bp2lastPe_2 = 0;
		return bp2lastPe_2;
	}
	bool interspace=0, same_tag=0;
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in2_tag & InTableBufferEntity[i].valid2 == 0)//tag match and valid1 == 0
		{
			interspace = 1;
			break;
		}
		else if (InTableBufferEntity[i].tag != in2_tag & InTableBufferEntity[i].valid2 == 0 & InTableBufferEntity[i].valid3 == 0 & InTableBufferEntity[i].valid1 == 0 & InTableBufferEntity[i].tag == 0)
		{
			interspace = 1;
			break;
		}
		else
		{
			continue;
		}
		//interspace = 0;
	}
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in2_tag && InTableBufferEntity[i].valid2 == 1)
		{
			same_tag = 1;
			break;
		}
		else
		{
			continue;
		}
		//same_tag = 0;
	}

	if (interspace & !same_tag)//buffer���п�λ����ͬ��tag
	{
		bp2lastPe_2 = 1;
	}
	else
	{
		bp2lastPe_2 = 0;
	}
	return bp2lastPe_2;
}

bool InTableBuffer::isBinBufferReady(short& in3_tag)
{
	if (in3_tag == last_tag_3)
	{
		bp2lastPe_3 = 0;
		return bp2lastPe_3;
	}
	bool interspace=0, same_tag=0;
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in3_tag & InTableBufferEntity[i].valid3 == 0)//tag match and valid1 == 0
		{
			interspace = 1;
			break;
		}
		else if (InTableBufferEntity[i].tag != in3_tag & InTableBufferEntity[i].valid3 == 0 & InTableBufferEntity[i].valid1 == 0 & InTableBufferEntity[i].valid2 == 0 & InTableBufferEntity[i].tag == 0)
		{
			interspace = 1;
			break;
		}
		else
		{
			continue;
		}
		//interspace = 0;
	}
	for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
	{
		if (InTableBufferEntity[i].tag == in3_tag && InTableBufferEntity[i].valid3 == 1)
		{
			same_tag = 1;
			break;
		}
		else
		{
			continue;
		}
		same_tag = 0;
	}

	if (interspace & !same_tag)//buffer���п�λ����ͬ��tag
	{
		bp2lastPe_3 = 1;
	}
	else
	{
		bp2lastPe_3 = 0;
	}
	return bp2lastPe_3;
}

bool InTableBuffer::line_ok(vector<TableLine>::size_type i,ProcessingElement* pe)
{
	if (!flag_reg1 & !flag_reg2 & !flag_reg3)//000
	{
		return 0;
	}
	else if (!flag_reg1 & !flag_reg2 & flag_reg3)//001
	{
		if (InTableBufferEntity[i].valid3)
		{
			return 1;
		}
		else
			return 0;
	}
	else if (!flag_reg1 & flag_reg2 & !flag_reg3)//010
	{
		if (InTableBufferEntity[i].valid2)
		{
			return 1;
		}
		else
			return 0;
	}
	else if (!flag_reg1 & flag_reg2 & flag_reg3)//011
	{
		if (pe->config_reg.front()[2] == 8)//MUX����
		{
			if (InTableBufferEntity[i].valid3 & !InTableBufferEntity[i].data3)// valid3=1;data3=0,ѡ��in2
			{
				if (InTableBufferEntity[i].valid2)
				{
					return 1;
				}
				else
					return 0;
			}			
			else
				return 0;
		}
		else
		{
			if (InTableBufferEntity[i].valid2 & InTableBufferEntity[i].valid3)
			{
				return 1;
			}
			else
				return 0;
		}
		
	}
	else if (flag_reg1 & !flag_reg2 & !flag_reg3)//100
	{
		if (InTableBufferEntity[i].valid1)
			return 1;
		else
			return 0;
	}
	else if (flag_reg1 & !flag_reg2 & flag_reg3)//101
	{
		if (pe->config_reg.front()[2] == 8)//MUX����
		{
			
			if (InTableBufferEntity[i].valid3 & InTableBufferEntity[i].data3)//valid3=1;data3=1,ѡ��in1
			{
				if (InTableBufferEntity[i].valid1)
				{
					return 1;
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else
		{
			if (InTableBufferEntity[i].valid1 & InTableBufferEntity[i].valid3)
				return 1;
			else
				return 0;
		}
		
	}
	else if (flag_reg1 & flag_reg2 & !flag_reg3)//110
	{
		if (InTableBufferEntity[i].valid1 & InTableBufferEntity[i].valid2)
			return 1;
		else
			return 0;
	}
	else if (flag_reg1 & flag_reg2 & flag_reg3)//111
	{
		if (pe->config_reg.front()[2] == 8)//MUX����
		{

			if (InTableBufferEntity[i].valid3 & !InTableBufferEntity[i].data3)//valid3=1;data3=0,ѡ��in2
			{
				if (InTableBufferEntity[i].valid2)
				{
					return 1;
				}
				else
					return 0;
			}
			else if (InTableBufferEntity[i].valid3 & InTableBufferEntity[i].data3)//valid3=1;data3=1,ѡ��in1
			{
				if (InTableBufferEntity[i].valid1)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}
		else
		{
			if (InTableBufferEntity[i].valid1 & InTableBufferEntity[i].valid2 & InTableBufferEntity[i].valid3)
				return 1;
			else
				return 0;
		}
		
	}
}

void InTableBuffer::dataIn(ProcessingElement* pe)
{
	//ack clear before op
	pe->ack2in1port = 0;                 //?
	pe->ack2in2port = 0;
	pe->ack2in3port = 0;

	//check flag_reg,3steps to simulate
	flag_reg1 = pe->config_reg.front()[20];    //pefield14
	flag_reg2 = pe->config_reg.front()[21];
	flag_reg3 = pe->config_reg.front()[22];
	if (flag_reg1)//in1portû������
	{
		bool match = 0;
		if (pe->din1_v)//��һ��PE������request����
		{
			bool ready1 = isDin1BufferReady(pe->din1_tag);   //inbuffer�п�����ͬ��tag
			pe->ack2in1port = pe->inTableBuffer.bp2lastPe_1;
			if (ready1)//buffer���Խ�������
			{
				pe->ack2in1port = 1;
				//��ʼ�����Ķ����Դ�����ݲ��Ҽ�¼һ�´�����ݵ�bufferID��
				for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
				{
					if ((InTableBufferEntity[i].tag == pe->din1_tag) & ((InTableBufferEntity[i].valid2) | (InTableBufferEntity[i].valid3)))
					{
						//tagƥ�����ˣ��ų������������˿�����û�д洢��ȥ��tag��������ɵ�tag==0ƥ������					
						InTableBufferEntity[i].valid1 = 1;
						InTableBufferEntity[i].data1 = pe->din1;
						last_tag_1 = pe->din1_tag;
						InTableBufferEntity[i].line_ok = line_ok(i,pe);//���table���ǲ���׼������
						match = 1;
						if (InTableBufferEntity[i].line_ok)	//��׼���õ���ID�Ž�����
						{
							line_ready_order.push_back(i);
						}
						break;
					}
					else
					{
						continue;
					}
				}
				if (!match)
				{
					//table����һ��û��ƥ���tag,��tag�����ݲ�����п�λ
					for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
					{
						if (InTableBufferEntity[i].tag == 0 && InTableBufferEntity[i].valid2 == 0 && InTableBufferEntity[i].valid3 == 0 && InTableBufferEntity[i].valid1 == 0)
						{
							InTableBufferEntity[i].tag = pe->din1_tag;
							InTableBufferEntity[i].valid1 = 1;
							InTableBufferEntity[i].data1 = pe->din1;
							InTableBufferEntity[i].line_ok = line_ok(i, pe);//���table���ǲ���׼������
							last_tag_1 = pe->din1_tag;
							if (InTableBufferEntity[i].line_ok)	//��׼���õ���ID�Ž�����
							{
								line_ready_order.push_back(i);
							}
							break;
						}
					}
				}
				
				//�����һ��PE�˿��ϵ�����
			
			}
		}
	}

	if (flag_reg2)//in2portû������
	{
		bool match = 0;
		if (pe->din2_v)//���Ӹö˿ڵ���һ��PE������request����
		{
			bool ready2 = isDin2BufferReady(pe->din2_tag);
			pe->ack2in2port = pe->inTableBuffer.bp2lastPe_2;
			if (ready2)//buffer���Խ�������
			{
				pe->ack2in2port = 1;
				//��ʼ�����Ķ����Դ�����ݲ��Ҽ�¼һ�´�����ݵ�bufferID��
				for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
				{
					if ((InTableBufferEntity[i].tag == pe->din2_tag) & ((InTableBufferEntity[i].valid1) | (InTableBufferEntity[i].valid3)))
					{
						//tagƥ�����ˣ��ų��˺����������˿�����û�д洢��ȥ������tag��������ɵ�tag==0ƥ������					
						InTableBufferEntity[i].valid2 = 1;
						InTableBufferEntity[i].data2 = pe->din2;
						last_tag_2 = pe->din2_tag;
						InTableBufferEntity[i].line_ok = line_ok(i,pe);//���table���ǲ���׼������
						match = 1;
						if (InTableBufferEntity[i].line_ok)	//��׼���õ���ID�Ž�����
						{
							line_ready_order.push_back(i);
						}
						break;
					}
					else
					{
						continue;
					}
				}
				if (!match)
				{
					//table����һ��û��ƥ���tag,��tag�����ݲ�����п�λ
					for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
					{
						if (InTableBufferEntity[i].tag == 0 && InTableBufferEntity[i].valid1 == 0 && InTableBufferEntity[i].valid2 == 0 && InTableBufferEntity[i].valid3 == 0)
						{
							InTableBufferEntity[i].tag = pe->din2_tag;
							InTableBufferEntity[i].valid2 = 1;
							InTableBufferEntity[i].data2 = pe->din2;
							InTableBufferEntity[i].line_ok = line_ok(i, pe);//���table���ǲ���׼������
							last_tag_2 = pe->din2_tag;
							break;
							//��������²��ü�����Ƿ�OK����Ϊdin1�ǵ�һ�����뵽����е�����
						}
					}
				}
				
			}
		}
	}

	if (flag_reg3)//in3portû������
	{
		bool match = 0;
		if (pe->bin_v)//���Ӹö˿ڵ���һ��PE������request����
		{
			bool ready3 = isBinBufferReady(pe->bin_tag);
			pe->ack2in3port = pe->inTableBuffer.bp2lastPe_3;
			if (ready3)//buffer���Խ�������
			{
				pe->ack2in3port = 1;
				//��ʼ�����Ķ����Դ�����ݲ��Ҽ�¼һ�´�����ݵ�bufferID��
				for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
				{
					if ((InTableBufferEntity[i].tag == pe->bin_tag) & ((InTableBufferEntity[i].valid1) | (InTableBufferEntity[i].valid2)))
					{
						//tagƥ�����ˣ��ų��˺����������˿�����û�д洢��ȥ������tag��������ɵ�tag==0ƥ������					
						InTableBufferEntity[i].valid3 = 1;
						InTableBufferEntity[i].data3 = pe->bin;
						last_tag_3 = pe->bin_tag;
						InTableBufferEntity[i].line_ok = line_ok(i,pe);//���table���ǲ���׼������
						match = 1;
						if (InTableBufferEntity[i].line_ok)	//��׼���õ���ID�Ž�����
						{
							line_ready_order.push_back(i);
						}
						break;
					}
					else
					{
						continue;
					}
				}
				if (!match)
				{
					//table����һ��û��ƥ���tag,��tag�����ݲ�����п�λ
					for (vector<TableLine>::size_type i = 0; i < InTableBufferEntity.size(); i++)
					{
						if (InTableBufferEntity[i].tag == 0 && InTableBufferEntity[i].valid1 == 0 && InTableBufferEntity[i].valid2 == 0 && InTableBufferEntity[i].valid3 == 0)
						{
							InTableBufferEntity[i].tag = pe->bin_tag;
							InTableBufferEntity[i].valid3 = 1;
							InTableBufferEntity[i].data3 = pe->bin;
							InTableBufferEntity[i].line_ok = line_ok(i, pe);//���table���ǲ���׼������
							last_tag_3 = pe->bin_tag;
							break;
							//��������²��ü�����Ƿ�OK����Ϊdin1�ǵ�һ�����뵽����е�����
						}
					}
				}
				
			}
		}
	}
}

void InTableBuffer::dataOut(ProcessingElement* pe)
{
	list<unsigned int>::iterator i;
	for (i = line_ready_order.begin(); i != line_ready_order.end(); i++)
	{
		if (InTableBufferEntity[*i].line_ok)
		{
			//��ȥ����ǲ���ÿһ���˿ڶ��Ƿ����յ�״̬������inbuffer������Ч������Ҳ�ó�����ֻ������ʹ��
			pe->inbuffer1_out = InTableBufferEntity[*i].data1;             //*i��ʾ����line_ready_order[i]��*i��ʾ������ָ��Ķ���
			pe->inbuffer1_out_v = InTableBufferEntity[*i].valid1;
			pe->inbuffer1_out_tag = InTableBufferEntity[*i].tag;
			pe->inbuffer2_out = InTableBufferEntity[*i].data2;
			pe->inbuffer2_out_v = InTableBufferEntity[*i].valid2;
			pe->inbuffer2_out_tag = InTableBufferEntity[*i].tag;
			pe->inbuffer3_out = InTableBufferEntity[*i].data3;
			pe->inbuffer3_out_v = InTableBufferEntity[*i].valid3;
			pe->inbuffer3_out_tag = InTableBufferEntity[*i].tag;
			break;
		}
	}
}


void InTableBuffer::buffer_clear()
{
	if (!line_ready_order.empty())
	{
		int id = line_ready_order.front();
		InTableBufferEntity[id].tag = 0;
		InTableBufferEntity[id].valid1 = 0;
		InTableBufferEntity[id].data1 = 0;
		InTableBufferEntity[id].valid2 = 0;
		InTableBufferEntity[id].data2 = 0;
		InTableBufferEntity[id].valid3 = 0;
		InTableBufferEntity[id].data3 = 0;
		InTableBufferEntity[id].line_ok = 0;
		line_ready_order.pop_front();
	}

	
}
//definition of OutBuffer

//OutBuffer::OutBuffer() {}
OutTableBuffer::OutTableBuffer(const int bufDepth) { this->bufDepth = bufDepth; }
OutTableBuffer::~OutTableBuffer() {}

void OutTableBuffer::isOutBufferFull()
{
	if (outBuffer.size() < outtablebuffer_depth)
	{
		isOutBufFull = 0;

	}
	else
	{
		isOutBufFull = 1;

	}
}


void OutTableBuffer::dataIn()
{
	isOutBufferFull();
	if (!isOutBufFull)
	{
		inDataTmp.data = in;
		inDataTmp.tag = in_tag;
		inDataTmp.valid = in_v;
		outBuffer.push(inDataTmp);
		isDataInFinished = 1;
	}
	else
	{
		//std::cout << "OutBuffer if full1" << std::endl;
		isDataInFinished = 0;
	}
}

void OutTableBuffer::dataOut()
{

	if (!outBuffer.empty())
	{
		outDataTmp = outBuffer.front();
		out = outDataTmp.data;
		out_tag = outDataTmp.tag;
		out_v = outDataTmp.valid;
	}
}

void OutTableBuffer::buffer_clear()
{
	if (!outBuffer.empty())
	{
		outBuffer.pop();
	}	
}

void ProcessingElement::valid_clear(CLOCK port_idx)
{
	if (port_idx == 0)//port1
	{
		dout1_v = 0;
	}
	else if (port_idx == 1)//port2
	{
		dout2_v = 0;
	}
	else if (port_idx == 2)//port3
	{
		bout_v = 0;
	}
}