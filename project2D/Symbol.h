#pragma once
#include <memory>

#ifndef Symbol_Init
#define Symbol_Init

class Symbol{
    char* data = nullptr;

    static char* copyString(char* str){
        int len = strlen(str);
        char* d = (char*)malloc(len + 1);
        strcpy(d, str);
        d[len] = '\0';
        return d;
    }
  public:

    Symbol(char* name){
        if(data != nullptr)
            free(data);
        
        data = copyString(name);
    }

    Symbol(const Symbol& original){
        if(data != nullptr)
            free(data);

        data = copyString(original.data);
    }

    Symbol(Symbol&& original) noexcept{
        if(data != nullptr)
            free(data);

        data = original.data;
        original.data = nullptr;
    }

    ~Symbol(){
        if(data != nullptr)
            free(data);
    }

    Symbol& operator=(const Symbol& original){
        if(data != nullptr)
            free(data);

        data = copyString(original.data);
        return *this;
    }
    
    Symbol& operator=(Symbol&& original)noexcept{
        if(data != nullptr)
            free(data);

        data = original.data;
        original.data = nullptr;
        return *this;
    }

    bool operator==(const Symbol& other){
        return strcmp(data, other.data) == 0;
    }
};

#endif