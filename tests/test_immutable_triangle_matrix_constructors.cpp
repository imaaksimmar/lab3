#include <gtest/gtest.h>
#include "../triangle_matrix.hpp"          
#include "../immutable_triangle_matrix.hpp"


TEST(ImmutableTriangleMatrixConstructors, DefaultConstructor) {
    ImmutableTriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.GetSize(), 0u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m -> m.GetSize()"
        << "\nexpected: 0";
}

TEST(ImmutableTriangleMatrixConstructors, ConstructorWithSize) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_EQ(m.GetSize(), 3u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(3) -> m.GetSize()"
        << "\nexpected: 3";
}

TEST(ImmutableTriangleMatrixConstructors, ConstructorInitializesWithZeros) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    EXPECT_EQ(m[0][0], 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(2) -> m[0][0]"
        << "\nexpected: 0 (конструктор инициализирует нулями)";
    EXPECT_EQ(m[1][0], 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(2) -> m[1][0]"
        << "\nexpected: 0 (конструктор инициализирует нулями)";
    EXPECT_EQ(m[1][1], 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(2) -> m[1][1]"
        << "\nexpected: 0 (конструктор инициализирует нулями)";
}

TEST(ImmutableTriangleMatrixConstructors, CopyConstructorSize) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(3);
    ImmutableTriangleMatrix<int, ArraySequence> m2(m1);

    EXPECT_EQ(m2.GetSize(), 3u)
        << "input: ImmutableTriangleMatrix m1(3) -> ImmutableTriangleMatrix m2(m1) -> m2.GetSize()"
        << "\nexpected: 3";
}

TEST(ImmutableTriangleMatrixConstructors, CopyConstructorDeep) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(m1);

    EXPECT_EQ(m1.GetSize(), m2.GetSize())
        << "input: ImmutableTriangleMatrix m1(2) -> m2(m1) -> размеры"
        << "\nexpected: размеры совпадают";
}
