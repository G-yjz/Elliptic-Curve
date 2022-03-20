#include"ECurve.h"

namespace myspace
{
	void test_one()
	{
		int x, y;
		//p=11��a=1��b=6��P(2,7)��Q(2,7)
		ECurve *e = new ECurve(11, 1, 6);//p,a,b

		e->showEpab();    //��ʾ����Բ����ѭ��ȺԪ��
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

		cout << "����p(����):";
		cin >> p;
		cout << "����a:";
		cin >> a;
		cout << "����b:";
		cin >> b;
		ECurve *e = new ECurve(p, a, b);//p,a,b
		cout << "����Բ����ѭ��ȺԪ��";
		e->showEpab();    //��ʾ����Բ����ѭ��ȺԪ��
		int x1, y1, x2, y2;//P(x1,y1),Q(x2,y2)
		cout << "����P+Q" << endl;
		cout << "����P����x1,y1: ";
		cin >> x1 >> y1;
		cout << "����Q����x2,y2: ";
		cin >> x2 >> y2;
		e->PplusQ(x1, y1, x2, y2, x, y);//P(x1,y1)+Q(x2,y2)
		cout << "P+Q: " << x << " " << y << endl;
		int k;
		cout << "����kP" << endl;
		cout << "��������ԪP����x1,y1: ";
		cin >> x1 >> y1;
		while (1)
		{
			cout << "����k��";
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