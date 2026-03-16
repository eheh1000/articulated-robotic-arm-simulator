#include "CBras.hpp"


//méthode
void CBras::addJoint(std::unique_ptr<CJoint> joint){
    bras_.push_back(std::move(joint));
}

Mat4 CBras::ComputeFK(){
    Mat4 m;
    for(int i = 0; i < size(bras_); i ++){
        m = m * bras_[i]->getTransform();
    }
    return m;
}

// getter
int CBras::getNbJoints(){
    return size(bras_);
}

CJoint* CBras::getJoint(size_t joint){
    return bras_[joint].get();
}
