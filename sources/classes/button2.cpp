namespace ige{
	class Button2{
		public:
			static int selected_id;
			std::string txt;
			
			int color[3], active_color[3];
			int id;

			double x, y, width, height, tx, ty;
			bool hov_snd_flag, active, hov;


			void set_all(int x, int y, int w = 200, int h = 50, char *t = "Button");
			void set_text();
			void setup();

			bool isInside(double x, double y);
		
			void onClick(int button, int state, double x, double y, void (*func)(void) = NULL); // prottek onClick funtion button and state add korte hbe
			void passive(double x, double y, void (*func)(void) = NULL);
			
			void draw();
	};


	void Button2::set_all(int x, int y, int w, int h, char *t)
	{
		this->x = x;
		this->y = y;
		width = w;
		height = h;

		txt = t;
	}

	void Button2::set_text()
	{
		tx = x + (width-9*txt.size())/2;
		ty = y + (height - 15)/2;
	}

	void Button2::setup()
	{
		hov_snd_flag = true;
		active = false;
		hov = false;

		color[0] = 50;
		color[1] = 50;
		color[2] = 50;

		active_color[0] = 100;
		active_color[1] = 100;
		active_color[2] = 100;

		set_text();
	}

	bool Button2::isInside(double x, double y)
	{
		if(this->x < x && x < this->x + width && this->y <= y && y <= this->y + height) return true;
		else return false;
	}

	void Button2::onClick(int button, int state, double x, double y, void (*func)(void))
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(isInside(x, y)){
				//active = true;
				selected_id = id;
				if(settings.sfx)
					sound::bt_cl.play();
									
				if(func)
					func();
			}
			//else active = false;
		}
	}

	void Button2::passive(double x, double y, void (*func)(void))
	{
		if(isInside(x, y)){
			
			hov = true;
			if(hov_snd_flag)
				if(settings.sfx)
					sound::bt_hov.play();
			hov_snd_flag = false;
		}
		else{
			hov = false;
			hov_snd_flag = true;
		}
	}

	void Button2::draw()
	{
		if(selected_id == id || hov)iSetColor(active_color[0], active_color[1], active_color[2]);
		else iSetColor(color[0], color[1], color[2]);
		iFilledRectangle(x, y, width, height);
		
		iSetColor(250, 250, 250);
		iText(tx, ty, (char *)txt.c_str());
	}
	int Button2::selected_id = 1;
}

