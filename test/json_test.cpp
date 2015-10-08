// json_test.cpp

#include "json_test.h"

using namespace sgdd;

// test the type function
class Json_Test_type : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data;
    Json_Test_type() {
        json = "{ 'name': 'Configuration', 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_type(){
    };
};


TEST_F(Json_Test_type, type_function_1) {
    EXPECT_EQ(JsonEntity::EntityType::JSON_ARRAY, data["values"].type());
}

TEST_F(Json_Test_type, type_function_2) {
    EXPECT_EQ(JsonEntity::EntityType::JSON_STRING, data["name"].type());
}




// getting object elements as an entity by operator[].
class Json_Test_bracket_object : public ::testing::Test {
  protected:
    std::string json, txt;
    JsonEntity data;
    
    Json_Test_bracket_object() {
        json = "{ 'name': 'Configuration', 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_bracket_object(){
    };
};


TEST_F(Json_Test_bracket_object, access_function_1) {
    txt = data["name"].asString();
    EXPECT_EQ("Configuration", txt);
}


// getting array elements as an entity by operator[].
class Json_Test_bracket_array : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data;
    int a;
    Json_Test_bracket_array() {
        json = "[1, 3, 'penguin'] ";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_bracket_array(){
    };
};

TEST_F(Json_Test_bracket_array, access_function_2) {
    a = data[1].asInt();
    EXPECT_EQ(3, a);
}


// getting object and elements as an entity by operator[].
class Json_Test_bracket : public ::testing::Test {
  protected:
    std::string json, txt;
    JsonEntity data;
    
    Json_Test_bracket() {
        json = "{ 'name': 'Configuration', 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_bracket(){
    };
};

TEST_F(Json_Test_bracket, access_function_3) {
    txt = data["values"][2].asString();
    EXPECT_EQ("penguin", txt);
}


// getting object elements as an entity by get function.
class Json_Test_get_object : public ::testing::Test {
  protected:
    std::string json, txt;
    JsonEntity data;
    
    Json_Test_get_object() {
        json = "{ 'name': 'Configuration', 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_get_object(){
    };
};

TEST_F(Json_Test_get_object, access_function_4) {
    txt = data["name"].asString();
    EXPECT_EQ("Configuration", txt);
}



// getting array elements as an entity by at function.
class Json_Test_at_array : public ::testing::Test {
  protected:
    std::string json, txt;
    JsonEntity data;
    int a; 
    Json_Test_at_array() {
        json = "[1, 3, 'penguin']";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_at_array(){
    };
};

TEST_F(Json_Test_at_array, access_function_4) {
    a = data[0].asInt();
    EXPECT_EQ(1, a);
    a = data[1].asInt();
    EXPECT_EQ(3, a);
    txt = data[2].asString();
    EXPECT_EQ("penguin", txt);
}


// check a entity is a object.
class Json_Test_isobject : public ::testing::Test {
  protected:
    std::string json, txt;
    JsonEntity data; 
    Json_Test_isobject() {
        json = "{ 'name': {'judge' : 'Configuration'}, 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isobject(){
    };
};

TEST_F(Json_Test_isobject, check_function_1) {
    EXPECT_TRUE(data["name"].isObject());
    EXPECT_FALSE(data["value"].isObject());
}


// check a entity is a array.
class Json_Test_isarray : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data; 
    Json_Test_isarray() {
        json = "{ 'name': {'judge' : 'Configuration'}, 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isarray(){
    };
};

TEST_F(Json_Test_isarray, check_function_2) {
    EXPECT_FALSE(data["name"].isArray());
    EXPECT_TRUE(data["value"].isArray());
}


// check a entity is a String.
class Json_Test_isstring : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data; 
    Json_Test_isstring() {
        json = "{ 'name':  'Configuration', 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isstring(){
    };
};

TEST_F(Json_Test_isstring, check_function_3) {
    EXPECT_FALSE(data["value"].isString());
    EXPECT_TRUE(data["name"].isString());
}


// check a entity is a Boolean.
class Json_Test_isbool : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data; 
    Json_Test_isbool() {
        json = "{ 'name':  true, 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isbool(){
    };
};

TEST_F(Json_Test_isbool, check_function_4) {
    EXPECT_FALSE(data["value"].isBoolean());
    EXPECT_TRUE(data["name"].isBoolean());
}


// check a entity is a Int.
class Json_Test_isint : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data; 
    Json_Test_isint() {
        json = "{ 'name':  true, 'values' : [1, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isint(){
    };
};

TEST_F(Json_Test_isint, check_function_5) {
    EXPECT_TRUE(data["value"][0].isInt());
    EXPECT_FALSE(data["name"].isInt());
}


// check a entity is a Float.
class Json_Test_isdouble : public ::testing::Test {
  protected:
    std::string json;
    JsonEntity data; 
    Json_Test_isdouble() {
        json = "{ 'name':  true, 'values' : [1.1123, 3, 'penguin'] }";
	data =  *(JsonParser::fromString( json ));
    };
    virtual ~Json_Test_isdouble(){
    };
};

TEST_F(Json_Test_isdouble, check_function_6) {
    EXPECT_TRUE(data["value"][0].isDouble());
    EXPECT_FALSE(data["name"].isDouble());
}
