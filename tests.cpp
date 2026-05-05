#include <gtest/gtest.h>
#include "triangle_matrix.hpp"


TEST(TriangleMatrixTest, Constructors) {

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


