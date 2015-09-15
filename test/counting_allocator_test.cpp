// counting_allocator_test.cpp

#include "counting_allocator_test.h"

using namespace sgdm;

// Test get function
class CountingAllocator_Test_get : public ::testing::Test {
  protected:
    CountingAllocator<int>* a1;
    CountingAllocator<char>* b1;
    int* ptr11;
    char* ptr12;
    CountingAllocator_Test_get() {
        a1 = new CountingAllocator<int>();
        b1 = new CountingAllocator<char>();
    }
    virtual ~CountingAllocator_Test_get(){
       delete a1;
       delete b1;
    }
};


TEST_F(CountingAllocator_Test_get, get_function1) {
    ptr11 = a1->get(5);
    EXPECT_EQ(5, a1->get_count());
    ptr11 = a1->get(3);
    EXPECT_EQ(8, a1->get_count());
};

TEST_F(CountingAllocator_Test_get, get_function2) {
    ptr12 = b1->get(100);
    EXPECT_EQ(100, b1->get_count());
    ptr12 = b1->get(300);
    EXPECT_EQ(400, b1->get_count());
};

// Test release function
class CountingAllocator_Test_release : public ::testing::Test {
  protected:
    CountingAllocator<int>* a2;
    CountingAllocator<char>* b2;
    int* ptr21;
    char* ptr22;
    CountingAllocator_Test_release() {
        a2 = new CountingAllocator<int>();
        b2 = new CountingAllocator<char>();
        ptr21 = a2->get(10);
        ptr22 = b2->get(400);
    };
    virtual ~CountingAllocator_Test_release(){
       delete a2;
       delete b2;
    };
};

TEST_F(CountingAllocator_Test_release, release_function1) { 
    a2->release(ptr21, 5);
    EXPECT_EQ(5, a2->get_count());
};

TEST_F(CountingAllocator_Test_release, release_function2) {
    b2->release(ptr22, 250);
    EXPECT_EQ(150, b2->get_count());
};

// Test get & release function
class CountingAllocator_Test_mix : public ::testing::Test {
  protected:
    CountingAllocator<int>* a3;
    CountingAllocator<char>* b3;
    int* ptr31;
    char* ptr32;
    CountingAllocator_Test_mix() {
        a3 = new CountingAllocator<int>();
        b3 = new CountingAllocator<char>();
    };
    virtual ~CountingAllocator_Test_mix(){
       delete a3;
       delete b3;
    };
};
TEST_F(CountingAllocator_Test_mix, get_release_function1) {
    ptr31 = a3->get(5);
    EXPECT_EQ(5, a3->get_count());
    a3->release(ptr31, 5);
    EXPECT_EQ(0, a3->get_count());
};

TEST_F(CountingAllocator_Test_mix, get_release_function2) {
    ptr32 = b3->get(500);
    EXPECT_EQ(500, b3->get_count());
    b3->release(ptr32, 500);
    EXPECT_EQ(0, b3->get_count());
};

// Test getAllocationCount function
class CountingAllocator_Test_getAllocationCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a41;
    CountingAllocator<int>* a42;
    int* ptr41;
    int* ptr42;
    CountingAllocator_Test_getAllocationCount() {
        a41 = new CountingAllocator<int>();
        a42 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getAllocationCount(){
       delete a41;
    };
};
TEST_F(CountingAllocator_Test_getAllocationCount, getAllocationCount_function1) {
    ptr41 = a41->get(5);
    EXPECT_EQ(1, a41->getAllocationCount());
    ptr41 = a41->get(500);
    EXPECT_EQ(2, a41->getAllocationCount());
};

TEST_F(CountingAllocator_Test_getAllocationCount, getAllocationCount_function2) {
    ptr42 = a42->get(5);
    EXPECT_EQ(1, a42->getAllocationCount());
    a42->release(ptr42, 5);
    EXPECT_EQ(1, a42->getAllocationCount());
};


// Test getReleaseCount function
class CountingAllocator_Test_getReleaseCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a51;
    CountingAllocator<int>* a52;
    int* ptr51;
    int* ptr52;
    CountingAllocator_Test_getReleaseCount() {
        a51 = new CountingAllocator<int>();
        a52 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getReleaseCount(){
       delete a51;
       delete a52;
    };
};
TEST_F(CountingAllocator_Test_getReleaseCount, getReleaseCount_function1) {
    ptr51 = a51->get(5);
    EXPECT_EQ(0, a51->getReleaseCount());
    ptr52 = a51->get(500);
    EXPECT_EQ(0, a51->getReleaseCount());
};

