#ifndef __HXSCRIPT_SRC_HXSLANG_CONSTANT_H__
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
} Constant;
static Constant* constantSymbolTable = NULL;
static long long constantCount = 0;
void initConstantSymbolTable(void) {
    constantSymbolTable = (Constant*)malloc(sizeof(Constant));
    if(!constantSymbolTable) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    return;
}
void defineConstant(
    const wchar_t* name,
    const wchar_t* type,
    bool hasValue,
    double value) {
    Constant* newConstant = (Constant*)malloc(sizeof(Constant));
    if(!newConstant) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    newConstant-> name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newConstant-> name) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newConstant);
        return;
    }
    wcscpy(newConstant->name,name);
    newConstant-> type = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(type)+1));
    if(!newConstant-> type) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newConstant->name);
        free(newConstant);
        return;
    }
    wcscpy(newConstant->type,type);
    if(wcscmp(newConstant->type,L"int") == 0) {
        newConstant->address = malloc(sizeof(int));
        if(!newConstant->address) {
            setlocale(LC_ALL,"chinese");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newConstant->name);
            free(newConstant->type);
            free(newConstant);
            return;
        }
        *(int*)newConstant->address = hasValue? (int)value:0;
    } else if(wcscmp(newConstant->type,L"float") == 0) {
        newConstant->address = malloc(sizeof(float));
        if(!newConstant->address) {
            setlocale(LC_ALL,"chinese");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newConstant->name);
            free(newConstant->type);
            free(newConstant);
            return;
        }
        *(float*)newConstant->address = hasValue? (float)value:0.0f;
    } else if(wcscmp(newConstant->type,L"double") == 0) {
        newConstant->address = malloc(sizeof(double));
        if(!newConstant->address) {
            setlocale(LC_ALL,"chinese");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newConstant->name);
            free(newConstant->type);
            free(newConstant);
            return;
        }
        *(double*)newConstant->address = hasValue? (double)value:0.000;
    } else if(wcscmp(newConstant->type,L"char") == 0) {
        newConstant->address = malloc(sizeof(wchar_t));   //为支持unicode,这里使用宽字符
        if(!newConstant->address) {
            setlocale(LC_ALL,"chinese");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newConstant->name);
            free(newConstant->type);
            free(newConstant);
            return;
        }
        *(wchar_t*)newConstant->address = hasValue? (wchar_t)value:L'\0';
    } else if(wcscmp(newConstant->type,L"bool") == 0) {
        newConstant->address = malloc(sizeof(bool));
        if(!newConstant->address) {
            setlocale(LC_ALL,"chinese");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newConstant->name);
            free(newConstant->type);
            free(newConstant);
            return;
        }
        *(bool*)newConstant->address = hasValue? (bool)value:true;
    } else {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",RUN_ERROR_UNKNOWN_TYPE);
        free(newConstant->name);
        free(newConstant->type);
        free(newConstant);
        return;
    }
    if(constantSymbolTable == NULL) {
        constantSymbolTable = NULL;
        constantCount = 0;
    }
    constantCount++;
    void* temp = realloc(constantSymbolTable,sizeof(Constant)*constantCount);
    if(!temp) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        constantCount--;
        return;
    }
    constantSymbolTable = (Constant*)temp;
    constantSymbolTable[constantCount-1] = *newConstant;
    free(newConstant);
    return;
}
double getConstantValue(const wchar_t* name) {
    if(constantSymbolTable == NULL) {
        setlocale(LC_ALL,"chinese");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_NULL_SYMBOL);
        return NAN;
    }
    for(long long i=0; i < constantCount; i++) {
        if(wcscmp(constantSymbolTable[i].name,name) == 0) {
            if (constantSymbolTable[i].address == NULL) {
                setlocale(LC_ALL,"chinese");
                fwprintf(stderr, L"错误：常量 %ls 未初始化！\n", name);
                return NAN;
            }
            if (wcscmp(constantSymbolTable[i].type, L"int") == 0) {
                return (double)*(int*)constantSymbolTable[i].address;
            } else if (wcscmp(constantSymbolTable[i].type, L"float") == 0) {
                return (double)*(float*)constantSymbolTable[i].address;
            } else if (wcscmp(constantSymbolTable[i].type, L"double") == 0) {
                return (double)*(double*)constantSymbolTable[i].address;
            } else if (wcscmp(constantSymbolTable[i].type, L"char") == 0) {
                return (double)*(wchar_t*)constantSymbolTable[i].address;
            } else if (wcscmp(constantSymbolTable[i].type, L"bool") == 0) {
                return (double)*(bool*)constantSymbolTable[i].address;
            }
        }
    }
    return NAN;
}
void cleanupConstantSymbolTable(void) {
    if (constantSymbolTable == NULL) return;
    for (long long i = 0; i < constantCount; i++) {
        free(constantSymbolTable[i].name);
        free(constantSymbolTable[i].type);
        free(constantSymbolTable[i].address);
    }
    free(constantSymbolTable);
    constantSymbolTable = NULL;
    constantCount = 0;
}
#define __HXSCRIPT_SRC_HXSLANG_CONSTANT_H__
#endif