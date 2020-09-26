namespace bt_funcs{

	void bt_play();
	void bt_inst();
	void bt_scr_brd();
	void bt_settings();
	void bt_abt_us();
	void bt_exit();

	void bt_back();

	void bt_save(); //eitar defination pg_settings.cpp te


	void bt_play()
	{
		/* demo game */
		if(curr_pg == 1) curr_pg = 21;
		else{
			sound::change_song = true;
			if(curr_pg == 21)
				game::start();
			else if(curr_pg == 23);
				game::resume();
			curr_pg = 22;
		}
		/* ... */
	}
	
	void bt_scr_brd()
	{
		curr_pg = 4;
	}
	void bt_settings()
	{
		curr_pg = 5;
	}
	void bt_inst()
	{
		curr_pg = 3;
	}
	void bt_abt_us()
	{
		curr_pg = 6;
	}
	void bt_exit(){
		settings.save();
		//scoreboard.save();
		exit(0);
	}

	void bt_back()
	{
		if(game_on && curr_pg == 23){ // int hte pause menu
			curr_pg = 1;
			//sound::change_song = true;
			game::stop();
		}
		else if(game_on){ // in game
			curr_pg = 23;
			//sound::change_song = true;
		}
		else curr_pg = 1;
	}

	void bt_save()
	{
		settings.save();
	}
}