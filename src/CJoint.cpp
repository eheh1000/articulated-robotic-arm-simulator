#include "CJoint.hpp"

//-------------------CLASSE MERE-------------------------------

// CONSTRUCTEURS

CJoint::CJoint(double qMin_, double qMax_, double q_){
    this->qMin_ = qMin_;
    this->qMax_ = qMax_;
    this->q_ = q_;
}

CJoint::CJoint(){
    q_ = 0.0;
    qMin_ = 0.0;
    qMax_ = 0.0;
}

// DESTRUCTEUR
CJoint::~CJoint(){}

// SETTER
void CJoint::setQ(double q){
    if(this->qMin_ <= q && this->qMax_ >= q){
        this->q_ = q;
    }
    else{
        throw std::out_of_range("q is out of range");
    }
}

// GETTTERS
double CJoint::getq() const{
    return q_;
}
double CJoint::getqMin() const{
    return qMin_;
}
double CJoint::getqMax() const{
    return qMax_;
}


//-------------------CLASSES FILLES----------------------------

// JOINT REVOLUTE
CJointRevolute::CJointRevolute(){
    dx_ = 0.0;
    q_ = 0.0;
    qMin_ = 0.0;
    qMax_ = 0.0;
}

double CJointRevolute::getdx() const{
    return dx_;
}

Mat4 CJointRevolute::getTransform() const{
    double q = getq(); 
    double dx = getdx();
    Mat4 m {{cos(q), -sin(q), 0 , dx},
            {sin(q),  cos(q), 0 ,  0},
            {   0  ,   0    , 1 ,  0},
            {   0  ,   0    , 0 ,  1},
    };
    return m;
}

std::string CJointRevolute::getTypeName() const{
    return "Revolute";
}

std::unique_ptr<CJoint> CJointRevolute::clone() const{
    return std::make_unique<CJointRevolute>(*this);
}

// JOINT PRISMATIC
CJointPrismatic::CJointPrismatic(){
    q_ = 0.0;
    qMin_ = 0.0;
    qMax_ = 0.0;
}

Mat4 CJointPrismatic::getTransform() const{
    double d = getq();
    Mat4 m {{1, 0, 0 , 0},
            {0, 1, 0 , 0},
            {0, 0, 1 , d},
            {0, 0, 0 , 1},
    };
    return m;
}

std::string CJointPrismatic::getTypeName() const{
    return "Prismatic";
}

std::unique_ptr<CJoint> CJointPrismatic::clone() const{
    return std::make_unique<CJointPrismatic>(*this);
}