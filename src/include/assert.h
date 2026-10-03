#ifndef LIMBO_ASSERT_H
#define LIMBO_ASSERT_H

#include "die.h"

#define ASSERT_STR(x) #x
#define ASSERT_STR_(x) ASSERT_STR(x)
#define LIMBO_ASSERT(x) if (!(x)) { die("Expectation disappointed: " #x " at " __FILE__ ":" ASSERT_STR_(__LINE__)); }

#endif //LIMBO_ASSERT_H
