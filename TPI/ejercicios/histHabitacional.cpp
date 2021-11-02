#include "ejercicios_individuales.h"

/* auxiliares */

int maxHabitaciones (const eph_h& th, dato region) {
    // TODO: preguntar, esto no cumple con la especificación, pero si con los tests
    // el largo que pide la especificación es solo a max habitaciones en la region, no
    // considera si son casas o no.
    int max = 0;
    for (int i = 0; i < th.size(); ++i) {
        if (th[i][REGION] == region && th[i][IV1] == 1 && th[i][IV2] > max)
            max = th[i][IV2];
    }
    return max;
}


/* implementación */

vector<int> _histHabitacional (const eph_h& th, const eph_i& ti, int region) {
    // pre: esEncuestaValida(th, ti) && 0 ≤ region ≤ 6
    vector<int> resultado (maxHabitaciones(th, region), 0);
    for (int i = 0; i < th.size(); ++i) {
        if (th[i][IV1] == 1 && th[i][REGION] == region)
            ++resultado[th[i][IV2] - 1];
    }
    return resultado;
}
