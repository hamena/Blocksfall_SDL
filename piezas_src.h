#ifndef PIEZAS_SRC_H_
#define PIEZAS_SRC_H_

#include <vector>
#include <utility>

using std::vector;
using std::pair;
using std::make_pair;

typedef vector< pair<unsigned,unsigned> > vEstado;

typedef struct{
	vEstado v1;
	vEstado v2;
	vEstado v3;
	vEstado v4;
	unsigned dim;
} PiezaL;

typedef struct{
	vEstado v1;
	vEstado v2;
	vEstado v3;
	vEstado v4;
	unsigned dim;
} PiezaL2;

typedef struct{
	vEstado v1;
	vEstado v2;
	unsigned dim;
} PiezaS;

typedef struct{
	vEstado v1;
	vEstado v2;
	unsigned dim;
} PiezaS2;

typedef struct{
	vEstado v1;
	vEstado v2;
	vEstado v3;
	vEstado v4;
	unsigned dim;
} PiezaT;

typedef struct{
	vEstado v1;
	unsigned dim;
} PiezaC;

typedef struct{
	vEstado v1;
	vEstado v2;
	unsigned dim;
} PiezaP;

typedef struct{
	PiezaL piezaL;
	PiezaL2 piezaL2;
	PiezaS piezaS;
	PiezaS2 piezaS2;
	PiezaT piezaT;
	PiezaC piezaC;
	PiezaP piezaP;
} Piezas;

void inicializar(PiezaL&);
void inicializar(PiezaL2&);
void inicializar(PiezaS&);
void inicializar(PiezaS2&);
void inicializar(PiezaT&);
void inicializar(PiezaC&);
void inicializar(PiezaP&);

#endif //PIEZAS_SRC_H_
