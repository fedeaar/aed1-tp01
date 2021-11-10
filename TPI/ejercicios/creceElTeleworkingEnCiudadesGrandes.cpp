#include "ejercicios_individuales.h"


/* auxiliares */

bool trabaja(const individuo& i, const hogar& h) {
    /* pre: esIndividuoValido(i) && esHogarValido(h) */
    return i[ESTADO] == 1 && h[MAS_500] == 1 && (h[IV1] == 1 || h[IV1] == 2);
}

double porcentajeTeleworking(const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th) */
    auto teletrabaja = [&th](const individuo& i) {
        /* obs: en esEncuestaValida.cpp está explicada la razón para este tipo de función.
         * */
        hogar h = th[posCorrespondiente(th, i[HOGCODUSU])];
        return trabaja(i, h) && i[PP04G] == 6 && h[II3] == 1;
    };
    auto noTeletrabaja = [&th](const individuo& i) {
        hogar h = th[posCorrespondiente(th, i[HOGCODUSU])];
        return trabaja(i, h);
    };
    int a = acumuladoCondicional(ti, teletrabaja); // def. en auxiliares.tpp
    int b = acumuladoCondicional(ti, noTeletrabaja);
    return porcentaje(a, b); // def. en auxiliares.tpp
}


/* implementación */

bool _creceElTeleworkingEnCiudadesGrandes (const eph_h& t1h, const eph_i& t1i, const eph_h& t2h, const eph_i& t2i) {
    /* pre: esEncuestaValida(t1h, t1i) && esEncuestaValida(t2h, t2i) &&
     *      año(t1i) < año(t2i) && trimestre(t1i) == trimestre(t2i)
     * */
    return  porcentajeTeleworking(t1h, t1i) < porcentajeTeleworking(t2h, t2i);
}