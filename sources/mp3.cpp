#include<iostream>
#include<string>
#include<Windows.h>
class Mp3{
	int id;
public:
	static int x;
	std::string fn;
	int dur; // in seconds

	Mp3(){
		id = x;
		++x;
		dur = 3*60; //seconds
	}
	void load(){
		std::string st = "open \"";
		st+=fn;
		st+="\" type mpegvideo alias mp3";
		st+= std::to_string((long long)id);
		
		mciSendString(st.c_str(), NULL, 0, NULL);

		// setting time to millisecond format
		st.clear();
		st = "set mp3";
		st += std::to_string((long long) id);
		st += " time format ms";
		mciSendString(st.c_str(), NULL, 0, NULL);

		// getting duration
		st.clear();
		st = "status mp3";
		st += std::to_string((long long) id);
		st += " length";
		
		#ifdef _UNICODE
			wchar_t rtstr[100];
		#else
			char rtstr[100];
		#endif

		mciSendString(st.c_str(), rtstr, 100, NULL);
		
		
		st.clear();
		st = rtstr;
		dur = std::stoi(st)/1000; // duration returned in ms, converting to s;
	}
	
	void play(int s = -1, int e = -1)
	{
		if(s == -1) s =0;
		std::string st = "play mp3";
		st += std::to_string((long long)id);
		st+= " from ";
		st+= std::to_string((long long)s*1000);
		
		if(e != -1){
			st+= " to ";
			st+= std::to_string((long long)e*1000);
		}
		
		mciSendString(st.c_str(), NULL, 0, NULL);
	}
	
	void resume(){
		std::string st = "resume mp3";
		st += std::to_string((long long) id);
		
		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}
	
	void pause()
	{
		std::string st = "pause mp3";
		st += std::to_string((long long) id);
		
		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}
	
	void stop(){
		std::string st = "stop mp3";
		st += std::to_string((long long) id);
		
		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}

	void close()
	{
		std::string st = "close mp3";
		st += std::to_string((long long) id);
		
		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}

	void set_volume(int v = 50){
		std::string st = "setaudio mp3";
		st += std::to_string((long long) id);
		st += " volume to ";
		st += std::to_string((long long) v);
		
		mciSendString((char *)st.c_str(), NULL, 0, NULL);
	}
};
int Mp3::x = 0;