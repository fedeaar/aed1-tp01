#include "ejercicios_individuales.h"

/* auxiliares */

float distanciaEuclidiana(const hogar &h, const pair<int, int> &centro){
    return sqrt(pow(centro.first - h[HOGLATITUD], 2) + pow(centro.second - h[HOGLONGITUD], 2));
}

void agregarAnilloCorrespondiente(vector<int> &res, const vector<int> &distancias, float distHogar){
    if(distHogar <= float(distancias[0])){
        res[0]++;
    }else{
        for(int i = 0; i < distancias.size() - 1; i++){
            if(float(distancias[i]) < distHogar && distHogar <= float(distancias[i+1]))
                res[i+1]++;
        }
    }
}

/* implementación */

vector<int> _histogramaDeAnillosConcentricos(const eph_h& th, const eph_i& ti, pair<int, int> centro, const vector<int>& distancias) {
    /*
     * Calculo la distancia euclidiana de cada hogar, y luego sumo 1 a la posición correspondiente de res.
     * */

    vector <int> resp(distancias.size(),0);

    for(int i = 0; i < th.size(); i++){
        float dist = distanciaEuclidiana(th[i], centro);
        agregarAnilloCorrespondiente(resp, distancias, dist);
    }

    return resp;
}
