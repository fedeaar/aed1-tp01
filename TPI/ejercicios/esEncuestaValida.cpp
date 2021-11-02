#include "ejercicios_individuales.h"

// validar hogares:

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

// validar individuos:

template <typename T>
bool esTabla(const vector<vector<T>> &tabla, int cantidadColumnas) {
    bool res = tabla.size() > 0;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res = tabla[i].size() == cantidadColumnas;
    }
    return res;
}

bool mismoIndividuo(const individuo &ind1, const individuo &ind2) {
    return  ind1[INDCODUSU] == ind2[INDCODUSU] &&
            ind1[COMPONENTE] == ind2[COMPONENTE];
}
template <typename T>
bool noHayRepetidos(const vector<vector<T>> &tabla, bool (*func)(vector<T>, vector<T>)) {
    // pre: esTabla(tabla)
    bool res = true;
    for(int i = 0; i < tabla.size() && res; ++i) {
        for(int j = i + 1; j < tabla.size() && res; ++j) {
            if (func(tabla[i], tabla[j]))
                res = false;
        }
    }
    return res;
}

bool individuoEnRango(const individuo &i) {
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
template <typename T>
bool valoresEnRango(const vector<vector<T>> &tabla, bool (*func)(vector<T>)) {
    bool res = true;
    for (int i = 0; i < tabla.size() && res; ++i) {
        if (!func(tabla[i]))
            res = false;
    }
    return res;
}

template <typename T>
int maxElem(const vector<vector<T>> &tabla, int col) {
    //pre: esTabla(tabla, cols_tabla) && |tabla[0]| > col >= 0
    int max = tabla[0][col];
    for (int i = 0; i < tabla.size(); ++i) {
        if (tabla[i][col] > max)
            max = tabla[i][col];
    }
    return max;
}

bool tablasRelacionadas(const eph_h &th, const eph_i &ti) {
    //pre: esTabla(th, FILAS_HOGAR) && esTabla(ti, FILAS_INDIVIDUO)
    int maxTh = maxElem(th, HOGCODUSU);
    int maxTi = maxElem(th, INDCODUSU);

    bool res = maxTh == maxTi;
    vector<int> codigos(maxTh + 1, 0);
    for (int i = 0; i < th.size() && res; ++i) {
        res = th[i][HOGTRIMESTRE] == th[0][HOGTRIMESTRE] &&
              th[i][HOGANIO] == th[0][HOGANIO];
        ++codigos[th[i][HOGCODUSU]];
    }
    for (int i = 0; i < ti.size() && res; ++i) {
        res = ti[i][INDTRIMESTRE] == th[0][HOGTRIMESTRE] &&
              ti[i][INDANIO] == th[0][HOGANIO];
        ++codigos[ti[i][INDCODUSU]];
        if (codigos[ti[i][INDCODUSU]] != 2)
            res = false;
    }
    return res;
}

bool menosDe21MiembrosPorHogar(const eph_h &th, const eph_i &ti) {
    // pre: !hayIndividuosSinHogares(th, ti)
    bool res = true;
    vector<int> habitantes(maxElem(th, HOGCODUSU) + 1, 0);
    for (int i = 0; i < ti.size() && res; ++i) {
        ++habitantes[ti[i][INDCODUSU]];
        if (habitantes[ti[i][INDCODUSU]] > 20)
            res = false;
    }
    return res;
}

bool checkeoDeIndividuos(const eph_i &ti){
    return  esTabla(ti, FILAS_INDIVIDUO) &&
            noHayRepetidos(ti, &mismoIndividuo) &&
            valoresEnRango(ti, &individuoEnRango);
}

bool _esEncuestaValida (eph_h th, eph_i ti) {
    bool resp = false;

    // TODO

    return resp;
}

