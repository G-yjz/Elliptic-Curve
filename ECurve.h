#pragma once
#include <iostream>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

struct point {
	int x;
	int y;
};


class ECurve {
public:
	ECurve(int p1, int a1, int b1);

	void showEpab();								//显示循环群元素

	int unEqLamda(point P, point Q);	//计算P不等于Q时的Lamda

	int equalLamda(point P);					//计算P等于Q时的Lamda

	point PplusQ(point P, point Q);  //计算P+Q

	point kP(int k,point P);                //计算kP 

	int getOrd(point P);


	vector<int> vx;        //存储循环群所有元素的x值
	vector<int> vy;        //存储循环群所有元素的y值

	//point ECodePoint(int key,point A_Q,point B_Q);
	//point DCodePoint(point m,int kb);
	vector<int> EncodeMsg(int key, point P, point A_Q, point B_Q, string message);
	string DcodeMsg(int key, point P, point A_Q, point B_Q, vector<int> secret);

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

int ECurve::unEqLamda(point P, point Q) {

	int up = ((Q.y - P.y) % p + p) % p, down = ((Q.x - P.x) % p + p) % p;
	int temp = pow(down, p - 2);
	return ((up*temp) % p + p) % p;
}

int ECurve::equalLamda(point P) {

	int up = ((3 * P.x * P.x + a) % p + p) % p, down = ((2 * P.y) % p + p) % p;
	int temp = pow(down, p - 2);
	return ((up*temp) % p + p) % p;
}



point ECurve::PplusQ(point P , point Q )
{
	point temp;

	if ((P.x == 0 && P.y == 0) || (Q.x == 0 && Q.y == 0))   //P为O or Q为O  情况
		if (P.x == 0)
			temp.x = Q.x, temp.y = Q.y;
		else
			temp.x = P.x, temp.y = P.y;
	else
	{												//P，Q都不为O时
		int lamda;
		if (P.x == Q.x && P.y == Q.y)					//P and Q 相等情况
			lamda = equalLamda(P);
		else										//P and Q 不相等
			lamda = unEqLamda(P, Q);
		temp.x = ((lamda * lamda - P.x - Q.x) % p + p) % p;
		temp.y = ((lamda * (P.x - temp.x) - P.y) % p + p) % p;
	}
	
	bool isO = true;									//P+Q是否是无穷远点
	int n;
	for (n = 0; n < vx.size(); n++)
	{
		if ((temp.x == (vx[n])) && (temp.y == (vy[n])))	//若当前x,y值存在于循环群列表中(该表不包含0，0)，则不是无穷远点
		{
			isO = false;
			break;
		}
	}
	if(isO)
		temp.x = 0, temp.y = 0;
	return temp;
}

point ECurve::kP(int k, point P)
{
	point temp;
	
	if (k == 1)
		temp.x = P.x, temp.y = P.y;
	else
	{
		temp = PplusQ(P, P);           //k个P相加
		for (; k > 2; k--)
		{
			temp = PplusQ(temp, P);
		}
	}

	return temp;
}

int ECurve::getOrd(point P)
{
	int n = 1;
	point temp = P;
	while (1)
	{
		n += 1;
		temp = PplusQ(temp, P);
		if (temp.x == 0 && temp.y == 0)
			break;
	}
	return n;
}




vector<int> ECurve::EncodeMsg(int key, point P, point A_Q, point B_Q, string message)
{
	vector<int> secretMsg;
	int num;
	point temp;
	temp = kP(key, B_Q);
	if (temp.x == 0)
		temp = PplusQ(P, temp);
	for (int i = 0; i < message.length(); i++)
	{
		num = (int)message[i] * temp.x;
		secretMsg.push_back(num);
	}
	return secretMsg;
}
//
string ECurve::DcodeMsg(int key, point P, point A_Q, point B_Q, vector<int> secret)
{
	string Dmessage="";
	point temp;
	int num;
	temp = kP(key, A_Q);
	if (temp.x == 0)
		temp = PplusQ(P, temp);
	for (int i = 0; i < secret.size(); i++)
	{
		num = secret[i] / temp.x;
		Dmessage += (char)num;
	}
	return Dmessage;
}