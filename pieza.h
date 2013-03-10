/// \file pieza.h
#ifndef PIEZA_H_
#define PIEZA_H_

#include "piezas_src.h"

#ifndef ESTADOIMPOSIBLE_H_
#define ESTADOIMPOSIBLE_H_

/// Excepción que controla un supuesto malfuncionamiento del programa.
class EstadoImposible{
	public:
		/// Constructor.
		/// \param str Cadena que contiene la razón de la excepción.
		EstadoImposible(const char* str) : cad(str){}
		
		/// Observa la razón.
		/// \return Razón.
		const char* who() const{ return cad; }
	private:
		const char* cad;	///< Cadena de bajo nivel que almacena la razón de la excepción.
};
	
#endif	//ESTADOIMPOSIBLE_H_


/// Pieza de tetris genérica.
class Pieza{
	public:
		/// Constructor.
		/// \param d Dimensión de la pieza.
		Pieza(unsigned d, SDL_Surface* b) : dim(d), bloq(b) {}
		
		/// Rota la pieza al siguiente estado.
		virtual void rotar(){}
		
		/// Observa el vector-estado actual.
		/// \return Vector-estado actual.
		virtual const vEstado& vectorEstado() const = 0;
		
		/// Observa la dimensión de la pieza.
		/// \return Dimensión.
		unsigned dimension() const{ return dim; }
		
		/// Observa el puntero al gráfico del bloque.
		/// \return Puntero al bloque.
		SDL_Surface* bloque() const{ return bloq; }
		
		virtual ~Pieza(){}
		
	private:
		unsigned dim;	///< Dimensión de la pieza.
		SDL_Surface * bloq;
		
};

#endif //PIEZA_H_



	#ifndef PIEZA_4_H_
	#define PIEZA_4_H_
	
	/// Pieza de 4 estados.
	class Pieza4 : public Pieza{
		public:
			/// Constructor.
			Pieza4(vEstado& v, vEstado& w, vEstado& x, vEstado& y, unsigned d, unsigned e=0,SDL_Surface* b) :
				Pieza(d,b), estado(e), v1(v), v2(w), v3(x), v4(y)
			{}
			
			/// Rota la pieza al siguiente estado.
			void rotar();
			
			/// Observa el vector-estado actual.
			/// \return Vector-estado actual.
			const vEstado& vectorEstado() const;
			
			/// Destructor.
			~Pieza4(){}
		private:
			unsigned estado;	///< Estado de la pieza
			vEstado 		v1,	///< Primer estado. 
							v2, ///< Segundo estado. 
							v3,	///< Tercer estado. 
							v4;	///< Cuarto estado. 
			
	};
	
	#endif	//PIEZA_4_H
	
	
	
	#ifndef PIEZA_2_H_
	#define PIEZA_2_H_
	
	/// Pieza de 2 estados.
	class Pieza2 : public Pieza{
		public:
			/// Constructor.
			Pieza2(vEstado& v, vEstado& w, unsigned d, unsigned e=0, SDL_Surface* b) : 
				Pieza(d,b), estado(e), v1(v), v2(w)
			{}
			
			/// Rota la pieza al siguiente estado.
			void rotar();
			
			/// Observa el vector-estado actual.
			/// \return Vector-estado actual.
			const vEstado& vectorEstado() const;
			
			/// Destructor.
			~Pieza2(){}
		private:
			unsigned estado;	///< Estado de la pieza
			vEstado 		v1,	///< Primer estado. 
							v2; ///< Segundo estado.
	};
	
	#endif	//PIEZA_2_H_
	
	
	
	#ifndef PIEZA_1_H_
	#define PIEZA_1_H_
	
	/// Pieza de un solo estado.
	class Pieza1 : public Pieza{
		public:
			/// Constructor.
			Pieza1(vEstado& v, unsigned d, SDL_Surface* b) : Pieza(d,b), v1(v){}
			
			/// Rota la pieza al siguiente estado.
			inline void rotar(){}
			
			/// Observa el vector-estado actual.
			/// \return Vector-estado actual.
			inline const vEstado& vectorEstado() const{ return v1; }
			
			/// Destructor.
			~Pieza1(){}
		private:
			vEstado v1;	///< Unico estado de la pieza.
	};
	
	#endif	//PIEZA_1_H_

