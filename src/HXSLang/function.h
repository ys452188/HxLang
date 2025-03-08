#ifndef __HXSCRIPT_SRC_HXSLANG_FUNCTION_H__
#define __HXSCRIPT_SRC_HXSLANG_FUNCTION_H__
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include "error.h"
typedef struct {
    wchar_t* name;
    wchar_t* body;
    wchar_t** argsName;
    wchar_t** argsType;
    wchar_t* returnType;
    void* temp;
} Function;
static Function* functionSymbolTable = NULL;
static long long functionCount = 0;
typedef struct {
    wchar_t* name;
    wchar_t* type;
    void* address;
} FunctionTempVariable;
void initFunctionSymbolTable(void) {
    functionSymbolTable = (Function*)malloc(sizeof(Function));
    if(!functionSymbolTable) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    return;
}
void defineFunction(
    const wchar_t* name,
    const wchar_t* returnType,
    const wchar_t** argsName,
    const wchar_t** argsType,
    const wchar_t* body
) {
    Function *newFunction = (Function*)malloc(sizeof(Function));
    if(!newFunction) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return;
    }
    newFunction->name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newFunction->name) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newFunction);
        return;
    }
    wcscpy(newFunction->name,name);
    newFunction->returnType = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(returnType)+1));
    if(!newFunction->returnType) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newFunction->name);
        free(newFunction);
        return;
    }
    wcscpy(newFunction->returnType,returnType);
    //复制参数名
    //计算共几个参数名
    long argsNameCount = 0;
    for(int i = 0; argsName[i] != NULL; i++) {
        argsNameCount++;
    }
    newFunction->argsName = (wchar_t**)malloc(sizeof(wchar_t*)*argsNameCount);
    if(!argsName) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        free(newFunction->name);
        free(newFunction->returnType);
        free(newFunction);
        return;
    }
    for(int i = 0; i < argsNameCount; i++) {
        newFunction->argsName[i] = (wchar_t*)malloc(sizeof(wchar_t)*wcslen(argsName[i]));
        if(!argsName[i]) {
            setlocale(LC_ALL,"C");
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(newFunction->name);
            free(newFunction->returnType);
            free(newFunction->argsName);
            free(newFunction);
            return;
        }
        wcscpy(newFunction->argsName[i],argsName[i]);
        /*********************************/
        setlocale(LC_ALL,"C");
        fwprintf(stdout,L"参数%d：%ls\n",i+1,newFunction->argsName[i]);
        /*********************************/
    }
    if(functionSymbolTable == NULL) {
        functionSymbolTable = NULL;
        functionCount = 0;
    }
    functionCount++;
    void* temp = realloc(functionSymbolTable,sizeof(Function)*functionCount);
    if(!temp) {
        setlocale(LC_ALL,"C");
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        functionCount--;
        return;
    }
    functionSymbolTable = (Function*)temp;
    functionSymbolTable[functionCount-1] = *newFunction;
    free(newFunction);
    return;
}
double callFunction(
    const wchar_t* name,
    const wchar_t* returnType,
    const wchar_t** argsType
) {

}
#endif