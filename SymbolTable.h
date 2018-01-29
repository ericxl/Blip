//
//  SymbolTable.h
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include "String.h"

#ifndef SymbolTable_h
#define SymbolTable_h
#define TABLE_SIZE 4096

enum SymbolError {
    NOERROR,
    REDEFINED,
    NOTFOUND
};

class SymbolTable {
public:
    struct TableNode{
        String name;
        int value;
        TableNode* left;
        TableNode* right;
        
        TableNode() {
            name = "";
            value = 0;
        }
        TableNode(int varValue, String varName) {
            value = varValue;
            name = varName;
        }
        
    };
    
    typedef TableNode* TableNodePtr;
    
    TableNodePtr roots[TABLE_SIZE];
private:
    int index;
    
public:
    SymbolTable();
    ~SymbolTable();
    
    void add(String name, int value, SymbolError* error);
    //void add(String name, int value);
    
    int get(String name, SymbolError* error);
    //int get(String name);
    
    void set(String name, int value, SymbolError* error);
    //void set(String name, int value);
    
    void next();
    void back();
};
#endif /* SymbolTable_h */
