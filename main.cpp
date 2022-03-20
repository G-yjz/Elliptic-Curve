#include"ECurve.h"

namespace myspace
{
	void test_one()
	{
		int x, y;
		//p=11、a=1、b=6、P(2,7)、Q(2,7)
		ECurve *e = new ECurve(11, 1, 6);//p,a,b

		e->showEpab();    //显示该椭圆曲线循环群元素
		e->PplusQ(2, 7, 2, 7, x, y);//P(x1,y1),Q(x2,y2)
		cout << "P+Q: (" << x << "," << y << ")"<<endl;
		e->kP(15, 2, 7, x, y);        //k,x1,y1
		cout << "kP: (" << x << "," << y << ")" << endl;
		
		delete e;
	}

	void test_two()
	{
		int x, y;
		int p, a, b;

		cout << "输入p(素数):";
		cin >> p;
		cout << "输入a:";
		cin >> a;
		cout << "输入b:";
		cin >> b;
		ECurve *e = new ECurve(p, a, b);//p,a,b
		cout << "该椭圆曲线循环群元素";
		e->showEpab();    //显示该椭圆曲线循环群元素
		int x1, y1, x2, y2;//P(x1,y1),Q(x2,y2)
		cout << "计算P+Q" << endl;
		cout << "输入P坐标x1,y1: ";
		cin >> x1 >> y1;
		cout << "输入Q坐标x2,y2: ";
		cin >> x2 >> y2;
		e->PplusQ(x1, y1, x2, y2, x, y);//P(x1,y1)+Q(x2,y2)
		cout << "P+Q: " << x << " " << y << endl;
		int k;
		cout << "计算kP" << endl;
		cout << "输入生成元P坐标x1,y1: ";
		cin >> x1 >> y1;
		while (1)
		{
			cout << "输入k：";
			cin >> k;
			e->kP(k, x1, y1, x, y);        //k,x1,y1
			cout << "kP: (" << x << "," << y <<")"<< endl;
		} 

		delete e;
	}	
}
	

int main()
{
	myspace::test_one();
	//myspace::test_two();
	return 0;
}