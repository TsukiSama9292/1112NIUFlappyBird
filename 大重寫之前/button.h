#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

class SFML_button
{	
	RenderWindow *window;
	vector<Sprite> btn_show;
	float mouse_x,mouse_y,btn_x,btn_y,btn_w,btn_h;	
	public:
		Texture btn;
		Sprite *sbtn;
		SFML_button();
		SFML_button(String,float,float,RenderWindow*);
		void setSFML(String,float,float,RenderWindow*);
		bool isMouseOver();
		void drawTowindow(RenderWindow *window);
};
