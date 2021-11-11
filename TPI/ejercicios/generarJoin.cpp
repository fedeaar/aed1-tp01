#include "ejercicios_individuales.h"


/* implementación */

join_hi _generarJoin(const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */
    join_hi res;
    for (int i = 0; i < ti.size(); ++i) {
        individuo ind = ti[i];
        hogar hog = th[posCorrespondiente(th, ind[HOGCODUSU])]; //def. en auxiliares.cpp
        res.push_back(make_pair(hog, ind));
    }
    return res;
}