#include"ECurve.h"



namespace myspace
{
	void test_one()
	{
		/*int p, a, b;
		while (1)
		{
			cout << "����p(����):";
			cin >> p;
			cout << "����a:";
			cin >> a;
			cout << "����b:";
			cin >> b;
			if ((4 * (a*a*a) + 27 * (b*b)) % p == 0)
				cout << "ѡȡ����Բ���߲������ڼ��ܣ�������ѡ��\n";
			else
				break;
		}*/
		int p = 11, a = 1, b = 6;
		//int p = 2833, a = 1, b = 1;
		ECurve C(p, a, b);
		C.showEpab();

		cout << "������ѭ��Ⱥ��ѡ��һ����P��Ϊ����Ԫ:";
		point P;
		cin >> P.x >> P.y;
		//P.x = 289;
		//P.y = 1897;
		//int n;
		//n = C.getOrd(P);
		//cout << "����ԪP�Ľ�Ϊ��" << n<<endl;

		int B_private_key;
		cout << "����B��˽Կ:";
		cin >> B_private_key;
		point B_Q;
		B_Q = C.kP(B_private_key, P);
		cout <<"������ԪP("<<P.x<<","<<P.y<<"),˽Կ:"<< B_private_key <<"������B�Ĺ�ԿQ("<<B_Q.x<<","<<B_Q.y<<")"<<endl;
		
		
		cout << endl << "===========A���B�Ĺ�Կ����B������Ϣ==========="<<endl;
		cout << "����A��˽Կ��";
		int A_private_key;
		cin >> A_private_key;
		point A_Q;//A�Ĺ�Կ
		A_Q = C.kP(A_private_key, P);

		cout << "��������:";
		string A_Msg;
		cin >> A_Msg;

		vector<int> A_EncodeMsg;//���ļ���
		A_EncodeMsg = C.EncodeMsg(A_private_key, P, A_Q, B_Q, A_Msg);
		cout << "A���ܺ󽫣�";
		for (int i = 0; i < A_EncodeMsg.size(); i++)
		{
			cout << A_EncodeMsg[i]<<"-";
		}
		cout << "���͸�B" << endl;


		cout << endl << "===========B����==========="<< endl;
		int mykey;
		while (1)
		{
			cout << "����B��˽Կ��";
			cin>>mykey;
			string B_DecodeMsg;
			B_DecodeMsg = C.DcodeMsg(mykey, P, A_Q, B_Q, A_EncodeMsg);
			cout << "B���ܺ�";
			cout << B_DecodeMsg;
		}
		
		
		

	}
	
	
	
	
	//
	void test_four()
	{
		string str= "abc";
		string str2;
		str2 += 32;
		int num = 3;
		for (int i = 0; i < str2.length(); i++)
		{
			cout << (int)(str2[i]*num) << "-";
		}
	}
}
	

int main()
{
	myspace::test_one();

	//myspace::test_four();
	return 0;
}