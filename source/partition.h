#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include "eqclass.h"
 
using namespace std;

 
class Partition
{
    public:

        //Constructors

        //Defualt constructor
        Partition();

        //Constructor, creates a partition with a especific size
        Partition(int size);

        //Deestructor
        ~Partition();

        //Mutators

        //union function, it's called merge becouse union is a reserved word
        //Fuses the classes of i and j
        void merge(int i, int j);

        //Same as merge but with EqClass(roots) (ready for temporary variables but permanent changes)
        //Given two roots, it joins them
        void join(EqClass &c1, EqClass &c2);

        //Given key data, it finds the EqClass
        EqClass find(int data);
 
    private:
        //given the EqClass eq, finds its root and reaorder the tree so the 
        //access to the root and join operation are constant (amoritzed analysis)
        EqClass* auxFind(EqClass* eq);
        vector<EqClass> _elems;
};
 
#endif 