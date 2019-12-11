#include <iostream>
#include"gp142.h"
#include "Header.h"
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <conio.h>
#pragma comment(lib, "windowscodecs.lib")
using namespace std;

fstream loxd("delete.pb");

#define FALSE 0
#define TRUE  1
#define MAX_COLORS     24
#define BLACK           0
#define WHITE           1
#define RED             2
#define GREEN           3
#define BLUE            4
#define YELLOW          5
#define MAGENTA         6
#define CYAN            7
#define PURPLE          8
#define NAVY_BLUE       9
#define DUSTY_PLUM      10
#define ICE_BLUE        11
#define TURQUOISE       12
#define ORANGE          13
#define BROWN           14
#define PINK            15
#define CHALK           16
#define GOLD            17
#define PEACH           18
#define FOREST_GREEN    19
#define SEA_GREEN       20
#define OLIVE           21
#define MED_GRAY        22
#define LT_GRAY         23


int color = 23;
int col1 = 0;
int width = 3;
int pill = 0;
shapes**all;
int size = 256;
int coun = 0;
colorpoint*allc;
int colcoun = 0;


void inter();
void dsquare(int x1, int y1, int x2, int y2);
void dtriangle(int x1, int y1, int x2, int y2, int x3, int y3);
bool check(int x1, int y1, int x2, int y2, int x, int y);
bool check_cir(int x1, int y1, int rad, int x, int y);
void color_ch(int mouse_x, int mouse_y);
void box_ch(int mouse_x, int mouse_y, char &key_pressed, int &quit);
void box_sel(int x1, int y1, int x2, int y2, int co);
void savepixel();
void loadpixel();
int colreturner(int c);
void load();
void loadclor(); 
void colarrload();
void fillcolorz(int color, int pill, int a, int b, int ride);
void clear(shapes**arr, int size);


void GP142_await_event2(int *x, int *y, char *c)
{
	*x = -350, *y = -350;
	while (*x >= 255 || *x <= -225 || *y <= -210 || *y >= 200)  GP142_await_event(x, y, c);
}
void dfsq(int colu, int x1, int y1, int x2, int y2){

	GP142_lineXY(colu, x1, y1, x2, y1, width);
	GP142_lineXY(colu, x1, y1, x1, y2, width);
	GP142_lineXY(colu, x2, y1, x2, y2, width);
	GP142_lineXY(colu, x2, y2, x1, y2, width);
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	for (int i = x1; i < x2; i++)
		GP142_lineXY(colu, i, y1, i, y2, width);
}
void shrink(int x){
	if (x >= 0)	all[x]->fedcol();
	int foj = 0;
	if (coun == 0)foj = 2;
	else foj = 2 * coun;
	colorpoint*allc1 = new colorpoint[foj];
	shapes**all1 = new shapes*[foj];
	int j = 0;
	for (int i = 0; i < coun; i++){
		if (i != x){
			all1[j] = all[i];
			allc1[j] = allc[i];
			j++;
		}
	}
	
	if (x != -1)	delete all[x];
	delete[]all;
	all = all1;
	allc = allc1;
	if (coun == 0)size = 2;
	else size = 2 * coun;
	if (x >= 0)	coun--;
	colcoun = coun;
}


