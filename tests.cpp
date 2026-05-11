#include <gtest/gtest.h>
#include "triangle_matrix.hpp"
#include "immutable_triangle_matrix.hpp"


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


int MultiplyByTen(int x) { return x*10; }

TEST(TriangleMatrixFunctional, MapResult) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 3;

    TriangleMatrix<int, ArraySequence> res = m.Map(MultiplyByTen);
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m{1,2,3}.Map(x*10) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 10)
        << "input: m{1,2,3}.Map(x*10) -> res[0][0]"
        << "\nexpected: 10 (1*10)";
    EXPECT_EQ(res[1][0], 20)
        << "input: m{1,2,3}.Map(x*10) -> res[1][0]"
        << "\nexpected: 20 (2*10)";
    EXPECT_EQ(res[1][1], 30)
        << "input: m{1,2,3}.Map(x*10) -> res[1][1]"
        << "\nexpected: 30 (3*10)";
}

TEST(TriangleMatrixFunctional, MapOriginalUnchanged) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 3;

    m.Map(MultiplyByTen);
    EXPECT_EQ(m[0][0], 1)
        << "input: m{1,2,3}.Map(x*10) -> m[0][0]"
        << "\nexpected: 1 (Map не изменяет оригинал)";
    EXPECT_EQ(m[1][0], 2)
        << "input: m{1,2,3}.Map(x*10) -> m[1][0]"
        << "\nexpected: 2 (Map не изменяет оригинал)";
    EXPECT_EQ(m[1][1], 3)
        << "input: m{1,2,3}.Map(x*10) -> m[1][1]"
        << "\nexpected: 3 (Map не изменяет оригинал)";
}

int SumReducer(int acc, int val) { return acc+val; }

TEST(TriangleMatrixFunctional, ReduceSum) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 2; 
    m[1][0] = 3; 
    m[1][1] = 4;

    int sum = m.Reduce(SumReducer, 0);
    EXPECT_EQ(sum, 9)
        << "input: m{2,3,4}.Reduce(a+b, 0)"
        << "\nexpected: 9 (2+3+4)";
}


bool IsTwoDivided(int x) { return x%2==0; }

TEST(TriangleMatrixFunctional, WhereResult) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 4;

    TriangleMatrix<int, ArraySequence> res = m.Where(IsTwoDivided);
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m{1,2,4}.Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m{1,2,4}.Where(x%2==0) -> res[0][0]"
        << "\nexpected: 0 (1 нечётное -> заменяется на 0)";
    EXPECT_EQ(res[1][0], 2)
        << "input: m{1,2,4}.Where(x%2==0) -> res[1][0]"
        << "\nexpected: 2 (2 чётное -> остаётся)";
    EXPECT_EQ(res[1][1], 4)
        << "input: m{1,2,4}.Where(x%2==0) -> res[1][1]"
        << "\nexpected: 4 (4 чётное -> остаётся)";
}

TEST(TriangleMatrixFunctional, WhereOriginalUnchanged) {
    TriangleMatrix<int, ArraySequence> m(2);
    m[0][0] = 1; 
    m[1][0] = 2; 
    m[1][1] = 4;
    m.Where(IsTwoDivided);

    EXPECT_EQ(m[0][0], 1)
        << "input: m{1,2,4}.Where(x%2==0) -> m[0][0]"
        << "\nexpected: 1 (Where не изменяет оригинал)";
    EXPECT_EQ(m[1][0], 2)
        << "input: m{1,2,4}.Where(x%2==0) -> m[1][0]"
        << "\nexpected: 2 (Where не изменяет оригинал)";
    EXPECT_EQ(m[1][1], 4)
        << "input: m{1,2,4}.Where(x%2==0) -> m[1][1]"
        << "\nexpected: 4 (Where не изменяет оригинал)";
}


TEST(TriangleMatrixExceptions, IndexOutOfRangeRow) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[3][0], IndexOutOfRange)
        << "input: TriangleMatrix m(3) -> m[3][0]"
        << "\nexpected: throw IndexOutOfRange (строка 3 выходит за пределы)";
}

TEST(TriangleMatrixExceptions, IndexOutOfRangeColumn) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[0][3], IndexOutOfRange)
        << "input: TriangleMatrix m(3) -> m[0][3]"
        << "\nexpected: throw IndexOutOfRange (столбец 3 выходит за пределы)";
}

