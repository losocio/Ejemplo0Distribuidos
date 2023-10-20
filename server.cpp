#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"


template <typename T>
T suma(T op1, T op2)
{
	
	return op1+op2;
	
}

int* sumaVector3i(int* op1, int* op2)
{
	int* res=new int[3];
	for (int i=0;i<3;i++)
		res[i]=op1[i]+op2[i];
	return res;
	
}


void atiendeOperacion(int clientId){
	   std::vector<unsigned char> rpcIn;
	   recvMSG(clientId,rpcIn);
	   operacion_t op=desempaquetaOperacion(rpcIn);
	   
	   switch(op.tipoOperacion)
	   {
		 case opSumaInt:
		 {
			 std::vector<int> res(1);
			 res[0]=suma(op.sumaInt.operando1,op.sumaInt.operando2);
			 sendMSG(clientId,res);
		 }break;
		 
		 case opSumaFloat:
		 {
			 std::vector<float> res(1);
			 res[0]=suma(op.sumaFloat.operando1,op.sumaFloat.operando2);
			 sendMSG(clientId,res);
		 }break;
		 
		 case opSumaDoubles:
		 {
			 std::vector<double> res(1);
			 res[0]=suma(op.sumaDoubles.operando1,op.sumaDoubles.operando2);
			 sendMSG(clientId,res);
		 }break;
		 case opSumaVector3Int:
		 {
			 std::vector<int> res(3);
			 int* resAux;
			 resAux=sumaVector3i(op.sumaVector3Int.operando1,
								op.sumaVector3Int.operando2);
			 std::copy(&resAux[0],&resAux[3],res.begin());
			 sendMSG(clientId,res);
			 delete[] resAux;
		 }break;
		default:
		{	
			std::cout<<"Error: función no definida\n";
		}		
	   };

}




int main(int argc, char** argv)
{
	//iniciar un servidor
    auto serverSocket=initServer(60000);
    while(1){
		//esperar conexiones en puerto
         while(!checkClient()){
             usleep(1000);
        }
		
		//resolver identificador Cliente
       int clientId=getLastClientID();
	    atiendeOperacion(clientId);
		atiendeOperacion(clientId);

	   closeConnection(clientId);
   }

    close(serverSocket);
    return 0;

      
}
