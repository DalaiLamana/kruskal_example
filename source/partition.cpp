#include "partition.h"

//Constructors

Partition::Partition(){
    this->_elems = vector<EqClass>();
}

Partition::Partition(int size){
    this->_elems = vector<EqClass>();
    this->_elems.resize(size);
}

//Destructor

Partition::~Partition() {
    this->_elems.clear();
}


//Functions


void Partition::join(EqClass &c1, EqClass &c2){
    if (c1._height > c2._height)
        //this redundance is just in case c1 and c2 are temporary
        c2._parent->_parent = c1._parent->_parent; 
    else{
        c1._parent = c2._parent;
        if (c1._height == c2._height)
            c2._height++;   
    }
}

void Partition::merge(int i, int j){
    EqClass *c1 = auxFind(&(this->_elems.at(i)));
    EqClass *c2 = auxFind(&(this->_elems.at(j)));
    join(*c1->_parent, *c2->_parent);
}


EqClass Partition::find(int data){
   EqClass *sol = auxFind(&(this->_elems.at(data)));
   return *sol;

}

EqClass* Partition::auxFind(EqClass *eq){
    if (eq->_parent == eq)
        return eq;
    else{
        eq->_parent = auxFind(eq->_parent);
        return eq->_parent;
    }

}