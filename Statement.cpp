//
//  Statement.cpp
//  pj10
//
//  Created by Eric Liang on 12/1/15.
//  Copyright © 2015 Apprilo. All rights reserved.
//

#include "Statement.h"
typedef ParseNode* ParseNodePtr;
Statement::Statement() {
    root = nullptr;
}

void destory_tree(ParseNode * node) {
    if(node!= nullptr){
        destory_tree(node->left);
        destory_tree(node->right);
        delete node;
    }
}

ParseNode* copyRec(ParseNode* that) {
    ParseNode* inserted = nullptr;
    if(that!=nullptr) {
        inserted = new ParseNode();
        inserted->value = that->value;
        inserted->type = that->type;
        inserted->name = String(that->name);
        inserted->binaryNode = that->binaryNode;
        inserted->endNode = that->endNode;
        inserted->left = copyRec(that->left);
        inserted->right = copyRec(that->right);
        
    } else return nullptr;
    return inserted;
}

Statement::Statement(const Statement &that) {
    this->root = copyRec(that.root);
}

Statement::~Statement() {
    destory_tree(root);
}

bool insert_recursive(ParseNodePtr &rootNode, ParseNode newNode) {
    ParseNode* inserted = new ParseNode();
    inserted->value = newNode.value;
    inserted->type = newNode.type;
    inserted->name = newNode.name;
    inserted->binaryNode = newNode.binaryNode;
    inserted->endNode = newNode.endNode;
    
    
    if(rootNode == nullptr) {
        rootNode = inserted;
        return true;
    }
    if(rootNode->endNode) {
        return false;
    }
    if(rootNode->left == nullptr) {
        rootNode->left = inserted;
        return true;
    }
    if(rootNode->left->endNode && rootNode->right==nullptr && rootNode->binaryNode) {
        rootNode->right = inserted;
        return true;
    }
    if(rootNode->left->endNode && !rootNode->binaryNode) {
        return false;
    }
    if(rootNode->left->endNode && rootNode->right->endNode) {
        return false;
    }
    
    if(rootNode->left->endNode && rootNode->right!=nullptr) {
        return insert_recursive(rootNode->right, newNode);
    }
   
    if(!insert_recursive(rootNode->left, newNode)) {
        return insert_recursive(rootNode->right, newNode);
    }
    return true;
}

void Statement::insert(ParseNode node) {
    
    if(!insert_recursive(this->root, node)) {
        //printf("\n error inserting\n");
    }
}

ParseNode::ReturnData Statement::execute() {
    return root->evaluate();
}

String Statement::name() {
    if(root!= nullptr) {
        return root->name;
    }
    return nullptr;
}
String Statement::leftName() {
    if (root) {
        if(root->left) {
            return root->left->name;
        }
    }
    return nullptr;
}
