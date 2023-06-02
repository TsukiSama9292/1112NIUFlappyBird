#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
#define TEAMNAME "111_2 NO.5 TEAM - Flappy bird"
#define SOUND_HIT "./AllSundries/sound/hit.wav"
#define SOUND_ADD "./AllSundries/sound/add.wav"
#define SOUND_BGM "./AllSundries/sound/bgm.wav"
#define SOUND_WING "./AllSundries/sound/wing.wav"
#define BACKGROUND "./AllSundries/image/background.png"
#define BIRD "./AllSundries/image/bird.png"
#define PIPE "./AllSundries/image/pipe.png"
#define FONT "./AllSundries/font/flappybird.ttf"
FlappyBird::FlappyBird(){ //�غc��(�l)�A�]�w��l�� 
  setSFML(); //�ѩ�SFML�M�󪺪���]�w���i�b�غc�l����A�ҥH�t�~�I�s��� 
}
void FlappyBird::setSFML(){ //�Ω�]�w��l�� 
	//�ѼƳ]�w 
	g =  frame = 0.f; //�]�w��l���q�B�V(�Ω�]�w�����ϥܻP�ɨ�) 
	interval = 240.f; //�]�w�޹D�϶� 
	count = 0; //�`��-�Ω�ͦ��޹D
	bgm_times = 0; //�]�w�I�����ּ��񤧥��O�� 
	gameover = addscore = false;  //�����B�[�����_ 
	score = 0;  //���Ƭ�0 
	
	//�����]�w 
	window = new RenderWindow(VideoMode(1000, 600),TEAMNAME); //�����]�w 
	window->setPosition(Vector2i(0, 0)); //��l�Ƶ����y�Х��W��(0,0) 
	
	//�ձ��C���t�� 
	window->setFramerateLimit( 60 ); //����̤j�V�ơA�ѩ󥦦b�����ϥ� sf::sleep�A���ר��M�󩳼h�ާ@�t�ΡA���G�]�i�঳�I����T�A
	//window->setFramerateLimit( 0 ); //�L�V�ƭ���A�C���H�̧֪��t�׶i�� 
	
	/*�H�U�O�I�����ϻP���F�]�w*/
	if(!bg.loadFromFile(BACKGROUND))//���J�Ϥ�
		cout<<"Fail loading background.png"<<endl;   
	background = new Sprite(); //�إߺ��F
	background->setTexture(bg); //���F�Ϯ׳]���I����
	//�L���]�w��m�P�j�p ��l��m��(0,0) �����P�ϵ��j 
	
	/*�H�U�O�����ϻP���F�]�w*/
	if(!bd.loadFromFile(BIRD))//���J�Ϥ�
		cout<<"Fail loading bird.png"<<endl;  
	bird = new Sprite(); //�إߺ��F 
	bird->setTexture(bd);  //���F�Ϯ׳]���� 
	bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //�]�w������l��m 
	bird->setScale(2.f, 2.f); //�վ�j�p(���)
	bird->setTextureRect(IntRect(0, 0, 34, 24)); //���ιϤ����A�̥������� 
	
	/*�H�U�O�޹D���ϻP���F�]�w*/
	if(!pipe.loadFromFile(PIPE))//���J�Ϥ� 
		cout<<"Fail loading pipe.png"<<endl;
	pipe.loadFromFile(PIPE); //���J�Ϥ�
	pipeBottom = new Sprite(); //�إߺ��F 
	pipeTop = new Sprite(); //�إߺ��F 
	pipeBottom->setTexture(pipe); //���F�Ϯ׳]���޹D 
	pipeTop->setTexture(pipe); //���F�Ϯ׳]���޹D 
	pipeBottom->setScale(1.5f, 1.5f); //�վ�j�p(���)
	pipeTop->setScale(1.5f, -1.5f); //�վ�j�p(���)�A�t�Ƭ��A�� 
	
	/*�H�U�O�C���������r��P��r�]�w*/
	if(!font.loadFromFile(FONT))//���J�r�� 
		cout<<"Fail loading flappybird.ttf"<<endl; 
	text_gameover.setFont(font); //�M�Φr�� 
	text_gameover.setString("Press SPACE to restart"); //��r���e�]�w 
	text_gameover.setPosition(200, 300); //��m�]�w 
	text_gameover.setCharacterSize(50); //�r��j�p�]�w 
	text_gameover.setOutlineThickness(3); //�r��ʲӳ]�w 
	
	/*�H�U�O���ƪ��r��P��r�]�w*/
	text_score.setFont(font); //�M�Φr�� 
	text_score.setString(std::to_string(score)); //��r���e�]�w  
	text_score.setPosition(10.f, 10.f); //��m�]�w
	text_score.setCharacterSize(50); //�r��j�p�]�w
	text_score.setOutlineThickness(3); //�r��ʲӳ]�w
	
	/*�H�U�O���ĳ]�w*/
	if(!buffer_hit.loadFromFile(SOUND_HIT)) //���J����_hit 
		cout<<"Fail loading hit.wav"<<endl; //���J����_hit 
	if(!buffer_wing.loadFromFile(SOUND_WING)) //���J����_wing
		cout<<"Fail loading wing.wav"<<endl; //���J����_wing 
	if(!buffer_add.loadFromFile(SOUND_ADD)) //���J����_add
		cout<<"Fail loading add.wav"<<endl;	//���J����_add
	if(!buffer_bgm.loadFromFile(SOUND_BGM)) //���J����_bgm
		cout<<"Fail loading bgm.wav"<<endl; //���J����_bgm
	sound_hit.setBuffer(buffer_hit); //���ļ��񾹳]�w_hit 
	sound_wing.setBuffer(buffer_wing); //���ļ��񾹳]�w_wing
	sound_add.setBuffer(buffer_add); //���ļ��񾹳]�w_add
	sound_bgm.setBuffer(buffer_bgm); //���ļ��񾹳]�w_bgm
	sound_bgm.play(); //bgm���ּ��� 
}

