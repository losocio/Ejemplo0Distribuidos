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
			case setNombreOp:
            {	
				int tam=unpack<int>(rpcIn);
				std:string dato;
				dato.resize(tam);

				unpackv(rpcIn, (char*)dato.data(), tam);
				p->setNombre(dato);

				pack(rpcOut, (unsigned char)MSG_OK);
			}break;
			case setDniOp:
            {	
				int tam=unpack<int>(rpcIn);
				std:string dato;
				dato.resize(tam);

				unpackv(rpcIn, (char*)dato.data(), tam);
				p->setDni(dato);

				pack(rpcOut, (unsigned char)MSG_OK);
			}break;
			case loadOp:
            {	
				int tam=unpack<int>(rpcIn);
				std:string dato;
				dato.resize(tam);

				unpackv(rpcIn, (char*)dato.data(), tam);
				p->load(dato);

				pack(rpcOut, (unsigned char)MSG_OK);
			}break;
			case saveOp:
            {	
				int tam=unpack<int>(rpcIn);
				std:string dato;
				dato.resize(tam);

				unpackv(rpcIn, (char*)dato.data(), tam);
				p->save(dato);

				pack(rpcOut, (unsigned char)MSG_OK);
			}break;
            case getNombreOp:
            {	
				std::string dato=p->getNombre();
                int tam=dato.length()+1;

                pack(rpcOut,tam);
                pack(rpcOut,(unsigned char)MSG_OK); 
                packv(rpcOut,dato.data(),tam);
			}break;
            case getDniOp:
            {	
				std::string dato=p->getDni();
                int tam=dato.length()+1;
                
                pack(rpcOut,tam);
                pack(rpcOut,(unsigned char)MSG_OK); 
                packv(rpcOut,dato.data(),tam);
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


//UNRELATED la practica 1
/*
develop equivalent to persona_stub.h and persona_imp.h

multmatrix.cpp/.h hay que distribuir
distribuir clase multmatrix
enviar datos, realizar computo, recivir resutlado



*/