int main(void){
	all = new shapes*[256];
	allc = new colorpoint[100];
	int quit;
	int event;
	int mouse_x, mouse_y;
	char key_pressed;
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	double rad = 0;
	GP142_open();
	inter();
	dfsq(1, 255, -210, -225, 200);// middle box

	GP142_textXY(0, -160, 20, 20, "Do you want to continue with previous file ?");
	GP142_textXY(0, -160, -20, 25, "         YES                NO");
	dsquare(-106, 12, -40, -18);
	dsquare(53, 12, 113, -18);
	GP142_await_event(&x, &y, &key_pressed);
	dfsq(1, 255, -210, -225, 200);// middle box
	if (check(-106, 12, -40, -18, x, y)){
		load();
		loadclor();
	}
	else{
		ofstream giopta01("color.txt");
		ofstream giopta02("delete.pb");
		giopta01.close();
		giopta02.close();
	}
	quit = FALSE;
	while (!quit) {
		inter();
		if (size == 0) {
			all = new shapes*[2];
			size = 2;
		}
		if (coun == 0){
			ofstream giopta1("color.txt");
			ofstream giopta2("delete.pb");
			giopta1.close();
			giopta2.close();
		}
		if (size - coun == 1)	shrink(-1);
		event = GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		switch (event) {
		case GP142_QUIT:
			quit = TRUE;
			break;

		case GP142_MOUSE:
			box_ch(mouse_x, mouse_y, key_pressed, quit);
			color_ch(mouse_x, mouse_y);
			break;

		case GP142_KBD:
			break;

		default:
			break;
		}
	}
	clear(all, size);
	GP142_close();
	return 0;
}
void dsquare(int x1, int y1, int x2, int y2){
	GP142_lineXY(color, x1, y1, x2, y1, width);
	GP142_lineXY(color, x1, y1, x1, y2, width);
	GP142_lineXY(color, x2, y1, x2, y2, width);
	GP142_lineXY(color, x2, y2, x1, y2, width);
}
void dtriangle(int x1, int y1, int x2, int y2, int x3, int y3){

	GP142_lineXY(color, x1, y1, x2, y2, width);
	GP142_lineXY(color, x2, y2, x3, y3, width);
	GP142_lineXY(color, x1, y1, x3, y3, width);

}
bool check(int x1, int y1, int x2, int y2, int x, int y){
	if (x <= x1&&x >= x2&&y <= y1&&y >= y2) return true;
	else	if (x >= x1&&x <= x2&&y >= y1&&y <= y2) return true;
	else	if (x >= x1&&x <= x2&&y <= y1&&y >= y2) return true;
	else	if (x <= x1&&x >= x2&&y >= y1&&y <= y2) return true;
	else return false;
}
bool check_cir(int x1, int y1, int rad, int x, int y){
	int x2 = x1 + rad;
	int y2 = y1 + rad;
	x1 = x1 - rad;
	y1 = y1 - rad;
	if (x <= x1&&x >= x2&&y <= y1&&y >= y2) return true;
	else	if (x >= x1&&x <= x2&&y >= y1&&y <= y2) return true;
	else	if (x >= x1&&x <= x2&&y <= y1&&y >= y2) return true;
	else	if (x <= x1&&x >= x2&&y >= y1&&y <= y2) return true;

	else return false;
}
void color_ch(int mouse_x, int mouse_y){
	if (check_cir(-232, 220, 7, mouse_x, mouse_y)){
		color = 0;
	}
	else 	if (check_cir(-212, 220, 7, mouse_x, mouse_y)){
		color = 1;
	}
	else 	if (check_cir(-192, 220, 7, mouse_x, mouse_y)){
		color = 2;
	}
	else 	if (check_cir(-172, 220, 7, mouse_x, mouse_y)){
		color = 3;
	}
	else 	if (check_cir(-152, 220, 7, mouse_x, mouse_y)){
		color = 4;
	}
	else 	if (check_cir(-132, 220, 7, mouse_x, mouse_y)){
		color = 5;
	}
	else 	if (check_cir(-112, 220, 7, mouse_x, mouse_y)){
		color = 6;
	}
	else 	if (check_cir(-92, 220, 7, mouse_x, mouse_y)){
		color = 7;
	}
	else 	if (check_cir(-72, 220, 7, mouse_x, mouse_y)){
		color = 8;
	}
	else 	if (check_cir(-52, 220, 7, mouse_x, mouse_y)){
		color = 9;
	}
	else 	if (check_cir(-32, 220, 7, mouse_x, mouse_y)){
		color = 10;
	}
	else 	if (check_cir(-12, 220, 7, mouse_x, mouse_y)){
		color = 11;
	}
	else 	if (check_cir(8, 220, 7, mouse_x, mouse_y)){
		color = 12;
	}
	else 	if (check_cir(28, 220, 7, mouse_x, mouse_y)){
		color = 13;
	}
	else 	if (check_cir(48, 220, 7, mouse_x, mouse_y)){
		color = 14;
	}
	else 	if (check_cir(68, 220, 7, mouse_x, mouse_y)){
		color = 15;
	}
	else 	if (check_cir(88, 220, 7, mouse_x, mouse_y)){
		color = 16;
	}
	else 	if (check_cir(108, 220, 7, mouse_x, mouse_y)){
		color = 17;
	}
	else 	if (check_cir(128, 220, 7, mouse_x, mouse_y)){
		color = 18;
	}
	else 	if (check_cir(148, 220, 7, mouse_x, mouse_y)){
		color = 19;
	}
	else 	if (check_cir(168, 220, 7, mouse_x, mouse_y)){
		color = 20;
	}
	else 	if (check_cir(188, 220, 7, mouse_x, mouse_y)){
		color = 21;
	}
	else 	if (check_cir(208, 220, 7, mouse_x, mouse_y)){
		color = 22;
	}
	else 	if (check_cir(228, 220, 7, mouse_x, mouse_y)){
		color = 23;
	}
}
void box_ch(int mouse_x, int mouse_y, char &key_pressed, int &quit){
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int us1 = 210;
	double rad = 0;

	if (check(-272, 210, -247, 195, mouse_x, mouse_y)){//box 1 rectangle
		box_sel(-272, 210, -247, 195, 17);
		all[coun] = new rectangle(color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 210, -247, 195, 23);
	}
	else 	if (check(-272, 175, -247, 160, mouse_x, mouse_y)){//box 2 triangle
		box_sel(-272, 175, -247, 160, 17);
		all[coun] = new triangle(color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 175, -247, 160, 23);
	}
	else 	if (check(-272, 140, -247, 125, mouse_x, mouse_y)){//box3 cirlce
		box_sel(-272, 140, -247, 125, 17);
		all[coun] = new circle(color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 140, -247, 125, 23);
	}
	else 	if (check(-272, 105, -247, 90, mouse_x, mouse_y)){// box 4 line
		box_sel(-272, 105, -247, 90, 17);
		int type = 0;
		dfsq(0, -272, 105, -247, 90);
		width = 1;
		box_sel(-272, 105, -259, 90, 1);
		box_sel(-259, 105, -247, 90, 1);
		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		if (check(-272, 105, -259, 90, mouse_x, mouse_y)){ 
			type = 0; 
			box_sel(-272, 105, -259, 90, 17);
		}
		if (check(-259, 105, -247, 90, mouse_x, mouse_y)){
			type = 1;
			box_sel(-259, 105, -247, 90, 17);
		}

		width = 3;
		all[coun] = new line(color, type);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 105, -247, 90, 23);
	}
	else 	if (check(-272, 70, -247, 55, mouse_x, mouse_y)){// box 5 polygon
		box_sel(-272, 70, -247, 55, 17);
		all[coun] = new polygon1(color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 70, -247, 55, 23);
	}
	else 	if (check(-272, 35, -247, 20, mouse_x, mouse_y)){// box 6 curve
		box_sel(-272, 35, -247, 20, 17);
		all[coun] = new curve(color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 35, -247, 20, 23);
	}
	else 	if (check(-272, 0, -247, -15, mouse_x, mouse_y)){// box 7 text
		box_sel(-272, 0, -247, -15, 17);
		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		x = mouse_x;
		y = mouse_y;
		char us[200];
		int i = 0;
		int event;
		quit = FALSE;
		while (!quit) {
			event = GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
			switch (event) {
			case GP142_KBD:
				us[i] = key_pressed;
				i++;
				break;
			default:
				quit = TRUE;
				break;
			}
		}
		quit = FALSE;
		us[i] = '\0';
		all[coun] = new text(x, y, us, color);
		all[coun]->draw();
		all[coun]->fedcol();
		coun++;
		box_sel(-272, 0, -247, -15, 23);
	}
	else 	if (check(-272, -35, -247, -50, mouse_x, mouse_y)){// box 8 delete
		box_sel(-272, -35, -247, -50, 17);
		mouse_x = 0, mouse_y = 0;
		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		while (!check(-272, -35, -247, -50, mouse_x, mouse_y)){
			int x = -1;
			point z;
			z.x = mouse_x;
			z.y = mouse_y;
			for (int i = coun - 1; i > -1; i--) {
				if (all[i]->checker(z)) {
					all[i]->fedcol();
					x = i;
					break;
				}
			}
			dfsq(1, 255, -210, -225, 200);// middle box
			for (int i = 0; i < coun; i++){
				if (i != x) all[i]->draw();
			}

			ofstream goshiop("color.txt");
			goshiop.close();
			for (int i = 0; i < coun; i++){
				all[i]->savecl();
			}
			if (x != -1){
				shrink(x); 
			}
		if (coun != 0)		colarrload();
		else {
				dfsq(1, 255, -210, -225, 200);// middle box
			}
		
		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
	}
		box_sel(-272, -35, -247, -50, 23);
	}
	else 	if (check(-272, -70, -247, -85, mouse_x, mouse_y)){// box 9 save
		box_sel(-272, -70, -247, -85, 17);
		//for (int i = 0; i < coun; i++){
		//	all[i]->saave();
		//}
		savepixel();
		box_sel(-272, -70, -247, -85, 23);
	}
	else 	if (check(-272, -105, -247, -120, mouse_x, mouse_y)){// box 10 load
		box_sel(-272, -105, -247, -120, 17);
		loadpixel();
		box_sel(-272, -105, -247, -120, 23);
	}
	else 	if (check(-272, -140, -247, -155, mouse_x, mouse_y)){// box 11 bucket fill
		box_sel(-272, -140, -247, -155, 17);
		mouse_x = 0, mouse_y = 0;
		GP142_await_event2(&mouse_x, &mouse_y, &key_pressed);
		pill = pil(mouse_x, mouse_y);
		if (colreturner(pill) != color){
			fillcolorz(color, pill, mouse_x, mouse_y, 0);
			fillcolorz(color, pill, mouse_x - 1, mouse_y, 1);
		}
		int x = -1;
		point z;
		z.x = mouse_x;
		z.y = mouse_y;
		for (int i = coun - 1; i > -1; i--) {
			if (all[i]->checker(z)) {
				x = i;
				all[x]->fedcol(color, z);
				break;
			}
		}
	
		box_sel(-272, -140, -247, -155, 23);
	}
	else 	if (check(-272, -175, -247, -190, mouse_x, mouse_y)){// box 12 clear
		box_sel(-272, -175, -247, -190, 17);
		GP142_circleXY(0, 0, 0, 500, 0);
		inter();
		coun = 0;
		size = 0;
		delete[]all;
		dfsq(1, 255, -210, -225, 200);// middle box
		box_sel(-272, -175, -247, -190, 23);
	}
	else	if (check(-272, -210, -247, -225, mouse_x, mouse_y)){// box 13 quit
		ofstream dash("delete.pb");
		box_sel(-272, -210, -247, -225, 17);
		for (int i = 0; i < coun; i++){
			all[i]->saave();
			all[i]->savecl();
		}
		dash.close();
		quit = TRUE;
		box_sel(-272, -210, -247, -225, 23);
	}
}
void box_sel(int x1, int y1, int x2, int y2, int co){
	col1 = color;
	color = co;
	//dsquare(x1, y1, x2, y2);
	dsquare(x1 - 1, y1 + 1, x2 + 1, y2 - 1);
	color = col1;
}
void inter(){
	dfsq(0, -292, 240, 268, 200);
	dfsq(0, 257, 240, 292, -240);
	dfsq(0, -292, 240, -226, -240);
	dfsq(0, -233, -212, 292, -240);

	col1 = color;
	color = 1;
	int us1 = 210;
	for (int i = 0; i < 13; i++){
		dsquare(-277, us1+5, -242, us1 - 20);
		//dsquare(-272, us1, -247, us1 - 15);
		us1 = us1 - 35;
	}
	us1 = 210;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Rect");		us1 = us1 - 35;
	GP142_textXY(1, -267, (us1 + (us1 - 30)) / 2, 10, "Tri");		us1 = us1 - 35;
	GP142_textXY(1, -267, (us1 + (us1 - 30)) / 2, 10, "Cir");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Line");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Poly");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Curv");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Text");		us1 = us1 - 35;
	GP142_textXY(1, -267, (us1 + (us1 - 30)) / 2, 10, "Del");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Save");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Load");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Buck");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "New");		us1 = us1 - 35;
	GP142_textXY(1, -269, (us1 + (us1 - 30)) / 2, 10, "Quit");		us1 = us1 - 35;

	us1 = -232;
	for (int i = 0; i < 24; i++){
		GP142_circleXY(1, us1, 220, 8, 0);
		GP142_circleXY(i, us1, 220, 7, 0);
		us1 = us1 + 20;
	}
	color = 22;
	int wid = width;
	width = 5;
	dsquare(255, -210, -225, 200);// middle box
	width = wid;
	color = 1;

	color = col1;
	GP142_circleXY(23, 270, 220, 17, 0);
	GP142_circleXY(1, 270, 220, 15, 0);
	GP142_circleXY(0, 270, 220, 11, 0);
	GP142_circleXY(color, 270, 220, 9, 0);
}
int colreturner(int c){
	if (c == 0)	return 0;
	else if (c == 16777215) return 1;
	else if (c == 255) return	2;
	else if (c == 65280) return 3;
	else if (c == 16711680) return 4;
	else if (c == 65535) return 5;
	else if (c == 16711935) return 6;
	else if (c == 16776960) return 7;
	else if (c == 13369497) return 8;
	else if (c == 10040064) return 9;
	else if (c == 10053273) return 10;
	else if (c == 16777113) return 11;
	else if (c == 13434777) return 12;
	else if (c == 26367) return 13;
	else if (c == 3368601) return 14;
	else if (c == 13408767) return 15;
	else if (c == 10092543) return 16;
	else if (c == 3381708) return 17;
	else if (c == 6724095) return 18;
	else if (c == 3368448) return 19;
	else if (c == 10079283) return 20;
	else if (c == 3381657) return 21;
	else if (c == 8421504) return 22;
	else if (c == 13421772) return 23;
}
void loadpixel(){
	ifstream load("paint.pb");
	int  c;

	for (int x = 255; x > -226; x--){
		for (int y = 200; y > -211; y--){
			load >> c;
			GP142_pixelXY(c, x, y);
		}
	}
	load.close();
}
void savepixel(){
	ofstream xave("paint.pb");
	for (int x = 255; x > -226; x--){
		for (int y = 200; y > -211; y--){
			xave << colreturner(pil(x, y)) << endl;
		}
	}
	xave.close();
}
point getpoint(){
	point t;
	float n;
	loxd >> n;
	t.x = n;
	loxd >> n;
	t.y = n;
	return t;
}
void load(){
	coun = 0;
	int ch;
	point* pp;
	int n;
	point a, b, c;
	while (!loxd.eof()){
		loxd >> ch;
		if (ch != -1){
			int f;
			if (ch == 1){
				loxd >> f;
				loxd >> n;
				a = getpoint();
				b = getpoint();
				all[coun] = new rectangle(f, a, b, 2);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 2){
				loxd >> f;
				loxd >> n;
				a = getpoint();
				b = getpoint();
				c = getpoint();

				all[coun] = new triangle(f, a, b, c, n);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 3){
				loxd >> f;
				loxd >> n;
				a = getpoint();
				b = getpoint();
				all[coun] = new circle(f, a, b, n);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 4){
				int type = 0;
				loxd >> f;
				loxd >> n;
				a = getpoint();
				b = getpoint();
				loxd >> type;
				all[coun] = new line(f, a, b, n, type);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 5){
				point*pp;
				loxd >> f;
				loxd >> n;
				pp = new point[n];
				for (int i = 0; i < n; i++){
					pp[i] = getpoint();
				}
				all[coun] = new polygon1(f, pp, n);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 6){
				point*pp;
				loxd >> f;
				loxd >> n;
				pp = new point[n];
				for (int i = 0; i < n; i++){
					pp[i] = getpoint();
				}
				all[coun] = new curve(f, pp, n);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
			else if (ch == 7){
				point*pp;
				char ext[100];
				loxd >> f;
				loxd >> n;
				pp = new point[n];
				for (int i = 0; i < n; i++){
					pp[i] = getpoint();
				}
				int len;
				loxd >> len;
				char*data = new char[len + 1];
				loxd.getline(ext, 100);
				loxd.getline(ext, 100);
				strcpy(data, ext);
				all[coun] = new text(pp[0].x,pp[0].y,data, f);
				all[coun]->draw();
				all[coun]->fedcol();
				coun++;
			}
		}
	}
}
void loadclor(){
	fstream dhosh("color.txt");
	int x; int y; int z;
	while (!dhosh.eof()){
		dhosh >> x;
		dhosh >> y;
		dhosh >> z;

		point z1;
		z1.x = x;
		z1.y = y;

		for (int i = coun - 1; i > -1; i--) {
			if (all[i]->checker(z1)){
				all[i]->fedcol(z, z1);
				break;
			}
		}

		pill = pil(x, y);
		if (colreturner(pill) != z&& z != -1){
			fillcolorz(z, pill, x, y, 0);
			fillcolorz(z, pill, x - 1, y, 1);
		}
	}
	dhosh.close();
}
void colarrload(){
	colorpoint g;
	for (int i = 0; i < colcoun; i++){
		g = all[i]->fcret();
		pill = pil(g.x, g.y);
		if (colreturner(pill) != g.c&& g.c != -1){
			fillcolorz(g.c, pill, g.x, g.y, 0);
			fillcolorz(g.c, pill, (g.x) - 1, g.y, 1);
		}
	}
}
void fillcolorz(int color, int pill, int a, int b, int ride){//ride 0 for upper left half  1 for lower right half
	if (pill == pil(a,b)){
		GP142_pixelXY(color, a, b);
		if (ride == 0){
			fillcolorz(color, pill, a - 1, b - 1, 0);
			fillcolorz(color, pill, a, b - 1, 0);
			fillcolorz(color, pill, a + 1, b + 1, 0);
			fillcolorz(color, pill, a + 1, b - 1, 1);
		}
		else 	if (ride == 1){
			fillcolorz(color, pill, a - 1, b - 1, 1);
			fillcolorz(color, pill, a, b + 1, 1);
			fillcolorz(color, pill, a + 1, b + 1, 1);
			fillcolorz(color, pill, a + 1, b - 1, 0);
		}
	}
	else return;
}
void clear(shapes**arr, int size){
	for (int i = 0; i < coun; i++){
		delete arr[i];
	}
	delete[]arr;
}