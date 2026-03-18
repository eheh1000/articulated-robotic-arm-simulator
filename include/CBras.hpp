#include <vector>
#include <iostream>
#include <memory>
#include "CJoint.hpp"

class CBras{
    private :
        std::vector<std::unique_ptr<CJoint>> joints_;
    public :
        const std::vector<std::unique_ptr<CJoint>>& getjoints_() const {
            return joints_;
        }
        void addJoint(std::unique_ptr<CJoint> joint);
        Mat4 ComputeFK() const;
        int getNbJoints() const;
        const CJoint& getJoint(size_t i) const;
};
    
std::ostream& operator<<(std::ostream &flux, const CBras& b);