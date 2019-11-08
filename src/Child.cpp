//
//  Child.cpp
//  Program3
//
//  Created by YouHua Tsao on 10/26/19.
//  Copyright © 2019 YouHua Tsao. All rights reserved.
//

#include "Child.h"

//Conctructor for Child with the information of names and ages
Child::Child(string firstName, string lastName, int age)
{
    this->lastName = lastName;
    this->firstName = firstName;
    this->age = age;
}

//default constructor
Child::Child()
{
    this->lastName = "";
    this->firstName = "";
    this->age = 0;
}

//deconstructor
Child::~Child()
{
    
}

//this operator helps to sort the names by comparing the size of names
bool operator<(const Child &lhs,const Child &rhs)
{
    if(lhs.lastName < rhs.lastName)
        return true;
    else if(lhs.lastName > rhs.lastName)
        return false;
    else if(lhs.firstName < rhs.firstName)
        return true;
    else if(lhs.firstName > rhs.firstName)
        return false;
    else if(lhs.age < rhs.age)
        return true;
    else
        return false;
}

//this operator helps to check if two childs share the same information
bool operator==(const Child &lhs, const Child &rhs)
{
    if(lhs.lastName == rhs.lastName && lhs.firstName == rhs.firstName && lhs.age == rhs.age)
        return true;
    else
        return false;
}


//this operator helps to print out child's information
ostream& operator<<(ostream &outStream, const Child &child)
{
    outStream << child.firstName;
    outStream << child.lastName;
    outStream << child.age;
    return outStream;
}

//this operator helps to take in child's information
ifstream& operator >> (ifstream &in, Child &child)
{
    in >> child.firstName;
    in >> child.lastName;
    in >> child.age;
    return in;
}

//this operator helps to sort the name by comparing the size of name
bool operator>(const Child &lhs, const Child &rhs)
{
    if(lhs.lastName > rhs.lastName)
        return true;
    else if(lhs.lastName < rhs.lastName)
        return false;
    else if(lhs.firstName > rhs.firstName)
        return true;
    else if(lhs.firstName < rhs.firstName)
        return false;
    else if(lhs.age > rhs.age)
        return true;
    else
        return false;
}
