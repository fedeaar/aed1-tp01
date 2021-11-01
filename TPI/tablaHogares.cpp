#include "tablaHogares.h"
using namespace std;

bool formatoCorrecto(const eph_h &th){
    /*
     * Devuelve true si: 1. No está vacía.
     *                   2. Es matriz (todas las filas igual tamaño).
     *                   3. Tiene cantidad correcta de columnas.
     * */

    if(th.size() == 0){//1
        return false;
    }

    for(int i = 0; i < th.size(); i++){//2,3
        if(th[i].size() != FILAS_HOGAR){
            return false;
        }
    }

    return true;
}

bool regionValida(const hogar &h){
    return  h[REGION] == 1 ||
            (h[REGION] >= 40 && h[REGION] <= 44);
}

bool valoresEnRangoH(const hogar &h){

    return  h[II2] <= h[IV2] &&
            h[HOGCODUSU] > 0 &&
            h[HOGTRIMESTRE] > 0 && h[HOGTRIMESTRE] <= 4 &&
            h[II7] > 0 && h[II7] <= 3 &&
            regionValida(h) &&
            (h[MAS_500] == 0 || h[MAS_500] == 1) &&
            h[IV1] > 0 && h[IV1] <= 5 &&
            h[IV2] > 0 &&
            h[II2] >= 1 &&
            (h[II3] == 1 || h[II3] == 2);
}

bool datosCorrectos(const eph_h &th){
    /*
     * Devuelve true si: 1. No hay hogares repetidos.
     *                   2. #habitaciones >= #dormitorios.
     *                   3. Valores están en rango.
     *
     * Asume tabla con formato correcto.
     * */

    for(int i = 0; i < th.size(); i++){//1
        for(int j = i+1; j < th.size(); j++){
            if(th[i][HOGCODUSU] == th[j][HOGCODUSU]){
                return false;
            }
        }
    }

    for(int i = 0; i < th.size(); i++){//2,3
        if(!valoresEnRangoH(th[i])){
            return false;
        }
    }

    return true;
}

bool checkeoDeHogares(const eph_h &th){
    return formatoCorrecto(th) && datosCorrectos(th);
}