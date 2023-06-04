#include <iostream>
#include <SFML/Graphics.hpp>
#include "test.hpp"
int main(){
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width/2)-445,(sf::VideoMode::getDesktopMode().height/2)-480);
	window.create(sf::VideoMode(1000,600),"SFML PRoject", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	sf::Font cirno;
	cirno.loadFromFile("cirno.ttf");
	Textbox textbox1(40,sf::Color::White,true);
	textbox1.setFont(cirno);
	textbox1.setPosition({100,100});  //textbox��m 
	textbox1.setLimit(true,29);  //�]�w�O�_�]��and�r�ƭ��� 
	
	while(window.isOpen()){
		sf::Event Event;
		while(window.pollEvent(Event)){
			switch(Event.type){
				case sf::Event::Closed:
					window.close();
				case sf::Event::TextEntered:   //��r��J�P�w 
					textbox1.typedOn(Event);
			}
		}
		window.clear();
		textbox1.drawTo(window); //drawto�禡 
		window.display();
	}
}
