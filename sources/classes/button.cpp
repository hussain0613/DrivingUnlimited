namespace ige{
	class Button: public ige::Image{// public ige::MouseInteractions{
		public:
			double nx, ny, nw, nh;
			bool hov_snd_flag;

			void setup();

			bool isInside(double x, double y);
		
			void onClick(int button, int state, double x, double y, void (*func)(void) = NULL); // prottek onClick funtion button and state add korte hbe
			void passive(double x, double y, void (*func)(void) = NULL);
			//void drag(double x, double y, void (*func)(void) = NULL){}
	};


	void Button::setup()
	{
		hov_snd_flag = true;
		
		nx = x;
		ny = y;
		nw = width;
		nh = height;
	
		ige::Image::setup();
	}

	bool Button::isInside(double x, double y)
	{
		if(this->x < x && x < this->x + width && this->y <= y && y <= this->y + height) return true;
		else return false;
	}

	void Button::onClick(int button, int state, double x, double y, void (*func)(void))
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(isInside(x, y)){
				
				if(settings.sfx)
					sound::bt_cl.play();
									
				this->x = nx;// - 5;
				this->y = ny;// - 5;
				width = nw;// + 10;
				height = nh;//+10;
				if(func)
					func();
			}
		}
	}

	void Button::passive(double x, double y, void (*func)(void))
	{
		if(isInside(x, y)){
			
			this->x = nx - 5;
			this->y = ny - 5;
			width = nw + 10;
			height = nh + 10;

			if(hov_snd_flag)
				if(settings.sfx)
					sound::bt_hov.play();
			hov_snd_flag = false;
		}
		else{
			this->x = nx;// - 5;
			this->y = ny;// - 5;
			width = nw;// + 10;
			height = nh;//+10;
			hov_snd_flag = true;
		}
	}
}

