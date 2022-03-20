#pragma once
#include <iostream>
#include<cmath>
#include<vector>

using namespace std;

class ECurve {
public:
	ECurve(int p1, int a1, int b1);

	void showEpab();								//显示循环群元素

	int unEqLamda(int x1, int y1, int x2, int y2);	//计算P不等于Q时的Lamda

	int equalLamda(int x1, int y1);					//计算P等于Q时的Lamda

	void PplusQ(int x1, int y1, int x2, int y2, int &x, int &y);  //计算P+Q

	void kP(int k,int x1, int y1, int &x, int &y);                //计算kP 

	vector<int> vx;        //存储循环群所有元素的x值
	vector<int> vy;        //存储循环群所有元素的y值
	
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
		if (z >= p)    //模p平方剩余
		{
			for (y = 0; y < p; y++)
				if (((y*y) % p) == z % p)   //成立求得一个循环群元素
				{
					cout << "(" << x << "," << y << ") ";
					vx.push_back(x);        //存储当前元素的x值
					vy.push_back(y);        //存储当前元素的y值
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
	if ((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))   //P为O or Q为O  情况
		if (x1 == 0)
			x = x2, y = y2;
		else
			x = x1, y = y1;
	else
	{												//P，Q都不为O时
		int lamda;
		if (x1 == x2 && y1 == y2)					//P and Q 相等情况
			lamda = equalLamda(x1, y1);
		else										//P and Q 不相等
			lamda = unEqLamda(x1, y1, x2, y2);
		x = ((lamda * lamda - x1 - x2) % p + p) % p;
		y = ((lamda * (x1 - x) - y1) % p + p) % p;
	}
	
	bool isO = true;									//P+Q是否是无穷远点
	int n;
	for (n = 0; n < vx.size(); n++)
	{
		if ((x == (vx[n])) && (y == (vy[n])))	//若当前x,y值存在于循环群列表中(该表不包含0，0)，则不是无穷远点
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
		PplusQ(x1, y1, x1, y1, x, y);            //k个P相加
		for (; k > 2; k--)
		{
			tx = x, ty = y;
			PplusQ(tx, ty, x1, y1, x, y);
		}
	}
}