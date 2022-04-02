#include"ECurve.h"

namespace myspace
{
	void test_one()
	{
		
		int p = 2833, a = 1, b = 1;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		P.x = 1341;
		P.y = 854;
		
		cout << "������ѭ��Ⱥ��ѡ��һ����P(" << P.x << "," << P.y << ")" << endl;

		int n = C.getOrd(P);
		cout << "����ԪP(" << P.x << "," << P.y << ")�Ľ�Ϊ��" << n << endl;


		int B_private_key;
		cout << "����B��˽Կ:";
		cin >> B_private_key;
		point B_Q;       //B�Ĺ�Կ
		B_Q = C.kP(B_private_key, P);
		cout <<"������ԪP("<<P.x<<","<<P.y<<"),˽Կ:"<< B_private_key <<"������B�Ĺ�ԿQ("<<B_Q.x<<","<<B_Q.y<<")"<<endl;
		
		
		cout << endl << "===========A���B�Ĺ�Կ����B������Ϣ==========="<<endl;
		cout << "����A��˽Կ��";
		int A_private_key;
		cin >> A_private_key;
		

		cout << "��������:";
		string A_Msg;
		cin >> A_Msg;

		vector<int> A_EncodeMsg;//���ļ���-����
		A_EncodeMsg = C.EncodeMsg(A_private_key, P, B_Q, A_Msg);
		cout << "A���ܺ󽫣�";
		for (int i = 0; i < A_EncodeMsg.size(); i++)
		{
			cout << A_EncodeMsg[i]<<"-";
		}
		cout << "���͸�B" << endl;


		cout << endl << "===========B����==========="<< endl;
		string B_DecodeMsg;//���Ľ���-����
		int mykey;
		while (1)
		{
			cout << "����B��˽Կ��";
			cin >> mykey;
			B_DecodeMsg = C.DcodeMsg(mykey, A_EncodeMsg);//��˽Կ����
			cout << "B���ܵõ����ģ�";
			cout << B_DecodeMsg;
			cout << endl;
		}
		
	}

	void test_two()   //��Ԫ�صĽ�
	{
		int p = 11, a = 1, b = 6;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		cout << "=========��Ԫ�صĽ�=========" << endl;
		while (1)
		{
			cout << "������ѭ��Ⱥ��ѡ��һ����P:";
			cin >> P.x >> P.y;
			int n = C.getOrd(P);
			cout << "����ԪP(" << P.x << "," << P.y << ")�Ľ�Ϊ��" << n << endl;
		}
		
	}

	void test_three() //��P+Q�Ľ��
	{
		int p = 11, a = 1, b = 6;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		P.x = 2;
		P.y = 7;
		cout << "=========��P+Q=========" << endl;
		while (1)
		{
			point Q;
			cout << "������ѭ��Ⱥ��ѡ��һ����Q:";
			cin >> Q.x >> Q.y;

			point T;
			T = C.PplusQ(P, Q);
			cout << "T: " << T.x << "," << T.y << endl;
		}
		
	}

	void test_four()//��kP
	{
		int p = 2833, a = 1, b = 1;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		P.x = 1341;
		P.y = 854;
		cout << "=========��kP=========" << endl;
		while (1)
		{
			int k;
			cout << "����k:";
			cin >> k;
			point temp;
			temp = C.kP(k, P);
			cout<< "temp: " << temp.x << "," << temp.y << endl;
		}
	}

	
}
	

int main()
{
	myspace::test_one();       //���ܽ���
	//myspace::test_two();       //��Ԫ�صĽ�
	//myspace::test_three();     //��P+Q�Ľ��
	//myspace::test_four();      //��kP

	return 0;
}