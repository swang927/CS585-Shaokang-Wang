// stack_guard_test.cpp

#include "stack_guard_test.h"

using namespace sgdm;

// Test operator-> function
class StackGuard_Test_arrow_operator : public ::testing::Test {
  protected:
    DefaultAllocator<char>* letmetry = new DefaultAllocator<char>();
    char* sentence;
    char* other = (char*)"Hello";
    char a; 
    StackGuard_Test_arrow_operator() {
       sentence = letmetry->get(6);
       for (int i = 0; i < 6; i++) {
		letmetry->construct(&sentence[i], other[i]);
	}
    };
    virtual ~StackGuard_Test_arrow_operator(){
    };
};

TEST_F(StackGuard_Test_arrow_operator, point) {
    StackGuard<char> config(sentence);
    a = config.operator->()[1];
    EXPECT_EQ('e',a);
    a = config.operator->()[0];
    EXPECT_EQ('H',a);
    a = config.operator->()[5];
    EXPECT_EQ('\0',a);
};