TEST_F(CountingAllocator_Test_getReleaseCount, getReleaseCount_function2) {
    ptr52 = a52->get(5);
    EXPECT_EQ(0, a52->getReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(1, a52->getReleaseCount());
};

TEST_F(CountingAllocator_Test_getReleaseCount, getReleaseCount_function3) {
    ptr52 = a52->get(5);
    EXPECT_EQ(0, a52->getReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(1, a52->getReleaseCount());
    ptr52 = a52->get(5);
    EXPECT_EQ(1, a52->getReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(2, a52->getReleaseCount());
};


// Test getOutstandingCount function
class CountingAllocator_Test_getOutstandingCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a61;
    int* ptr61;
    int* ptr62;
    CountingAllocator_Test_getOutstandingCount() {
        a61 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getOutstandingCount(){
       delete a61;
    };
};

TEST_F(CountingAllocator_Test_getOutstandingCount, getOutstandingCount_function1) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    EXPECT_EQ(2, a61->getAllocationCount());
    EXPECT_EQ(0, a61->getReleaseCount());
    EXPECT_EQ(2, a61->getOutstandingCount());
};

TEST_F(CountingAllocator_Test_getOutstandingCount, getOutstandingCount_function2) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    a61->release(ptr61, 5);
    EXPECT_EQ(2, a61->getAllocationCount());
    EXPECT_EQ(1, a61->getReleaseCount());
    EXPECT_EQ(1, a61->getOutstandingCount());
};

TEST_F(CountingAllocator_Test_getOutstandingCount, getOutstandingCount_function3) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    a61->release(ptr61, 5);
    a61->release(ptr62, 500);
    EXPECT_EQ(2, a61->getAllocationCount());
    EXPECT_EQ(2, a61->getReleaseCount());
    EXPECT_EQ(0, a61->getOutstandingCount());
};

// Test getTotalAllocationCount function
class CountingAllocator_Test_getTotalAllocationCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a41;
    CountingAllocator<int>* a42;
    int* ptr41;
    int* ptr42;
    CountingAllocator_Test_getTotalAllocationCount() {
        a41 = new CountingAllocator<int>();
        a42 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getTotalAllocationCount(){
       delete a41;
    };
};
TEST_F(CountingAllocator_Test_getTotalAllocationCount, getTotalAllocationCount_function1) {
    ptr41 = a41->get(5);
    EXPECT_EQ(5, a41->getTotalAllocationCount());
    ptr41 = a41->get(500);
    EXPECT_EQ(505, a41->getTotalAllocationCount());
};

TEST_F(CountingAllocator_Test_getTotalAllocationCount, getTotalAllocationCount_function2) {
    ptr42 = a42->get(5);
    EXPECT_EQ(5, a42->getTotalAllocationCount());
    a42->release(ptr42, 5);
    EXPECT_EQ(5, a42->getTotalAllocationCount());
};


// Test getTotalReleaseCount function
class CountingAllocator_Test_getTotalReleaseCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a51;
    CountingAllocator<int>* a52;
    int* ptr51;
    int* ptr52;
    CountingAllocator_Test_getTotalReleaseCount() {
        a51 = new CountingAllocator<int>();
        a52 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getTotalReleaseCount(){
       delete a51;
       delete a52;
    };
};
TEST_F(CountingAllocator_Test_getTotalReleaseCount, getTotalReleaseCount_function1) {
    ptr51 = a51->get(5);
    EXPECT_EQ(0, a51->getTotalReleaseCount());
    ptr52 = a51->get(500);
    EXPECT_EQ(0, a51->getTotalReleaseCount());
};

TEST_F(CountingAllocator_Test_getTotalReleaseCount, getTotalReleaseCount_function2) {
    ptr52 = a52->get(5);
    EXPECT_EQ(0, a52->getTotalReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(5, a52->getTotalReleaseCount());
};

TEST_F(CountingAllocator_Test_getTotalReleaseCount, getTotalReleaseCount_function3) {
    ptr52 = a52->get(5);
    EXPECT_EQ(0, a52->getTotalReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(5, a52->getTotalReleaseCount());
    ptr52 = a52->get(5);
    EXPECT_EQ(5, a52->getTotalReleaseCount());
    a52->release(ptr52, 5);
    EXPECT_EQ(10, a52->getTotalReleaseCount());
};


// Test getTotalOutstandingCount function
class CountingAllocator_Test_getTotalOutstandingCount : public ::testing::Test {
  protected:
    CountingAllocator<int>* a61;
    int* ptr61;
    int* ptr62;
    CountingAllocator_Test_getTotalOutstandingCount() {
        a61 = new CountingAllocator<int>();
    };
    virtual ~CountingAllocator_Test_getTotalOutstandingCount(){
       delete a61;
    };
};

TEST_F(CountingAllocator_Test_getTotalOutstandingCount, getTotalOutstandingCount_function1) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    EXPECT_EQ(505, a61->getTotalAllocationCount());
    EXPECT_EQ(0, a61->getTotalReleaseCount());
    EXPECT_EQ(505, a61->getTotalOutstandingCount());
};

TEST_F(CountingAllocator_Test_getTotalOutstandingCount, getTotalOutstandingCount_function2) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    a61->release(ptr61, 5);
    EXPECT_EQ(505, a61->getTotalAllocationCount());
    EXPECT_EQ(5, a61->getTotalReleaseCount());
    EXPECT_EQ(500, a61->getTotalOutstandingCount());
};

TEST_F(CountingAllocator_Test_getTotalOutstandingCount, getTotalOutstandingCount_function3) {
    ptr61 = a61->get(5);
    ptr62 = a61->get(500);
    a61->release(ptr61, 5);
    a61->release(ptr62, 500);
    EXPECT_EQ(505, a61->getTotalAllocationCount());
    EXPECT_EQ(505, a61->getTotalReleaseCount());
    EXPECT_EQ(0, a61->getTotalOutstandingCount());
};






