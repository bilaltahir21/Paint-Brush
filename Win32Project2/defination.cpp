#include <iostream>
#include <windows.h>
#include<winuser.h>
#include"gp142.h"
#include "Header.h"
#include <fstream>

fstream dobj("delete.pb");
fstream cloor("color.txt");
using namespace std;
int width1 = 3;
int x = 0, y = 0;
char key_pressed;
point p1;



bool onSegment(point pa, point qa, point ra)
{
	if (qa.x <= max(pa.x, ra.x) && qa.x >= min(pa.x, ra.x) &&
		qa.y <= max(pa.y, ra.y) && qa.y >= min(pa.y, ra.y))
		return true;

	return false;
}
int orientation(point pa, point q, point r){
	int val = (q.y - pa.y) * (r.x - q.x) -
		(q.x - pa.x) * (r.y - q.y);
	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}
bool doIntersect(point p1, point q1, point p2, point q2){
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);
	if (o1 != o2 && o3 != o4)
		return true;
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;
	return false;
}
bool polycheck(point ch, int no, vector<point>&p){
	point u;
	int count = 0;
	for (int d = 0; d < no - 1; d++){
		u.x = 255, u.y = -210;
		if (doIntersect(p[d], p[d + 1], ch, u)){
			count++;
		}
	}
	if (doIntersect(p[no - 1], p[0], ch, u))	count++;

	if (count % 2 != 0) return true;
	else{
		count = 0;
		for (int d = 0; d < no - 1; d++){
			u.x = 255, u.y = 200;
			if (doIntersect(p[d], p[d + 1], ch, u)){
				count++;
			}
		}
		if (doIntersect(p[no - 1], p[0], ch, u))	count++;
	}

	if (count % 2 != 0) return true;
	else{
		count = 0;
		for (int d = 0; d < no - 1; d++){
			u.x = -225, u.y = 200;
			if (doIntersect(p[d], p[d + 1], ch, u)){
				count++;
			}
			if (doIntersect(p[no - 1], p[0], ch, u))	count++;
		}
	}

	if (count % 2 != 0) return true;
	else{
		count = 0;
		for (int d = 0; d < no - 1; d++){
			u.x = -225, u.y = -210;
			if (doIntersect(p[d], p[d + 1], ch, u)){
				count++;
			}
		}
		if (doIntersect(p[no - 1], p[0], ch, u))	count++;
	}
	if (count % 2 != 0) return true;
	else return false;
}
float disfom(int x1, int y1, int  x2, int y2){
	float distancex = 0;
	float distancey = 0;
	distancex = (x2 - x1)*(x2 - x1);
	distancey = (y2 - y1) *(y2 - y1);
	return  (sqrt(distancex + distancey));
}
void GP142_await_event1(int *x, int *y, char *c)
{
	*x = -350, *y = -350;
	while (*x >= 255 || *x <= -225 || *y <= -210 || *y >= 200)  GP142_await_event(x, y, c);
}
bool linchek(int x1, int y1, int x2, int y2, int x3, int y3){
	float g = (disfom(x1, y1, x3, y3) + disfom(x2, y2, x3, y3)) - disfom(x1, y1, x2, y2);
	if (g <= 0.4 && g >= -0.4) return true;
	else return false;
}

rectangle::rectangle(int col){
	no = 2;
	color = col;
	shap = 1;
	for (int i = 0; i < no; i++){
		GP142_await_event1(&x, &y, &key_pressed);
		p1.x = x, p1.y = y;
		p.push_back(p1);
	}
}
rectangle::rectangle(int col, point a, point b, int n){
	no = n;
	color = col;
	shap = 1;
	p.push_back(a);
	p.push_back(b);

}
void rectangle::draw(){
	GP142_lineXY(color, p[0].x, p[0].y, p[1].x, p[0].y, width1);
	GP142_lineXY(color, p[0].x, p[0].y, p[0].x, p[1].y, width1);
	GP142_lineXY(color, p[1].x, p[0].y, p[1].x, p[1].y, width1);
	GP142_lineXY(color, p[1].x, p[1].y, p[0].x, p[1].y, width1);
}
bool rectangle::checker(point ch){
	if (ch.x <= p[0].x&&ch.x >= p[1].x&&ch.y <= p[0].y&&ch.y >= p[1].y) return true;
	else	if (ch.x >= p[0].x&&ch.x <= p[1].x&&ch.y >= p[0].y&&ch.y <= p[1].y) return true;
	else	if (ch.x >= p[0].x&&ch.x <= p[1].x&&ch.y <= p[0].y&&ch.y >= p[1].y) return true;
	else	if (ch.x <= p[0].x&&ch.x >= p[1].x&&ch.y >= p[0].y&&ch.y <= p[1].y) return true;
	else return false;
}

