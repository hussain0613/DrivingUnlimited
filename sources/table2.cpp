#include<stdlib.h>

class Field
{
public:
	int x, y, fwidth, fheight, tx, ty;//, txt_color[3], bg_color[3];
	std::string txt;
	int car_id;
	

	void setup()
	{
		fwidth = 160; fheight = 50;
		int n = txt.length();
		tx = x+(fwidth - 9*n)/2; //centre allignment
		//tx = (x+fwidth) - (9*n+10); // right side alignment 10px pad
		//tx = x;
		ty = y + (fheight-15)/2;
		car_id =-1;

		//printf("%d %d %d %d\n", x, y, fwidth, fheight);
	}
	void draw()
	{
		iSetColor(250, 250, 250);
		iText(tx, ty, (char *) txt.c_str(), GLUT_BITMAP_9_BY_15); //(char *) txt.c_str()
	}
};

class Row
{
public:
	int n, x, y, fw, fh, rw, rh; //, bg_color[3];
	Field fields[7];
	bool header;

	void setup()
	{
		header = false;
		n = 7;
		fw = 160;
		fh = 50;
		rw = fw*n;
		rh = fh;

		int fx = x;
		for(int i = 0; i<n; ++i){
			fields[i].x = fx;
			fields[i].y = y;
			fields[i].setup();
			fx += fw;
		}

	}
	
	void draw()
	{
		//iSetColor(bg_color[0], bg_color[1], bg_color[2]);
		iFilledRectangle(x, y, rw, rh);
		int i;
		for(i = 0; i<n-1; ++i){
			fields[i].draw();
		}
		
		if(!header && fields[i].car_id!=-1) iShowImage(fields[i].x+70, fields[i].y+2, 22, 48, game::cars[fields[i].car_id].img_id);
		else fields[i].draw();
	}
};



class Table{
public:
	int x, y, fh, fw, ncoll, nrow;
	//Row *rows;
	Row rows[11];

	void clear();
	void setup();
	void draw();
};


void Table::clear()
{
	for(int i = 0; i<11; ++i){
		for(int j = 0; j<ncoll; ++j){
			rows[i].fields[j].txt.clear();
			rows[i].setup();
		}
	}
}

void Table::setup()
{
	//rows = (Row *) malloc(sizeof(Row) * 11);
	
	nrow = 11;
	ncoll = 7;

	fw = 160;
	fh = 50;
	x = (SCRN_WIDTH - fw*ncoll)/2;
	y = (SCRN_HEIGHT - fh*nrow)/2;

	for(int i = 0; i<nrow; ++i){
		rows[i].x = x;
		rows[i].y = (y + i*fh);
		rows[i].setup();
	}
	rows[10].header = true;

	/*for(int i = 0;i<4;++i){
		rows[10].fields[i].tx = rows[10].fields[i].x+(fw - 9*rows[10].fields[i].txt.length())/2;
	}*/
}

void Table::draw()
{
	for(int i =0; i<nrow; ++i){
		if(i&1)iSetColor(50, 50, 50);
		else iSetColor(30, 30, 30);
		rows[i].draw();
	}
}