/*
	authur: Muhammad Hossain
*/

#include<math.h>
//#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctime>
//#include<typeinfo>
//#include "iGraphics.h"

/*
//functions for testing and debugging
#define GLUT_BITMAP_9_BY_15		((void*)2)
#define GLUT_BITMAP_8_BY_13		((void*)3)
#define GLUT_BITMAP_TIMES_ROMAN_10	((void*)4)
#define GLUT_BITMAP_TIMES_ROMAN_24	((void*)5)
//enum hfont {GLUT_BITMAP_8_BY_13, GLUT_BITMAP_9_BY_15};


void iSetColor(int r, int g, int b)
{
  printf("Color: %d %d %d\n", r, g, b);
}
void iText(int x, int y, char *text, void *font = (void*) GLUT_BITMAP_8_BY_13)
{
    char *f = "Not";
    //if(typeid (font) == typeid(GLUT_BITMAP_8_BY_13)) f = "Default";
    printf("iText on point (%d, %d) with font %s. the text: '%s'\n", x, y, f, text);
}
void iRectangle(int x, int y, int dx, int dy)
{
    printf("Rectangle at (%d, %d) with wXh as %d X %d\n", x, y, dx, dy);
}
void iFilledRectangle(int x, int y, int dx, int dy)
{
    printf("FilledRectangle at (%d, %d) with wXh as %d X %d\n", x, y, dx, dy);
}
void iCircle(int x, int y, int r)
{
    printf("Circle at (%d, %d) with radius %d\n", x, y, r);
}
void iFilledCircle(int x, int y, int r)
{
    printf("FilledCircle at (%d, %d) with radius %d\n", x, y, r);
}
void iShowBMP(int x, int y, char *fn)
{
    printf("BMP image at (%d, %d) file: %s\n", x, y, fn);
}

// end of testing and debugging functions and types
//*/

namespace ige_v1{

#define SCRN_WIDTH 1360
#define SCRN_HEIGHT 765
#define MX_FILES 10
#define MX_SHAPE_POINTS 5
#define MX_TEXT_LEN 200

struct Point{
	double x;
	double y;
};
typedef struct Point Point;


enum hShapes {RECT, CIRC, TRI, POL};
enum hFill {NONE, SOLID, IMG};

// class declarations
class Physics;
class hObject;
class hText; //: public hObject;
class hArea; //: public hObject;
class hRectangle; //: public hArea;
class hCircle; //: public hArea;
class hTriangle; //: public hArea;
class hPolygon; //: public hArea;
class TextArea; //: public hArea; //corresponding shape er shob ekhane use kora jaabe
class Button; //: public TextArea;
class TextInput; //: public TextArea;


// class definations without method defination
class hObject{
private:
    int __objId__;
public:
    static int __id_tracker__;

	Point cor;
	int color[3], img_ids[MX_FILES], aud_ids[MX_FILES];
	hFill fill_type;
	char *sound_files[MX_FILES], *image_files[MX_FILES];
	bool is_selected;
	double last_drawn; // every draw function must set value to this to use this
	//Physics phys;

    hObject(double x = 0, double y = 0); // every instance of the subclasses should go through this function to get a id

    int get_obj_id();

	void set_color(int r = 255, int g = 255, int b = 255);
	void set_sound_files(char **arr, int n);
	void set_img_files(char **arr, int n);

	void onClick(double x, double y, void (*func)(int x, int y) = NULL); // prottek onClick funtion button and state add korte hbe
	void passive(double x, double y, void (*func)(int x, int y) = NULL);
	void drag(double x, double y, void (*func)(int x, int y) = NULL);
	int isInside(double x, double y);
	void keyReaction(char key, void (*func)(char key) = NULL);

	void setup();
	void draw();
};
int ige_v1::hObject::__id_tracker__ = 0;

class hArea: public hObject{
public:
	bool border;
	// color will be fill color if there is a fill, otherwise border color and if none
	int bd_color[3];

	// muloto subclass er jonno. del kora jaite pare pore
	double height, width, radius, area;
	Point *points;

    hArea(double x = 0, double y = 0, bool b = false);

	void get_points(int **arr, int n); // special for triangle and other polygons
	void set_bd_color(int r, int g, int b);
	void calculate_area();
};


class Rectangle: public hArea{
	// eigula ke redefine korte hobe
public:
    Rectangle(double x = 0, double y = 0, double w = 200, double h = 100, bool b = false);
	void calculate_area();
	int isInside(double x, double y);
	void setup();
	void draw();
};


class Circle: public hArea{
	// eigula ke redefine korte hobe
public:
    Circle(double x = 50, double y = 50, double r = 50, bool b = false);
	void calculate_area();
	void setup();
	void draw();
};

class Triangle: public hArea{
	// eigula ke redefine korte hobe
public:
	void get_points(int **arr, int n);
	void calculate_area();
	void setup();
	void draw();
};

class hText: public hObject{
public:
	void *font;
	char *text;
	int len, index;

