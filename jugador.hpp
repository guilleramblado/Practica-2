#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <queue>
#include <time.h>
#include <stdlib.h>


struct estado {
  int fila;
  int columna;
  int orientacion;
  //variables utilizadas para recordar al agente si posee una zapatilla o un bikini
  bool llevaBikini;
  bool llevaZapatillas;
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado (nivel 3 y 4)
      srand(time(NULL));
      bikini=false;
      zapatillas=false;
      hay_plan=false;
      esquinas_almacenadas=false;
      recalcular=false;
      //inicializamos casilla objetivo
      objetivo_actual.fila=-1;
      objetivo_actual.columna=-1;
      objetivo_actual.llevaBikini=false;
      objetivo_actual.llevaZapatillas=false;
      objetivo_actual.orientacion=-1;;
      //Inicializamos las listas
      objetivos.clear();
      visitados.clear();
      plan.clear();
      casillas_recarga.clear();
      recargas_hechas=0;
      alcanzando_recarga=false;
      recargando=false;
      bateria_recargada=0;
      aniadir_objetivo=0;
    }
    
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado (para niveles 0,1 y 2)
      hay_plan=false;
      bikini=false;
      zapatillas=false;
      //acciones_realizadas=0;
      //buscar_objetivo=false;
      //srand(time(NULL));
      //girar=0;

    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    estado actual;
    list<estado> objetivos;
    list<Action> plan;
    bool hay_plan;
    bool bikini;
    bool zapatillas;
    //estado que nos permite recordar el objetivo actual por el que estamos yendo
    estado objetivo_actual;
    //lista de objetivos ya visitados, para evitar dirigirnos a ellos mas de una vez
    list<estado> visitados;
    list<estado> casillas_recarga;
    bool esquinas_almacenadas;
    bool recalcular;
    int recargas_hechas;
    bool alcanzando_recarga;
    bool recargando;
    int bateria_recargada;
    int aniadir_objetivo;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino,list<Action> &plan);
    bool pathFinding_Anchura_Optimizado(const estado &origen, const estado &destino,list<Action> &plan);
    void comprobarCasillaEspecial(estado &st);
    bool pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_AEstrella(const estado &origen, const estado &destino,list<Action> &plan);
    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);
    Action giro_casillabloqueada();

};

#endif
