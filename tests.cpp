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


