//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "XImage.h"
#include "Region_8.h"

using namespace std;

//* ��ͨ�����ı��
int ** CRegion_8::ScanSign(int **pdata, int imgrow, int imgcol)
{
	int **matrix_new = new int *[imgrow];//�洢��Ǻ������
	for (int i = 0; i < imgrow; i++)
	{
		matrix_new[i] = new int[imgcol];
	}
	//��ʼ��0��
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			matrix_new[i][j] = 0;
		}
	}

	//ɨ��ͼ��Ѱ�Ұ����򣬲��������
	for (int i = 0; i < imgrow; i++)//ɨ��һ��
	{
		for (int j = 0; j< imgcol; j++)//ɨ��һ��
		{
			//�ж��Ƿ�ΪĿ������
			//�ҵ�Ŀ�����أ�������Ϊ����
			if (pdata[i][j] == 1)
			{
				//�����Ե���أ����������ϵ�����
				//�󶥵������
				if (i == 0 && j == 0)
				{
					//�½�һ�����򣬽������ص������ͨ���򣬲������¾�����ͨ����ı�Ǻ�·��
					conregion_num++;
					ConReg *con_region = new ConReg;
					(*con_region).label =conregion_num;//label���ڵ�����
					(*con_region).label_num = (*con_region).label_num + 1;
					//·��
					int *region_route = new int[2];
					region_route[0] = i;
					region_route[1] = j;
					(*con_region).route_list.push_back(region_route);
					matrix_new[i][j] = (*con_region).label;
					conregion_list.push_back(con_region);
				}
				//��0�е�����
				else if (i == 0 && j > 0)
				{
					//�ж���ߵ����Ƿ�Ϊ1,���Ϊ1������ߵı�ǩ��������أ�ͬʱ�����е���Ŀ��1��·���м�������
					if (pdata[i][j - 1] == 1)
					{
						matrix_new[i][j] = matrix_new[i][j - 1];
						int templabel = matrix_new[i][j];//��Ԫ��ֵ������Ǳ�ţ�����1�洢λ��Ϊ0������2�洢Ϊ1��������
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
					}
					else
					{
						conregion_num++;
						//Ҫʵ�����ṹ�壬����ָ��ָ��
						ConReg *con_region = new ConReg;
						//.�����ó�Ա������������ṹ��
						//����vector�е�Ϊ�ṹ��ָ�룬����ʹ��->����ȻҲ����ʹ��**��.
						(*con_region).label = conregion_num;//��ʱ�ı�ǩӦ����ǰ������еı�ǩ��1��������Ϊ��������Ŀ+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}
				//��0��
				else if (i > 0 && j == 0)
				{
					if (pdata[i - 1][j + 1] == 1)
					{
						matrix_new[i][j] = matrix_new[i - 1][j + 1];
						int templabel = matrix_new[i][j];
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
						continue;
					}
					else if (pdata[i - 1][j] == 1)
					{
						matrix_new[i][j] = matrix_new[i - 1][j];
						int templabel = matrix_new[i][j];
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
						continue;
					}
					else
					{
						conregion_num++;
						ConReg *con_region = new ConReg;
						(*con_region).label = conregion_num;//��ʱ�ı�ǩӦ����ǰ������еı�ǩ��1��������Ϊ��������Ŀ+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}
				//���һ��
				else if (j == imgcol && i>0)
				{
					//��
					if (pdata[i - 1][j] == 1)
					{
						matrix_new[i][j] = matrix_new[i - 1][j];
						int templabel = matrix_new[i][j];
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
						continue;
					}
					//����
					if (pdata[i - 1][j - 1] == 1)
					{
						matrix_new[i][j] = matrix_new[i - 1][j - 1];
						int templabel = matrix_new[i][j];
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
						continue;
					}
					//��
					if (pdata[i][j - 1] == 1)//
					{
						matrix_new[i][j] = matrix_new[i][j - 1];
						int templabel = matrix_new[i][j];
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
						continue;
					}
					else
					{
						conregion_num++;
						ConReg *con_region = new ConReg;
						(*con_region).label = conregion_num;//��ʱ�ı�ǩӦ����ǰ������еı�ǩ��1��������Ϊ��������Ŀ+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}

				//��Ϊ��Ե���أ��������ϣ��ϣ����ϣ����ĸ���
				else
				{
					//��Χ�ĸ��㶼��Ϊ1
					if (pdata[i - 1][j + 1] != 1 && pdata[i - 1][j] != 1 && pdata[i - 1][j - 1] != 1 && pdata[i][j - 1] != 1)
					{
						//�������ص������ͨ���򣬲����±��
						conregion_num++;
						ConReg *con_region = new ConReg;
						(*con_region).label = conregion_num;
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
					else//˵��������һ����������ͨ����������һ��Ϊ1
					{
						//������ϵ�����ϵ㶼Ϊ1����ȡ����֮��Ľ�Сֵ,�����ϴ�ֵ��Ϊ��Сֵ
						//��ʱ��һ�����⣬���������������ͨ������������ӦҲ�޸�Ϊ��Сֵ
						if (pdata[i - 1][j - 1] == 1 && pdata[i - 1][j + 1]==1)
						{
							int templabel = 0;
							int originlabel = 0;
							//���������ȣ���ȡ����һ��
							//������߲��ȣ���ȡС���Ǹ�����������Ǹ�ֵ������ͨ�����ڵ�ֵȫ����ΪС��ֵ
							if (matrix_new[i - 1][j + 1]==matrix_new[i - 1][j - 1])
							{
								matrix_new[i][j] = matrix_new[i - 1][j + 1];
								templabel = matrix_new[i][j];
							}
							else if (matrix_new[i - 1][j + 1]<matrix_new[i - 1][j - 1])
							{
								matrix_new[i][j] = matrix_new[i - 1][j + 1];
								templabel = matrix_new[i][j];
								originlabel = matrix_new[i - 1][j - 1];
								//ԭʼ��ǩ������������е����е�
								for (int r = 0; r < conregion_list[originlabel - 1]->label_num; r++)
								{
									int rrow = conregion_list[originlabel - 1]->route_list[r][0];
									int rcol = conregion_list[originlabel - 1]->route_list[r][1];
									matrix_new[rrow][rcol] = templabel;
								}
							}
							else
							{
								matrix_new[i][j] = matrix_new[i - 1][j - 1];
								templabel = matrix_new[i][j];
								originlabel = matrix_new[i - 1][j + 1];
								for (int r = 0; r < conregion_list[originlabel - 1]->label_num; r++)
								{
									int rrow = conregion_list[originlabel - 1]->route_list[r][0];
									int rcol = conregion_list[originlabel - 1]->route_list[r][1];
									matrix_new[rrow][rcol] = templabel;
								}
							}
							//matrix_new[i][j] = min(matrix_new[i - 1][j + 1], matrix_new[i - 1][j - 1]);//ȡСֵ
							//�½�С����ͨ���������ؼ�1
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}

						//����������ϵ㶼Ϊ1
						if (pdata[i][j - 1] == 1 && pdata[i - 1][j + 1] == 1)
						{
							int templabel = 0;
							int originlabel = 0;
							if (matrix_new[i - 1][j + 1]==matrix_new[i][j - 1])
							{
								matrix_new[i][j] = matrix_new[i - 1][j + 1];
								templabel = matrix_new[i][j];
							}
							else if (matrix_new[i - 1][j + 1]<matrix_new[i][j - 1])
							{
								matrix_new[i][j] = matrix_new[i - 1][j + 1];
								templabel = matrix_new[i][j];
								originlabel = matrix_new[i][j - 1];
								for (int r = 0; r < conregion_list[originlabel - 1]->label_num; r++)
								{
									int rrow = conregion_list[originlabel - 1]->route_list[r][0];
									int rcol = conregion_list[originlabel - 1]->route_list[r][1];
									matrix_new[rrow][rcol] = templabel;
								}
							}
							else
							{
								matrix_new[i][j] = matrix_new[i][j - 1];
								templabel = matrix_new[i][j];
								originlabel = matrix_new[i - 1][j + 1];
								for (int r = 0; r < conregion_list[originlabel - 1]->label_num; r++)
								{
									int rrow = conregion_list[originlabel - 1]->route_list[r][0];
									int rcol = conregion_list[originlabel - 1]->route_list[r][1];
									matrix_new[rrow][rcol] = templabel;
								}
							}
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}

						// �����ϵ�Ϊ1,˵����ǰ������ϵ��ֵ��ͬ
						if (pdata[i - 1][j + 1] == 1)
						{
							matrix_new[i][j] = matrix_new[i - 1][j + 1];
							int templabel = matrix_new[i][j];
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}

						if (pdata[i - 1][j] == 1)
						{
							matrix_new[i][j] = matrix_new[i - 1][j];
							int templabel = matrix_new[i][j];
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}

						if (pdata[i - 1][j - 1] == 1)
						{
							matrix_new[i][j] = matrix_new[i - 1][j - 1];
							int templabel = matrix_new[i][j];
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}
						if (pdata[i][j - 1] == 1)
						{
							matrix_new[i][j] = matrix_new[i][j - 1];
							int templabel = matrix_new[i][j];
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}
					}
				}
			}
		}
	}
	return matrix_new;//���ر�Ǻ������
}


//*ϸСĿ����޳�
//���ڳ������ԣ�ֻ�д������ˮ����ڿ��Ƿ�Χ֮�ڣ������С��ˮ��߽磬��������֣���ʹ������֣�Ҳ����Ϊ���������ĸ���Ʒ��
//�Գ���������Ӱ�첻��
int **CRegion_8::RemoveSmall(int **pdata, int imgrow, int imgcol)
{
	//vector<int> re_labelist;//��¼��Ҫ�Ƴ�����ı�ǩ�б�
	//������ͨ����������Ŀ<100�ģ����ò��������ֵȫ����ֵΪ0
	for (int i = 0; i < conregion_list.size(); i++)
	{
		if (conregion_list[i]->label_num < 10000)
		{
			for (int j = 0; j < conregion_list[i]->route_list.size(); j++)
			{
				int row = conregion_list[i]->route_list[j][0];//���µ���к�
				int col = conregion_list[i]->route_list[j][1];//���µ���к�
				pdata[row][col] = 0;
			}
		}
	}

	////������ͨ����������Ŀ<100�ģ����ò��������ֵȫ����ֵΪ0
	//for (int i = 0; i < conregion_list.size(); i++)
	//{
	//	if (conregion_list[i]->label_num < 100)
	//		re_labelist.push_back(conregion_list[i]->label);
	//}
	///*�ҳ����������ǩֵ��ͬ�����ݣ���Ϊ0*/
	////�˴��������ʽ��������޸�
	//for (int i = 0; i < imgrow; i++)
	//{
	//	for (int j = 0; j < imgcol; j++)
	//	{
	//		for (int k = 0; k < re_labelist.size(); k++)
	//		{
	//			if (pdata[i][j] == re_labelist[k])
	//				pdata[i][j] = 0;
	//		}
	//	}
	//}

	//���������������ǩ��0�����ݣ�����Ϊ1
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			if (pdata[i][j]>0)
				pdata[i][j] = 1;
		}
	}
	return pdata;
}


