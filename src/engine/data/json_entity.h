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
    // define the JsonObject type with map
    typedef sgdc::Map<JsonEntity> JsonObject;
    // define the JsonArray type with dynamic array
    typedef sgdc::DynamicArray<JsonEntity> JsonArray;
    // define the JsonString type with string
    typedef std:: string JsonString;
    // use union to save space.
    union JsonPrimitive
    {
        bool boolValue;
        int intValue;
        double doubleValue;
    } j_Primitive;

    // the map use to recored value as object type with key
    JsonObject j_Object;
    // the dynamic array use to save the array type
    JsonString j_String;
    // the JsonString to save the string
    JsonArray j_Array;
  public:
    // Enum detailing the type of data stored
    enum class EntityType
    {
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
    //double entity constructor.
    JsonEntity(double double_number);
    // DESTRUCTOR
    ~JsonEntity();

    // OPERATOR OVERLOADS
    JsonEntity& operator = (const JsonEntity &other);
     

    // ACCESSORS
    // getting object elements as an entity.
    JsonEntity& operator[](std::string key);
    // getting array elements as an entity.
    JsonEntity& operator[](unsigned int index);

    // getting object elements as an entity.
    JsonEntity get(std::string key);
    // getting array elements as an entity.
    JsonEntity at(unsigned int index);

    // get what type this enity is.
    EntityType type() const;

    // get value as array
    const sgdc::DynamicArray<JsonEntity>& asArray() const;
    // get value as string
    const std::string& asString() const;
    // get value as boolean
    bool asBoolean() const;
    // get value as int
    int asInt() const;
    //float asFloat() const;
    double asDouble() const;
    // get values

    // Checker
    // check the value type is NULL
    bool isNull() const;
    // check the value type is NULL
    bool isObject() const;
    // check the value type is NULL
    bool isArray() const;
    // check the value type is NULL
    bool isString() const;
    // check the value type is NULL
    bool isBoolean() const;
    // check the value type is NULL
    bool isInt() const;
    //bool isFloat() const;
    bool isDouble() const;
    // checking types.

   

};


// CONSTRUCTORS
// default constructor.
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


//double entity constructor.
inline
JsonEntity::JsonEntity(double double_number) : j_type(EntityType::JSON_DOUBLE){
    j_Primitive.doubleValue = double_number;
}



// DESTRUCTOR
inline
JsonEntity::~JsonEntity(){

}


// OPERATOR OVERLOADS
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


// Accese the entity
// getting object elements as an entity, need string as key
inline
JsonEntity& JsonEntity::operator[](std::string key) 
{
    assert(isObject());
    return j_Object[key];
}


// getting array elements as an entity, need int as index
inline
JsonEntity& JsonEntity::operator[](unsigned int index) 
{
    assert(isArray());
    return j_Array[index];
}


// getting object elements as an entity, need string as key
inline
JsonEntity JsonEntity::get(std::string key){
    assert(isObject());
    return j_Object[key];
    
}
// getting array elements as an entity,  need int as index
inline
JsonEntity JsonEntity::at(unsigned int index){
    assert(isArray());
    return j_Array[index];
}


// get what type this enity is.
inline
JsonEntity::EntityType JsonEntity::type() const{
    return j_type;
}


// get values
// get value as array
inline
const sgdc::DynamicArray<JsonEntity>& JsonEntity::asArray() const
{
    assert(j_type == EntityType::JSON_ARRAY);
    return j_Array;
}


// get value as string
inline
const std::string& JsonEntity::asString() const
{
    assert(j_type == EntityType::JSON_STRING);
    return j_String;
}


// get value as boolean
inline
bool JsonEntity::asBoolean() const
{
    assert(j_type == EntityType::JSON_BOOL);
    return j_Primitive.boolValue;
}


// get value as int
inline
int JsonEntity::asInt() const
{
    assert(j_type == EntityType::JSON_INT);
    return j_Primitive.intValue;
}


//float asFloat() const;
inline
double JsonEntity::asDouble() const
{
    assert(j_type == EntityType::JSON_DOUBLE);
    return j_Primitive.doubleValue;
}



// check the entity type
// check the value type is NULL
inline
bool JsonEntity::isNull() const
{
    return (j_type == EntityType::JSON_NULL);
}


// check the value type is object
inline
bool JsonEntity::isObject() const
{
    return (j_type == EntityType::JSON_OBJECT);
}


// check the value type is array
inline
bool JsonEntity::isArray() const
{
    return (j_type == EntityType::JSON_ARRAY);
}


// check the value type is string
inline
bool JsonEntity::isString() const
{
    return (j_type == EntityType::JSON_STRING);
}


// check the value type is boolean
inline
bool JsonEntity::isBoolean() const
{
    return (j_type == EntityType::JSON_BOOL);
}


// check the value type is int
inline
bool JsonEntity::isInt() const
{
    return (j_type == EntityType::JSON_INT);
}


// check the value type is double
inline
bool JsonEntity::isDouble() const
{
    return (j_type == EntityType::JSON_DOUBLE);
}


};
#endif