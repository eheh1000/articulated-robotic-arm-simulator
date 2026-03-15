#include <iostream>
#include "../include/CJoint.hpp"

int main() {
	CJointRevolute jointRevolute(0.0, 0.5, -3.14, 3.14);
	CJoint* joint;
	joint = &jointRevolute;
	Mat4 m = joint->getTransform();
	std::cout << m << std::endl;
}