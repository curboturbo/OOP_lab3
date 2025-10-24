#include <gtest/gtest.h>
#include "../src/f.h" 


TEST(TriangleTest, AssignmentOperator) {
    Triangle a({0,0,4,0,0,3});
    Triangle b;
    b = a;
    EXPECT_TRUE(a == b);
}

TEST(TriangleTest, MoveConstructor) {
    Triangle a({0,0,4,0,0,3});
    Triangle b(std::move(a));
    EXPECT_NEAR(b.area_calculate(), 6.0, 1e-6);
}

TEST(TriangleTest, ConversionToDouble) {
    Triangle t({0,0,4,0,0,3});
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 6.0, 1e-6);
}


TEST(SquareTest, CenterCalculation) {
    Square s({0,0,0,2,2,2,2,0});
    auto c = s.center();
    EXPECT_NEAR(c[0], 1.0, 1e-6);
    EXPECT_NEAR(c[1], 1.0, 1e-6);
}

TEST(SquareTest, EqualityOperator) {
    Square a({0,0,0,2,2,2,2,0});
    Square b({0,0,0,2,2,2,2,0});
    EXPECT_TRUE(a == b);
}

TEST(SquareTest, AssignmentOperator) {
    Square a({0,0,0,2,2,2,2,0});
    Square b;
    b = a;
    EXPECT_TRUE(a == b);
}

TEST(SquareTest, MoveConstructor) {
    Square a({0,0,0,2,2,2,2,0});
    Square b(std::move(a));
    EXPECT_NEAR(b.area_calculate(), 4.0, 1e-6);
}

TEST(SquareTest, ConversionToDouble) {
    Square s({0,0,0,2,2,2,2,0});
    double area = static_cast<double>(s);
    EXPECT_NEAR(area, 4.0, 1e-6);
}


TEST(OctagonTest, CenterCalculation) {
    Octagon o({0,0,1,0,2,1,2,2,1,3,0,3,-1,2,-1,1});
    auto c = o.center();
    EXPECT_NEAR(c[0], 0.5, 1e-6);  
    EXPECT_NEAR(c[1], 1.5, 1e-6);
}

TEST(OctagonTest, AssignmentOperator) {
    Octagon a({0,0,1,0,2,1,2,2,1,3,0,3,-1,2,-1,1});
    Octagon b;
    b = a;
    EXPECT_TRUE(a == b);
}

TEST(OctagonTest, MoveConstructor) {
    Octagon a({0,0,1,0,2,1,2,2,1,3,0,3,-1,2,-1,1});
    Octagon b(std::move(a));
    EXPECT_GT(b.area_calculate(), 0.0);
}

TEST(OctagonTest, ConversionToDouble) {
    Octagon o({0,0,1,0,2,1,2,2,1,3,0,3,-1,2,-1,1});
    double area = static_cast<double>(o);
    EXPECT_GT(area, 0.0);
}


TEST(ArrayTest, AddDeleteMultipleFigures) {
    Array arr;
    Triangle t({0,0,4,0,0,3});  
    Square s({0,0,0,2,2,2,2,0}); 
    Octagon o({0,0,1,0,2,1,2,2,1,3,0,3,-1,2,-1,1}); 
    arr.add_figure(&t);
    arr.add_figure(&s);
    arr.add_figure(&o);
    double total = t.area_calculate() + s.area_calculate() + o.area_calculate();
    EXPECT_NEAR(arr.summary_square(), total, 1e-6);

    arr.delete_by_index(1); 
    total -= s.area_calculate();
    EXPECT_NEAR(arr.summary_square(), total, 1e-6);
}

TEST(ArrayTest, CopyConstructor) {
    Array arr1;
    Triangle t({0,0,4,0,0,3});
    arr1.add_figure(&t);
    Array arr2(arr1);
    EXPECT_NEAR(arr2.summary_square(), 6.0, 1e-6);
}

TEST(ArrayTest, MoveConstructor) {
    Array arr1;
    Triangle t({0,0,4,0,0,3});
    arr1.add_figure(&t);
    Array arr2(std::move(arr1));
    EXPECT_NEAR(arr2.summary_square(), 6.0, 1e-6);
    EXPECT_EQ(arr1.summary_square(), 0.0);
}
