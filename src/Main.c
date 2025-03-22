#include <stdio.h>
#include "HXSLang/variable.h"
#include "HXSLang/constant.h"
#include "HXSLang/function.h"
#include "HxScript.h"
#include "FileReader.h"
int main(int argc, char** argv) {
    initSymbol();
    setlocale(LC_ALL,"zh_CN.UTF-8");
    wchar_t** str = getCommamdFromSourceFile("/storage/emulated/0/Android/data/com.cjkj.clanide/files/CJ_IDE/CProject/默认目录/HxScript/example.hxs");
    fwprintf(stdout,L"%ls\n",str[0]);
    cleanupSymbol();
    return 0;
}