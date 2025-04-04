/*Hx����Ԥ�������Ĵʷ�������*/
#ifndef HXLANG_SRC_HXC_LEXER
#define HXLANG_SRC_HXC_LEXER
/*By ����ͭ�ǳ��ó�*/
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
typedef enum {
    TOKEN_KEY_WORD,       /*�ؼ���*/
    TOKEN_STR_VALUE,      /*�ַ�������*/
    TOKEN_NUMBER_VALUE,   /*����*/
    TOKEN_VARIABLE_NAME,  /*������*/
    TOKEN_FUNCTION_NAME,  /*������*/
    TOKEN_STRUCT_NAME,    /*�ṹ��*/
    TOKEN_OPERATOR_SYMBOL, /*�������*/
} TokenType;
typedef struct {
    TokenType type;    /*���Token������,���ڱ�ʶ���Token�����ʲô*/
    wchar_t* value;    /*�������*/
} Token;
wchar_t* getData(const char* path);             /*���ļ���ȡ����*/
Token* lexer_getToken(const wchar_t* data);  /*�����ݲ��Ϊtoken*/
wchar_t* getData(const char* path) {
    /*Windows ��ʹ�� UTF-8 ����*/
#ifdef _WIN32
    FILE* fp = fopen(path, "r, ccs=UTF-8");
#else
    FILE* fp = fopen(path, "r");
#endif
    if (fp == NULL) {
#ifdef _WIN32
        fprintf(stderr, "[E]�����޷����ļ� %s (%s)\n", path, strerror(errno));
#else
        fprintf(stderr, "\033[31m[E]�����޷����ļ� %s (%s)\033[0m\n", path, strerror(errno));
#endif
        return NULL;
    }

    int capacity = 8;
    int size = capacity;
    wchar_t* data = (wchar_t*)malloc(sizeof(wchar_t) * size);
    if (!data) {
        fclose(fp);
#ifdef _WIN32
        fprintf(stderr, "[E]�ڴ����ʧ�ܣ�\n");
#else
        fprintf(stderr, "\033[31m[E]�ڴ����ʧ�ܣ�\033[0m\n");
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
                fprintf(stderr, "[E]�ڴ����ʧ��\n");
#else
                fprintf(stderr, "\033[31m[E]�ڴ����ʧ�ܣ�\033[0m\n");
#endif
                return NULL;
            }
            data = (wchar_t*)temp;
            size = capacity * 2;
            capacity *= 2;
        }
        data[index++] = ch;
    }
    /*ȷ����ֹ���ռ�*/
    if (index >= size) {
        void* temp = realloc(data, (index + 1) * sizeof(wchar_t));
        if (!temp) {
            fclose(fp);
            free(data);
#ifdef _WIN32
            fprintf(stderr, "[E]�ڴ����ʧ�ܣ�\n");
#else
            fprintf(stderr, "\033[31m[E]�ڴ����ʧ��\033[0m\n");
#endif
            return NULL;
        }
        data = (wchar_t*)temp;
    }
    data[index] = L'\0';
    /*���� BOM��Windows �����Զ����� UTF-8 BOM��*/
#ifndef _WIN32
    if (index >= 3 && data[0] == 0xEFBB && data[1] == 0xBF00) { /*UTF-8 BOM �Ŀ��ַ���ʾ*/
        memmove(data, data + 3, (index - 3) * sizeof(wchar_t));
        index -= 3;
        data[index] = L'\0';
    }
#endif
    fclose(fp);
    return data;
}

#endif