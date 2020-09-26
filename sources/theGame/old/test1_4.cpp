
namespace game{

#define NPC_Q 4
#define MX_NPC_Q 15
#define MX_LIFE 5
#define CARS_Q 7
#define RD_Q 5
	
	class Road{
	public:
		int x, y;
		int left, right, mid, quarter;

		void draw()
		{
			//iShowImage(x,y, SCRN_WIDTH, SCRN_HEIGHT, asphalt);
			
			iShowImage(x,y, SCRN_WIDTH, SCRN_HEIGHT, left);
			iShowImage(x,y, SCRN_WIDTH, SCRN_HEIGHT, right);
			
			iShowImage(x, y, SCRN_WIDTH, SCRN_HEIGHT, mid);

			if(quarter>-1) iShowImage(x,y, SCRN_WIDTH, SCRN_HEIGHT, quarter);
		}
	};

	class Car {
	public:
		int x, y, w, h;
		int speed, ac;
		int car_id;
		ige::Image car;

		void draw(){
			//iShowImage(x,y, w, h, car_id);
			car.draw();
		}
	};
	
	
	int collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
	
	void controll_player_speed();
	void player_movement();
	void player_collision_check();

	// debug er jonno eta
	void special_npc_col_check();
	
	void visibility();
	
	void load_images();
	
	void spawn_road(int index, int tier);
	void road_movement();


	void npc_gen();
	void npc_spawn_left(int i);
	void npc_spawn_right(int i);
	void npc_movement();


	void setup();
	void start();
	void pause();
	void resume();
	void stop();
	void game_over();

	void keyboard(int key);
	void specialKeyboardUp(int key);
	void specialKeyboard(int key);
	void draw();



	//int loaded = 0, state=0, timers_ini, 
	int road_timer, min_speed, max_speed, player_speed, ac, rd_x1, rd_x2; // level main theke othoba bahir theke initialize korte hbe
	int level, initial_level, dLevel;
	int score, life, last_hit, active_npc_q;
	int player_car_index;
	int sc_timer;
	int frame = 0;

	/* game over er por score save er jono */
	backend::Row row;

	bool visible;
	int vis_timer_id;

	ige::Image rd_asphalt, rd_lefts[2], rd_rights[2], rd_mids[3], rd_quarter, cars[CARS_Q], cars_f[CARS_Q];
	Road roads[RD_Q];
	Car player, npc_left[MX_NPC_Q], npc_right[MX_NPC_Q];

	double theta; //test_drive

	bool arrow_states[4];


	void load_images()
	{
		//needs no rendering
		rd_asphalt.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_asphalt.png");
		rd_asphalt.setup();


		// needs rendering
		rd_lefts[0].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_scene_left_1.png");
		rd_lefts[0].setup();

		rd_lefts[1].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_scene_left_2.png");
		rd_lefts[1].setup();

		rd_rights[0].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_scene_right_1.png");
		rd_rights[0].setup();

		rd_rights[1].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_scene_right_2.png");
		rd_rights[1].setup();

		rd_mids[0].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_line_middle_1.png");
		rd_mids[0].setup();

		rd_mids[1].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_line_middle_2.png");
		rd_mids[1].setup();

		rd_mids[2].set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_line_middle_3.png");
		rd_mids[2].setup();

		rd_quarter.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, "images/roads/road_line_quarter_2.png");
		rd_quarter.setup();

		// cars
		cars[0].set_all(0, 0, 37, 80, "images/cars/car_1.png");
		
		cars[1].set_all(0, 0, 37, 80, "images/cars/car_2.png");
		
		cars[2].set_all(0, 0, 39, 85, "images/cars/car_3.png");
		
		cars[3].set_all(0, 0, 37, 75, "images/cars/car_4.png");
		
		cars[4].set_all(0, 0, 44, 93, "images/cars/car_5.png");
		
		cars[5].set_all(0, 0, 44, 90, "images/cars/car_6.png");
		
