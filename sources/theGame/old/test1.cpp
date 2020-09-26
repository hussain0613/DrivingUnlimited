
namespace game{
#define NPC_Q 5
#define MX_NPC_Q 20
#define MX_LIFE 5
	
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
	void player_collision_check();

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
	void specialKeyboard(int key);
	void draw();



	//int loaded = 0, state=0, timers_ini, 
	int road_timer, min_speed, max_speed, player_speed, ac, rd_x1, rd_x2; // level main theke othoba bahir theke initialize korte hbe
	int level, initial_level, dLevel;
	int score, life, last_hit, active_npc_q;
	bool visible;
	int vis_timer_id;

	ige::Image rd_asphalt, rd_lefts[2], rd_rights[2], rd_mids[3], rd_quarter, cars[3], cars_f[3];
	Road roads[3];
	Car player, npc_left[MX_NPC_Q], npc_right[MX_NPC_Q];


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
		cars[0].setup();

		cars[1].set_all(0, 0, 37, 80, "images/cars/car_2.png");
		cars[1].setup();

		cars[2].set_all(0, 0, 37, 80, "images/cars/car_3.png");
		cars[2].setup();

		cars[3].set_all(0, 0, 37, 80, "images/cars/car_4.png");
		cars[3].setup();

		// cars_flipped
		cars_f[0].set_all(0, 0, 37, 80, "images/cars/car_1f.png");
		cars_f[0].setup();

		cars_f[1].set_all(0, 0, 37, 80, "images/cars/car_2f.png");
		cars_f[1].setup();

		cars_f[2].set_all(0, 0, 37, 80, "images/cars/car_3f.png");
		cars_f[2].setup();

