#include "ejercicios_individuales.h"
// TODO: preguntar sobre el uso de funciones en parametros


/* auxiliares */

/*
template <typename T> using Tabla = vector<vector<T>>;

template <typename T>
bool esTabla(const Tabla<T>& tabla, int cantidadColumnas) {
    //pre: cantidadColumnas > 0
    bool res = tabla.size() > 0;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res &= tabla[i].size() == cantidadColumnas;
    }
    return res;
}
*/

template <typename T, typename Function>
bool noHayRepetidos(const Tabla<T>& tabla, Function estanRepetidas) {
    // pre: esTabla(tabla, #cols_tabla)
    // lambda estanRepetidas toma dos argumentos de tipo vector<T> (dos filas de la tabla)
    bool res = true;
    for(int i = 0; i < tabla.size() && res; ++i) {
        for(int j = i + 1; j < tabla.size() && res; ++j) {
            res &= !estanRepetidas(tabla[i], tabla[j]);
        }
    }
    return res;
}

template <typename T, typename Function>
bool valoresEnRango(const Tabla<T>& tabla, Function filaEnRango) {
    // pre: esTabla(tabla, #cols_tabla)
    // lambda filaEnRango toma un argumento de tipo vector<T> (una fila de la tabla)
    bool res = true;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res &= filaEnRango(tabla[i]);
    }
    return res;
}


/* tabla hogares */

bool mismoHogar(const hogar& hog1, const hogar& hog2) {
    return  hog1[HOGCODUSU] == hog2[HOGCODUSU];
}

bool hogarEnRango(const hogar& h) {
    return  h[II2] <= h[IV2] &&
            h[HOGCODUSU] > 0 &&
            h[HOGTRIMESTRE] > 0 && h[HOGTRIMESTRE] <= 4 &&
            h[II7] > 0 && h[II7] <= 3 &&
            (h[REGION] == 1 || (h[REGION] >= 40 && h[REGION] <= 44)) &&
            (h[MAS_500] == 0 || h[MAS_500] == 1) &&
            h[IV1] > 0 && h[IV1] <= 5 &&
            h[IV2] > 0 &&
            h[II2] >= 1 &&
            (h[II3] == 1 || h[II3] == 2);
}

bool chequeoDeHogares(const eph_h& th) {
    bool res =  esTabla(th, FILAS_HOGAR) &&
                noHayRepetidos(th, &mismoHogar) &&
                valoresEnRango(th, &hogarEnRango);
    return res;
}


/* tabla individuos */

bool mismoIndividuo(const individuo& ind1, const individuo& ind2) {
    return  ind1[INDCODUSU] == ind2[INDCODUSU] &&
            ind1[COMPONENTE] == ind2[COMPONENTE];
}

bool individuoEnRango(const individuo& i) {
    return  i[INDCODUSU] > 0 &&
            i[COMPONENTE] > 0 &&
            (i[INDTRIMESTRE] > 0 && i[INDTRIMESTRE] <= 4) &&
            (i[CH4] > 0 && i[CH4] <= 2) &&
            i[CH6] >= 0 &&
            (i[NIVEL_ED] == 0 || i[NIVEL_ED] == 1) &&
            (i[ESTADO] >= -1 && i[ESTADO] <= 1) &&
            (i[CAT_OCUP] >= 0 && i[CAT_OCUP] <= 4) &&
            i[p47T] >= -1 &&
            (i[PP04G] >= 0 && i[PP04G] <= 10);
}

bool chequeoDeIndividuos(const eph_i& ti){
    bool res =  esTabla(ti, FILAS_INDIVIDUO) &&
                noHayRepetidos(ti, &mismoIndividuo) &&
                valoresEnRango(ti, &individuoEnRango);
    return res;
}


/* chequeo cruzado */

bool cantidadValidaDeIndividuosPorHogar(const eph_h& th, const eph_i& ti) {
    bool res = true;
    for (int i = 0; i < th.size() && res; ++i) {
        int cantidad = 0;
        for (int j = 0; j <ti.size(); ++j) {
            if (th[i][HOGCODUSU] == ti[j][INDCODUSU])
                ++cantidad;
        }
        res &= (cantidad > 0 && cantidad < 21);
    }
    return res;
}

bool todoIndividuoTieneHogar(const eph_h& th, const eph_i& ti) {
    bool res = true;
    for (int j = 0; j < ti.size() && res; ++j) {
        bool tieneHogar = false;
        for (int i = 0; i < th.size() && !tieneHogar; ++i) {
            tieneHogar = th[i][HOGCODUSU] == ti[j][INDCODUSU];
        }
        res &= tieneHogar;
    }
    return res;
}

