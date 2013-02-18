/// \file contador.h
#ifndef CONTADOR_H_
#define CONTADOR_H_

#include <iostream>
#include <vector>

using std::vector;
using std::ostream;

/// Contador para integrarlo en la matriz del tetris
class Contador{
	public:
		
		
		/// Constructor.
		/// \param cifras Número de cifras que dispondrá el contador.
		Contador(unsigned cifras) : puntos( vector<int>(cifras,0)), vueltas(0){}
		
		/// Constructor de copia.
		/// \param c Contador a copiar.
		Contador(const Contador& c) : puntos(c.puntos), vueltas(0) {}
		
		/// Incrementa el contador en n unidades.
		/// \param n Numero de unidades a incrementar.
		void incrementar(int n);
		
		/// Observador de puntos.
		/// \return Puntos como un vector de enteros.
		const vector<int>& vectorPuntos() const{ return puntos; }
		
		/// Observador de puntos.
		int numero() const;
	private:
		vector<int> puntos;		///< Vector donde estan representados los puntos.
		unsigned vueltas;		///< Número de vueltas que se le han dado al contador.
		
		/// Suma un numero a una celda del vector de puntos.
		/// \param cont Indice del vector
		/// \param n Entero entre 0 y 9 a sumar.
		void sumarCelda(int cont, int n);
		
		/// Da la vuelta al contador.
		void vuelta();
};

#endif	//CONTADOR_H_