TEST(TriangleMatrixExceptions, IndexOutOfRangeMessage) {
    TriangleMatrix<int, ArraySequence> m(3);
    try 
    {
        m[5][0];
        FAIL() << "input: TriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: throw IndexOutOfRange, но исключение не было брошено";
    } 
    catch(const IndexOutOfRange& e) 
    {
        std::string expected = "IndexOutOfRange: requested index 5, BUT actual size is 3";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m(3) -> m[5][0] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: IndexOutOfRange, но брошено другое исключение";
    }
}

TEST(TriangleMatrixExceptions, InvalidArgumentUpperTriangle) {
    TriangleMatrix<int, ArraySequence> m(3);
    EXPECT_THROW(m[0][1], InvalidArgument)

        << "input: TriangleMatrix m(3) -> m[0][1]"
        << "\nexpected: throw InvalidArgument (верхний треугольник)";
    EXPECT_THROW(m[1][2], InvalidArgument)
        << "input: TriangleMatrix m(3) -> m[1][2]"
        << "\nexpected: throw InvalidArgument (верхний треугольник)";
}

TEST(TriangleMatrixExceptions, InvalidArgumentMessage) {
    TriangleMatrix<int, ArraySequence> m(3);
    try 
    {
        m[0][2];
        FAIL() << "input: TriangleMatrix m(3) -> m[0][2]"
               << "\nexpected: throw InvalidArgument, но исключение не было брошено";
    } 
    catch(const InvalidArgument& e) 
    {
        std::string expected = "InvalidArgument: access to upper triangle is forbidden (Row: 0, Column: 2)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m(3) -> m[0][2] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m(3) -> m[0][2]"
               << "\nexpected: InvalidArgument, но брошено другое исключение";
    }
}

TEST(TriangleMatrixExceptions, SizeMismatchAdd) {
    TriangleMatrix<int, ArraySequence> m1(2);
    TriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: TriangleMatrix m1(2) + TriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(TriangleMatrixExceptions, SizeMismatchMessage) {
    TriangleMatrix<int, ArraySequence> m1(2);
    TriangleMatrix<int, ArraySequence> m2(4);
    try 
    {
        m1.Add(m2);
        FAIL() << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
               << "\nexpected: throw SizeMismatch, но исключение не было брошено";
    } 
    catch(const SizeMismatch& e) 
    {
        std::string expected = "SizeMismatch: sizes do not match (2 vs 4)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: TriangleMatrix m1(2).Add(m2(4)) -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    } 
    catch(...) 
    {
        FAIL() << "input: TriangleMatrix m1(2).Add(TriangleMatrix m2(4))"
               << "\nexpected: SizeMismatch, но брошено другое исключение";
    }
}



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


TEST(ImmutableTriangleMatrix, GetSizeZero) {
    ImmutableTriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.GetSize(), 0u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m -> m.GetSize()"
        << "\nexpected: 0";
}

TEST(ImmutableTriangleMatrix, GetSizeValue) {
    ImmutableTriangleMatrix<int, ArraySequence> m(5);

    EXPECT_EQ(m.GetSize(), 5u)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(5) -> m.GetSize()"
        << "\nexpected: 5";
}


TEST(ImmutableTriangleMatrixImmutability, AddReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1.Add(m2);

    EXPECT_EQ(m1.GetSize(), 2u)
        << "input: m1(2).Add(m2(2)) -> m1.GetSize()"
        << "\nexpected: 2 (Add не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2).Add(m2(2)) -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixImmutability, ScalarMultiplyReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);
    ImmutableTriangleMatrix<int, ArraySequence> res = m.ScalarMultiply(5);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).ScalarMultiply(5) -> m.GetSize()"
        << "\nexpected: 2 (ScalarMultiply не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).ScalarMultiply(5) -> res.GetSize()"
        << "\nexpected: 2";
}

static bool isEvenImmut(int x) { return x%2 == 0; }
static int doubleItImmut(int x) { return x*2; }

TEST(ImmutableTriangleMatrixImmutability, WhereReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Where(isEvenImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).Where(x%2==0) -> m.GetSize()"
        << "\nexpected: 2 (Where не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixImmutability, MapReturnsNewMatrix) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Map(doubleItImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2).Map(x*2) -> m.GetSize()"
        << "\nexpected: 2 (Map не изменяет исходную матрицу)";
    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2).Map(x*2) -> res.GetSize()"
        << "\nexpected: 2";
}


