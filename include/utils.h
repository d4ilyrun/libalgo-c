//
// Created by leo on 3/26/21.
//


#ifndef LIBALGO_UTILS_H
#define LIBALGO_UTILS_H

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define SWAP(a,b) ({typeof(a) tmp = a; a = b; b = tmp;})
#define ABS(a) (((a) < 0) ? -(a) : (a))

#define TRUE 1
#define FALSE 0

typedef enum bool {
    true = 1,
    false = 0
}bool;

#ifdef NDEBUG

#define ASSERT(...) ((void)0)
#define ASSERT_RETURN(...) ((void)0)
#define ASSERT_NOT_REACHED(...) ((void)0)
#define ASSERT_NOT_REACHED_RETURN(...) ((void)0)

#else

#include <stdio.h>

#define ASSERT(predicate) ({if (!(predicate)) __ASSERTION_FAILED(#predicate);})
#define __MY_ASSERTION_FAILED(predicate) \
    ({fprintf(stderr, "Error:%s:%s:%d - '%s' failed\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, predicate); return;})

#define ASSERT_RETURN(predicate, _return) ({if (!(predicate)) __MY_ASSERTION_FAILED_RETURN(#predicate, _return);})
#define __MY_ASSERTION_FAILED_RETURN(predicate, _return) \
    ({fprintf(stderr, "Error:%s:%s:%d - '%s' failed\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, predicate); return _return;})

#define ASSERT_NOT_REACHED() __MY_ASSERTION_FAILED("Unreachable code reached")

#define ASSERT_NOT_REACHED_RETURN(_return) ({__MY_ASSERTION_FAILED("Unreachable code reached"); return _return;})
#endif

#endif //LIBALGO_UTILS_H
