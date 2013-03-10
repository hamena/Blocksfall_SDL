#include "piezas_src.h"

void inicializar(PiezaL& p){
	p.v1.push_back(make_pair(0,1));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(2,1));
	p.v1.push_back(make_pair(2,2));
	
	p.v2.push_back(make_pair(1,0));
	p.v2.push_back(make_pair(1,1));
	p.v2.push_back(make_pair(1,2));
	p.v2.push_back(make_pair(2,0));
		
	p.v3.push_back(make_pair(0,0));
	p.v3.push_back(make_pair(0,1));
	p.v3.push_back(make_pair(1,1));
	p.v3.push_back(make_pair(2,1));
		
	p.v4.push_back(make_pair(1,2));
	p.v4.push_back(make_pair(2,2));
	p.v4.push_back(make_pair(2,1));
	p.v4.push_back(make_pair(2,0));
	p.dim = 3;
	p.bloque = SDL_LoadBMP("recursos/bloque_azul.bmp");
}

void inicializar(PiezaL2& p){
	p.v1.push_back(make_pair(0,1));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(2,1));
	p.v1.push_back(make_pair(2,0));
		
	p.v2.push_back(make_pair(1,0));
	p.v2.push_back(make_pair(2,0));
	p.v2.push_back(make_pair(2,1));
	p.v2.push_back(make_pair(2,2));
		
	p.v3.push_back(make_pair(0,1));
	p.v3.push_back(make_pair(0,2));
	p.v3.push_back(make_pair(1,1));
	p.v3.push_back(make_pair(2,1));
	
	p.v4.push_back(make_pair(1,0));
	p.v4.push_back(make_pair(1,1));
	p.v4.push_back(make_pair(1,2));
	p.v4.push_back(make_pair(2,2));
	p.dim = 3;
	p.bloque = SDL_LoadBMP("recursos/bloque_verde.bmp");
}

void inicializar(PiezaS& p){
	p.v1.push_back(make_pair(0,2));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(1,2));
	p.v1.push_back(make_pair(2,1));
	
	p.v2.push_back(make_pair(1,0));
	p.v2.push_back(make_pair(1,1));
	p.v2.push_back(make_pair(2,1));
	p.v2.push_back(make_pair(2,2));
	p.dim = 3;
	p.bloque = SDL_LoadBMP("recursos/bloque_amarillo.bmp");
}

void inicializar(PiezaS2& p){
	p.v1.push_back(make_pair(0,0));
	p.v1.push_back(make_pair(1,0));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(2,1));
	
	p.v2.push_back(make_pair(1,1));
	p.v2.push_back(make_pair(1,2));
	p.v2.push_back(make_pair(2,0));
	p.v2.push_back(make_pair(2,1));
	p.dim = 3;
	p.bloque = SDL_LoadBMP("recursos/bloque_rojo.bmp");
}

void inicializar(PiezaT& p){
	p.v1.push_back(make_pair(0,1));
	p.v1.push_back(make_pair(1,0));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(1,2));
	
	p.v2.push_back(make_pair(0,1));
	p.v2.push_back(make_pair(1,1));
	p.v2.push_back(make_pair(1,2));
	p.v2.push_back(make_pair(2,1));
	
	p.v3.push_back(make_pair(1,0));
	p.v3.push_back(make_pair(1,1));
	p.v3.push_back(make_pair(1,2));
	p.v3.push_back(make_pair(2,1));
	
	p.v4.push_back(make_pair(0,1));
	p.v4.push_back(make_pair(1,0));
	p.v4.push_back(make_pair(1,1));
	p.v4.push_back(make_pair(2,1));
	p.dim = 3;
	p.bloque = SDL_LoadBMP("recursos/bloque_verdeosc.bmp");
}

void inicializar(PiezaC& p){
	p.v1.push_back(make_pair(0,0));
	p.v1.push_back(make_pair(0,1));
	p.v1.push_back(make_pair(1,0));
	p.v1.push_back(make_pair(1,1));
	p.dim = 2;
	p.bloque = SDL_LoadBMP("recursos/bloque_morado.bmp");
}

void inicializar(PiezaP& p){
	p.v1.push_back(make_pair(0,1));
	p.v1.push_back(make_pair(1,1));
	p.v1.push_back(make_pair(2,1));
	p.v1.push_back(make_pair(3,1));
	
	p.v2.push_back(make_pair(1,0));
	p.v2.push_back(make_pair(1,1));
	p.v2.push_back(make_pair(1,2));
	p.v2.push_back(make_pair(1,3));
	p.dim = 4;
	p.bloque = SDL_LoadBMP("recursos/bloque_celeste.bmp");
}
