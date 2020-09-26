#include "sources\table2.cpp"

namespace pages{
	class Scoreboard : public ige::Menu{
	public:
		Table tbl;

		char *txt[2];
		int state;

		void keyboard(unsigned char key);
		void update();
		void setup();
		void draw();
	};

	void Scoreboard::keyboard(unsigned char key)
	{
		if(key == 27) bt_funcs::bt_back();
		if(key == 'c' && state == 0){
			state = 1;
		}
		if(state == 1){
			if(key == 'y'){
				tbl.clear();
				scorb.clear();
				scorb.save();
				state = 0;
			}
			if(key == 'n'){
				state = 0;
			}
		}
	}

	void Scoreboard::setup()
	{
		nb = 1;
		__array_setup__();
		
		txt[0] = "* press 'c' to clear scoreboard";
		txt[1] = "** are you sure you want to clear scoreboard?(y/n)";
		state = 0;
		

		bt_w = 200;
		bt_h = 50;
		bt_gap = 25;
		bt_x = 5;
		bt_y = SCRN_HEIGHT-5-bt_h;


		fn[1] = "images//pg_scoreboard.png";
		fn[0] = "images//BACK.png";

		bt_functions[0] = bt_funcs::bt_back;

		bt[0].set_all(bt_x, bt_y, bt_w, bt_h, fn[0]);
		bt[0].setup();

		bg_image.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, fn[1]);
		bg_image.setup();

		update();
	}

	void Scoreboard::update()
	{
		tbl.rows[10].fields[0].txt = "Name";
		tbl.rows[10].fields[1].txt = "Score";
		tbl.rows[10].fields[2].txt = "Distance(km)";
		tbl.rows[10].fields[3].txt = "Duration(s)";
		tbl.rows[10].fields[4].txt = "Starting level";
		tbl.rows[10].fields[5].txt = "Finishing level";
		tbl.rows[10].fields[6].txt = "Car";

		std::multiset<backend::Row, std::greater<backend::Row> >::iterator it;
		int r = 9;
		for(it = scorb.entries.begin(); it != scorb.entries.end(); ++it){
			if(r<0)break;
			tbl.rows[r].fields[0].txt = it->name;
			tbl.rows[r].fields[1].txt = std::to_string(long long(it->score));
			tbl.rows[r].fields[2].txt = std::to_string(long double(it->dist * PX_TO_KM)); //converting into km before showing
			tbl.rows[r].fields[3].txt = std::to_string(long double(it->dur));
			tbl.rows[r].fields[4].txt = std::to_string((long long)it->start_level);
			tbl.rows[r].fields[5].txt = std::to_string((long long)it->finish_level);
			tbl.rows[r].fields[6].car_id = it->car;
			--r;
			//printf("%s\n", it->name.c_str());
		}

		tbl.setup();
		r = 9;
		for(it = scorb.entries.begin(); it != scorb.entries.end(); ++it){
			if(r<0)break;
			tbl.rows[r].fields[6].car_id = it->car;
			--r;
		}
		scorb.changed = false;
	}

	void Scoreboard::draw()
	{
		if(scorb.changed) update();

		Menu::draw();
		tbl.draw();

		iText(tbl.x, tbl.y - 50, txt[state], GLUT_BITMAP_9_BY_15); 
	}

}