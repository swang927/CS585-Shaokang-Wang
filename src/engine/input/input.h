// input.h
#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT

#include <iostream>
#include "../scene/itickable.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


namespace sgdi
{
enum class InputType
{
	UNKNOWN = -1,
	// KEYBOARD BUTTONS
	A_KEY = 0,
	B_KEY,
	C_KEY,
	D_KEY,
	E_KEY,
	F_KEY,
	G_KEY,
	H_KEY,
	I_KEY,
	J_KEY,
	K_KEY,
	L_KEY,
	M_KEY,
	N_KEY,
	O_KEY,
	P_KEY,
	Q_KEY,
	R_KEY,
	S_KEY,
	T_KEY,
	U_KEY,
	V_KEY,
	W_KEY,
	X_KEY,
	Y_KEY,
	Z_KEY,
	NUM0_KEY,
	NUM1_KEY,
	NUM2_KEY,
	NUM3_KEY,
	NUM4_KEY,
	NUM5_KEY,
	NUM6_KEY,
	NUM7_KEY,
	NUM8_KEY,
	NUM9_KEY,
	ESCAPE_KEY,
	LCONTROL_KEY,
	LSHIFT_KEY,
	LALT_KEY,
	LSYSTEM_KEY,
	RCONTROL_KEY,
	RSHIFT_KEY,
	RALT_KEY,
	RSYSTEM_KEY,
	MENU_KEY,
	LBRACKET_KEY,
	RBRACKET_KEY,
	SEMICOLON_KEY,
	COMMA_KEY,
	PERIOD_KEY,
	QUOTE_KEY,
	SLASH_KEY,
	BACKSLASH_KEY,
	TILDE_KEY,
	EQUAL_KEY,
	DASH_KEY,
	SPACE_KEY,
	RETURN_KEY,
	BACKSPACE_KEY,
	TAB_KEY,
	PAGEUP_KEY,
	PAGEDOWN_KEY,
	END_KEY,
	HOME_KEY,
	INSERT_KEY,
	DELETE_KEY,
	ADD_KEY,
	SUBTRACT_KEY,
	MULTIPLY_KEY,
	DIVIDE_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	UP_KEY,
	DOWN_KEY,
	NUMPAD0_KEY,
	NUMPAD1_KEY,
	NUMPAD2_KEY,
	NUMPAD3_KEY,
	UMPAD4_KEY,
	NUMPAD5_KEY,
	NUMPAD6_KEY,
	NUMPAD7_KEY,
	NUMPAD8_KEY,
	NUMPAD9_KEY,
	F1_KEY,
	F2_KEY,
	F3_KEY,
	F4_KEY,
	F5_KEY,
	F6_KEY,
	F7_KEY,
	F8_KEY,
	F9_KEY,
	F10_KEY,
	F11_KEY,
	F12_KEY,
	F13_KEY,
	F14_KEY,
	F15_KEY,
	PAUSE_KEY,
	// MOUSE BUTTONS
	LEFT_MOUSE,
	RIGHT_MOUSE,
	MIDDLE_MOUSE,
	XBUTTON1_MOUSE,
	XBUTTON2_MOUSE,
	INPUT_COUNT,
	KEY_COUNT,
	MOUSE_COUNT
};

// A lightweight wrapper around SFML’s input implementation
class Input : public sgds::ITickable {
  private:
	// a record for key state 
	struct _KeyState{
		bool isPressed;
		bool wasPressed;
	};

	// key states.
	_KeyState d_keyStates[(int)InputType::INPUT_COUNT];

	//Constructors
	Input();

	// disable all constructors in a singleton class.
	Input(const Input &) = delete;
	Input(Input &&) = delete;
	// disable assignment in a singleton class.
	Input& operator = (const Input &) = delete;
	Input& operator = (Input &&) = delete;

  public:
	// access singleton thrpugh this.
	static Input& inst();
	// Poll input state at this point, setup internal state
	void preTick() override;
	void tick(float dtS) override;
	void postTick() override;

