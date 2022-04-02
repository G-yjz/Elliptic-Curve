#pragma once
#include <iostream>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

struct point {
	long int x;
	long int y;
};

//求两数最大公因式
int gcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return gcd(y, x%y);
}

//求得分母逆元(扩展欧几里得)
int get_inverse_element(int num, int p)
{
	for (int i = 1; i < p; i++)
	{
		if (((i*num) % p) == 1)
			return i;
	}
	return -1;
}

class ECurve {
public:
	ECurve(int p1, int a1, int b1);

	void showEpab();					//显示循环群元素

	int unEqLamda(point P, point Q);	//计算P不等于Q时的Lamda

	int equalLamda(point P);		    //计算P等于Q时的Lamda

	point PplusQ(point P, point Q);     //计算P+Q

	point kP(int k,point P);            //计算kP 

	int getOrd(point P);				//求该元素的阶


	vector<int> EncodeMsg(int key, point A_Q, point B_Q, string message);//对明文加密
	string DcodeMsg(int key, vector<int> secret);                        //对密文解密

private:
	int p, a, b;

};

ECurve::ECurve(int p1, int a1, int b1) :p(p1), a(a1), b(b1) {}


void ECurve::showEpab()
{
	int n = 0;//存储该曲线循环群元素个数
	unsigned long long z;

	for (int x = 1; x < p; x++)
	{
		z = pow(x,3)+ a * x + b;
		if (z >= p)    //模p平方剩余
		{
			for (int y = 1; y < p; y++)
			{
				if (((y*y) % p) == (z % p))   //成立求得一个循环群元素
				{
					cout << "(" << x << "," << y << ") ";
					n += 1;
				}
			}	
		}
	}
	cout << endl << "该曲线循环群元素个数:" << n << endl;
}

int ECurve::unEqLamda(point P, point Q) {

	long int up = ((Q.y - P.y) % p + p) % p, down = ((Q.x - P.x) % p + p) % p;//分子、分母

	//将分子和分母化为最简
	long int gcd_value = gcd(up, down);
	up = int(up / gcd_value);
	down = int(down / gcd_value);
	
	//求分母的逆元
	long int inverse_value = get_inverse_element(down, p);
	long long int lamda = (up*inverse_value);//求得lamda

	return lamda;
}

int ECurve::equalLamda(point P) {

	long int up = ((3 * P.x * P.x + a) % p + p) % p, down = ((2 * P.y) % p + p) % p;//分子、分母
	
	//将分子和分母化为最简
	long int gcd_value = gcd(up, down);
	up = int(up / gcd_value);
	down = int(down / gcd_value);

	//求分母的逆元
	long int inverse_value = get_inverse_element(down, p);
	long long int lamda = (up*inverse_value);//求得lamda

	return lamda;
}



point ECurve::PplusQ(point P , point Q )
{
	point temp;

	if ((P.x == 0 && P.y == 0) || (Q.x == 0 && Q.y == 0))   //P为O or Q为O  情况，返回非零那一个
		if (P.x == 0)
			temp.x = Q.x, temp.y = Q.y;
		else
			temp.x = P.x, temp.y = P.y;
	else if (P.x == Q.x&&P.y == p - Q.y)					//P为Q的加法逆元，相加为无穷远点(0,0)
	{
		temp.x = 0;
		temp.y = 0;
		return temp;
	}
	else
	{												//P，Q都不为O时且非加法逆元
		long long int lamda;
		if (P.x == Q.x && P.y == Q.y)				//P and Q 相等情况
			lamda = equalLamda(P);
		else										//P and Q 不相等
			lamda = unEqLamda(P, Q);

		temp.x = ((lamda * lamda - P.x - Q.x) % p +p) % p;
		temp.y = ((lamda * (P.x - temp.x) - P.y) % p + p) % p;

	}

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

int ECurve::getOrd(point P)        //求元素的阶
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

//对明文加密
vector<int> ECurve::EncodeMsg(int A_key, point P, point B_Q, string message)
{
	vector<int> secretMsg;    //密文
	
	point C1;//A的公钥
	C1 = kP(A_key, P);
	secretMsg.push_back(C1.x);
	secretMsg.push_back(C1.y);
	
	point kQ;
	kQ = kP(A_key, B_Q);

	unsigned long int C2;
	for (int i = 0; i < message.length(); i++)		//对逐个字符编码加密
	{
		C2 = (int)message[i] + kQ.x;
		secretMsg.push_back(C2);
	}
	return secretMsg;
}

//对密文解密
string ECurve::DcodeMsg(int B_key, vector<int> secret)
{
	string Dmessage="";        //明文

	point C1;
	C1.x = secret[0];
	C1.y = secret[1];

	point xC1;
	xC1 = kP(B_key, C1);

	int num;
	for (int i = 2; i < secret.size(); i++)          //对逐个数字解密编码
	{
		num = secret[i] - xC1.x;
		Dmessage += (char)num;
	}
	return Dmessage;
}