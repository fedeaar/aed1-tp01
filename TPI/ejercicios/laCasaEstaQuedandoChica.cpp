#include "ejercicios_individuales.h"


/* auxiliares */

void calcularProporcionHacinamiento(const eph_h &th, const eph_i &ti, pair <int, float> &region){
    int hogaresValidos = 0;
    int hogaresHacinados = 0;
    for(int i = 0; i < th.size(); i++){
        if(th[i][IV1] == 1 && th[i][REGION] == region.first && th[i][MAS_500] == 0){
            hogaresValidos++;
            if(cantIndividuosEnHogar(th[i],ti) > 3 * th[i][II2])
                hogaresHacinados++;
        }
    }

    if(hogaresValidos == 0){
        region.second = 0;
    }else{
        region.second = float(hogaresHacinados)/float(hogaresValidos);
    }
}


/* implementación */

vector<pair<int, float>> _laCasaEstaQuedandoChica (const eph_h& th, const eph_i& ti) {
    /* pre: esEncuestaValida(th, ti) */
    vector<pair<int,float>> resp = {make_pair(1,-1.0),
                                    make_pair(40, -1.0),
                                    make_pair(41, -1.0),
                                    make_pair(42,-1.0),
                                    make_pair(43,-1.0),
                                    make_pair(44,-1.0)};

    //For loop para cada region + función auxiliar que calcule proporción
    for(int i = 0; i < resp.size(); i++){
        calcularProporcionHacinamiento(th,ti,resp[i]);
    }

    return resp;
}
