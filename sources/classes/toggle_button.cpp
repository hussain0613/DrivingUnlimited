namespace ige{
	class ToggleButton
	{
	public:
		char *srcs[2];
		int img_ids[2];

		int x, y, width, height, curr_img, bt_state, id;

		void set_dim(int x, int y, int w, int h);
		void set_state(int st);
		void setup();

		bool isInside(int x, int y);
		
		void onClick(int button, int state, double x, double y, void (*func)(int state) = NULL);
		
		void draw();
	};

	void ToggleButton::set_state(int st)
	{
		bt_state = st;
		curr_img = img_ids[bt_state];
	}

	void ToggleButton::set_dim(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		width = w;
		height = h;
	}

	void ToggleButton::setup()
	{
		img_ids[0] = iLoadImage(srcs[0]);
		img_ids[1] = iLoadImage(srcs[1]);
		bt_state = 0;
		curr_img = img_ids[bt_state];
	}
	
	bool ToggleButton::isInside(int x, int y)
	{
		if(this->x < x && x < this->x + width && this->y <= y && y <= this->y + height) return true;
		else return false;
	}

	void ToggleButton::onClick(int button, int state, double x, double y, void (*func)(int state))
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(isInside(x, y)){
				bt_state = !bt_state;
				curr_img = img_ids[bt_state];
				if(func)
					func(bt_state);
				sound::settings_changed = id;

				if(settings.sfx)
					sound::bt_cl.play();
			}
		}
	}

	void ToggleButton::draw()
	{
		iShowImage(x, y, width, height, curr_img);
	}
}