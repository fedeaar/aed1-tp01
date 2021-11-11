#include "ejercicios_individuales.h"

/* auxiliares */

void swapTH(eph_h &th, int ind1, int ind2){
    hogar aux = th[ind1];
    th[ind1] = th[ind2];
    th[ind2] = aux;
}

void swapTI(eph_i &ti, int ind1, int ind2){
    individuo aux = ti[ind1];
    ti[ind1] = ti[ind2];
    ti[ind2] = aux;
}

void mandarAlFrente(eph_i &ti, int &posACambiar, vector<int> individuos){
    for(int j = 0; j < individuos.size(); j++){
        swapTI(ti, posACambiar, individuos[j]);
        posACambiar++;
    }
}

void ordenarComponente(eph_i &ti, int inicio, int fin){
    for(int j = inicio; j < fin; j++){//Selection Sort
        int minimo = j;
        for(int k = j + 1; k < fin; k++){
            if(ti[k][COMPONENTE] < ti[minimo][COMPONENTE])
                minimo = k;
        }
        swapTI(ti, j, minimo);
    }
}

void ordenarIndividuosPorCodusuDeHogarYComponente(const eph_h &th, eph_i &ti){
    /*
     * Primero ordeno según CODUSU de tabla hogares
     * Almacena los individuos pertenecientes a cada hogar en orden de la tabla de hogares.
     * Luego, los envía a todos juntos al frente de la tabla todavía no ordenada.
     * Por último, los ordena entre sí por COMPONENTE.
     * */

    int posACambiar = 0;
    for(int i = 0; i < th.size(); i++){
        int codusu = th[i][HOGCODUSU];
        vector<int> individuosDelHog;

        for(int j = 0; j < ti.size(); j++){//Almaceno los individuos del hogar
            if(ti[j][INDCODUSU] == codusu){
                individuosDelHog.push_back(j);
            }
        }

        mandarAlFrente(ti, posACambiar, individuosDelHog);//Los mando al frente
        ordenarComponente(ti, posACambiar - int(individuosDelHog.size()), posACambiar);//Los ordeno por COMP
    }
}

void ordenarHogaresRegionYCodusu(eph_h &th){
    for(int i = 0; i < th.size(); i++){ //Ordeno tabla por región y codusu - Selection sort
        int minimo = i;
        pair<int, int> parMin = make_pair(th[i][REGION], th[i][HOGCODUSU]);
        for(int j = i+1; j < th.size(); j++){
            pair<int, int> aComparar = make_pair(th[j][REGION], th[j][HOGCODUSU]);
            if(aComparar < parMin){
                minimo = j;
                parMin = aComparar;
            }
        }
        swapTH(th, minimo, i);
    }
}

/* implementación */

void _ordenarRegionYCODUSU (eph_h& th, eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */

    //Primero ordeno los hogares y luego los individuos
    ordenarHogaresRegionYCodusu(th);
    ordenarIndividuosPorCodusuDeHogarYComponente(th,ti);
}

