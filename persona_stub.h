//Included by: clienteObjetos.cpp
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "operaciones.h"

void sendStringOp( int serverId, std::string dato, personaOp op)
{
	std::vector<unsigned char> rpcOut;
	std::vector<unsigned char> rpcIn;

	pack(rpcOut,op);
	
	int tam=dato.length()+1;
	pack(rpcOut,tam);

	packv(rpcOut,dato.data(),tam);

	sendMSG(serverId,rpcOut);
	
	recvMSG(serverId,rpcIn);
	if(rpcIn[0]!=MSG_OK)
	{
		std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";				
	}
	
}



void recvStringOp( int serverId, std::string& dato,personaOp op)
{
	std::vector<unsigned char> rpcOut;
	std::vector<unsigned char> rpcIn;

	pack(rpcOut,op);
	sendMSG(serverId,rpcOut);


	recvMSG(serverId,rpcIn);
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
	private: //TODO Change ip everytime
		std::string ip="172.31.59.126";
		int port=60000;
		connection_t serverConnection;
	public:
		//constructor
		Persona(){
			//conectar con servidor
			serverConnection=initClient(ip,port);
			personaOp op=constructorOp;
			std::vector<unsigned char> rpcOut;
			std::vector<unsigned char> rpcIn;

			pack(rpcOut,op);
			
			sendMSG(serverConnection.serverId,rpcOut);
			recvMSG(serverConnection.serverId,rpcIn);
			if(rpcIn[0]!=MSG_OK)
			{
				std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";				
			}
		}
		
		//destructor
		~Persona(){
			//cerrar conexión
			personaOp op=destructorOp;
			std::vector<unsigned char> rpcOut;
			std::vector<unsigned char> rpcIn;

			pack(rpcOut,op);
			
			sendMSG(serverConnection.serverId,rpcOut);
			recvMSG(serverConnection.serverId,rpcIn);
			if(rpcIn[0]!=MSG_OK)
			{
				std::cout<<"ERROR "<<__FILE__<<":"<<__LINE__<<"\n";				
			}
			closeConnection(serverConnection.serverId);
		}
		
		//setters
		void setNombre(std::string dato){
			
			
			sendStringOp(serverConnection.serverId, dato, setNombreOp);
			
		};
		void setDni(std::string dato){
			
			sendStringOp(serverConnection.serverId, dato, setDniOp);
			
		};
		void setEdad(int dato){};
		
		//getters
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
			
			sendStringOp(serverConnection.serverId, fileName, saveOp);
			
			
		};
		void load(std::string fileName){
			
			sendStringOp(serverConnection.serverId, fileName, loadOp);

		};
		
	
};