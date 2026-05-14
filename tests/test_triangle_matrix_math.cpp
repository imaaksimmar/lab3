#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"   

using namespace exceptions;
using namespace array_sequence;
using namespace list_sequence;
using namespace triangle_matrix;

TEST(TriangleMatrix, GetSizeZero) {
    TriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.GetSize(), 0u)
        << "input: TriangleMatrix<int, ArraySequence> m -> m.GetSize()"
        << "\nexpected: 0";
}

TEST(TriangleMatrix, GetSizeValue) {
    TriangleMatrix<int, ArraySequence> m(5);

    EXPECT_EQ(m.GetSize(), 5u)
        << "input: TriangleMatrix<int, ArraySequence> m(5) -> m.GetSize()"
        << "\nexpected: 5";
}

TEST(TriangleMatrixMath, AddResult) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 1; 
    m1[1][0] = 2; 
    m1[1][1] = 3;

    TriangleMatrix<int, ArraySequence> m2(2);
    m2[0][0] = 10; 
    m2[1][0] = 10; 
    m2[1][1] = 10;

    m1.Add(m2);
    EXPECT_EQ(m1[0][0], 11)
        << "input: m1{1,2,3}.Add(m2{10,10,10}) -> m1[0][0]"
        << "\nexpected: 11 (1+10)";
    EXPECT_EQ(m1[1][0], 12)
        << "input: m1{1,2,3}.Add(m2{10,10,10}) -> m1[1][0]"
        << "\nexpected: 12 (2+10)";
    EXPECT_EQ(m1[1][1], 13)
        << "input: m1{1,2,3}.Add(m2{10,10,10}) -> m1[1][1]"
        << "\nexpected: 13 (3+10)";
}

TEST(TriangleMatrixMath, AddSizeMismatch) {
    TriangleMatrix<int, ArraySequence> m1(2);
    TriangleMatrix<int, ArraySequence> m3(3);

    EXPECT_THROW(m1.Add(m3), SizeMismatch)
        << "input: TriangleMatrix m1(2).Add(TriangleMatrix m3(3))"
        << "\nexpected: throw SizeMismatch";
}

TEST(TriangleMatrixMath, ScalarMultiply) {
    TriangleMatrix<double, ArraySequence> m(2);
    m[0][0] = 1.5; 
    m[1][1] = -2.0;

    m.ScalarMultiply(2.0);
    EXPECT_DOUBLE_EQ(m[0][0], 3.0)
        << "input: m[0][0]=1.5 -> m.ScalarMultiply(2.0) -> m[0][0]"
        << "\nexpected: 3.0 (1.5*2.0)";

    EXPECT_DOUBLE_EQ(m[1][1], -4.0)
        << "input: m[1][1]=-2.0 -> m.ScalarMultiply(2.0) -> m[1][1]"
        << "\nexpected: -4.0 (-2.0*2.0)";
}

TEST(TriangleMatrixMath, NormWithValues) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = -5; 
    m[1][0] = 2; 
    m[1][1] = 2;

    EXPECT_EQ(m.Norm(), 5)
        << "input: m{-5,2,2} -> m.Norm()"
        << "\nexpected: 5 ";
}

TEST(TriangleMatrixMath, NormEmpty) {
    TriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.Norm(), 0)
        << "input: TriangleMatrix<int, ArraySequence> m -> m.Norm()"
        << "\nexpected: 0 (пустая матрица)";
}

TEST(TriangleMatrixMath, NormZeros) {
    TriangleMatrix<int, ArraySequence> m(2);
    EXPECT_EQ(m.Norm(), 0)
        << "input: TriangleMatrix<int, ArraySequence> m(2) -> m.Norm()"
        << "\nexpected: 0 (матрица нулевая)";
}
