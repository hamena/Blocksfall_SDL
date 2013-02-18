#include "contador.h"

void Contador::incrementar(int n){
	unsigned cont=puntos.size()-1;
	int mult=1;
	bool terminado = false;
	while(!terminado){
		if(!(n/mult > 0)){
			cont++;
			mult /= 10;
			while(!terminado){
				if(cont == puntos.size()-1){
					sumarCelda(cont,n);
					terminado = true;
				}
				else{
					sumarCelda(cont,n/mult);
					n -= mult * (n/mult);
					cont++;
					mult /= 10;
				}
			}
		}
		else{
			cont--;
			mult *= 10;
		}
	}
}

void Contador::sumarCelda(int cont, int n){
	if(puntos[cont]+n < 10)
		puntos[cont] += n;
	else
		if(cont==0){
			puntos[cont] += n;
			vuelta();
		}
		else{
			sumarCelda(cont-1,1);
			puntos[cont] += n-10;
		}
}

int Contador::numero() const{
	unsigned mult = 1;
	int p = 0;
	for(short int i=puntos.size()-1 ; i>=0 ; i--){
		p += puntos[i] * mult;
		mult *= 10;
	}
	p += vueltas * 99999;
	return p;
}

void Contador::vuelta(){
	int num = 0, mult = 1 ;
	for(short int i=puntos.size()-1 ; i>=0 ; i--){
		num += puntos[i]*mult;
		puntos[i] = 0;
		mult *= 10;
	}
	incrementar(num-99999);
	vueltas++;
}
