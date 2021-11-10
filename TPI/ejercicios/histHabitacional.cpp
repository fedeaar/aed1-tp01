#include "ejercicios_individuales.h"

/* implementación */

vector<int> _histHabitacional (const eph_h& th, const eph_i& ti, int region) {
    /* pre: esEncuestaValida(th, ti) && 0 ≤ region ≤ 6 */
    auto esHogarValido = [region](const individuo& i) {
        /* obs: en esEncuestaValida.cpp está explicada la razón para este tipo de función.
         * */
        return i[REGION] == region;
    };
    vector<int> resultado(maxCondicional(th, IV2, esHogarValido), 0); // def. en auxiliares.tpp, *1
    for (int i = 0; i < th.size(); ++i) {
        if (esHogarValido(th[i]) && th[i][IV1] == 1)
            ++resultado[th[i][IV2] - 1];
    }
    return resultado;
}

/* 1. La especificación no lo contempla, pero tiene sentido (en espíritu) devolver un vector vacío
 *    si no se cumplen las condiciones para ningún hogar.
 * */

