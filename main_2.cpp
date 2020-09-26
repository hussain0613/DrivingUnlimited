#include<stdio.h>
#include<Windows.h>

#include "sources/iGraphicsHeaders/iGraphics_3.h"


#define SCRN_WIDTH 1360
#define SCRN_HEIGHT 765

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3



int curr_pg;
bool paused, game_on;


#include "sources\settings_backend.cpp"
#include "sources\scoreboard_backend2.cpp"

backend::Settings settings;
backend::Scoreboard scorb;


#include "sources\mp3.cpp"

#include "sources\sound.cpp"


#include "sources\classes\image.cpp"
//#include "sources\classes\interactions.cpp"
#include "sources\classes\page.cpp"
#include "sources\classes\button.cpp"
#include "sources\classes\button2.cpp"
#include "sources\classes\menu.cpp"
#include "sources\classes\input_filed.cpp" // field banan thik korte hbe
#include "sources\classes\toggle_button.cpp"
//#include "sources\table.cpp"


/* skeletal demo */
//#include "sources\racing_basic_demo\test.cpp"

#include "sources\theGame\game_6.cpp"
/*...*/


#include "sources\bt_functions.cpp"

#include "sources\pg_mainMenu.cpp"
#include "sources\pg_instructions.cpp"
#include "sources\pg_abt_us.cpp"
#include "sources\pg_welcome.cpp"
#include "sources\pg_settings.cpp"
#include "sources\pg_scoreboard2.cpp"
// game over page - options thakbe finish, retry from start level, retry from last level
#include "sources\pg_pause_menu.cpp"
#include "sources\pg_gameOver.cpp"
#include "sources\pg_selection.cpp"

pages::MainMenu menu;
pages::Instructions inst;
pages::About abt;
pages::Welcome wlcm;
pages::Settings st;
pages::Scoreboard scrb;
pages::PauseMenu pmenu;
pages::GameOver go;
//pages::Selection sel;


void iDraw()
{
	iClear();
	
	sound::sound_controll();

	switch(curr_pg)
	{
		case 0:
			wlcm.draw();
			break;
		case 1:
			menu.draw();
			break;

		case 3:
			inst.draw();
			break;
		case 4:
			scrb.draw();
			break;
		case 5:
			st.draw();
			break;
		case 6:
			abt.draw();
			break;
		/* demo game */
		case 21:
			sel.draw();
			break;
		case 22:
			game::draw();
			break;
		case 23:
			pmenu.draw();
			break;
		case 24:
			go.draw();
		/* ... */
	}

}

void iPassiveMouse(int x, int y)
{
	switch(curr_pg)
	{
		case 1:
			menu.passives(x, y);
			break;
		case 3:
			inst.passives(x, y);
			break;
		case 4:
			scrb.passives(x, y);
			break;
		case 5:
			st.passives(x, y);
			break;
		case 6:
			abt.passives(x, y);
			break;
		/* demo game */
		case 21:
			sel.passives(x, y);
			break;
		case 23:
			pmenu.passives(x, y);
			break;
		/* ... */
	}
}
void iMouse(int button, int state, int x, int y)
{
	switch(curr_pg)
	{
		case 1:
			menu.onClicks(button, state, x, y);
			break;
		case 3:
			inst.onClicks(button, state, x, y);
			break;
		case 4:
			scrb.onClicks(button, state, x, y);
			break;
		case 5:
			st.onClicks(button, state, x, y);
			break;
		case 6:
			abt.onClicks(button, state, x, y);
			break;
		/* demo game */
		case 21:
			sel.onClicks(button, state, x, y);
			break;
		case 23:
			pmenu.onClicks(button, state, x ,y);
			break;
		case 24:
			//printf("%d %d\n", x, y);
			go.onClicks(button, state, x, y);
			break;
		/* ... */
	}
}

void iMouseMove(int x, int y){}

void iKeyboard(unsigned char key)
{
	switch(curr_pg)
	{
		case 0:
			wlcm.keyboard(key);
			break;
		case 4:
			scrb.keyboard(key);
			break;
		case 5:
			st.keyboard(key);
			break;
		case 21:
			sel.keyboard(key);
			break;
		case 22:
			game::keyboard(key);
			break;
		case 23:
			if(key == 27)
				bt_funcs::bt_play();
			break;
		case 24:
			go.keyboard(key);
			break;
		default:
			if(key == 27)
				bt_funcs::bt_back();
	}
}
void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_F1){
		if(game_on && !paused) game::pause();
		curr_pg = 3;//instruction page
	}
	if(key == GLUT_KEY_F2){
		if(game_on && !paused) game::pause();
		curr_pg = 5; //settings page
	}
	if(key == GLUT_KEY_F3) sound::change_song = true;
	if(key == GLUT_KEY_F4) sound::toggle();
	
	switch(curr_pg){
	/* demo game */
		case 21:
			sel.specialKeyboard(key);
			break;
		case 22:
			game::specialKeyboard(key);
			break;
	/* ... */
	}
}

void hKeyboardUp(unsigned char key){
	/*
	if(curr_pg == 5){
		st.keyboardUp(key);
	}
	*/
	if(curr_pg){
		game::keyboardUp(key);
	}
}

void hSpecialKeyboardUp(int key)
{
	if(curr_pg == 22){
		game::specialKeyboardUp(key);
	}
}

int main()
{
	curr_pg = 0;
	

	settings.file_name = "data\\settings.csv";
	settings.load();
	scorb.src = "data\\scoreboard.csv";
	scorb.load();

	sound::setup();

	iInitialize(SCRN_WIDTH, SCRN_HEIGHT, "Driving Unlimited");
	
	menu.setup();
	inst.setup();
	abt.setup();
	wlcm.setup();
	st.setup();
	scrb.setup();

	/* demo game */
	game::setup();
	sel.setup();
	go.setup();
	
	pmenu.setup();
	/* ... */
	
	game_on = false;

	/*srand(time(NULL));
	curr_song = rand()%n_song;
	if (settings.menu_music){
		sound::play_song();
	}*/
	
	sound::sound_controll();
	
	iStart();
}

