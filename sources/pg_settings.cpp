#include<string>
namespace pages{
	class Settings : public ige::Page{
	public:
		//backend::Settings stats;

		ige::Image bg;

		ige::InputField field;
		
		char **lebels;// *inst, **fn;
		

		void (**tg_funcs)(int state);
		void (*back_f)(void);
		void (*save_f)(void);

		
		int bt_x, bt_y, bt_gap, bt_w, bt_h;

		int ntb;
		ige::ToggleButton *bt;
		ige::Button back, save;

		
		void __array_setup__();
		void setup();
	
		void passives(int x, int y);
		void onClicks(int button, int state, int x, int y);
		//void drag(int x, int y);

		void keyboard(unsigned char key);
		//void specialKeyboard(unsigned char key);

		void draw();
	};


	void Settings::__array_setup__()
	{
		lebels = (char**) malloc(sizeof(char*)*ntb + 1);
		
		bt = (ige::ToggleButton*) malloc(sizeof(ige::ToggleButton)*ntb);
		tg_funcs = (void (**)(int)) malloc(sizeof(  void (*)(int)  ) * ntb);
	}

	void Settings::setup()
	{
		ntb = 4;

		__array_setup__();
		
		bt_w = 200;
		bt_h = 50;
		bt_gap = 25;
				

		// background setup
		bg.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images//main_menu2 - Copy//BACKGROUND.jpg");
		bg.setup();

		
		// back button setup
		bt_x = 5;
		bt_y = SCRN_HEIGHT-5-bt_h;

		back_f = bt_funcs::bt_back;
		back.set_all(bt_x, bt_y, bt_w, bt_h, "images//BACK.png");
		back.setup();

		
		//save button setup

		bt_x = (SCRN_WIDTH - bt_w)/2;
		bt_y = (SCRN_HEIGHT-(bt_h*(ntb+1)+(ntb)*bt_gap))/2.0;
		bt_y -= (100 + bt_h);

		save_f = bt_funcs::bt_save; //eita pore thik korte hbe

		save.set_all(bt_x, bt_y, bt_w, bt_h, "images//SAVE.png");
		save.setup();

		// lebel setup
		lebels[0] = "Name";
		lebels[1] = "Menu Music";
		lebels[2] = "SFX";
		lebels[3] = "Gameplay Music";
		lebels[4] = "Environment Sound";
		
		
		//toggle buttons
		
		bt_x = (SCRN_WIDTH-(bt_w + 600 + 50))/2.0 + 600+50;
		bt_y = (SCRN_HEIGHT-(bt_h*(ntb+1)+(ntb)*bt_gap))/2.0;
		
		for(int i = ntb-1; i>=0; --i){
			bt[i].id = i;
			bt[i].set_dim(bt_x, bt_y, bt_w, bt_h);
			
			bt[i].srcs[0] = "images//off.png";
			bt[i].srcs[1] = "images//on.png";
			bt[i].setup();
			
			bt_y += bt_h + bt_gap;
		}
		bt[0].set_state(settings.menu_music);
		bt[1].set_state(settings.sfx);
		bt[2].set_state(settings.gameplay_music); // eita thik korte hobe
		bt[3].set_state(settings.environment_sound);
		
		//button gulay fucntions add korte hbe. // nope

		// input field setup
		field.set_all(bt_x, bt_y, bt_w, bt_h, (char*)settings.name.c_str());
		field.setup();

		// instruction setup

		
	}

	void Settings::passives(int x, int y)
	{
		back.passive(x, y);
		save.passive(x, y);
	}

	void Settings::onClicks(int button, int state, int x, int y)
	{
		back.onClick(button, state, x, y, back_f);
		
		for(int i = 0; i<ntb; ++i){
			bt[i].onClick(button, state, x, y);// tg_funcs[i]);
		}
		field.onClick(button, state, x, y); // pore add korte hobe

		
		settings.menu_music = bt[0].bt_state;
		settings.sfx = bt[1].bt_state;
		settings.gameplay_music = bt[2].bt_state;
		settings.environment_sound = bt[3].bt_state;


		save.onClick(button, state, x, y, save_f);
	}

	void Settings::keyboard(unsigned char key)
	{
		if(field.active == true){
			field.keyboard(key);
			settings.name = field.text;
		}
		else{
			if(key == 27) bt_funcs::bt_back();
			else if(key == 13) settings.save();
		}
	}

	void Settings::draw()
	{
		bg.draw();

		back.draw();

		for(int i = 0; i<ntb; ++i){
			bt[i].draw();
		}

		field.draw();
		//lebel gula baaki aase // ekhon ar nai
		bt_x = (SCRN_WIDTH-(bt_w + 600 + 50))/2.0;
		bt_y = (SCRN_HEIGHT-(bt_h*(ntb+1)+(ntb)*bt_gap))/2.0;
		
		for(int i = ntb; i>=0; --i){
			iSetColor(50, 50, 50);
			iFilledRectangle(bt_x, bt_y, 300, bt_h);
			
			iSetColor(250, 250, 250);
			iText(bt_x+30, bt_y+17, lebels[i], GLUT_BITMAP_TIMES_ROMAN_24);
			bt_y += bt_h + bt_gap;
		}
		save.draw();
	}
}