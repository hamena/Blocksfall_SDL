#include "pieza.h"

void Pieza4::rotar(){
	if(estado < 3)
		estado++;
	else
		if(estado == 3)
			estado = 0;
		else
			throw EstadoImposible("Pieza4 tiene un estado imposible");
}

const vEstado& Pieza4::vectorEstado() const{
	switch(estado){
		case 0:
			return v1;
			break;
		case 1:
			return v2;
			break;
		case 2:
			return v3;
			break;
		case 3:
			return v4;
			break;
		default:
			throw EstadoImposible("Pieza4 tiene un estado imposible");
	}
}

void Pieza2::rotar(){
	if(estado == 0)
		estado++;
	else
		if(estado == 1)
			estado = 0;
		else
			throw EstadoImposible("Pieza2 tiene un estado imposible");
}

const vEstado& Pieza2::vectorEstado() const{
	if(estado)
		return v2;
	else
		if(estado == 0)
			return v1;
		else
			throw EstadoImposible("Pieza2 tiene un estado imposible");
}
