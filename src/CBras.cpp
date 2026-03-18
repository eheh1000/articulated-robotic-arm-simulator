#include "../include/CBras.hpp"

void CBras::addJoint(std::unique_ptr<CJoint> joint){
    joints_.push_back(std::move(joint));
}

Mat4 CBras::ComputeFK() const{
    Mat4 m{{1, 0, 0 , 0},
           {0, 1, 0 , 0},
           {0, 0, 1 , 0},
           {0, 0, 0 , 1},
    };
    if(size(joints_) == 0){
        return m;
    }
    for(int i = 0; i < size(joints_); i ++){
        m = m * joints_[i]->getTransform();
    }
    return m;
}

int CBras::getNbJoints () const{
    return size(joints_);
}

const CJoint& CBras::getJoint(size_t i) const{
    if(i <= size(joints_)){
        return *joints_[i];
    }else{
        throw std::out_of_range("joint is out of range");
    }
}

std::ostream& operator<<(std::ostream& flux, const CBras& b){

    const auto& joints_ = b.getjoints_();

    flux << "joints_" << "[" << joints_.size() << " DDL]" << std::endl;

    for (size_t i = 0; i < size(joints_); i++){
        if(joints_[i]->getTypeName() == "Revolute"){
            flux << "[" << i << "] Revolute   q = " << joints_[i]->getq() << " rad bornes=[" 
            << joints_[i]->getqMin() << ", " << joints_[i]->getqMax() << "]" << std::endl;
        }else{
            flux << "[" << i << "] Prismatic  q = " << joints_[i]->getq() << " m   bornes=[" 
            << joints_[i]->getqMin() << ", " << joints_[i]->getqMax() << "]" << std::endl;
        }
    }

    flux << std::endl;
    return flux;
}