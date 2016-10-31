#include <stdio.h>

#include "gtest/gtest.h"

int main(int argc, char **argv) {
	printf("Running main() from main.cpp\n");
	printf("Compiled on %s at %s\n", __DATE__, __TIME__);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}