TEST(ImmutableTriangleMatrixMath, AddResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1.Add(m2);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2){0,0,0}.Add(m2(2){0,0,0}) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m1(2){0,0,0}.Add(m2(2){0,0,0}) -> res[0][0]"
        << "\nexpected: 0 (0+0)";
}

TEST(ImmutableTriangleMatrixMath, AddSizeMismatch) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixMath, ScalarMultiplyResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);
    ImmutableTriangleMatrix<int, ArraySequence> res = m.ScalarMultiply(5);

    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.ScalarMultiply(5) -> res[0][0]"
        << "\nexpected: 0 (0*5)";
    EXPECT_EQ(res[1][1], 0)
        << "input: m(2){0,0,0}.ScalarMultiply(5) -> res[1][1]"
        << "\nexpected: 0 (0*5)";
}

TEST(ImmutableTriangleMatrixMath, NormEmpty) {
    ImmutableTriangleMatrix<int, ArraySequence> m;

    EXPECT_EQ(m.Norm(), 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m -> m.Norm()"
        << "\nexpected: 0 (пустая матрица)";
}

TEST(ImmutableTriangleMatrixMath, NormZeros) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_EQ(m.Norm(), 0)
        << "input: ImmutableTriangleMatrix<int, ArraySequence> m(3) -> m.Norm()"
        << "\nexpected: 0 (матрица нулевая)";
}



TEST(ImmutableTriangleMatrixOperators, AddOperatorResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1+m2;

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m1(2){0} + m2(2){0} -> res.GetSize()"
        << "\nexpected: 2";
}

TEST(ImmutableTriangleMatrixOperators, AddOperatorOperandsUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m1+m2;

    EXPECT_EQ(m1.GetSize(), 2u)
        << "input: m1(2) + m2(2) -> m1.GetSize()"
        << "\nexpected: 2 (operator+ не изменяет m1)";
    EXPECT_EQ(m2.GetSize(), 2u)
        << "input: m1(2) + m2(2) -> m2.GetSize()"
        << "\nexpected: 2 (operator+ не изменяет m2)";
}

TEST(ImmutableTriangleMatrixOperators, AddOperatorSizeMismatch) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2) + ImmutableTriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixOperators, MultiplyOperatorResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m*3;

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0} *3 -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0} *3 -> res[0][0]"
        << "\nexpected: 0 (0*3)";
}

TEST(ImmutableTriangleMatrixOperators, MultiplyOperatorOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m*3;

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0} * 3 -> m.GetSize()"
        << "\nexpected: 2 (operator* не изменяет оригинал)";
}

TEST(ImmutableTriangleMatrixOperators, AssignOperatorCopiesValues) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(3);
    ImmutableTriangleMatrix<int, ArraySequence> m2;

    m2 = m1;

    EXPECT_EQ(m2.GetSize(), 3u)
        << "input: m1(3) -> m2 = m1 -> m2.GetSize()"
        << "\nexpected: 3";
}

TEST(ImmutableTriangleMatrixOperators, AssignOperatorSelfAssign) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.operator=(m);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2) -> m=m -> m.GetSize()"
        << "\nexpected: 2 (самоприсваивание не ломает матрицу)";
}


static int immutMultiplyByTen(int x) { return x*10; }

TEST(ImmutableTriangleMatrixFunctional, MapResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Map(immutMultiplyByTen);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0,0,0}.Map(x*10) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.Map(x*10) -> res[0][0]"
        << "\nexpected: 0 (0*10)";
}

TEST(ImmutableTriangleMatrixFunctional, MapOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.Map(immutMultiplyByTen);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0}.Map(x*10) -> m.GetSize()"
        << "\nexpected: 2 (Map не изменяет оригинал)";
    EXPECT_EQ(m[0][0], 0)
        << "input: m(2){0}.Map(x*10) -> m[0][0]"
        << "\nexpected: 0 (Map не изменяет оригинал)";
}

static int immutSumReducer(int acc, int val) { return acc+val; }

TEST(ImmutableTriangleMatrixFunctional, ReduceSum) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    int sum = m.Reduce(immutSumReducer, 0);

    EXPECT_EQ(sum, 0)
        << "input: m(2){0,0,0}.Reduce(a+b, 0)"
        << "\nexpected: 0 (0+0+0)";
}

TEST(ImmutableTriangleMatrixFunctional, WhereResult) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    ImmutableTriangleMatrix<int, ArraySequence> res = m.Where(isEvenImmut);

    EXPECT_EQ(res.GetSize(), 2u)
        << "input: m(2){0,0,0}.Where(x%2==0) -> res.GetSize()"
        << "\nexpected: 2";
    EXPECT_EQ(res[0][0], 0)
        << "input: m(2){0,0,0}.Where(x%2==0) -> res[0][0]"
        << "\nexpected: 0 (0 чётное -> остаётся)";
}

