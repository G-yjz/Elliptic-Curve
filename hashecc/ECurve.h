#pragma once
#include <iostream>
#include<cmath>
#include<vector>
#include<string>
#include <cstdlib>
#include <ctime>
#include"hash.h"

using namespace std;

struct point {

	long int x;
	long int y;

	point(long int x1 = 0, long int y1 = 0) :x(x1), y(y1) {}

	friend inline bool operator == (const point& P, const point& Q) {
		return (P.x == Q.x&&P.y == Q.y);//记得加friend,以外部函数的方式调用
	}
};

class ECurve{
public:
	ECurve(int p1=0, int a1=0, int b1=0) : p(p1), a(a1), b(b1) {}//构造函数
	ECurve(const ECurve& C);//拷贝构造
	ECurve& operator=(const ECurve& C);//拷贝赋值
	~ECurve(){}//析构函数

	void showEpab();					//显示循环群元素

	int unEqLamda(point P, point Q);	//计算P不等于Q时的Lamda

	int equalLamda(point P);		    //计算P等于Q时的Lamda

	point PplusQ(point P, point Q);     //计算P+Q

	point kP(int k,point P);            //计算kP 

	int getOrd(point P);				//求该元素的阶

	vector<int> EncodeMsg(int key, point A_Q, point B_Q, string message);//对明文加密
	string DcodeMsg(int key, vector<int> secret);                        //对密文解密

	vector<int> sign(const char* msg, int A_private_key, point P, int n);//签名
	bool verify(const char* msg, vector<int> sig, point P, int n);//对签名验证

private:
	int p, a, b;//构建循环群的参数

};

//ECurve::ECurve(int p1, int a1, int b1) :p(p1), a(a1), b(b1) {}
inline ECurve::ECurve(const ECurve& C) {
	p = C.p;
	a = C.a;
	b = C.b;
}
inline ECurve& ECurve::operator=(const ECurve& C) {
	p = C.p;
	a = C.a;
	b = C.b;
	return *this;
}

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
		if (P==Q)				//P and Q 相等情况
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

vector<int> ECurve::sign(const char* msg, int A_private_key, point P, int n)
{
	point A_Q;
	A_Q = kP(A_private_key, P);

	int d = rand() % (n - 2 + 1) + 1;//随机数[1,n)
	point K;
	K = kP(d, P);
	int r = K.x%n;

	int e;
	e = myhash(msg);

	int inv_d = get_inverse_element(d, n);
	int s = (inv_d*(e + A_private_key * r)) % n;

	vector<int> temp;
	temp.push_back(A_Q.x);
	temp.push_back(A_Q.y);
	temp.push_back(r);
	temp.push_back(s);

	return temp;
}

bool ECurve::verify(const char* msg, vector<int> sig, point P, int n)
{
	point Q;
	Q.x = sig[0];
	Q.y = sig[1];
	int r = sig[2];
	int s = sig[3];

	if ((r <= 0 && r >= n)|| (s <= 0 && s >= n))
		return false;

	int inv_s = get_inverse_element(s, n);
	int w = inv_s % n;
	int e = myhash(msg);

	int u1 = (e * w) % n;
	int u2 = (r * w) % n;

	point temp, temp1, temp2;
	temp1 = kP(u1, P);
	temp2 = kP(u2, Q);
	temp = PplusQ(temp1, temp2);
	int v = temp.x%n;

	return v == r;

}