//
//  List342.h
//  Program3
//
//  Created by YouHua Tsao on 10/26/19.
//  Copyright © 2019 YouHua Tsao. All rights reserved.
//

#ifndef List342_h
#define List342_h
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Child.h"
using namespace std;


template<class T> class List342;
template<class T> struct Node;
class Child;


template<class T>

struct Node{
    T *item;
    Node *next;
    
    Node(T nodeItem)
    {
        item = new T();
        *item = nodeItem;
        next = NULL;
    }
    
    ~Node()
    {
        if(item != NULL)
        {
            delete item;
            item = NULL;
            next = NULL;
        }
    }
};

template<class T>
class List342
{
    public:
    
    //default constructor
    List342()
    {
        head = NULL;
    }
    
    //copy constructor
    List342(const List342<T> &copy)
    {
       
        Node<T> *p = copy.head;
        if(p == NULL) {
            head = NULL;
            return;
        }
        Node<T> *l = new Node<T>(*(p->item));
        this->head = l;
        p = p->next;
        while(p != NULL)
        {
            l->next = new Node<T>(*(p->item));
            l = l->next;
            p = p->next;
        }
    }
    
    //deconstructor
    ~List342()
    {
        if(head!=NULL)
        {
        DeleteList();
        head = NULL;
        }
    }
    
    //this function build a list from the content of a file
    bool BuildList(string fileName)
    {
        ifstream inFile;
           inFile.open(fileName);
           while(!inFile.eof()){
               T localItem;
               inFile >> localItem;
               Insert(&localItem);
            }
               
            return head!=NULL;
    }
    
    //this function allow user to insert a value to the list
    bool Insert(T *obj)
    {
        Node<T> *prev = NULL;
        Node<T> *p = head;
        if(p == NULL){
            p = new Node<T>(*obj);
            head = p;
            return true;
        }
        while(p!=NULL && p-> item != NULL && *obj > *(p->item))
        {
            prev = p;
            p = p->next;
        }
        
        if(p!=NULL && p-> item != NULL &&*obj == *(p->item))
        {
            return false;
        }
        
        if(p == NULL)
        {
            Node<T> *insert = new Node<T>(*obj);
            prev->next = insert;
            return true;
        }
        
        if(prev == NULL)
        {
            Node<T> *insert = new Node<T>(*obj);
            insert->next = head;
            head = insert;
            return true;
        }
        
        Node<T> *current = new Node<T>(*obj);
        current->next = p;
        prev->next = current;
        return true;
        
    }
        
    //This function allows user to remove one value from the list
    bool Remove(T target, T &result)
    {
        Node<T> *p = head;
        Node<T> *prev;
        if(head != NULL)
        {
            prev = p;
            p = p->next;
        }
        else
        {
            return false;
        }
        
        if(*(prev->item) == target)
        {
            result = *(prev->item);
            delete prev;
            head = p;
        }
        
        while(p != NULL)
        {
            if(*(p->item) == target)
            {
                result = *(p->item);
                prev->next = p->next;
                delete p;
                return true;
            }
            else
            {
                p = p->next;
                prev = prev->next;
            }
        }
        return false;
    }
    
    //this funciton allows user to check if a value is in the list or not
    bool Peek(T target, T &result) const
    {
        Node<T> *p = head;
        while(p != NULL) {
            
            if(target == *(p->item))
            {
                result = *(p->item);
                return true;
            }
            
            if(target < *(p->item))
            {
                return false;
            }
            
            p = p->next;
        
        
        }
        
        return false;
        
    }
    
    //check if the list is empty
    bool isEmpty() const
    {
        if(head == NULL)
            return true;
        else
            return false;
    }
    
    //delete the lsit
    void DeleteList()
    {
        Node<T> *p = head;
        while(p != NULL)
        {
            Node<T> *temp = p->next;
            delete p;
            p = temp;
        }
        head = NULL;
    }
    
    //This function allows user to merge two lists; memory allocation is not needed for both lhs and rhs. rhs will set to be empty list by this function.
    bool Merge(List342 &list1)
    {
        List342 ret;
        mergeWithMemOption(*this, list1, ret, "RHS_MEM_ALLOC");
        return true;
    }
    
