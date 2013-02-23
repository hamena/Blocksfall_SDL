#include "matriztetris.h"

MatrizTetris::MatrizTetris(unsigned alto, unsigned ancho) : 
	m( Matriz<bool>(alto,ancho,NULL) )
	//c(ch)
{
	//inicializaM1();
	//inicializaM2();
	
	inicializaSDL();
	fondo = SDL_LoadBMP("recursos/fondo.bmp");
	bloque = SDL_LoadBMP("recursos/bloque.bmp");
	SDL_BlitSurface(fondo,NULL,pantalla,NULL);
}

/*void MatrizTetris::inicializaM1(){
	m1.rellenaFila(0,c);
	m1.rellenaFila(m1.dimensionY()-1,c);
	m1.rellenaColumna(0,c);
	m1.rellenaColumna(m1.dimensionX()-1,c);
}*/

/*void MatrizTetris::inicializaM2(){
	for(unsigned i=0 ; i<m2.dimensionY() ; i++)
		for(unsigned j=0 ; j<m2.dimensionX() ; j++)
			m2[i][j] = ' ';
	m2.rellenaColumna(m2.dimensionX()-1,c);
	m2.rellenaFila(0,c);
	m2.rellenaFila(7,c);
	m2.rellenaFila(12,c);
	m2.rellenaFila(16,c);
	m2[8][0] = 'S'; m2[8][1] = 'c'; m2[8][2] = 'o'; m2[8][3] = 'r'; m2[8][4] = 'e';
	m2[10][0] = 'L'; m2[10][1] = 'n'; m2[10][2] = 'a'; m2[10][3] = 's';
	m2[13][0] = 'L'; m2[13][1] = 'e'; m2[13][2] = 'v'; m2[13][3] = 'e'; m2[13][4] = 'l';
}*/

void MatrizTetris::inicializaSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout<<"No se pudo iniciar SDL: "<<SDL_GetError()<<std::endl;
		exit(1);
	}
	
	pantalla = SDL_SetVideoMode(640,480,24,SDL_HWSURFACE);
	if(pantalla == NULL){
		std::cout<<"No se puede inicializar el modo gráfico: "<<SDL_GetError()<<std::endl;
		exit(1);
	}
}

bool MatrizTetris::pintaPiezaEn(const Pieza& p, unsigned y, unsigned x){
	if(!v.empty()) borraPieza();
	if(!detectaColision(p.vectorEstado(),y,x)){
		SDL_Rect d;
		d.w = bloque->w;
		d.h = bloque->h;
		posX = x;
		posY = y;
		v = p.vectorEstado();
		for(unsigned i=0 ; i<v.size() ; i++){
			//m1[y + v[i].first][x + v[i].second] = '#';
			
			d.x = XI + (x + v[i].second)*TAMBLO;
			d.y = YI + (y + v[i].first)*TAMBLO;
			SDL_BlitSurface(bloque,NULL,pantalla,&d);
			m[y + v[i].first][x + v[i].second] = true;
		}
		return true;
	}
	else return false;
}

bool MatrizTetris::detectaColision(const vEstado& v, unsigned y, unsigned x){
	for(unsigned i=0 ; i<v.size() ; i++)
		if((y + v[i].first) < m.dimensionY() && (x + v[i].second) < m.dimensionX()){
			if(m[y + v[i].first][x + v[i].second])
				return true;
		}
		else
			return true;
	
	return false;
}

bool MatrizTetris::detectaLinea(int fila){
	for(unsigned j=0 ; j<m.dimensionX() ; j++){
		if(!m[fila][j])
			return false;
	}
	return true;
}

void MatrizTetris::borraPieza(){
	SDL_Rect d;
	d.w = bloque->w;
	d.h = bloque->h;
	for(unsigned i=0 ; i<v.size() ; i++){
		d.x = XI + (posX + v[i].second)*TAMBLO;
		d.y = YI + (posY + v[i].first)*TAMBLO;
		SDL_FillRect(pantalla,&d,SDL_MapRGB(pantalla->format,CFR,CFG,CFB));
		m[posY + v[i].first][posX + v[i].second] = false;
	}
}

