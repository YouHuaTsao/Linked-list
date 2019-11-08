//
//  Child.hpp
//  Program3
//
//  Created by YouHua Tsao on 10/26/19.
//  Copyright © 2019 YouHua Tsao. All rights reserved.
//

#ifndef Child_hpp
#define Child_hpp

#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class Child
{
    
public:
    Child();
    Child(string firstName, string lastName, int age);
    ~Child();
    
    //this operator defines how to read a Child object from input file stream
    friend ifstream& operator >> (ifstream &in, Child &child);
    
    //this operator helps printing out child value
    friend ostream& operator<<(ostream &outStream, const Child &child);
    
    //this operator checks if one child's value is smaller than another one
    friend bool operator<(const Child &lhs, const Child &rhs);
    
    //this operator checks if one child's value is bigger than another one
    friend bool operator>(const Child &lhs, const Child &rhs);
    
    //this operator checks if one child's value is equal to another one
    friend bool operator==(const Child &lhs, const Child &rhs);
    
    private:
    string firstName;
    string lastName;
    int age;
    
};

#endif /* Child_hpp */
