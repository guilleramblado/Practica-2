#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>


Action giro_a_realizar(int numero){
	if(numero==0){
		//giramos 90º a la derecha
		return actTURN_R;
	}
	else if(numero==1){
		return actTURN_L;
	}
	else if(numero==2){
		return actSEMITURN_R;
	}
	else{
		return actSEMITURN_L;
	}
}

//funcion que pinta todas las casillas visibles de nuestro campo sobre la matriz mapaResultado
void pintar(int fila_actual, int columna_actual, std::vector<std::vector<unsigned char>> &mapaResultado, std::vector<unsigned char> terreno, int orientacion)
{

	// al comienzo, pintamos la casilla actual
	int tipo_terreno = 0;
	mapaResultado[fila_actual][columna_actual] = terreno[tipo_terreno];

	//cout<<"\nFILA ACTUAL:"<<fila_actual<<"//COLUMNA ACTUAL:"<<columna_actual;

	int comienzo_f;
	int comienzo_c;

	int fila_inicio;
	int columna_inicio;
	int casillas_bloque = 3;
	int auxiliar;
	tipo_terreno++;

	if (orientacion == 0)
	{
		// mirando hacia el norte
		fila_inicio = fila_actual - 1;
		columna_inicio = columna_actual - 1;
		for (int i = 0; i < 3; i++)
		{
			auxiliar = columna_inicio;
			for (int j = 0; j < casillas_bloque; j++)
			{
				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];
				columna_inicio++;
				tipo_terreno++;
			}

			// guardamos la columna de la primera casilla del siguiente bloque de casillas
			columna_inicio = auxiliar - 1;

			// actualizamos la fila del siguiente bloque y el numero de casillas
			fila_inicio--;
			casillas_bloque += 2;
		}
	}
	else if(orientacion == 1){
		//mirando hacia el noreste
		fila_inicio=fila_actual-1;
		columna_inicio=columna_actual;
		int mitad;
		//casillas bloque vale 3

		for(int i=0;i<3;i++){
			mitad=(casillas_bloque-1)/2;
			//debemos guardar los valores iniciales de fila_inicio y columna_inicio
			comienzo_f=fila_inicio;
			comienzo_c=columna_inicio;
			for(int j=0;j<casillas_bloque;j++){

				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];
				//cout<<"\nPintando en fila:"<<fila_inicio<<" y columna:"<<columna_inicio;
				//incrementamos la columna sin tocar la fila
				//cuando hayamos pintado la mitad de las casillas, comenzaremos a incrementar la fila sin tocar la columna
				if(j<mitad){
					//sólo incrementamos la columna
					columna_inicio++;
				}
				else{
					//ahora incrementamos sólo la fila
					fila_inicio++;	
				}

				//incrementamos el numero de casilla
				tipo_terreno++;
				
			}
			//pintaremos dos casillas mas que en la anterior iteracion
			casillas_bloque+=2;
			//ajustamos los valores iniciales de fila_inicio y columna_inicio para la siguiente iteracion
			fila_inicio=comienzo_f-1;
			columna_inicio=comienzo_c;
		}

	}
	else if (orientacion == 2)
	{
		//mirando hacia el este
		fila_inicio = fila_actual - 1;
		columna_inicio = columna_actual + 1;
		for (int i = 0; i < 3; i++)
		{
			auxiliar = fila_inicio;
			for (int j = 0; j < casillas_bloque; j++)
			{
				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];
				fila_inicio++;
				tipo_terreno++;
			}

			// actualizamos la primera fila del siguiente bloque y la guardamos
			fila_inicio = auxiliar - 1;

			// actualizamos el tamaño del siguiente bloque del campo de vision
			casillas_bloque += 2;
			columna_inicio++;
		}
	}
	else if(orientacion==3){
		//mirando hacia el sureste
		fila_inicio=fila_actual;
		columna_inicio=columna_actual+1;
		int mitad;
		//casillas bloque vale 3

		for(int i=0;i<3;i++){
			mitad=(casillas_bloque-1)/2;
			//debemos guardar los valores iniciales de fila_inicio y columna_inicio
			comienzo_f=fila_inicio;
			comienzo_c=columna_inicio;
			for(int j=0;j<casillas_bloque;j++){

				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];

				//incrementamos la columna sin tocar la fila
				//cuando hayamos pintado la mitad de las casillas, comenzaremos a incrementar la fila sin tocar la columna
				if(j<mitad){
					//sólo incrementamos la fila
					fila_inicio++;
				}
				else{
					//ahora decrementamos la columna
					columna_inicio--;;	
				}

				//incrementamos el numero de casilla
				tipo_terreno++;
				
			}
			//pintaremos dos casillas mas que en la anterior iteracion
			casillas_bloque+=2;
			//ajustamos los valores iniciales de fila_inicio y columna_inicio para la siguiente iteracion
			fila_inicio=comienzo_f;
			columna_inicio=comienzo_c+1;
		}
	}
	else if (orientacion == 4)
	{
		// mirando hacia el sur
		fila_inicio = fila_actual + 1;
		columna_inicio = columna_actual + 1;
		for (int i = 0; i < 3; i++)
		{
			auxiliar = columna_inicio;
			for (int j = 0; j < casillas_bloque; j++)
			{
				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];
				columna_inicio--;
				tipo_terreno++;
			}

			// guardamos la columna de la primera casilla del siguiente bloque de casillas
			columna_inicio = auxiliar + 1;

			// actualizamos la fila del siguiente bloque y el numero de casillas
			fila_inicio++;
			casillas_bloque += 2;
		}
	}
	else if(orientacion==5){
		//mirando hacia el suroeste
		fila_inicio=fila_actual+1;
		columna_inicio=columna_actual;
		int mitad;
		//casillas bloque vale 3

		for(int i=0;i<3;i++){
			mitad=(casillas_bloque-1)/2;
			//debemos guardar los valores iniciales de fila_inicio y columna_inicio
			comienzo_f=fila_inicio;
			comienzo_c=columna_inicio;
			for(int j=0;j<casillas_bloque;j++){

				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];

				//incrementamos la columna sin tocar la fila
				//cuando hayamos pintado la mitad de las casillas, comenzaremos a incrementar la fila sin tocar la columna
				if(j<mitad){
					//sólo decrementamos la columna
					columna_inicio--;
				}
				else{
					//ahora decrementamos la fila
					fila_inicio--;	
				}

				//incrementamos el numero de casilla
				tipo_terreno++;
				
			}
			//pintaremos dos casillas mas que en la anterior iteracion
			casillas_bloque+=2;
			//ajustamos los valores iniciales de fila_inicio y columna_inicio para la siguiente iteracion
			fila_inicio=comienzo_f+1;
			columna_inicio=comienzo_c;
		}
	}
	else if(orientacion==6)
	{
		// mirando hacia el oeste
		fila_inicio = fila_actual + 1;
		columna_inicio = columna_actual - 1;
		for (int i = 0; i < 3; i++)
		{
			auxiliar = fila_inicio;
			for (int j = 0; j < casillas_bloque; j++)
			{
				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];
				//cout<<"\nPintando en fila:"<<fila_inicio<<" y columna:"<<columna_inicio;
				fila_inicio--;
				tipo_terreno++;
			}

			// guardamos la columna de la primera casilla del siguiente bloque de casillas
			fila_inicio = auxiliar + 1;

			// actualizamos la fila del siguiente bloque y el numero de casillas
			columna_inicio--;
			casillas_bloque += 2;
		}
	}
	else{
		//mirando hacia el noroeste
		fila_inicio=fila_actual;
		columna_inicio=columna_actual-1;
		int mitad;
		//casillas bloque vale 3

		for(int i=0;i<3;i++){
			mitad=(casillas_bloque-1)/2;
			//debemos guardar los valores iniciales de fila_inicio y columna_inicio
			comienzo_f=fila_inicio;
			comienzo_c=columna_inicio;
			for(int j=0;j<casillas_bloque;j++){

				mapaResultado[fila_inicio][columna_inicio] = terreno[tipo_terreno];

				//incrementamos la columna sin tocar la fila
				//cuando hayamos pintado la mitad de las casillas, comenzaremos a incrementar la fila sin tocar la columna
				if(j<mitad){
					//sólo decrementamos la fila
					fila_inicio--;
				}
				else{
					//ahora incrementamos la columna
					columna_inicio++;	
				}

				//incrementamos el numero de casilla
				tipo_terreno++;
				
			}
			//pintaremos dos casillas mas que en la anterior iteracion
			casillas_bloque+=2;
			//ajustamos los valores iniciales de fila_inicio y columna_inicio para la siguiente iteracion
			fila_inicio=comienzo_f;
			columna_inicio=comienzo_c-1;
		}
	}

	// las casillas del campo han sido pintadas
}

