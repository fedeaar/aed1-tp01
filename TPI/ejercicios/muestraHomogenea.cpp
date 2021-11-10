#include "ejercicios_individuales.h"


/* alias */

typedef vector<pair<hogar, dato>> join_thxdato;


/* auxiliares: calcular ingresos */

join_thxdato THxIngresos(const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */
    join_thxdato res;
    for (int i = 0; i < th.size(); ++i) {
        dato hogcodusu = th[i][HOGCODUSU];
        auto sumaIngresos = [hogcodusu](const individuo& ind) {
            /* pre: esIndividuoValido(ind)
             * obs: en histHabitacional.cpp está explicada la razón para este tipo de función.
             * */
            return ind[INDCODUSU] == hogcodusu && ind[p47T] > -1;
        };
        int ingresoTotal = sumaCondicional(ti, p47T, sumaIngresos); //def. en auxiliares.tpp
        res.push_back(make_pair(th[i], ingresoTotal));
    }
    return res;
}


/* auxiliares: ordenar */

bool ingresoMenor(pair<hogar, dato>& a, pair<hogar, dato>& b) {
    return a.second < b.second;
}


/* auxiliares: eval. subsecuencias */

vector<int> subsecuenciaMasLarga(const join_thxdato& t, int i, int j) { // *1
    /* pre: ordenada(t) && 0 <= i < j < |t| */
    vector<int> sml = {i, j};
    int dif = t[j].second - t[i].second;
    if (dif > 0)
        for (int k = j + 1; k < t.size(); ++k) {
            if (t[k].second - t[sml[sml.size() - 1]].second == dif)
                sml.push_back(k);
        }
    return sml;
}

/* 1. idea del algoritmo:
 *  i  j
 * [2, 4, 6, 7, 8]
 *      -> dif = 4 - 2 = 2
 *  i  j  k
 * [2, 4, 6, 7, 8]
 *      -> dif = 6 - 4 = 2
 *  i  j  k1 k
 * [2, 4, 6, 7, 8]
 *      -> dif = 7 - 6 = 1
 *  i  j  k1    k
 * [2, 4, 6, 7, 8]
 *      -> dif = 8 - 6 = 2
 *  i  j  k1    k2
 * [2, 4, 6, 7, 8]
 *      return [i, j, k1, k2]
 * */

vector<int> maximizarSML(const join_thxdato& t) {
    /* pre: ordenada(t) */
    vector<int> max;
    for (int i = 0; i < t.size(); ++i) {
        for (int j = i + 1; j < t.size(); ++j) {
            vector<int> tmp = subsecuenciaMasLarga(t, i, j);
            if (tmp.size() > max.size())
                max = tmp;
        }
    }
    return max;
}

/* auxiliares: combinar */

vector<hogar> seleccionarHogares(const join_thxdato& t, const vector<int>& posiciones) {
    /* (Ai:Z)(0 <= i < |posiciones| ->L 0 <= posiciones[i] < |t|) */
    vector<hogar> seleccion(posiciones.size());
    for (int i = 0; i < posiciones.size(); ++i) {
        seleccion[i] = t[posiciones[i]].first;
    }
    return seleccion;
}


/* implementación */

vector<hogar> _muestraHomogenea(const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */
    join_thxdato hi = THxIngresos(th, ti);
    selectSort(hi, ingresoMenor); //def. en auxiliares.tpp
    vector<int> SML = maximizarSML(hi);
    vector<hogar> res = seleccionarHogares(hi, SML);
    return res.size() < 3 ? vector<hogar>{} : res;
}
