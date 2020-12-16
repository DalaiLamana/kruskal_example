#ifndef EQCLASS_H
#define EQCLASS_H
 
#include <iostream>
using namespace std;



class EqClass
{
    public:
    
        //Constructors

        EqClass() :_height(0), _parent(this){
        }
        EqClass(int h) :_height(h), _parent(this) {
        }
        ~EqClass(){
        }

        //It compares their parents, not their roots
        //useful if find or findaux has been used before
        bool equalParent(const EqClass& c) {
            return this->_parent == c._parent;
        }
               
        EqClass *_parent;
        int _height;
};



#endif 