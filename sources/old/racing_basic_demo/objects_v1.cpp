class Car;
class Road;

class Car : public ige_v1::Rectangle{
public:
	
	double speed, score, life;

	Car(){};
	Car(double x, double y, double w, double h, double speed = 3);
	void set_all(double x, double y, double w, double h, double speed = 3);
};

class Road: public ige_v1::Rectangle{
public:
	double speed;
	int type;

	Road(){};
	Road(double y, double w, double h, int ty = 0, double speed = 3);
	void set_all(double y, double w, double h, int ty = 1, double speed = 3);
	void draw();
};


Car::Car(double x, double y, double w, double h, double speed) : ige_v1::Rectangle(x, y, w, h)
{
	this->speed = speed;
}

void Car::set_all(double x, double y, double w, double h, double speed)
{
	cor.x = x;
	cor.y = y;
	width = w;
	height = h;
	this->speed = speed;
}


Road::Road(double y, double w, double h, int ty, double speed):ige_v1::Rectangle(0, y, w, h)
{
	cor.x = (SCRN_WIDTH-w)/2;
	
	type = ty;
	this->speed = speed;
}

void Road::set_all(double y, double w, double h, int ty, double speed)
{
	cor.x = (SCRN_WIDTH-w)/2;
	cor.y = y;//SCRN_HEIGHT;
	width = w;
	height = h;
	type = ty;
	this->speed = speed;
}

void Road::draw()
{
	iSetColor(255, 255, 255);
		
	//left border
	iLine(cor.x, cor.y, cor.x, cor.y + height);
	iLine(cor.x-5, cor.y, cor.x-5, cor.y + height);
		
	//right border
	iLine(cor.x+width, cor.y, cor.x+width, cor.y + height);
	iLine(cor.x-5+width, cor.y, cor.x-5+width, cor.y + height);

	//middle line
	if(!type) return;
	if(type==1)
		iLine(SCRN_WIDTH/2, cor.y, SCRN_WIDTH/2, cor.y+height);
	else if(type == 2)
	{
		int h = 20;
		int n = height/h;
		int y = cor.y;
		
		for(int i = 0; i<n; ++i){
			if(i%2){
				iLine(SCRN_WIDTH/2, y, SCRN_WIDTH/2, y + h);
			}
			y += 2*h;
		}
	}
}

