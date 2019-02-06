#include <stdio.h>
#include "Joystick.h"
#define PORT 8889
#define IP "127.0.0.1"
//#define _WIN32_WINNT 0x501
/*
	compile with -lws2_32 and -lwinmm flag
*/
#pragma comment(lib, "Ws2_32.lib")

using namespace std;
//variaveis do Joystick
BUTTONS click;
Joystick gamepad;
int main(){
	//inicializa o winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//verifica se houve erro ao iniciar
	if(iResult != 0){
		printf("WSAStartup failed: %d\n", iResult);
		return 0;
	}
	/*
		criando a struct que guarda as informações do socket
	*/
	struct sockaddr_in saServer;
	//	setando as informações do socket
	
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = inet_addr(IP);
	saServer.sin_port = htons(PORT); 
	
	//criando o socket para escutar as requisições dos clients
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//linkando o socket com o ip e port
	iResult=bind(listenSocket, (SOCKADDR*) &saServer, sizeof(saServer));
	if(iResult == SOCKET_ERROR){
		printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
	}else printf("Bounded to ip %s and port %d\n",IP, PORT );
	//esperando a requisição de algum client
	if ( listen( listenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
	    printf( "Listen failed with error: %ld\n", WSAGetLastError() );
	    closesocket(listenSocket);
	    WSACleanup();
	    return 1;
	}
	//criando o socket para "lidar" com o client
	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = accept(listenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
	    printf("accept failed: %d\n", WSAGetLastError());
	    closesocket(listenSocket);
	    WSACleanup();
	    return 1;
	}else printf("Connected to client\n");
	
	string data;//apenas para facilitar o manuseio com strings
	char recvbuf[512];//buffer para a msg do client
	int iSendResult;//verificar se tudo da certo com ao enviar a mensagem
	closesocket(listenSocket);
	//while para tratamento da mensagem, recebimento e envio de mensagens
	do{
		memset(recvbuf, 0, sizeof(recvbuf));
		iResult = recv(clientSocket, recvbuf, 512, 0);
		cout << recvbuf << endl;
		data.clear();
		char sendData [512];
		memset(sendData, 0, sizeof(sendData));
		if(iResult > 0){
			int i = 0;
			while(recvbuf[i+1] != '>'){
					//cout << data << endl;
					i++;
					data += recvbuf[i];
			}
			cout <<data<<endl;
			if(data == "CONNECTION_OPEN"){
				data += ";;";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
				
			}else if(data == "GET_NUM_ARMS"){
				data += ";1;";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ARM_CODNAME;1"){
				data += ";NS_00101";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ARM_AXES;1"){
				data += ";111111----";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ARM_AUX;1"){
				data += ";----------";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ARM_BASE;1"){
				data += ";0;0;0;0;0;0";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_TOOL_RMT;1"){
				data += ";false";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ARM_ALL_FRAMES;1"){
				data += ";0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_AUX_BASE;1"){
				data += ";0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_ALL_JNT"){
				data = "GET_ALL_JNT;"; 
				//cout << click.val1 << endl;
				//valores para caso o controle tenha sido apertado
				data += to_string(click.val1)+ ";";
				data += to_string(click.val2);
				data += ";0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0";
				cout << data << endl;
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}else if(data == "GET_IR_TYPES"){
				data += ";0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0";
				//char sendData [512];
				for(int i = 0; i < data.size(); i++){
					sendData[i] = data[i];
				}
				//sendData[data.size()+2] = '\0';
				cout << sendData << endl;
				iSendResult = send(clientSocket, sendData, data.size(), 0);
				if (iSendResult == SOCKET_ERROR) {
			           printf("send failed: %d\n", WSAGetLastError());
			           closesocket(clientSocket);
			           WSACleanup();
			           return 1;
		        }
			}
			//verificação do joystick (função do Joystick.h)
			gamepad.getButtons(&click);
				
		}else if(iResult == 0){//para caso o client pare de enviar msgs
			printf("connection lost\n");
			closesocket(clientSocket);
			return 1;
		}else{//caso ocorra um erro ao receber msg do client
			printf("recv failed: %d\n", WSAGetLastError);
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}
			
	}while(iResult > 0);
	closesocket(clientSocket);
	return 0;
}