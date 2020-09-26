namespace pages{
	class Instructions: public ige::Menu{
	public:
		void setup();
	};

	void Instructions::setup()
	{
		nb = 1;
		__array_setup__();
		

		bt_w = 200;
		bt_h = 50;
		bt_gap = 25;
		bt_x = 5;
		bt_y = SCRN_HEIGHT-5-bt_h;


		fn[1] = "images//INS22.png";
		fn[0] = "images//BACK.png";

		bt_functions[0] = bt_funcs::bt_back;

		bt[0].set_all(bt_x, bt_y, bt_w, bt_h, fn[0]);
		bt[0].setup();

		bg_image.set_all(0, 0, SCRN_WIDTH, SCRN_HEIGHT, fn[1]);
		bg_image.setup();
	}
}