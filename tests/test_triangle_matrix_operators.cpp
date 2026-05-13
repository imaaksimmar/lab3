#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          

TEST(TriangleMatrixOperators, AssignOperatorCopiesValues) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 100;

    TriangleMatrix<int, ArraySequence> m2;
    m2 = m1;

    EXPECT_EQ(m2.GetSize(), 2u)
        << "input: m1(2){100} -> m2 = m1 -> m2.GetSize()"
        << "\nexpected: 2";

    EXPECT_EQ(m2[0][0], 100)
        << "input: m1(2){100} -> m2 = m1 -> m2[0][0]"
        << "\nexpected: 100";
}

TEST(TriangleMatrixOperators, AssignOperatorDeep) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 100;

    TriangleMatrix<int, ArraySequence> m2;
    m2 = m1;
    m1[0][0] = 200;
    EXPECT_EQ(m2[0][0], 100)
        << "input: m1[0][0]=100 -> m2=m1 -> m1[0][0]=200 -> m2[0][0]"
        << "\nexpected: 100 ";
}

TEST(TriangleMatrixOperators, AssignOperatorSelfAssign) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 100;
    m.operator=(m);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){100} -> m=m -> m.GetSize()"
        << "\nexpected: 2 (самоприсваивание не ломает матрицу)";

    EXPECT_EQ(m[0][0], 100)
        << "input: m(2){100} -> m=m -> m[0][0]"
        << "\nexpected: 100 (самоприсваивание не меняет значения)";
}

TEST(TriangleMatrixOperators, AddOperatorResult) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 5; 
    m1[1][0] = 1; 
    m1[1][1] = 2;

    TriangleMatrix<int, ArraySequence> m2(2);
    m2[0][0] = 10; 
    m2[1][0] = 3; 
    m2[1][1] = 4;

    TriangleMatrix<int, ArraySequence> res = m1+m2;
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1{5,1,2} + m2{10,3,4} -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 15)
        << "input: m1{5,1,2} + m2{10,3,4} -> res[0][0]"
        << "\nexpected: 15 (5+10)";
    EXPECT_EQ(res[1][0], 4)
        << "input: m1{5,1,2} + m2{10,3,4} -> res[1][0]"
        << "\nexpected: 4 (1+3)";
    EXPECT_EQ(res[1][1], 6)
        << "input: m1{5,1,2} + m2{10,3,4} -> res[1][1]"
        << "\nexpected: 6 (2+4)";
}

TEST(TriangleMatrixOperators, AddOperatorOperandsUnchanged) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 5;

    TriangleMatrix<int, ArraySequence> m2(2);
    m2[0][0] = 10;

    TriangleMatrix<int, ArraySequence> res = m1 + m2;
    EXPECT_EQ(m1[0][0], 5)
        << "input: m1{5} + m2{10} -> m1[0][0]"
        << "\nexpected: 5 (operator+ не изменяет m1)";
    EXPECT_EQ(m2[0][0], 10)
        << "input: m1{5} + m2{10} -> m2[0][0]"
        << "\nexpected: 10 (operator+ не изменяет m2)";
}


TEST(TriangleMatrixOperators, MultiplyOperatorOriginalUnchanged) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 4; 
    m[1][0] = -2; 
    m[1][1] = 5;

    TriangleMatrix<int, ArraySequence> res = m*3;
    EXPECT_EQ(m[0][0], 4)
        << "input: m{4,-2,5} * 3 -> m[0][0]"
        << "\nexpected: 4 (operator* не изменяет оригинал)";
    EXPECT_EQ(m[1][0], -2)
        << "input: m{4,-2,5} * 3 -> m[1][0]"
        << "\nexpected: -2 (operator* не изменяет оригинал)";
    EXPECT_EQ(m[1][1], 5)
        << "input: m{4,-2,5} * 3 -> m[1][1]"
        << "\nexpected: 5 (operator* не изменяет оригинал)";
}
