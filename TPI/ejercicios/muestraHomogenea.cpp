#include "ejercicios_individuales.h"


/* ingresos */

bool sumaIngresos(const individuo& ind, dato hogcodusu) {
    return ind[INDCODUSU] == hogcodusu && ind[p47T] > -1;
}

join_thxdato ingresosPorHogar(const eph_h& th, const eph_i& ti) {
    //pre: esEncuestaValida(th, ti)
    join_thxdato res;
    for (int i = 0; i < th.size(); ++i) {
        dato ingresoTotal = sumaCondicional(ti, p47T, &sumaIngresos, th[i][HOGCODUSU]);
        res.push_back(make_pair(th[i], ingresoTotal));
    }
    return res;
}


/* ordenar */

void ordenarIngresosPorHogar(join_thxdato& th_ingresos) {
    //insertion sort (creo)
    for (int i = 0; i < th_ingresos.size() - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < th_ingresos.size(); ++j) {
            if (th_ingresos[j].second < th_ingresos[min].second)
                min = j;
        }
        swap(th_ingresos[i], th_ingresos[min]);
    }
}


/* evaluar subsecuencias de diferencia constante */

vector<int> subsecuenciaMasLarga(const join_thxdato& t, int i, int j) {
    //pre: ordenada(t) && 0 <= i < j < |t| && dif > 0
    vector<int> sml;
    int dif = t[j].second - t[i].second;
    if (dif > 0) {
        sml = {i, j};
        for (int k = j + 1; k < t.size(); ++k) {
            if (t[k].second - t[sml[sml.size() - 1]].second == dif)
                sml.push_back(k);
        }
    }
    return sml;
}

vector<int> maximizarSML(const join_thxdato& t) {
    //pre: ordenada(t)
    vector<int> max;
    for (int i = 0; i < t.size(); ++i) { // O(N^3)
        for (int j = i + 1; j < t.size(); ++j) {
            vector<int> tmp = subsecuenciaMasLarga(t, i, j);
            if (tmp.size() > max.size())
                max = tmp;
        }
    }
    return max;
}


/* combinar */

vector<hogar> seleccionarHogares(const join_thxdato t, const vector<int> posiciones) {
    vector<hogar> seleccion;
    for (int i = 0; i < posiciones.size(); ++i) {
        seleccion.push_back(t[posiciones[i]].first);
    }
    return seleccion;
}


/* implementación */

vector<hogar> _muestraHomogenea(const eph_h& th, const eph_i& ti){
    join_thxdato hi = ingresosPorHogar(th, ti);
    ordenarIngresosPorHogar(hi);
    vector<int> SML = maximizarSML(hi);
    return seleccionarHogares(hi, SML);
}