triangle::triangle(int col){
	no = 3;
	shap = 2;
	color = col;
	for (int i = 0; i < no; i++){
		GP142_await_event1(&x, &y, &key_pressed);
		p1.x = x, p1.y = y;
		p.push_back(p1);
	}
}
triangle::triangle(int col, point a, point b, point c, int n){
	no = n;
	color = col;
	shap = 2;
	p.push_back(a);
	p.push_back(b);
	p.push_back(c);
}
void triangle::draw(){
	GP142_lineXY(color, p[0].x, p[0].y, p[1].x, p[1].y, width1);
	GP142_lineXY(color, p[1].x, p[1].y, p[2].x, p[2].y, width1);
	GP142_lineXY(color, p[0].x, p[0].y, p[2].x, p[2].y, width1);
}
bool triangle::checker(point ch){
	if (polycheck(ch, no, p)) return true;
	else return false;

}

circle::circle(int col){
	no = 2;
	color = col;
	shap = 3;
	GP142_await_event1(&x, &y, &key_pressed);
	p1.x = x, p1.y = y;
	p.push_back(p1);
	GP142_await_event1(&x, &y, &key_pressed);
	p1.x = x, p1.y = y;
	p.push_back(p1);
	radius = (disfom(p[0].x, p[0].y, p[1].x, p[1].y));
}
circle::circle(int col, point a, point b, int n){
	no = n;
	color = col;
	shap = 3;
	p.push_back(a);
	p.push_back(b);
	radius = (disfom(p[0].x, p[0].y, p[1].x, p[1].y));
}
void circle::draw(){
	GP142_circleXY(color, p[0].x, p[0].y, radius, width1);
}
bool circle::checker(point ch){
	int distancex = 0;
	int distancey = 0;
	distancex = (p[0].x - ch.x)*(p[0].x - ch.x);
	distancey = (p[0].y - ch.y) *(p[0].y - ch.y);

	if ((sqrt(distancex + distancey)) <= radius)
		return true;
	else
		return false;
}

line::line(int col, int ty){
	no = 2;
	type = ty;
	shap = 4;
	color = col;
	for (int i = 0; i < no; i++){
		GP142_await_event1(&x, &y, &key_pressed);
		p1.x = x, p1.y = y;
		p.push_back(p1);
	}
}
line::line(int col, point a, point b, int n, int ty){
	no = n;
	type = ty;
	color = col;
	shap = 4;
	p.push_back(a);
	p.push_back(b);
}
void line::draw(){
	if (type == 0)
		GP142_lineXY(color, p[0].x, p[0].y, p[1].x, p[1].y, width1);
	else {

		int dx = p[1].x - p[0].x;
		int dy = p[1].y - p[0].y;
		int steps;
		if (abs(dx) > abs(dy))
			steps = abs(dx);
		else
			steps = abs(dy);
		float Xincrement = dx / (float)steps;
		float Yincrement = dy / (float)steps;
		point pp = p[0];
		for (int i = 0; i < steps; i++){
			pp.x = pp.x + Xincrement;
			pp.y = pp.y + Yincrement;
			if (i % 3 == 0)		GP142_pixelXY(color, round(pp.x), round(pp.y));
		}
	}
}
bool line::checker(point ch){
	if (linchek(p[0].x, p[0].y, p[1].x, p[1].y, ch.x, ch.y)) return true;
	else return false;
}

polygon1::polygon1(int col){
	int quit = FALSE;
	shap = 5;
	color = col;
	no = 1;
	GP142_await_event1(&x, &y, &key_pressed);
	p1.x = x, p1.y = y;
	p.push_back(p1);
	while (quit != TRUE){
		int	event = GP142_await_event(&x, &y, &key_pressed);
		switch (event) {
		case GP142_MOUSE:
			p1.x = x;
			p1.y = y;
			p.push_back(p1);
			no++;
			break;
		default:
			quit = TRUE;
			break;
		}
	}
}
polygon1::polygon1(int col, point *a, int n){
	no = n;
	color = col;
	shap = 5;
	for (int i = 0; i < n; i++){
		p.push_back(a[i]);
	}
}
void polygon1::draw(){
	for (int i = 0; i < no - 1; i++){
		GP142_lineXY(color, p[i].x, p[i].y, p[i + 1].x, p[i + 1].y, width1);
	}
	GP142_lineXY(color, p[0].x, p[0].y, p[no - 1].x, p[no - 1].y, width1);
}
bool polygon1::checker(point ch){
	if (polycheck(ch,no,p)) return true;
	else return false;
}