// Dado el codigo en caracter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla)
{
	if (casilla == 'P' or casilla == 'M')
		return true;
	else
		return false;
}

//funcion que comprueba si una casilla objetivo ya se ha fijado como posible objetivo en nuestra lista
bool objetivo_fijado(estado objetivo,list<estado> objetivos){
	//para recorrer los elementos de una lista, definimos un iterador que vaya apuntando a cada elemento(estado)

	if(!objetivos.empty()){
		//la lista contiene objetivos
		//iterador que apunta al primer elemento de una lista
		std::list<estado>::iterator it;
		for(it=objetivos.begin();it!=objetivos.end();it++){
			if(objetivo.fila==(*it).fila and objetivo.columna==(*it).columna){
				//la casilla objetivo ya ha sido fijada como posible objetivo
				cout<<"\nCasilla objetivo ya visitada anteriormente";
				return true;
			}
		}
		return false;
	}
	else{
		//si la lista no tiene objetivos, claramente el objetivo no va a estar en la lista
		cout<<"\nLa casill aun no ha sido visitada";
		return false;
	}
}

/*
//funcion que comprueba si el nuevo objetivo ya ha sido alcanzado, devolviendo 'true' en ese caso
bool objetivo_alcanzado(estado objetivo,vector<estado> objetivos_alcanzados){
	for(int i=0;i<objetivos_alcanzados.size();i++){
		if(objetivo.fila==objetivos_alcanzados[i].fila and objetivo.columna==objetivos_alcanzados[i].columna){
			//el nuevo objetivo ya se alcanzó previamente
			return true;
		}
	}
	return false;

}
*/

