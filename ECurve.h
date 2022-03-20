#pragma once
#include <iostream>
#include<cmath>
#include<vector>

using namespace std;

class ECurve {
public:
	ECurve(int p1, int a1, int b1);

	void showEpab();								//��ʾѭ��ȺԪ��

	int unEqLamda(int x1, int y1, int x2, int y2);	//����P������Qʱ��Lamda

	int equalLamda(int x1, int y1);					//����P����Qʱ��Lamda

	void PplusQ(int x1, int y1, int x2, int y2, int &x, int &y);  //����P+Q

	void kP(int k,int x1, int y1, int &x, int &y);                //����kP 

	vector<int> vx;        //�洢ѭ��Ⱥ����Ԫ�ص�xֵ
	vector<int> vy;        //�洢ѭ��Ⱥ����Ԫ�ص�yֵ
	
private:
	int p, a, b;

};

ECurve::ECurve(int p1, int a1, int b1) :p(p1), a(a1), b(b1) {}


void ECurve::showEpab()
{
	int x, y, z;
	for (x = 0; x < p; x++)
	{
		z = x * x * x + a * x + b;
		if (z >= p)    //ģpƽ��ʣ��
		{
			for (y = 0; y < p; y++)
				if (((y*y) % p) == z % p)   //�������һ��ѭ��ȺԪ��
				{
					cout << "(" << x << "," << y << ") ";
					vx.push_back(x);        //�洢��ǰԪ�ص�xֵ
					vy.push_back(y);        //�洢��ǰԪ�ص�yֵ
				}		
		}
	}
	cout << endl;
}

int ECurve::unEqLamda(int x1, int y1, int x2, int y2) {

	int up = ((y2 - y1) % p + p) % p, down = ((x2 - x1) % p + p) % p;
	int temp = pow(down, p - 2);
	return ((up*temp) % p + p) % p;
}

int ECurve::equalLamda(int x1, int y1) {

	int up = ((3 * x1 * x1 + a) % p + p) % p, down = ((2 * y1) % p + p) % p;
	int temp = pow(down, p - 2);
	return ((up*temp) % p + p) % p;
}



void ECurve::PplusQ(int x1, int y1, int x2, int y2, int &x, int &y)
{
	if ((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))   //PΪO or QΪO  ���
		if (x1 == 0)
			x = x2, y = y2;
		else
			x = x1, y = y1;
	else
	{												//P��Q����ΪOʱ
		int lamda;
		if (x1 == x2 && y1 == y2)					//P and Q ������
			lamda = equalLamda(x1, y1);
		else										//P and Q �����
			lamda = unEqLamda(x1, y1, x2, y2);
		x = ((lamda * lamda - x1 - x2) % p + p) % p;
		y = ((lamda * (x1 - x) - y1) % p + p) % p;
	}
	
	bool isO = true;									//P+Q�Ƿ�������Զ��
	int n;
	for (n = 0; n < vx.size(); n++)
	{
		if ((x == (vx[n])) && (y == (vy[n])))	//����ǰx,yֵ������ѭ��Ⱥ�б���(�ñ�����0��0)����������Զ��
		{
			isO = false;
			break;
		}
	}
	if(isO)
		x = 0, y = 0;
}

void ECurve::kP(int k, int x1, int y1, int &x, int &y)
{
	if (k == 1)
		x = x1, y = y1;
	else
	{
		int tx, ty;
		PplusQ(x1, y1, x1, y1, x, y);            //k��P���
		for (; k > 2; k--)
		{
			tx = x, ty = y;
			PplusQ(tx, ty, x1, y1, x, y);
		}
	}
}