curve::curve(int col){
	int quit = FALSE;
	shap = 6;
	color = col;
	no = 1;
	GP142_await_event1(&x, &y, &key_pressed);
	p1.x = x, p1.y = y;
	p.push_back(p1);
	while (quit != TRUE){
		int	event = GP142_await_event(&x, &y, &key_pressed);
		switch (event) {
		case GP142_MOUSE:
			p1.x = x;
			p1.y = y;
			p.push_back(p1);
			no++;
			break;
		default:
			quit = TRUE;
			break;
		}
	}
}
curve::curve(int col, point *a, int n){
	no = n;
	color = col;
	shap = 5;
	for (int i = 0; i < n; i++){
		p.push_back(a[i]);
	}
}
void curve::draw(){
	for (int i = 0; i < no - 1; i++){
		GP142_lineXY(color, p[i].x, p[i].y, p[i + 1].x, p[i + 1].y, width1);
	}
}
bool curve::checker(point ch){
	for (int d = 0; d<no - 1; d++){
		if (linchek(p[d].x, p[d].y, p[d + 1].x, p[d + 1].y, ch.x, ch.y)) return true;
	}
	return false;
}

text::text(int a, int b, char* l, int col){
	p1.x = a; p1.y = b;
	no = 1;
	color = col;
	shap = 7;
	p.push_back(p1);
	length = strlen(l);
	data = new char[length];
	strcpy(data, l);
}
void text::draw(){
	const char *cstr = data;
	GP142_printfXY(color, p[0].x, p[0].y, 18, cstr);
}
bool text::checker(point ch){
	if (ch.x <= ((p[0].x + 18) + 18) && ch.x >= (p[0].x + (length * 18)) && ch.y <= (p[0].y + 18) && ch.y >= p[0].y) return true;
	else	if (ch.x >= (p[0].x + 18) && ch.x <= (p[0].x + (length * 18)) && ch.y >= (p[0].y + 18) && ch.y <= p[0].y) return true;
	else	if (ch.x >= (p[0].x + 18) && ch.x <= (p[0].x + (length * 18)) && ch.y <= (p[0].y + 18) && ch.y >= p[0].y) return true;
	else	if (ch.x <= (p[0].x + 18) && ch.x >= (p[0].x + (length * 18)) && ch.y >= (p[0].y + 18) && ch.y <= p[0].y) return true;
	else return false;
}

void shapes::saave(){
	dobj << shap << endl;
	dobj << color << endl;
	dobj << no << endl;
	for (int i = 0; i < no; i++){
		dobj << p[i].x << endl << p[i].y << endl;
	}
	if (shap == 7){
		char ext[50];
		int len;
		if (text* child = dynamic_cast<text*>(this)) {
			len = child->retlen();
			strcpy_s(ext,child->retdata());
		}
		dobj << len << endl;
		dobj << ext<<endl; 
	}
	if (shap == 4){
		int typ;
		if (line* child = dynamic_cast<line*>(this)) {
			typ = child->retty();
		}
		dobj << typ << endl;
	}

	dobj << -1 << endl;
}
void shapes::savecl(){
	cloor << fclor.x << endl << fclor.y << endl;
	cloor << filledcolor << endl;
}
void shapes::fedcol(int c, point z){
	filledcolor = c;
	fclor.x = z.x;
	fclor.y = z.y;
	fclor.c = c;
	//	cloor << fclor.x << endl << fclor.y << endl;
	//	cloor << filledcolor << endl;
}
void shapes::fedcol(){
	filledcolor = -1;
	fclor.x = -400;
	fclor.y = -400;
	fclor.c = -1;
	//	cloor << fclor.x << endl << fclor.y << endl;
	//	cloor << filledcolor << endl;

	//int 	pill = pil(fclor.x, fclor.y);
	//if (filledcolor != 1){
	//	fillcolor(color, pill, fclor.x, fclor.y, 0);
	//	fillcolor(color, pill, fclor.x - 1, fclor.y, 1);
	//}
}
