/// \file controlTetris.h
#ifndef CONTROL_TETRIS_H_
#define CONTROL_TETRIS_H_

#include <ctime>
#include <cstdlib>
#include "matriztetris.h"
#include "pieza.h"

/// API de control de la funciones del tetris.
class ControlTetris{
	public:
		/// Constructor.
		/// \param mat Matriz de gráficos donde realizar los cambios.
		ControlTetris(MatrizTetris& mat, Piezas& ps);
		
		/// Deja caer la pieza al fondo del tablero.
		void caerPieza();
		
		/// Baja la pieza una posición.
		inline void bajarPieza();
		
		/// Mueve la pieza una posición a la derecha.
		inline void moverDrcha();
		
		/// Mueve la pieza una posición a la izquierda.
		inline void moverIzqda();
		
		/// Rota la pieza al siguiente estado.
		inline void rotarPieza();
		
		/// Pausa el juego.
		void pause();
		
		/// Observa el contador de puntos.
		/// \return Contador de puntos.
		const Contador& getPuntos() const{ return puntos; }
		
		/// Observa el contador de lineas.
		/// \return Contador de lineas.
		const Contador& getLineas() const{ return lineas; }
		
		/// Observa el nivel.
		/// \return Nivel actual.
		unsigned getNivel() const{ return nivel; }
		
		class RandomException;
		class GameOver;
		
		~ControlTetris(){
			if(p != NULL) delete p;
			if(pSig != NULL) delete pSig;
		}
		
	private:
		MatrizTetris* mt;		///< Puntero a matriz de gráficos
		Contador 	puntos, 	///< Contador de puntos.
					lineas;		///< Contador de líneas.
		unsigned 	nivel, 		///< Nivel de dificultad.
					posX, 		///< Posición de la pieza en el eje X.
					posY;		///< Posición de la pieza en el eje Y.
		Pieza 		*p, 		///< Puntero a la pieza con la que se juega actualmente.
					*pSig;		///< Puntero a la siguiente pieza que entrará en juego.
		Piezas		*piezas;	///< Puntero a la información de piezas.
		
		///	Genera una pieza aleatoria y devuelve un puntero a ella.
		/// \return Puntero a la pieza generada.
		Pieza* piezaAleatoria();
		
		/// Cambia la pieza actual por la siguiente y toma una nueva como siguiente.
		void siguientePieza();
		
		/// Limpia las lineas completas.
		void limpiaLineas();
		
		/// Incrementa el nivel de dificultad.
		inline void subirNivel();
		
		/// Incrementa el contador un número de puntos.
		/// \param n Puntos.
		inline void incrementarPuntos(int n);
		
		/// Incrementa el contador un número de líneas.
		/// \param n Líneas.
		inline void incrementarLineas(unsigned n);
		
		/// Cambia el nivel.
		/// \param n Nuevo nivel
		inline void cambiarNivel(unsigned n);
		
};

/// Excepción para controlar el malfuncionamiento del programa.
class ControlTetris::RandomException{
	public:
		/// Constructor.
		/// \param cad Razón de la excepción.
		RandomException(const char* cad) : str(cad){}
		
		/// Observa la razón de la excepción.
		/// \return Razón.
		const char* why() const{ return str; }
	private:
		const char* str;	///< Cadena de bajo nivel que almacena la razón de la excepción.
};
		
/// Excepción para marcar el final del juego.
class ControlTetris::GameOver{
	public:
		/// Constructor
		/// \param m Matriz asociada.
		GameOver(MatrizTetris& m) : mt(m) {
			mt.pintaGameOver();
		}
	private:
		MatrizTetris& mt;	///< Referencia a la matriz del tetris. Podría ser útil en algún momento.
};

void ControlTetris::bajarPieza(){
	if(mt->pintaPiezaEn(*p,posY+1,posX)){
		posY++;
	}
	else{
		mt->pintaPiezaEn(*p,posY,posX);
		mt->vaciaVector();
		incrementarPuntos(50);
		limpiaLineas();
		siguientePieza();
	}
}

void ControlTetris::moverDrcha(){
	if(mt->pintaPiezaEn(*p,posY,posX+1))
		posX++;
	else
		mt->pintaPiezaEn(*p,posY,posX);
}

void ControlTetris::moverIzqda(){
	if(mt->pintaPiezaEn(*p,posY,posX-1))
		posX--;
	else
		mt->pintaPiezaEn(*p,posY,posX);
}

void ControlTetris::rotarPieza(){
	p->rotar();
	if(!mt->pintaPiezaEn(*p,posY,posX)){
		p->rotar();
		p->rotar();
		p->rotar();
		mt->pintaPiezaEn(*p,posY,posX);
	}
}

void ControlTetris::incrementarPuntos(int n){
	puntos.incrementar(n);
	mt->pintaPuntos(puntos);
	if(unsigned(puntos.numero()) >= 10000*nivel)
		subirNivel();
}

void ControlTetris::incrementarLineas(unsigned n){
	lineas.incrementar(n);
	mt->pintaLineas(lineas);
}

void ControlTetris::cambiarNivel(unsigned n){
	nivel = n;
	mt->pintaNivel(nivel);
}

void ControlTetris::subirNivel(){
	if(nivel < 9){
		nivel++;
		mt->pintaNivel(nivel);
	}
}

#endif	// CONTROL_TETRIS_H_
