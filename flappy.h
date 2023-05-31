#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
class FlappyBird {
	RenderWindow *window;
	float y,g,frame,interval;
	int count, score;
	Font font;
	Text text_score, text_gameover;
	Texture bg, bd, pipe;
	Sprite *background, *bird, *pipeBottom, *pipeTop;
	vector<Sprite> pipes;
	bool gameover, addscore;
	protected:
		void pipeMove();
		void birdAnime();
		void birdMove();
		void events();
		void draw();
		void game();
	public:
		FlappyBird();
		void setSFML();
		void run();
};
