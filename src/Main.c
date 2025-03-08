#include <stdio.h>
#include "HXSLang/variable.h"
#include "HXSLang/constant.h"
#include "HxScript.h"
int main(int argc, char** argv) {
    initSymbol();
    defineVariable(L"var1",L"int",true,114);
    defineVariable(L"var2",L"char",true,L'c');
    defineConstant(L"a",L"int",true,514);
    printf("Hello world\n");
    wprintf(L"%d,%d,%c\n",(int)getValue(L"var1"),(int)getValue(L"a"),(wchar_t)getValue(L"var2"));
    printf("%d\n",parser_defineVariable(L"定义变量 a = b"));
    cleanupSymbol();
    return 0;
}