#include "ejercicios_individuales.h"


/* implementación */

void _corregirRegion(eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */
    for(int i = 0; i < th.size(); i++){
        if(th[i][REGION] == 1)
            th[i][REGION] = 43;
    }
}