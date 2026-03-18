#include <gtest/gtest.h>
#include "../include/CJoint.hpp"
#include <pinocchio/spatial/se3.hpp>
#include <cmath>

TEST(CJointTest, SetQ_OutOfRange) {
    CJointRevolute j(-1.0, 1.0, 0.0, 0.5);

    EXPECT_THROW(j.setQ(2.0), std::out_of_range);
}

TEST(CJointTest, SetQ_Valid) {
    CJointRevolute j(-1.0, 1.0, 0.0, 0.5);

    EXPECT_NO_THROW(j.setQ(0.5));
}

TEST(CJointRevoluteTest, IdentityTransform) {
    CJointRevolute j(-M_PI, M_PI, 0.0, 0.0);

    Eigen::Matrix4d T = j.getTransform();
    Eigen::Matrix4d I = Eigen::Matrix4d::Identity();

    for(int i = 0; i < 4; ++i)
        for(int k = 0; k < 4; ++k)
            EXPECT_NEAR(T(i,k), I(i,k), 1e-10);
}

TEST(CJointPrismaticTest, TranslationZ) {
    CJointPrismatic j(0.0, 2.0, 1.0); 

    Eigen::Matrix4d T = j.getTransform();

    EXPECT_NEAR(T(2,3), 1.0, 1e-10);
}

TEST(CJointRevoluteTest, CompareWithPinocchio) {
    double theta = M_PI / 4.0;
    double dx = 0.5;

    CJointRevolute j(-M_PI, M_PI, theta, dx);
    Eigen::Matrix4d T1 = j.getTransform();

    Eigen::Matrix3d R;
    R << cos(theta), -sin(theta), 0,
         sin(theta),  cos(theta), 0,
         0,           0,          1;

    Eigen::Vector3d t(dx, 0, 0);

    pinocchio::SE3 M(R, t);
    Eigen::Matrix4d T2 = M.toHomogeneousMatrix();

    for(int i = 0; i < 4; ++i)
        for(int k = 0; k < 4; ++k)
            EXPECT_NEAR(T1(i,k), T2(i,k), 1e-10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}