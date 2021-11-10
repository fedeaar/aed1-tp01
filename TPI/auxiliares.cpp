#include "auxiliares.h"


/* generales */

int posCorrespondiente (const eph_h& th, dato hogcodusu) {
    /* pre: chequeoDeHogares(th) && 0 < hogcodusu */
    int i = 0; bool found = false;
    while (i < th.size() && !found) {
        if (th[i][HOGCODUSU] == hogcodusu)
            found = true;
        else
            ++i;
    }
    return found ? i : -1;
}

bool hogarEnTabla (const eph_h& th, dato hogcodusu) {
    /* pre: chequeoDeHogares(th) && 0 < hogcodusu */
    return posCorrespondiente(th, hogcodusu) != -1;
}

int cantIndividuosEnHogar (const hogar& h, const eph_i& ti) {
    /* pre: chequeoDeIndividuos(ti) && esHogarValido(h) */
    int res = 0;
    for(int i = 0; i < ti.size(); i++){
        if(ti[i][INDCODUSU] == h[HOGCODUSU])
            res++;
    }
    return res;
}


