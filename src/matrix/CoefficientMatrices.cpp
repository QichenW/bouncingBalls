//
// Created by Qichen on 10/25/16.
//

#include "CoefficientMatrices.h"

CoefficientMatrices::CoefficientMatrices(bool useEuler, int position, int total)  {
    isEuler = useEuler;
    pos = position;
    totalLength = total;
    if(pos == totalLength - 1) {
        next = nullptr;
    } else {
        next = new CoefficientMatrices(isEuler, pos + 1, totalLength);
    }
}

void CoefficientMatrices::printCurrentCoefficientMatrices() {
    cout<< "segment position: "<< pos + 1 <<endl;
    cout<< "is euler: "<< isEuler <<endl;
    int i ,j ;
    float l;
    if (isEuler){
        //TODO
    } else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                l = translation[i][j];
                cout << l << '\t';
            }
            cout << '\n';
        }
        cout << '\n';
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                l = qRotation[i][j];
                cout << l << '\t';
            }
            cout << '\n';
        }
    }
}
