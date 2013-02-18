/// \file matriz.h
#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;
using std::endl;

/// Matriz genérica
template <typename T> class Matriz{
	public:
		/// Constructor predeterminado.
		Matriz(){}
		
		/// Constructor.
		/// \param alto Alto de la matriz.
		/// \param ancho Ancho de la matriz.
		/// \param e Elementos internos.
		Matriz(unsigned alto, unsigned ancho, const T& e = T());
		
		/// Constructor de copia.
		/// \param mat Matriz a copiar.
		Matriz(const Matriz<T>& mat);
		
		/// Observa el largo de la matriz.
		/// \return Dimensión a lo largo.
		unsigned dimensionX() const;
		
		/// Observa el alto de la matriz.
		/// \return Dimensión a lo alto.
		unsigned dimensionY() const;
		
		/// Operador de índice de lectura.
		/// \param i Indice.
		/// \return Vector en el indice i.
		vector<T> operator[](unsigned i) const;
		
		/// Operador de índice lectura/escritura.
		/// \param i Indice.
		/// \return Referencia al vector en el índice i.
		vector<T>& operator[](unsigned i);
		
		/// Acceso a un elemeneto en la matriz, sólo lectura.
		/// \param i Fila.
		/// \param j Columna.
		/// \return Copia del elemento en (j,i)
		unsigned at(unsigned i, unsigned j) const;
		
		/// Acceso a un elemeneto en la matriz, lectura y escritura.
		/// \param i Fila.
		/// \param j Columna.
		/// \return Referencia al elemento en (j,i)
		unsigned& at(unsigned i, unsigned j);
		
		/// Rellena una fila con un elemento.
		/// \param i Fila a rellenar.
		/// \param x Elemento con el que rellenar.
		void rellenaFila(unsigned i, const T& x);
		
		/// Rellena una columna con un elemento.
		/// \param j Columna a rellenar.
		/// \param x Elemento con el que rellenar.
		void rellenaColumna(unsigned j, const T& x);
		
		class OutOfRange;
		
	protected:
		vector< vector<T> > m;	///< Vector de vectores que forman la matriz.
};

/// Excepción para controlar un desbordamiento de índice de esta matriz.
class OutOfRange{
	public:
		/// Constructor.
		/// \param c Cadena que contiene la razón de la excepción.
		OutOfRange(const char* c){ cad = c; }
		
		/// Observa la razón.
		/// \reutrn Razón.
		const char* why() const{ return cad; }
	private:
		const char* cad;	///< Cadena de bajo nivel que almacena la razón de la excepción.
};

template <typename T>
ostream& operator <<(ostream&, const Matriz<T>&);

template <typename T>
Matriz<T>::Matriz(unsigned alto, unsigned ancho, const T& e) : m(alto,vector<T>(ancho,e)) {}

template <typename T>
Matriz<T>::Matriz(const Matriz<T>& mat){
	if(&mat != this){
		m.clear();
		for(unsigned i=0 ; i<mat.m.size() ; i++)
			m.push_back(mat.m[i]);
	}
}

template <typename T>
inline unsigned Matriz<T>::dimensionX() const{ return m[0].size(); }
template <typename T>
inline unsigned Matriz<T>::dimensionY() const{ return m.size(); }

template <typename T>
inline vector<T> Matriz<T>::operator [](unsigned i) const{ return m[i]; }
template <typename T>
inline vector<T>& Matriz<T>::operator [](unsigned i){ return m[i]; }
template <typename T>
inline unsigned Matriz<T>::at(unsigned i, unsigned j) const{
	if(dimensionY() > i) throw OutOfRange("El indice i sobrepasa el eje Y");
	if(dimensionX() > j) throw OutOfRange("El indice j sobrepasa el eje X");
	return m[i][j];
}
template <typename T>
inline unsigned& Matriz<T>::at(unsigned i, unsigned j){
	if(dimensionY() > i) throw OutOfRange("El indice i sobrepasa el eje Y");
	if(dimensionX() > i) throw OutOfRange("El indice j sobrepasa el eje X");
	return m[i][j];
}

template <typename T>
void Matriz<T>::rellenaFila(unsigned i, const T& x){
	for(unsigned j=0 ; j<dimensionX() ; j++)
		m[i][j] = x;
}

template <typename T>
void Matriz<T>::rellenaColumna(unsigned j, const T& x){
	for(unsigned i=0 ; i<dimensionY() ; i++)
		m[i][j] = x;
}

template <typename T>
ostream& operator <<(ostream& os, const Matriz<T>& m){
	for(unsigned i=0 ; i<m.dimensionY() ; i++){
		for(unsigned j=0 ; j<m.dimensionX() ; j++)
			os<<m[i][j];
		os<<endl;
	}
	return os;
}

#endif