//funcion que halla la posicion exacta de una casilla de nuestro campo de vision
void posicion_exacta(int numero,int orientacion,int fila_actual,int columna_actual,int &fila,int &columna){
	//ajustamos primero la fila
	//ahora tenemos 8 orientaciones posibles, las consideramos

	switch (orientacion){
		case 0:
			//NORTE
			if(numero==1 or numero==2 or numero==3){
				fila=fila_actual-1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==7 or numero==8){
				fila=fila_actual-2;
			}else{
				//de la 9 a la 15
				fila=fila_actual-3;
			}
			break;
		case 1:
			//NORESTE
			if(numero==3 or numero==8 or numero==15){
				fila=fila_actual;
			}
			else if(numero==1 or numero==2 or numero==7 or numero==14){
				fila=fila_actual-1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==13){
				fila=fila_actual-2;
			}
			else{
				//casilla [9,12]
				fila=fila_actual-3;
			}
			break;
		case 2:
			//ESTE
			if(numero==2 or numero==6 or numero==12){
				fila=fila_actual;
			}else if(numero==1 or numero==5 or numero==11){
				fila=fila_actual-1;
			}else if(numero==4 or numero==10){
				fila=fila_actual-2;
			}
			else if(numero==9){
				fila=fila_actual-3;
			}
			else if(numero==3 or numero==7 or numero==13){
				fila=fila_actual+1;
			}
			else if(numero==8 or numero==14){
				fila=fila_actual+2;
			}
			else{
				//casilla 15
				fila=fila_actual+3;
			}
			break;
		case 3:
			//SURESTE
			if(numero==1 or numero==4 or numero==9){
				fila=fila_actual;
			}
			else if(numero==3 or numero==2 or numero==5 or numero==10){
				fila=fila_actual+1;
			}
			else if(numero==8 or numero==7 or numero==6 or numero==11){
				fila=fila_actual+2;
			}
			else{
				//casilla [12,15]
				fila=fila_actual+3;
			}
			break;
		case 4:
			//SUR
			if(numero==1 or numero==2 or numero==3){
				fila=fila_actual+1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==7 or numero==8){
				fila=fila_actual+2;
			}else{
				
				fila=fila_actual+3;
			}
			break;
		case 5:
			//SUROESTE
			if(numero==15 or numero==8 or numero==3){
				fila=fila_actual;
			}
			else if(numero==14 or numero==7 or numero==2 or numero==1){
				fila=fila_actual+1;
			}
			else if(numero==13 or numero==6 or numero==5 or numero==4){
				fila=fila_actual+2;
			}
			else{
				//casilla [9,12]
				fila=fila_actual+3;
			}
			break;
		case 6:
			//OESTE
			if(numero==2 or numero==6 or numero==12){
				fila=fila_actual;
			}else if(numero==1 or numero==5 or numero==11){
				fila=fila_actual+1;
			}else if(numero==4 or numero==10){
				fila=fila_actual+2;
			}
			else if(numero==9){
				fila=fila_actual+3;
			}
			else if(numero==3 or numero==7 or numero==13){
				fila=fila_actual-1;
			}
			else if(numero==8 or numero==14){
				fila=fila_actual-2;
			}
			else{
				//casilla 15
				fila=fila_actual-3;
			}
			break;
		case 7:
			//NOROESTE
			if(numero==1 or numero==4 or numero==9){
				fila=fila_actual;
			}
			else if(numero==2 or numero==3 or numero==5 or numero==10){
				fila=fila_actual-1;
			}
			else if(numero==6 or numero==7 or numero==8 or numero==11){
				fila=fila_actual-2;
			}
			else{
				//casillas 12,13,14 o 15
				fila=fila_actual-3;
			}
			break;
	}

	//ajustamos la columna
	switch(orientacion){
		case 0:
			//NORTE
			if(numero==2 or numero==6 or numero==12){
				columna=columna_actual;
			}
			else if(numero==1 or numero==5 or numero==11){
				columna=columna_actual-1;
			}
			else if(numero==4 or numero==10){
				columna=columna_actual-2;
			}
			else if(numero==9){
				columna=columna_actual-3;
			}
			else if(numero==3 or numero==7 or numero==13){
				columna=columna_actual+1;
				//cout<<"\nSumando uno a la columna";
			}
			else if(numero==8 or numero==14){
				columna=columna_actual+2;
			}
			else{
				//cuadrilla numero 15
				columna=columna_actual+3;
			}
			break;
		case 1:
			//NORESTE
			if(numero==1 or numero==4 or numero==9){
				columna=columna_actual;
			}
			else if(numero==3 or numero==2 or numero==5 or numero==10){
				columna=columna_actual+1;
			}
			else if(numero==8 or numero==7 or numero==6 or numero==11){
				columna=columna_actual+2;
			}
			else{
				//casillas 12,13,14 o 15
				columna=columna_actual+3;
			}
			break;
		case 2:
			//ESTE
			if(numero==1 or numero==2 or numero==3){
				columna=columna_actual+1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==7 or numero==8){
				columna=columna_actual+2;
			}
			else{
				//de la 9 a la 15
				columna=columna_actual+3;
			}
			break;
		case 3:
			//SURESTE
			if(numero==3 or numero==8 or numero==15){
				columna=columna_actual;
			}
			else if(numero==1 or numero==2 or numero==7 or numero==14){
				columna=columna_actual+1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==13){
				columna=columna_actual+2;
			}
			else{
				//casilla 9,10,11 o 12
				columna=columna_actual+3;
			}
			break;
		case 4:
			//SUR
			if(numero==2 or numero==6 or numero==12){
				columna=columna_actual;
			}
			else if(numero==1 or numero==5 or numero==11){
				columna=columna_actual+1;
			}
			else if(numero==4 or numero==10){
				columna=columna_actual+2;
			}
			else if(numero==9){
				columna=columna_actual+3;
			}
			else if(numero==3 or numero==7 or numero==13){
				columna=columna_actual-1;
			}
			else if(numero==8 or numero==14){
				columna=columna_actual-2;
			}
			else{
				//cuadrilla numero 15
				columna=columna_actual-3;
			}
			break;
		case 5:
			//SUROESTE
			if(numero==1 or numero==4 or numero==9){
				columna=columna_actual;
			}
			else if(numero==3 or numero==2 or numero==5 or numero==10){
				columna=columna_actual-1;
			}
			else if(numero==8 or numero==7 or numero==6 or numero==11){
				columna=columna_actual-2;
			}
			else{
				//casillas 12,13,14 o 15
				columna=columna_actual-3;
			}
			break;
		case 6:
			//OESTE
			if(numero==1 or numero==2 or numero==3){
				columna=columna_actual-1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==7 or numero==8){
				columna=columna_actual-2;
			}
			else{
				//de la 9 a la 15
				columna=columna_actual-3;
			}
			break;
		case 7:
			//SUROESTE
			if(numero==3 or numero==8 or numero==15){
				columna=columna_actual;
			}
			else if(numero==1 or numero==2 or numero==7 or numero==14){
				columna=columna_actual-1;
			}
			else if(numero==4 or numero==5 or numero==6 or numero==13){
				columna=columna_actual-2;
			}
			else{
				//casillas 9,10,11 o 12
				columna=columna_actual-3;
			}
			break;


	}

	//cout<<"\nFila_objeto:"<<fila<<"-Columna_objeto:"<<columna;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;

	actual.fila = sensores.posF;
	actual.columna = sensores.posC;
	actual.orientacion = sensores.sentido;

	cout << "Fila: " << actual.fila << endl;
	cout << "Col : " << actual.columna << endl;
	cout << "Ori : " << actual.orientacion << endl;

	if(sensores.nivel==0 or sensores.nivel==1 or sensores.nivel==2){
		// Capturo los destinos
		cout << "sensores.num_destinos : " << sensores.num_destinos << endl;
		objetivos.clear();
		for (int i = 0; i < sensores.num_destinos; i++)
		{
			estado aux;
			aux.fila = sensores.destino[2 * i];
			aux.columna = sensores.destino[2 * i + 1];
			objetivos.push_back(aux);
		}

		//calculamos el plan
		hay_plan = pathFinding(sensores.nivel, actual, objetivos, plan);
	}
	else if(sensores.nivel==3){
		//PINTAMOS
		pintar(sensores.posF,sensores.posC,mapaResultado,sensores.terreno,sensores.sentido);

		/*
		cout<<"\nPOSICION DE LAS 4 ESQUINAS DEL MAPA...";
		cout<<"\nEsquina inferior derecha// Fila:"<<mapaResultado[0].size()-4<<"//Columna:"<<mapaResultado[0].size()-4;
		cout<<"\nEsquina inferior izquierda// Fila:"<<mapaResultado[0].size()-4<<"//Columna:3";
		cout<<"\nEsquina superior derecha// Fila:3//Columna:"<<mapaResultado[0].size()-4;
		cout<<"\nEsquina superior izquierda// Fila:3//Columna:3";
		*/
		
		cout<<"Objetivo actual-----Fila:"<<objetivo_actual.fila<<"//Columna:"<<objetivo_actual.columna;


		
		//cout<<"\nNumero uno";
		if(sensores.posF==objetivo_actual.fila and sensores.posC==objetivo_actual.columna){
			cout<<"\nEstamos pisando la casilla objetivo...";
			//volvemos a buscar un objetivo
			hay_plan=false;
			//comprobemos si el objetivo alcanzado era una casilla de recarga
			if(alcanzando_recarga){
				//hemos llegado a la casilla de recarga
				cout<<"\nHemos alcanzado la casilla de recarga";
				alcanzando_recarga=false;
				recargando=true;
				casillas_recarga.pop_front();
				casillas_recarga.push_back(objetivo_actual);
				cout<<"\nVamos a recargar ahora...";
			}
			if(!recargando){
				//eliminamos el objetivo alcanzado de la lista
				//cout<<"\nEliminando objetivo...";
				objetivos.pop_front();
				//cout<<"\nAñadiendo a visitados...";
				visitados.push_back(objetivo_actual);
			}
		}
		//comprobamos si tenemos menos de 1500 de bateria --> buscamos una casilla de recarga siempre y cuando no estemos siguiendo un plan
		//comprobamos si hemos alcanzado una casilla objetivo
		if(sensores.bateria<=1500 and !hay_plan and !casillas_recarga.empty() and !recargando and recargas_hechas<3 and !recalcular){
			//nos dirigimos hacia una casilla de recarga
			cout<<"\nTengo poca bateria, buscando plan para casilla de recarga...";
			estado actual;
			actual.fila=sensores.posF;
			actual.columna=sensores.posC;
			actual.orientacion=sensores.sentido;
			objetivo_actual=casillas_recarga.front();
			if(pathFinding_AEstrella(actual,objetivo_actual,plan)){
				//hay un plan, vamos a seguirlo
				hay_plan=true;
				alcanzando_recarga=true;
			}
			else{
				//no hay plan para alcanzar la casilla de recarga
				casillas_recarga.pop_front();
				casillas_recarga.push_back(objetivo_actual);
				//sigue sin haber plan
			}
			
		}

		//cout<<"\nNumero dos\n";
		//comprobamos si estamos en una casilla con zapatillas o bikini
		if(sensores.terreno[0]=='K' and !bikini){
			//cogemos el bikini comprobando antes si ya tenemos zapatillas
			zapatillas=false;
			bikini=true;
		}
		else if(sensores.terreno[0]=='D' and !zapatillas){
			bikini=false;
			zapatillas=true;
		}

		if(!esquinas_almacenadas){
			//añadimos las esquinas como objetivos siempre y cuando no sean muros
			estado esquina;
			//esquina superior izquierda
			esquina.fila=3;
			esquina.columna=3;
			objetivos.push_back(esquina);
			
			//esquina inferior derecha
			esquina.fila=mapaResultado[0].size()-4;
			esquina.columna=mapaResultado[0].size()-4;
			objetivos.push_back(esquina);
			
			//esquina superior derecha
			esquina.fila=3;
			esquina.columna=mapaResultado[0].size()-4;
			objetivos.push_back(esquina);
			
			//esquina inferior izquierda
			esquina.fila=mapaResultado[0].size()-4;
			esquina.columna=3;
			objetivos.push_back(esquina);

			//indicamos que ya hemos almacenado las esquinas
			esquinas_almacenadas=true;
			cout<<"\nEsquinas almacenada:"<<int(esquinas_almacenadas);

			//metemos luego los puntos medios
			estado lado;
			//punto centrico
			cout<<"Centro:Fila:"<<int((mapaResultado[0].size())/2)<<"Columna:"<<int((mapaResultado[0].size())/2);

			cout<<"\nLado izquierda"<<int((mapaResultado[0].size()+3)/2)<<"Columna:3";
			lado.fila=int((mapaResultado[0].size()+3)/2);
			lado.columna=3;
			objetivos.push_back(lado);



			cout<<"\nLado derecha"<<int((mapaResultado[0].size()+3)/2)<<"Columna:"<<mapaResultado[0].size()-4;
			lado.fila=int((mapaResultado[0].size()+3)/2);
			lado.columna=mapaResultado[0].size()-4;
			objetivos.push_back(lado);

			cout<<"\nLado arriba"<<3<<"Columna:"<<int((mapaResultado[0].size()+3)/2);
			lado.fila=3;
			lado.columna=int((mapaResultado[0].size()+3)/2);
			objetivos.push_back(lado);

			cout<<"\nLado abajo"<<mapaResultado[0].size()-4<<"Columna:"<<int((mapaResultado[0].size()+3)/2);
			lado.fila=mapaResultado[0].size()-4;
			lado.columna=int((mapaResultado[0].size()+3)/2);
			objetivos.push_back(lado);

			
		}

		if((sensores.terreno[0]=='A' and !bikini) or (sensores.terreno[0]=='B' and !zapatillas)){
			//he aparecido inicialmente en bosque o agua sin su objeto, avanzo y sino gro
			if(sensores.terreno[2]=='M' or sensores.terreno[2]=='P'){
				if((rand()%2)==0){
					accion=actTURN_R;
				}
				else{
					accion=actTURN_L;
				}
			}
			else{
				accion=actFORWARD;
			}
		}
		else if(recargando){
			//recargamos hasta lograr recargar +1000 de bateria
			if(bateria_recargada<1000){
				accion=actIDLE;
				bateria_recargada=bateria_recargada+10;
				cout<<"\nRecargando bateria...Bateria Recargada=+"<<bateria_recargada;
			}else{
				//ya hemos recargardo +1000 de bateria, dejamos de recargar
				bateria_recargada=0;
				recargando=false;
				cout<<"\nDejo de recargar...";
				recargas_hechas++;
				objetivo_actual.fila=-1;
				objetivo_actual.columna=-1;
			}

		}
		else{
			//mientras que no haya plan, calculamos uno
			while(!hay_plan){
				//comprobamos si tenemos que recalcular o no
				if(recalcular){
					cout<<"\nRecalculando plan para casilla objetivo...";
					//seguimos comprobando que no sea muro o precipicio
					if(!EsObstaculo(mapaResultado[objetivo_actual.fila][objetivo_actual.columna])){
						//calculamos el plan
						estado actual;
						actual.fila=sensores.posF;
						actual.columna=sensores.posC;
						actual.orientacion=sensores.sentido;
						if(pathFinding_AEstrella(actual,objetivo_actual,plan)){
							//hay un plan, vamos a seguirlo
							hay_plan=true;
							recalcular=false;
						}
						else{
							//no hay plan
							objetivos.pop_front();
							objetivos.push_back(objetivo_actual);
							recalcular=false;
						}
					}
					else{
						//si al ver la casilla nos damos cuenta de que es muro o precipicio, anulamos objetivo
						//hay_plan sigue a false
						cout<<"\nAl recalcular, nos hemos dado cuenta que la casilla objetivo era muro o precipicio, dejamos de seguirla...";
						objetivos.pop_front();
						visitados.push_back(objetivo_actual);
						recalcular=false;
					}
				}
				else{
					if(!objetivos.empty()){
						objetivo_actual=objetivos.front();
						//nuestros objetivos serán objetos cuya posicion conocemos, esquinas y casillas aleatorias
						if(!EsObstaculo(mapaResultado[objetivo_actual.fila][objetivo_actual.columna])){
							//calculamos el plan
							estado actual;
							actual.fila=sensores.posF;
							actual.columna=sensores.posC;
							actual.orientacion=sensores.sentido;
							if(pathFinding_AEstrella(actual,objetivo_actual,plan)){
								//hay un plan, vamos a seguirlo
								hay_plan=true;
							}
							else{
								//no hay plan
								objetivos.pop_front();
								objetivos.push_back(objetivo_actual);
							}
						}
						else{
							//ese objetivo es un obstaculo asi que lo eliminamos y lo almacenamos en visitados ya que no podemos ir hacia el
							objetivos.pop_front();
							visitados.push_back(objetivo_actual);
						}
				
					}
					else{
						cout<<"\nNo hay objetivos...";
						//comprobamos si nos toca desplazarnos libremente o buscar casilla aleatoria
						//no hay plan y no hay objetivos, le pasamos una casilla aleatoria...
						int fila_aleatoria=rand()%(mapaResultado[0].size()-7); //[0,92]
						int columna_aleatoria=rand()%(mapaResultado[0].size()-7); //[0,92]
						estado aux;
						aux.fila=fila_aleatoria+4; //aux.fila esta en [4,96]
						aux.columna=columna_aleatoria+4; //aux.columna esta en [4,96]
						//añadimos como objetivo la casilla aleatoria
						int contador=0;
						while(mapaResultado[aux.fila][aux.columna]!='?' and contador<30){
							cout<<"\nCasilla aleatoria generada ya descubierta, generamos otra...";
							//seguimos generando casillas aleatorias hasta encontrar una que no haya sido descubierta
							int fila_aleatoria=rand()%(mapaResultado[0].size()-7); //[0,92]
							int columna_aleatoria=rand()%(mapaResultado[0].size()-7); //[0,92]
							estado aux;
							aux.fila=fila_aleatoria+4; //aux.fila esta en [4,96]
							aux.columna=columna_aleatoria+4; //aux.columna esta en [4,96]
							//para evitar tardar mucho generando 
							contador++;
						}
						//si no hemos encontrado casilla aleatoria desconocida, vamos a por una ya conocida
						if(!EsObstaculo(mapaResultado[aux.fila][aux.columna]) and !objetivo_fijado(aux,objetivos)){
							objetivos.push_back(aux);
							cout<<"\nAñadida como objetivo la casilla...Fila:"<<aux.fila<<"Columna:"<<aux.columna;
						}
						//seguimos sin plan
						
					}
				}
			}
			//salimos del while --> tenemos un plan
			//si vemos una casilla de recarga, la guardamos y vamos a por ella cuando tengamos menos de 1500 de bateria y no estemos siguiendo un plan
			for(int i=1;i<=15;i++){
				if(sensores.terreno[i]=='X'){
					//calculamos su posicion
					estado nuevo;
					posicion_exacta(i,sensores.sentido,sensores.posF,sensores.posC,nuevo.fila,nuevo.columna);
					//almacenamos en la lista de casillas de recarga siempre y cuando no se haya almacenado ya y no hayamos cargado mas de 3 veces
					if(recargas_hechas!=3){
						if(!objetivo_fijado(nuevo,casillas_recarga)){
							//añadimos la casilla de recarga vista a la lista
							cout<<"\nCasilla de recarga aniadida...";
							casillas_recarga.push_back(nuevo);
						}
					}
				}	
			}
			//seguimos el plan
			accion=plan.front();
			plan.erase(plan.begin());
			//si la accion es avanzar, comprobamos que podamos avanzar
			if(accion==actFORWARD){
				//agua sin bikini o bosque sin zapatillas
				if((sensores.terreno[2]=='A' and !bikini) or (sensores.terreno[2]=='B' and !zapatillas) or EsObstaculo(sensores.terreno[2])){
					//no puedo avanzar, asi que anulo el plan y recalculo
					hay_plan=false;
					//sigo manteniendo el objetivo actual
					accion=actIDLE;
					//indicamos que tenemos que recalcular el objetivo
					recalcular=true;
					//dejamos de ver el plan antiguo
					plan.clear();
					estado origen;
					origen.fila=sensores.posF;
					origen.columna=sensores.posC;
					origen.orientacion=sensores.sentido;
					VisualizaPlan(origen,plan);
				}
			}
			
		}
		
	}

	return accion;
}

