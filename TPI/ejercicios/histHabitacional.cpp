#include "ejercicios_individuales.h"

/* implementación */

vector<int> _histHabitacional (const eph_h& th, const eph_i& ti, int region) {
    /* pre: esEncuestaValida(th, ti) && 0 ≤ region ≤ 6 */
    auto esHogarValido = [region](const individuo& i) {
        /* esHogarValido está pensado de este modo porque la region es un meta-parámetro (así se dirá?)
         * para maxCondicional(). Es decir: maxCondicional() evalúa el máximo
         * de una columna que satisface cierta condición. Pero ya que la condición
         * está en sí parametrizada, se requiere construir la condición
         * correcta antes de utilizarla en maxCondicional().
         * */
        return i[REGION] == region;
    };
    vector<int> resultado(maxCondicional(th, IV2, esHogarValido), 0); // *1
    for (int i = 0; i < th.size(); ++i) {
        if (esHogarValido(th[i]) && th[i][IV1] == 1)
            ++resultado[th[i][IV2] - 1];
    }
    return resultado;
}

/* 1. La especificación no lo contempla, pero tiene sentido (en espíritu) devolver un vector vacío
 *    si no se cumplen las condiciones para ningún hogar.
 * */

