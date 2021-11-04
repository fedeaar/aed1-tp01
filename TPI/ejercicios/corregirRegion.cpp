#include "ejercicios_individuales.h"

/* auxiliares */


/* implementación */

void _corregirRegion(eph_h& th, const eph_i& ti) {

    for(int i = 0; i < th.size(); i++){
        if(th[i][REGION] == 1)
            th[i][REGION] = 43;
    }

    return;
}