// Llama al algoritmo de busqueda que se usara en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan)
{

	estado un_objetivo;

	switch (level)
	{
	case 0:
		cout << "Demo\n";
		un_objetivo = objetivos.front();
		cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
		return pathFinding_Profundidad(origen, un_objetivo, plan);
		break;

	case 1:
		cout << "Optimo numero de acciones\n";
		un_objetivo = objetivos.front();
		cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
		return pathFinding_Anchura_Optimizado(origen, un_objetivo, plan);
		break;
	case 2:
		cout << "Optimo en coste\n";
		un_objetivo = objetivos.front();
		cout << "fila: " << un_objetivo.fila << " col:" << un_objetivo.columna << endl;
		//return pathFinding_CosteUniforme(origen, un_objetivo, plan);
		return pathFinding_AEstrella(origen,un_objetivo,plan);
		break;
	case 3:
		cout << "Reto 1: Descubrir el mapa\n";
		// Incluir aqui la llamada al algoritmo de busqueda para el Reto 1
		return pathFinding_AEstrella(origen,un_objetivo,plan);
		break;
	case 4:
		cout << "Reto 2: Maximizar objetivos\n";
		// Incluir aqui la llamada al algoritmo de busqueda para el Reto 2
		cout << "No implementado aun\n";
		break;
	}
	return false;
}

