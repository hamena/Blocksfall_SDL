#include "matriztetris.h"

MatrizTetris::MatrizTetris(unsigned alto, unsigned ancho) : 
  m( Matriz<bool>(alto,ancho,NULL) )
{
  colorFuente.r = 189;
  colorFuente.g = 129;
  colorFuente.b = 71;
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
  cout<<"\t\tfuente25...";
  fuente25 = TTF_OpenFont("recursos/Russian.ttf",25);
  if(!fuente25) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
	
  cout<<"\t\tfuente35...";
  fuente35 = TTF_OpenFont("recursos/Russian.ttf",35);
  if(!fuente35) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
}

void MatrizTetris::cargaGraficos(){
  cout<<"\tCargando graficos..."<<endl;
  cout<<"\t\tfondo...";
  fondo = SDL_LoadBMP("recursos/fondo_mader.bmp");
  if(!fondo) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
	
  cout<<"\t\ttextoPuntos...";
  textoPuntos = TTF_RenderText_Blended(fuente35,"00000",colorFuente);
  if(!textoPuntos) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
	
  cout<<"\t\ttextoMulti...";
  textoMulti = TTF_RenderText_Blended(fuente25,"x1",colorFuente);
  if(!textoMulti) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
	
  cout<<"\t\ttextoNivel...";
  textoNivel = TTF_RenderText_Blended(fuente35,"1",colorFuente);
  if(!textoNivel) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
	
  cout<<"\t\ttextoLineas...";
  textoLineas = TTF_RenderText_Blended(fuente35,"000",colorFuente);
  if(!textoLineas) cout<<"FAIL"<<endl;
  else cout<<"OK"<<endl;
}

bool MatrizTetris::pintaPiezaEn(const Pieza& p, unsigned y, unsigned x){
  if(!v.empty()) borraPieza();
  if(!detectaColision(p.vectorEstado(),y,x)){
    SDL_Rect d;
    d.w = TAMBLO;
    d.h = TAMBLO;
    posX = x;
    posY = y;
    v = p.vectorEstado();
    for(unsigned i=0 ; i<v.size() ; i++){
      d.x = XI + (x + v[i].second)*TAMBLO;
      d.y = YI + (y + v[i].first)*TAMBLO;
      SDL_BlitSurface(p.bloque(),NULL,pantalla,&d);
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
  d.w = TAMBLO;
  d.h = TAMBLO;
  for(unsigned i=0 ; i<v.size() ; i++){
    d.x = XI + (posX + v[i].second)*TAMBLO;
    d.y = YI + (posY + v[i].first)*TAMBLO;
    SDL_BlitSurface(fondo,&d,pantalla,&d);
    m[posY + v[i].first][posX + v[i].second] = false;
  }
}

void MatrizTetris::pintaPiezaSig(const Pieza& p){
  SDL_Rect dest;
  dest.x = XIND;
  dest.y = YI;
  dest.w = 110;
  dest.h = 110;
  SDL_BlitSurface(fondo,&dest,pantalla,&dest);
	
  dest.w = TAMBLO;
  dest.h = TAMBLO;
  vSig = p.vectorEstado();
  for(unsigned i=0 ; i<vSig.size() ; i++){
    dest.x = (XIND + 22) + (vSig[i].second * TAMBLO);
    dest.y = (YI + 11) + (vSig[i].first * TAMBLO);
    SDL_BlitSurface(p.bloque(),NULL,pantalla,&dest);
  }
}

void MatrizTetris::pintaPuntos(unsigned n){
  SDL_Rect dest;
  char* str = new char[6];
  sprintf(str, "%.6d", n);
  textoPuntos = TTF_RenderText_Blended(fuente35,str,colorFuente);
	
  dest.x = XIND;
  dest.y = YP;
  dest.w = 110;
  dest.h = 35;
  SDL_BlitSurface(fondo,&dest,pantalla,&dest);
	
  dest.y -= 4;	//Desplazamiento 4 px hacia arriba.
  dest.x += 4;	//Desplazamiento 4 px a la izq.
  SDL_BlitSurface(textoPuntos,NULL,pantalla,&dest);
  delete[] str;
}

void MatrizTetris::pintaMulti(unsigned n){
  SDL_Rect dest;
  char* str = new char[2];
  str[0] = 'x';
  str[1] = n+48;
  textoMulti = TTF_RenderText_Blended(fuente25,str,colorFuente);
	
  dest.x = XIND;
  dest.y = YM;
  dest.w = 45;
  dest.h = 25;
  SDL_BlitSurface(fondo,&dest,pantalla,&dest);
	
  dest.y -= 5;	//Desplazamiento 4 px hacia arriba.
  dest.x += 4;	//Desplazamiento 4 px a la izq.
  SDL_BlitSurface(textoMulti,NULL,pantalla,&dest);
  delete[] str;
}

void MatrizTetris::pintaNivel(unsigned n){
  SDL_Rect dest;
  char* c = new char[1];
  c[0] = n+48;
  textoNivel = TTF_RenderText_Blended(fuente35,c,colorFuente);
	
  dest.x = XIND;
  dest.y = YN;
  dest.w = 35;
  dest.h = 40;
  SDL_BlitSurface(fondo,&dest,pantalla,&dest);
	
  dest.y -= 3;	//Desplazamiento 3 px hacia arriba.
  dest.x += 7;	//Desplazamiento 7 px a la dcha.
  SDL_BlitSurface(textoNivel,NULL,pantalla,&dest);
  delete[] c;
}

void MatrizTetris::pintaLineas(unsigned n){
  SDL_Rect dest;
  char* str = new char[3];
  sprintf(str, "%.3d", n);
  textoNivel = TTF_RenderText_Blended(fuente35,str,colorFuente);
	
  dest.x = XIND;
  dest.y = YL;
  dest.w = 55;
  dest.h = 40;
  SDL_BlitSurface(fondo,&dest,pantalla,&dest);
	
  dest.y -= 3;	//Desplazamiento 3 px hacia arriba.
  dest.x += 2;	//Desplazamiento 2 px a la izq
  SDL_BlitSurface(textoNivel,NULL,pantalla,&dest);
  delete[] str;
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
  d.w = TAMBLO;
  d.h = TAMBLO;
  d.y = YI + linea*TAMBLO;
  for(unsigned j=0 ; j<m.dimensionX() ; j++){
    d.x = XI + j*TAMBLO;
    SDL_BlitSurface(fondo,&d,pantalla,&d);
    m[linea][j] = false;
  }
  bajarTodo(linea-1);
}

void MatrizTetris::bajarTodo(unsigned linea){
  SDL_Rect d,ant;
  d.w = TAMBLO;
  d.h = TAMBLO;
  ant.w = TAMBLO;
  ant.h = TAMBLO;
	
  for(int i=linea ; i>=0 ; i--){
    d.y = YI + (i+1)*TAMBLO;
    ant.y = YI + i*TAMBLO;
    for(unsigned j=0 ; j<m.dimensionX() ; j++){
      d.x = XI + j*TAMBLO;
      ant.x = XI + j*TAMBLO;
      if(m[i][j]){
	SDL_BlitSurface(pantalla,&ant,pantalla,&d);
	m[i+1][j] = true;
      }
      else{
	SDL_BlitSurface(fondo,&d,pantalla,&d);
	m[i+1][j] = false;
      }
    }
  }
  d.y = YI;
  for(unsigned j=0 ; j<m.dimensionX() ; j++){
    d.x = XI + j*TAMBLO;
    SDL_BlitSurface(fondo,&d,pantalla,&d);
    m[0][j] = false;
  }
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
