#include<stdio.h>
#include<string>
namespace backend{
	class Settings{
	public:
		std::string name, file_name;
		int menu_music, sfx, gameplay_music, environment_sound;

		void load();
		void save();
	};

	void Settings::load()
	{
		FILE *f;
		if((f = fopen(file_name.c_str(), "r")) == NULL){
			menu_music = 1;
			sfx = 1;
			gameplay_music = 1;
			environment_sound = 1;
			name = "Player";
			printf("setting file name: %s\n", file_name.c_str());
			printf("[!] Could not load settings file. Setting everything to default.\n");
		}
		else{
			char ch;
			for(int i = 0; !feof(f)&&((ch = fgetc(f)) != ','); ++i) name.push_back(ch);
			
			if(!feof(f)){
				fscanf(f, "%d,%d,%d,%d", &menu_music, &sfx, &gameplay_music, &environment_sound);
			}
			else{
				menu_music = 1;
				gameplay_music = 1;
				sfx = 1;
				environment_sound = 1;
			}
			fclose(f);
			printf("[*]Settings Loaded\n");
		}

	}

	void Settings::save()
	{
		FILE *f;
		if((f = fopen(file_name.c_str(), "w")) == NULL){
			printf("setting file name: %s\n", file_name.c_str());
			printf("[!] Could not save settings file.\n");
		}
		else{			
			char *nm = (char*) name.c_str();
			for(int i = 0; nm[i]; ++i) fputc(nm[i], f);
			fprintf(f, ",%d,%d,%d,%d", menu_music, sfx, gameplay_music, environment_sound);
			fclose(f);
			printf("[*] Settings saved\n");
		}
	}

}