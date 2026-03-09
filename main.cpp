#include "CJoint.h"


int main (){
    CJoint* joint;
    CJointRevolute pivot;
    joint = &pivot;
    Mat4 mat = joint->getTransform();
    //mat2.pinocchio::SE3::toHomogeneousMatrix();

    std::cout<<mat<<std::endl;


    

    return 0;
}