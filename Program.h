
#include "String.h"

#ifndef _Program_h
#define _Program_h

#define SUPPORTED_RECURSIONS 4096

class Statement;

typedef Statement* StatementPtr;

class Program {
public:
	Statement* statements; // an array of Statement objects
private:
	int capacity;
	int length;
    int _pc;
    
    int returnAddresses[SUPPORTED_RECURSIONS];
    int __return_index;
public:
	Program(void);
	~Program(void);
	int size(void);
	Statement& operator[](int k);
    void insert(Statement &st);
    
    void run();
    
    int run_subroutine(ParseNode* callNode);
};

#endif /* _Program_h */