#ifndef __HXSCRIPT_SRC_FILEREADER_H__
#define __HXSCRIPT_SRC_FILEREADER_H__
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HXSLang/error.h"
//从标准输入流读取一行,发生错误时返回1
int getLine(wchar_t* obj_str) {
    if(obj_str == NULL) {
        return 1;
    }
    size_t capacity = 16;
    wchar_t ch;
    int count = 0;      //已读取字符的计数,便于将字符加入字符串
    while((ch = fgetwc(stdin)) != WEOF && ch != L'\n') {
        if (count + 1 >= capacity) {
            capacity *= 2;
            wchar_t* temp = (wchar_t*)realloc(obj_str, sizeof(wchar_t) * capacity);
            if (!temp) {
                free(obj_str);
                fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
                setlocale(LC_ALL, NULL);
                return 1;
            }
            obj_str = temp;
        }
        obj_str[count++] = (wchar_t)ch;
    }
    obj_str[count] = L'\0';
    return 0;
}
//从文件中读取并拆分语句的方法,一行表示一个命令,命令以';'或'。'分隔
wchar_t** getCommamdFromSourceFile(const char* path) {
    setlocale(LC_ALL,"zh_CN.UTF-8");
    int rows = 1;                  //行数、命令数
    //分配初始行数
    wchar_t** commands = (wchar_t**)malloc(sizeof(wchar_t*)*rows);
    if(!commands) {
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
        return NULL;
    }
    FILE* fp = fopen(path,"r");
    if(!fp) {
        fwprintf(stderr,L"%ls",SYSTEM_ERROR_FILE_OPEN);
        free(commands);
        return NULL;
    }
    size_t capacity = 8;              //每次扩容
    wchar_t ch;                       //临时字符
    bool hasDoubleQuote = false;      //是否有双引号括起
    bool hasHuaKuoHao = false;        //是否有花括号括起
    int count = 0;
    while((ch = fgetwc(fp)) != WEOF) {
        //初始化
        if(commands[rows-1] == NULL) {
            commands[rows-1] = (wchar_t*)malloc(sizeof(wchar_t)*capacity);
            if(!commands[rows-1]) {
                free(commands);
                fclose(fp);
                fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
                return NULL;
            }
        }
        //调整大小
        if(count+1 >= capacity) {
            capacity *= 2;
            wchar_t* temp = (wchar_t*)realloc(commands[rows-1], sizeof(wchar_t) * capacity);
            if (!temp) {
                free(commands);
                fclose(fp);
                fwprintf(stderr,L"%ls",SYSTEM_ERROR_MEMORY_MALLOC);
                setlocale(LC_ALL, NULL);
                return NULL;
            }commands[rows-1] = temp;
        }
        if(ch == L'\"') {
            //检查count，防止越界
           if(count == 0) {
                commands[rows-1][count] = ch;
                hasDoubleQuote = true;
                continue;


                
           } 
        }
    }
    fclose(fp);
    return commands;
}
#endif