//
//  Interpreter.cpp
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include "Interpreter.h"


Interpreter::Interpreter() {
}
Interpreter::~Interpreter() {
    if(symbolTable) {
        delete symbolTable;
        symbolTable = nullptr;
    }
}

ParseNode generateParseNode() {
    ParseNode node = ParseNode();
    //what to ignore
    do {
        read_next_token();
        node.name = next_token();
        node.type = next_token_type;
        node.value = token_number_value;
    } while (node.name == "smarap" || node.name == "sgra");
    //skip lines
    if (node.name == "//") {
        skip_line();
        return generateParseNode();
    }
    //a number is always an end node
    if(node.type == NUMBER) {
        node.endNode = true;
    }
    //every symbol is a binary node excep ~ and !
    else if(node.type == SYMBOL ){
        if(node.name == "~" || node.name == "!") {
            node.binaryNode = false;
        }
    }
    //every name either implies a var or a keyword
    else if(node.type == NAME) {
        // if a keyword, then not end node; otherwise it implies a variable
        if(node.name != "set" && node.name != "var" && node.name!= "text" && node.name!= "output" && node.name != "do" && node.name != "if" &&node.name != "defun" && node.name!="params" && node.name!="call" && node.name!="args" && node.name!="return") {
            node.endNode = true;
        }
        //keyword, value is 0
        else {
            node.value = 0;
        }
        //keyword, but not a binary node
        if(node.name == "if" || node.name == "do" || node.name == "return") {
            node.binaryNode = false;
        }
    }
    
    return node;
}
Program *program;
void Interpreter::interpret() {
    if(symbolTable== nullptr) {
        symbolTable = new SymbolTable();
    }
    else {
        delete symbolTable;
        symbolTable = new SymbolTable;
    }
    
    Program pro = Program();
    program = &pro;
    
    Statement* st = nullptr;
    while (true) {
        ParseNode node = generateParseNode();
        
        if (node.type == END) {
            if (st != nullptr) {
                Statement newSt = *st;
                pro.insert(*st);
                //delete st;
            }
            break;
        }
        
        //these implies that a new statement needs to be formed
        if (node.name == "set" || node.name == "var" || node.name == "output" || node.name == "text" || node.name == "do" || node.name == "od" || node.name == "if" || node.name == "else" || node.name == "fi" || node.name == "defun" || node.name == "return" || node.name == "nufed") {
            if (st != nullptr) {
                Statement newSt = *st;
                pro.insert(*st);
                //delete st;
            }
            st = new Statement();
        }
        st->insert(node);
    }
    //call the program to run
    pro.run();
}