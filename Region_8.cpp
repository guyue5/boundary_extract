//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "XImage.h"
#include "Region_8.h"

using namespace std;

//* 连通分量的标记
int ** CRegion_8::ScanSign(int **pdata, int imgrow, int imgcol)
{
	int **matrix_new = new int *[imgrow];//存储标记后的数据
	for (int i = 0; i < imgrow; i++)
	{
		matrix_new[i] = new int[imgcol];
	}
	//初始化0阵
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			matrix_new[i][j] = 0;
		}
	}

	//扫描图像，寻找八邻域，并标记像素
	for (int i = 0; i < imgrow; i++)//扫描一行
	{
		for (int j = 0; j< imgcol; j++)//扫描一列
		{
			//判断是否为目标像素
			//找到目标像素，并以其为中心
			if (pdata[i][j] == 1)
			{
				//处理边缘像素，即四条边上的像素
				//左顶点的数据
				if (i == 0 && j == 0)
				{
					//新建一个区域，将该像素点加入连通区域，并更新新矩阵、连通区域的标记和路径
					conregion_num++;
					ConReg *con_region = new ConReg;
					(*con_region).label =conregion_num;//label是在递增的
					(*con_region).label_num = (*con_region).label_num + 1;
					//路径
					int *region_route = new int[2];
					region_route[0] = i;
					region_route[1] = j;
					(*con_region).route_list.push_back(region_route);
					matrix_new[i][j] = (*con_region).label;
					conregion_list.push_back(con_region);
				}
				//第0行的数据
				else if (i == 0 && j > 0)
				{
					//判断左边的数是否为1,如果为1，将左边的标签赋予该像素，同时区域中的数目加1，路径中加新坐标
					if (pdata[i][j - 1] == 1)
					{
						matrix_new[i][j] = matrix_new[i][j - 1];
						int templabel = matrix_new[i][j];//其元素值本身就是标号，区域1存储位置为0，区域2存储为1，。。。
						conregion_list[templabel - 1]->label_num++;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						conregion_list[templabel - 1]->route_list.push_back(region_route);
					}
					else
					{
						conregion_num++;
						//要实例化结构体，定义指针指向
						ConReg *con_region = new ConReg;
						//.是引用成员变量，代表其结构体
						//由于vector中的为结构体指针，所以使用->，当然也可以使用**加.
						(*con_region).label = conregion_num;//此时的标签应该是前面的已有的标签加1，可以认为是区域数目+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}
				//第0列
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
						(*con_region).label = conregion_num;//此时的标签应该是前面的已有的标签加1，可以认为是区域数目+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}
				//最后一列
				else if (j == imgcol && i>0)
				{
					//上
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
					//左上
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
					//左
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
						(*con_region).label = conregion_num;//此时的标签应该是前面的已有的标签加1，可以认为是区域数目+1
						(*con_region).label_num = (*con_region).label_num + 1;
						int *region_route = new int[2];
						region_route[0] = i;
						region_route[1] = j;
						(*con_region).route_list.push_back(region_route);
						matrix_new[i][j] = (*con_region).label;
						conregion_list.push_back(con_region);
					}
				}

				//不为边缘像素，存在右上，上，左上，左四个点
				else
				{
					//周围四个点都不为1
					if (pdata[i - 1][j + 1] != 1 && pdata[i - 1][j] != 1 && pdata[i - 1][j - 1] != 1 && pdata[i][j - 1] != 1)
					{
						//将该像素点加入连通区域，并更新标记
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
					else//说明至少有一个点与其连通，即至少有一点为1
					{
						//如果左上点和右上点都为1，则取两者之间的较小值,并将较大值改为较小值
						//此时有一个问题，就是与该数据相连通的其他区域理应也修改为较小值
						if (pdata[i - 1][j - 1] == 1 && pdata[i - 1][j + 1]==1)
						{
							int templabel = 0;
							int originlabel = 0;
							//如果两者相等，则取任意一个
							//如果两者不等，则取小的那个，并将大的那个值及其连通区域内的值全部改为小的值
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
								//原始标签所代表的区域中的所有点
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
							//matrix_new[i][j] = min(matrix_new[i - 1][j + 1], matrix_new[i - 1][j - 1]);//取小值
							//新较小的连通区域中像素加1
							conregion_list[templabel - 1]->label_num++;
							int *region_route = new int[2];
							region_route[0] = i;
							region_route[1] = j;
							conregion_list[templabel - 1]->route_list.push_back(region_route);
							continue;
						}

						//如果左点和右上点都为1
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

						// 若右上点为1,说明当前点和右上点的值相同
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
	return matrix_new;//返回标记后的数组
}


//*细小目标的剔除
//对于场景而言，只有大面积的水域才在考虑范围之内，如果很小的水域边界，可能是误分，即使不是误分，也是作为其他场景的附属品，
//对场景的整体影响不大
int **CRegion_8::RemoveSmall(int **pdata, int imgrow, int imgcol)
{
	//vector<int> re_labelist;//记录需要移除区域的标签列表
	//对于连通域内像素数目<100的，将该部分区域的值全部赋值为0
	for (int i = 0; i < conregion_list.size(); i++)
	{
		if (conregion_list[i]->label_num < 10000)
		{
			for (int j = 0; j < conregion_list[i]->route_list.size(); j++)
			{
				int row = conregion_list[i]->route_list[j][0];//存下点的行号
				int col = conregion_list[i]->route_list[j][1];//存下点的列号
				pdata[row][col] = 0;
			}
		}
	}

	////对于连通域内像素数目<100的，将该部分区域的值全部赋值为0
	//for (int i = 0; i < conregion_list.size(); i++)
	//{
	//	if (conregion_list[i]->label_num < 100)
	//		re_labelist.push_back(conregion_list[i]->label);
	//}
	///*找出数组中与标签值相同的数据，置为0*/
	////此处运行速率较慢，需修改
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

	//对于数组中其余标签非0的数据，都置为1
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


