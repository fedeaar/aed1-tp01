#include "ejercicios_individuales.h"


/* implementación */

int _costoSubsidioMejora(const eph_h& th, const eph_i& ti, int monto) {
    int resp = 0;

    for(int i = 0; i < th.size(); i++){
        //Si el hogar cumple el requisito, agrego un subsidio
        //Si es tenencia propia y cantInd - 2 > cantDormitorios
        if(th[i][II7] == 1 && cantIndividuosEnHogar(th[i],ti) - 2 > th[i][II2])
            resp += monto;
    }

    return  resp;
}