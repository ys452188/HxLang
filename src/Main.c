#include <stdio.h>
#include "HXC/dataStruct.h"

int main(void) {
    
    initSymbol();
    addVariable(L"newVariable",HXC_TYPE_INT,114514);
    printf("Hello, World!\nnewVariable = %d\n",(int)getVariableValue(L"newVariable"));
    cleanupSymbol();
    return 0;
}