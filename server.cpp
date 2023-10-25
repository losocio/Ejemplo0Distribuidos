#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "operaciones.h"

// Implementacion operacion suma
template <typename T>
T suma(T op1, T op2)
{
	
	return op1+op2;
	
}

// Implementacion operacion suma de Vector3i
int* sumaVector3i(int* op1, int* op2)
{
	int* res=new int[3];
	for (int i=0;i<3;i++)
		res[i]=op1[i]+op2[i];
	return res;
	
}

// Atiende peticion del cliente para realiza una operacion
void atiendeOperacion(int clientId){
	    std::vector<unsigned char> rpcIn;
		// Se usa recvMSG() para en recibir y guardar los datos de la operacion (como su tipo, etc). Dichos datos se guardan en el vector rpcIn
	    recvMSG(clientId,rpcIn);
		// Se utiliza desempaquetaOperacion() para sacar el objeto de tipo operacion_t del mensaje recibido
	    operacion_t op=desempaquetaOperacion(rpcIn);
	   
	   // Se realiza el computo dependiendo del tipo de operacion que nos pida el cliente
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
	// Iniciar un servidor en puerto 60000
    auto serverSocket=initServer(60000);

    while(1){
		// Esperar conexiones en puerto
        while(!checkClient()){
            usleep(1000);
        }
		
		// Una vez hay conexion, se atienden las peticiones del cliente 
        int clientId=getLastClientID();
	    atiendeOperacion(clientId);
		atiendeOperacion(clientId);

		// Cerrar conexion
	    closeConnection(clientId);
    }

    close(serverSocket);
    return 0;
      
}
