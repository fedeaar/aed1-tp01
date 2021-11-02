#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"

using namespace std;
// Implementacion Problema 1
bool esEncuestaValida (eph_h th, eph_i ti) {
    return _esEncuestaValida(th, ti);
}

// Implementacion Problema 2
vector<int> histHabitacional (eph_h th, eph_i ti, int region) {
    return _histHabitacional(th, ti, region);
}

// Implementacion Problema 3
vector<pair<int, float>> laCasaEstaQuedandoChica (eph_h th, eph_i ti) {
    return _laCasaEstaQuedandoChica(th, ti);
}

// Implementacion Problema 4
bool creceElTeleworkingEnCiudadesGrandes (eph_h t1h, eph_i t1i, eph_h t2h, eph_i t2i) {
	return _creceElTeleworkingEnCiudadesGrandes(t1h, t1i, t2h, t2i);
}

// Implementacion Problema 5
int costoSubsidioMejora(eph_h th, eph_i ti, int monto) {
	return _costoSubsidioMejora(th, ti, monto);
}

// Implementacion Problema 6
join_hi generarJoin(eph_h th, eph_i ti) {
    return _generarJoin(th, ti);
}

// Implementacion Problema 7
void ordenarRegionYCODUSU (eph_h &th, eph_i &ti) {
    _ordenarRegionYCODUSU(th, ti);
}

// Implementacion Problema 8
vector<hogar> muestraHomogenea(eph_h &th, eph_i &ti) {
    return _muestraHomogenea(th, ti);
}

// Implementacion Problema 9
void corregirRegion(eph_h &th, eph_i ti) {
    _corregirRegion(th, ti);
}

// Implementacion Problema 10
vector<int> histogramaDeAnillosConcentricos(eph_h th, eph_i ti, pair <int, int> centro, vector<int> distancias) {
	return _histogramaDeAnillosConcentricos(th, ti, centro, distancias);
}

// Implementacion Problema 11
pair<eph_h, eph_i> quitarIndividuos(eph_i &ti, eph_h &th, vector<pair<int, dato>> busqueda) {
    return _quitarIndividuos(ti, th, busqueda);
}
