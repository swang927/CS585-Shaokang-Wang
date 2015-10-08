// json_entity.h

#ifndef INCLUDED_JSON_ENTITY
#define INCLUDED_JSON_ENTITY

#include <string>
#include <algorithm>
#include "../containers/dynamic_array.h"
#include "../containers/map.h"


namespace sgdd
{
class JsonEntity{
  private:
	typedef sgdc::Map<JsonEntity> JsonObject;
	typedef sgdc::DynamicArray<JsonEntity> JsonArray;
	typedef std:: string JsonString;
	// use union to save space.
	union JsonPrimitive
	{
		bool boolValue;
		int intValue;
		double doubleValue;
	} j_Primitive;


	JsonObject j_Object;
	JsonString j_String;
	JsonArray j_Array;

  public:
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
	EntityType type() const;
	// getting what type this enity is.

	const sgdc::DynamicArray<JsonEntity>& asArray() const;
	const std::string& asString() const;
	bool asBoolean() const;
	int asInt() const;
	//float asFloat() const;
	double asDouble() const;
	// getting values

	bool isNull() const;
	bool isObject() const;
	bool isArray() const;
	bool isString() const;
	bool isBoolean() const;
	bool isInt() const;
	//bool isFloat() const;
	bool isDouble() const;
	// checking types.

	// getting object elements as an entity.
	JsonEntity& operator[](std::string key);
	// getting array elements as an entity.
	JsonEntity& operator[](unsigned int index);

	// getting object elements as an entity.
	JsonEntity get(std::string key);
	// getting array elements as an entity.
	JsonEntity at(unsigned int index);

};


// CONSTRUCTORS
inline
JsonEntity::JsonEntity() : j_type(EntityType::JSON_NULL){
}


inline
JsonEntity::JsonEntity(std::string str) : j_type(EntityType::JSON_STRING){
	j_String = str;
}


inline
JsonEntity::JsonEntity(JsonArray arry) : j_type(EntityType::JSON_ARRAY){
	j_Array = arry;
}

inline
JsonEntity::JsonEntity(JsonObject object) : j_type(EntityType::JSON_OBJECT){
	j_Object = object;
}

inline
JsonEntity::JsonEntity(bool judge) : j_type(EntityType::JSON_BOOL){
	j_Primitive.boolValue = judge;
}

inline
JsonEntity::JsonEntity(int int_number) : j_type(EntityType::JSON_INT){
	j_Primitive.intValue = int_number;
}

inline
JsonEntity::JsonEntity(double double_number) : j_type(EntityType::JSON_DOUBLE){
	j_Primitive.doubleValue = double_number;
}

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

inline
JsonEntity& JsonEntity::operator[](std::string key) 
{
	assert(isObject());
	return j_Object[key];
}

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



// accese the entity
inline
JsonEntity::EntityType JsonEntity::type() const{
	return j_type;
}



inline
const sgdc::DynamicArray<JsonEntity>& JsonEntity::asArray() const
{
	assert(j_type == EntityType::JSON_ARRAY);
	return j_Array;
}

inline
const std::string& JsonEntity::asString() const
{
	assert(j_type == EntityType::JSON_STRING);
	return j_String;
}

inline
bool JsonEntity::asBoolean() const
{
	assert(j_type == EntityType::JSON_BOOL);
	return j_Primitive.boolValue;
}

inline
int JsonEntity::asInt() const
{
	assert(j_type == EntityType::JSON_INT);
	return j_Primitive.intValue;
}


inline
double JsonEntity::asDouble() const
{
	assert(j_type == EntityType::JSON_DOUBLE);
	return j_Primitive.doubleValue;
}



// check the entity type
inline
bool JsonEntity::isNull() const
{
	return (j_type == EntityType::JSON_NULL);
}

inline
bool JsonEntity::isObject() const
{
	return (j_type == EntityType::JSON_OBJECT);
}

inline
bool JsonEntity::isArray() const
{
	return (j_type == EntityType::JSON_ARRAY);
}

inline
bool JsonEntity::isString() const
{
	return (j_type == EntityType::JSON_STRING);
}

inline
bool JsonEntity::isBoolean() const
{
	return (j_type == EntityType::JSON_BOOL);
}

inline
bool JsonEntity::isInt() const
{
	return (j_type == EntityType::JSON_INT);
}


inline
bool JsonEntity::isDouble() const
{
	return (j_type == EntityType::JSON_DOUBLE);
}


};
#endif