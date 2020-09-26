namespace ige{

	class Page{
	public:
		int page_id;

		void setup(); // will setup everything necessary
	
		void passives(int x, int y);
		void onClicks(int button, int state, int x, int y); //jeikhane kaaj hbe sheikhane eitar function define kora hobe.. preferbly in the namespace
		void drag(int x, int y);

		void keyboard(unsigned char key);
		void specialKeyboard(unsigned char key);

		void draw(); // will draw the page.. i.e. show the page
	};
}