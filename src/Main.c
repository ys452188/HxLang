#include <stdio.h>
#include "HXC/dataStruct.h"
#include "HXC/lexer.h"
int main(void) {
    initSymbol();
    printf("%ls\n",getData("src.hxl"));
    printf("Hello,world!\n");
    cleanupSymbol();
    return 0;
}