    //Add two list together; memory allocation is needed for both lhs and rhs. Both of lhs and rhs will not be modified by this function.
    friend List342 operator+(const List342 lhs, const List342 rhs)
    {
        List342 ret;
        mergeWithMemOption(lhs, rhs, ret, "LHS_RHS_MEM_ALLOC");
        return ret;
    }
    
    //Add two list together; memory allocation is needed only for rhs.  rhs will not be modified; only lhs is modified.
    friend List342& operator+=(List342 &lhs, List342 &rhs)
    {
        List342 ret;
        mergeWithMemOption(lhs, rhs, ret, "RHS_MEM_ALLOC");
        return lhs;
    }
    
    
    static void mergeWithMemOption(List342 &lhs, List342 &rhs, List342 &ret, string memType)
    {
        Node<T> *p = lhs.head;
        Node<T> *q = rhs.head;
        Node<T> *newHead = NULL;
        Node<T> *t = NULL;
        
        while(p != NULL && q != NULL)
        {
            Node<T> **nodePointerAddr = NULL;
            if(newHead == NULL)
            {
                nodePointerAddr = &(newHead);
            }
            else {
                nodePointerAddr = &(t->next);
            }
            
            if(*(p->item)<*(q->item))
            {
                if(memType == "LHS_RHS_MEM_ALLOC") {
                    *nodePointerAddr = new Node<T>(*(p->item));
                }
                else{
                    *nodePointerAddr = p;
                }
                t = *nodePointerAddr;
                p = p->next;
            }
            else if(*(p->item)>*(q->item))
            {
                if(memType == "LHS_RHS_MEM_ALLOC" || memType == "RHS_MEM_ALLOC"){
                    *nodePointerAddr = new Node<T>(*(q->item));
                }
                else{
                    *nodePointerAddr = q;
                }
                t = *nodePointerAddr;
                q = q->next;
            }
            
            //If there are two same value in the lists
            else
            {
                if(memType == "LHS_RHS_MEM_ALLOC"){
                    *nodePointerAddr = new Node<T>(*(p->item));
                }
                else{
                    *nodePointerAddr = p;
                }
                t = *nodePointerAddr;
                p = p->next;
                q = q->next;
            }
        }
        
        if(p == NULL)
        {
            p = q;
        }
        
        if (memType == "LHS_RHS_MEM_ALLOC" ||
            (memType == "RHS_MEM_ALLOC" && q!=NULL))
        {
            while(p != NULL)
            {
                t->next = new Node<T>(*(p->item));
                t = t->next;
                p = p->next;
            }
        }
        else
        {
            t->next = p;
        }
        
        if(memType == "LHS_RHS_MEM_ALLOC") {
            ret.head = newHead;
        }
    }
    
    //Check if two lists are not equal to each other
    friend bool operator!=(List342 &list1, List342 &list2)
    {
        return !(list1==list2);
    }
    
    //Check if two lists are equal to each other
    friend bool operator==(List342 &list1, List342 &list2)
    {
        Node<T> *p = list1.head;
        Node<T> *q = list2.head;
        while(p != NULL && q != NULL)
        {
            if(*(p->item) == *(q->item))
            {
                p = p->next;
                q = q->next;
            }
            else
                return false;
        }
        return p == q;
        
    }
    
    //This operator makes one list equal to another list
    void operator=(const List342<T> &list)
    {
        List342<T> *newList = new List342<T>(list);
        head = newList->head;
        newList->head = NULL;
        delete newList;
    }
    
    //output operator <<
    friend ostream& operator<<(ostream &outStream, const List342 &list)
    {
        Node<T> *p = list.head;
        while(p != NULL)
        {
            Node<T> *temp = p->next;
            outStream << *(p->item);
            p = temp;
        }
        return outStream;
    }
    
    //input operator >>
    friend ifstream& operator >> (ifstream &in, Node<T> &head){
        in >> head.item;;
        head.next = NULL;
        return in;
    }
    
    private:
    Node<T> *head;
};

#include "List342.cpp"
#endif /* List342_h */
