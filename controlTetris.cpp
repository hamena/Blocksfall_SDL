#include "controlTetris.h"

#include <unistd.h>

ControlTetris::ControlTetris(MatrizTetris& mat, Piezas& ps) :
	mt(&mat),
	puntos(0),
	lineas(0),
	nivel(1),
	posX(3),
	posY(1),
	p(NULL),
	pSig(NULL),
	piezas(&ps)
{
	p = piezaAleatoria();
	mt->pintaPiezaEn(*p,posY,posX);
	mt->pintaPuntos(puntos);
	mt->pintaLineas(lineas);
	mt->pintaNivel(nivel);
	usleep(1000000);
	pSig = piezaAleatoria();
	mt->pintaPiezaSig(*pSig);
}

void ControlTetris::siguientePieza(){
	posX = 3;
	posY = 1;
	if(p != NULL) delete p;
	p = pSig;
	pSig = NULL;
	if(!mt->pintaPiezaEn(*p,posY,posX))	throw(GameOver(*mt));
	pSig = piezaAleatoria();
	mt->pintaPiezaSig(*pSig);
}

void ControlTetris::caerPieza(){
	while(mt->pintaPiezaEn(*p,posY+1,posX))
		posY++;
	mt->pintaPiezaEn(*p,posY,posX);
	mt->vaciaVector();
	incrementarPuntos(50);
	limpiaLineas();
	siguientePieza();
}

void ControlTetris::limpiaLineas(){
	int fila = mt->alto() - 1;
	bool linea = false;
	while(fila >= 0 && !linea){
		if(mt->detectaLinea(fila)){
			incrementarLineas(1);
			incrementarPuntos(1000);
			mt->borraLinea(fila);
		}
		else
			fila--;
	}
}

Pieza* ControlTetris::piezaAleatoria(){
	PiezaL* pl = &piezas->piezaL;
	PiezaL2* pl2 = &piezas->piezaL2;
	PiezaS* ps = &piezas->piezaS;
	PiezaS2* ps2 = &piezas->piezaS2;
	PiezaT* pt = &piezas->piezaT;
	PiezaC* pc = &piezas->piezaC;
	PiezaP* pp = &piezas->piezaP;
	
	srand(time(0));
	switch(rand()%16){
		case 1: case 10: case 15:
			return new Pieza2(ps->v1, ps->v2, ps->dim);
			break;
		case 2: case 11: case 8:
			return new Pieza2(ps2->v1, ps2->v2, ps2->dim);
			break;
		case 3: case 12: case 7:
			return new Pieza4(pl->v1, pl->v2, pl->v3, pl->v4, pl->dim);
			break;
		case 13: case 14: case 9:
			return new Pieza4(pl2->v1, pl2->v2, pl2->v3, pl2->v4, pl2->dim);
			break;
		case 0: case 5:
			return new Pieza4(pt->v1, pt->v2, pt->v3, pt->v4, pt->dim);
			break;
		case 6:
			return new Pieza1(pc->v1, pc->dim);
			break;
		case 4:
			return new Pieza2(pp->v1, pp->v2, pp->dim);
			break;
		default:
			throw RandomException("PIEZA FUERA DE SWITCH");
	}
}

void ControlTetris::pause(){
	/*while(true)
		if(ControlTetris::kbhit())				//KBHIT
			if(getch() == 'p')
				break;*/
}
