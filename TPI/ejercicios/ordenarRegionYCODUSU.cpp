#include "ejercicios_individuales.h"

/* auxiliares */

/*
void ordenarDentroDeRegion(eph_h &th, int region, const vector<int> &cantHogarPorRegion){
    //Calculo desde y hasta donde tengo que ordenar
    int comienzo = 0;
    for(int i = 0; i < region; i++){
        comienzo += cantHogarPorRegion[i];
    }
    int final = comienzo + cantHogarPorRegion[region];

    for(int i = comienzo; i < final; i++){ //Selection sort
        int minimo = i;
        for(int j = i+1; j < final; j++){
            if(th[j][HOGCODUSU] < th[minimo][HOGCODUSU]){
                minimo = j;
            }
        }
        swapTH(th, minimo, i);
    }
}

void ordenarHogaresRegionYCodusu(eph_h &th){
    vector<int> cantHogarPorRegion(CANTIDAD_DE_REGIONES,0);
    for(int i = 0; i < th.size(); i++){ //Ordeno tabla por región - Selection sort
        int minimo = i;
        for(int j = i+1; j < th.size(); j++){
            if(th[j][REGION] < th[minimo][REGION]){
                minimo = j;
            }
        }
        swapTH(th, minimo, i);
        //Tengo que hacer esta distinción, ya que no están seguidos los valores posibles de REGION
        if(th[minimo][REGION] == 1){
            cantHogarPorRegion[0]++;
        }else{
            cantHogarPorRegion[th[minimo][REGION] - 39]++;
        }
    }

    //Con la cantidad de hogares por región contados, ordeno dentro de cada region por CODUSU
    for(int region = 0; region < CANTIDAD_DE_REGIONES; region++){
        ordenarDentroDeRegion(th, region, cantHogarPorRegion); //O(n^2)
    }
}
*/

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
                minimo = j;
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
    for(int i = 0; i < th.size(); i++){ //Ordeno tabla por región - Selection sort
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

    //Primero ordeno los hogares y luego los individuos
    ordenarHogaresRegionYCodusu(th);
    ordenarIndividuosPorCodusuDeHogarYComponente(th,ti);

    return;
}

