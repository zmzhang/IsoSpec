/*
 *   Copyright (C) 2015-2016 Mateusz Łącki and Michał Startek.
 *
 *   This file is part of IsoSpec.
 *
 *   IsoSpec is free software: you can redistribute it and/or modify
 *   it under the terms of the Simplified ("2-clause") BSD licence.
 *
 *   IsoSpec is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *   You should have received a copy of the Simplified BSD Licence
 *   along with IsoSpec.  If not, see <https://opensource.org/licenses/BSD-2-Clause>.
 */


#ifndef CWRAPPER_H
#define CWRAPPER_H


#define ALGO_LAYERED 0
#define ALGO_ORDERED 1
#define ALGO_THRESHOLD_ABSOLUTE 2
#define ALGO_THRESHOLD_RELATIVE 3
#define ALGO_LAYERED_ESTIMATE 4


#ifdef __cplusplus
extern "C" {
#endif

void* setupIso( int      _dimNumber,
                const int*      _isotopeNumbers,
                const int*      _atomCounts,
                const double*   _isotopeMasses,
                const double*   _isotopeProbabilities);



// ================================================================


void* setupIsoLayered( int             _dimNumber,
                       const int*      _isotopeNumbers,
                       const int*      _atomCounts,
                       const double*   _isotopeMasses,
                       const double*   _isotopeProbabilities,
                       const double    _cutOff,
                       int             tabSize,
                       double          step,
                       bool            estimate,
                       bool            trim
);

void* setupIsoThreshold( int             _dimNumber,
                         const int*      _isotopeNumbers,
                         const int*      _atomCounts,
                         const double*   _isotopeMasses,
                         const double*   _isotopeProbabilities,
                         const double    _threshold,
                         int             _absolute,
                         int             tabSize,
                         int             hashSize
);

int getIsotopesNo(void* iso);

int getIsoConfNo(void* iso);

void getIsoConfs(void* iso, double* res_mass, double* res_logProb, int* res_isoCounts);

void destroyIso(void* iso);

#ifdef __cplusplus
}
#endif



#endif
