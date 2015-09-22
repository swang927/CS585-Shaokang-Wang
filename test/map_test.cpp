// map_test.cpp

#include "map_test.h"

using namespace sgdc;

// Test operator[] function
class Map_Test_index_operator : public ::testing::Test {
  protected:
    Map<int> stry ;
    std::string a, b ,c ,d, e;
    int x;
    Map_Test_index_operator() {
        a = "baby";
        b = "box";
        c = "bank";
        d = "bad";
        e = "A";
    };
    virtual ~Map_Test_index_operator(){
    };
};

TEST_F(Map_Test_index_operator, insert) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    stry[e] = 9;
    EXPECT_EQ(3,stry[a]);
    EXPECT_EQ(1,stry[c]);
    EXPECT_EQ(9,stry[e]);
};
TEST_F(Map_Test_index_operator, retrive) {
    x = stry[b];
    EXPECT_EQ(0,x);
};

// Test has function
class Map_Test_has : public ::testing::Test {
  protected:
    Map<int> stry ;
    std::string a, b ,c ,d, e;
    int x;
    Map_Test_has() {
        a = "baby";
        b = "box";
        c = "bank";
        d = "bad";
        e = "A";
    };
    virtual ~Map_Test_has(){
    };
};

TEST_F(Map_Test_has, test1) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    EXPECT_TRUE(stry.has(a));
    EXPECT_TRUE(stry.has(d));
    EXPECT_FALSE(stry.has(e));
};
TEST_F(Map_Test_has, test2) {
    EXPECT_FALSE(stry.has(e));
    stry[e] = 9;
    EXPECT_TRUE(stry.has(e));
};


// Test remove function
class Map_Test_remove : public ::testing::Test {
  protected:
    Map<int> stry ;
    std::string a, b ,c ,d, e;
    int x;
    Map_Test_remove() {
        a = "baby";
        b = "box";
        c = "bank";
        d = "bad";
        e = "A";
    };
    virtual ~Map_Test_remove(){
    };
};

TEST_F(Map_Test_remove, test1) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    EXPECT_TRUE(stry.has(a));
    stry.remove(a);
    EXPECT_FALSE(stry.has(a));
};
TEST_F(Map_Test_remove, test2) {
    stry[a] = 3;
    EXPECT_TRUE(stry.has(a));
    EXPECT_TRUE(stry.has(a));  
};

// Test keys function
class Map_Test_keys : public ::testing::Test {
  protected:
    Map<int> stry;
    sgdc::DynamicArray<std::string> str;
    std::string a, b ,c ,d, e;
    int x;
    Map_Test_keys() {
        a = "baby";
        b = "box";
        c = "bank";
        d = "bad";
        e = "A";
        str = *(new sgdc::DynamicArray<std::string>());
    };
    virtual ~Map_Test_keys(){
    };
};

TEST_F(Map_Test_keys, test1) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    stry[e] = 9;
    str = stry.keys();
    EXPECT_EQ(a, str[4]);
};
TEST_F(Map_Test_keys, test2) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    stry[e] = 9;
    stry.remove(a);
    str = stry.keys();
    EXPECT_EQ(c, str[3]);
};


// Test values function
class Map_Test_values : public ::testing::Test {
  protected:
    Map<int> stry;
    sgdc::DynamicArray<int> x;
    std::string a, b ,c ,d, e;
    Map_Test_values() {
        a = "baby";
        b = "box";
        c = "bank";
        d = "bad";
        e = "A";
        x = *(new sgdc::DynamicArray<int>());
    };
    virtual ~Map_Test_values(){
    };
};

TEST_F(Map_Test_values, test1) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    stry[e] = 9;
    x = stry.values();
    EXPECT_EQ(3, x[4]);
};
TEST_F(Map_Test_values, test2) {
    stry[a] = 3;
    stry[b] = 0;
    stry[c] = 1;
    stry[d] = 2;
    stry[e] = 9;
    stry.remove(a);
    x = stry.values();
    EXPECT_EQ(1, x[3]);
};

