// json_entity.h

#ifndef INCLUDED_JSON_ENTITY
#define INCLUDED_JSON_ENTITY

#include <string>
#include <algorithm>
#include "../containers/dynamic_array.h"
#include "../containers/map.h"

namespace sgdd
{
// An aggregate type capable of storing various primitive, object, and array data describing json. 
class JsonEntity{
  private:
    // define map as JsonObject to save object entity
    typedef sgdc::Map<JsonEntity> JsonObject;
    // define dynamic array as JsonArray to save array entity
    typedef sgdc::DynamicArray<JsonEntity> JsonArray;
    // define string as JsonString to save string
    typedef std:: string JsonString;

    // use union as JsonPrimitive to save boolean & int & double type.
    union JsonPrimitive{
        // three possible value type:
        bool boolValue;
        int intValue;
        double doubleValue;
    };

    // create fields for those type
    JsonObject j_Object;
    JsonString j_String;
    JsonArray j_Array;
    JsonPrimitive j_Primitive;

  public:
    // enum all the possible json type
    enum class EntityType
    {
        // TODO:
        JSON_NULL,
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_BOOL,
        JSON_INT,
        JSON_DOUBLE
    } j_type;

    // CONSTRUCTORS
    // default constructor.
    JsonEntity();
    //string entity constructor.
    JsonEntity(std::string str);
    //array entity constructor.
    JsonEntity(JsonArray arry);
    //object entity constructor.
    JsonEntity(JsonObject object);
    //boolean entity constructor.
    JsonEntity(bool judge);
    //int entity constructor.
    JsonEntity(int int_number);
    //bouble entity constructor.
    JsonEntity(double double_number);

    // DESTRUCTOR
    ~JsonEntity();

    // OPERATOR OVERLOADS
    JsonEntity& operator = (const JsonEntity &other);

    // ACCESSORS
    // getting what type this enity is.
    EntityType type() const;
    
    
    // getting values
    // getting value as array
    const sgdc::DynamicArray<JsonEntity>& asArray() const;
    // getting value as string
    const std::string& asString() const;
    // getting value as boolean
    bool asBoolean() const;
    // getting value as int
    int asInt() const;
    // getting value as double
    double asDouble() const;

    


    // checking types.
    // check is value type is NULL
    bool isNull() const;
    // check is value type is Object
    bool isObject() const;
    // check is value type is Array
    bool isArray() const;
    // check is value type is String
    bool isString() const;
    // check is value type is boolean
    bool isBoolean() const;
    // check is value type is int
    bool isInt() const;
    // check is value type is double
    bool isDouble() const;

    
    // getting object elements as an entity.
    JsonEntity& operator[](std::string key);
    // getting array elements as an entity.
    JsonEntity& operator[](unsigned int index);

    // getting object elements as an entity.
    JsonEntity get(std::string key);
    // getting array elements as an entity.
    JsonEntity at(unsigned int index);

}; // end of class


// CONSTRUCTORS
inline
JsonEntity::JsonEntity() : j_type(EntityType::JSON_NULL){

}

//string entity constructor.
inline
JsonEntity::JsonEntity(std::string str) : j_type(EntityType::JSON_STRING){
    j_String = str;
}

//array entity constructor.
inline
JsonEntity::JsonEntity(JsonArray arry) : j_type(EntityType::JSON_ARRAY){
    j_Array = arry;
}


//object entity constructor.
inline
JsonEntity::JsonEntity(JsonObject object) : j_type(EntityType::JSON_OBJECT){
    j_Object = object;
}


//boolean entity constructor.
inline
JsonEntity::JsonEntity(bool judge) : j_type(EntityType::JSON_BOOL){
    j_Primitive.boolValue = judge;
}


//int entity constructor.
inline
JsonEntity::JsonEntity(int int_number) : j_type(EntityType::JSON_INT){
    j_Primitive.intValue = int_number;
}


//bouble entity constructor.
inline
JsonEntity::JsonEntity(double double_number) : j_type(EntityType::JSON_DOUBLE){
    j_Primitive.doubleValue = double_number;
}


// assign OPERATOR OVERLOADS
inline
JsonEntity& JsonEntity::operator = (const JsonEntity &other){
    if (this != &other) {
        j_Primitive = other.j_Primitive;
        j_Object = other.j_Object;
        j_String = other.j_String;
        j_Array = other.j_Array;
        j_type = other.j_type;
    };
    return *this;
}


// DESTRUCTOR
inline
JsonEntity::~JsonEntity(){
}


// accese the entity
// getting what type this enity is.
inline
JsonEntity::EntityType JsonEntity::type() const{
    return j_type;
}


// getting value as array
inline
const sgdc::DynamicArray<JsonEntity>& JsonEntity::asArray() const
{
    assert(j_type == EntityType::JSON_ARRAY);
    return j_Array;
}


// getting value as string
inline
const std::string& JsonEntity::asString() const
{
    assert(j_type == EntityType::JSON_STRING);
    return j_String;
}


// getting value as boolean
inline
bool JsonEntity::asBoolean() const
{
    assert(j_type == EntityType::JSON_BOOL);
    return j_Primitive.boolValue;
}


// getting value as int
inline
int JsonEntity::asInt() const
{
    assert(j_type == EntityType::JSON_INT);
    return j_Primitive.intValue;
}


// getting value as double
inline
double JsonEntity::asDouble() const
{
    assert(j_type == EntityType::JSON_DOUBLE);
    return j_Primitive.doubleValue;
}


// check the entity type
// check is value type is NULL
inline
bool JsonEntity::isNull() const
{
    return (j_type == EntityType::JSON_NULL);
}


// check is value type is object
inline
bool JsonEntity::isObject() const
{
    return (j_type == EntityType::JSON_OBJECT);
}


// check is value type is array
inline
bool JsonEntity::isArray() const
{
    return (j_type == EntityType::JSON_ARRAY);
}


// check is value type is string
inline
bool JsonEntity::isString() const
{
    return (j_type == EntityType::JSON_STRING);
}


// check is value type is boolean
inline
bool JsonEntity::isBoolean() const
{
    return (j_type == EntityType::JSON_BOOL);
}


// check is value type is int
inline
bool JsonEntity::isInt() const
{
    return (j_type == EntityType::JSON_INT);
}


// check is value type is double
inline
bool JsonEntity::isDouble() const
{
    return (j_type == EntityType::JSON_DOUBLE);
}


// getting object elements as an entity.
inline
JsonEntity& JsonEntity::operator[](std::string key)
{
    assert(isObject());
    return j_Object[key];
}


// getting array elements as an entity.
inline
JsonEntity& JsonEntity::operator[](unsigned int index)
{
    assert(isArray());
    return j_Array[index];
}


// getting object elements as an entity.
inline
JsonEntity JsonEntity::get(std::string key){
    assert(isObject());
    return j_Object[key];
}

// getting array elements as an entity.    
inline
JsonEntity JsonEntity::at(unsigned int index){
    assert(isArray());
    return j_Array[index];
}

}; // end of name space
    
#endif