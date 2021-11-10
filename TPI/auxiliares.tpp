#include "auxiliares.h"


/* validación de tabla */

template <typename T>
bool esTabla(const Tabla<T>& tabla, int cantidadColumnas) {
    /* pre: cantidadColumnas > 0 */
    bool res = tabla.size() > 0;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res &= tabla[i].size() == cantidadColumnas;
    }
    return res;
}

template <typename T, typename Lambda>
bool noHayRepetidos(const Tabla<T>& tabla, const Lambda& equivalen) {
    /* pre: esTabla(tabla, #cols_tabla) && equivalen corresponde a la tabla */
    bool res = true;
    for (int i = 0; i < tabla.size() && res; ++i) {
        for (int j = i + 1; j < tabla.size() && res; ++j) {
            res &= !equivalen(tabla[i], tabla[j]);
        }
    }
    return res;
}

template <typename T, typename Lambda>
bool valoresEnRango(const Tabla<T>& tabla, const Lambda& filaEnRango) {
    /* pre: esTabla(tabla, #cols_tabla) && filaEnRango corresponde a la tabla */
    bool res = true;
    for (int i = 0; i < tabla.size() && res; ++i) {
        res &= filaEnRango(tabla[i]);
    }
    return res;
}


/* estadística */

template <typename T, typename Lambda>
T maxCondicional (const Tabla<T>& tabla, int col, const Lambda& cond) {
    /* pre: esTabla(tabla, #cols_tabla) && 0 <= col <= #cols_tabla
     *      && T es comparable && cond corresponde a la tabla
     * */
    int max = 0;
    for (int i = 0; i < tabla.size(); ++i) {
        if (cond(tabla[i]) && tabla[i][col] > max)
            max = tabla[i][col];
    }
    return max;
}

template <typename T, typename Lambda>
T sumaCondicional(const Tabla<T>& tabla, int col, const Lambda& cond) {
    /* pre: esTabla(tabla, #cols_tabla) && 0 <= col <= #cols_tabla
     *      && T es de tipo sumable && cond corresponde a la tabla
     * */
    int total = 0;
    for (int i = 0; i < tabla.size(); ++i) {
        if (cond(tabla[i]))
            total += tabla[i][col];
    }
    return total;
}

template <typename T, typename Lambda>
int acumuladoCondicional(const Tabla<T>& tabla, const Lambda& cond) {
    /* pre: esTabla(tabla, #cols_tabla) && cond corresponde a la tabla */
    int total = 0;
    for (int i = 0; i < tabla.size(); ++i) {
        if (cond(tabla[i]))
            ++total;
    }
    return total;
}

template <typename T>
double porcentaje(T a, T b) {
    /* pre: T es de tipo numérico */
    double res = 0;
    if (b != 0) {
        res = a / double(b);
    }
    return res;
}


/* sort */

template <typename T, typename Lambda>
void selectSort(vector<T>& ordenar, const Lambda& comp) {
    /* pre: comp(actual, candidato) corresponde a elementos de tipo T
     * default: comp considera que tipo T es comparable por '<'
     * */
    for (int i = 0; i < ordenar.size() - 1; ++i) {
        int mover = i;
        for (int j = i + 1; j < ordenar.size(); ++j) {
            if (comp(ordenar[j], ordenar[mover]))
                mover = j;
        }
        swap(ordenar[i], ordenar[mover]);
    }
}
template <typename T> // default
void selectSort(vector<T>& ordenar) {
    selectSort(ordenar, [](T a, T b){return a < b;});
}


template <typename T, typename Lambda>
vector<T>  merge(const vector<T>& v1, const vector<T>& v2, const Lambda& comp) {
    /* pre: ordenado(v1) && ordenado(v2) */
    vector<T> res;
    int i = 0; int j = 0;
    while (i < v1.size() || j < v2.size()) {
        if (j == v2.size() || (i != v1.size() && comp(v1[i], v2[j]))) {
            res.push_back(v1[i]);
            ++i;
        } else {
            res.push_back(v2[j]);
            ++j;
        }
    }
    return res;
}
template <typename T, typename Lambda>
vector<T> mergeSort(const vector<T>& ordenar, const Lambda& comp, int i, int j) {
    if (j - i == 1)
        return vector<T>{ordenar[i]};
    int medio = (i + j) / 2;
    vector<T> l = mergeSort(ordenar, comp, i, medio);
    vector<T> r = mergeSort(ordenar, comp, medio, j);
    return merge(l, r, comp);
}
template <typename T, typename Lambda> // interfaz
void mergeSort(vector<T>& ordenar, const Lambda& comp) {
    /* pre: comp(a, B) corresponde a elementos de tipo T
     * default: comp considera que tipo T es comparable por '<'
     * */
    ordenar = mergeSort(ordenar, comp, 0, ordenar.size());
}
template <typename T> // default
void mergeSort(vector<T>& ordenar) {
    mergeSort(ordenar, [](const T& a, const T& b){return a < b;});
}