	hText(double x = 0, double y = 0, char *t = "Text", void *f = GLUT_BITMAP_8_BY_13);
	void clear();
	void setup();
	void draw();
};


/*class __TextArea__: public hArea{
public:
    __TextArea__(double x = 0, double y = 0, char *text = "Text Area"); // default shape will be rect but inheriting and invoking this constructor in subclass will help for other shapes
    // default shape rectangular
	hText text;
};*/


class TextArea: public Rectangle{
public:
    TextArea(double x = 0, double y = 0, char *text = "Text Area", double w = 200, double h = 100); // default shape rectangular
	hText text;

	void setup();
	void draw(); //based on shape draw function will change*/
};



class Button: public TextArea{
	// needs redefination
public:
    int color2[3], bd_color2[3];

    Button(double x = 0, double y = 0, char *t = "Button", double w = 100, double h=40);

	void onClick(double x, double y, void (*func)(int x, int y) = NULL);
	void passive(double x, double y, void (*func)(int x, int y) = NULL);
	void drag(double x, double y, void (*func)(int x, int y) = NULL);
	void keyReaction(char key, void (*func)(char key) = NULL);

	void setup();
	//void draw();
};

class TextInput: public TextArea{
public:
    bool show_welcome_text, ready_for_input;

    TextInput(double x = 0, double y = 0, double w = 200, double h = 30);

	void onClick(double x, double y, void (*func)(int x, int y) = NULL);
	void passive(double x, double y, void (*func)(int x, int y) = NULL);
	void drag(double x, double y, void (*func)(int x, int y) = NULL);
	void keyReaction(char key, void (*func)(char key) = NULL);

