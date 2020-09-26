#include "sources\racing_basic_demo\objects_v1.cpp"
#include "sources\racing_basic_demo\to_string.cpp"
#include<string>
#include<list>


/*
	spawn function gulay kisu constatn aache jegula onekbar calculate korte hoy,, oigulake global variable declare korte hobe..
	and setup er dhukai dite hbe..

	**** ekta kaaj korte hobe.. level beshi hoile score o druto barar bebostha.. eitar jonno chaile scorer e na baraya prottek notun gari
		spawn er shomoy score barano jay... othoba notun gari spawn e ektu bonus.. ****
*/


namespace mbal
{
	#define RND_CARS_QUANTITY 10
	#define RD_Q 7
	#define BLD_Q 3

	void player_movement(unsigned char key);
	void player_collision();
	
	void spawn1(int i);
	void spawn2(int i);
	void npc_gen();
	void npc_movement(int ac = 0);
	void npc_movement_fortimer();
	void npc_draw();

	void road_gen();
	void road_movement(int h = 0);
	void road_movement_fortimer();
	void road_draw();

	bool collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

	void setup();

	void indestructable();
	void scorer();
	void flash_msg();

	void draw();
	

	double rd_width, min_rd_height, mx_rd_height, rd_x;
	double min_speed, mx_speed, speeds1[RND_CARS_QUANTITY], speeds2[RND_CARS_QUANTITY], level;
	double min_car_height, mx_car_height, ratio;
	double car_width, car_height;
	double last_hit, start_time;
	
	char life[20], score[20], level_str[20];
	
	std::list< std::pair<std::string, double> > msgs;
	std::list< std::pair<std::string, double> >::iterator it;

	Car car, cars1[RND_CARS_QUANTITY], cars2[RND_CARS_QUANTITY];
	Road rd[RD_Q];
	Car buildings1[BLD_Q], buildings2[BLD_Q];

	void road_gen()
	{
		int y = 0;
		for(int i = 0; i< RD_Q; ++i){
			rd[i].set_all(y, rd_width, rand()%(int)mx_rd_height+min_rd_height, 2);
			y += rd[i].height;
			rd[i].speed = 2;
			
			//buildings1[i].setup()
		}
		
	}
	
	void road_movement(int h)
	{
		for(int i = 0; i< RD_Q; ++i){
			rd[i].cor.y -= (rd[i].speed + h+level);
			if(rd[i].cor.y+rd[i].height < 0){
				rd[i].cor.y = SCRN_HEIGHT;
				rd[i].type = rand()%3;
			}
		}
	}

	void road_movement_fortimer()
	{
		road_movement(0);
	}

	void road_draw()
	{
		for(int i = 0; i< RD_Q; ++i){
			rd[i].draw();
		}
	}


	void player_movement(unsigned char key)
	{
		//double rd_x = (SCRN_WIDTH-rd_width)/2; // eitake global korte hbe, smartly
		
		if(key == GLUT_KEY_UP){
			if(car.cor.y +car.height < SCRN_HEIGHT)
				car.cor.y += car_height/2;
			road_movement(2);
			npc_movement(2);
		}
		if(key == GLUT_KEY_DOWN){
			if(car.cor.y > 0)
				car.cor.y -= car_height/2;
			road_movement(-2);
			npc_movement(-2);
		}
		if(key == GLUT_KEY_RIGHT) {
			if(car.cor.x + car.width < rd_x+rd_width)
				car.cor.x += car_width/2;
		}
		if(key == GLUT_KEY_LEFT) {
			if(car.cor.x > rd_x)
				car.cor.x -= car_width/2;
		}
	}

	void setup()
	{
		srand(time(NULL));
		
		rd_width = 834; min_rd_height = 200; mx_rd_height = 500;
		rd_x = (SCRN_WIDTH-rd_width)/2;
		
		car_width = 20; car_height = 35;

		min_speed = 3; mx_speed = 4;// mx_speed may be dorkar nai
		min_car_height = 20; mx_car_height = 50; ratio = car_width/car_height;

		car.set_all(SCRN_WIDTH/2 - car_width/2, 2, car_width, car_height);
		car.score = 0;
		car.life = 3;

		last_hit = time(NULL);
		start_time = time(NULL);

		level = 0;


		//road_gen();
		car.set_color(255, 255, 255);
		npc_gen();
		
	
		//iSetTimer(20, mbal::flash_msg);
		iSetTimer(100, scorer);
		iSetTimer(17, indestructable);
		//iSetTimer(15, road_movement_fortimer);
		iSetTimer(15, npc_movement_fortimer);
		iSetTimer(15, player_collision);
	}


