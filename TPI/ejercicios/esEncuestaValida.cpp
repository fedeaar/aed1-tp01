#include "ejercicios_individuales.h"


/* tabla hogares */

bool hogaresEquivalentes(const hogar& hog1, const hogar& hog2) {
    bool res = hog1[HOGCODUSU] == hog2[HOGCODUSU];
    return res;
}

bool hogarEnRango(const hogar& h) {
    bool res = h[II2] <= h[IV2] &&
               h[HOGCODUSU] > 0 &&
               h[HOGTRIMESTRE] > 0 && h[HOGTRIMESTRE] <= 4 &&
               h[II7] > 0 && h[II7] <= 3 &&
               (h[REGION] == 1 || (h[REGION] >= 40 && h[REGION] <= 44)) &&
               (h[MAS_500] == 0 || h[MAS_500] == 1) &&
               h[IV1] > 0 && h[IV1] <= 5 &&
               h[IV2] > 0 &&
               h[II2] >= 1 &&
               (h[II3] == 1 || h[II3] == 2);
    return res;
}

bool chequeoDeHogares(const eph_h& th) {
    bool res = esTabla(th, FILAS_HOGAR) && // def. en auxiliares.tpp
               noHayRepetidos(th, hogaresEquivalentes) && // def. en auxiliares.tpp
               valoresEnRango(th, hogarEnRango); // def. en auxiliares.tpp
    return res;
}


/* tabla individuos */

bool individuosEquivalentes(const individuo& ind1, const individuo& ind2) {
    bool res = ind1[INDCODUSU] == ind2[INDCODUSU] &&
               ind1[COMPONENTE] == ind2[COMPONENTE];
    return res;
}

bool individuoEnRango(const individuo& i) {
    bool res = i[INDCODUSU] > 0 &&
               i[COMPONENTE] > 0 &&
               (i[INDTRIMESTRE] > 0 && i[INDTRIMESTRE] <= 4) &&
               (i[CH4] > 0 && i[CH4] <= 2) &&
               i[CH6] >= 0 &&
               (i[NIVEL_ED] == 0 || i[NIVEL_ED] == 1) &&
               (i[ESTADO] >= -1 && i[ESTADO] <= 1) &&
               (i[CAT_OCUP] >= 0 && i[CAT_OCUP] <= 4) &&
               i[p47T] >= -1 &&
               (i[PP04G] >= 0 && i[PP04G] <= 10);
    return res;
}

bool chequeoDeIndividuos(const eph_i& ti){
    bool res =  esTabla(ti, FILAS_INDIVIDUO) &&
                noHayRepetidos(ti, individuosEquivalentes) &&
                valoresEnRango(ti, individuoEnRango);
    return res;
}


/* chequeo cruzado */

bool cantidadValidaDeIndividuosPorHogar(const eph_h& th, const eph_i& ti) {
    /* pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th) */
    bool res = true;
    for (int i = 0; i < th.size() && res; ++i) {
        int cantidad = 0;
        for (int j = 0; j < ti.size(); ++j) {
            if (th[i][HOGCODUSU] == ti[j][INDCODUSU])
                ++cantidad;
        }
        res &= (cantidad > 0 && cantidad < 21);
    }
    return res;
}

bool todoIndividuoTieneHogar(const eph_h& th, const eph_i& ti) {
    /* pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th) */
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
    /* pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th) */
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
    /* pre: chequeoDeIndividuos(ti) && chequeoDeHogares(th) */
    bool res = cantidadValidaDeIndividuosPorHogar(th, ti) &&
               todoIndividuoTieneHogar(th, ti) &&
               encuestasCorrespondientes(th, ti);
    return res;
}


/* implementación */

bool _esEncuestaValida(const eph_h& th, const eph_i& ti) {
    bool res = chequeoDeHogares(th) &&
               chequeoDeIndividuos(ti) &&
               chequeoCruzado(th, ti);
    return res;
}

