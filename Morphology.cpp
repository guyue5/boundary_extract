//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "XImage.h"
#include "Morphology.h"


using namespace std;


bool CMorphology::And(int ci, int cj, int** pmatrix)
{
	//wrow��wcol����ֱ��ʹ��
	bool a = true;
	for (int irow = -(wrow - 1) / 2; irow < (wrow - 1) / 2; irow++)
	{
		for (int jcol = -(wcol - 1) / 2; jcol < (wcol - 1) / 2; jcol++)
		{
			if (cell[((wrow - 1) / 2 + irow)][((wcol - 1) / 2 + jcol)] * 255 == 255)//��������
			{
				if (pmatrix[ci + irow][cj + jcol] * 255 != 255)
					return false;
					
			}
		}
	}
	return true;
}

bool CMorphology::Or(int ci, int cj, int** pmatrix)
{
	for (int irow = -(wrow - 1) / 2; irow < (wrow - 1) / 2; irow++)
	{
		for (int jcol = -(wcol - 1) / 2; jcol < (wcol - 1) / 2; jcol++)
		{
			if (cell[((wrow - 1) / 2 + irow)][((wcol - 1) / 2 + jcol)] * 255 == 255)//��������
			{
				if (pmatrix[ci + irow][cj + jcol]*255 == 255)
					return true;
			}
		}
	}
	return false;
}

int ** CMorphology::Corrosion(int** pmatrix, int imgrow, int imgcol)//��ʴ����Ե���ز�����
{
	int** matrix_new = new int* [imgrow];//�洢���Ƕ�ά���飬����ʴ֮����µ�ͼ�����飬�������ж������ֱ������ʲ��ø��ֶ��巽ʽ
	for (int i = 0; i < imgrow; i++)
	{
		cout << i << endl;
		matrix_new[i] = new int[imgcol];
	}
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			matrix_new[i][j] = pmatrix[i][j];
		}
	}
	for (int i = (wrow - 1) / 2; i < imgrow - (wrow - 1) / 2; i++)
	{
		for (int j = (wcol - 1) / 2; j < imgcol - (wcol - 1) / 2; j++)
		{
			if (And(i, j, pmatrix))
				matrix_new[i][j] = 1;
			else
				matrix_new[i][j] = 0;
		}
	}
	return matrix_new;
}
int ** CMorphology::Expand(int** pmatrix, int imgrow, int imgcol)
{
	int** matrix_new = new int*[imgrow];
	for (int i = 0; i < imgrow; i++)
	{
		matrix_new[i] = new int[imgcol];
	}
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			matrix_new[i][j] = pmatrix[i][j];
		}
	}
	for (int i = (wrow - 1) / 2; i < imgrow - (wrow - 1) / 2; i++)
	{
		for (int j = (wcol - 1) / 2; j < imgcol - (wcol - 1) / 2; j++)
		{
			if (Or(i, j, pmatrix))
				matrix_new[i][j] = 1;
			else
				matrix_new[i][j] = 0;
		}
	}
	return matrix_new;
}

int ** CMorphology::Close(int** pmatrix,int imgrow, int imgcol,int num)//�����㣬�����ͣ���ʴ�����׶�
{
	int ** expand_matrix = Expand(pmatrix,imgrow,imgcol);
	//int ** expand_matrix2 = Expand(expand_matrix, imgrow, imgcol);
	int ** close_matrix = Corrosion(expand_matrix,imgrow,imgcol);
	//int ** close_matrix2 = Corrosion(close_matrix, imgrow, imgcol);
	return close_matrix;
}

int ** CMorphology::Open(int** pmatrix, int imgrow, int imgcol, int num)//�����㣬�����ͣ���ʴ�����׶�
{
	int ** close_matrix = Corrosion(pmatrix, imgrow, imgcol);
	//int ** close_matrix2 = Corrosion(close_matrix, imgrow, imgcol);
	int ** expand_matrix = Expand(close_matrix, imgrow, imgcol);
	//int ** expand_matrix2 = Expand(expand_matrix, imgrow, imgcol);
	return expand_matrix;
}

int ** CMorphology::GetBound(int **pmatrix, int imgrow, int imgcol)
{
	int num = 0;
	int ** expand_matrix = Expand(pmatrix, imgrow, imgcol);
	int ** corrssion_matrix = Corrosion(pmatrix, imgrow, imgcol);
	for (int i = 0; i < imgrow; i++)
	{
		for (int j = 0; j < imgcol; j++)
		{
			pmatrix[i][j] = expand_matrix[i][j] - corrssion_matrix[i][j];
			if (pmatrix[i][j] == 1)
				num++;
		}
	}
	return pmatrix;
}