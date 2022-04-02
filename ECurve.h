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

//�����������ʽ
int gcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return gcd(y, x%y);
}

//��÷�ĸ��Ԫ(��չŷ�����)
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

	void showEpab();					//��ʾѭ��ȺԪ��

	int unEqLamda(point P, point Q);	//����P������Qʱ��Lamda

	int equalLamda(point P);		    //����P����Qʱ��Lamda

	point PplusQ(point P, point Q);     //����P+Q

	point kP(int k,point P);            //����kP 

	int getOrd(point P);				//���Ԫ�صĽ�


	vector<int> EncodeMsg(int key, point A_Q, point B_Q, string message);//�����ļ���
	string DcodeMsg(int key, vector<int> secret);                        //�����Ľ���

private:
	int p, a, b;

};

ECurve::ECurve(int p1, int a1, int b1) :p(p1), a(a1), b(b1) {}


void ECurve::showEpab()
{
	int n = 0;//�洢������ѭ��ȺԪ�ظ���
	unsigned long long z;

	for (int x = 1; x < p; x++)
	{
		z = pow(x,3)+ a * x + b;
		if (z >= p)    //ģpƽ��ʣ��
		{
			for (int y = 1; y < p; y++)
			{
				if (((y*y) % p) == (z % p))   //�������һ��ѭ��ȺԪ��
				{
					cout << "(" << x << "," << y << ") ";
					n += 1;
				}
			}	
		}
	}
	cout << endl << "������ѭ��ȺԪ�ظ���:" << n << endl;
}

int ECurve::unEqLamda(point P, point Q) {

	long int up = ((Q.y - P.y) % p + p) % p, down = ((Q.x - P.x) % p + p) % p;//���ӡ���ĸ

	//�����Ӻͷ�ĸ��Ϊ���
	long int gcd_value = gcd(up, down);
	up = int(up / gcd_value);
	down = int(down / gcd_value);
	
	//���ĸ����Ԫ
	long int inverse_value = get_inverse_element(down, p);
	long long int lamda = (up*inverse_value);//���lamda

	return lamda;
}

int ECurve::equalLamda(point P) {

	long int up = ((3 * P.x * P.x + a) % p + p) % p, down = ((2 * P.y) % p + p) % p;//���ӡ���ĸ
	
	//�����Ӻͷ�ĸ��Ϊ���
	long int gcd_value = gcd(up, down);
	up = int(up / gcd_value);
	down = int(down / gcd_value);

	//���ĸ����Ԫ
	long int inverse_value = get_inverse_element(down, p);
	long long int lamda = (up*inverse_value);//���lamda

	return lamda;
}



point ECurve::PplusQ(point P , point Q )
{
	point temp;

	if ((P.x == 0 && P.y == 0) || (Q.x == 0 && Q.y == 0))   //PΪO or QΪO  ��������ط�����һ��
		if (P.x == 0)
			temp.x = Q.x, temp.y = Q.y;
		else
			temp.x = P.x, temp.y = P.y;
	else if (P.x == Q.x&&P.y == p - Q.y)					//PΪQ�ļӷ���Ԫ�����Ϊ����Զ��(0,0)
	{
		temp.x = 0;
		temp.y = 0;
		return temp;
	}
	else
	{												//P��Q����ΪOʱ�ҷǼӷ���Ԫ
		long long int lamda;
		if (P.x == Q.x && P.y == Q.y)				//P and Q ������
			lamda = equalLamda(P);
		else										//P and Q �����
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
		temp = PplusQ(P, P);           //k��P���
		for (; k > 2; k--)
		{
			temp = PplusQ(temp, P);
		}
	}

	return temp;
}

int ECurve::getOrd(point P)        //��Ԫ�صĽ�
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

//�����ļ���
vector<int> ECurve::EncodeMsg(int A_key, point P, point B_Q, string message)
{
	vector<int> secretMsg;    //����
	
	point C1;//A�Ĺ�Կ
	C1 = kP(A_key, P);
	secretMsg.push_back(C1.x);
	secretMsg.push_back(C1.y);
	
	point kQ;
	kQ = kP(A_key, B_Q);

	unsigned long int C2;
	for (int i = 0; i < message.length(); i++)		//������ַ��������
	{
		C2 = (int)message[i] + kQ.x;
		secretMsg.push_back(C2);
	}
	return secretMsg;
}

//�����Ľ���
string ECurve::DcodeMsg(int B_key, vector<int> secret)
{
	string Dmessage="";        //����

	point C1;
	C1.x = secret[0];
	C1.y = secret[1];

	point xC1;
	xC1 = kP(B_key, C1);

	int num;
	for (int i = 2; i < secret.size(); i++)          //��������ֽ��ܱ���
	{
		num = secret[i] - xC1.x;
		Dmessage += (char)num;
	}
	return Dmessage;
}