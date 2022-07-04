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


	void test_five()
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

		cout << endl << "===========A���B�Ĺ�Կ����B������Ϣ===========" << endl;
		cout << "����A��˽Կ��";
		int A_private_key;
		cin >> A_private_key;

		cout << "��������:";
		string A_Msg;
		cin >> A_Msg;
	}

	void test_myhash()
	{
		const char* text = "asd";
		int num = myhash(text);
		cout << num;
	}

	void sign_verify()
	{
		int p = 2833, a = 1, b = 1;

		ECurve C(p, a, b);
		point P;
		P.x = 1341;
		P.y = 854;
		int n = C.getOrd(P);

		cout << "===========sign_verify()===========" << endl;
		cout << "����A��˽Կ��";
		int A_private_key;
		cin >> A_private_key;

		const char* msg = "this is an important message";
		const char* msg2 = "thix is an important message";

		vector<int> sig;
		sig = C.sign(msg, A_private_key, P, n);

		bool test;
		
		test = C.verify(msg2, sig, P, n);
		cout << test;
	}

}
	

int main()
{
	//myspace::test_one();       //���ܽ���
	//myspace::test_two();       //��Ԫ�صĽ�
	//myspace::test_three();     //��P+Q�Ľ��
	//myspace::test_four();      //��kP
	//myspace::test_five();
	//myspace::test_myhash();
	myspace::sign_verify();    //˽Կ�������һ�������޸�msg��msg2��������ͬΪ1����ͬΪ0
	return 0;
}