#include <iostream>
#include <Eigen/Dense>
#include <memory>

using Mat4 = Eigen::Matrix4d;

class CJoint
{

protected:
    double q_;
    double qMin_;
    double qMax_;

public:
    CJoint();
    CJoint(double qMin_, double qMax_, double q_);
    virtual ~CJoint();
    virtual Mat4 getTransform() const = 0;
    virtual std::string getTypeName() const = 0;
    virtual std::unique_ptr<CJoint> clone() const = 0;

    void setQ(double q);
    double getq() const;
    double getqMin() const;
    double getqMax() const;
};

class CJointRevolute : public CJoint
{
private :
    double dx_;
public:
    CJointRevolute();
    CJointRevolute(double qMin_, double qMax_, double q_, double dx_) :
                    CJoint(qMin_, qMax_, q_), dx_(dx_){};
    virtual Mat4 getTransform() const override;
    virtual std::string getTypeName() const override;
    virtual std::unique_ptr<CJoint> clone() const override;

    double getdx() const;

};

class CJointPrismatic : public CJoint
{

public:
    CJointPrismatic();
    CJointPrismatic(double qMin_, double qMax_, double q_) :
                    CJoint(qMin_, qMax_, q_){};
    virtual Mat4 getTransform() const override;
    virtual std::string getTypeName() const override;
    virtual std::unique_ptr<CJoint> clone() const override;
};