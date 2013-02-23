#include "juegotetris.h"

bool tocaMover(Uint32 t_viejo, unsigned t_espera){
	Uint32 t = SDL_GetTicks() - t_viejo;
	return t >= t_espera;
}

JuegoTetris::JuegoTetris() : 
	delay(NULL),
	mt(NULL),
	ct(NULL),
	tiempo(0),
	LETSPLAYBABY(false),
	cont(0)
{}

void JuegoTetris::preparar(){
	//printw("Preparando vector de tiempos... "); refresh();
	if(!delay){
		int rest = 1000;
		delay = new vector<unsigned>(9,0);
		for(unsigned i=0 ; i<delay->size() ; i++){
			delay->at(i) = rest;
			rest -= 100;
		}
	}
	//printw("OK\n"); refresh();
	
	//printw("Preparando tablero del tetris... "); refresh();
	if(mt) delete mt;
	mt = new MatrizTetris();
	//printw("OK\n"); refresh();
	
	//printw("Preparando piezas...\n"); refresh();
	piezas = new Piezas;
	//printw("\tPiezaL..."); refresh();
	inicializar(piezas->piezaL);
	//printw("OK\n");
	//printw("\tPiezaL2..."); refresh();
	inicializar(piezas->piezaL2);
	//printw("OK\n");
	//printw("\tPiezaS..."); refresh();
	inicializar(piezas->piezaS);
	//printw("OK\n");
	//printw("\tPiezaS2..."); refresh();
	inicializar(piezas->piezaS2);
	//printw("OK\n");
	//printw("\tPiezaT..."); refresh();
	inicializar(piezas->piezaT);
	//printw("OK\n");
	//printw("\tPiezaC..."); refresh();
	inicializar(piezas->piezaC);
	//printw("OK\n");
	//printw("\tPiezaP..."); refresh();
	inicializar(piezas->piezaP);
	//printw("OK\n"); refresh();
	
	//printw("Preparando control del tetris... "); refresh();
	if(ct) delete ct;
	ct = new ControlTetris(*mt,*piezas);
	//printw("OK\n"); refresh();
	
	LETSPLAYBABY = true;
}

void JuegoTetris::iniciar(){
	SDL_Event event;
	tiempo = SDL_GetTicks();
	while(LETSPLAYBABY){
		try{
			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_KEYDOWN){		//KBHIT
					switch(event.key.keysym.sym){
						case SDLK_DOWN:
							ct->bajarPieza();
							break;
						case SDLK_UP:
							ct->rotarPieza();
							break;
						case SDLK_LEFT:
							ct->moverIzqda();
							break;
						case SDLK_RIGHT:
							ct->moverDrcha();
							break;
						case SDLK_SPACE:
							ct->caerPieza();
							break;
						//case SDLK_p:
							//ct->pause();
							//break;
						case SDLK_ESCAPE:
							LETSPLAYBABY = false;
							break;
					}
					mt->imprimeMatriz();
				}
			}
			if(tocaMover(tiempo,delay->at(ct->getNivel()-1))){
				ct->bajarPieza();
				tiempo = SDL_GetTicks();
				mt->imprimeMatriz();
			}
		}catch(ControlTetris::GameOver){
			finDelJuego();
			LETSPLAYBABY = false;
		}
	}
}

void JuegoTetris::finDelJuego(){
	mt->imprimeMatriz();
	SDL_Delay(4000);
}

JuegoTetris::~JuegoTetris(){
	if(delay) delete delay;
	if(mt) delete mt;
	if(ct) delete ct;
}
