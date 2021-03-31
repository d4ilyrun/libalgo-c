//
// Created by leo on 3/26/21.
//

#include "../include/data_types.h"

Type data_type(size_t data_size)
{
    DataType type;

    switch (data_size) {
        case 1:
        case 2:
        case 4:
        case 8:
            type = (DataType)data_size;
            break;
        default:
            type = T_UNDEFINED;
            break;
    }

    return (Type){type, data_size};
}