#include <iostream>
#include "test.h"

int main(int argc, char **argv) {
    std::cout << "Testing...";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

