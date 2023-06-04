#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
//�������լO�_�i�H���Obutton 
class Button{
	private:
		float mouse_x,mouse_y,btn_x,btn_y,btn_w,btn_h;
		bool isMouseOver(RenderWindow &window){
			mouse_x = Mouse::getPosition(window).x; //���o�ƹ�x�y�� 
			mouse_y = Mouse::getPosition(window).y; //���o�ƹ�y�y�� 
			btn_x = sbtn->getPosition().x; //���o���sx�y�� 
			btn_y = sbtn->getPosition().y; //���o���sy�y�� 
			btn_w = sbtn->getPosition().x + sbtn->getGlobalBounds().width; //���o���sx�d�� 
			btn_h = sbtn->getPosition().y + sbtn->getGlobalBounds().height; //���o���sy�d�� 
			if (mouse_x < btn_w && mouse_x > btn_x && mouse_y < btn_h && mouse_y > btn_y) //�p�G�ƹ��b���s�d�򤧤� 
				return true; //�^�ǬO 
			return false; //���b�d�� �^�ǧ_ 
		}
	public:
		Texture tbtn;
		Sprite *sbtn;
		bool button_Mouse(RenderWindow &window){ //���s����ϻP���U 
			if (isMouseOver(window)){
				sbtn->setTextureRect(IntRect(tbtn.getSize().x/2.f,0,tbtn.getSize().x/2.f,tbtn.getSize().y)); //�令�ƹ��b�W�Ϥ�
				if (Mouse::isButtonPressed(Mouse::Left)){
					return true;
				}
			}else{
				sbtn->setTextureRect(IntRect(0,0,tbtn.getSize().x/2.f,tbtn.getSize().y));
			}
			return false;
		}
		void drawTo(RenderWindow &window){window.draw(*sbtn);}//�w��V���s 
		Button(){cout<<"Error Button obj!!!";}//�L�ޭȫغc��(���~�غc����)
		Button(string data,float resize,float px,float py){
			tbtn.loadFromFile(data);
			sbtn=new Sprite();
			sbtn->setTexture(tbtn);//�Ϥ��]�w 
			sbtn->setScale(resize,resize);//�j�p(���) 
			sbtn->setTextureRect(IntRect(0,0,tbtn.getSize().x/2.f,tbtn.getSize().y));//���Ϥ��S�w�d�� 
			sbtn->setPosition(px-sbtn->getGlobalBounds().width/2.f,py-sbtn->getGlobalBounds().height/2.f);//�]�w��m 
		}
		
};
