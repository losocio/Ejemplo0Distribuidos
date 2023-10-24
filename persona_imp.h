#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"
#include "persona.h"

class Persona_imp{
	private:
	int clientId=-1;
	Persona* p=nullptr;

	public:
	Persona_imp(int clientId): clientId(clientId){};

	bool connectionClosed()
	{
		return p==nullptr;
	}

	void recibeOp()
	{
	//recibe operacion
		std::vector<unsigned char> rpcIn;
		std::vector<unsigned char> rpcOut;
		recvMSG(clientId,rpcIn);
	
		personaOp operacion=unpack<personaOp>(rpcIn);
	//ejecuta
		switch(operacion)
		{
			case constructorOp:
			{
				p=new Persona();
				pack(rpcOut, (unsigned char)MSG_OK);

			}break;
			case destructorOp:
                        {
				delete p;
				p=nullptr;
				pack(rpcOut, (unsigned char)MSG_OK);
			}break;
			default:
			{
				std::cout<<"Error: funcion no definida\n";
				pack(rpcOut, (unsigned char)MSG_NOK);
			}break;
		};
	//devuelve resultado
		sendMSG(clientId,rpcOut);
	};

};
