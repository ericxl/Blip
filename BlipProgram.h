//
//  Project10.h
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#ifndef BlipProgram_h
#define BlipProgram_h

#include "Interpreter.h"
#include "SymbolTable.h"

SymbolTable* symbolTable = nullptr;

void run() {
    Interpreter interpreter = Interpreter();
    interpreter.interpret();
}

#endif /* BlipProgram_h */
