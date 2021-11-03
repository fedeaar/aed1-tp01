#include "ejercicios_individuales.h"


/* auxiliares */

bool trabaja(const individuo& i, const hogar& h) {
    return i[ESTADO] == 1 && h[MAS_500] == 1 && (h[IV1] == 1 || h[IV1] == 2);
}

bool teletrabaja(const individuo& i, const eph_h& th) {
    hogar h = hogarCorrespondiente(i, th);
    return  trabaja(i, h) && i[PP04G] == 6 && h[II3] == 1;;
}

bool noTeletrabaja(const individuo& i, const eph_h& th) {
    hogar h = hogarCorrespondiente(i, th);
    return trabaja(i, h);
}

float porcentajeTeleworking(const eph_h& th, const eph_i& ti) {
    float res = 0;
    float qTrabaja = acumuladoCondicional(ti, &noTeletrabaja, th);
    if (qTrabaja > 0) {
        float qTeletrabaja = acumuladoCondicional(ti, &teletrabaja, th);
        res = qTeletrabaja / qTrabaja;
    }
    return res;
}


/* implementación */

bool _creceElTeleworkingEnCiudadesGrandes (const eph_h& t1h, const eph_i& t1i, const eph_h& t2h, const eph_i& t2i) {
    //pre esEncuestaValida(t1h, t1i) && esEncuestaValida(t2h, t2i) &&
    // año(t1i) < año(t2i) && trimestre(t1i) == trimestre(t2i)
    return  porcentajeTeleworking(t1h, t1i) < porcentajeTeleworking(t2h, t2i);
}