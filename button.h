#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
//此為測試是否可以類別button 
class Button{
	private:
		float mouse_x,mouse_y,btn_x,btn_y,btn_w,btn_h;
		bool isMouseOver(RenderWindow &window){
			mouse_x = Mouse::getPosition(window).x; //取得滑鼠x座標 
			mouse_y = Mouse::getPosition(window).y; //取得滑鼠y座標 
			btn_x = sbtn->getPosition().x; //取得按鈕x座標 
			btn_y = sbtn->getPosition().y; //取得按鈕y座標 
			btn_w = sbtn->getPosition().x + sbtn->getGlobalBounds().width; //取得按鈕x範圍 
			btn_h = sbtn->getPosition().y + sbtn->getGlobalBounds().height; //取得按鈕y範圍 
			if (mouse_x < btn_w && mouse_x > btn_x && mouse_y < btn_h && mouse_y > btn_y) //如果滑鼠在按鈕範圍之內 
				return true; //回傳是 
			return false; //不在範圍內 回傳否 
		}
	public:
		Texture tbtn;
		Sprite *sbtn;
		bool button_Mouse(RenderWindow &window){ //按鈕之改圖與按下 
			if (isMouseOver(window)){
				sbtn->setTextureRect(IntRect(tbtn.getSize().x/2.f,0,tbtn.getSize().x/2.f,tbtn.getSize().y)); //改成滑鼠在上圖片
				if (Mouse::isButtonPressed(Mouse::Left)){
					return true;
				}
			}else{
				sbtn->setTextureRect(IntRect(0,0,tbtn.getSize().x/2.f,tbtn.getSize().y));
			}
			return false;
		}
		void drawTo(RenderWindow &window){window.draw(*sbtn);}//預渲染按鈕 
		Button(){cout<<"Error Button obj!!!";}//無引值建構元(錯誤建構物件)
		Button(string data,float resize,float px,float py){
			tbtn.loadFromFile(data);
			sbtn=new Sprite();
			sbtn->setTexture(tbtn);//圖片設定 
			sbtn->setScale(resize,resize);//大小(比例) 
			sbtn->setTextureRect(IntRect(0,0,tbtn.getSize().x/2.f,tbtn.getSize().y));//取圖片特定範圍 
			sbtn->setPosition(px-sbtn->getGlobalBounds().width/2.f,py-sbtn->getGlobalBounds().height/2.f);//設定位置 
		}
		
};