//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st)
{
	int fil = st.fila, col = st.columna;

	// calculo cual es la casilla de delante del agente
	switch (st.orientacion)
	{
	case 0:
		fil--;
		break;
	case 1:
		fil--;
		col++;
		break;
	case 2:
		col++;
		break;
	case 3:
		fil++;
		col++;
		break;
	case 4:
		fil++;
		break;
	case 5:
		fil++;
		col--;
		break;
	case 6:
		col--;
		break;
	case 7:
		fil--;
		col--;
		break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil < 0 or fil >= mapaResultado.size())
		return true;
	if (col < 0 or col >= mapaResultado[0].size())
		return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col]))
	{
		// No hay obstaculo, actualizo el parametro st poniendo la casilla de delante.
		st.fila = fil;
		st.columna = col;
		return false;
	}
	else
	{
		return true;
	}
}

struct nodo
{
	estado st;
	list<Action> secuencia;
	//coste real de desplazarnos hasta 'x' nodo
	int coste;
	//coste real para alcanzar dicho nodo + distancia desde dicho nodo al destino
	int coste_total;
};

struct ComparaEstados
{
	bool operator()(const estado &a, const estado &n) const
	{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
			(a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};

struct ComparaEstados2
{
	bool operator()(const estado &a, const estado &n) const
	{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
			(a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion) or 
			(a.fila == n.fila and a.columna == n.columna and a.orientacion==n.orientacion and a.llevaBikini>n.llevaBikini)
			or (a.fila == n.fila and a.columna == n.columna and a.orientacion==n.orientacion and a.llevaBikini==n.llevaBikini and a.llevaZapatillas>n.llevaZapatillas))
			return true;
		else
			return false;
	}
};

/*
struct ComparaEstados2{
	bool operator()(const estado &a, const estado &n) const
	{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion) or (a.fila == n.fila and a.columna == n.columna and a.orientacion==n.orientacion and a.llevaBikini!=n.llevaBikini) or (a.fila == n.fila and a.columna == n.columna and a.orientacion==n.orientacion and a.llevaZapatillas!=n.llevaZapatillas))
			return true;
		else
			return false;
	}
};
*/

//usado en coste uniforme para ordenar nodos del mismo nivel segun coste real de llegar hasta dicho nodo
struct ComparaCoste
{
	bool operator()(const nodo &nodo1, const nodo &nodo2)const{
		return nodo1.coste>nodo2.coste;
	}
};


//funcion que calcula el coste real de desplazarnos hacia un nodo
int CalculaCoste(const nodo &n,Action accion,std::vector< std::vector< unsigned char> > mapaResultado){
	//calculamos el coste de alcanzar un nodo(llevar a cabo una accion)
	int coste;
	int terreno=mapaResultado[n.st.fila][n.st.columna];
	//para evitar comprobar por cada tipo de terreno la accion realizada, definimos las siguientes estructuras
	//los costes estan asociados respectivamente a las acciones:
	//actFORWARD,actTURN_L y actTURN_R, actSEMITURN_L y actSEMITURN_R
	int costeAguaSinBikini[]={200,500,300};
	int costeAguaConBikini[]={10,5,2};
	int costeBosqueSinZapatillas[]={100,3,2};
	int costeBosqueConZapatillas[]={15,1,1};
	int costeTierra[]={2,2,1};
	//dependiendo de la accion que realicemos...
	if(accion==actIDLE){
		//no hay coste asociado ya que no nos hemos movido
		coste=0;
	}
	else{
		//hay un coste asociado, lo calculamos
		//comprobamos la accion realizada
		int posicion;
		if(accion==actFORWARD){
			posicion=0;
		}
		else if(accion==actTURN_L or accion==actTURN_R){
			posicion=1;
		}
		else{
			//giro de 45 grados
			posicion=2;
		}
		//comprobamos el terreno de la casilla actual
		if(terreno=='A'){
			//comprobamos si tenemos o no bikini
			if(n.st.llevaBikini){
				coste=costeAguaConBikini[posicion];
			}
			else{
				coste=costeAguaSinBikini[posicion];
			}
		}
		else if(terreno=='B'){
			if(n.st.llevaZapatillas){
				coste=costeBosqueConZapatillas[posicion];
			}
			else{
				coste=costeBosqueSinZapatillas[posicion];
			}
		}
		else if(terreno=='T'){
			coste=costeTierra[posicion];
		}
		else if(terreno=='?'){
			//para nivel 3
			//le añadimos un coste superior a la casilla de agua o de bosque
			coste=510;
		}
		else{
			//resto de casillas porque nos interesa descubrir mapa en el nivel 3
			//coste por defecto
			coste=1;
		}

	}
	
	return coste;
}
//heuristica que devuelve una aproximacion del coste de desplazarnos desde nodo inicial al destino
int Heuristica(const estado &origen,const estado &destino){
	//distancia de manhattan --> NO es admisible en este mundo con 8 orientaciones
	//return abs(origen.fila-destino.fila)+abs(origen.columna-destino.columna);
	//hemos seguido la pista de la relacion 2b..
	return max(abs(origen.fila-destino.fila),abs(origen.columna-destino.columna));
}

//sobrecarga del ()
//true cuando cuesta más raiz-nodo1-destino que raiz-nodo2-destino
struct ComparaCosteTotal{
	bool operator()(const nodo &nodo1,const nodo &nodo2)const{
		return nodo1.coste_total>nodo2.coste_total;
	}
};

// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan)
{
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> Cerrados; // Lista de Cerrados
	stack<nodo> Abiertos;				  // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{

		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.top();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}

// Implementacion de la busqueda en anchura utilizada para el nivel 1
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan)
{
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> Cerrados; // Lista de Cerrados
	queue<nodo> Abiertos;				  // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{

		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.front();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}

