/*���ݽṹ*/
#ifndef __HXLANG_SRC_HXC_DATASTRUCT_H__
#define __HXLANG_SRC_HXC_DATASTRUCT_H__
/*���ͱ��*/
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
long int varCount = 0;     /*��������*/
long int conCount = 0;     /*��������*/
long int funCount = 0;     /*��������*/
int initSymbol(void);      /*��ʼ�����ű�ʧ���򷵻�-1*/
int addVariable(const wchar_t* name,const int type,const double value);  /*��ӱ��������ű�ʧ���򷵻�-1*/
int addConstant(const wchar_t* name,const int type,const double value);  /*��ӳ��������ű�ʧ���򷵻�-1*/
int addFunction(const wchar_t* name,
    const wchar_t** argsName,
    const int returnType,
    const int* argsType,
    const wchar_t* body);        /*��Ӻ��������ű�ʧ���򷵻�-1*/
bool isVariableExist(wchar_t* name);  /*�жϱ����Ƿ���ڣ������򷵻�true*/
bool isConstantExist(wchar_t* name);  /*�жϳ����Ƿ���ڣ������򷵻�true*/
bool isFunctionExist(wchar_t* name,const int* argsType);  /*�жϺ����Ƿ���ڣ������򷵻�true*/
double getVariableValue(const wchar_t* name);  /*��ȡ������ֵ*/
double getConstantValue(const wchar_t* name);  /*��ȡ������ֵ*/
void cleanupSymbol(void);   /*������ű�*/
/***************************************************************************************************/
typedef struct {       /*����*/
    wchar_t* name;     /*������*/
    int type;          /*��������*/
    void* address;     /*��ַ*/
} Variable;
Variable* variableSymbolTable = NULL;  /*�������ű�*/
typedef struct {       /*����*/
    wchar_t* name;     /*������*/
    int type;          /*��������*/
    void* address;     /*��ַ*/
} Constant;
Constant* constantSymbolTable = NULL;  /*�������ű�*/
typedef struct {       /*����*/
    wchar_t* name;     /*������*/
    wchar_t** argsName;/*������*/
    int returnType;   /*��������*/
    int* argsType;     /*��������*/
    wchar_t* body;     /*������*/
} Function;
Function* functionSymbolTable = NULL;  /*�������ű�*/
/**************************************************************************************************/
int initSymbol(void) {
    if(variableSymbolTable == NULL) {
        variableSymbolTable = (Variable*)malloc(sizeof(Variable)*1);
        if(!variableSymbolTable) {
            /*��ƽ̨����ɫ�任*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
            #endif
            return -1;
        }
    }
    if(constantSymbolTable == NULL) {
        constantSymbolTable = (Constant*)malloc(sizeof(Constant)*1);
        if(!constantSymbolTable) {
            /*��ƽ̨����ɫ�任*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
            #endif
            return -1;
        }
    }
    if(functionSymbolTable == NULL) {
        functionSymbolTable = (Function*)malloc(sizeof(Function)*1);
        if(!functionSymbolTable) {
            /*��ƽ̨����ɫ�任*/
            #ifdef _WIN32
            system("COLOR C");
            fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
            system("COLOR");
            #else
            fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
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
        /*��ƽ̨����ɫ�任*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
        #endif
        return -1;
    }
    newVar->name = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(name)+1));
    if(!newVar->name) {
        /*��ƽ̨����ɫ�任*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
        #endif
        free(newVar);
        return -1;
    }
    wcscpy(newVar->name,name);
    newVar->type = type;
    newVar->address = malloc(sizeof(double));
    if(!newVar->address) {
        /*��ƽ̨����ɫ�任*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
        #endif
        free(newVar->name);
        free(newVar);
        return -1;
    }
    *(double*)newVar->address = value;
    variableSymbolTable = (Variable*)realloc(variableSymbolTable,sizeof(Variable)*(varCount+1));
    if(!variableSymbolTable) {
        /*��ƽ̨����ɫ�任*/
        #ifdef _WIN32
        system("COLOR C");
        fprintf(stderr,"[E]�ڴ����ʧ�ܣ�\n");
        system("COLOR");
        #else
        fprintf(stderr,"\033[38;2;255;0;0m[E]�ڴ����ʧ�ܣ�\033[0m\n");
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