TEST(ImmutableTriangleMatrixFunctional, WhereOriginalUnchanged) {
    ImmutableTriangleMatrix<int, ArraySequence> m(2);

    m.Where(isEvenImmut);

    EXPECT_EQ(m.GetSize(), 2u)
        << "input: m(2){0}.Where(x%2==0) -> m.GetSize()"
        << "\nexpected: 2 (Where не изменяет оригинал)";
}

TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeRow) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_THROW(m[3][0], IndexOutOfRange)
        << "input: ImmutableTriangleMatrix m(3) -> m[3][0]"
        << "\nexpected: throw IndexOutOfRange (строка 3 выходит за пределы)";
}

TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeColumn) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_THROW(m[0][3], IndexOutOfRange)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][3]"
        << "\nexpected: throw IndexOutOfRange (столбец 3 выходит за пределы)";
}


TEST(ImmutableTriangleMatrixExceptions, IndexOutOfRangeMessage) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);
    try
    {
        m[5][0];
        FAIL() << "input: ImmutableTriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: throw IndexOutOfRange, но исключение не было брошено";
    }
    catch(const IndexOutOfRange& e)
    {
        std::string expected = "IndexOutOfRange: requested index 5, BUT actual size is 3";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: ImmutableTriangleMatrix m(3) -> m[5][0] -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    }
    catch(...)
    {
        FAIL() << "input: ImmutableTriangleMatrix m(3) -> m[5][0]"
               << "\nexpected: IndexOutOfRange, но брошено другое исключение";
    }
}

TEST(ImmutableTriangleMatrixExceptions, UpperTriangleReturnsDefault) {
    ImmutableTriangleMatrix<int, ArraySequence> m(3);

    EXPECT_EQ(m[0][1], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][1]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
    EXPECT_EQ(m[0][2], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[0][2]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
    EXPECT_EQ(m[1][2], 0)
        << "input: ImmutableTriangleMatrix m(3) -> m[1][2]"
        << "\nexpected: 0 (верхний треугольник возвращает T() )";
}

TEST(ImmutableTriangleMatrixExceptions, SizeMismatchAdd) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
        << "\nexpected: throw SizeMismatch";
    EXPECT_THROW(m1+m2, SizeMismatch)
        << "input: ImmutableTriangleMatrix m1(2) + ImmutableTriangleMatrix m2(4)"
        << "\nexpected: throw SizeMismatch";
}

TEST(ImmutableTriangleMatrixExceptions, SizeMismatchMessage) {
    ImmutableTriangleMatrix<int, ArraySequence> m1(2);
    ImmutableTriangleMatrix<int, ArraySequence> m2(4);
    try
    {
        m1.Add(m2);
        FAIL() << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
               << "\nexpected: throw SizeMismatch, но исключение не было брошено";
    }
    catch(const SizeMismatch& e)
    {
        std::string expected = "SizeMismatch: sizes do not match (2 vs 4)";
        EXPECT_EQ(std::string(e.what()), expected)
            << "input: ImmutableTriangleMatrix m1(2).Add(m2(4)) -> e.what()"
            << "\nexpected: \"" << expected << "\"";
    }
    catch(...)
    {
        FAIL() << "input: ImmutableTriangleMatrix m1(2).Add(ImmutableTriangleMatrix m2(4))"
               << "\nexpected: SizeMismatch, но брошено другое исключение";
    }
}


TEST(ImmutableTriangleMatrixListSequence, ConstructorWithSize) {
    ImmutableTriangleMatrix<int, ListSequence> m(3);

    EXPECT_EQ(m.GetSize(), 3u)
        << "input: ImmutableTriangleMatrix<int, ListSequence> m(3) -> m.GetSize()"
        << "\nexpected: 3";
}

TEST(ImmutableTriangleMatrixListSequence, AddSizeMismatch) {
    ImmutableTriangleMatrix<int, ListSequence> m1(2);
    ImmutableTriangleMatrix<int, ListSequence> m2(3);

    EXPECT_THROW(m1.Add(m2), SizeMismatch)
        << "input: ImmutableTriangleMatrix<ListSequence> m1(2).Add(m2(3))"
        << "\nexpected: throw SizeMismatch";
}