	//void setup();
	//void draw();
};


// method definations

// hObject methods
hObject::hObject(double x, double y)
{
    __objId__ = __id_tracker__++;

    cor.x = x;
    cor.y = y;

    set_color(255, 255, 255);
    fill_type = SOLID;
	last_drawn = -1; // meaning it is yet to be drawn
}


int hObject::get_obj_id()
{
    return __objId__;
}

void hObject::set_color(int r, int g, int b)
{
	//printf("inside hObject::set_color : %d %d %d\n", r, g, b);
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void hObject::set_img_files(char **arr, int n)
{
	for(int i = 0; i<n; ++i){
		image_files[i] = arr[i];
	}
}

void hObject::set_sound_files(char **arr, int n)
{
	for(int i = 0; i<n; ++i){
		sound_files[i] = arr[i];
	}
}

// hArea methods
hArea::hArea(double x, double y, bool b) : hObject(x, y)
{
    border = b;
    set_bd_color(250, 250, 250);
}
void hArea::set_bd_color(int r, int g, int b)
{
	bd_color[0] = r;
	bd_color[1] = g;
	bd_color[2] = b;
}

// different shapes' methods
Rectangle::Rectangle(double x, double y, double w, double h, bool b):hArea(x, y, b)
{
    width = w;
    height = h;
}
void Rectangle::calculate_area()
{
	area = height * width;
}

int Rectangle::isInside(double x, double y)
{
    if(cor.x < x && x < cor.x + width && cor.y < y && y < cor.y + height) return 1;
    else if(x == cor.x && x == cor.x + width && y == cor.y && y == cor.y + height) return 2;
    else return 0;
}

void Rectangle::setup()
{
	calculate_area();

	if(fill_type == IMG){
		img_ids[0] = iLoadImage(image_files[0]);
	}
}

void Rectangle::draw()
{
	//printf("form inside rect draw. stat:\n");
	//printf("x, y, w, h, r, g, b: %.2f %.2f %.2f %.2f %d %d %d\n", cor.x, cor.y, width, height, color[0], color[1], color[2]);
	double fx = cor.x, fy = cor.y, fh = height, fw = width;
	if(border){
		++fx; ++fy;
		fh-=2; fw -= 2;

		iSetColor(bd_color[0], bd_color[1], bd_color[2]);
		iRectangle(cor.x, cor.y, width, height);
	}

	if(fill_type == NONE){
		return;
	}
	else if(fill_type == SOLID){
		iSetColor(color[0], color[1], color[2]);
		iFilledRectangle(fx, fy, fw, fh);

		//iSetColor(bd_color[0], bd_color[1], bd_color[2]);
		//iRectangle(cor.x, cor.y, width, height);
	}
	else{
		//iShowBMP(fx, fy, image_files[1]);
		iShowImage(fx, fy, width, height, img_ids[0]);
	}

}

Circle::Circle(double x, double y, double r, bool b):hArea(x, y, b)
{
    radius = r;
}

void Circle::calculate_area()
{
	area = 3.14 * radius * radius;
}

void Circle::setup()
{
	calculate_area();
}

void Circle::draw()
{
	double fx = cor.x, fy = cor.y, r = radius;
	if(border){
		iSetColor(bd_color[0], bd_color[1], bd_color[2]);
		iCircle(cor.x, cor.y, r--);
	}

	if(fill_type == NONE){
		return;
	}
	else if(fill_type == SOLID){
		iSetColor(color[0], color[1], color[2]);
		iFilledCircle(fx, fy, r);
	}
	else{
		iShowBMP(fx, fy, image_files[1]); // will not work properly
		printf("[!] WARNING! IMAGE in CIRCLE might not work properly!\n");
	}

}


// hText methods
hText::hText(double x, double y, char *t, void *f): hObject(x, y)
{
	text = (char*) malloc(MX_TEXT_LEN);
    strcpy(text, t);
	if(f)
		font = font;
	else font = GLUT_BITMAP_8_BY_13;
	set_color(255, 255, 255);
    setup();
}

void hText::clear()
{
	text = (char*) calloc(MX_TEXT_LEN, sizeof(char));
}

void hText::setup()
{
    len = strlen(text);
}

void hText::draw()
{	
	//printf("form inside hText.draw with id %d text: %s at loc: %.2f, %.2f color: %d %d %d\n", get_obj_id(), text,cor.x, cor.y, color[0], color[1], color[2]);
	iSetColor(color[0], color[1], color[2]);
	iText(cor.x, cor.y, text);
}


//TextArea methods
/*__TextArea__::__TextArea__(double x, double y, char *text):hArea(x, y)
{
    this->text.text = text;
    this->text.cor.x = x;
    this->text.cor.y = y;
}*/
TextArea::TextArea(double x, double y, char *txt, double w, double h):Rectangle(x, y, w, h)
{
	text.text = txt;
    text.cor.x = x+5;
    text.cor.y = y+h-18;
	set_color(70, 70, 70);
	text.set_color(250, 250, 250);
}

void TextArea::draw()
{
    Rectangle::draw();
    text.draw();
}

//button
Button::Button(double x, double y, char* t, double w, double h) : TextArea(x, y, t, w, h)
{
	set_color(250, 250, 250);
	text.set_color(70, 70, 70);
    setup();
}

void Button::setup()
{
    text.setup();
    double cw = 9, ch = 15, tw, th;
    if(text.font == GLUT_BITMAP_9_BY_15){
        cw = 9;
        ch = 15;
    }
    else if(text.font == GLUT_BITMAP_8_BY_13){
        cw = 8;
        ch = 13;
    }
    else if(text.font == GLUT_BITMAP_TIMES_ROMAN_10){
        cw = 10;
        ch = 10;
    }
    else if(text.font == GLUT_BITMAP_TIMES_ROMAN_24){
        cw = 24;
        ch = 24;
    }
    tw = text.len * cw;
    th = ch;
    text.cor.x = cor.x + (width - tw)/2;
    text.cor.y = cor.y + (height - th)/2;

    for(int i=0; i<3; ++i){
        color2[i] = color[i];
	}
}


void Button::onClick(double x, double y, void (*func)(int x, int y))
{
    if(isInside(x, y)){
        //set_color(color[0]/2, color[1]/2, color[2]/2);
        set_color(180, 180, 180);
		if(func) func(x, y);
    }
}

void Button::passive(double x, double y, void (*func)(int x, int y))
{
    if(isInside(x, y)){
        //set_color(color[0]*(2/3), color[1]*(2/3), color[2]*(2/3));
        set_color(220, 220, 220);
		if(func) func(x, y);
    }
    else{
        set_color(color2[0], color2[1], color2[2]);
		//set_color(bd_color2[0], bd_color2[1], bd_color2[2]);
    }
}

// TextInput
TextInput::TextInput(double x, double y, double w, double h):TextArea(x, y, "Click here for typing...", w, h)
{
    show_welcome_text = true;
    ready_for_input = false;
}

void TextInput::onClick(double x, double y, void (*func) (int x, int y))
{
    if(isInside(x, y)){
        ready_for_input = true;
        if(show_welcome_text){
            show_welcome_text = false;
            text.clear();
            text.len = 0;
            text.index = 0;
        }
    }
    else{
        ready_for_input = false;
    }
}

void TextInput::keyReaction(char key, void (*func)(char key))
{
    if(ready_for_input && 32<= key && key<=126 && text.len<MX_TEXT_LEN){
		//__str__.append(std::string(key));
		text.text[text.len] = key;
		text.text[++text.len] = '\0';
	}
	else if (ready_for_input && key == 8) // back_space
	{
		if(text.len > 0) text.text[--text.len] = '\0';
	}
	/*else if(mode = 1 && (key == 10 || key == 13))
	{
		text[++i] = 10;
		text[i] = '\0';
	}*/
	else ready_for_input = 0;
}

}


/*
int main()
{
    printf("Hello World\n");
	ige::Rectangle r;
	ige::TextArea ta(14, 15, "HELLO");
    ige::Button bt;

	printf("\n");
	printf("details for object with id: %d\n", ta.get_obj_id());
	ta.draw();
	printf("\n");

	printf("\n");
	printf("details for object with id: %d\n", bt.get_obj_id());
	bt.draw();
	printf("\n");

	return 0;
}
*/
