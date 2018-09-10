#include <string>

class CMorphology
{
public://公共属性
	int wrow;//模板的宽
	int wcol;//模板的长
	int **cell;//模板
public://公共函数
	//单波段图像
	bool And(int ci, int cj, int** pmatrix);//取并运算，ci为中心点，pmatrix为指向图像数据的指针,该图像为二值化图像
	int ** Corrosion(int** pmatrix, int imgrow, int imgcol);//腐蚀
	bool Or(int ci, int cj, int** pmatrix);//取或
	int ** Expand(int** pmatrix, int imgrow, int imgcol);//膨胀,num为做几次开闭运算
	int ** Close(int **pmatrix,int imgrow,int imgcol,int num);//闭运算，先膨胀，后腐蚀，填充孔洞,去除周围噪声
	int ** Open(int **pmatrix, int imgrow, int imgcol, int num);//闭运算，先膨胀，后腐蚀，去除内部噪声，细小点
	int ** GetBound(int **pmatrix, int imgrow, int imgcol);//膨胀后的图像-原始图像
};

