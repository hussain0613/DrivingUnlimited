namespace pages{

	class MainMenu : public ige::Menu{
	public:
		void setup();
	};

	void MainMenu::setup()
	{
		nb = 6; //+2
		__array_setup__();

		bt_w = 200;
		bt_h = 50;
		bt_gap = 25;
		bt_x = (SCRN_WIDTH-bt_w)/2.0;
		bt_y = (SCRN_HEIGHT-(bt_h*nb+(nb-1)*bt_gap))/2.0;
		
		int i = 0;
		
		/*fn[i++] = "images/main_menu/play_bt.png";
		fn[i++] = "images/main_menu/inst_bt.png";
		fn[i++] = "images/main_menu/sr_brd_bt.png";
		fn[i++] = "images/main_menu/settings_bt.png";
		fn[i++] = "images/main_menu/abt_us_bt.png";
		fn[i++] = "images/main_menu/exit.png";
		fn[i++] = "images/main_menu/menu_bg.png";*/

		fn[i++] = "images/main_menu2 - Copy/PLAY.png";
		fn[i++] = "images/main_menu2 - Copy/INS.png";
		fn[i++] = "images/main_menu2 - Copy/SB.png";
		fn[i++] = "images/main_menu2 - Copy/SETTINGS.png";
		fn[i++] = "images/main_menu2 - Copy/ABOUTUS.png";
		fn[i++] = "images/main_menu2 - Copy/EXIT.png";
		fn[i++] = "images/main_menu2 - Copy/BACKGROUND.jpg";

		for(i = nb-1; i>=0; --i){
			bt[i].set_all(bt_x, bt_y, bt_w, bt_h, fn[i]);
			
			bt[i].setup();
			
			bt_y += bt_h + bt_gap;
			//printf("%.2f\n", bt_y);
		}
		//bt[i].set_all(0,0,SCRN_WIDTH, SCRN_HEIGHT, fn[i]);
		//bt[i].setup();

		i = 0;
		
		bt_functions[0] = bt_funcs::bt_play;
		bt_functions[1] = bt_funcs::bt_inst;
		bt_functions[2] = bt_funcs::bt_scr_brd;
		bt_functions[3] = bt_funcs::bt_settings;
		bt_functions[4] = bt_funcs::bt_abt_us;
		bt_functions[5] = bt_funcs::bt_exit;

		bg_image.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, fn[nb]);
		bg_image.setup();
	}

}