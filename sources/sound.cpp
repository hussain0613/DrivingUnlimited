namespace sound{
	Mp3 mp3;
	
	const int n_music = 2, n_game_music = 2, n_env_snd = 2;
	int curr_music, curr_env, last_song, dur, n_song, song_t;
	bool change_song;
	int settings_changed;
	Mp3 musics[n_music], in_game_musics[n_game_music], environment_sounds[n_env_snd], bt_cl, bt_hov, crash_snd, level_up_snd, gm_ovr_snd;


	void toggle();

	void setup();
	void sound_controll();
	void play_song();


	void setup()
	{	
		dur = 3*60; //changable
		curr_music = rand()%n_music;
		curr_env = rand()%n_env_snd;
		change_song = true;
		settings_changed = true;

		bt_hov.fn = "audios/Click_Standard_05.mp3";
		//bt_hov.fn = "audios/MUSICiGraph/ButtonSound/snd_1.mp3";
		bt_hov.load();
		//bt_hov.set_volume(50);
		
		//bt_cl.fn = "audios/UI Sound Library/Mp3/Click_Sharp_00.mp3";
		//bt_cl.fn = "audios/snd_1.mp3";
		bt_cl.fn = "audios/click1.wav";
		bt_cl.load();


		crash_snd.fn = "audios/environment/Car+Crash.mp3";
		crash_snd.load();


		level_up_snd.fn = "audios/environment/upshort.wav";
		level_up_snd.load();


		gm_ovr_snd.fn = "audios/environment/GAMEOVER.mp3";
		gm_ovr_snd.load();


		musics[0].fn = "audios/music/its_my_life.mp3";
		musics[1].fn = "audios/music/Linkin Park - I ll Be Gone.mp3";
		for(int i = 0; i<n_music; ++i)musics[i].load();

		in_game_musics[0].fn = "audios/environment/Zander Noriega - Perpetual Tension.mp3";
		in_game_musics[1].fn = "audios/environment/one_0.mp3";
		for(int i=0; i<n_env_snd; ++i) in_game_musics[i].load();
	}

	void sound_controll()
	{
		if((time(NULL) - song_t) > dur){
			change_song = true;
		}
		if(settings_changed == 0) change_song = true;

		if(change_song){
			play_song();
			change_song = false;
			settings_changed = -1;
		}
	}


	void play_song()
	{
		
		if(curr_pg ==22){
			//for(int i = 0; i<n_music; ++i) musics[i].pause();
			
			musics[curr_music].pause();
			if(settings.gameplay_music){
				last_song = curr_env;
				while((curr_env = rand()%n_env_snd) == last_song);
			
				dur = in_game_musics[curr_env].dur;
				in_game_musics[last_song].pause();
				in_game_musics[curr_env].play();
				song_t = time(NULL);
			}
			else{
				in_game_musics[curr_env].pause();
			}


			/*last_song = curr_music;
			while((curr_music = rand()%n_music) == last_song);
			musics[curr_music].play();*/
		}

		else if (curr_pg == 24){
			musics[curr_music].pause();
			in_game_musics[curr_env].pause();

			if(settings.environment_sound)
				gm_ovr_snd.play();
		}
		else{
			
			in_game_musics[curr_env].pause();
			if(settings.menu_music){
				last_song = curr_music;
				while((curr_music = rand()%n_music) == last_song);
			
				dur = musics[curr_music].dur;
				musics[last_song].pause();
				musics[curr_music].play();
				song_t = time(NULL);
			}
			else{
				musics[curr_music].pause();
			}
		}
	}


	void toggle()
	{
		
		if(curr_pg == 22 || curr_pg == 24){
			//settings.environment_sound = !settings.environment_sound;
			settings.gameplay_music = !settings.gameplay_music;
		}
		
		else{
			settings.sfx = !settings.sfx;
			settings.menu_music = !settings.menu_music;
		}
		change_song = true;
	}
}


