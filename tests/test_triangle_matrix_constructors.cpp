#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          

TEST(TriangleMatrixConstructors, DefaultConstructor) {
    TriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.GetSize(), 0u)
        << "input: TriangleMatrix<int, ArraySequence> m -> m.GetSize()"
        << "\nexpected: 0";
    EXPECT_THROW(m[0][0], IndexOutOfRange)
        << "input: TriangleMatrix<int, ArraySequence> m -> m[0][0]"
        << "\nexpected: throw IndexOutOfRange";
}

TEST(TriangleMatrixConstructors, ConstructorWithSize) {
    TriangleMatrix<double, ArraySequence> m(2);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: TriangleMatrix<double, ArraySequence> m(2) -> m.GetSize()"
        << "\nexpected: 2";
}

TEST(TriangleMatrixConstructors, CopyConstructorSize) {
    TriangleMatrix<double, ArraySequence> m2(2);
    m2[0][0] = 1.0; 
    m2[1][0] = 2.0; 
    m2[1][1] = 3.0;

    TriangleMatrix<double, ArraySequence> m3(m2);
    EXPECT_EQ(m3.GetSize(), 2u)
        << "input: TriangleMatrix m2(2){1.0,2.0,3.0} -> TriangleMatrix m3(m2) -> m3.GetSize()"
        << "\nexpected: 2";
}

TEST(TriangleMatrixConstructors, CopyConstructorValues) {
    TriangleMatrix<double, ArraySequence> m2(2);
    m2[0][0] = 1.0; 
    m2[1][0] = 2.0; 
    m2[1][1] = 3.0;

    TriangleMatrix<double, ArraySequence> m3(m2);
    for(size_t i=0; i<2; i++) {
        for(size_t j=0; j<=i; j++) {
            EXPECT_DOUBLE_EQ(m3[i][j], m2[i][j])
                << "input: TriangleMatrix m2(2){1.0,2.0,3.0} -> m3(m2) -> m3[" << i << "][" << j << "]"
                << "\nexpected: " << m2[i][j];
        }
    }
}

TEST(TriangleMatrixConstructors, CopyConstructorDeep) {
    TriangleMatrix<double, ArraySequence> m2(2);
    m2[1][1] = 3.0;

    TriangleMatrix<double, ArraySequence> m3(m2);
    m2[1][1] = 100.0;

    EXPECT_DOUBLE_EQ(m3[1][1], 3.0)
        << "input: m2[1][1]=3.0 -> m3(m2) -> m2[1][1]=100.0 -> m3[1][1]"
        << "\nexpected: 3.0 ";
}