bool encuestasCorrespondientes(const eph_h& th, const eph_i& ti) {
    //pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th)
    bool res = true;
    for (int i = 0; i < th.size() && res; ++i) {
        res &=  th[i][HOGTRIMESTRE] == th[0][HOGTRIMESTRE] &&
                th[i][HOGANIO] == th[0][HOGANIO];
    }
    for (int i = 0; i < ti.size() && res; ++i) {
        res &=  ti[i][INDTRIMESTRE] == th[0][HOGTRIMESTRE] &&
                ti[i][INDANIO] == th[0][HOGANIO];
    }
    return res;
}

bool chequeoCruzado(const eph_h& th, const eph_i& ti) {
    bool res =  cantidadValidaDeIndividuosPorHogar(th, ti) &&
                todoIndividuoTieneHogar(th, ti) &&
                encuestasCorrespondientes(th, ti);
    return res;
}


/* implementación */

bool _esEncuestaValida(const eph_h& th, const eph_i& ti) {
    bool res =  chequeoDeHogares(th) &&
                chequeoDeIndividuos(ti) &&
                chequeoCruzado(th, ti);
    return res;
}



//bool formatoCorrecto(const eph_h &th){
//    /*
//     * Devuelve true si: 1. No está vacía.
//     *                   2. Es matriz (todas las filas igual tamaño).
//     *                   3. Tiene cantidad correcta de columnas.
//     * */
//
//    if(th.size() == 0){//1
//        return false;
//    }
//
//    for(int i = 0; i < th.size(); i++){//2,3
//        if(th[i].size() != FILAS_HOGAR){
//            return false;
//        }
//    }
//
//    return true;
//}
//
//bool regionValida(const hogar &h){
//    return  h[REGION] == 1 ||
//            (h[REGION] >= 40 && h[REGION] <= 44);
//}
//
//bool valoresEnRangoH(const hogar &h){
//
//    return  h[II2] <= h[IV2] &&
//            h[HOGCODUSU] > 0 &&
//            h[HOGTRIMESTRE] > 0 && h[HOGTRIMESTRE] <= 4 &&
//            h[II7] > 0 && h[II7] <= 3 &&
//            regionValida(h) &&
//            (h[MAS_500] == 0 || h[MAS_500] == 1) &&
//            h[IV1] > 0 && h[IV1] <= 5 &&
//            h[IV2] > 0 &&
//            h[II2] >= 1 &&
//            (h[II3] == 1 || h[II3] == 2);
//}
//
//bool datosCorrectos(const eph_h &th){
//    /*
//     * Devuelve true si: 1. No hay hogares repetidos.
//     *                   2. #habitaciones >= #dormitorios.
//     *                   3. Valores están en rango.
//     *
//     * Asume tabla con formato correcto.
//     * */
//
//    for(int i = 0; i < th.size(); i++){//1
//        for(int j = i+1; j < th.size(); j++){
//            if(th[i][HOGCODUSU] == th[j][HOGCODUSU]){
//                return false;
//            }
//        }
//    }
//
//    for(int i = 0; i < th.size(); i++){//2,3
//        if(!valoresEnRangoH(th[i])){
//            return false;
//        }
//    }
//
//    return true;
//}
//
//bool chequeoDeHogares(const eph_h &th){
//    return formatoCorrecto(th) && datosCorrectos(th);
//}


/*
template <typename T>
int maxElem(const vector<vector<T>>& tabla, int col) {
    //pre: esTabla(tabla, #cols_tabla) && 0 <= col < |tabla[0]|
    int max = tabla[0][col];
    for (int i = 0; i < tabla.size(); ++i) {
        if (tabla[i][col] > max)
            max = tabla[i][col];
    }
    return max;
}

bool tablasRelacionadas(const eph_h& th, const eph_i& ti) {
    //pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th)
    int maxTh = maxElem(th, HOGCODUSU);
    int maxTi = maxElem(th, INDCODUSU);
    bool res = maxTh == maxTi;
    vector<int> codigos(maxTh + 1, 0);
    for (int i = 0; i < th.size() && res; ++i) {
        ++codigos[th[i][HOGCODUSU]]; // pre: no hay hogares repetidos.
    }
    for (int i = 0; i < ti.size() && res; ++i) {
        res &= codigos[ti[i][INDCODUSU]] > 0; // hay hogar
        ++codigos[ti[i][INDCODUSU]];
    }
    for (int i = 0; i < codigos.size() && res; ++i) {
        res &= !(codigos[i] == 1 || codigos[i] > 21);
        // hay hogares sin individuos,
        // o hay mas de 20 individuos en un hogar.
    }
    return res;
}
*/



