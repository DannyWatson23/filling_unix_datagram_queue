#include <stdlib.h>
#include <stdio.h>
#include "ret_check.h"
#include <errno.h>
#include <string.h>

void check_return_code(int returncode)
{
 if (returncode < 0){
   printf("Failed operation: retcode (%d),  %s\n", returncode, strerror(errno));
   exit(EXIT_FAILURE);
 }
}
