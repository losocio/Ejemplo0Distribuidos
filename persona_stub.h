#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "operaciones.h"

#define MSG_OK 1
#define MSG_NOK 0

typedef enum personaOp{
	constructorOp=1,
	destructorOp=2
}personaOp;


class Persona{
        private:
		std::string ip="172.31.74.9";
		int port=60000;
		connection_t serverConnection;
	public:
                //Constructor
                Persona(){
			//conectar con servidor
			serverConnection=initClient(ip,port);
			personaOP op=constructorOp;
			std::vector<unsigned char> rpcOut;
			std::vector<unsigned char> rpcIn;

			pack(rpcOut,op);

			sendMSG(serverConnection.serverId,rpcOut);
			recvMSG(serverConnection.serverId,rpcIn);
			if(rpcIn[0]!=MSG_OK){
				std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";
			}
		}

                //Destructor
                ~Persona(){
			personaOP op=destructorOp;
                        std::vector<unsigned char> rpcOut;
			std::vector<unsigned char> rpcIn;

                        pack(rpcOut,op);

                        sendMSG(serverConnection.serverId,rpcOut);
                        recvMSG(serverConnection.serverId,rpcIn);
                        if(rpcIn[0]!=MSG_OK){ 
                                std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";
                        }

			closeConnection(serverConnection.serverId);
		}

                //Setters
                void setNombre(std::string dato);
                void setDni(std::string dato);
                void setEdad(int dato);

                //Getters
                std::string getNombre();
                std::string getDni();
                int getEdad();

                void save(std::string fileName);
                void load(std::string fileName);
};
