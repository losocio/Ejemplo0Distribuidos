#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"


int main(int argc, char** argv)
{
	//iniciar conexion
	auto serverConnection=initClient("127.0.0.1",60000);
	/*//mensaje al servidor
	std::string mensaje="Hola server desde cliente\n";
	
	//empaquetar mensaje
	std::vector<char> msgOut;
	msgOut.resize(mensaje.length());
	std::copy(mensaje.begin(),mensaje.end(),msgOut.begin());
	//enviar mensaje
	sendMSG(serverConnection.serverId,msgOut);
	//cerrar conexion*/
	operacion_t op;
	op.tipoOperacion=opSumaInt;
	op.sumaInt.operando1=5;
	op.sumaInt.operando2=7;
	
	std::vector<unsigned char> rpcOut;
	empaquetaOperacion(rpcOut,op); 
	
	

	sendMSG(serverConnection.serverId,rpcOut);
	std::vector<int> res;
	recvMSG(serverConnection.serverId,res);
	
	std::cout<<"El resultado es "<<res[0]<<"\n";
	
	op.tipoOperacion=opSumaVector3Int;
	for(int i=0;i<3;i++)
	{
		op.sumaVector3Int.operando1[i]=i;
		op.sumaVector3Int.operando2[i]=i;
	}
	rpcOut.resize(0);
	
	empaquetaOperacion(rpcOut,op);
	
	sendMSG(serverConnection.serverId,rpcOut);
	res.resize(0);
	recvMSG(serverConnection.serverId,res);
	
	std::cout<<"El segundo resultado es ";
	
	for(auto &r:res)
	{
		std::cout<<r<<",";
	}
	std::cout<<"\n";
	
	closeConnection(serverConnection.serverId);
	return 0;
}