	// is current state down
	bool isDown(InputType input_type);
	// is current state up
	bool isUp(InputType input_type); 
	// was down and now is up
	bool wasPressed(InputType input_type); 	
};

// constructor
inline
Input::Input(){
	int size = (int)InputType::INPUT_COUNT;
	for (int i = 0; i < size; ++i)
	{
		d_keyStates[i].isPressed = false;
		d_keyStates[i].wasPressed = false;
	}
};

inline
Input& Input::inst(){
	static Input inst;
	return inst;
}

// MEMBER FUNCTIONS
inline
void Input::preTick()
{
	int keySize = sf::Keyboard::KeyCount;
	int mouseSize = sf::Mouse::ButtonCount;
	for (int i = 0; i < keySize; ++i)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) i))
		{
			// if last frame is pressed.
			if (d_keyStates[i].isPressed)
			{
				d_keyStates[i].wasPressed = true;
			}
			d_keyStates[i].isPressed = true;
		}
		else
		{
			// if last frame is not press.
			if (!d_keyStates[i].isPressed)
			{
				d_keyStates[i].wasPressed = false;
			}
			d_keyStates[i].isPressed = false;
		}
	}

	for (int i = (int)InputType::LEFT_MOUSE; i < (int)InputType::LEFT_MOUSE + mouseSize; ++i)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button) (i - (int)InputType::LEFT_MOUSE)))
		{
			// if last frame is pressed.
			if (d_keyStates[i].isPressed)
			{
				d_keyStates[i].wasPressed = true;
			}
			d_keyStates[i].isPressed = true;
		}
		else
		{
			// if last frame is not press.
			if (!d_keyStates[i].isPressed)
			{
				d_keyStates[i].wasPressed = false;
			}
			d_keyStates[i].isPressed = false;
		}
	}

}

inline
void Input::tick(float dtSec){
}

inline
void Input::postTick(){
}

inline
bool Input::isDown(InputType input_type){
/*	switch (input_type)
	{
	case InputType::A:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	case InputType::B:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::B);
	case InputType::C:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::C);
	case InputType::D:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	case InputType::E:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	case InputType::F:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F);
	case InputType::G:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::G);
	case InputType::H:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::H);
	case InputType::I:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::I);
	case InputType::J:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::J);
	case InputType::K:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::K);
	case InputType::L:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::L);
	case InputType::M:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::M);
	case InputType::N:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::N);
	case InputType::O:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::O);
	case InputType::P:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::P);
	case InputType::Q:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
	case InputType::R:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::R);
	case InputType::S:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	case InputType::T:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::T);
	case InputType::U:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::U);
	case InputType::V:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::V);
	case InputType::W:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	case InputType::X:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::X);
	case InputType::Y:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
	case InputType::Z:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	case InputType::Escape:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	case InputType::LControl:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
	case InputType::LShift:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	case InputType::LAlt:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
	case InputType::LSystem:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem);

	case InputType::RControl:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
	case InputType::RShift:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	case InputType::RAlt:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
	case InputType::RSystem:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
	case InputType::Menu:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Menu);

	case InputType::LBracket:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket);
	case InputType::RBracket:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket);
	case InputType::SemiColon:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon);
	case InputType::Comma:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Comma);
	case InputType::Period:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Period);
	case InputType::Quote:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Quote);
	case InputType::Slash:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Slash);

	case InputType::BackSlash:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash);
	case InputType::Tilde:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
	case InputType::Equal:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Equal);
	case InputType::Dash:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Dash);
	case InputType::Space:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	case InputType::Return:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
	case InputType::BackSpace:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
	case InputType::Tab:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
	case InputType::PageUp:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp);

	case InputType::PageDown:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown);
	case InputType::End:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::End);
	case InputType::Home:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Home);
	case InputType::Insert:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Insert);
	case InputType::Delete:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Delete);

	case InputType::Add:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Add);
	case InputType::Subtract:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
	case InputType::Multiply:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply);
	case InputType::Divide:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Divide);
	case InputType::Left:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	case InputType::Right:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	case InputType::Up:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	case InputType::Down:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	case InputType::Num0:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num0);
	case InputType::Num1:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
	case InputType::Num2:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
	case InputType::Num3:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
	case InputType::Num4:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
	case InputType::Num5:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num5);
	case InputType::Num6:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num6);
	case InputType::Num7:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num7);
	case InputType::Num8:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num8);
	case InputType::Num9:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num9);

	
	case InputType::F1:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
	case InputType::F2:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
	case InputType::F3:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
	case InputType::F4:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F4);
	case InputType::F5:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
	case InputType::F6:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F6);
	case InputType::F7:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F7);
	case InputType::F8:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F8);
	case InputType::F9:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F9);
	case InputType::F10:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F10);
	case InputType::F11:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F11);
	case InputType::F12:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F12);
	case InputType::F13:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F13);
	case InputType::F14:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F14);
	case InputType::F15:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::F15);
	case InputType::Pause:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Pause);
	case InputType::KeyCount:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::KeyCount);

	case InputType::LEFT_MOUSE:
		return sf::Mouse::isButtonPressed(sf::Mouse::Left);
	case InputType::RIGHT_MOUSE:
		return sf::Mouse::isButtonPressed(sf::Mouse::Right);
	}
	return false;
*/
	return d_keyStates[(int)input_type].isPressed == true;
}

inline
bool Input::isUp(InputType input_type){

	return d_keyStates[(int)input_type].isPressed == false;
}

inline
bool Input::wasPressed(InputType input_type){
	return (d_keyStates[(int)input_type].isPressed == false
		&& d_keyStates[(int)input_type].wasPressed == true);
}

};
#endif