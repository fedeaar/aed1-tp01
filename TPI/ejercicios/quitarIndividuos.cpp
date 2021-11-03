#include "ejercicios_individuales.h"

/* auxiliares */

bool satisfaceBusqueda(const individuo& ind, const vector<pair<int, dato>>& busqueda) {
    //pre: esBusquedaValida(busqueda)
    bool res = true;
    for (int i = 0; i < busqueda.size() && res; ++i) {
        res &= ind[busqueda[i].first] == busqueda[i].second;
    }
    return res;
}

/*
bool hogarEnTabla(const eph_h& th, dato hogcodusu) {
    //pre: chequeoDeHogares(th) && 0 < hogcodusu
    bool res = false;
    for (int i = 0; i < th.size() && !res; ++i) {
        res = th[i][HOGCODUSU] == hogcodusu;
    }
    return res;
}
*/

/* implementación */

pair<eph_h, eph_i> _quitarIndividuos(eph_i& ti, eph_h& th, const vector<pair<int, dato>>& busqueda) {
    //pre: esEncuestaValida(th, ti) && esBusquedaValida(busqueda)
    eph_h rth = {}; eph_i rti = {}; eph_i mti = {}; eph_h mth = {};
    for (int i = 0; i < ti.size(); ++i) {
        hogar hog = hogarCorrespondiente(ti[i], th);
        if (satisfaceBusqueda(ti[i], busqueda)) {
            rti.push_back(ti[i]);
            if (!hogarEnTabla(rth, ti[i][INDCODUSU]))
                rth.push_back(hog);
        }
        else {
            mti.push_back(ti[i]);
            if (!hogarEnTabla(mth, ti[i][INDCODUSU]))
                mth.push_back(hog);
        }
    }
    th = mth; ti = mti;
    pair<eph_h, eph_i> res = make_pair(rth, rti);
    return res;
}