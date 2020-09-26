#include<stdlib.h>
#include<ctime>
#include<string.h>

#include "iGraphicsHeaders/iGraphics.h"


#define SCRN_WIDTH 600
#define SCRN_HEIGHT 700



class Ball{
public:
	double x, y, r, color[3];

	void setall(double x, double y, double r);
	void set_color(int r=255, int g=255, int b=255);
	void draw();
};

Ball ball;
double dx, dy;
bool pause;
int id;
int tx;
char *t1 = "Press 'p' to start/stop.", *t2 = "Press 'r' to reset.";


int OffScreenStat(double x, double y, double r);
void changePos();
void setup();


void iDraw()
{
	iClear();

	ball.draw();

	iSetColor(170, 250, 210);
	iLine(0, 43, SCRN_WIDTH, 43);
	iText(tx, 25, t1);
	iText(tx, 5, t2);
}


void iPassiveMouse(int x, int y){}
void iMouse(int button, int state, int x, int y){};
void iMouseMove(int x, int y){}

void iKeyboard(unsigned char key)
{
	if(key == 'p'){
		if(pause){
			iResumeTimer(id);
			pause = false;
		}
		else{
			iPauseTimer(id);
			pause = true;
		}
	}
	else if (key == 'r'){
		setup();
	}
}


void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END){
		exit(NULL);
	}
}



int main()
{

	iInitialize(SCRN_WIDTH, SCRN_HEIGHT, "Bouncing Ball (19.01.04.060)");

	setup();

	id = iSetTimer(17, changePos);
	
	iStart();

	return 0;
}


// Ball::<methods> definations
void Ball::setall(double x, double y, double r)
{
	this->x = x;
	this->y = y;
	this->r = r;
}
void Ball::set_color(int r, int g, int b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
void Ball::draw()
{
	iSetColor(color[0], color[1], color[2]);
	iFilledCircle(x, y, r);
}


// other functions' definations
int OffScreenStat(double x, double y, double r)
{
	if(x-r<0) return 1;
	if(y+r>SCRN_HEIGHT) return 2;
	if(x+r>SCRN_WIDTH) return 3;
	if(y-r<0) return 4;
	return 0;
}

void changePos()
{
	int stat = OffScreenStat(ball.x+dx, ball.y+dy, ball.r);
	
	if(!stat){
		//do_nothing
	}

	else if(stat&1){
		dx *= -1;
		ball.set_color(rand()%201+50, rand()%201+50, rand()%201+50);
	}
	else{ 
		dy *= -1;
		ball.set_color(rand()%201+50, rand()%201+50, rand()%201+50);
	}

	ball.x += dx;
	ball.y += dy;
}

void setup()
{
	srand(time(NULL));

	dx = rand()%13 + 1;
	dy = rand()%13 + 1;
	dx *= (rand()&1)? -1: 1;
	dy *= (rand()&1)? -1: 1;

	
	ball.set_color(rand()%201+50, rand()%201+50, rand()%201+50);
	ball.setall(SCRN_WIDTH/2, SCRN_HEIGHT/2, 10);
	pause = true;

	tx = (SCRN_WIDTH-strlen(t1) * 9)/2;
}