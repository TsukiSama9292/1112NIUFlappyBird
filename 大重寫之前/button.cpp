#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
enum Status{homepage, inputname, game, gameover, showrank, introduce
}gamestatus = homepage;

SFML_button::SFML_button(){
	cout<<"sfml";
}
SFML_button::SFML_button(String name,float btn_px,float btn_py,RenderWindow *window){
	setSFML(name,btn_px,btn_py,window);
}
void SFML_button::setSFML(String name,float btn_px,float btn_py,RenderWindow *window){
	this->window=window;
	if(!btn.loadFromFile("./AllSundries/image/bird.png"))
		cout<<"Fail btn loadFromFile"<<endl;
	sbtn=new Sprite();
	sbtn->setTexture(btn);
	//sbtn->setPosition(btn_px,btn_py);
}
bool SFML_button::isMouseOver(){
	float mouse_x = Mouse::getPosition(*window).x;
	float mouse_y = Mouse::getPosition(*window).y;
	
	btn_x = sbtn->getPosition().x;
	btn_y = sbtn->getPosition().y;
	btn_w = sbtn->getPosition().x + sbtn->getGlobalBounds().width;
	btn_h = sbtn->getPosition().y + sbtn->getGlobalBounds().height;
	
	if (mouse_x < btn_w && mouse_x > btn_x && mouse_y < btn_h && mouse_y > btn_y)
		return true;
	return false;	
}
void SFML_button::drawTowindow(RenderWindow *window)
{
	if(!btn.loadFromFile("./AllSundries/image/bird.png"))
		cout<<"Fail btn loadFromFile"<<endl;
	sbtn=new Sprite();
	sbtn->setTexture(btn);
	//sbtn->setPosition(btn_px,btn_py);
	window->draw(*sbtn);
}

/*
switch(Status){
	case homepage:
		auto e = new Event(); 
		while( window->isOpen() ){
			window -> clear();
			window -> draw(*background);
			window -> draw(*sbtn_n);
			window -> draw(*sbtn_r);
			window -> draw(*sbtn_i);
			window -> display();
			while(window->pollEvent(*e)){
				if (sbtn_n.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = inputname;
					}
				}
				else if (sbtn_r.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = showrank;
					}
				}
				else if (sbtn_i.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = introduce;
					}
				}
			}
		}  
		//button1->setTexture(btn1); //精靈圖案設為管道
		//button1.setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
		break;
	case inputname:
		while(window->isOpen()){
			
		}
		window -> clear();
		window -> draw(*background);
		window -> draw(*sbtn_p);
		//call inputtextbox return name;
		window -> display(); 
		while(window->pollEvent(*e)){
				if (sbtn_p.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = game;
					}
				}
		}
		break;
	case game:
		run();
		break;
	case gameover;
		window -> clear();
		window -> draw(*background);
		window -> draw(*sbtn_rp);
		window -> draw(*sbtn_h);
		window -> display(); 
		while(window->pollEvent(*e)){
				if (sbtn_rp.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = game;
					}
				}
				else if (sbtn_h.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = homepage;
					}
				}
		}
	case showrank:
		window -> draw(*background);
		window -> draw(*sbtn_h);
		window -> display(); 
		while(window->pollEvent(*e)){
				if (sbtn_h.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = homepage;
					}
				}
		}
	case introduce:
		window -> draw(*background);
		window -> draw(*sbtn_h);
		window -> display(); 
		while(window->pollEvent(*e)){
				if (sbtn_h.isMouseOver(window)){
					//button1->setTextureRect 改圖片 
					if (Mouse::isButtonPressed(Mouse::Left)){
						Status = homepage;
					}
				}
		}
	dafault:
		break;
}*/
