//
//  Project10.h
//  pj10
//
//  Created by Eric Liang on 12/2/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#ifndef Project10_h
#define Project10_h

#include "Interpreter.h"

SymbolTable* symbolTable = nullptr;

void run() {
    Interpreter interpreter = Interpreter();
    interpreter.interpret();
}

#endif /* Project10_h */
