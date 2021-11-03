#ifndef TPI_EJERCICIOS_INDIVIDUALES_H
#define TPI_EJERCICIOS_INDIVIDUALES_H

#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include "../auxiliares.h"
#include "../definiciones.h"


bool _esEncuestaValida (const eph_h& th, const eph_i& ti);
vector<int> _histHabitacional (const eph_h& th, const eph_i& ti, int region);
vector<pair<int, float>> _laCasaEstaQuedandoChica (const eph_h& th, const eph_i& ti);
bool _creceElTeleworkingEnCiudadesGrandes (const eph_h& t1h, const eph_i& t1i, const eph_h& t2h, const eph_i& t2i);
int _costoSubsidioMejora (const eph_h& th, const eph_i& ti, int monto);
join_hi _generarJoin (const eph_h& th, const eph_i& ti);
void _ordenarRegionYCODUSU (eph_h& th, eph_i& ti);
vector <hogar> _muestraHomogenea(const eph_h& th, const eph_i& ti);
void _corregirRegion(eph_h& th, const eph_i& ti);
vector<int> _histogramaDeAnillosConcentricos(const eph_h& th, const eph_i& ti, pair<int, int> centro, const vector<int>& distancias);
pair <eph_h, eph_i> _quitarIndividuos(eph_i& ti, eph_h& th, const vector<pair<int, dato>>& busqueda);


#endif //TPI_EJERCICIOS_INDIVIDUALES_H
