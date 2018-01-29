//
//  Interpreter.h
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

extern class SymbolTable* symbolTable;

class Interpreter {
    
public:
    Interpreter();
    ~Interpreter();
    
    void interpret();
};

#endif /* Interpreter_h */