		cars[6].set_all(0, 0, 39, 80, "images/cars/car_7.png");
		

		// cars_flipped
		cars_f[0].set_all(0, 0, 37, 80, "images/cars/car_1f.png");
		
		cars_f[1].set_all(0, 0, 37, 80, "images/cars/car_2f.png");
		
		cars_f[2].set_all(0, 0, 39, 85, "images/cars/car_3f.png");
		
		cars_f[3].set_all(0, 0, 37, 75, "images/cars/car_4f.png");
		
		cars_f[4].set_all(0, 0, 44, 93, "images/cars/car_5f.png");
		
		cars_f[5].set_all(0, 0, 44, 90, "images/cars/car_6f.png");
		
		cars_f[6].set_all(0, 0, 39, 80, "images/cars/car_7f.png");
		
		for(int i = 0; i<CARS_Q; ++i){
			cars[i].setup();
			cars_f[i].setup();
		}
	}
	

	void spawn_road(int i, int tier){
		
		roads[i].left = rd_lefts[rand()%2].img_id;
		roads[i].right = rd_rights[rand()%2].img_id;
		
		roads[i].mid = rd_mids[rand()%3].img_id;
		
		roads[i].quarter = (rand()%2<1)? rd_quarter.img_id: -1;


		roads[i].x = 0;
		if(tier == -1){
			if(i== (RD_Q-1)) roads[i].y = roads[0].y - SCRN_HEIGHT;
			else roads[i].y = roads[i+1].y - SCRN_HEIGHT - player_speed;
		}
		else if(0<=tier && tier<RD_Q){
			roads[i].y = SCRN_HEIGHT*(tier-2);
		}
		
		else if (tier >= RD_Q){
			if(i == 0) roads[i].y = (roads[RD_Q-1].y + SCRN_HEIGHT - player_speed);
			else roads[i].y = roads[i-1].y + SCRN_HEIGHT;	
		}
		
	}

	void road_movement()
	{
		for(int i = 0; i<RD_Q; ++i){
			roads[i].y -= (player_speed);
			if(roads[i].y < -2*SCRN_HEIGHT) spawn_road(i, RD_Q);
			else if(roads[i].y > 2*SCRN_HEIGHT) spawn_road(i, -1);
			
			if(player.car.y < player.y && !arrow_states[GLUT_KEY_DOWN - 100]) roads[i].y += 1;
			if(player.car.y > player.y && !arrow_states[GLUT_KEY_UP - 100]) roads[i].y -= 1;
		}
	}


	int collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
	{
		if(x1 > x2+w2 || x2 > x1+w1) return 0; // not colliding and one is on the left/right of the other entirely
		else{
			if(y1>y2+h2) return 2; // car1 car2 er upore
			else if(y2>y1+h1) return -2; //car1 car2 er niche
			else return 1; //they are colliding
		}
	}

	void controll_player_speed()
	{
		if(arrow_states[GLUT_KEY_UP-100]){
			if (player_speed+1 <= max_speed) player_speed += 1;
		}
		if(arrow_states[GLUT_KEY_DOWN-100]){
			if(player_speed-1 >= -min_speed) player_speed -= 1;
		}
	}

	void player_movement(){
		bool side = false;
		int var = 0;

		if(arrow_states[GLUT_KEY_UP-100]){
			side = true;
			var = 1;
			
			if((player.car.y+player.car.height) < (SCRN_HEIGHT-250))
				player.car.y += 2;
		}
		if(arrow_states[GLUT_KEY_DOWN-100]){
			side = true;
			var = -1;
			
			if(player.car.y >= 150)
				player.car.y -= 2;
		}
		
		if(player.car.y != player.y) side = true;

		if(arrow_states[GLUT_KEY_RIGHT-100]) {
			if(theta > -3 && var != -1) theta -= .2;
			else if(theta < 3 && var == -1) theta += .2;

			if(side){
				if(player.car.x+player.car.width*1.5 < rd_x2)
					player.car.x += 3;
			}
		}
		else{
			if(theta < 0) theta += .1;
		}

		if(arrow_states[GLUT_KEY_LEFT-100]) {
			if(theta < 3 && var!=-1) theta += .2;
			else if(theta >-3 && var == -1) theta -= .2;

			if(side){
				if(player.car.x - (player.car.width/2) >= rd_x1)
					player.car.x -= 3;
			}
		}
		else{
			if(theta>0) theta -= .1;
		}

		if(!var && player.car.y < player.y){
			++player.car.y;
		}
			
		if(!var && player.car.y > player.y) 
			--player.car.y;
		
		side = false;
		var = false;
	}


	void player_collision_check()
	{
		if(time(NULL)-last_hit<2) return;
		
		int i;
		for(i = 0; i < active_npc_q; ++i){
			if(collide(player.car.x, player.car.y, player.car.width, player.car.height, npc_left[i].car.x, npc_left[i].car.y, npc_left[i].car.width, npc_left[i].car.height) == 1){
				if(settings.environment_sound)
					sound::crash_snd.play();

				player.car. x = player.x;
				player.car.y = player.y;
				last_hit = time(NULL);
				score -= 25;
				--life;
			}
			if(collide(player.car.x, player.car.y, player.car.width, player.car.height, npc_right[i].car.x, npc_right[i].car.y, npc_right[i].car.width, npc_right[i].car.height) == 1){
				if(settings.environment_sound)
					sound::crash_snd.play();

				player.car. x = player.x;
				player.car.y = player.y;
				last_hit = time(NULL);
				score -= 25;
				--life;
			}
		}
	}

	void visibility()
	{
		if(time(NULL) - last_hit< 2){
			visible = !visible;
		}
		else visible = true;
	}

	void scorer()
	{
		if(game_on && !paused){
			score += (double)level*((double)abs(player_speed)/(double)max_speed);
			if((dLevel+1)*(dLevel * .25 +1 ) * 500 <= score) {
				if(settings.environment_sound)
					sound::level_up_snd.play();

				if(life<MX_LIFE && dLevel%3) ++life;
				if(active_npc_q < MX_NPC_Q) ++active_npc_q;
				
				++level;
				++dLevel;
				++min_speed;
				++max_speed;
			}
		}
	}


	void npc_gen()
	{
		for(int i = 0; i< MX_NPC_Q; ++i){
			npc_spawn_left(i);
			npc_spawn_right(i);
		}
	}
	
	void npc_spawn_left(int i)
	{
		//int dy = max_speed+1;

		Car car;
		int x, y, w, h, speed, flag, x2, y2, w2, h2, speed2;

		int ind;
		while((ind = rand()%CARS_Q) == player_car_index);
		car.car = cars[ind];
		
		w = car.car.width;
		h = car.car.height;

		speed = rand()%(max_speed - min_speed)+min_speed;
		x = rand()%(675-30-rd_x1-25) + rd_x1+25; //in_between rd_x+25 and 675-30 px
		
		if(speed>player_speed) y = -(rand()%SCRN_HEIGHT+100); // in between -SCRN_HEIGHT and -100
		else y = (rand()%(int)(SCRN_HEIGHT*1.5) + SCRN_HEIGHT);

		//for(int j = 0; j<MX_NPC_Q; ++j){
		for(int j = 0; j<active_npc_q; ++j){
			if(j != i){
				x2 = npc_left[j].car.x;

				y2 = npc_left[j].car.y;
				
				w2 = npc_left[j].car.width;
				h2 = npc_left[j].car.height;
				speed2 = npc_left[j].speed;

				flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
				while(flag){ //flag = 0 hoile ok.. otherwise kaaj korte hbe
					if(flag == 1){ // 1 hoile full collision
						x = rand()%(675-rd_x1-25) + rd_x1+25;
						if(speed > player_speed) y = -(rand()%SCRN_HEIGHT+100); // in between -SCRN_HEIGHT and -100
						else y = (rand()%SCRN_HEIGHT*2 + SCRN_HEIGHT);
						flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
						j =-1;
					}
					else{ // not full collision but chances are they may collide in near future
						if(flag == 2 && speed < speed2){ // car1 car2 er upore.. so car1 er speed kom hoile hbe na..
							speed = speed2;
							flag = 0; // as car1 ar car er collison er ar kono chance nai
						}
						else if(flag == -2 && speed>speed2) {// car1 car2 er niche.. so car1 er speed beshi hoile cholbe na
							speed = speed2;
							flag = 0; // as car1 ar car er collison er ar kono chance nai
						}
						else flag = 0; // as car1 ar car er collison er ar kono chance nai
					}
				}
			}
		}
		
		car.car.x = x;//in_between rd_x and 675 px
		car.car.y = y; // in between -SCRN_HEIGHT and -100
		car.speed = speed;

		
		npc_left[i] = car;
	}
	
	void npc_spawn_right(int i)
	{
		Car car;
		int x, y, w, h, speed, flag, x2, y2, w2, h2, speed2;

		int ind;
		while((ind = rand()%CARS_Q) == player_car_index);
		car.car = cars_f[ind];
		
		w = car.car.width;
		h = car.car.height;

		
		speed = rand()%(max_speed - min_speed)+min_speed; //base speed ,+2 to make sure speed is more than road*/
		x =  rand()%(rd_x2-30 - 690 - w) + 690;//in_between 690 and rd_x2-30 px
		y = (rand()%SCRN_HEIGHT + SCRN_HEIGHT); // in between SCRN_HEIGHT and SCRN_HEIGHT*2

		//for(int j = 0; j<MX_NPC_Q; ++j){
		for(int j = 0; j<active_npc_q; ++j){
			if(j != i){
				x2 = npc_right[j].car.x;
				
				y2 = npc_right[j].car.y;
				
				w2 = npc_right[j].car.width;
				h2 = npc_right[j].car.height;
				speed2 = npc_right[j].speed;

				flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
				while(flag){ //flag = 0 hoile ok.. otherwise kaaj korte hbe
					if(flag == 1 ){ // 1 hoile full collision
						x = rand()%(rd_x2 - 30 - 690 - w) + 690;
						y = (rand()%SCRN_HEIGHT + SCRN_HEIGHT);
						flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
						j=-1;
					}
					else{ // not full collision but chances are they will collide in near future
						if(flag == 2 && speed > speed2){ // car1 car2 er upore.. so car1 er speed beshi hoile hbe na..
							speed = speed2;
							flag = 0; // as car1 ar car er collison er ar kono chance nai
						}
						else if(flag == -2 && speed < speed2) {// car1 car2 er niche.. so car1 er speed kom hoile cholbe na
							speed = speed2;
							flag = 0; // as car1 ar car er collison er ar kono chance nai
						}
						else flag = 0; // as car1 ar car er collison er ar kono chance nai
					}
				}
			}
		}
		
		car.speed = speed;
		car.car.x = x;
		car.car.y = y; 

		car.x = x;
		car.y = y; 

		npc_right[i] = car;
	}
	
	void npc_movement()
	{
		int dy;
		//left side
		for(int i=0; i < active_npc_q; ++i){
			dy = (npc_left[i].speed - ac - player_speed);
			
			if(npc_left[i].car.y > 2.5*SCRN_HEIGHT) {
				npc_spawn_left(i); 
				score += 2;
			}
			
			if( (npc_left[i].car.y+npc_left[i].car.height < -.75*SCRN_HEIGHT) && dy<0) {
				npc_spawn_left(i); 
				score += 2;
			}

			npc_left[i].car.y += dy;
		}
		// right side
		for(int i=0; i < active_npc_q; ++i){
			
			if(npc_right[i].car.y+npc_right[i].car.height < -SCRN_HEIGHT) {
				npc_spawn_right(i); 
				score += 2;
			}

			npc_right[i].car.y -= (npc_right[i].speed + player_speed + ac);
		}

		//special_npc_col_check();
	}

	void rd_npc_movement()
	{
		if(game_on && !paused){
			npc_movement();
			road_movement();
			player_movement();

			if(ac>0) --ac;
			else if(ac<0) ++ac;
		}

		//scorer();
	}

	void keyboardUp(int key){}

	void keyboard(int key)
	{
		if(key == 27){
			pause();
		}
	}

	void specialKeyboard(int key)
	{
		if(100 <= key && key<=103)
			arrow_states[key-100] = true;
	}
	void specialKeyboardUp(int key){
		if(100 <= key && key<=103)
			arrow_states[key-100] = false;
	}

	void setup()
	{
		arrow_states[0] = 0;
		arrow_states[1] = 0;
		arrow_states[2] = 0;
		arrow_states[3] = 0;

		load_images();

		last_hit = 0;
		min_speed = 5; level = 1; ac = 0; max_speed = 10;
		initial_level = 1;
		dLevel = level - initial_level;
		player_speed = 0;
		
		if(NPC_Q +level <= MX_NPC_Q) active_npc_q = NPC_Q +level;
		else active_npc_q = MX_NPC_Q;

		paused = true;

		rd_x1 = 263;
		rd_x2 = 1097;

		score = 0;
		life = 3;
		
		printf("[*] Game has been setup\n");
	}

	void start()
	{
		theta = 0;

		arrow_states[0] = 0;
		arrow_states[1] = 0;
		arrow_states[2] = 0;
		arrow_states[3] = 0;

		
		level = 1; // eita level selection theke thik kore dite hbe
		initial_level = level;
		dLevel = level - initial_level;
		
		min_speed = 3 + level; ac = 0; max_speed = 20 + level;
		
		if(NPC_Q +level <= MX_NPC_Q) active_npc_q = NPC_Q +level;
		else active_npc_q = MX_NPC_Q;

		player_speed = 0;//(min_speed+max_speed)/2;
		score = 0;
		life = 3;

		for(int i = 0; i<RD_Q; ++i){
			spawn_road(i, i);
		}
		
		player_car_index = 3;
		player.car = cars[player_car_index]; // player ke choose korar option deya jay
		player.car.x = (SCRN_WIDTH-player.car.width)/2;
		player.car.y = (SCRN_HEIGHT-player.car.height)/2;//100;
		player.x = player.car.x;
		player.y = player.car.y;
		
		npc_gen();
		
		paused = false;
		last_hit = time(NULL);


		score = 0;
		life = 3;

		game_on = true;
	}


	void pause()
	{    
		if(game_on)
			curr_pg = 23;
		//else curr_pg = 1;
		
		sound::change_song = true;
		paused = true;
	}

	void resume()
	{
		curr_pg = 22;

		sound::change_song = true;
		last_hit = time(NULL);
		paused = false;
	}

	void stop()
	{
		game_on = false;
		
		if(life<=0){
			curr_pg = 24;
			sound::change_song = true;
		}
		else curr_pg = 1;
	}

	void game_over()
	{
		stop();
		row.name = settings.name;
		row.score = score;
		row.start_level = initial_level;
		row.finish_level = level;
	}

	void special_npc_col_check(){
		int i, j;
		int x10, y10, x1, y1, w1, h1, x20, y20, x2, y2, w2, h2, flag;
		for(i=0; i<MX_NPC_Q; ++i){
			
			x10 = npc_left[i].x;
			y10 = npc_left[i].y;
			
			x1 = npc_left[i].car.x;
			y1 = npc_left[i].car.y;
			w1 = npc_left[i].car.width;
			h1 = npc_left[i].car.height;
			
			for(j=0; j<MX_NPC_Q; ++j){
				if(i==j) continue;
				
				x20 = npc_left[j].x;
				y20 = npc_left[j].y;
				
				x2 = npc_left[j].car.x;
				y2 = npc_left[j].car.y;
				w2 = npc_left[j].car.width;
				h2 = npc_left[j].car.height;
				flag = collide(x1, y1, w1, h2, x2, y2, w2, h2);
				//flag = collide(x, y, w, h, x2, y2, w2, h2);
				if(flag == 1){
					//pause();
					printf("left| flag, i, j: %d %d %d\n", flag, i, j);
					printf("x_i, y_i, x1, y1, w1, h1 || x_i, y_i, x2, y2, w2, h2: %d %d %d %d %d %d || %d %d %d %d %d %d\n", x10, y10, x1, y1, w1, h1, x20, y20, x2, y2, w2, h2);
				}
			}
		}

		for(i=0; i<MX_NPC_Q; ++i){
			
			x1 = npc_right[i].car.x;
			y1 = npc_right[i].car.y;
			w1 = npc_right[i].car.width;
			h1 = npc_right[i].car.height;
			
			for(j=0; j<MX_NPC_Q; ++j){
				if(i==j) continue;
				x2 = npc_right[j].car.x;
				y2 = npc_right[j].car.y;
				w2 = npc_right[j].car.width;
				h2 = npc_right[j].car.height;
				flag = collide(x1, y1, w1, h2, x2, y2, w2, h2);
				if(flag == 1){
					//pause();
					printf("right| flag, i, j: %d %d %d\n", flag, i, j);
					printf("x1, y1, w1, h1 || x2, y2, w2, h2: %d %d %d %d || %d %d %d %d\n", x1, y1, w1, h1, x2, y2, w2, h2);
				}
			}
		}
		printf("\n\n");
	}


	void draw()
	{
		rd_asphalt.draw();
		for(int i = 0; i< RD_Q; ++i){
			roads[i].draw();
			//iText(150, roads[i].y+300, (char*)std::to_string((long long)i).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
		}

		for(int i = 0; i<active_npc_q; ++i){
			npc_left[i].draw();
			npc_right[i].draw();
		}

		if(visible){
			iRotate(player.car.x, player.car.y, theta);
			player.draw();
			iUnRotate();
		}

		//if(game_on && life <= 0) game_over();

		iSetColor(50, 50, 50);
		iFilledRectangle(15, SCRN_HEIGHT - 40, 100, 35);
		iSetColor(200, 200, 200);
		iText(25, SCRN_HEIGHT - 30, "Life: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(95, SCRN_HEIGHT - 30, (char*)std::to_string((long long) life).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);


		iSetColor(50, 50, 50);
		iFilledRectangle(rd_x2+15, SCRN_HEIGHT - 40, 225, 35);
		iSetColor(200, 200, 200);
		iText(rd_x2+25, SCRN_HEIGHT - 30, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(rd_x2+ 95, SCRN_HEIGHT - 30, (char*)std::to_string((long long)score).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
		

		iSetColor(50, 50, 50);
		iFilledRectangle(rd_x2+15, SCRN_HEIGHT - 80, 150, 35);
		iSetColor(200, 200, 200);
		iText(rd_x2+25, SCRN_HEIGHT - 70, "Level: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(rd_x2+ 95, SCRN_HEIGHT - 70, (char*)std::to_string((long long) level).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);

		
		// animtions
		if(game_on && !paused){
			player_collision_check();

			if(!(frame%6))
				scorer();

			if(!(frame%2))
				rd_npc_movement();
			if(!(frame%10))
				visibility();
			
			if(!(frame%15))
				controll_player_speed();

			if(!(frame%20)){
				if(player_speed>0 && !arrow_states[GLUT_KEY_UP-100]) --player_speed;
				if(player_speed<0 && !arrow_states[GLUT_KEY_DOWN-100]) ++player_speed;
			}
		}
		++frame;
	}
}
