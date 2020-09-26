namespace pages{
	class GameOver: public ige::Page{
	public:
		ige::Image bg_img;
		ige::InputField inpf;

		void onClicks(int button, int state, int x, int y);
		void keyboard(unsigned char key);

		void setup();
		void draw();
	};

	void GameOver::onClicks(int button, int state, int x, int y)
	{
		inpf.onClick(button, state, x, y);
	}

	void GameOver::keyboard(unsigned char key)
	{
		if(inpf.active)
			inpf.keyboard(key);
		
		else if(key == 13) {
			game::row.name = inpf.text;
			scorb.add(game::row);
			scorb.save();

			sound::gm_ovr_snd.pause();
			sound::change_song = true;
			curr_pg = 1;
		}
	}

	void GameOver::setup(){
		bg_img.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/game_over.png");
		bg_img.setup();

		inpf.set_all(730 , 285, 200, 25, (char *) settings.name.c_str());
		inpf.setup();
	}

	void GameOver::draw(){
		game::draw();
		
		bg_img.draw();

		iText(730, 403+5, (char *) std::to_string((long long) game::score ).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);//score
		iText(730, 361+5, (char *) std::to_string((long double) game::dist*(PX_TO_KM)).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);//distance
		iText(730, 321+5, (char *) std::to_string((long double) game::dur).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);//duration
		
		inpf.draw();
	}
}