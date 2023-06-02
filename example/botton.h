#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

class Button{
public:
	Texture btn;
	Sprite *button;
	
	bool isMouseOver(){
		float mouseX = Mouse::getPosition(window).x;
		float mouseY = Mouse::getPosition(window).y;
		
		btnX = button.getPosition().x;
		btnX = button.getPosition().x;
		btnWX = button.getPosition().x + button.getGlobalBounds().width;
		btnHY = button.getPosition().y + button.getGlobalBounds().height;
		
		if (mouseX < btnWX && mouseX > btnX && mouseY < btnHY && mouseY > btnY)
			return true;
		return false;
		
		
	}
				
};
