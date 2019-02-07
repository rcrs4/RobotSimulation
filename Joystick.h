#ifndef Joystick_h
#define Joystick_h

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <queue>
#include <utility>
#define START_PRESSED 1

//apenas uma struct para guardar valores das juntas
typedef struct BUTTONS{
		int val1,val2;
}BUTTONS;
//start  128 e back 64

//classe para funções e variaveis
class Joystick{
	public:
		void getButtons(BUTTONS*);
	private:
		void sreturnPosi(BUTTONS*);
		void breturnPosi(BUTTONS*);
		JOYINFO info;
		int startPressed,backPressed, s1, s2;
		std::queue <std::pair<int, int> > q;
};

//função para verificar o estado dos botões
void Joystick::getButtons(BUTTONS* click){
	//Joystick::JOYINFO info;
		//função da biblioteca windows
		joyGetPos(0, &info);
		//std::cout << info.wButtons << "\n";	

		if(backPressed && !q.empty()){
			//if para caso esteja no estado de retorno ao apertar "back"
			if(q.front().first == 1){
				if(q.front().second == 0){
					(*click).val1 -= 2;
				}else{
					(*click).val1 += 2;
				}
				q.pop();
			}else if(q.front().first == 2){
				if(q.front().second == 0){
					(*click).val2 -= 2;
				}else{
					(*click).val2 += 2;
				}
				q.pop();
			}

		}else if(info.wButtons == 1){//verifica qual botao foi apertado
			(*click).val2 += 2;
			if(startPressed == 1){
				q.push(std::make_pair(2, 1));	
			}
		}else if(info.wButtons == 2){
			(*click).val1 -= 2;
			if(startPressed == 1){
				q.push(std::make_pair(1, 0));	
			}
		}else if(info.wButtons == 4){
			(*click).val1 += 2;
			if(startPressed == 1){
				q.push(std::make_pair(1, 1));	
			}
		}else if(info.wButtons == 8){
			(*click).val2 -= 2;
			if(startPressed == 1){
				q.push(std::make_pair(2, 0));	
			}
		}else if(info.wButtons == 128){
			sreturnPosi(click);//chama a função ao "start" ser apertado
			startPressed = 1;//variavel para saber que o start foi pressionado
		}else if(info.wButtons == 64){
			breturnPosi(click);//chama a função ao "back ser apertado"
			startPressed = 0;//variavel retorna pra 0 para saber que a função do back foi feita
		}

		if(backPressed && q.empty()){
			backPressed = 0;
		}
}

void Joystick::sreturnPosi(BUTTONS* click){
	if(startPressed == 0){
		startPressed = 1;
		s1 = (*click).val1;
		s2 = (*click).val2;
	}
}

void Joystick::breturnPosi(BUTTONS* click){
	if(startPressed == 1){//se start foi pressionado pega a diferença dos valores e guarda em vs1(volta start 1)
		backPressed = 1;
		(*click).val1 = s1;
		(*click).val2 = s2;
	}
}

#endif