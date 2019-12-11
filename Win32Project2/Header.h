#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct colorpoint{
	int x, y, c;
};
struct point{
	float x, y;
};


class shapes
{
protected:
	vector <point> p;
	int color;
	int no;
	int shap; // rect-1 , tri -2 , cir-3, line-4,poly-5, curve -6
	int filledcolor;
	colorpoint fclor;

public:
	void colc(int c){
		color = c;
	}
	virtual void draw() = 0;
	virtual bool checker(point ch) = 0;
	void saave();
	void fedcol(int c, point z);
	void fedcol();
	void savecl();
	colorpoint fcret(){
		return fclor;
	}
	~shapes(){
		p.clear();
	}
};

class openshape :public shapes{
public:
	//virtual	
	void changecolor();// = 0;
};
class polygon :public shapes{
protected:

public:
};
class circle :public shapes{
	int radius;
public:
	circle(int col);
	circle(int col, point a, point b, int n);
	void draw();
	bool circle::checker(point ch);
};
class text :public shapes{
	int length;
	char* data;
public:
	int retlen(){
		return length;
	}
	char* retdata(){
		return data;
	}
	text(int a, int b, char* l, int col);
	void draw();
	bool checker(point ch);
};

class rectangle :public polygon{

public:
	rectangle(int col);
	rectangle(int col, point a, point b, int n);
	void draw();
	bool checker(point ch);
};
class triangle :public polygon{

public:
	triangle(int col);
	triangle(int col, point a, point b, point c, int n);
	void draw();
	bool checker(point ch);
};
class polygon1 :public polygon{
public:
	polygon1(int col);
	polygon1(int col, point *a, int n);
	void draw();
	bool checker(point ch);
};
class line :public openshape{
	int type;//0 for solid ,1 for dotted
public:
	line(int col, int ty);
	line(int col, point a, point b, int n, int ty);
	int retty(){
		return type;
	}
	void draw();
	bool checker(point ch);
};
class curve :public openshape{

public:
	curve(int col);
	curve(int col, point *a, int n);
	void draw();
	bool checker(point ch);
};
