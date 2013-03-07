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
	cout<<"Preparando vector de tiempos... ";
	if(!delay){
		int rest = 1000;
		delay = new vector<unsigned>(9,0);
		for(unsigned i=0 ; i<delay->size() ; i++){
			delay->at(i) = rest;
			rest -= 100;
		}
	}
	cout<<"OK\n";
	
	cout<<"Preparando tablero del tetris... "<<endl;
	if(mt) delete mt;
	mt = new MatrizTetris();
	
	cout<<"Preparando piezas...\n";
	piezas = new Piezas;
	cout<<"\tPiezaL...";
	inicializar(piezas->piezaL);
	cout<<"OK\n";
	cout<<"\tPiezaL2...";
	inicializar(piezas->piezaL2);
	cout<<"OK\n";
	cout<<"\tPiezaS...";
	inicializar(piezas->piezaS);
	cout<<"OK\n";
	cout<<"\tPiezaS2...";
	inicializar(piezas->piezaS2);
	cout<<"OK\n";
	cout<<"\tPiezaT...";
	inicializar(piezas->piezaT);
	cout<<"OK\n";
	cout<<"\tPiezaC...";
	inicializar(piezas->piezaC);
	cout<<"OK\n";
	cout<<"\tPiezaP...";
	inicializar(piezas->piezaP);
	cout<<"OK\n";
	
	cout<<"Preparando control del tetris... ";
	if(ct) delete ct;
	ct = new ControlTetris(*mt,*piezas);
	cout<<"OK\n";
	
	LETSPLAYBABY = true;
}

void JuegoTetris::iniciar(){
	SDL_Event event;
	tiempo = SDL_GetTicks();
	while(LETSPLAYBABY){
		try{
			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_KEYDOWN){		//KBHIT
					/*switch(event.key.keysym.sym){
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
						case SDLK_ESCAPE:
							LETSPLAYBABY = false;
							break;
						default:
							if(event.key.keysym.sym == SDLK_p)
								ct->pause();
					}*/
					if(event.key.keysym.sym == SDLK_DOWN)
						ct->bajarPieza();
					else if(event.key.keysym.sym == SDLK_UP)
						ct->rotarPieza();
					else if(event.key.keysym.sym == SDLK_LEFT)
						ct->moverIzqda();
					else if(event.key.keysym.sym == SDLK_RIGHT)
						ct->moverDrcha();
					else if(event.key.keysym.sym == SDLK_SPACE)
						ct->caerPieza();
					else if(event.key.keysym.sym == SDLK_p)
						ct->pause();
					else if(event.key.keysym.sym == SDLK_ESCAPE)
						LETSPLAYBABY = false;
					
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
