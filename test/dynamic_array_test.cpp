// dynamic_array_test.cpp

#include "dynamic_array_test.h"

using namespace sgdc;

// Test push function
class DynamicArray_Test_push : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_push() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_push(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_push, push_function1) {
    ary->push(1);
    EXPECT_EQ(1,ary->at(0));
    ary->push(2);
    EXPECT_EQ(1,ary->at(0));
    EXPECT_EQ(2,ary->at(1));
};
TEST_F(DynamicArray_Test_push, push_function2) {
    ary->push(1);
    EXPECT_EQ(1,ary->getLength());
    ary->push(2);
    EXPECT_EQ(2,ary->getLength());
};

// Test pushFront function
class DynamicArray_Test_pushFront : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_pushFront() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_pushFront(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_pushFront, pushFront_function1) {
    ary->pushFront(1);
    EXPECT_EQ(1,ary->at(0));
    ary->pushFront(2);
    EXPECT_EQ(2,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
};
TEST_F(DynamicArray_Test_pushFront, pushFront_function2) {
    ary->pushFront(1);
    EXPECT_EQ(1,ary->getLength());
    ary->pushFront(2);
    EXPECT_EQ(2,ary->getLength());
};


// Test pop function
class DynamicArray_Test_pop : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_pop() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_pop(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_pop, pop_function1) {
    ary->push(1);
    ary->push(2);
    ary->push(3);
    EXPECT_EQ(1,ary->at(0));
    EXPECT_EQ(2,ary->at(1));
    EXPECT_EQ(3,ary->at(2));
    ary->pop();
    ary->push(4);
    EXPECT_EQ(1,ary->at(0));
    EXPECT_EQ(2,ary->at(1));
    EXPECT_EQ(4,ary->at(2));
};
TEST_F(DynamicArray_Test_pop, pop_function2) {
    ary->push(1);
    ary->push(2);
    EXPECT_EQ(2,ary->getLength());
    ary->pop();
    EXPECT_EQ(1,ary->getLength());
};


// Test popFront function
class DynamicArray_Test_popFront : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_popFront() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_popFront(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_popFront, popFront_function1) {
    ary->push(1);
    ary->push(2);
    ary->push(3);
    EXPECT_EQ(1,ary->at(0));
    EXPECT_EQ(2,ary->at(1));
    EXPECT_EQ(3,ary->at(2));
    ary->popFront();
    ary->push(4);
    EXPECT_EQ(2,ary->at(0));
    EXPECT_EQ(3,ary->at(1));
    EXPECT_EQ(4,ary->at(2));
};
TEST_F(DynamicArray_Test_popFront, popFront_function2) {
    ary->push(1);
    ary->push(2);
    EXPECT_EQ(2,ary->getLength());
    ary->popFront();
    EXPECT_EQ(1,ary->getLength());
};

// Test getLength function
class DynamicArray_Test_getLength : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_getLength() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_getLength(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_getLength, getLength_function1) {
    EXPECT_EQ(0,ary->getLength());
    ary->push(1);
    EXPECT_EQ(1,ary->getLength());
    ary->pushFront(3);
    EXPECT_EQ(2,ary->getLength());
    ary->popFront();
    EXPECT_EQ(1,ary->getLength());
    ary->pop();
    EXPECT_EQ(0,ary->getLength());
};


// Test at function
class DynamicArray_Test_at : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_at() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_at(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_at, at_function1) {
    ary->push(1);
    ary->pushFront(3);
    EXPECT_EQ(3,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
    ary->pushFront(5);
    EXPECT_EQ(5,ary->at(0));
};

// Test removeAt function
class DynamicArray_Test_removeAt : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_removeAt() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_removeAt(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_removeAt, removeAt_function1) {
    ary->push(0);
    ary->push(1);
    ary->push(2);
    ary->push(3);
    ary->push(4);
    EXPECT_EQ(0,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
    EXPECT_EQ(2,ary->at(2));
    EXPECT_EQ(3,ary->at(3));
    EXPECT_EQ(4,ary->at(4));
    ary->removeAt(2);
    ary->push(5);
    EXPECT_EQ(0,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
    EXPECT_EQ(3,ary->at(2));
    EXPECT_EQ(4,ary->at(3));
    EXPECT_EQ(5,ary->at(4));
};

TEST_F(DynamicArray_Test_removeAt, removeAt_function2) {
    ary->push(0);
    ary->push(1);
    ary->push(2);
    ary->push(3);
    ary->push(4);
    EXPECT_EQ(5,ary->getLength());
    ary->removeAt(3);
    EXPECT_EQ(4,ary->getLength());
};

// Test insertAt function
class DynamicArray_Test_insertAt : public ::testing::Test {
  protected:
    sgdm::CountingAllocator<int>* a;
    DynamicArray<int>* ary;
    DynamicArray_Test_insertAt() {
        a = new sgdm::CountingAllocator<int>();
        ary = new DynamicArray<int>(a);
    };
    virtual ~DynamicArray_Test_insertAt(){
       delete a;
    };
};

TEST_F(DynamicArray_Test_insertAt, insertAt_function1) {
    ary->push(0);
    ary->push(1);
    ary->push(2);
    ary->push(3);
    ary->push(4);
    EXPECT_EQ(0,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
    EXPECT_EQ(2,ary->at(2));
    EXPECT_EQ(3,ary->at(3));
    EXPECT_EQ(4,ary->at(4));
    ary->insertAt(2,6);
    EXPECT_EQ(0,ary->at(0));
    EXPECT_EQ(1,ary->at(1));
    EXPECT_EQ(6,ary->at(2));
    EXPECT_EQ(2,ary->at(3));
    EXPECT_EQ(3,ary->at(4));
    EXPECT_EQ(4,ary->at(5));
};

TEST_F(DynamicArray_Test_insertAt, insertAt_function2) {
    ary->push(0);
    ary->push(1);
    ary->push(2);
    ary->push(3);
    ary->push(4);
    EXPECT_EQ(5,ary->getLength());
    ary->insertAt(3, 6);
    EXPECT_EQ(6,ary->getLength());
};


