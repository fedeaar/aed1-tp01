#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

// templates

template <typename T> using Tabla = vector<vector<T>>;

typedef vector<pair<hogar, dato>> join_thxdato;

// generales

template <typename T>
bool esTabla(const Tabla<T>& tabla, int cantidadColumnas) {
    //pre: cantidadColumnas > 0
    bool res = tabla.size() > 0;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res &= tabla[i].size() == cantidadColumnas;
    }
    return res;
}

bool hogarEnTabla(const eph_h& th, dato hogcodusu);

hogar hogarCorrespondiente(const individuo& ind, const eph_h& th);


// sumatorias

template <typename T, typename Function, typename Param>
int sumaCondicional(const Tabla<T>& tabla, int col, Function condicion, Param p) {
    // pre: esTabla(tabla, #cols_tabla) && 0 <= col <= #cols_tabla
    // lambda condicion -> bool toma parámetros (tabla[i], p);
    int total = 0;
    for (int i = 0; i < tabla.size(); ++i) {
        if (condicion(tabla[i], p))
            total += tabla[i][col];
    }
    return total;
}

template <typename T, typename Function, typename Param>
int acumuladoCondicional(const Tabla<T>& tabla, Function condicion, Param p) {
    // pre: esTabla(tabla, #cols_tabla)
    // lambda condicion -> bool toma parámetros (tabla[i], p);
    int total = 0;
    for (int i = 0; i < tabla.size(); ++i) {
        if (condicion(tabla[i], p))
            ++total;
    }
    return total;
}

#endif //SOLUCION_AUXILIARES_H
