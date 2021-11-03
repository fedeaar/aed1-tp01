#include "auxiliares.h"


// generales

hogar hogarCorrespondiente(const individuo& ind, const eph_h& th) {
    int i = 0; bool found = false;
    while (i < th.size() && !found) {
        if (th[i][HOGCODUSU] == ind[INDCODUSU])
            found = true;
        else
            ++i;
    }
    return th[i];
}


