//���ļ��������ֳ�������Ҫ��ʼ������
//ÿһ�Ҫ�У��޸����뱣ֻ֤�޸����֣�����������Ŀ


//for no tag
#define outbuffer_depth 1		//outputBuffer�����
#define inbuffer_depth 1		//inBuffer�����
//for tag
#define outtablebuffer_depth 4	//outTableBuffer�����
#define intablebuffer_depth 4	//intablebuffer�����
//unit num
#define peNums 36				//PE����
#define leNums 7				//LE����
#define seNums 3				//SE����

#define lbeginNums 2			//loop begin����
#define lendNums 2				//loop end����
#define joinNums 0				//join�ڵ�����
#define switchNums 0				//switch�ڵ�����
#define breakNums 0				//break�ڵ�����
#define lendsNums 0				//loop end2�ڵ�����
#define joinbpNums 0			//joinbp�ڵ�����

#define taNums 0				//ta�ڵ������
#define fgNums (lbeginNums+lendNums+joinNums+switchNums+breakNums+lendsNums+joinbpNums)				//�ܵ�fg�ڵ������

#define unitTotalNums (peNums+leNums+seNums+fgNums+taNums)		//�ܵĵ�Ԫ����

#define joininportNums 2			//������ϸ����ģ�飨join�ڵ㣩������˿�����
#define memoryDepth 256			//������������memory�Ĵ�С
#define memory2depth 256			//�����������memory�Ĵ�С

//with memory or not
#define ATTACH_MEMORY 1			//���������ϻ��߲�����memory

//�ۼӼĴ����ı߽�ֵ
#define THRESHOLD 10