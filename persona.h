#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>


class Persona{
	private:
		std::string nombre="";
		int edad=0;
		std::string dni="";
	public:
	
		Persona();
		~Persona();
		
		void setNombre(std::string dato);
		void setDni(std::string dato);
		void setEdad(int dato);
		
		std::string getNombre();
		std::string getDni();
		int getEdad();
	
		void save(std::string fileName);
		void load(std::string fileName);
		
	
};


inline Persona::Persona(){};

inline Persona::~Persona(){};

void Persona::setNombre(std::string dato){nombre=dato;};
void Persona::setDni(std::string dato){dni=dato;};
void Persona::setEdad(int dato){edad=dato;};

std::string Persona::getNombre(){return nombre;};
std::string Persona::getDni(){return dni;};
int Persona::getEdad(){return edad;};

void Persona::save(std::string fileName){
	FILE* f=fopen(fileName.c_str(),"wb");
	
	int length=nombre.length()+1;
	
	fwrite(&length,sizeof(int), 1,f);
	fwrite(nombre.c_str(),sizeof(char),length,f);
	
	length=dni.length()+1;
	
	fwrite(&length,sizeof(int), 1,f);
	fwrite(dni.c_str(),sizeof(char),length,f);
	
	fwrite(&edad,sizeof(int), 1,f);
	
	fclose(f);
};



void Persona::load(std::string fileName){
	
	
	FILE* f=fopen(fileName.c_str(),"rb");
	
	int length=0;
	std::vector<char> dato;
	
	
	fread(&length,sizeof(int), 1,f);
	dato.resize(length);
	fread(dato.data(),length,1,f);
	
	nombre.resize(length);
	std::copy(dato.begin(),dato.end(),nombre.begin());
	
	length=0;
	fread(&length,sizeof(int), 1,f);
	dato.resize(length);
	fread(dato.data(),length,1,f);
	
	dni.resize(length);
	std::copy(dato.begin(),dato.end(),dni.begin());

	fread(&edad,sizeof(int), 1,f);
	
	fclose(f);
	
};