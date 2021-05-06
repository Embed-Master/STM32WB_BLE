#pragma once

#define ALIGN(n)             __attribute__((aligned(n)))
#define PLACE_IN_SECTION( __x__ )  __attribute__((section (__x__)))