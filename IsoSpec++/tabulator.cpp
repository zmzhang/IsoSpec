#include "tabulator.h"

#define INIT_TABLE_SIZE 1024

#define PUSH_TO_ARRAY(array, input) \
{ \
    if (confs_no == current_size) \
    { \
        current_size *= 2; \
        array = (double *) realloc(array, current_size * sizeof(double)); \
    } \
    array[confs_no] = input; \
    confs_no++; \
}

#define MEMCPY_TO_ARRAY(array, input) \
{ \
    if (confs_no == current_size) \
    { \
        current_size *= 2; \
        array = (double *) realloc(array, current_size * sizeof(double)); \
    } \
    memcpy(array+confs_tbl_idx, generator->get_conf_signature(), allDimSizeOfInt) \
    confs_tbl_idx += generator->getAllDim(); \
}

void reallocate(double **array, int new_size){
    if( *array != nullptr ){
        *array = (double *) realloc(*array, new_size);
    }
}

// MAKE A TEMPLATE OUT OF THAT SHIT, to accept any type of generator.
template <typename T> Tabulator<T>::Tabulator(T* generator,
                     bool get_masses, bool get_probs,
                     bool get_lprobs, bool get_confs  )
{
    int current_size = INIT_TABLE_SIZE;
    int confs_tbl_idx = 0;
    _confs_no = 0;

    const int allDimSizeOfInt = sizeof(int)*generator->getAllDim();

    _masses = get_masses ? (double *) malloc(INIT_TABLE_SIZE * sizeof(double)) : nullptr;
    _lprobs = get_lprobs ? (double *) malloc(INIT_TABLE_SIZE * sizeof(double)) : nullptr;
    _probs  = get_probs  ? (double *) malloc(INIT_TABLE_SIZE * sizeof(double)) : nullptr;
    _confs  = get_confs  ? (int *)    malloc(INIT_TABLE_SIZE * allDimSizeOfInt): nullptr;


    while(generator->advanceToNextConfiguration()){
        if( _confs_no == current_size )
        {
            current_size *= 2;
            reallocate(&_masses, current_size * sizeof(double));
            reallocate(&_lprobs, current_size * sizeof(double));
            reallocate(&_probs,  current_size * sizeof(double));

            if( _confs != nullptr ){
                _confs = (int *) realloc(_confs, current_size * allDimSizeOfInt);
            }
        }

        if(_masses != nullptr) _masses[_confs_no] = generator->mass();

        if(_lprobs != nullptr) _lprobs[_confs_no] = generator->lprob();

        if(_probs  != nullptr) _probs[_confs_no]  = generator->eprob();

        if(_confs  != nullptr){
            generator->get_conf_signature(_confs + confs_tbl_idx);
            confs_tbl_idx += generator->getAllDim();
        }

        _confs_no++;
    }

    _masses = (double *) realloc(_masses, _confs_no * sizeof(double));
    _lprobs = (double *) realloc(_lprobs, _confs_no * sizeof(double));
    _probs  = (double *) realloc(_probs,  _confs_no * sizeof(double));
    _confs  = (int *)    realloc(_confs,  confs_tbl_idx * sizeof(int));
}

template <typename T> Tabulator<T>::~Tabulator()
{
    if( _masses != nullptr ) free(_masses);
    if( _lprobs != nullptr ) free(_lprobs);
    if( _probs  != nullptr ) free(_probs);
    if( _confs  != nullptr ) free(_confs);
}

template class Tabulator<IsoThresholdGenerator>;
template class Tabulator<IsoLayeredGenerator>;
