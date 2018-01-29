//
//  Statement.h
//  pj10
//
//  Created by Eric Liang on 12/1/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//
#include "ParseNode.h"

#ifndef Statement_h
#define Statement_h

class Statement {
public:
    ParseNode* root;

    Statement();
    Statement(const Statement &that);
    ~Statement();
    
    
    void insert(ParseNode node);
    
    
    ParseNode::ReturnData execute();
    String name();
    String leftName();
};



#endif /* Statement_h */
