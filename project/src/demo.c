/**
 * @file stdio.h
 * @brief this header file contains all the standard input and output functions.
 *
 * @file basic.h
 * @brief this header file contains the addition and substraction functions.
 *
 * @author   Rajat Bhagat
 *
 * @date 08/26/2019
 */

#include "basic.h"
#include <stdio.h>

/**
 * The function will demonstrate addition and substraction functions
 * @return return type is int.
 */
int main()
{
  int x = 10, y = 20;
  printf("\n%d + %d = %d", x, y, add(x, y));
  printf("\n%d + %d = %d", x, y, sub(x, y));
  return 0;
}
