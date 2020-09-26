namespace ige{

	class Image{
		public:
			int img_id;
			char *src;
		
			int x, y, height, width;

			void set_all(int x, int y, int w, int h, char *fn);
			void setup();
			void draw();
	
	};

	void Image::set_all(int x, int y, int w, int h, char *fn)
	{
		this->x = x;
		this->y = y;
		width = w;
		height = h;

		src = fn;
	}

	void Image::setup()
	{
		img_id = iLoadImage(src);
		//printf("image#%d: %s\n", img_id, src);
	}
	void Image::draw()
	{
		iShowImage(x, y, width, height, img_id);
	}
}