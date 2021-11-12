#include "ejercicios_individuales.h"

/* implementación */

vector<int> _histHabitacional (const eph_h& th, const eph_i& ti, int region) {
    /* pre: esEncuestaValida(th, ti) && 0 ≤ region ≤ 6 */
    auto esHogarValidoHist = [region](const individuo& i) {
        /* obs: en esEncuestaValida.cpp está explicada la razón para este tipo de función.
         * */
        return i[REGION] == region;
    };
    vector<int> resultado(maxCondicional(th, IV2, esHogarValidoHist), 0); // def. en auxiliares.tpp, *1
    for (int i = 0; i < th.size(); ++i) {
        if (esHogarValidoHist(th[i]) && th[i][IV1] == 1)
            ++resultado[th[i][IV2] - 1];
    }
    return resultado;
}

/* 1. obs: La especificación es imposible de satisfacer si no hay hogares en la region pedida,
 *         ya que LongitudIgualAMaximaCantidadDeHabitaciones devolverá false siempre.
 *         Consideramos una interpretación válida, en tal situación, devolver el vector vacío.
 * */

