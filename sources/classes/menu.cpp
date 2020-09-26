#include<stdlib.h>

namespace ige{

	class Menu: public ige::Page{
		public:
		
		int nb;
		double bt_x, bt_y, bt_gap, bt_w, bt_h;
		
		char **fn;
		Button *bt;
		
		void (**bt_functions)(void);

		ige::Image bg_image;

		void __array_setup__();
		
		void setup(); // will setup everything necessary
	
		void passives(int x, int y);
		void onClicks(int button, int state, int x, int y); //jeikhane kaaj hbe sheikhane eitar function define kora hobe.. preferbly in the namespace
		void drag(int x, int y){};

		void keyboard(unsigned char key);
		void specialKeyboard(unsigned char key);

		void draw(); // will draw the page.. i.e. show the page
	};


	void Menu::__array_setup__(){
		fn = (char**) malloc(sizeof(char*)*nb);
		bt = (ige::Button*) malloc(sizeof(ige::Button)*nb);
		bt_functions = (void (**)(void)) malloc(sizeof(  void (*)(void)  ) * nb);
	}

	void Menu::passives(int x, int y)
	{
		for(int i = 0; i<nb; ++i){
			bt[i].passive(x, y);
		}
	}

	void Menu::onClicks(int button, int state, int x, int y)
	{
		for(int i = 0; i<nb; ++i){
			bt[i].onClick(button, state, x, y, bt_functions[i]);
		}
	}

	void Menu::draw()
	{
		bg_image.draw();
		
		for(int i = 0; i<nb; ++i){
			bt[i].draw();
		}
	}
}