#include <iostream>
#include "../include/CBras.hpp"

int main() {
	CJointRevolute jointRevolute(-3.14, 3.14, 0.5, 0.0);
	CJoint* joint;
	joint = &jointRevolute;
	Mat4 m = joint->getTransform();
	std::cout << m << std::endl;

	CBras bras;
	bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.5, 0.0));
	bras.addJoint(std::make_unique<CJointRevolute>(-M_PI, M_PI, 0.3, 0.3));
	bras.addJoint(std::make_unique<CJointPrismatic>(0.0, 0.5, 0.1));
	std::cout << bras;
}