		cars_f[3].set_all(0, 0, 37, 80, "images/cars/car_4.png");
		cars_f[3].setup();
	}
	

	void spawn_road(int i, int tier){
		roads[i].left = rd_lefts[rand()%2].img_id;
		roads[i].right = rd_rights[rand()%2].img_id;
		
		roads[i].mid = rd_mids[rand()%3].img_id;
		
		//int j = rand()%2;
		roads[i].quarter = (rand()%2<1)? rd_quarter.img_id: -1;

		roads[i].x = 0;
		if(tier<3)
			roads[i].y = SCRN_HEIGHT*(tier-1);
		else if (tier >=3){
			if(i == 0) roads[i].y = (roads[2].y - (min_speed+level+ac)) + SCRN_HEIGHT;
			else roads[i].y = roads[i-1].y+SCRN_HEIGHT;
		}
		
	}

	void road_movement()
	{
		for(int i = 0; i<3; ++i){
			roads[i].y -= (player_speed+ac);
			if(roads[i].y < -SCRN_HEIGHT) spawn_road(i, 3);
			//if(roads[i].y > SCRN_HEIGHT) spawn_road(i, -1);
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


	void player_collision_check()
	{
		if(time(NULL)-last_hit<2) return;
		
		int i;
		for(i = 0; i < MX_NPC_Q; ++i){
			if(collide(player.car.x, player.car.y, player.car.width, player.car.height, npc_left[i].car.x, npc_left[i].car.y, npc_left[i].car.width, npc_left[i].car.height) == 1){
				player.car. x = SCRN_WIDTH/2;
				player.car.y = 20;
				last_hit = time(NULL);
				score -= 25;
				--life;
				//return true;
			}
			if(collide(player.car.x, player.car.y, player.car.width, player.car.height, npc_right[i].car.x, npc_right[i].car.y, npc_right[i].car.width, npc_right[i].car.height) == 1){
				player.car. x = SCRN_WIDTH/2;
				player.car.y = 20;
				last_hit = time(NULL);
				score -= 25;
				--life;
				//return true;
			}
		}
		//return false;
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
		score+=1;
		if((dLevel+1)*(dLevel * .25 +1) * 250 <= score) {
			if(life<MX_LIFE) life += 1;
			level += 1;
			dLevel += 1;
			player_speed += 1;
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
		
		Car car;
		int x, y, w, h, speed, flag, x2, y2, w2, h2, speed2;

		car.car = cars[rand()%3];
		
		w = car.car.width;
		h = car.car.height;

		speed = rand()%(max_speed - min_speed)+min_speed + 2; //base speed
		x = rand()%(675-30-rd_x1-50) + rd_x1+50; //in_between rd_x+50 and 675-30 px
		y = -(rand()%SCRN_HEIGHT+100); // in between -SCRN_HEIGHT and -100

		for(int j = 0; j<MX_NPC_Q; ++j){
			if(j != i){
				x2 = npc_left[j].car.x;

				y2 = npc_left[j].car.y;
				if(j>i) y2 += (npc_left[j].speed + level - ac); // j>i hoar maane car1 spawn howar por car2 er actual position change hbe.. tai eita add kora hoise
				
				w2 = npc_left[j].car.width;
				h2 = npc_left[j].car.height;
				speed2 = npc_left[j].speed;

				flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
				while(flag){ //flag = 0 hoile ok.. otherwise kaaj korte hbe
					if(flag == 1 ){ // 1 hoile full collision
						x = rand()%(675-rd_x1-50) + rd_x1+50;
						y = -(rand()%SCRN_HEIGHT+100);
						flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
						j =-1;
					}
					else{ // not full collision but chances are they will collide in near future
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

		car.car = cars_f[rand()%3];
		
		w = car.car.width;
		h = car.car.height;

		speed = rand()%(max_speed - min_speed)+min_speed + 3; //base speed ,+2 to make sure speed is more than road*/
		x =  rand()%(rd_x2-30 - 690 - w) + 690;//in_between 690 and rd_x2-30 px
		y = (rand()%SCRN_HEIGHT*2 + SCRN_HEIGHT); // in between SCRN_HEIGHT and SCRN_HEIGHT*2

		for(int j = 0; j<MX_NPC_Q; ++j){
			if(j != i){
				x2 = npc_right[j].car.x;
				
				y2 = npc_right[j].car.y;
				if(j>i) y2 -= (npc_right[j].speed + player_speed+ level + ac);
				
				w2 = npc_right[j].car.width;
				h2 = npc_right[j].car.height;
				speed2 = npc_right[j].speed;

				flag = collide(x-10, y-10, w+20, h+20, x2, y2, w2, h2);
				while(flag){ //flag = 0 hoile ok.. otherwise kaaj korte hbe
					if(flag == 1 ){ // 1 hoile full collision
						x = rand()%(rd_x2 -30 - 690 - w) + 690;
						y = (rand()%SCRN_HEIGHT*2 + SCRN_HEIGHT);
						//flag = collide(x-5, y-5, w+5, h+5, x2-5, y2-5, w2+5, h2+5);
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

		npc_right[i] = car;
	}
	void npc_movement()
	{
		
		for(int i=0; i < active_npc_q; ++i){
			npc_left[i].car.y += (npc_left[i].speed + level- ac);
			if(npc_left[i].car.y > 1.5*SCRN_HEIGHT) {npc_spawn_left(i); score += 10;}
		}
		for(int i=0; i < active_npc_q; ++i){
			npc_right[i].car.y -= (npc_right[i].speed + player_speed+ level + ac);
			if(npc_right[i].car.y+npc_right[i].car.height < -.5*SCRN_HEIGHT) {npc_spawn_right(i); score+= 10;}
		}

		//special_npc_col_check();
	}

	void rd_npc_movement()
	{
		if(game_on && !paused){
			npc_movement();
			road_movement();
		
			if(ac>0) --ac;
			else if(ac<0) ++ac;

			scorer();
		}
	}

	void keyboard(int key)
	{
		if(key == 27){
			pause();
		}
	}

	void specialKeyboard(int key)
	{
		//double rd_x = (SCRN_WIDTH-rd_width)/2; // eitake global korte hbe, smartly
		
		if(key == GLUT_KEY_UP){
			if (ac <= min_speed+level)ac += 2;
			if(player.car.y+player.car.height < SCRN_HEIGHT)
				//player.car.y += player.car.height/2;
				player.car.y += player.car.height/8;
		}
		if(key == GLUT_KEY_DOWN){
			if(ac-2 + (min_speed+level) >= 0) ac -= 2;

			if(player.car.y - (player.car.height/2) >= 0)
				//player.car.y -= player.car.height/2;
				player.car.y -= player.car.height/8;
		}
		if(key == GLUT_KEY_RIGHT) {
			
			if(player.car.x+player.car.width*1.5 < rd_x2)
				//player.car.x += player.car.width/2;
				player.car.x += player.car.width/8;
		}
		if(key == GLUT_KEY_LEFT) {
			if(player.car.x - (player.car.width/2) >= rd_x1)
				//player.car.x -= player.car.width/2;
				player.car.x -= player.car.width/8;
		}
	
	}

	void setup()
	{
		load_images();

		last_hit = 0;
		min_speed = 1; level = 1; ac = 0; max_speed = 4;
		initial_level = 1;
		dLevel = level - initial_level;
		//player_speed = (min_speed+max_speed)/2 + level;//jokhon level baarbe tokhon eta abar barate hbe
		player_speed = min_speed + level;
		if(NPC_Q +level <= MX_NPC_Q) active_npc_q = NPC_Q +level;
		else active_npc_q = MX_NPC_Q;

		paused = true;

		rd_x1 = 263;
		rd_x2 = 1097;

		score = 0;
		life = 3;

		road_timer = iSetTimer(17, rd_npc_movement);
		iPauseTimer(road_timer);
		vis_timer_id = iSetTimer(75, visibility);
		iPauseTimer(vis_timer_id);

		
		printf("game has been setup\n");
	}

	void start()
	{
		int seed = time(NULL); 
		//1599848441 ei seed e speed er jonno 2ta baghe dhore
		//1599849456 shurutei ekta baagh..
		seed = 1599849456;

		srand(seed);
		printf("seed: %d\n", seed);

		level = 1; // eita level selection theke thik kore dite hbe
		initial_level = level;
		dLevel = level - initial_level;
		
		if(NPC_Q +level <= MX_NPC_Q) active_npc_q = NPC_Q +level;
		else active_npc_q = MX_NPC_Q;

		player_speed = min_speed + level;
		score = 0;
		life = 3;

		spawn_road(0,0);
		spawn_road(1,1);
		spawn_road(2,2);
		
		//player_speed = (min_speed+max_speed)/2 + level;//jokhon level baarbe tokhon eta abar barate hbe

		

		//player.car_id = cars[0].img_id;
		player.car = cars[0]; // player ke choose korar option deya jay
		player.car.x = SCRN_WIDTH/2;
		player.car.y = 50;
		npc_gen();
		
		paused = false;
		last_hit = time(NULL);
		iResumeTimer(road_timer);
		iResumeTimer(vis_timer_id);

		game_on = true;
	}


	void pause()
	{    
		iPauseTimer(road_timer);
		iPauseTimer(vis_timer_id);
		if(game_on)
			curr_pg = 23;
		else curr_pg = 1;
		
		changed = 1;
		paused = true;
	}

	void resume()
	{
		curr_pg = 22;
		iResumeTimer(road_timer);
		iResumeTimer(vis_timer_id);
		changed = 1;
		last_hit = time(NULL);
		paused = false;
	}

	void stop()
	{
		game_on = false;
		pause();
		//curr_pg = 1;
	}

	void game_over()
	{
		stop();
		backend::Row r;
		r.name = settings.name;
		r.score = score;
		r.start_level = initial_level;
		r.finish_level = level;

		scorb.add(r);
		scorb.save();
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
		roads[0].draw();
		roads[1].draw();
		roads[2].draw();

		for(int i = 0; i<active_npc_q; ++i){
			npc_left[i].draw();
			npc_right[i].draw();
		}

		if(visible)
			player.draw();
		
		player_collision_check();

		if(life <= 0) game_over();

		iText(25, SCRN_HEIGHT - 30, "Life: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(95, SCRN_HEIGHT - 30, (char*)std::to_string((long long) life).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);

		iText(rd_x2+25, SCRN_HEIGHT - 30, "Score: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(rd_x2+ 95, SCRN_HEIGHT - 30, (char*)std::to_string((long long)score).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
		
		iText(rd_x2+25, SCRN_HEIGHT - 70, "Level: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(rd_x2+ 95, SCRN_HEIGHT - 70, (char*)std::to_string((long long) level).c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
