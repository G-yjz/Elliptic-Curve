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

	void showEpab();								//��ʾѭ��ȺԪ��

	int unEqLamda(point P, point Q);	//����P������Qʱ��Lamda

	int equalLamda(point P);					//����P����Qʱ��Lamda

	point PplusQ(point P, point Q);  //����P+Q

	point kP(int k,point P);                //����kP 

	int getOrd(point P);


	vector<int> vx;        //�洢ѭ��Ⱥ����Ԫ�ص�xֵ
	vector<int> vy;        //�洢ѭ��Ⱥ����Ԫ�ص�yֵ

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

	if ((P.x == 0 && P.y == 0) || (Q.x == 0 && Q.y == 0))   //PΪO or QΪO  ���
		if (P.x == 0)
			temp.x = Q.x, temp.y = Q.y;
		else
			temp.x = P.x, temp.y = P.y;
	else
	{												//P��Q����ΪOʱ
		int lamda;
		if (P.x == Q.x && P.y == Q.y)					//P and Q ������
			lamda = equalLamda(P);
		else										//P and Q �����
			lamda = unEqLamda(P, Q);
		temp.x = ((lamda * lamda - P.x - Q.x) % p + p) % p;
		temp.y = ((lamda * (P.x - temp.x) - P.y) % p + p) % p;
	}
	
	bool isO = true;									//P+Q�Ƿ�������Զ��
	int n;
	for (n = 0; n < vx.size(); n++)
	{
		if ((temp.x == (vx[n])) && (temp.y == (vy[n])))	//����ǰx,yֵ������ѭ��Ⱥ�б���(�ñ�����0��0)����������Զ��
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
		temp = PplusQ(P, P);           //k��P���
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