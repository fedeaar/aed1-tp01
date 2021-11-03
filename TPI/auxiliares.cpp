#include "auxiliares.h"


// generales

bool hogarEnTabla(const eph_h& th, dato hogcodusu) {
    //pre: chequeoDeHogares(th) && 0 < hogcodusu
    bool res = false;
    for (int i = 0; i < th.size() && !res; ++i) {
        res = th[i][HOGCODUSU] == hogcodusu;
    }
    return res;
}


hogar hogarCorrespondiente(const individuo& ind, const eph_h& th) {
    int i = 0; bool found = false;
    while (i < th.size() && !found) {
        if (th[i][HOGCODUSU] == ind[INDCODUSU])
            found = true;
        else
            ++i;
    }
    return th[i];
}


