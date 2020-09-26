#include<string>

namespace ige{
	class InputField{
	public:
		int x, y, height, width, txt_x, txt_y;
		
		std::string text;
		
		int txt_len, curr_index, border_color[3], txt_color[3];
		bool active;

		void set_all(int x, int y, int w, int h, char *txt);
		void set_color(int r, int g, int b, int flag = 1);
		
		void set_txt_pos();
		void setup();

		bool isInside(int x, int y);
		void onClick(int button, int state, int x, int y);
		void keyboard(unsigned char key, void (*save)(void) = NULL);

		void draw();
	};

	void InputField::set_all(int x, int y, int w, int h, char *txt)
	{
		this->x = x;
		this->y = y;
		width = w;
		height = h;

		
		text = txt;
	}

	void InputField::set_color(int r, int g, int b, int flag)
	{
		if(flag == 1){
			txt_color[0] = r;
			txt_color[1] = g;
			txt_color[2] = b;
		}
		if(flag == 0){
			border_color[0] = r;
			border_color[1] = g;
			border_color[2] = b;
		}
	}

	void InputField::set_txt_pos()
	{
		txt_x = x + (width - (txt_len*9))/2;
		txt_y = y + (height - 15)/2;
	}
	
	void InputField::setup()
	{
		txt_len = text.length();
		curr_index = txt_len;

		set_txt_pos();
	}

	bool InputField::isInside(int x, int y)
	{
		if(this->x < x && x < this->x + width && this->y <= y && y <= this->y + height) return true;
		else return false;
	}
	void InputField::onClick(int button, int state, int x, int y)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

			if(isInside(x, y)){
				active = true;
			}
			else{
				active = false;
			}
		}
	}

	void InputField::keyboard(unsigned char key, void (*save)(void))
	{
		if(active){
			if(32<= key && key<=126){
				text.push_back(key);
				txt_x = x + (width - (text.length()*9))/2;
			}
			else if(key == 8 && text.length() > 0){
				text.pop_back();
				txt_x = x + (width - (text.length()*9))/2;
			}
			else if(key == 27) active = false; //esc
			else if(key == 13){ //enter
				active = false;
				// enter dile saved emon ekta flash msg er bebostha kora jay..
				if(save)
					save(); //add korte hobe
			}
		}
	}

	

	void InputField::draw()
	{
		if(active){
			iSetColor(200, 200, 200);
			iFilledRectangle(x, y, width, height);

			iSetColor(50, 220, 100);
			//iSetColor(0, 0, 0);
			iRectangle(x, y, width, height);
			iRectangle(x+1, y+1, width-2, height-2);
		}
		else{
			//iSetColor(border_color[0], border_color[1], border_color[2]);
			iSetColor(200, 200, 200);

			iFilledRectangle(x, y, width, height);
		}
		//iSetColor(txt_color[0], txt_color[1], txt_color[2]);
		iSetColor(50, 50, 50);
		iText(txt_x, txt_y, (char*) text.c_str(), GLUT_BITMAP_9_BY_15);
		//iText(txt_x, txt_y, (char*) text.c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
	}
}