#include <list>
#include <vector>

typedef struct conregion  // 连通区域
{
	int label_num = 0;
	int label = 0;//区域标记
	std::vector<int *> route_list;//存储连通点的坐标
}ConReg;

typedef std::vector<ConReg*> ConReg_list;//区域集合，变长

class CRegion_8
{
public:
	int conregion_num = 0;//连通区域数目
	ConReg_list conregion_list;
public:
	int **ScanSign(int **pdata, int imgrow, int imgcol); //标记函数
	int **MergeRegion(int **pdata, int imgrow, int imgcol);//区域合并函数
	int **RemoveSmall(int **pdata, int imgrow, int imgcol);//移除小区域
};