//
bool ComportamientoJugador::pathFinding_Anchura_Optimizado(const estado &origen, const estado &destino, list<Action> &plan)
{
	//OPTIMIZACION
	//1. Evitamos meter un nodo en abierto que ya se encuentre repetido --> Simplemente lo metemos en Cerrados cada vez que lo metamos en Abiertos
	//2. A la hora de expander, si el nodo hijo es una meta, detenemos el algoritmo de busqueda
	bool hay_meta=false;
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> Cerrados; // Lista de Cerrados
	queue<nodo> Abiertos;				  // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);
	Cerrados.insert(current.st);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{

		Abiertos.pop();

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
			Cerrados.insert(hijoTurnR.st);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
			Cerrados.insert(hijoSEMITurnR.st);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
			Cerrados.insert(hijoTurnL.st);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
			Cerrados.insert(hijoSEMITurnL.st);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
				Cerrados.insert(hijoForward.st);
			}

			//comprobamos si el nodo hijo es una meta para detener el algoritmo de busqueda
			if(hijoForward.st.fila==destino.fila and hijoForward.st.columna==destino.columna){
				hay_meta=true;
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			if(!hay_meta){
				current = Abiertos.front();
			}
			else{
				//hemos metido en abiertos una meta --> evitamos procesar todos los abiertos situados por delante
				current=hijoForward;
			}
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}


//funcion utilizada para actualizar las variables de estado de cada nodo 
//variables: tieneBikini // tieneZapatilla
void ComportamientoJugador::comprobarCasillaEspecial(estado &st){
	char terreno=mapaResultado[st.fila][st.columna];
	//comprobamos si hay zapatilla o bikini
	if(terreno=='K' and !st.llevaBikini){
		st.llevaBikini=true;
		st.llevaZapatillas=false;
	}
	else if(terreno=='D' and !st.llevaZapatillas){
		st.llevaZapatillas=true;
		st.llevaBikini=false;
	}
}

// Implementacion de la busqueda de coste uniforme utilizada para el nivel 2
// El coste real de desplazarnos hacia un nodo se ha definido anteriormente
bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan)
{
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> Cerrados; // Lista de Cerrados
	priority_queue<nodo,vector<nodo>,ComparaCoste> Abiertos;				  // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();
	//inicializamos a false las variables de estado
	current.st.llevaBikini=current.st.llevaZapatillas=false;
	//comprobamos si estamos en una casilla especial
	comprobarCasillaEspecial(current.st);
	//inicializamos el coste inicial de la casilla de partida
	current.coste=CalculaCoste(current,actIDLE,mapaResultado);

	Abiertos.push(current);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{

		Abiertos.pop();
		Cerrados.insert(current.st);

		//comprobamos si el nodo al que nos hemos desplazado esta asociado a una casilla especial
		comprobarCasillaEspecial(current.st);

		//EXPANDIMOS EL NODO ACTUAL...

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;
		//ajustamos el coste que supondria desplazarnos hacia él
		hijoTurnR.coste+=CalculaCoste(hijoTurnR,actTURN_R,mapaResultado);
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		hijoSEMITurnR.coste+=CalculaCoste(hijoSEMITurnR,actSEMITURN_R,mapaResultado);
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		hijoTurnR.coste+=CalculaCoste(hijoTurnL,actTURN_L,mapaResultado);
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		hijoSEMITurnL.coste+=CalculaCoste(hijoSEMITurnL,actSEMITURN_L,mapaResultado);
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		//ajustamos el coste de realizar dicha accion
		hijoForward.coste+=CalculaCoste(hijoForward,actFORWARD,mapaResultado);
		//comprobamos si realmente podemos avanzar
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.top();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}


//Implementacion básica de A*
bool ComportamientoJugador::pathFinding_AEstrella(const estado &origen, const estado &destino,list<Action> &plan){
	cout<<"\nAplicando A*...\n";
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados2> Cerrados; // Lista de Cerrados
	priority_queue<nodo,vector<nodo>,ComparaCosteTotal> Abiertos; // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	//inicializamos las variables de estado utilizando las variables 'zapatilla' y 'bikini'
	current.st.llevaBikini=bikini;
	current.st.llevaZapatillas=zapatillas;

	//inicializamos el coste inicial de la casilla de partida
	current.coste=0;
	current.coste_total=0;
	//comprobamos si la casilla en la que estamos es una casilla especial
	comprobarCasillaEspecial(current.st);

	Abiertos.push(current);
	//Cerrados.insert(current.st);
	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{

		Abiertos.pop();
		//comprobamos si el nuevo nodo esta asociado a una casilla especial
		comprobarCasillaEspecial(current.st);

		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;
		//ajustamos el coste que supondria desplazarnos hacia él
		//hijoTurnR.coste++;
		if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.coste+=CalculaCoste(hijoTurnR,actTURN_R,mapaResultado);
			//coste total raiz-hijoturnr-meta
			hijoTurnR.coste_total=hijoTurnR.coste+Heuristica(hijoTurnR.st,destino);
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		//hijoSEMITurnR.coste++;
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.coste+=CalculaCoste(hijoSEMITurnR,actSEMITURN_R,mapaResultado);
			hijoSEMITurnR.coste_total=hijoSEMITurnR.coste+Heuristica(hijoSEMITurnR.st,destino);
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		//hijoTurnL.coste++;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.coste+=CalculaCoste(hijoTurnL,actTURN_L,mapaResultado);
			hijoTurnL.coste_total=hijoTurnL.coste+Heuristica(hijoTurnL.st,destino);
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		//hijoSEMITurnL.coste++;
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.coste+=CalculaCoste(current,actSEMITURN_L,mapaResultado);
			hijoSEMITurnL.coste_total=hijoSEMITurnL.coste+Heuristica(hijoSEMITurnL.st,destino);
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		//ajustamos el coste de realizar dicha accion (desde la casilla desde las que nos desplazamos hacia delante)
		//comprobamos si realmente podemos avanzar
		//esta funcion tb actualiza la fila y columna de la casilla que tenemos delante
		//hijoForward.coste++;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				//ajustamos el coste de ir desde la siguiente casilla hasta la meta
				hijoForward.coste+=CalculaCoste(current,actFORWARD,mapaResultado);
				hijoForward.coste_total=hijoForward.coste+Heuristica(hijoForward.st,destino);
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.top();
			while(!Abiertos.empty() and Cerrados.find(current.st)!=Cerrados.end()){
				//eliminamos todos aquellos abiertos que ya esten en cerrados
				//como la heuristica es monotona, si se genera un nodo que ya esta en cerrado, el coste que ofrece no va a ser mejor que el que tiene en cerrados
				Abiertos.pop();
				current=Abiertos.top();
			}
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}

// Sacar por la consola la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan)
{
	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			cout << "A ";
		}
		else if (*it == actTURN_R)
		{
			cout << "D ";
		}
		else if (*it == actSEMITURN_R)
		{
			cout << "d ";
		}
		else if (*it == actTURN_L)
		{
			cout << "I ";
		}
		else if (*it == actSEMITURN_L)
		{
			cout << "i ";
		}
		else
		{
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

// Funcion auxiliar para poner a 0 todas las casillas de una matriz
void AnularMatriz(vector<vector<unsigned char>> &m)
{
	for (int i = 0; i < m[0].size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			m[i][j] = 0;
		}
	}
}

// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan)
{
	AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			switch (cst.orientacion)
			{
			case 0:
				cst.fila--;
				break;
			case 1:
				cst.fila--;
				cst.columna++;
				break;
			case 2:
				cst.columna++;
				break;
			case 3:
				cst.fila++;
				cst.columna++;
				break;
			case 4:
				cst.fila++;
				break;
			case 5:
				cst.fila++;
				cst.columna--;
				break;
			case 6:
				cst.columna--;
				break;
			case 7:
				cst.fila--;
				cst.columna--;
				break;
			}
			mapaConPlan[cst.fila][cst.columna] = 1;
		}
		else if (*it == actTURN_R)
		{
			cst.orientacion = (cst.orientacion + 2) % 8;
		}
		else if (*it == actSEMITURN_R)
		{
			cst.orientacion = (cst.orientacion + 1) % 8;
		}
		else if (*it == actTURN_L)
		{
			cst.orientacion = (cst.orientacion + 6) % 8;
		}
		else if (*it == actSEMITURN_L)
		{
			cst.orientacion = (cst.orientacion + 7) % 8;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