	void npc_gen()
	{
		for(int i = 0; i<RND_CARS_QUANTITY; ++i)
			spawn1(i);
		
		for(int i = 0; i<RND_CARS_QUANTITY; ++i)
			spawn2(i);
	}
	
	void spawn1(int i)
	{
		double h = rand()% (int) (mx_car_height - min_car_height) + min_car_height;
		double w = h*ratio;
		double x, y;
		
		x = rand() % (int)(SCRN_WIDTH/2 - (int)cars1[i].width - rd_x) + rd_x;
		y = rand() % (int)(SCRN_HEIGHT* 1.75) + SCRN_HEIGHT;
		
		
		cars1[i].height = h;
		cars1[i].width = w;
		cars1[i].set_color(rand()% (256- 50) + 50, rand()% (256- 50) + 50, rand()% (256- 50) + 50);
		for(int j = 0; j<RND_CARS_QUANTITY; ++j)
		{
			if(j!=i){
				while(collide(x - 5, y - 5, w + 5 , h + 5, cars1[j].cor.x, cars1[j].cor.y, cars1[i].width, cars1[i].height)){ // added 2 jate shundor ekta distance thake
					x = rand() % (int)(SCRN_WIDTH/2 - (int)cars1[i].width - rd_x) + rd_x;
					y = rand() % (int)(SCRN_HEIGHT* 1.75) + SCRN_HEIGHT;
				}
			}
		}
		cars1[i].cor.x = x;
		cars1[i].cor.y = y;
		cars1[i].speed = rand()% (int) (mx_speed-min_speed) + min_speed + level;
	}
	
	
	void spawn2(int i)
	{
		double h = rand()% (int) (mx_car_height - min_car_height) + min_car_height;
		double w = h*ratio;
		double x, y;
		
		int temp1 = (int) (.5*SCRN_WIDTH - rd_x - cars2[i].width);
		int temp2 = SCRN_WIDTH/2;
		
		x = rand() % temp1 + temp2;
		y = rand() % (int) (SCRN_HEIGHT) - 1.5*SCRN_HEIGHT;
		
		
		cars2[i].height = h;
		cars2[i].width = w;
		cars2[i].set_color(rand()% (256- 50) + 50, rand()% (256- 50) + 50, rand()% (256- 50) + 50);
		for(int j = 0; j<RND_CARS_QUANTITY; ++j)
		{
			if(j!=i){
				while(collide(x - 5, y - 5, w + 5 , h + 5, cars2[j].cor.x, cars2[j].cor.y, cars2[i].width, cars2[i].height)){ // added 2 jate shundor ekta distance thake
					x = rand() % temp1 + temp2;
					y = rand() % (int)(SCRN_HEIGHT) - 1.5 * SCRN_HEIGHT;
				}
			}
		}
		cars2[i].cor.x = x;
		cars2[i].cor.y = y;
		cars2[i].speed = - ((rand()% (int) (mx_speed-min_speed) + (min_speed-2) + level));
	}
	
	void npc_movement(int ac)
	{
		for(int i = 0; i<RND_CARS_QUANTITY; ++i){
			if(cars1[i].cor.y < -cars1[i].height) {spawn1(i); car.score += 5;}
			//else cars[i].cor.y -= rand()% (int) (top_speed-least_speed) + least_speed; eitar fole ekoi gari proti frame e different speed e jay.. unsmooth hoy
			else cars1[i].cor.y -= (cars1[i].speed + ac);
		}
		
		for(int i = 0; i<RND_CARS_QUANTITY; ++i){
			if(cars2[i].cor.y > SCRN_HEIGHT) {spawn2(i); car.score += 5;}
			//else cars[i].cor.y -= rand()% (int) (top_speed-least_speed) + least_speed; eitar fole ekoi gari proti frame e different speed e jay.. unsmooth hoy
			else cars2[i].cor.y -= (cars2[i].speed + ac);
		}
	}
	void npc_movement_fortimer()
	{
		npc_movement(0);
	}
	
	void npc_draw()
	{
		for(int i = 0; i<RND_CARS_QUANTITY; ++i){
			cars1[i].draw();
			cars2[i].draw();
		}
	}

