//
//  ParseNode.cpp
//  pj10
//
//  Created by Eric Liang on 12/1/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include "ParseNode.h"
#include "Program.h"
#include "Interpreter.h"
ParseNode::ParseNode() {
    name = "";
    value = 0;
    type = INVALID;
    endNode = false;
    binaryNode = true;
    left = nullptr;
    right = nullptr;
}

ParseNode::ParseNode(String varName, TokenType tokentype, int var) {
    name = varName;
    this->type = tokentype;
    this->value = var;
    left = nullptr;
    right = nullptr;
    endNode = false;
    binaryNode = true;
}

ParseNode::ParseNode(int var) {
    name = "";
    this->type = TokenType::NUMBER;
    this->value = var;
    left = nullptr;
    right = nullptr;
    endNode = true;
    binaryNode = true;
}
/*
ParseNode::ParseNode (const ParseNode &that) {
    this->name = that.name;
    this->type = that.type;
    this->value = that.value;
    left = nullptr;
    right = nullptr;
    endNode = that.endNode;
    binaryNode = that.binaryNode;
}
*/
ParseNode::~ParseNode(){
}
extern Program *program;
ParseNode::ReturnData ParseNode::evaluate() {
    ParseNode::ReturnData returnValue = ReturnData{0,false};
    
    if(this->type == NUMBER) {
        returnValue.value = this->value;
        returnValue.returned = true;
    }
    else if(this->type == SYMBOL) {
        if(name == "+") {
            returnValue = this->left->evaluate() + this->right->evaluate();
        }
        else if(name == "-") {
            returnValue = this->left->evaluate() - this->right->evaluate();
        }
        else if(name == "*") {
            returnValue = this->left->evaluate() * this->right->evaluate();
        }
        else if(name == "/") {
            returnValue = this->left->evaluate() / this->right->evaluate();
        }
        else if(name == "%") {
            returnValue = this->left->evaluate() % this->right->evaluate();
        }
        else if(name == "&&") {
            returnValue = this->left->evaluate() && this->right->evaluate();
        }
        else if(name == "||") {
            returnValue = this->left->evaluate() || this->right->evaluate();
        }
        else if(name == "<") {
            returnValue = this->left->evaluate() < this->right->evaluate();
        }
        else if(name == ">") {
            returnValue = this->left->evaluate() > this->right->evaluate();
        }
        else if(name == "==") {
            returnValue = this->left->evaluate() == this->right->evaluate();
        }
        else if(name == "!=") {
            returnValue = this->left->evaluate() != this->right->evaluate();
        }
        else if(name == "<=") {
            returnValue = this->left->evaluate() <= this->right->evaluate();
        }
        else if(name == ">=") {
            returnValue = this->left->evaluate() >= this->right->evaluate();
        }
        else if(name == "!") {
            returnValue = !(this->left->evaluate());
        }
        else if(name == "~") {
            returnValue = ~(this->left->evaluate());
        }
    }
    else if(this->type == NAME) {
        if(name =="set") {
            int value = this->right->evaluate().value;
            SymbolError err;
            symbolTable->set(this->left->name, value, &err);
            if(err==NOTFOUND) {
                printf("variable %s not declared",this->left->name.c_str());
            }
        }
        else if(name =="var") {
            int value = this->right->evaluate().value;
            SymbolError err;
            symbolTable->add(this->left->name, value, &err);
            if(err==REDEFINED) {
                printf("variable %s incorrectly re-initialized",this->left->name.c_str());
            }
        }
        else if(name == "output") {
            int value = this->left->evaluate().value;
            printf("%d",value);
        }
        else if(name == "text") {
            printf("%s",this->left->name.c_str());
        }
        else if(name == "do") {
            //int value = this->left->evaluate().value;
            if (!this->left->evaluate().value) {
                returnValue.returned = true;
            }
        }
        else if(name == "od") {
            returnValue.returned = true;
        }
        else if(name == "if") {
            if (!this->left->evaluate().value) {
                returnValue.returned = true;
            }
            else {
                returnValue.returned = false;
            }
            
        }
        
        else if(name == "else") {
            returnValue.returned = true;
        }
        else if(name == "fi") {
            returnValue.returned = false;
        }
        
        else if(name == "defun") {
            returnValue.returned = true;
        }
        else if (name == "nufed") {
            returnValue.returned = false;
        }
        else if(name == "call") {
            returnValue.value = program->run_subroutine(this);
            returnValue.returned = false;
        }
        else if(name == "return") {
            returnValue.value = this->left->evaluate().value;
            returnValue.returned = true;
        }
        else {
            SymbolError err;
            int varValue = symbolTable->get(name, &err);
            if(err == NOERROR) {
                returnValue.value = varValue;
                returnValue.returned = true;
            }
        }
    }
    else if(this->type == END) {
        
    }
    return returnValue;
}