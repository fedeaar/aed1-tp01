#ifndef SOLUCION_AUXILIARES_H
#define SOLUCION_AUXILIARES_H

#include "definiciones.h"

/* alias de tipo */

template <typename T> using Fila = vector<T>;
template <typename T> using Tabla = vector<Fila<T>>;


/* generales */

bool hogarEnTabla(const eph_h& th, dato hogcodusu);

int posCorrespondiente (const eph_h& th, dato hogcodusu);

int cantIndividuosEnHogar(const hogar& h, const eph_i& ti);


/* validación de tabla */

template <typename T>
bool esTabla(const Tabla<T>& tabla, int cantidadColumnas);

template <typename T, typename Lambda>
bool noHayRepetidos(const Tabla<T>& tabla, const Lambda& equivalen);

template <typename T, typename Lambda>
bool valoresEnRango(const Tabla<T>& tabla, const Lambda& filaEnRango);


/* estadística */

template <typename T, typename Lambda>
T maxCondicional (const Tabla<T>& tabla, int col, const Lambda& cond);

template <typename T, typename Lambda>
T sumaCondicional(const Tabla<T>& tabla, int col, const Lambda& cond);

template <typename T, typename Lambda>
int acumuladoCondicional(const Tabla<T>& tabla, const Lambda& cond);

template <typename T>
double porcentaje(T a, T b);


/* sort */

template <typename T, typename Lambda>
void selectSort(vector<T>& ordenar, const Lambda& comp);
template <typename T> // default
void selectSort(vector<T>& ordenar);

template <typename T, typename Lambda>
void mergeSort(vector<T>& ordenar, const Lambda& comp);
template <typename T> // default
void mergeSort(vector<T>& ordenar);


#include "auxiliares.tpp"

#endif //SOLUCION_AUXILIARES_H
