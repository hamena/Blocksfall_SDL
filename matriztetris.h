/// \file matriztetris.h
#ifndef MATRIZ_TETRIS_H_
#define MATRIZ_TETRIS_H_

#define XM2 6
#define YM2 17

#define TAMBLO 22
#define XI 20
#define YI 20
#define CFR 75		// Color del fondo RED
#define CFG 70		// Color del fondo GREEN
#define CFB 70		// Color del fondo BLUE

#include <iostream>
#include <curses.h>
#include <string>
#include <SDL/SDL.h>
#include "matriz.h"
#include "pieza.h"
#include "contador.h"

using std::ostream;
using std::endl;
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
		bool detectaLinea(short int& fila);
		
		/// Imprime la matriz completa a través de funciones de curses.h
		void imprimeMatriz() const;
		
		/// Imprime en el flujo de salida la matriz completa.
		/// \param os Flujo de salida.
		/// \param mt Matriz completa a imprimir.
		/// \return Referencia al flujo de salida.
		friend ostream& operator <<(ostream& os, const MatrizTetris& mt);
		
		~MatrizTetris(){
			SDL_FreeSurface(fondo);
			SDL_FreeSurface(bloque);
		}
		
	private:
		//Matriz<char>	m1,		///< Matriz que representa el tablero de juego.
		//				m2;		///< Matriz que contiene la información sobre la partida.
		//char 			c;		///< Carácter con el que se pintarán los bordes. Por defecto 'X'.
		vEstado 		v,		///< Vector que almacena el estado de la pieza actual.
						vSig;	///< Vector que almacena el estado de la siguiente pieza.
		unsigned 		posX,	///< Posición de la pieza actual en el eje X.
						posY;	///< Posición de la pieza actual en el eje Y.
						
		Matriz<bool> m;
		SDL_Surface *pantalla, *fondo, *bloque;
		
		void inicializaSDL();
		
		/// Método auxiliar para inicializar el tablero de juego.
		//void inicializaM1();
		
		/// Método auxiliar para inicializar la información sobre la partida.
		//void inicializaM2();
		
		/// Borra del tablero la pieza actual.
		void borraPieza();
		
		/// Borra la siguiente pieza mostrada.
		void borraPiezaSig();
		
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
