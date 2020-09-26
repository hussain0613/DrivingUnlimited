namespace bt_funcs{
	void bt_up();
	void bt_down();
	void bt_left();
	void bt_right();
	void bt_cont();
}
namespace pages{
	class Selection : public ige::Page{
	public:
		ige::Image bg;
		ige::Button up, down, left, right, back, cont;
		ige::InputField inp;
		ige::Button2 bt_levels[5];

		/* functions for button /
		void bt_up();
		void bt_down();
		/* ... */


		int top_level, selected_car, left_car, right_car;

		void keyboard(unsigned char key);
		void specialKeyboard(unsigned char key);
		void passives(int x, int y);
		void onClicks(int button, int state, int x, int y);

		void create_labels();
		void setup();
		void draw();
	};

	void Selection::create_labels()
	{
		std::string st = "Level ";
		for(int i = top_level; i<top_level+5; ++i){
			
			bt_levels[i - top_level].txt = (char *)(st+std::to_string((long long)i)).c_str();
			bt_levels[i - top_level].set_text();
			bt_levels[i - top_level].id = i;
		}
	}

	void Selection::setup()
	{
		
		bg.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/selcetion_2.png");
		bg.setup();


		top_level = 1;
		//selected_level = 1;
		left_car = 2;
		selected_car = (left_car + 1)%CARS_Q;
		right_car = (left_car + 2) %CARS_Q;

		int y = 207, x = 215;
		for(int i = 4; i>=0; --i){
			bt_levels[i].set_all(x, y);
			bt_levels[i].setup();
			y+= 50+25;
		}
		//bt_levels[selected_level-1].active = true;
		create_labels();
		

		up.set_all(x+75, y, 50, 50, "images/BUTTON/UP.png");
		down.set_all(x+75, 207-75, 50, 50, "images/BUTTON/DOWN.png");
		
		left.set_all(800, 150, 50, 50, "images/BUTTON/LEFT.png");
		right.set_all(1200, 150, 50, 50, "images/BUTTON/RIGHT.png");

		back.set_all(20, SCRN_HEIGHT-70, 50, 50, "images/BUTTON/BACK1.png");
		cont.set_all(SCRN_WIDTH-120, SCRN_HEIGHT-70, 50, 50, "images/BUTTON/CONT.png");

		inp.set_all(0,0, 50, 50, "1");

		up.setup();
		down.setup();
		left.setup();
		right.setup();

		back.setup();
		cont.setup();

		inp.setup();
	}


	void Selection::draw()
	{
		bg.draw();
		
		for(int i = 0; i<5; ++i){
			bt_levels[i].draw();
		}


		cont.draw();
		back.draw();


		if(top_level != 1)up.draw();
		down.draw();

		
		left.draw();
		right.draw();

		
		int r = game::cars[left_car].height/game::cars[left_car].width;
		//iRectangle(800 + 25, 250, 80, 160);
		iShowImage(800 + 25, 250, 80, 80*r, game::cars[left_car].img_id);
		
		r = game::cars[selected_car].height/game::cars[selected_car].width;
		//iRectangle(933 + 25, 250, 130, 260);
		iShowImage(933 + 25, 250, 130, 130*r, game::cars[selected_car].img_id);
		
		r = game::cars[right_car].height/game::cars[right_car].width;
		//iRectangle(1116 + 25, 250, 80, 160);
		iShowImage(1116 + 25, 250, 80, 80*r, game::cars[right_car].img_id);
	}


	void Selection::passives(int x, int y)
	{
		for(int i=0; i<5; ++i){
			bt_levels[i].passive(x, y);
		}
		if(top_level != 1) up.passive(x, y);
		down.passive(x, y);

		left.passive(x, y);
		right.passive(x, y);

		back.passive(x, y);
		cont.passive(x, y);
	}
	void Selection::onClicks(int button, int state, int x, int y)
	{
		if((bt_levels[0].x <= x && x <= bt_levels[0].x+200) && (bt_levels[4].y <= y && y <= bt_levels[0].y+50)){
			for(int i=0; i<5; ++i){
				bt_levels[i].onClick(button, state, x, y);
			}
		}
		if(top_level != 1) up.onClick(button, state, x, y, bt_funcs::bt_up);
		down.onClick(button, state, x, y, bt_funcs::bt_down);

		left.onClick(button, state, x, y, bt_funcs::bt_left);
		right.onClick(button, state, x, y, bt_funcs::bt_right);

		back.onClick(button, state, x, y, bt_funcs::bt_back);
		cont.onClick(button, state, x, y, bt_funcs::bt_cont);
	}

	void Selection::keyboard(unsigned char key)
	{
		if(key == 'a') bt_funcs::bt_left();
		if(key == 'w'){
			int i = ige::Button2::selected_id;
			if(i == 1)return;
			
			if(i == top_level) bt_funcs::bt_up();
			--ige::Button2::selected_id;
		}
		if(key == 'd') bt_funcs::bt_right();
		if(key == 's'){
			int i = ige::Button2::selected_id;
			
			if(i == top_level + 4) bt_funcs::bt_down();
			++ige::Button2::selected_id;
		}

		if(key == ' ' || key == 13) bt_funcs::bt_cont();
		if(key == 27) bt_funcs::bt_back();
	}
	
	
	void Selection::specialKeyboard(unsigned char key)
	{
		if(key == GLUT_KEY_LEFT) bt_funcs::bt_left();
		
		if(key == GLUT_KEY_UP){
			
			int i = ige::Button2::selected_id;
			if(i == 1)return;
			
			if(i == top_level) bt_funcs::bt_up();
			--ige::Button2::selected_id;
		}
		if(key == GLUT_KEY_RIGHT) bt_funcs::bt_right();
		
		if(key == GLUT_KEY_DOWN){
			int i = ige::Button2::selected_id;
			
			if(i == top_level + 4) bt_funcs::bt_down();
			++ige::Button2::selected_id;
		}
		
		if(key == GLUT_KEY_PAGE_UP) if(top_level!=1)bt_funcs::bt_up();
		if(key == GLUT_KEY_PAGE_DOWN) bt_funcs::bt_down();
	}
}

pages::Selection sel;

void bt_funcs::bt_down()
{
	sel.top_level += 5;
	sel.create_labels();
}

void bt_funcs::bt_up()
{
	sel.top_level -= 5;
	sel.create_labels();
}

void bt_funcs::bt_left()
{
	if(sel.left_car==0) sel.left_car = CARS_Q-1;
	else --sel.left_car;
	sel.selected_car = (sel.left_car+1)%CARS_Q;
	sel.right_car = (sel.selected_car+1)%CARS_Q;
}

void bt_funcs::bt_right()
{
	++sel.left_car;
	sel.left_car = sel.left_car%CARS_Q;
	sel.selected_car = (sel.left_car+1)%CARS_Q;
	sel.right_car = (sel.selected_car+1)%CARS_Q;
}


void bt_funcs::bt_cont()
{
	game::player_car_index = sel.selected_car;
	game::initial_level = ige::Button2::selected_id;
	bt_play();
}
