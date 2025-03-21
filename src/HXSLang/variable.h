#ifndef __HXSCRIPT_SRC_HXSLANG_VARIABLE_H__
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include "error.h"
typedef struct {
    wchar_t* name;
    wchar_t* type;
    void* address;
} Variable;
static Variable* variableSymbolTable = NULL;
static long long variableCount = 0;
void initVariableSymbolTable(void) {
    variableSymbolTable = (Variable*)malloc(sizeof(Variable));
    if(!variableSymbolTable) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    return;
}
void defineVariable(
    const wchar_t* name,
    const wchar_t* type,
    bool hasValue,
    double value) {
    Variable* newVariable = (Variable*)malloc(sizeof(Variable));
    if(!newVariable) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    newVariable-> name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newVariable-> name) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newVariable);
        return;
    }
    wcscpy(newVariable->name,name);
    newVariable-> type = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(type)+1));
    if(!newVariable-> type) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newVariable->name);
        free(newVariable);
        return;
    }
    wcscpy(newVariable->type,type);
    if(wcscmp(newVariable->type,L"int") == 0) {
        newVariable->address = malloc(sizeof(int));
        if(!newVariable->address) {
            setlocale(LC_ALL,"zh_CN.UTF-8");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newVariable->name);
            free(newVariable->type);
            free(newVariable);
            return;
        }
        *(int*)newVariable->address = hasValue? (int)value:0;
    } else if(wcscmp(newVariable->type,L"float") == 0) {
        newVariable->address = malloc(sizeof(float));
        if(!newVariable->address) {
            setlocale(LC_ALL,"zh_CN.UTF-8");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newVariable->name);
            free(newVariable->type);
            free(newVariable);
            return;
        }
        *(float*)newVariable->address = hasValue? (float)value:0.0f;
    } else if(wcscmp(newVariable->type,L"double") == 0) {
        newVariable->address = malloc(sizeof(double));
        if(!newVariable->address) {
            setlocale(LC_ALL,"zh_CN.UTF-8");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newVariable->name);
            free(newVariable->type);
            free(newVariable);
            return;
        }
        *(double*)newVariable->address = hasValue? (double)value:0.000;
    } else if(wcscmp(newVariable->type,L"char") == 0) {
        newVariable->address = malloc(sizeof(wchar_t));   //为支持unicode,这里使用宽字符
        if(!newVariable->address) {
            setlocale(LC_ALL,"zh_CN.UTF-8");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newVariable->name);
            free(newVariable->type);
            free(newVariable);
            return;
        }
        *(wchar_t*)newVariable->address = hasValue? (wchar_t)value:L'\0';
    } else if(wcscmp(newVariable->type,L"bool") == 0) {
        newVariable->address = malloc(sizeof(bool));
        if(!newVariable->address) {
            setlocale(LC_ALL,"zh_CN.UTF-8");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newVariable->name);
            free(newVariable->type);
            free(newVariable);
            return;
        }
        *(bool*)newVariable->address = hasValue? (bool)value:true;
    } else {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",RUN_ERROR_UNKNOWN_TYPE);
        free(newVariable->name);
        free(newVariable->type);
        free(newVariable);
        return;
    }
    if(variableSymbolTable == NULL) {
        variableSymbolTable = NULL;
        variableCount = 0;
    }
    variableCount++;
    void* temp = realloc(variableSymbolTable,sizeof(Variable)*variableCount);
    if(!temp) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        variableCount--;
        return;
    }
    variableSymbolTable = (Variable*)temp;
    variableSymbolTable[variableCount-1] = *newVariable;
    free(newVariable);
    return;
}
double getVariableValue(const wchar_t* name) {
    if(variableSymbolTable == NULL) {
        setlocale(LC_ALL,"zh_CN.UTF-8");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_NULL_SYMBOL);
        return NAN;
    }
    for(long long i=0; i < variableCount; i++) {
        if(wcscmp(variableSymbolTable[i].name,name) == 0) {
            if (!variableSymbolTable[i].address) {
                fwprintf(stderr, L"错误：变量 %ls 未初始化！\n", name);
                return NAN;
            }
            if (wcscmp(variableSymbolTable[i].type, L"int") == 0) {
                return (double)*(int*)variableSymbolTable[i].address;
            } else if (wcscmp(variableSymbolTable[i].type, L"float") == 0) {
                return (double)*(float*)variableSymbolTable[i].address;
            } else if (wcscmp(variableSymbolTable[i].type, L"double") == 0) {
                return (double)*(double*)variableSymbolTable[i].address;
            } else if (wcscmp(variableSymbolTable[i].type, L"char") == 0) {
                return (double)*(wchar_t*)variableSymbolTable[i].address;
            } else if (wcscmp(variableSymbolTable[i].type, L"bool") == 0) {
                return (double)*(bool*)variableSymbolTable[i].address;
            }
        }
    }
    return NAN;
}
void cleanupVariableSymbolTable() {
    if (variableSymbolTable == NULL) return;
    for (long long i = 0; i < variableCount; i++) {
        free(variableSymbolTable[i].name);
        free(variableSymbolTable[i].type);
        free(variableSymbolTable[i].address);
    }
    free(variableSymbolTable);
    variableSymbolTable = NULL;
    variableCount = 0;
}
#define __HXSCRIPT_SRC_HXSLANG_VARIABLE_H__
#endif