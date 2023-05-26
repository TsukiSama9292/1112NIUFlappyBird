#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
class FlappyBird {
	float y;

  sf::RenderWindow *window;     //«Å§iµøµ¡
  float gravity, frame, space;
  int count, score;
  sf::Texture bg, flappy, pipe;
  sf::Sprite *background, *bird, *pipeBottom, *pipeTop;
  std::vector<sf::Sprite> pipes;
  bool gameover, add;

  sf::Font font;
  sf::Text txt_score, txt_gameover;

  protected:
   void events();
   void draw();
   void game();
   void movePipes();
   void setAnimeBird();
   void moveBird();

  public:
   FlappyBird();
   void setSFML();
   void run();
};
