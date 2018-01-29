//
//  ParseNode.h
//  pj10
//
//  Created by Eric Liang on 12/1/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include <stdio.h>
#include "String.h"
#include "Parse.h"
#include "SymbolTable.h"

#ifndef ParseNode_h
#define ParseNode_h

extern SymbolTable* symbolTable;
class ParseNode{
public:
    
    struct ReturnData {
        //the return value when a parse node executes
        int value;
        //at the base node, it means whether to change the pc
        bool returned;
        
        ReturnData operator+(ReturnData data) {
            return ReturnData{this->value + data.value, this->returned && data.returned};
        }
        ReturnData operator-(ReturnData data) {
            return ReturnData{this->value - data.value, this->returned && data.returned};
        }
        ReturnData operator*(ReturnData data) {
            return ReturnData{this->value * data.value, this->returned && data.returned};
        }
        ReturnData operator/(ReturnData data) {
            return ReturnData{this->value / data.value, this->returned && data.returned};
        }
        ReturnData operator%(ReturnData data) {
            return ReturnData{this->value % data.value, this->returned && data.returned};
        }
        ReturnData operator&&(ReturnData data) {
            return ReturnData{this->value && data.value, this->returned && data.returned};
        }
        ReturnData operator||(ReturnData data) {
            return ReturnData{this->value || data.value, this->returned && data.returned};
        }
        ReturnData operator<(ReturnData data) {
            return ReturnData{this->value < data.value, this->returned && data.returned};
        }
        ReturnData operator>(ReturnData data) {
            return ReturnData{this->value > data.value, this->returned && data.returned};
        }
        ReturnData operator==(ReturnData data) {
            return ReturnData{this->value == data.value, this->returned && data.returned};
        }
        ReturnData operator!=(ReturnData data) {
            return ReturnData{this->value != data.value, this->returned && data.returned};
        }
        ReturnData operator<=(ReturnData data) {
            return ReturnData{this->value <= data.value, this->returned && data.returned};
        }
        ReturnData operator>=(ReturnData data) {
            return ReturnData{this->value >= data.value, this->returned && data.returned};
        }
        ReturnData operator!() {
            return ReturnData{!this->value, this->returned};
        }
        ReturnData operator~() {
            return ReturnData{-(this->value), this->returned};
        }
    };
public:

    String name;
    TokenType type;
    int value;
    bool endNode;
    bool binaryNode;
    
    ParseNode *left;
    ParseNode *right;
    
    ParseNode();
    ParseNode(String varName, TokenType tokentype, int var);
    ParseNode(int var);
    //ParseNode (const ParseNode &that);
    ~ParseNode();
    
    ReturnData evaluate();
};



#endif /* ParseNode_h */
