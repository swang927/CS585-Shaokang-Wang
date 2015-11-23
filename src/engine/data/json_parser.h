//  json_parser.h

#ifndef INCLUDED_JSON_PARSER
#define INCLUDED_JSON_PARSER

#include "json_entity.h"
#include "../memory/iallocator.h"
#include "../memory/default_allocator.h"
#include "../memory/counting_allocator.h"
#include <string>
#include <iostream>
    
namespace sgdd
{
// A struct containing a static utility function for parsing a json string
struct JsonParser{
    // Dynamic list to save the list entities need to be parsed 
    sgdc::DynamicArray<std::string> list;
    // Dynamic list to save the object entities need to be parsed 
    sgdc::DynamicArray<std::string> object;
    // temporary array to save the list elements
    sgdc::DynamicArray<JsonEntity> temp_array;
    //  temporary map to save the object elements
    sgdc::Map<JsonEntity> temp_map;
    // current entity parsed from the string
    JsonEntity* Entity;
    // the string can be parsed to single entity
    std::string token;
    // save the key
    std::string key;
    // save the value
    std::string value;

    // CONSTRUCTORS
    // default constructor.
    JsonParser();

    // static utility function for parsing a json string
    static JsonEntity* fromString(const std::string& rawJson);

    // verify a input is representing a number or not
    static bool isNumber(std::string txt);
    // abstract a string to the basic json format:
    /*
    object ->    {}    ||    { members }
    members ->    pair    ||    pair    ||     members    ||    pair
    string ->    value    ||    array    ||    []    ||    [elements]
    elements ->    value    ||    value, elements
    value ->    string    ||    number    ||    object    ||    array    ||
                true    ||    false    ||    null
    */
    void foldstring(std::string& txt);
};


// CONSTRUCTORS
// default constructor.
inline
JsonParser::JsonParser(){
    list = *(new sgdc::DynamicArray<std::string>);
    object = *(new sgdc::DynamicArray<std::string>);
    temp_array = *(new sgdc::DynamicArray<JsonEntity>);
    temp_map = *(new sgdc::Map<JsonEntity>);
    Entity = new JsonEntity;
}


// abstract a string to the basic json format:
inline
void JsonParser::foldstring(std::string& txt){
    // fold objects - save the object block to 'object' list 
    int count_brace = 0;
    int start_index = -1;
    for (unsigned int i = 0; i < txt.length(); i++){
        if (txt[i] == '{'){
            count_brace++;
            if (start_index == -1)
                start_index = i;
        }
        if (txt[i] == '}'){
            count_brace--;
            if (start_index != -1 && count_brace == 0){
                int len = i - start_index + 1;
                this->object.push(txt.substr(start_index, len));
                // replace the object as string "OBJECT_HERE"
                txt.replace(start_index, len, "OBJECT_HERE");
                i = i - len + 11;
                start_index = -1;
            }
        }
    }
    // fold array - save the list block to 'list' list 
    int count_square_bracket = 0;
    start_index = -1;
    for (unsigned int i = 0; i < txt.length(); i++){
        if (txt[i] == '['){
            count_square_bracket++;
            if (start_index == -1)
                start_index = i;
        }
        if (txt[i] == ']'){
            count_square_bracket--;
            if (start_index != -1 && count_square_bracket == 0){
                int len = i - start_index + 1;
                this->list.push(txt.substr(start_index, len));
                // replace the list as string "LIST_HERE"
                txt.replace(start_index, len, "LIST_HERE");
                i = i - len + 9;
                start_index = -1;
            }
        }
    }
};



// static utility function for parsing a json string
inline
JsonEntity* JsonParser::fromString(const std::string& rawJson){
    // create a new parser
    JsonParser parser = JsonParser();
    // load raw text
    char start = rawJson[rawJson.find_first_not_of(" \t\r\n")];

    // create as string entity
    if (start == '\''){
        if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != '\''){
            ::std::cout << "string_syntax : " << rawJson << std::endl;
            return parser.Entity;
        }
        // recursively process the rest raw txt
        parser.token = rawJson.substr(rawJson.find("\'") + 1);
        parser.token = parser.token.substr(0, parser.token.find("\'"));
        // create the string entity
        parser.Entity = new JsonEntity(parser.token);
    }


