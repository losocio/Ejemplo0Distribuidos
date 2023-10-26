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
	destructorOp=2,
        setNombreOp=3,
        setDniOp=4,
        saveOp=5,
        loadOp=6
}personaOp;

void setStringOp(int serveId, std::string dato, personaOp op){
        std::vector<unsigned char> rpcOut;
        std::vector<unsigned char> rpcIn;

        pack(rpcOut,op);

        int tam=dato.length()+1;
        pack(rpcOut,tam);

        packv(rpcOut,dato.data(),tam);

        sendMSG(serverId, rpcOut);
        
        recvMSG(serverId, rpcOut);
        if(rpcIn[0]!=MSG_OK){ 
                std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";
        }
}

void recvStringOp(int serveId, std::string& dato, personaOp op){
        std::vector<unsigned char> rpcOut;
        std::vector<unsigned char> rpcIn;

        pack(rpcOut, op);
        sendMSG(serverId, rpcOut);

        recvMSG(serverId, rpcIn);
        unsigned char ok=unpack<unsigned char>(rpcIn);
        if(ok!=MSG_OK)
        {
                std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";
        }else{
                int tam=unpack<int>(rpcIn);
                dato.resize(tam);
                unpackv(rpcIn,(char*)dato.data(),tam);
        }
}

class Persona{
        private: //TODO Cambiar ip cada vez
		std::string ip="172.31.74.9";
		int port=60000;
		connection_t serverConnection;
	public:
                //Constructor
                Persona(){
			//conectar con servidor
			serverConnection=initClient(ip,port);
			personaOp op=constructorOp;
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
			personaOp op=destructorOp;
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
                void setNombre(std::string dato){
                        sendStringOp(serverConnection.serverId, dato, setDniOp);                        
                };

                void setDni(std::string dato){
                        sendStringOp(serverConnection.serverId, dato, setDniOp);
                };
                
                void setEdad(int dato){
                        sendStringOp(serverConnection.serverId, dato, setDniOp);
                };

                //Getters
                std::string getNombre(){
                        std::string dato;
                        recvStringOp(serverConnection.serverId, dato, getNombreOp);
                        return dato;
                };

                std::string getDni(){
                        std::string dato;
                        recvStringOp(serverConnection.serverId, dato, getDniOp);
                        return dato;
                };

                //TODO Lo tenemos que hacer por nuestra cuenta los alumnos
                int getEdad(){};

                void save(std::string fileName){
                        sendStringOp(serverConnection.serverId, fileName, setDniOp);
                };

                void load(std::string fileName){
                        sendStringOp(serverConnection.serverId, fileName, setDniOp);
                };
};
