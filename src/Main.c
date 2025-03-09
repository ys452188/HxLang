#include <stdio.h>
#include "HXSLang/variable.h"
#include "HXSLang/constant.h"
#include "HXSLang/function.h"
#include "HxScript.h"
int main(int argc, char** argv) {
    initSymbol();
    defineVariable(L"var1",L"int",true,114);
    defineVariable(L"var2",L"char",true,L'c');
    defineConstant(L"a",L"int",true,514);
    defineFunction(L"func",L"int",
    (const wchar_t*[]) {
        L"arg1",L"arg2",L"arg3",NULL
    },
    (const wchar_t*[]) {
        L"int",L"int",L"int",NULL
    },
    L"arg3 = arg2+arg1;return arg3;");
    setlocale(LC_ALL,"chinese");
    wprintf(L"var1 = %d, a = %d,var2 = \'%c\'\n",(int)getValue(L"var1"),(int)getValue(L"a"),(wchar_t)getValue(L"var2"));
    wprintf(L"是否定义变量：%d\n",parser_defineVariable(L"定义变量 a = b"));
    cleanupSymbol();
    return 0;
}