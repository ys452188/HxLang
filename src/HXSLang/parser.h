#ifndef __HXSCRIPT_SRC_HXSLANG_PARSER_H__
#include <wchar.h>
#include <stdlib.h>
#include <stdbool.h>
#include "variable.h"
#include "error.h"
//语法分析:定义变量
bool parser_defineVariable(const wchar_t*);
//语法分析:定义常量
bool parser_defineConstant(const wchar_t*);

bool parser_defineVariable(const wchar_t* command_o) {
    wchar_t* command = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(command_o)+1));
    if(!command) {
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return true;
    }
    wcscpy(command,command_o);
    wchar_t* p = command;
    while(*p == L' ' || *p == L'\t') {
        p++;
    }
    //检查长度以避免越界
    wchar_t* ptrCommandEnd = command + wcslen(command); // 指向字符串结尾的 \0
    if (ptrCommandEnd - p <= 3) { // 剩余字符不足 "var " 的最小长度
        free(command);
        return false;
    }
    if(*p == L'v'&&*(p +1 ) == L'a'&&*(p+2) == L'r'
            && (*(p+3) == L' ' || *(p+3) == L'\t')) {
        p+=3;
        while(*p == L' ' || *p == L'\t') {
            p++;
        }
        wchar_t* variableBegin = p;
        while(!(*p == L' ' || *p == L'\t')) {
            p++;
        }
        wchar_t* variableEnd = p;
        size_t variableLength = variableEnd-variableBegin;
        wchar_t* variable = (wchar_t*)malloc(sizeof(wchar_t)*(variableLength+1));
        if(!variable) {
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(command);
            return true;
        }
        wcsncpy(variable,variableBegin,variableLength);
        variable[variableLength] = L'\0';

        fwprintf(stdout,L"%ls\n",variable);
        
        //递归求右值
        double temp = 0;

        free(command);
        free(variable);
        return true;
    }

    if (ptrCommandEnd - p <= 4) {
        free(command);
        return false;
    }
    if(*p == L'定'&&*(p +1 ) == L'义'&&*(p+2) == L'变' && *(p+3) == L'量'
            && (*(p+4) == L' ' || *(p+4) == L'\t')) {
        p+=4;
        while(*p == L' ' || *p == L'\t') {
            p++;
        }
        wchar_t* variableBegin = p;
        while(!(*p == L' ' || *p == L'\t')) {
            p++;
        }
        wchar_t* variableEnd = p;
        size_t variableLength = variableEnd-variableBegin;
        wchar_t* variable = (wchar_t*)malloc(sizeof(wchar_t)*(variableLength+1));
        if(!variable) {
            fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
            free(command);
            return true;
        }
        wcsncpy(variable,variableBegin,variableLength);
        variable[variableLength] = L'\0';
		/********************************/
        setlocale(LC_ALL,"chinese");
        fwprintf(stdout,L"定义的变量：%ls\n",variable);
		/********************************/
        free(command);
        free(variable);
        return true;
    } else {
        free(command);
        return false;
    }
    return false;
}
#define __HXSCRIPT_SRC_HXSLANG_PARSER_H__
#endif