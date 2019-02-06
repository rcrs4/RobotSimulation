#ifndef Joystick_h
#define Joystick_h

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
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
		int startPressed;
		int s1, s2, vs1, vs2;
};

//função para verificar o estado dos botões
void Joystick::getButtons(BUTTONS* click){
	//Joystick::JOYINFO info;
		//função da biblioteca windows
		joyGetPos(0, &info);
		//std::cout << info.wButtons << "\n";	

		if(vs1!=0 || vs2 != 0){
			//if para caso esteja no estado de retorno ao apertar "back"
			if(vs1 < 0){
				vs1+=2;
				(*click).val1 += 2;
			}else if(vs1 > 0){
				vs1-=2;
				(*click).val1 -=2;
			}else if(vs2 < 0){
				vs2+=2;
				(*click).val2 +=2;
			}else if(vs2 > 0){
				vs2-=2;
				(*click).val2 -=2;
			}

		}else if(info.wButtons == 1){//verifica qual botao foi apertado
			(*click).val1 += 2;
		}else if(info.wButtons == 2){
			(*click).val1 -= 2;
		}else if(info.wButtons == 4){
			(*click).val2 += 2;
		}else if(info.wButtons == 8){
			(*click).val2 -= 2;
		}else if(info.wButtons == 128){
			sreturnPosi(click);//chama a função ao "start" ser apertado
			startPressed = 1;//variavel para saber que o start foi pressionado
		}else if(info.wButtons == 64){
			breturnPosi(click);//chama a função ao "back ser apertado"
			startPressed = 0;//variavel retorna pra 0 para saber que a função do back foi feita
		}
}

void Joystick::sreturnPosi(BUTTONS* click){
	if(startPressed == 0){
		s1 = (*click).val1;//guarda os valores atuais das juntas
		s2 = (*click).val2;
	}
}

void Joystick::breturnPosi(BUTTONS* click){
	
	if(startPressed == 1){//se start foi pressionado pega a diferença dos valores e guarda em vs1(volta start 1)
		vs1 = (*click).val1 - s1;
		vs2 = (*click).val2 - s2;
	}
}

#endif