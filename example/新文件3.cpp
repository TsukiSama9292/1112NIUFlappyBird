using namespace std;
using namespace sf;
enum Status{homepage, inputname, game, gameover, showrank, introduce}gamestatus = homepage;
	
	btn_n.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_n = new Sprite(); //建立精靈  
	sbtn_n -> setTexture(btn_n); //
	//sbtn_n -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_n -> setScale(1.0f, 1.0f); //調整大小 
	
	btn_p.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_p = new Sprite(); //建立精靈  
	sbtn_p -> setTexture(btn_p); //
	//sbtn_p -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_p -> setScale(1.0f, 1.0f); //調整大小 
	
	btn_r.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_r = new Sprite(); //建立精靈  
	sbtn_r -> setTexture(btn_r); //
	//sbtn_r -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_r -> setScale(1.0f, 1.0f); //調整大小 
	
	btn_i.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_i = new Sprite(); //建立精靈  
	sbtn_i -> setTexture(btn_i); //
	//sbtn_i -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_i -> setScale(1.0f, 1.0f); //調整大小 
	
	btn_h.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_h = new Sprite(); //建立精靈  
	sbtn_h -> setTexture(btn_n); //
	//sbtn_h -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_h -> setScale(1.0f, 1.0f); //調整大小 
	
	btn_rp.loadFromFile("./resources/img/btn_play.png"); //載入圖片
	sbtn_rp = new Sprite(); //建立精靈  
	sbtn_rp -> setTexture(btn_rp); //
	//sbtn_rp -> setPosition(400.f - btn1.getSize().x / 2.f , 300.f - btn1.getSize().y / 2.f);
	//sbtn_rp -> setScale(1.0f, 1.0f); //調整大小 

		

switch(Status)
		{
			case homepage:
				auto e = new Event(); 
				while( window->isOpen() ){ //當視窗還開著 
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
		}
