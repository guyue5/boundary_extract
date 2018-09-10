#include <string>

class CMorphology
{
public://��������
	int wrow;//ģ��Ŀ�
	int wcol;//ģ��ĳ�
	int **cell;//ģ��
public://��������
	//������ͼ��
	bool And(int ci, int cj, int** pmatrix);//ȡ�����㣬ciΪ���ĵ㣬pmatrixΪָ��ͼ�����ݵ�ָ��,��ͼ��Ϊ��ֵ��ͼ��
	int ** Corrosion(int** pmatrix, int imgrow, int imgcol);//��ʴ
	bool Or(int ci, int cj, int** pmatrix);//ȡ��
	int ** Expand(int** pmatrix, int imgrow, int imgcol);//����,numΪ�����ο�������
	int ** Close(int **pmatrix,int imgrow,int imgcol,int num);//�����㣬�����ͣ���ʴ�����׶�,ȥ����Χ����
	int ** Open(int **pmatrix, int imgrow, int imgcol, int num);//�����㣬�����ͣ���ʴ��ȥ���ڲ�������ϸС��
	int ** GetBound(int **pmatrix, int imgrow, int imgcol);//���ͺ��ͼ��-ԭʼͼ��
};