	bool collide(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
	{
		if(x1 > x2+w2 || x2 > x1+w1) return false;
		if(y1 > y2+h2 || y2 > y1+h1) return false;
		return true;
	}

	void player_collision()
	{
		bool b = 0;

		if(time(NULL)- last_hit < 2) return;
		
		for(int i = 0; i < RND_CARS_QUANTITY; ++i)
		{
			if(collide(car.cor.x, car.cor.y, car.width, car.height, cars1[i].cor.x, cars1[i].cor.y, cars1[i].width, cars1[i].height)){
				car.cor.x =  SCRN_WIDTH/2;
				car.cor.y = 2;
				car.score -= 25;
				car.life -= 1;
				last_hit = time(NULL);
				msgs.push_back(std::make_pair(std::string("Collision, Life -1"), time(NULL)));
				return;
			}
			if(collide(car.cor.x, car.cor.y, car.width, car.height, cars2[i].cor.x, cars2[i].cor.y, cars2[i].width, cars2[i].height)){
				car.cor.x =  SCRN_WIDTH/2;
				car.cor.y = 2;
				car.score -= 25;
				car.life -= 1; // it is death count actually, for now
				last_hit = time(NULL);
				msgs.push_back(std::make_pair(std::string("Collision, Life -1"), time(NULL)));
				return;
			}
			
			// for near misses, thik hoy nai.. ekta gari theikai onek bonus paya jay.. even dhush khaoar aag porjonto bonus paite thake..
			if(collide(car.cor.x-15, car.cor.y-15, car.width+15, car.height+15, cars1[i].cor.x, cars1[i].cor.y, cars1[i].width, cars1[i].height)){
				//car.cor.x =  SCRN_WIDTH/2;
				//car.cor.y = 2;
				if((car.cor.y - (cars1[i].cor.y + cars1[i].height)) == 14){
					car.score += 25;
					msgs.push_back(std::make_pair(std::string("Near miss. +25"), (double)time(NULL)));
				}
			}
			if(collide(car.cor.x-15, car.cor.y-15, car.width+15, car.height+15, cars2[i].cor.x, cars2[i].cor.y, cars2[i].width, cars2[i].height)){
				//car.cor.x =  SCRN_WIDTH/2;
				//car.cor.y = 2;
				if((cars2[i].cor.y - (car.cor.y + car.height)) == 14){
					car.score += 25;
					msgs.push_back(std::make_pair(std::string("Near miss. +25"), (double)time(NULL))); //eikhane aro kaaj laagbe..
				}
			}
		}
	}

	void indestructable()
	{
		if(time(NULL) - last_hit < 2)
			car.set_color(rand()%(205)+50, rand()%(205)+50, rand()%(205)+50);
		else car.set_color();
	}

	void scorer()
	{
		car.score+=1;
		dbl_to_str::intToStr(car.score, score, 1);
		if((level +1)* 1000 <= car.score) {
			car.life += 1;
			level += 1;
			msgs.push_back(std::make_pair(std::string("^^ Leve UP ^^"), time(NULL)));
			msgs.push_back(std::make_pair(std::string("Bonus Life +1"), time(NULL)));
		}
	}

	void flash_msg()// eitake aro shundor korte hobe..
	{
		double y = SCRN_HEIGHT-50;

		for(it = msgs.begin(); it != msgs.end();){
			if(time(NULL) - it->second > 2){
				it = msgs.erase(it);
			}
			else{
				iSetColor(255, 255, 255);
				iText( SCRN_WIDTH - rd_x, y, (char *) it->first.c_str(), GLUT_BITMAP_9_BY_15);
				y-=20;
				++it;
			}
		}
	}

	void draw()
	{
		dbl_to_str::intToStr(mbal::car.life, life, 1);
		dbl_to_str::intToStr(mbal::level+1, level_str, 1);
		//dbl_to_str::ftoa(mbal::car.score, score, 3);
		//life = std::to_string(3.0 + mbal::car.life * 1.0);

		iSetColor(250, 250, 250);
		iText(15, SCRN_HEIGHT-15, life);// it is death count actually, for now
		iText(mbal::rd_width+mbal::rd_x+15, SCRN_HEIGHT-15, score);
		iText(15, SCRN_HEIGHT-30, level_str);
	
		//mbal::road_draw();
		mbal::npc_draw();
		mbal::car.draw();
		//mbal::player_collision();
		mbal::flash_msg();
	}
}
