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

struct JsonParser{

	sgdc::DynamicArray<std::string> list;

	sgdc::DynamicArray<std::string> object;

	sgdc::DynamicArray<JsonEntity> temp_array;

	sgdc::Map<JsonEntity> temp_map;

	JsonEntity* Entity;

	std::string token;

	std::string key;

	std::string value;



	JsonParser();

	static JsonEntity* fromString(const std::string& rawJson);

	static bool isNumber(std::string txt);

	void foldstring(std::string& txt);

};







inline

JsonParser::JsonParser(){

	list = *(new sgdc::DynamicArray<std::string>);

	object = *(new sgdc::DynamicArray<std::string>);

	temp_array = *(new sgdc::DynamicArray<JsonEntity>);

	temp_map = *(new sgdc::Map<JsonEntity>);

	Entity = new JsonEntity;

}



inline

void JsonParser::foldstring(std::string& txt){

	// fold the object 

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

				txt.replace(start_index, len, "OBJECT_HERE");

				i = i - len + 11;

				start_index = -1;

			}

		}

	}

	// fold array

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

				txt.replace(start_index, len, "LIST_HERE");

				i = i - len + 9;

				start_index = -1;

			}

		}

	}

}





inline

JsonEntity* JsonParser::fromString(const std::string& rawJson){

	JsonParser parser = JsonParser();

	char start = rawJson[rawJson.find_first_not_of(" \t\r\n")];



	// save as string

	if (start == '\''){

		if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != '\''){

			::std::cout << "string_syntax : " << rawJson << std::endl;

			return parser.Entity;

		}

		parser.token = rawJson.substr(rawJson.find("\'") + 1);

		parser.token = parser.token.substr(0, parser.token.find("\'"));

		parser.Entity = new JsonEntity(parser.token);

	}



	// save the array

	else if (start == '['){

		if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != ']'){

			::std::cout << "array_syntax : " << rawJson << std::endl;

			return parser.Entity;

		}

		std::string txt = rawJson.substr(0, rawJson.rfind("]"));

		txt = txt.substr(rawJson.find("[") + 1);

		

		// remove the array and oject effect

		parser.foldstring(txt);



		// build the array

		int currPos = 0;

		int prevPos = 0;

		while (txt.find(",", currPos) >= 0)

		{

			currPos = txt.find(",", currPos);

			parser.token = txt.substr(prevPos, currPos - prevPos);

			parser.token = parser.token.substr(parser.token.find_first_not_of(" \t\r\n"));

			parser.token = parser.token.substr(0, parser.token.find_last_not_of(" \t\r\n") + 1);



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

			if (currPos == 0)

				break;

		}

		parser.Entity = new JsonEntity(parser.temp_array);



	}

	

	// save the object

	else if (start == '{'){

		if (rawJson[rawJson.find_last_not_of(" \t\r\n")] != '}'){

			::std::cout << "object_syntax : " << rawJson << std::endl;

			return parser.Entity;

		}

		

		std::string txt = rawJson.substr(0, rawJson.rfind("}"));

		txt = txt.substr(rawJson.find("{") + 1);



		// remove the array and oject effect

		parser.foldstring(txt);



		// build the object

		int currPos = 0;

		int prevPos = 0;

		while (txt.find(",", currPos) >= 0)

		{

			currPos = txt.find(",", currPos);

			parser.token = txt.substr(prevPos, currPos - prevPos);



			parser.key = parser.token.substr(0, parser.token.find(":"));

			parser.value = parser.token.substr(parser.token.find(":") + 1);



			parser.key = parser.key.substr(parser.key.find("'") + 1);

			parser.key = parser.key.substr(0, parser.key.rfind("'"));

			parser.value = parser.value.substr(parser.value.find_first_not_of(" \t\r\n"));

			parser.value = parser.value.substr(0, parser.value.find_last_not_of(" \t\r\n") + 1);



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



			currPos++;

			prevPos = currPos;

			if (currPos == 0)

				break;

		}



		parser.Entity = new JsonEntity(parser.temp_map);

	}

	else{

		parser.token = rawJson.substr(rawJson.find_first_not_of(" \t\r\n"));

		parser.token = parser.token.substr(0, parser.token.find_last_not_of(" \t\r\n") + 1);

		if (parser.token.compare("true") == 0 || parser.token.compare("TRUE") == 0){

			bool judge = 1;

			parser.Entity = new JsonEntity(judge);

		}

		else if (parser.token.compare("false") == 0 || parser.token.compare("FALSE") == 0){

			bool judge = 0;

			parser.Entity = new JsonEntity(judge);

		}

		else{

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

					parser.Entity = new JsonEntity(dnumber);

				}

				// if is intiger save as a intiger

				else{

					inumber = inumber*sign;

					parser.Entity = new JsonEntity((int)inumber);

				}



			}

		}

	}



	return parser.Entity;

}



inline

bool JsonParser::isNumber(std::string txt){

	bool decimal = false;

	bool itis = true;

	for (unsigned int i = 0; i < txt.length(); i++){

		if (txt[i] >= '0' && txt[i] <= '9'){

			itis = true;

		}

		else if (txt[i] == '-' && i == 0){

			itis = true;

		}

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