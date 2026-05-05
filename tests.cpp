#include <gtest/gtest.h>
#include "triangle_matrix.hpp"


TEST(TriangleMatrixConstructors, Constructors) {

    TriangleMatrix<int, ArraySequence> m1;
    EXPECT_EQ(m1.GetSize(), 0u);
    EXPECT_THROW(m1[0][0], IndexOutOfRange);


    TriangleMatrix<double, ArraySequence> m2(2); 
    EXPECT_EQ(m2.GetSize(), 2u);

    m2[0][0] = 1.0;
    m2[1][0] = 2.0;
    m2[1][1] = 3.0;

    TriangleMatrix<double, ArraySequence> m3(m2); 
    EXPECT_EQ(m3.GetSize(), 2u);
    
    for(size_t i=0; i<2; i++) { 
        for(size_t j=0; j<=i; j++) {
            EXPECT_DOUBLE_EQ(m3[i][j], m2[i][j]);
        }
    }

    m2[1][1] = 100.0; 
    EXPECT_DOUBLE_EQ(m3[1][1], 3.0); 
}

TEST(TriangleMatrix, GetSize) {
    TriangleMatrix<int, ArraySequence> m0;
    EXPECT_EQ(m0.GetSize(), 0u);

    TriangleMatrix<int, ArraySequence> m5(5);
    EXPECT_EQ(m5.GetSize(), 5u);

    TriangleMatrix<int, ArraySequence> m100(100);
    EXPECT_EQ(m100.GetSize(), 100u);
}

TEST(TriangleMatrixMath, Add) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 1; 
    m1[1][0] = 2; 
    m1[1][1] = 3;
    
    TriangleMatrix<int, ArraySequence> m2(2);
    m2[0][0] = 10; 
    m2[1][0] = 10;
    m2[1][1] = 10;
    
    m1.Add(m2); 
    EXPECT_EQ(m1[0][0], 11);
    EXPECT_EQ(m1[1][0], 12);
    EXPECT_EQ(m1[1][1], 13);

    TriangleMatrix<int, ArraySequence> m3(3);
    EXPECT_THROW(m1.Add(m3), SizeMismatch);
}

TEST(TriangleMatrixMath, ScalarMultiply) {
    TriangleMatrix<double, ArraySequence> m(2);
    m[0][0] = 1.5; 
    m[1][1] = -2.0;
    
    m.ScalarMultiply(2.0);
    EXPECT_DOUBLE_EQ(m[0][0], 3.0);
    EXPECT_DOUBLE_EQ(m[1][1], -4.0);
}

TEST(TriangleMatrixMath, Norm) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = -5; 
    m[1][0] = 2; 
    m[1][1] = 2;
    EXPECT_EQ(m.Norm(), 5); 

    TriangleMatrix<int, ArraySequence> m_empty;
    EXPECT_EQ(m_empty.Norm(), 0);

    TriangleMatrix<int, ArraySequence> m_zeros(2);
    EXPECT_EQ(m_zeros.Norm(), 0);
}

TEST(TriangleMatrixOperators, AssignOperator) {
    TriangleMatrix<int, ArraySequence> m1(2);
    m1[0][0] = 100;
    TriangleMatrix<int, ArraySequence> m2;
    
    m2 = m1; 
    EXPECT_EQ(m2.GetSize(), 2u);
    EXPECT_EQ(m2[0][0], 100);
    
    m1[0][0] = 200;
    EXPECT_EQ(m2[0][0], 100);

    m2.operator=(m2);
    EXPECT_EQ(m2.GetSize(), 2u);
    EXPECT_EQ(m2[0][0], 100); 
}

TEST(TriangleMatrixOperators, AddOperator) {
    TriangleMatrix<int, ArraySequence> m1(2); 
    m1[0][0] = 5; 
    m1[1][0] = 1; 
    m1[1][1] = 2;

    TriangleMatrix<int, ArraySequence> m2(2); 
    m2[0][0] = 10; 
    m2[1][0] = 3; 
    m2[1][1] = 4;
    
    TriangleMatrix<int, ArraySequence> res = m1 + m2;
    EXPECT_EQ(res.GetSize(), 2u);

    EXPECT_EQ(res[0][0], 15); 
    EXPECT_EQ(res[1][0], 4);  
    EXPECT_EQ(res[1][1], 6);  
    
    EXPECT_EQ(m1[0][0], 5);
    EXPECT_EQ(m2[0][0], 10);
}

TEST(TriangleMatrixOperators, MultiplyOperator) {
    TriangleMatrix<int, ArraySequence> m(2); 
    m[0][0] = 4;
    m[1][0] = -2; 
    m[1][1] = 5;
    
    TriangleMatrix<int, ArraySequence> res = m*3;
    
    EXPECT_EQ(res.GetSize(), 2u);

    EXPECT_EQ(res[0][0], 12);
    EXPECT_EQ(res[1][0], -6); 
    EXPECT_EQ(res[1][1], 15); 
    
    EXPECT_EQ(m[0][0], 4);
    EXPECT_EQ(m[1][0], -2);
    EXPECT_EQ(m[1][1], 5);
}

int MultiplyByTen(int x) { return x*10; }

TEST(TriangleMatrixFunctional, MapFunction) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 3;

    TriangleMatrix<int, ArraySequence> res = m.Map(MultiplyByTen);

    EXPECT_EQ(res.GetSize(), 2u);

    EXPECT_EQ(res[0][0], 10);
    EXPECT_EQ(res[1][0], 20);
    EXPECT_EQ(res[1][1], 30);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][0], 2);
    EXPECT_EQ(m[1][1], 3);
}

int SumReducer(int acc, int val) { return acc+val; }
int MultiplyReducer(int acc, int val) { return acc*val; }

TEST(TriangleMatrixFunctional, ReduceFunction) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 2; 
    m[1][0] = 3; 
    m[1][1] = 4;

    int sum = m.Reduce(SumReducer, 0);
    EXPECT_EQ(sum, 9);

    int product = m.Reduce(MultiplyReducer, 1);
    EXPECT_EQ(product, 24);
}