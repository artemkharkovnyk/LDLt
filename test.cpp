

#include <gtest/gtest.h>


TEST(SquareRootTest, NegativeNos) {
    int a, b;
    a = 2; b =3;
    EXPECT_EQ(a, b);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
