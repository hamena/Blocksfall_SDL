#include "matriztetris.h"

MatrizTetris::MatrizTetris(unsigned alto, unsigned ancho) : 
	m( Matriz<bool>(alto,ancho,NULL) )
{
	inicializaSDL();
	inicializaTTF();
	cargaGraficos();
	SDL_BlitSurface(fondo,NULL,pantalla,NULL);
}

void MatrizTetris::inicializaSDL(){
	cout<<"\tInicializando SDL...";
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout<<"FAIL"<<endl;
	}else
		cout<<"OK"<<endl;
	
	cout<<"\tInicializando ventana...";
	pantalla = SDL_SetVideoMode(VENTANA_W,VENTANA_H,BPP,SDL_SWSURFACE|SDL_DOUBLEBUF);
	if(pantalla == NULL){
		cout<<"FAIL"<<endl;
	}else
		cout<<"OK"<<endl;
}

void MatrizTetris::inicializaTTF(){
	cout<<"\tInicializando TTF...";
	if(TTF_Init() < 0){
		cout<<"FAIL"<<endl;
	}else
		cout<<"OK"<<endl;
	
	cout<<"\tCargando fuentes..."<<endl;
	cout<<"\t\tfuente60...";
	fuente60 = TTF_OpenFont("recursos/Russian.ttf",60);
	if(!fuente60) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
	
	cout<<"\t\tfuente40...";
	fuente40 = TTF_OpenFont("recursos/Russian.ttf",40);
	if(!fuente40) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
}

void MatrizTetris::cargaGraficos(){
	cout<<"\tCargando graficos..."<<endl;
	cout<<"\t\tfondo...";
	fondo = SDL_LoadBMP("recursos/fondo.bmp");
	if(!fondo) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
	
	cout<<"\t\tbloque...";
	bloque = SDL_LoadBMP("recursos/bloque.bmp");
	if(!bloque) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
	
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	
	cout<<"\t\ttextoPuntos...";
	textoPuntos = TTF_RenderText_Blended(fuente60,"00000",color);
	if(!textoPuntos) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
	
	cout<<"\t\ttextoNivel...";
	textoNivel = TTF_RenderText_Blended(fuente40,"1",color);
	if(!textoNivel) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
	
	cout<<"\t\ttextoLineas...";
	textoLineas = TTF_RenderText_Blended(fuente40,"000",color);
	if(!textoLineas) cout<<"FAIL"<<endl;
	else cout<<"OK"<<endl;
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
	SDL_Rect dest;
	dest.x = 260;
	dest.y = YS;
	dest.w = 110;
	dest.h = 110;
	SDL_FillRect(pantalla,&dest,SDL_MapRGB(pantalla->format,CFIR,CFIG,CFIB));
	
	dest.w = TAMBLO;
	dest.h = TAMBLO;
	vSig = p.vectorEstado();
	for(unsigned i=0 ; i<vSig.size() ; i++){
		dest.x = XS + (vSig[i].second * TAMBLO);
		dest.y = YS + (vSig[i].first * TAMBLO);
		SDL_BlitSurface(bloque,NULL,pantalla,&dest);
	}
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

void MatrizTetris::imprimeMatriz() const{ SDL_Flip(pantalla); }

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
