namespace ige{
	class MouseInteractions{
	public:
		
		bool isInside(double x, double y);
		
		void onClick(int button, int state, double x, double y, void (*func)(void) = NULL); // prottek onClick funtion button and state add korte hbe
		void passive(double x, double y, void (*func)(void) = NULL);
		void drag(double x, double y, void (*func)(void) = NULL);
	};

	class KeyboardInteractions{
	public:
		void keyReaction(char key, void (*func)(char key) = NULL);
		void specialKeyReaction(char key, void (*func)(char key) = NULL);
	};
}