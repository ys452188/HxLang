/*数据结构*/
#ifndef __HXLANG_SRC_HXC_DATASTRUCT_H__
#define __HXLANG_SRC_HXC_DATASTRUCT_H__
/*类型编号*/
#define HXC_TYPE_INT 1
#define HXC_TYPE_FLOAT 2
#define HXC_TYPE_DOUBLE 3
#define HXC_TYPE_CHAR 4
#define HXC_TYPE_UNICODE 5
#define HXC_TYPE_STR 6
#define HXC_TYPE_BOOL 7
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
/****************************************************************************************************/
long int varCount = 0;     /*变量计数*/
long int conCount = 0;     /*常量计数*/
long int funCount = 0;     /*函数计数*/
int initSymbol(void);      /*初始化符号表，失败则返回-1*/
int addVariable(const wchar_t* name,const int type,const double value);  /*添加变量到符号表，失败则返回-1*/
int addConstant(const wchar_t* name,const int type,const double value);  /*添加常量到符号表，失败则返回-1*/
int addFunction(const wchar_t* name,
    const wchar_t** argsName,
    const int returnType,
    const int* argsType,
    const wchar_t* body);        /*添加函数到符号表，失败则返回-1*/
bool isVariableExist(wchar_t* name);  /*判断变量是否存在，存在则返回true*/
bool isConstantExist(wchar_t* name);  /*判断常量是否存在，存在则返回true*/
bool isFunctionExist(wchar_t* name,const int* argsType);  /*判断函数是否存在，存在则返回true*/
double getVariableValue(const wchar_t* name);  /*获取变量的值*/
double getConstantValue(const wchar_t* name);  /*获取常量的值*/
void cleanupSymbol(void);   /*清理符号表*/
/***************************************************************************************************/
typedef struct {       /*变量*/
    wchar_t* name;     /*变量名*/
    int type;          /*变量类型*/
    void* address;     /*地址*/
} Variable;
Variable* variableSymbolTable = NULL;  /*变量符号表*/
typedef struct {       /*常量*/
    wchar_t* name;     /*常量名*/
    int type;          /*常量类型*/
    void* address;     /*地址*/
} Constant;
Constant* constantSymbolTable = NULL;  /*常量符号表*/
typedef struct {       /*函数*/
    wchar_t* name;     /*函数名*/
    wchar_t** argsName;/*参数名*/
    int returnType;   /*反回类型*/
    int* argsType;     /*参数类型*/
    wchar_t* body;     /*函数体*/
} Function;
Function* functionSymbolTable = NULL;  /*函数符号表*/
/**************************************************************************************************/
int initSymbol(void) {
    if(variableSymbolTable == NULL) {
        variableSymbolTable = (Variable*)malloc(sizeof(Variable)*1);
        if(!variableSymbolTable) {
            /*跨平台的颜色变换*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]内存分配失败！\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
            #endif
            return -1;
        }
    }
    if(constantSymbolTable == NULL) {
        constantSymbolTable = (Constant*)malloc(sizeof(Constant)*1);
        if(!constantSymbolTable) {
            /*跨平台的颜色变换*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]内存分配失败！\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
            #endif
            return -1;
        }
    }
    if(functionSymbolTable == NULL) {
        functionSymbolTable = (Function*)malloc(sizeof(Function)*1);
        if(!functionSymbolTable) {
            /*跨平台的颜色变换*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]内存分配失败！\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
            #endif
            return -1;
        }
    }
    return 0;
}
void cleanupSymbol(void) {
    if(variableSymbolTable == NULL) {
        goto c;
    } else {
        for(long int i = 0; i < varCount;i++) {
            free(variableSymbolTable[i].address);
            free(variableSymbolTable[i].name);
        }
        free(variableSymbolTable);
    }
    c:
    if (constantSymbolTable == NULL) {
        goto f;
    } else {
        for(long int i = 0; i < conCount;i++) {
            free(constantSymbolTable[i].address);
            free(constantSymbolTable[i].name);
        }
        free(constantSymbolTable);
    }
    f:
    if (functionSymbolTable == NULL) {
        return;
    } else {
        for(long int i = 0; i < funCount;i++) {
            free(functionSymbolTable[i].body);
            free(functionSymbolTable[i].name);
            free(functionSymbolTable[i].argsType);
            free(functionSymbolTable[i].argsName);
        }
        free(functionSymbolTable);
    }
    return;
}
int addVariable(const wchar_t* name,const int type,const double value) {
    Variable* newVar = (Variable*)malloc(sizeof(Variable));
    if(!newVar) {
        /*跨平台的颜色变换*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]内存分配失败！\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
        #endif
        return -1;
    }
    newVar->name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newVar->name) {
        /*跨平台的颜色变换*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]内存分配失败！\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
        #endif
        free(newVar);
        return -1;
    }
    wcscpy(newVar->name,name);
    newVar->type = type;
    newVar->address = malloc(sizeof(double));
    if(!newVar->address) {
        /*跨平台的颜色变换*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]内存分配失败！\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
        #endif
        free(newVar->name);
        free(newVar);
        return -1;
    }
    *(double*)newVar->address = value;
    variableSymbolTable = (Variable*)realloc(variableSymbolTable,sizeof(Variable)*(varCount+1));
    if(!variableSymbolTable) {
        /*跨平台的颜色变换*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]内存分配失败！\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
        #endif
        free(newVar->name);
        free(newVar->address);
        free(newVar);
        return -1;
    }
    variableSymbolTable[varCount] = *newVar;
    free(newVar->name);
    free(newVar->address);
    free(newVar);
    varCount++;
    return 0;
}
double getVariableValue(const wchar_t* name) {
    for(long int i = 0; i < varCount;i++) {
        if(wcscmp(variableSymbolTable[i].name,name) == 0) {
            return *(double*)variableSymbolTable[i].address;
        }
    }
    return NAN;
}
#endif
