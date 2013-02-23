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
	curses(false),
	cont(0)
{}

void JuegoTetris::preparar(){
	if(!curses) iniciaCurses();
	
	printw("Preparando vector de tiempos... "); refresh();
	if(!delay){
		int rest = 1000;
		delay = new vector<unsigned>(9,0);
		for(unsigned i=0 ; i<delay->size() ; i++){
			delay->at(i) = rest;
			rest -= 100;
		}
	}
	printw("OK\n"); refresh();
	
	printw("Preparando tablero del tetris... "); refresh();
	if(mt) delete mt;
	mt = new MatrizTetris();
	printw("OK\n"); refresh();
	
	printw("Preparando piezas...\n"); refresh();
	piezas = new Piezas;
	printw("\tPiezaL..."); refresh();
	inicializar(piezas->piezaL);
	printw("OK\n");
	printw("\tPiezaL2..."); refresh();
	inicializar(piezas->piezaL2);
	printw("OK\n");
	printw("\tPiezaS..."); refresh();
	inicializar(piezas->piezaS);
	printw("OK\n");
	printw("\tPiezaS2..."); refresh();
	inicializar(piezas->piezaS2);
	printw("OK\n");
	printw("\tPiezaT..."); refresh();
	inicializar(piezas->piezaT);
	printw("OK\n");
	printw("\tPiezaC..."); refresh();
	inicializar(piezas->piezaC);
	printw("OK\n");
	printw("\tPiezaP..."); refresh();
	inicializar(piezas->piezaP);
	printw("OK\n"); refresh();
	
	printw("Preparando control del tetris... "); refresh();
	if(ct) delete ct;
	ct = new ControlTetris(*mt,*piezas);
	printw("OK\n"); refresh();
	
	LETSPLAYBABY = true;
}

void JuegoTetris::iniciar(){
	if(!curses) iniciaCurses();
	tiempo = SDL_GetTicks();
	while(LETSPLAYBABY){
		try{
			if(ControlTetris::kbhit()){		//KBHIT
				switch(getch()){
					case 's':
						ct->bajarPieza();
						break;
					case 'w':
						ct->rotarPieza();
						break;
					case 'a':
						ct->moverIzqda();
						break;
					case 'd':
						ct->moverDrcha();
						break;
					case ' ':
						ct->caerPieza();
						break;
					case 'p':
						ct->pause();
						break;
					case '0':
						LETSPLAYBABY = false;
						break;
				}
				clearScreen();
				mt->imprimeMatriz();
			}
			if(tocaMover(tiempo,delay->at(ct->getNivel()-1))){
				ct->bajarPieza();
				tiempo = SDL_GetTicks();
				mt->imprimeMatriz();
			}
		}catch(ControlTetris::GameOver){
			finDelJuego();
			nodelay(stdscr, FALSE);
			char continuar = getch();
			nodelay(stdscr, TRUE);
			if(continuar == 'n' || continuar == 'N')
				LETSPLAYBABY = false;
			else
				preparar();
		}
	}
	finCurses();
}

void JuegoTetris::clearScreen(){ //clear(); 
}

void JuegoTetris::iniciaCurses(){
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curses = true;
}

void JuegoTetris::finCurses(){
	endwin();
	curses = false;
}

void JuegoTetris::mostrarControles() const{
	printw("\t# CONTROLES #");
	printw("\n-Izquierda: a\n-Derecha: d\n-Rotar: w\n-Bajar: s\n-Soltar pieza: Espacio\n\n");
	refresh();
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
}

void JuegoTetris::finDelJuego(){
	clearScreen();
	mt->imprimeMatriz();
	usleep(4000000);
	clearScreen();					//LIMPIA PANTALLA
	
	/*printw("\n\t¿Tan solo ");
	printw((char)ct->getPuntos().numero());
	printw(" puntos y ");
	printw((char)ct->getLineas().numero());
	printw(" lineas?\n");
	printw("\t\nNo creo que lo vayas a superar pero aun asi...\n");*/
	printw("Otra partida? [s/n]: ");
	refresh();
}

JuegoTetris::~JuegoTetris(){
	if(curses) finCurses();
	if(delay) delete delay;
	if(mt) delete mt;
	if(ct) delete ct;
}
