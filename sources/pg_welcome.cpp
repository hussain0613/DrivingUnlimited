namespace pages{
	class Welcome : public ige::Page{
	public:
		ige::Image bg, flash_msg;
		int timer_id;
		
		static bool flash;

		static void timer_func();

		void setup();
		void keyboard(unsigned char key);
		void draw();
	};

	void Welcome::timer_func()
	{
		Welcome::flash = !Welcome::flash;
	}
	void Welcome::setup()
	{
		bg.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images//WTDU.jpg");
		bg.setup();
		
		int mw = 707, mh = 168;
		//flash_msg.set_all((SCRN_WIDTH-mw)/2, 50, mw, mh, "images//welcome_flash_msg.png");
		flash_msg.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images//welcome_flash_msg_v6.png");
		flash_msg.setup();

		Welcome::flash = true;
		timer_id = iSetTimer(1000, Welcome::timer_func);
	}

	void Welcome::keyboard(unsigned char key)
	{
		if(key == 13 || key == 32){
			curr_pg = 1; // eikhane ektu karsaji korle eita jekono jaygay bebohar kora jaabe
			iPauseTimer(timer_id);
		}
	}

	void Welcome::draw()
	{
		bg.draw();
		
		if(Welcome::flash)
			flash_msg.draw();
	}

	bool Welcome::flash = true;
}

