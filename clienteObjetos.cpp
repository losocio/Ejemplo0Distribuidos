#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "persona_stub.h"

int main(int argc, char** argv)
{
	Persona p = Persona();
	p.setNombre("Juan");
	p.setDni("0657557K");
	p.setEdad(22);

	p.save("juan.fran");

	return 0;
}