void FlappyBird::events(){ //�Ω����������A���s�}�l�C�� 
	auto e = new Event(); //�����ƥ󪫥�]�w 
	while( window->pollEvent( *e ) ){ //�ƥ�o�ͮɰ��� 
		if( e->type == Event::Closed){ //�ƥ�Y���I���������� 
			window->close(); //�������������A�Y�C������ 
		}
	}
	if(gameover && Keyboard::isKeyPressed(Keyboard::Space)){//�C�������ɫ��U�ť���A�Y�i���s�}�l 
		score = 0; //��l�Ƥ���
		bgm_times=0;
		g =  frame = 0.f; //��l�ƭ��q�B�V(�Ω�]�w�����ϥܻP�ɨ�)
		text_score.setString(to_string(score)); //��l�Ƥ��Ƥ�r���e 
		pipes.clear(); //�޹D�����M��
		bird->setPosition(500.f - bd.getSize().x / 2.f , 300.f-bd.getSize().y / 2.f); //��l�Ƴ����y�� 
		gameover = false; //�]�����������_ 
	}
}

void FlappyBird::draw(){ //��s�e���A��V����ܹϥ� 
	window->clear(); //�M����ӵe���A�Ω��s�e���A�F��ʵe�ĪG 
	window->draw(*background); //�ݰ�����ܭI�� 
	window->draw(*bird); //�ݰ�����ܳ� 
	for(auto &p:pipes){ //�M���Ҧ��޹D 
		window->draw(p); //�ݰ�����ܺ޹D 
	}
	if(gameover) //�p�G�C������ 
		window->draw(text_gameover); //�ݰ�����ܹC������ 
	window->draw(text_score); //�ݰ�����ܤ��� 
	window->display(); //�I�sOpenGL��V������ե�(���e�V���Ҧ�����ܹϹ���ܦb�e���W) 
}

