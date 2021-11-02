#include "ejercicios_individuales.h"


/* auxiliares */

int cantIndividuosEnHogar(hogar h, const eph_i &ti){
    int res = 0;
    for(int i = 0; i < ti.size(); i++){
        if(ti[i][INDCODUSU] == h[HOGCODUSU])
            res++;
    }
    return res;
}

void hogaresValidos(const eph_h &th, int region, vector<int> &ind, int &cant){
    for(int i = 0; i < th.size(); i++){
        if(th[i][IV1] == 1 && th[i][REGION] == region && th[i][MAS_500] == 0){
            ind.push_back(i);
            cant++;
        }
    }
}

int hogaresHacinados(const eph_h &th, const eph_i &ti, const vector<int> &ind){
    int res = 0;
    for(int i = 0; i < ind.size(); i++){
        if(cantIndividuosEnHogar(th[ind[i]],ti) > 3 * th[ind[i]][II2])
            res++;
    }
    return res;
}

void calcularProporcionHacinamiento(const eph_h &th, const eph_i &ti, pair <int, float> &region){
    /*
     * Un hogar es válido si: -Es de tipo casa
     *                        -Se encuentra en la región
     *                        -Está en aglomeraciones de <500.000 habitantes
     *
     * Además, es de hacinamiento crítico si la cantidad de individuos asociados al hogar
     * es mayor a 3 veces los dormitorios.
     * */

    //Calculo la cantidad de hogares válidos y sus índices en la tabla de hogares
    vector<int> indHogaresValidos;
    int cantHogaresValidos = 0;
    hogaresValidos(th, region.first, indHogaresValidos, cantHogaresValidos);

    if(cantHogaresValidos == 0){
        region.second = 0;
    }else{
        int cantHogaresHacinados = hogaresHacinados(th,ti,indHogaresValidos);
        region.second = float(cantHogaresHacinados)/float(cantHogaresValidos);
    }
}


/* implementación */

vector<pair<int, float>> _laCasaEstaQuedandoChica (const eph_h& th, const eph_i& ti) {
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
