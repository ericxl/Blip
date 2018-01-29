//
//  SymbolTable.cpp
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    index = 0;
    for (int i=0; i<TABLE_SIZE;i++){
        roots[i] = nullptr;
    }
    //capacity = 1;
    //roots = new TableNodePtr[capacity];
}
void deleteRec(SymbolTable::TableNode* root) {
    if(root!=nullptr) {
        deleteRec(root->left);
        deleteRec(root->right);
        
        delete root;
    }
}
SymbolTable::~SymbolTable() {
    for(int i = 0; i<TABLE_SIZE;i++) {
        if(roots[i]!= nullptr) {
            deleteRec(roots[i]);
        }
    }
}

void addRec(SymbolTable::TableNodePtr &root, String name, int value, SymbolError* error) {
    if(root==nullptr) {
        SymbolTable::TableNodePtr newNode = new SymbolTable::TableNode;
        newNode->name = name;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        root = newNode;
        if(error) *error = NOERROR;
        
        return;
    }
    if(name < root->name) {
        addRec(root->left, name, value, error);
    }
    else if(name > root->name) {
        addRec(root->right, name, value, error);
    }
    else {
        root->name = name;
        root->value = value;
        if(error) *error = REDEFINED;
    }
}
int getRec(SymbolTable::TableNodePtr &root, String name, SymbolError* error) {
    if(root==nullptr) {
        if(error) *error = NOTFOUND;
        return 0;
    }
    if(root->name == name) {
        if(error) *error = NOERROR;
        return root->value;
    }
    if(root->name < name) {
        return getRec(root->right, name,error);
    }
    if(root->name > name) {
        return getRec(root->left, name,error);
    }
    return 0;
}

void setRec(SymbolTable::TableNodePtr &root, String name, int value, SymbolError* error) {
    if(root==nullptr) {
        if(error) *error = NOTFOUND;
        return;
    }
    if(root->name == name) {
        if(error) *error = NOERROR;
        root->value = value;
        return;
    }
    if(root->name < name) {
        return setRec(root->right, name,value,error);
    }
    if(root->name > name) {
        return setRec(root->left, name,value,error);
    }
}



void SymbolTable::add(String name, int value, SymbolError* error) {
    addRec(roots[index], name, value, error);
}
int SymbolTable::get(String name, SymbolError* error) {
    int result = getRec(roots[index], name, error);
    
    if(*error == NOERROR) {
        return result;
    }
    result = getRec(roots[0], name, error);
    
    return result;
    
}
void SymbolTable::set(String name, int value, SymbolError* error) {
    setRec(roots[index], name, value, error);
    
    if(*error==NOERROR) {
        return;
    }
    
    setRec(roots[0], name, value, error);
    if(*error!=NOERROR) {
        addRec(roots[0], name, value, nullptr);
    }
}
void SymbolTable::next(){
    if(index+1<TABLE_SIZE){
        index++;
    }
}

void SymbolTable::back() {
    if(index>0) {
        deleteRec(roots[index]);
        roots[index] = nullptr;
        index = index-1;
    }
}