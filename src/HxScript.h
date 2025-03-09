#ifndef __HXSCRIPT_HXSCRIPT_H__
#include "HXSLang/variable.h"
#include "HXSLang/constant.h"
#include "HXSLang/parser.h"
void execut_file(const char* path);
void execut_shell(void);
void cleanupSymbol(void) {
    cleanupVariableSymbolTable();
    cleanupConstantSymbolTable();
}
double getValue(const wchar_t* name) {
    if(!isnan(getConstantValue(name))) {
        return getConstantValue(name);
    } else if(!isnan(getVariableValue(name))) { 
        return getVariableValue(name);
    } else {
        setlocale(LC_ALL,"chinese");
    	fwprintf(stderr,L"%ls",RUN_ERROR_UNDEFINED_VARIABLE);
    }
    return NAN;
}
void initSymbol(void) {
    initVariableSymbolTable();
    initConstantSymbolTable();
}
#define __HXSCRIPT_HXSCRIPT_H__
#endif