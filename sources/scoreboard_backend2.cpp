#include<string>
#include<set>

namespace backend{
	class Row{
	public:

		std::string name;
		int score;
		int start_level, finish_level;
		int car;
		double dist, dur; //in km, in mins


		bool operator> (const Row &right) const
		{
			if(score != right.score) return score>right.score;
			if(dist != right.dist) return dist>right.dist;
			if(dur != right.dur) return dur<right.dur; // uprer duita shoman hole je kom time e beshi score korbe she upore thakbe
			return finish_level > right.finish_level; 
		}
	};

	class Scoreboard{
	public:
		std::string src;
		std::multiset<Row, std::greater<Row> > entries;
		//Row entries[10];
		//int sorted;
		bool changed;

		void add(char *name, int score, double dst, double dr, int lvl1, int lvl2, int cr);
		void add(Row r);
		void clear();
		void load();
		void save();
	};

	void Scoreboard::add(char *name, int score, double dst, double dr, int lvl1, int lvl2, int cr)
	{
		Row r;
		r.name = name;
		r.score = score;
		r.dist = dst;
		r.dur = dr;
		r.start_level = lvl1;
		r.finish_level = lvl2;
		r.car = cr;

		add(r);
	}

	void Scoreboard::add(Row r)
	{
		if(entries.size()<10){
			entries.insert(r);
			changed = true;
		}
		else{
			if (std::next(entries.begin(), 9)->score <= r.score) {// orthat 10 number hight score theke choto hole shudhu add korbe.
				entries.insert(r); 
				changed = true;
			}
		}
	}

	void Scoreboard::clear()
	{
		entries.clear();
		changed = true;
		printf("[*] Cleared scoreboard.\n");

		std::multiset<Row, std::greater<Row> >::iterator it;
	}


	void Scoreboard::load()
	{
		FILE *f;
		f = fopen(src.c_str(), "r");
		if( f == NULL){
			
			printf("scoreboard file name: %s\n", src.c_str());
			printf("[!] Could not load scoreboard file.\n");
		}
		else{
			Row r;
			char ch;
			while(!feof(f)){
				for(int i = 0; !feof(f)&&((ch = fgetc(f)) != ','); ++i){
					r.name.push_back(ch);
				}
				if(!feof(f)){
					fscanf(f, "%d,%lf,%lf,%d,%d,%d%c", &r.score, &r.dist, &r.dur, &r.start_level, &r.finish_level, &r.car, &ch);
					entries.insert(r);
				}
				//printf("%s, %d, %d, %d\n", r.name.c_str(), r.score, r.start_level, r.finish_level);
				r.name.clear();
			}
			fclose(f);
			printf("[*]Scoreboard loaded.\n");
		}
	}


	void Scoreboard::save()
	{
		FILE *f;
		if((f = fopen(src.c_str(), "w")) == NULL){
			printf("scorboard file name: %s\n", src.c_str());
			printf("[!] Could not save scoreboard file.\n");
		}
		else{			
			char *nm;
			
			std::multiset<Row, std::greater<Row> >::iterator it;
			
			for(it = entries.begin(); it != entries.end(); ++it){
				nm = (char*) it->name.c_str();
				for(int i = 0; nm[i]; ++i){ 
					fputc(nm[i], f);
				}
				fprintf(f, ",%d,%.2f,%.2f,%d,%d,%d\n", it->score, it->dist, it->dur, it->start_level, it->finish_level, it->car);//, environment_music);
			}

			fclose(f);
			printf("[*] Scoreboard updated\n");
		}
	}
}