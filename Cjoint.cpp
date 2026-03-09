#include "CJoint.h"
//constructeur par défault
CJoint::CJoint(){
    q_ = 0;
    qMin_ = 0;
    qMax_ = 0;
}
//constructeur paramétrisé
CJoint::CJoint(double q, double qMax, double qMin){
    q_ = q;
    qMin_ = qMin;
    qMax_ = qMax;
}
// Méthodes virtuelles de CJointRevolute
Mat4 CJointRevolute::getTransform() const{

    Mat4 Trev;
    Trev << cos(O), -sin(O), 0, dx,
            sin(O), cos(O), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    return Trev;
}

std::string CJointRevolute::getTypename() const{
    return "CJointRevolute";
}

std::unique_ptr<CJoint> CJointRevolute::clone() const{
    auto copie = std::make_unique<CJointRevolute>();
    copie->q_ = getQ();
    copie->qMin_ = getQMin();
    copie->qMax_ = getQMax();
    copie->O = getO();
    copie->dx = getDx();
    return copie;
}

// Méthodes virtuelles de CJointPrismatique
Mat4 CJointPrismatic::getTransform() const{

    Mat4 Tpris;
    Tpris <<1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, d,
            0, 0, 0, 1;
    return Tpris;
}

std::string CJointPrismatic::getTypename() const{
    return "CJointPrismatic";
}

std::unique_ptr<CJoint> CJointPrismatic::clone() const{
    auto copie = std::make_unique<CJointPrismatic>();
    copie->q_ = getQ();
    copie->qMin_ = getQMin();
    copie->qMax_ = getQMax();
    copie->d = getD();
    return copie;
}
