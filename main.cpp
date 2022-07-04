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


	void test_five()
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

		cout << endl << "===========A获得B的公钥，向B发送消息===========" << endl;
		cout << "输入A的私钥：";
		int A_private_key;
		cin >> A_private_key;

		cout << "输入明文:";
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
		cout << "输入A的私钥：";
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
	//myspace::test_one();       //加密解密
	//myspace::test_two();       //求元素的阶
	//myspace::test_three();     //求P+Q的结果
	//myspace::test_four();      //求kP
	//myspace::test_five();
	//myspace::test_myhash();
	myspace::sign_verify();    //私钥输入随机一个数，修改msg和msg2，内容相同为1，不同为0
	return 0;
}