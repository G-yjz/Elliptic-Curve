#include"ECurve.h"



namespace myspace
{
	void test_one()
	{
		/*int p, a, b;
		while (1)
		{
			cout << "输入p(素数):";
			cin >> p;
			cout << "输入a:";
			cin >> a;
			cout << "输入b:";
			cin >> b;
			if ((4 * (a*a*a) + 27 * (b*b)) % p == 0)
				cout << "选取的椭圆曲线不能用于加密，请重新选择\n";
			else
				break;
		}*/
		int p = 11, a = 1, b = 6;
		//int p = 2833, a = 1, b = 1;
		ECurve C(p, a, b);
		C.showEpab();

		cout << "在以上循环群中选出一个点P作为生成元:";
		point P;
		cin >> P.x >> P.y;
		//P.x = 289;
		//P.y = 1897;
		//int n;
		//n = C.getOrd(P);
		//cout << "生成元P的阶为：" << n<<endl;

		int B_private_key;
		cout << "输入B的私钥:";
		cin >> B_private_key;
		point B_Q;
		B_Q = C.kP(B_private_key, P);
		cout <<"由生成元P("<<P.x<<","<<P.y<<"),私钥:"<< B_private_key <<"，生成B的公钥Q("<<B_Q.x<<","<<B_Q.y<<")"<<endl;
		
		
		cout << endl << "===========A获得B的公钥，向B发送消息==========="<<endl;
		cout << "输入A的私钥：";
		int A_private_key;
		cin >> A_private_key;
		point A_Q;//A的公钥
		A_Q = C.kP(A_private_key, P);

		cout << "输入明文:";
		string A_Msg;
		cin >> A_Msg;

		vector<int> A_EncodeMsg;//明文加密
		A_EncodeMsg = C.EncodeMsg(A_private_key, P, A_Q, B_Q, A_Msg);
		cout << "A加密后将：";
		for (int i = 0; i < A_EncodeMsg.size(); i++)
		{
			cout << A_EncodeMsg[i]<<"-";
		}
		cout << "发送给B" << endl;


		cout << endl << "===========B解密==========="<< endl;
		int mykey;
		while (1)
		{
			cout << "输入B的私钥：";
			cin>>mykey;
			string B_DecodeMsg;
			B_DecodeMsg = C.DcodeMsg(mykey, P, A_Q, B_Q, A_EncodeMsg);
			cout << "B解密后：";
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