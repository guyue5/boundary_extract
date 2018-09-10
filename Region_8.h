#include <list>
#include <vector>

typedef struct conregion  // ��ͨ����
{
	int label_num = 0;
	int label = 0;//������
	std::vector<int *> route_list;//�洢��ͨ�������
}ConReg;

typedef std::vector<ConReg*> ConReg_list;//���򼯺ϣ��䳤

class CRegion_8
{
public:
	int conregion_num = 0;//��ͨ������Ŀ
	ConReg_list conregion_list;
public:
	int **ScanSign(int **pdata, int imgrow, int imgcol); //��Ǻ���
	int **MergeRegion(int **pdata, int imgrow, int imgcol);//����ϲ�����
	int **RemoveSmall(int **pdata, int imgrow, int imgcol);//�Ƴ�С����
};

