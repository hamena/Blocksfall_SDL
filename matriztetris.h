/// \file matriztetris.h
#ifndef MATRIZ_TETRIS_H_
#define MATRIZ_TETRIS_H_

#define VENTANA_W 390	// Resolución de la ventana
#define VENTANA_H 480	// Resolución de la ventana
#define BPP 24		// Bits por píxeles
#define TAMBLO 22	// Tamaño en píxeles de un bloque
#define XI 20		// Pixeles del marco eje x
#define YI 20		// Pixeles del marco eje y
#define XS 282		// X Pieza siguiente	
#define YS 31		// Y Pieza siguiente
#define XIND 387	// X de los indicadores
#define YP 205		// Y del indicador PUNTOS
#define YN 320		// Y del indicador de NIVEL
#define YL 425		// Y del indicador de LINEAS
#define CFR 75		// Color del fondo RED
#define CFG 70		// Color del fondo GREEN
#define CFB 70		// Color del fondo BLUE
#define CFIR 128	// Color del fondo de indicadores RED
#define CFIG 122	// Color del fondo de indicadores GREEN
#define CFIB 122	// Color del fondo de indicadores BLUE

#include <iostream>
#include <curses.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "matriz.h"
#include "pieza.h"
#include "contador.h"

using std::ostream;
using std::endl;
using std::cout;
using std::string;

/// Unificación del tablero de juego y la información de la partida en una sola entidad.
class MatrizTetris{
	public:
		///Constructor.
		/// \param alto Alto del tablero. Por defecto 17.
		/// \param ancho Ancho del tablero. Por defecto 10.
		/// \param ch Carácter para dibujar los bordes. Por defecto 'X'.
		MatrizTetris(unsigned alto=20, unsigned ancho=10);
		
		/// Pinta una pieza en unas coordenadas
		/// \param p Referencia a la pieza que se quiere pintar.
		/// \param y Coordenada Y donde se pintará la pieza.
		/// \param x Coordenada X donde se pintará la pieza.
		/// \return Verdadero si la pieza ha sido posible de pintar, falso en otro caso.
		bool pintaPiezaEn(const Pieza& p, unsigned y, unsigned x);
		
		/// Pinta la pieza siguiente en la matriz que muestra la información de la partida.
		/// \param p Referencia de la pieza a pintar.
		void pintaPiezaSig(const Pieza& p);
		
		/// Pinta el nº de puntos del contador en la matriz que contiene la información de la partida.
		/// \param c Contador de puntos.
		void pintaPuntos(const Contador& c);
		
		/// Pinta el nº de lineas del contador en la matriz que contiene la información de la partida.
		/// \param c Contador de lineas.
		void pintaLineas(const Contador& c);
		
		/// Pinta en el tablero el mensaje de GAME OVER.
		void pintaGameOver();
		
		/// Pinta el nivel en la matriz que contiene la información de la partida.
		/// \param n Nivel que se va a pintar.
		inline void pintaNivel(unsigned n);
		
		/// Vacía el vector estado actual.
		inline void vaciaVector();
		
		/// Borra la línea deseada.
		/// \param linea Indice donde borrar.
		void borraLinea(unsigned linea);
		
		/// Detecta si hay una línea completa en una fila.
		/// \param fila Indice donde detectar si hay línea completa.
		/// \return Verdadero si hay linea completa, falso si no.
		bool detectaLinea(int fila);
		
		/// Imprime la matriz completa a través de funciones de curses.h
		void imprimeMatriz() const;
		
		int alto() const{ return m.dimensionY(); }
		int ancho() const{ return m.dimensionX(); }
		
		/// Imprime en el flujo de salida la matriz completa.
		/// \param os Flujo de salida.
		/// \param mt Matriz completa a imprimir.
		/// \return Referencia al flujo de salida.
		friend ostream& operator <<(ostream& os, const MatrizTetris& mt);
		
		~MatrizTetris(){
			SDL_FreeSurface(fondo);
			SDL_FreeSurface(bloque);
			SDL_FreeSurface(textoPuntos);
			SDL_FreeSurface(textoNivel);
			SDL_FreeSurface(textoLineas);
			TTF_CloseFont(fuente60);
			TTF_CloseFont(fuente40);
		}
		
	private:
		vEstado 		v,		///< Vector que almacena el estado de la pieza actual.
						vSig;	///< Vector que almacena el estado de la siguiente pieza.
		unsigned 		posX,	///< Posición de la pieza actual en el eje X.
						posY;	///< Posición de la pieza actual en el eje Y.
						
		Matriz<bool> m;
		SDL_Surface *pantalla, *fondo, *bloque;
		TTF_Font *fuente60, *fuente40;
		SDL_Surface *textoPuntos, *textoNivel, *textoLineas;
		
		void inicializaSDL();
		void inicializaTTF();
		void cargaGraficos();
		
		/// Borra del tablero la pieza actual.
		void borraPieza();
		
		/// Baja todo lo que este en el tablero desde el comiezo hasta un índice 1 posición.
		/// \param linea Indice que marca el máximo.
		void bajarTodo(unsigned linea);
		
		/// Detecta si la pieza colisiona en unas coordenadas con un estado determinado.
		/// \param v Estado de la pieza a comprobar.
		/// \param y Coordenada Y.
		/// \param x Coordenada X.
		/// \return Verdadero si existe colisión, falso si no.
		bool detectaColision(const vEstado& v, unsigned y, unsigned x);
		
};

void MatrizTetris::pintaNivel(unsigned n){ //m2[15][3] = n+48; 
}

void MatrizTetris::vaciaVector(){ v.clear(); }

#endif
