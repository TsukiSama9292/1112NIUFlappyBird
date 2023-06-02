#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
class FlappyBird : protected setrank{
	RenderWindow *window;
	float y,g,frame,interval;
	int count, score , bgm_times;
	SoundBuffer buffer_hit,buffer_wing,buffer_add,buffer_bgm;
	Sound sound_hit,sound_wing,sound_add,sound_bgm;
	
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
		void bgmCircle();
	public:
		FlappyBird();
		void setSFML();
		void run();
};
