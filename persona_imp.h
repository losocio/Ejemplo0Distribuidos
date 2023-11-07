//Included by: serverObjetos.cpp
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
		std::vector<unsigned char> rpcIn;
		std::vector<unsigned char> rpcOut;
		//recibe operación
		recvMSG(clientId,rpcIn);
		
		personaOp operacion=unpack<personaOp>(rpcIn);
		
		
		//ejecuta
		switch(operacion)
		{
			case constructorOp:
			{
				
				p=new Persona();
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
			case destructorOp:
			{
				delete p;
				p=nullptr;
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
			case setNombreOp:
			{
				int tam=unpack<int>(rpcIn);
				std::string dato;
				dato.resize(tam);
				unpackv(rpcIn,(char*)dato.data(),tam);
				p->setNombre(dato);
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
			case setDniOp:
			{
				int tam=unpack<int>(rpcIn);
				std::string dato;
				dato.resize(tam);
				unpackv(rpcIn,(char*)dato.data(),tam);
				p->setDni(dato);
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
				
			case loadOp:
			{
				int tam=unpack<int>(rpcIn);
				std::string dato;
				dato.resize(tam);
				unpackv(rpcIn,(char*)dato.data(),tam);
				p->load(dato);
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
			case saveOp:
			{
				int tam=unpack<int>(rpcIn);
				std::string dato;
				dato.resize(tam);
				unpackv(rpcIn,(char*)dato.data(),tam);
				p->save(dato);
				pack(rpcOut,(unsigned char)MSG_OK);
				
			}break;
			
			case getNombreOp:
			{
				std::string dato=p->getNombre();
				int tam=dato.length()+1;

				pack(rpcOut,(unsigned char)MSG_OK);
				pack(rpcOut,tam);
				packv(rpcOut,dato.data(),tam);
				
			}break;
			
			case getDniOp:
			{
				std::string dato=p->getDni();
				int tam=dato.length()+1;

				pack(rpcOut,(unsigned char)MSG_OK);
				pack(rpcOut,tam);
				packv(rpcOut,dato.data(),tam);
				
			}break;
			
			default:
			{
				std::cout<<"Error: función no definida\n";
				pack(rpcOut,(unsigned char)MSG_NOK);
			}break;

		};
		//devuelve resultados
		sendMSG(clientId,rpcOut);	
	};
};