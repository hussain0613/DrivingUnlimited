namespace amb{
	/*
	at least 3ta page thakbe, welcome, puase, the game itself
	*/

	/*
	issuies:

		1. **** ektar upor arekta spawn hoy eita thik korte hbe ****  [solved]

		2. score/elapsed time er upor base kore speed change korte hbe.. 
		3. collision add korte hobe [solved]
		4. collision ghotle ki hobe tar likhte hobe..
		6. road, screan er baire jaite pare player.. thik korte hbe..

		echara graphics, score eishob to achei...
	*/

	/*
	ideas:
		1. alda profile profile bhaag kora jay.
		2. or level thakbe.. aste aste unclocked hobe.. ar ke uncloked korse record e thakbe
			ekta game shesh e naam, score, starting level, ending leve, lifes consumed, minutes played, and kokhon khela hoise save thakbe
		3. shurute 3 life thakbe.. aste aste ekoi game score er upor base kore level unlock hobe.. notun level unlock e 2 ta notun life 
			deoa hobe
		4. shobar sheshe (c1 * duration + c2 * level_ups - c3 * life_consumed) ba ei type er kisu er upor base kore bonus deoa jay..
			c1, c2 and c3 are some arbitrary constants
		5. and most certainly, ekbar ekta level unlock korar por oi level ba nicher jekono level theke khela jabe..
		6. it can go to up to infinite leve theoritically. :v :P
		
	*************************************************************************************************
	*************************************************************************************************
		7. *** ekta second set er car toiri kora jay... dui lane e 2 set car 2 dike jaabe...***
		8. actual racing er moto other players o include kora jay chaile..
		9. trafic speed, others player speed eigula hobe dificulty er ongsho..
		10. eitake chaile tokhon multiplayer o kora jaabe..
		11. alda ekta game kora jay eita..
		12. road er baire gele speed kom thakbe emon ekta system deoa jay deoa jay
		13. eitate ful damage na diya collosion e speed e change kora jay..

	*************************************************************************************************
	*************************************************************************************************
		7. collision er shomoy size compare kore damage deoa jay player ke...
			ekbarei pura life shesh na hoye aste aste life shesh hobe...

		
			aobut buttons: ekta button er 3 ta image dorkar.. 3 state er jonno, click, hover, passive. 3 ta ekoi image different darkness..
			or may be different image
	*/

	

	void move(unsigned char key);
	
	void road();
	
	void random_car_gen();
	void random_car_draw();
	void random_car_movement();
	
	void spawn_car(int i);
	
	bool collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
	
	void player_collision();
	
	
	#define RND_CARS_QUANTIT 8
	double least_speed = 1, top_speed = 5; //speed_per_frame (pixel_per_frame)
	int speeds[RND_CARS_QUANTIT];
	double car_width = 20, car_height = 35;
	double mx_ch = 50, min_ch = 20, ratio = 20.0/35.0, h, w;
	
	ige::Rectangle car(SCRN_WIDTH/2 - car_width/2, 2, car_width, car_height), cars[RND_CARS_QUANTIT];
	
	
	

	void player_collision()
	{
		for(int i = 0; i < RND_CARS_QUANTIT; ++i)
		{
			if(collide(car.cor.x, car.cor.y, car.width, car.height, cars[i].cor.x, cars[i].cor.y, cars[i].width, cars[i].height)){
				car.cor.x =  SCRN_WIDTH/2;
				car.cor.y = 2;
			}
		}
	}
	
	bool collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
	{
		if(x1 > x2+w2 || x2 > x1+w1) return false;
		if(y1 > y2+h2 || y2 > y1+h1) return false;
		return true;
	}

	void spawn_car(int i)
	{
		//spawn e ekta option rakhte hbe jaate different speed er car jeno ekta arekar shathe colidena kore..
		// bagh horinke dhorte parbe kina ongkota mne hoitase laagaiya shundor kichu kora jaite paare eitar jonno. :v

		double h = rand()% (int) (mx_ch - min_ch) + min_ch;
		double w = h*ratio;
		double x, y;
		
		x = rand() % (SCRN_WIDTH-80- (int)cars[i].width- 80) + 80;
		y = rand() % (int)(SCRN_HEIGHT* 1.75) + SCRN_HEIGHT;
		
		
		cars[i].height = h;
		cars[i].width = w;
		cars[i].set_color(rand()% (256- 50) + 50, rand()% (256- 50) + 50, rand()% (256- 50) + 50);
		for(int j = 0; j<RND_CARS_QUANTIT; ++j)
		{
			if(j!=i){
				while(collide(x - 5, y - 5, w + 5 , h + 5, cars[j].cor.x, cars[j].cor.y, cars[i].width, cars[i].height)){ // added 2 jate shundor ekta distance thake
					x = rand() % (SCRN_WIDTH-80- (int)cars[i].width- 80) + 80;
					y = rand() % (int)(SCRN_HEIGHT* 1.75) + SCRN_HEIGHT;
				}
			}
		}
		cars[i].cor.x = x;
		cars[i].cor.y = y;
		speeds[i] = 5;//rand()% (int) (top_speed-least_speed) + least_speed;
	}


	void random_car_gen()
	{
		for(int i = 0; i<RND_CARS_QUANTIT; ++i)
			spawn_car(i);
	}

	void random_car_movement()
	{
		for(int i = 0; i<RND_CARS_QUANTIT; ++i){
			if(cars[i].cor.y < -cars[i].height) spawn_car(i);
			//else cars[i].cor.y -= rand()% (int) (top_speed-least_speed) + least_speed; eitar fole ekoi gari proti frame e different speed e jay.. unsmooth hoy
			else cars[i].cor.y -= speeds[i];
		}
	}

	void random_car_draw()
	{
		for(int i = 0; i<RND_CARS_QUANTIT; ++i){
			cars[i].draw();
		}
	}

	void move(unsigned char key)
	{
		if(key == GLUT_KEY_UP) car.cor.y += car_height/2;
		if(key == GLUT_KEY_DOWN) car.cor.y -= car_height/2;
		if(key == GLUT_KEY_RIGHT) car.cor.x += car_width;
		if(key == GLUT_KEY_LEFT) car.cor.x -= car_width;
	}

	void road()
	{
		iSetColor(255, 255, 255);
		
		//left border
		iLine(80, 0, 80, SCRN_HEIGHT);
		iLine(80-5, 0, 80-5, SCRN_HEIGHT);
		
		//right border
		iLine(SCRN_WIDTH - 80, 0, SCRN_WIDTH-80, SCRN_HEIGHT);
		iLine(SCRN_WIDTH - 80+5, 0, SCRN_WIDTH-80+5, SCRN_HEIGHT);

		//middle line
		iLine(SCRN_WIDTH/2, 0, SCRN_WIDTH/2, SCRN_HEIGHT);
	}
}