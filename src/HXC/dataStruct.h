/*数据结构*/
#ifndef HXLANG_SRC_HXC_DATASTRUCT_H
#define HXLANG_SRC_HXC_DATASTRUCT_H
/*By 硫酸铜非常好吃*/
/*类型编号*/
#define HXC_TYPE_INT 1
#define HXC_TYPE_FLOAT 2
#define HXC_TYPE_DOUBLE 3
#define HXC_TYPE_CHAR 4
#define HXC_TYPE_UNICODE_CHAR 5
#define HXC_TYPE_STR 6
#define HXC_TYPE_BOOL 7
#define HXC_TYPE_UNICODE_STR 8
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
int addVariable(const wchar_t* name,const int type,const void* value);  /*添加变量到符号表，失败则返回-1*/
int addConstant(const wchar_t* name,const int type,const double value);  /*添加常量到符号表，失败则返回-1*/
int addFunction(const wchar_t* name,
                const wchar_t** argsName,
                const int returnType,
                const int* argsType,
                const int argsCount,
                const wchar_t* body);        /*添加函数到符号表，失败则返回-1*/
bool isVariableExist(const wchar_t* name);  /*判断变量是否存在，存在则返回true*/
bool isConstantExist(const wchar_t* name);  /*判断常量是否存在，存在则返回true*/
bool isFunctionExist(const wchar_t* name,const int* argsType);  /*判断函数是否存在，存在则返回true*/
void outputVariableValue(const wchar_t* name);  /*获取变量的值*/
void outputConstantValue(const wchar_t* name);  /*获取常量的值*/
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
    int argCount;      /*参数个数*/
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

            fprintf(stderr,"[E]内存分配失败！\n");

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

            fprintf(stderr,"[E]内存分配失败！\n");

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

            fprintf(stderr,"[E]内存分配失败！\n");

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
        for(long int i = 0; i < varCount; i++) {
            free(variableSymbolTable[i].address);
            free(variableSymbolTable[i].name);
        }
        free(variableSymbolTable);
    }
c:
    if (constantSymbolTable == NULL) {
        goto f;
    } else {
        for(long int i = 0; i < conCount; i++) {
            free(constantSymbolTable[i].address);
            free(constantSymbolTable[i].name);
        }
        free(constantSymbolTable);
    }
f:
    if (functionSymbolTable == NULL) {
        return;
    } else {
        for(long int i = 0; i < funCount; i++) {
            free(functionSymbolTable[i].body);
            free(functionSymbolTable[i].name);
            free(functionSymbolTable[i].argsType);
            for (int j = 0; j < functionSymbolTable[i].argCount; j++) {
                free(functionSymbolTable[i].argsName[j]);
            }
            free(functionSymbolTable[i].argsName);
        }
        free(functionSymbolTable);
    }
    return;
}
int addVariable(const wchar_t* name,const int type,const void* value) {
    Variable* newVar = (Variable*)malloc(sizeof(Variable));
    if(!newVar) {
        /*跨平台的颜色变换*/
#ifdef _WIN32
        fprintf(stderr,"[E]内存分配失败！\n");
#else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
        return -1;
    }
    newVar->name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newVar->name) {
        /*跨平台的颜色变换*/
#ifdef _WIN32
        fprintf(stderr,"[E]内存分配失败！\n");
#else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
        free(newVar);
        return -1;
    }
    wcscpy(newVar->name,name);
    newVar->type = type;
    switch(newVar->type) {
    case HXC_TYPE_INT:
        newVar-> address = malloc(sizeof(int));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }

        printf("value = %d\n",*(int*)value);

        *(int*)newVar-> address = *(int*)value;

        printf("value = %d",*(int*)newVar-> address);

        break;
    case HXC_TYPE_DOUBLE:
        newVar-> address = malloc(sizeof(double));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }
        *(double*)newVar-> address = *(double*)value;
        break;
    case HXC_TYPE_FLOAT:
        newVar-> address = malloc(sizeof(float));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }
        *(float*)newVar-> address = *(float*)value;
        break;
    case HXC_TYPE_CHAR:
        newVar-> address = malloc(sizeof(char));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }
        *(char*)newVar-> address = *(char*)value;
        break;
    case HXC_TYPE_UNICODE_CHAR:
        newVar-> address = malloc(sizeof(wchar_t));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }
        *(wchar_t*)newVar-> address = *(wchar_t*)value;
        break;
    case HXC_TYPE_BOOL:
        newVar-> address = malloc(sizeof(bool));
        if(!newVar->address) {
#ifdef _WIN32
            fprintf(stderr,"[E]内存分配失败！\n");
#else
            fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
            free(newVar->name);
            free(newVar);
            return -1;
        }
        *(bool*)newVar-> address = *(bool*)value;
        break;
    case HXC_TYPE_STR:
        newVar-> address = malloc(sizeof(char));
        break;
    case HXC_TYPE_UNICODE_STR:
        newVar-> address = malloc(sizeof(wchar_t));
        break;
    default:
#ifdef _WIN32
        fprintf(stderr,"[E]未知类型！\n");
#else
        fprintf(stderr,"\033[38;2;255;0;0m[E]未知类型！\033[0m\n");
#endif
        free(newVar->name);
        free(newVar);
        return -1;
    }
    variableSymbolTable = (Variable*)realloc(variableSymbolTable,sizeof(Variable)*(varCount+1));
    if(!variableSymbolTable) {
        /*跨平台的颜色变换*/
#ifdef _WIN32
        fprintf(stderr,"[E]内存分配失败！\n");
#else
        fprintf(stderr,"\033[38;2;255;0;0m[E]内存分配失败！\033[0m\n");
#endif
        free(newVar->name);
        free(newVar->address);
        free(newVar);
        return -1;
    }
    variableSymbolTable[varCount] = *newVar;
    varCount++;
    return 0;
}
void outputVariableValue(const wchar_t* name) {
    for(long int i = 0; i < varCount; i++) {
        if(wcscmp(variableSymbolTable[i].name,name) == 0) {
            switch(variableSymbolTable[i].type) {
            case HXC_TYPE_INT:
                printf("%ls = %d\n",variableSymbolTable[i].name,*(int*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_DOUBLE:
                printf("%ls = %lf\n",variableSymbolTable[i].name,*(double*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_FLOAT:
                printf("%ls = %f\n",variableSymbolTable[i].name,*(float*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_CHAR:
                printf("%ls = %c\n",variableSymbolTable[i].name,*(char*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_UNICODE_CHAR:
                printf("%ls = %c\n",variableSymbolTable[i].name,*(wchar_t*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_BOOL:
                printf("%ls = %d\n",variableSymbolTable[i].name,*(bool*)variableSymbolTable[i].address);
                break;
            case HXC_TYPE_STR:

                break;
            case HXC_TYPE_UNICODE_STR:

                break;
            default:
#ifdef _WIN32
                fprintf(stderr,"[E]未知类型！\n");
#else
                fprintf(stderr,"\033[38;2;255;0;0m[E]未知类型！\033[0m\n");
#endif
                return;
            }
        }
    }
    return;
}
#endif