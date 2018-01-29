#include <cassert>
#include "Program.h"
#include "Statement.h"
#include "SymbolTable.h"

#define DEFAULT_CAPACITY  1

Program::Program(void) {
	this->capacity = DEFAULT_CAPACITY;
	this->statements = new Statement[this->capacity];
	this->length = 0;
    this->_pc = 0;
    for (int i = 0; i < SUPPORTED_RECURSIONS; i++) {
        this->returnAddresses[i] = -1;
    }
    this->__return_index = -1;
}

Program::~Program(void) {
	delete[] this->statements;
}

int Program::size(void) {
    return this->length;
}
Statement& Program::operator[](int k) {
    assert(k >= 0 && k < this->length);
    return this->statements[k];
}
void Program::insert(Statement &st) {
    if(this->length + 1 > this->capacity) {
        if(this->capacity == 0) {
            this->capacity = 1;
        }
        this->capacity = 2 * this->capacity;
        Statement* newStatementsPt = new Statement[this->capacity];
        
        int i= 0;
        while (i < this->length) {
            newStatementsPt[i] = this->statements[i];
            i++;
        }
        
        this->statements = newStatementsPt;
    }
    
    this->statements[this->length] = st;
    this->length +=1;
}

void Program::run() {
    if(statements == nullptr) {
        return;
    }
    
    if(length == 0 || capacity == 0 ) {
        return;
    }
    
    while (_pc < length){
        String stName = statements[_pc].name();
        
        int current_statement = _pc;
        _pc++;
        ParseNode::ReturnData data = statements[current_statement].execute();
        if(data.returned) {
            if(stName == "do") {
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "do" ){
                        __occurance++;
                    }
                    else if(stName == "od") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                } while(true);
            }
            else if(stName == "od") {
                _pc = _pc - 2;
                if(_pc < 0) {
                    return;
                }
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc--;
                    if(stName == "od" ){
                        __occurance++;
                    }
                    else if(stName == "do") {
                        if(__occurance<=0)  {
                            break;
                        }
                        __occurance--;
                    }
                }while (true);
                _pc = _pc + 1;
            }
            else if (stName == "if"){
                int __occurance = 0;
                do {
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "if"){
                        __occurance++;
                    }
                    else if(stName == "fi" || stName == "else") {
                        if(__occurance <= 0) break;
						if (__occurance > 0 && stName == "fi") {
							__occurance--;
						}
                    }
                } while(true);
            }
            else if(stName == "else"){
                int __occurance = 0;
                do {
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "if"){
                        __occurance++;
                    }
                    else if(stName == "fi") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                    
                } while (true);
            }
            else if(stName == "defun") {
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "defun" ){
                        __occurance++;
                    }
                    else if(stName == "nufed") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                } while(true);
            }
            else if(stName == "return") {
                break;
            }
        }
    }
}

int Program::run_subroutine(ParseNode *callNode) {
    __return_index++;
    if(__return_index >=SUPPORTED_RECURSIONS || __return_index <0) {
        return -1;
    }
    returnAddresses[__return_index] = _pc ;
    
    String subroutineName = "";
    if(callNode && callNode->left) {
        subroutineName = callNode->left->name;
    }
    if(callNode && callNode->right) {
        if (callNode->right->name != "args") {
            return -1;
        }
    }
    //parsing arguments
    int* args = new int[2];
    int numOfArgs = 0;
    ParseNode *startArgs = callNode->right->left;
    if (startArgs != nullptr){
        numOfArgs++;
        args[0] = startArgs->evaluate().value;
    }
    startArgs = callNode->right->right;
    if (startArgs != nullptr){
        numOfArgs++;
        args[1] = startArgs->evaluate().value;
    }
    
    
    
    int i = 0;
    for (i = 0; i < length; i++) {
        if(statements[i].name() == "defun") {
            if(statements[i].leftName() == subroutineName) {
                break;
            }
        }
    }
    _pc = i+1;
    
    ParseNode *startParams = statements[i].root->right->left;
    symbolTable->next();
    if(numOfArgs>=1) {
        symbolTable->add(startParams->name, args[0], nullptr);
    }
    if(numOfArgs>=2) {
        startParams = statements[i].root->right->right;
        symbolTable->add(startParams->name, args[1], nullptr);
    }
    
    
    //go to sub and execute
    int subroutineReturnValue = 0;
    while (statements[_pc].name() != "nufed") {
        String stName = statements[_pc].name();
        int current_statement = _pc;
        _pc++;
        ParseNode::ReturnData data = statements[current_statement].execute();
        if(stName == "return") {
            subroutineReturnValue = data.value;
            break;
        }
        if(data.returned) {
            if(stName == "do") {
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "do" ){
                        __occurance++;
                    }
                    else if(stName == "od") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                } while(true);
            }
            else if(stName == "od") {
                _pc = _pc - 2;
                
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc--;
                    if(stName == "od" ){
                        __occurance++;
                    }
                    else if(stName == "do") {
                        if(__occurance<=0)  {
                            break;
                        }
                        __occurance--;
                    }
                }while (true);
                _pc = _pc + 1;
            }
			else if (stName == "if") {
				int __occurance = 0;
				do {
					stName = statements[_pc].name();
					_pc++;
					if (stName == "if") {
						__occurance++;
					}
					else if (stName == "fi" || stName == "else") {
						if (__occurance <= 0) break;
						if (__occurance > 0 && stName == "fi") {
							__occurance--;
						}
					}
				} while (true);
			}
            else if(stName == "else"){
                int __occurance = 0;
                do {
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "if"){
                        __occurance++;
                    }
                    else if(stName == "fi") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                    
                } while (true);
            }
            else if(stName == "defun") {
                int __occurance = 0;
                do {
                    
                    stName = statements[_pc].name();
                    _pc++;
                    if(stName == "defun" ){
                        __occurance++;
                    }
                    else if(stName == "nufed") {
                        if(__occurance <= 0) break;
                        __occurance--;
                    }
                } while(true);
            }
        }
    }
    
    _pc = returnAddresses[__return_index];
    __return_index--;
    symbolTable->back();
    
    return subroutineReturnValue;
}
 