    // create as array entity
    else if (start == '['){
        // find the close mark "]" and chop the list part from input
        if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != ']'){
            ::std::cout << "array_syntax : " << rawJson << std::endl;
            return parser.Entity;
        }
        std::string txt = rawJson.substr(0, rawJson.rfind("]"));
        txt = txt.substr(rawJson.find("[") + 1);
        // remove the array and oject inside the txt
        parser.foldstring(txt);
        // build the array
        int currPos = 0;
        int prevPos = 0;
        while (txt.find(",", currPos) >= 0)
        {
            // chop the list by ","
            currPos = txt.find(",", currPos);
            parser.token = txt.substr(prevPos, currPos - prevPos);
            parser.token = parser.token.substr(parser.token.find_first_not_of(" \t\r\n"));
            parser.token = parser.token.substr(0, parser.token.find_last_not_of(" \t\r\n") + 1);
            // recover the fold list or object entities if there is
            if (parser.token.compare("LIST_HERE") == 0){
                parser.token = parser.list.popFront();
                int start_index = parser.token.find("OBJECT_HERE");
                while (start_index >= 0){
                    std::string object_txt = parser.object.popFront();
                    parser.token.replace(start_index, 11, object_txt);
                    start_index = parser.token.find("OBJECT_HERE");
                }
            }
            else if (parser.token.compare("OBJECT_HERE") == 0){
                parser.token = parser.object.popFront();
            }

            // push the element to template array
            parser.temp_array.push(*(fromString(parser.token)));
            currPos++;
            prevPos = currPos;
            // if go through all element then leave the loop 
            if (currPos == 0)
                break;
        }
        // create the array entity
        parser.Entity = new JsonEntity(parser.temp_array);
    }

    // create as object entity
    else if (start == '{'){
        // find the close mark "}" and chop the object part from input
        if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != '}'){
            ::std::cout << "object_syntax : " << rawJson << std::endl;
            return parser.Entity;
        }
        std::string txt = rawJson.substr(0, rawJson.rfind("}"));
        txt = txt.substr(rawJson.find("{") + 1);
        // remove the array and oject inside the txt
        parser.foldstring(txt);

        // build the object
        int currPos = 0;
        int prevPos = 0;
        while (txt.find(",", currPos) >= 0)
        {
            // chop the first object by "," from txt
            currPos = txt.find(",", currPos);
            parser.token = txt.substr(prevPos, currPos - prevPos);
            // split the object to key and value by ":"
            parser.key = parser.token.substr(0, parser.token.find(":"));
            parser.value = parser.token.substr(parser.token.find(":") + 1);
            // save the key
            parser.key = parser.key.substr(parser.key.find("'") + 1);
            parser.key = parser.key.substr(0, parser.key.rfind("'"));
            // save the value
            parser.value = parser.value.substr(parser.value.find_first_not_of(" \t\r\n"));
            parser.value = parser.value.substr(0, parser.value.find_last_not_of(" \t\r\n") + 1);
            // recover the fold list or object entities if there is
            if (parser.value.compare("LIST_HERE") == 0){
                parser.value = parser.list.popFront();
                int start_index = parser.value.find("OBJECT_HERE");
                while (start_index >= 0){
                    std::string object_txt = parser.object.popFront();
                    parser.value.replace(start_index, 11, object_txt);
                    start_index = parser.value.find("OBJECT_HERE");
                }
            }
            else if (parser.value.compare("OBJECT_HERE") == 0){
                parser.value = parser.object.popFront();
            }

            // push the element to template map
            parser.temp_map[parser.key] = *(fromString(parser.value));
            // if go through all element then leave the loop 
            currPos++;
            prevPos = currPos;
            if (currPos == 0)
                break;
        }
        // create the object entity
        parser.Entity = new JsonEntity(parser.temp_map);
    }

    else{
        parser.token = rawJson.substr(rawJson.find_first_not_of(" \t\r\n"));
        parser.token = parser.token.substr(0, parser.token.find_last_not_of(" \t\r\n") + 1);

        // create as boolean entity
        // entity with true value
        if (parser.token.compare("true") == 0 || parser.token.compare("TRUE") == 0){
            bool judge = 1;
            parser.Entity = new JsonEntity(judge);
        }
        // entity with false value
        else if (parser.token.compare("false") == 0 || parser.token.compare("FALSE") == 0){
            bool judge = 0;
            parser.Entity = new JsonEntity(judge);
        }
        else{
        // create as number: int or float 
            std::string txt = parser.token;
            if (!isNumber(txt)){
                ::std::cout << "number_syntax: " << parser.token << std::endl;
                return parser.Entity;
            }
            else{
                bool isFloat = false;
                int decimal = 0;
                double dnumber = 0;
                long int inumber = 0;

                int sign = 1;
                // assigne the sign
                if (txt[0] == '-')
                    sign = -1;
                // compute the number and save decimal palce if it is a float number
                for (unsigned int i = 0; i < txt.length(); i++){
                    if (isFloat)
                        decimal++;
                    if (txt[i] >= '0' && txt[i] <= '9'){
                        inumber = inumber * 10 + (txt[i] - '0');
                    }
                    if (txt[i] == '.')
                        isFloat = true;
                }
                // if is float number save a double entity
                if (isFloat){
                    dnumber = double(inumber);
                    for (int i = 0; i < decimal; i++){
                        dnumber = dnumber / 10;
                    }
                    dnumber = dnumber*sign;
                // create the double entity
                    parser.Entity = new JsonEntity(dnumber);
                }

                // if is intiger save as a intiger
                else{
                    inumber = inumber*sign;
                // create the int entity
                    parser.Entity = new JsonEntity((int)inumber);
                }
            }
        }
    }
    return parser.Entity;
}



// verify a input is representing a number or not
inline
bool JsonParser::isNumber(std::string txt){
    bool decimal = false;
    bool itis = true;
    // go through the whole txt, check each char
    for (unsigned int i = 0; i < txt.length(); i++){
        if (txt[i] >= '0' && txt[i] <= '9'){
            itis = true;
        }
        // only the first digit can be sign place
        else if (txt[i] == '-' && i == 0){
            itis = true;
        }
        // make sure there is only one "."
        else if (txt[i] == '.' && decimal == false){
            itis = true;
            decimal = true;
        }
        else{
            itis = false;
            break;
        }
    }
    return itis;
};


};

#endif