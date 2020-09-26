
namespace game{
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
	//void stop();

	void keyboard(int key);
	void specialKeyboard(int key);
	void draw();



	//int loaded = 0, state=0, timers_ini, 
	int road_timer, min_speed, max_speed, level, ac, rd_x1, rd_x2; // level main theke othoba bahir theke initialize korte hbe
	ige::Image rd_asphalt, rd_lefts[2], rd_rights[2], rd_mids[3], rd_quarter, cars[3], cars_f[3];
	Road roads[3];
	Car player, npc_left[5], npc_right[5];



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

		// cars_flipped
		cars_f[0].set_all(0, 0, 37, 80, "images/cars/car_1f.png");
		cars_f[0].setup();

		cars_f[1].set_all(0, 0, 37, 80, "images/cars/car_2f.png");
		cars_f[1].setup();

		cars_f[2].set_all(0, 0, 37, 80, "images/cars/car_3f.png");
		cars_f[2].setup();
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
		/*else if(tier ==-1){
			if(i==2) roads[i].y = roads[0].y - SCRN_HEIGHT;
			else roads[i].y = (roads[i+1].y - (min_speed+level+ac)) - SCRN_HEIGHT;
			//else if (i==0) roads[i].y = roads[i+1].y-SCRN_HEIGHT;
		}*/
		
	}

	void road_movement()
	{
		for(int i = 0; i<3; ++i){
			roads[i].y -= (min_speed+level+ac);
			if(roads[i].y < -SCRN_HEIGHT) spawn_road(i, 3);
			if(roads[i].y > SCRN_HEIGHT) spawn_road(i, -1);
		}
	}

	void npc_gen()
	{
		for(int i = 0; i<5; ++i){
			npc_spawn_left(i);
			npc_spawn_right(i);
		}
	}
	void npc_spawn_left(int i)
	{
		npc_left[i].car = cars[rand()%3];
		npc_left[i].car.x = rand()%(675-rd_x1) + rd_x1;//in_between rd_x and 675 px
		npc_left[i].car.y = -(rand()%SCRN_HEIGHT+100); // in between -SCRN_HEIGHT and -100
		npc_left[i].speed = rand()%(max_speed - min_speed)+min_speed + 2; //base speed ,+2 to make sure speed is more than road
	}
	void npc_spawn_right(int i)
	{
		npc_right[i].car = cars_f[rand()%3];
		npc_right[i].car.x = rand()%(rd_x2 - 685 - npc_right[i].car.width) + 685;//in_between 685 and rd_x2 px
		npc_right[i].car.y = (rand()%SCRN_HEIGHT*2 + SCRN_HEIGHT); // in between SCRN_HEIGHT and SCRN_HEIGHT*2
		npc_right[i].speed = rand()%(max_speed - min_speed)+min_speed + 2; //base speed ,+2 to make sure speed is more than road
	}
	void npc_movement()
	{
		for(int i=0; i<5; ++i){
			npc_left[i].car.y += (npc_left[i].speed + level - ac);
			if(npc_left[i].car.y > SCRN_HEIGHT) npc_spawn_left(i);
		}
		for(int i=0; i<5; ++i){
			npc_right[i].car.y -= (npc_right[i].speed + level + ac + min_speed);
			if(npc_right[i].car.y+npc_right[i].car.height < 0) npc_spawn_right(i);
		}
	}

	void rd_npc_movement()
	{
		npc_movement();
		road_movement();
		
		if(ac>0) --ac;
		else if(ac<0) ++ac;
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
			if (ac <= level+max_speed)ac += 2;
			
			if(player.car.y+player.car.height < SCRN_HEIGHT)
				player.car.y += player.car.height/2;
		}
		if(key == GLUT_KEY_DOWN){
			if(ac-2 + (min_speed+level) >= 0) ac -= 2;

			if(player.car.y - (player.car.height/2) >= 0)
				player.car.y -= player.car.height/2;
		}
		if(key == GLUT_KEY_RIGHT) {
			
			if(player.car.x+player.car.width*1.5 < rd_x2)
				player.car.x += player.car.width/2;
		}
		if(key == GLUT_KEY_LEFT) {
			if(player.car.x - (player.car.width/2) >= rd_x1)
				player.car.x -= player.car.width/2;
		}
	
	}

	void setup()
	{
		load_images();

		road_timer = iSetTimer(17, rd_npc_movement);
		iPauseTimer(road_timer);

		min_speed = 1; level = 1; ac = 0; max_speed = 4;
		paused = true;

		rd_x1 = 263;
		rd_x2 = 1097;
	}

	void start()
	{
		spawn_road(0,0);
		spawn_road(1,1);
		spawn_road(2,2);

		paused = false;
		iResumeTimer(road_timer);

		//player.car_id = cars[0].img_id;
		player.car = cars[0]; // player ke choose korar option deya jay
		player.car.x = SCRN_WIDTH/2;
		player.car.y = 50;
		npc_gen();

		game_on = true;
	}


	void pause()
	{    
		iPauseTimer(road_timer);
		curr_pg = 23;
		changed = 1;
		paused = true;
	}

	void resume()
	{
		curr_pg = 22;
		iResumeTimer(road_timer);
		changed = 1;
		paused = false;
	}

	void stop()
	{
		game_on = false;
		pause();
	}
	void draw()
	{
		rd_asphalt.draw();
		roads[0].draw();
		roads[1].draw();
		roads[2].draw();

		for(int i = 0; i<5; ++i){
			npc_left[i].draw();
			npc_right[i].draw();
		}

		player.draw();
	}
}
