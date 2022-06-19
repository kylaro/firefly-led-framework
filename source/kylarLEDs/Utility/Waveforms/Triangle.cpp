#include "Triangle.h"




// Input:  0 -> .5-> 1
// Output: 0 -> 1 -> 0
double Triangle::sample(double index){
    if(index < 0.5){
        return index*2.0;
    }else{
        return 1.0-index;
    }
}
