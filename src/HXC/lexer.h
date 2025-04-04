/*Hx语言预编译器的词法分析器*/
#ifndef HXLANG_SRC_HXC_LEXER
#define HXLANG_SRC_HXC_LEXER
/*By 硫酸铜非常好吃*/
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef enum {
    TOKEN_KEY_WORD,       /*关键字*/
    TOKEN_STR_VALUE,      /*字符串数据*/
    TOKEN_NUMBER_VALUE,   /*数字*/
    TOKEN_VARIABLE_NAME,  /*变量名*/
    TOKEN_FUNCTION_NAME,  /*函数名*/
    TOKEN_STRUCT_NAME,    /*结构体*/
    TOKEN_OPERATOR_SYMBOL, /*运算符号*/
} TokenType;
typedef struct {
    TokenType type;    /*这个Token的类型,用于标识这个Token大概是什么*/
    wchar_t* value;    /*具体代码*/
} Token;
wchar_t* getData(const char* path);             /*从文件获取数据*/
Token* lexer_getToken(const wchar_t* data);  /*将数据拆分为token*/
wchar_t* getData(const char* path) {
    /*Windows 下使用 UTF-8 编码*/
#ifdef _WIN32
    FILE* fp = fopen(path, "r, ccs=UTF-8");
#else
    FILE* fp = fopen(path, "r");
#endif
    if (fp == NULL) {
#ifdef _WIN32
        fprintf(stderr, "[E]错误：无法打开文件 %s (%s)\n", path, strerror(errno));
#else
        fprintf(stderr, "\033[31m[E]错误：无法打开文件 %s (%s)\033[0m\n", path, strerror(errno));
#endif
        return NULL;
    }

    int capacity = 8;
    int size = capacity;
    wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * size);
    if (!data) {
        fclose(fp);
#ifdef _WIN32
        fprintf(stderr, "[E]内存分配失败！\n");
#else
        fprintf(stderr, "\033[31m[E]内存分配失败！\033[0m\n");
#endif
        return NULL;
    }

    wchar_t ch;
    size_t index = 0;
    while ((ch = fgetwc(fp)) != WEOF) {
        if (index >= size) {
            void* temp = realloc(data, capacity * 2 * sizeof(wchar_t));
            if (!temp) {
                fclose(fp);
                free(data);
#ifdef _WIN32
                fprintf(stderr, "[E]内存分配失败\n");
#else
                fprintf(stderr, "\033[31m[E]内存分配失败！\033[0m\n");
#endif
                return NULL;
            }
            data = (wchar_t*)temp;
            size = capacity * 2;
            capacity *= 2;
        }
        data[index++] = ch;
    }
    /*确保终止符空间*/
    if (index >= size) {
        void* temp = realloc(data, (index + 1) * sizeof(wchar_t));
        if (!temp) {
            fclose(fp);
            free(data);
#ifdef _WIN32
            fprintf(stderr, "[E]内存分配失败！\n");
#else
            fprintf(stderr, "\033[31m[E]内存分配失败\033[0m\n");
#endif
            return NULL;
        }
        data = (wchar_t*)temp;
    }
    data[index] = L'\0';
    /*处理 BOM（Windows 下已自动跳过 UTF-8 BOM）*/
#ifndef _WIN32
    if (index >= 3 && data[0] == 0xEFBB && data[1] == 0xBF00) { /*UTF-8 BOM 的宽字符表示*/
        memmove(data, data + 3, (index - 3) * sizeof(wchar_t));
        index -= 3;
        data[index] = L'\0';
    }
#endif
    fclose(fp);
    return data;
}

#endif