void FlappyBird::pipeMove(){ //�Ω󲾰ʤ��ޡA�P�������D 

	if(Keyboard::isKeyPressed(Keyboard::Space)&&bird->getPosition().y>25){ //����25�T��W
		sound_wing.play(); //���񴧯ͻH���� 
		bird->setRotation(-frame - 10.f); //����y�L�V�W�� 
		g = -8.f; //�]�w���q�V�U 
	}
	else
		bird->setRotation(frame - 10.f); //����y�L�V�U��
	if( count % 150 == 0 ){ //�C����150���� 
		int pos = rand() % 335 + 25; //�]�w�H������ 
		pipeTop->setPosition(1000, pos);  //�W�޹D�]�w��m
		pipeBottom->setPosition(1000, pos + interval); //�U�޹D�]�w��m 
		pipes.push_back(*pipeTop); //�޹Dvector�s�W�W�޹D 
		pipes.push_back(*pipeBottom); //�޹Dvector�s�W�U�޹D  
	}
	for (size_t i {}; i < pipes.size(); i++) { //�Q��size_t �M������  
		if(pipes[i].getGlobalBounds().intersects(bird->getGlobalBounds())){ //�ͦ��޹D�B�P�����x�ΡA�p�G��x�Υ��|�A���� 
			/*/�]���ͦ��x�η|���޹D�B���Ϥ��H�����઺�A���Y��L���x�Τj�p(�z���]��)�i��ͦ��A�ɭP�ǳ\�j�p���t 
			���F�����ݰ_�ӹ��O���W�h�A�ҥH���������V�e����*/
			bird->move(15.f, 0); 
			if( pipes[i].getScale().y < 0 ) //�p�G(�I���޹Dy�b����Ҥp��0�A�Y�O�W�޹D)�A���� 
				bird->move(0,-10.f); //�y�L�V�W 
			else //�Y���U�޹D 
				bird->move(0,10.f); //�y�L�V�U 
			gameover = true; //�C������ 
			sound_hit.play(); //���������� 
		}
		if(pipes[i].getPosition().x < -150 ){ //�޹D��x�b�b�e������150(�W�X�e��) 
			pipes.erase(pipes.begin() + i );  //�M���޹D 
		} 
		pipes[i].move(-4.f, 0); //�޹D�V������ 
		if(pipes[i].getPosition().x == 408 && !addscore ){ //��޹D�񳾧�a�����A�B�٥��[�� 
			text_score.setString(to_string(++score)); //��ܤ��ƼW�[ 
			sound_add.play(); //����[������  
			addscore = true; //�]�w�w�g�[�L���ƤF�A�קK�W�U�޹D���[�� 
		}else //�t�@�Ӻ޹D�q�L�A�N��]�w�٥��[�L���ơA�ϤU�����~��[�� 
			addscore = false;
	}
}

void FlappyBird::birdAnime(){ //�]�w�����ʵe 
	frame += 0.15f; // �]�w�V 
	if( frame > 3 ){ // ��j��T
		frame -= 3; // �]��-3�A�s�y�`�����Pı 
	}	
	bird->setTextureRect(IntRect( 34 * (int)frame, 0, 34, 24 )); //�]�w�ϥܨ��˽d�� 
}

void FlappyBird::birdMove(){ //���ʳ� 
	bird->move(0, g); //�V�U�Y�� 
	g += 0.5f; //�v���W�� 
	if(bird->getPosition().y>650){ //���ӳ��W�X�e��(y>650) 
		sound_hit.play(); //����������  
		gameover = true; //�C������ 
	}
}

void FlappyBird::game(){ //������F���ʻP�������D�M�ʵe 
	if(!gameover){ //�٨S�����C��
		birdAnime(); //�I�s�����ʵe 
		birdMove(); //�I�s�����첾 
		pipeMove(); //�I�s�޹D���첾 
	}
}

void FlappyBird::run(){ 
	while( window->isOpen() ){ //������ٶ}��
		
		events(); //�I�s���events�A�Ω����������A���s�}�l�C�� 
		game(); //�I�s���game�A������F���ʻP�������D�M�ʵe 
		draw(); //�I�s���draw�A��s�e���A��V����ܹϥ�
		count++; //�`�ƼW�[�A�Ω�޹D�ͦ�
		if( count == 300 ){ //�`�Ƶ���300 
			count = 0; //�`�ƭ��s
			bgmCircle(); //�I�s���֭��Ƽ��� 
		}
	}
}
void FlappyBird::bgmCircle(){ //���֭��Ƽ��� 
	if(bgm_times>=6){ //��count�`��6�� ���s����bgm 
		bgm_times=0; //��l��bgm_times 
		sound_bgm.play(); //���s����bgm 
	}else{
		bgm_times++; //�O��+1 
	}
}

