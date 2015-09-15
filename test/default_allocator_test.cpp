// default_allocator_test.cpp

#include "default_allocator_test.h"

using namespace sgdm;

// Test get function
class DefaultAllocator_Test_get : public ::testing::Test {
  protected:
    DefaultAllocator<int>* a1;
    DefaultAllocator<char>* b1;
    int* ptr11;
    char* ptr12;
    DefaultAllocator_Test_get() {
        a1 = new DefaultAllocator<int>();
        b1 = new DefaultAllocator<char>();
    }
    virtual ~DefaultAllocator_Test_get(){
       delete a1;
       delete b1;
    }
};


TEST_F(DefaultAllocator_Test_get, get_function1) {
    ptr11 = a1->get(5);
    EXPECT_EQ(5, a1->get_count());
    ptr11 = a1->get(3);
    EXPECT_EQ(8, a1->get_count());
}

TEST_F(DefaultAllocator_Test_get, get_function2) {
    ptr12 = b1->get(100);
    EXPECT_EQ(100, b1->get_count());
    ptr12 = b1->get(300);
    EXPECT_EQ(400, b1->get_count());
}

// Test release function
class DefaultAllocator_Test_release : public ::testing::Test {
  protected:
    DefaultAllocator<int>* a2;
    DefaultAllocator<char>* b2;
    int* ptr21;
    char* ptr22;
    DefaultAllocator_Test_release() {
        a2 = new DefaultAllocator<int>();
        b2 = new DefaultAllocator<char>();
        ptr21 = a2->get(10);
        ptr22 = b2->get(400);
    }
    virtual ~DefaultAllocator_Test_release(){
       delete a2;
       delete b2;
    }
};

TEST_F(DefaultAllocator_Test_release, release_function1) { 
    a2->release(ptr21, 5);
    EXPECT_EQ(5, a2->get_count());
}

TEST_F(DefaultAllocator_Test_release, release_function2) {
    b2->release(ptr22, 250);
    EXPECT_EQ(150, b2->get_count());
}

// Test get & release function
class DefaultAllocator_Test_mix : public ::testing::Test {
  protected:
    DefaultAllocator<int>* a3;
    DefaultAllocator<char>* b3;
    int* ptr31;
    char* ptr32;
    DefaultAllocator_Test_mix() {
        a3 = new DefaultAllocator<int>();
        b3 = new DefaultAllocator<char>();
    }
    virtual ~DefaultAllocator_Test_mix(){
       delete a3;
       delete b3;
    }
};
TEST_F(DefaultAllocator_Test_mix, get_release_function1) {
    ptr31 = a3->get(5);
    EXPECT_EQ(5, a3->get_count());
    a3->release(ptr31, 5);
    EXPECT_EQ(0, a3->get_count());
}

TEST_F(DefaultAllocator_Test_mix, get_release_function2) {
    ptr32 = b3->get(500);
    EXPECT_EQ(500, b3->get_count());
    b3->release(ptr32, 500);
    EXPECT_EQ(0, b3->get_count());
}




