//
// Created by leo on 3/26/21.
//

#ifndef LIBALGO_DATA_TYPES_H
#define LIBALGO_DATA_TYPES_H

#include <stdlib.h>

typedef enum DataType{
    T_CHAR = 1,
    T_SHORT = 2,
    T_INT = 4,
    T_LONG = 8,
    T_UNDEFINED = 0
} DataType;

typedef struct Type {
    DataType type;
    size_t size;
}Type;

Type data_type(size_t data_size);

#endif //LIBALGO_DATA_TYPES_H