void MatrizTetris::pintaPiezaSig(const Pieza& p){
	/*if(!vSig.empty()) borraPiezaSig();
	vSig = p.vectorEstado();
	for(unsigned i=0 ; i<vSig.size() ; i++)
		m2[2 + vSig[i].first][1 + vSig[i].second] = '#';*/
}

void MatrizTetris::borraPiezaSig(){
	/*for(unsigned i=0 ; i<vSig.size() ; i++)
		m2[2 + vSig[i].first][1 + vSig[i].second] = ' ';*/
}

void MatrizTetris::pintaPuntos(const Contador& c){
	/*const vector<int>& v = c.vectorPuntos();
	for(unsigned j=0 ; j<v.size() ; j++)
		m2[9][j] = v[j] + 48;*/
}

void MatrizTetris::pintaLineas(const Contador& c){
	/*const vector<int>& v = c.vectorPuntos();
	for(unsigned j=0 ; j<v.size() ; j++)
		m2[11][j+1] = v[j] + 48;*/
}

void MatrizTetris::pintaGameOver(){
	/*unsigned dim = m1.dimensionX() / 2;
	for(unsigned i=1 ; i<7 ; i++)
		for(unsigned j=dim-3 ; j< dim+3 ; j++)
			m1[i][j] = ' ';
			
	m1[2][dim-2] = 'G';
	m1[2][dim-1] = 'A';
	m1[2][dim]	 = 'M';
	m1[2][dim+1] = 'E';
	m1[5][dim-2] = 'O';
	m1[5][dim-1] = 'V';
	m1[5][dim]	 = 'E';
	m1[5][dim+1] = 'R';*/
}

void MatrizTetris::borraLinea(unsigned linea){
	SDL_Rect d;
	d.w = bloque->w;
	d.h = bloque->h;
	d.y = YI + linea*TAMBLO;
	for(unsigned j=0 ; j<m.dimensionX() ; j++){
		d.x = XI + j*TAMBLO;
		SDL_FillRect(pantalla,&d,SDL_MapRGB(pantalla->format,CFR,CFG,CFB));
		m[linea][j] = false;
	}
	bajarTodo(linea-1);
}

void MatrizTetris::bajarTodo(unsigned linea){
	SDL_Rect d;
	d.w = bloque->w;
	d.h = bloque->h;
	
	for(int i=linea ; i>=0 ; i--){
		d.y = YI + (i+1)*TAMBLO;
		for(unsigned j=0 ; j<m.dimensionX() ; j++){
			d.x = XI + j*TAMBLO;
			if(m[i][j]){
				SDL_BlitSurface(bloque,NULL,pantalla,&d);
				m[i+1][j] = true;
			}
			else{
				SDL_FillRect(pantalla,&d,SDL_MapRGB(pantalla->format,CFR,CFG,CFB));
				m[i+1][j] = false;
			}
		}
	}
	d.y = YI;
	for(unsigned j=0 ; j<m.dimensionX() ; j++){
		d.x = XI + j*TAMBLO;
		SDL_FillRect(pantalla,&d,SDL_MapRGB(pantalla->format,CFR,CFG,CFB));
		m[0][j] = false;
	}
}

void MatrizTetris::imprimeMatriz() const{
	/*unsigned dim1 = m1.dimensionX();
	unsigned dim2 = m2.dimensionX();
	for(unsigned i=0 ; i<m1.dimensionY() ; i++){
		for(unsigned j=0 ; j<dim1 ; j++)
			addch(m1[i][j]);
		for(unsigned j=0 ; j<dim2 ; j++)
			addch(m2[i][j]);
		addch('\n');
	}
	refresh();*/
	
	SDL_Flip(pantalla);
}

ostream& operator <<(ostream& os, const MatrizTetris& mt){
	/*unsigned dim1 = mt.m1.dimensionX();
	unsigned dim2 = mt.m2.dimensionX();
	for(unsigned i=0 ; i<mt.m1.dimensionY() ; i++){
		for(unsigned j=0 ; j<dim1 ; j++)
			os<<mt.m1[i][j];
		for(unsigned j=0 ; j<dim2 ; j++)
			os<<mt.m2[i][j];
		os<<endl;
	}*/
	return os;
}
