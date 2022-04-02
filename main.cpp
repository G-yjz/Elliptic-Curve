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
		
		cout << "在以上循环群中选出一个点P(" << P.x << "," << P.y << ")" << endl;

		int n = C.getOrd(P);
		cout << "生成元P(" << P.x << "," << P.y << ")的阶为：" << n << endl;


		int B_private_key;
		cout << "输入B的私钥:";
		cin >> B_private_key;
		point B_Q;       //B的公钥
		B_Q = C.kP(B_private_key, P);
		cout <<"由生成元P("<<P.x<<","<<P.y<<"),私钥:"<< B_private_key <<"，生成B的公钥Q("<<B_Q.x<<","<<B_Q.y<<")"<<endl;
		
		
		cout << endl << "===========A获得B的公钥，向B发送消息==========="<<endl;
		cout << "输入A的私钥：";
		int A_private_key;
		cin >> A_private_key;
		

		cout << "输入明文:";
		string A_Msg;
		cin >> A_Msg;

		vector<int> A_EncodeMsg;//明文加密-密文
		A_EncodeMsg = C.EncodeMsg(A_private_key, P, B_Q, A_Msg);
		cout << "A加密后将：";
		for (int i = 0; i < A_EncodeMsg.size(); i++)
		{
			cout << A_EncodeMsg[i]<<"-";
		}
		cout << "发送给B" << endl;


		cout << endl << "===========B解密==========="<< endl;
		string B_DecodeMsg;//密文解密-明文
		int mykey;
		while (1)
		{
			cout << "输入B的私钥：";
			cin >> mykey;
			B_DecodeMsg = C.DcodeMsg(mykey, A_EncodeMsg);//用私钥解密
			cout << "B解密得到明文：";
			cout << B_DecodeMsg;
			cout << endl;
		}
		
	}

	void test_two()   //求元素的阶
	{
		int p = 11, a = 1, b = 6;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		cout << "=========求元素的阶=========" << endl;
		while (1)
		{
			cout << "在以上循环群中选出一个点P:";
			cin >> P.x >> P.y;
			int n = C.getOrd(P);
			cout << "生成元P(" << P.x << "," << P.y << ")的阶为：" << n << endl;
		}
		
	}

	void test_three() //求P+Q的结果
	{
		int p = 11, a = 1, b = 6;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		P.x = 2;
		P.y = 7;
		cout << "=========求P+Q=========" << endl;
		while (1)
		{
			point Q;
			cout << "在以上循环群中选出一个点Q:";
			cin >> Q.x >> Q.y;

			point T;
			T = C.PplusQ(P, Q);
			cout << "T: " << T.x << "," << T.y << endl;
		}
		
	}

	void test_four()//求kP
	{
		int p = 2833, a = 1, b = 1;

		ECurve C(p, a, b);
		C.showEpab();
		point P;
		P.x = 1341;
		P.y = 854;
		cout << "=========求kP=========" << endl;
		while (1)
		{
			int k;
			cout << "输入k:";
			cin >> k;
			point temp;
			temp = C.kP(k, P);
			cout<< "temp: " << temp.x << "," << temp.y << endl;
		}
	}

	
}
	

int main()
{
	myspace::test_one();       //加密解密
	//myspace::test_two();       //求元素的阶
	//myspace::test_three();     //求P+Q的结果
	//myspace::test_four();      //求kP

	return 0;
}