#include "ejercicios_individuales.h"


/* auxiliares */

bool trabaja(const individuo& i, const hogar& h) {
    /* pre: esIndividuoValido(i) && esHogarValido(h) */
    return i[ESTADO] == 1 && h[MAS_500] == 1 && (h[IV1] == 1 || h[IV1] == 2);
}

auto teletrabaja(const eph_h& th) {
    /* pre: esTablaDeHogaresValida(th)
     * obs: en histHabitacional.cpp está explicada la razón para este tipo de función.
     * */
    return [&th](const individuo& i) {
        /* pre: esIndividuoValido(i) */
        hogar h = th[posCorrespondiente(th, i[HOGCODUSU])];
        return  trabaja(i, h) && i[PP04G] == 6 && h[II3] == 1;
    };
}

auto noTeletrabaja(const eph_h& th) {
    /* pre: esTablaDeHogaresValida(th) */
    return [&th](const individuo& i) {
        /* pre: esIndividuoValido(i) */
        hogar h = th[posCorrespondiente(th, i[HOGCODUSU])];
        return  trabaja(i, h);
    };
}

double porcentajeTeleworking(const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th) */
    int a = acumuladoCondicional(ti, teletrabaja(th)); // def. en auxiliares.tpp
    int b = acumuladoCondicional(ti, noTeletrabaja(th));
    return porcentaje(a, b); // def. en auxiliares.tpp
}


/* implementación */

bool _creceElTeleworkingEnCiudadesGrandes (const eph_h& t1h, const eph_i& t1i, const eph_h& t2h, const eph_i& t2i) {
    /* pre: esEncuestaValida(t1h, t1i) && esEncuestaValida(t2h, t2i) &&
     *      año(t1i) < año(t2i) && trimestre(t1i) == trimestre(t2i)
     * */
    return  porcentajeTeleworking(t1h, t1i) < porcentajeTeleworking(t2h, t2i);
}