#pragma once

namespace Sampo
{
	enum class ButtonKeyState
	{
		kUp = 0,
		kFalling,
		kDown
	};

	enum class MouseButton
	{
		kUnknownButton = 0,
		kButton1,
		kButton2,
		kButton3,
		kButton4,
		kButton5,
		kButton6,
		kButton7,
		kButton8,

		kLeft = kButton1,
		kMiddle = kButton3,
		kRight = kButton2,
	};

	enum class KeyboardButton
	{
		kUnknownButton = 0,
		kSPACE,
		kAPOSTROPHE,
		kCOMMA,
		kMINUS,
		kPERIOD,
		kSLASH,
		k0,
		k1,
		k2,
		k3,
		k4,
		k5,
		k6,
		k7,
		k8,
		k9,
		kSEMICOLON,
		kEQUAL,
		kA,
		kB,
		kC,
		kD,
		kE,
		kF,
		kG,
		kH,
		kI,
		kJ,
		kK,
		kL,
		kM,
		kN,
		kO,
		kP,
		kQ,
		kR,
		kS,
		kT,
		kU,
		kV,
		kW,
		kX,
		kY,
		kZ,
		kLEFT_BRACKET,
		kBACKSLASH,
		kRIGHT_BRACKET,
		kGRAVE_ACCENT,
		kWorld1,
		kWorld2,
		kESCAPE,
		kENTER,
		kTAB,
		kBACKSPACE,
		kINSERT,
		kDELETE,
		kRIGHT,
		kLEFT,
		kDOWN,
		kUP,
		kPAGE_UP,
		kPAGE_DOWN,
		kHOME,
		kEND,
		kCAPS_LOCK,
		kSCROLL_LOCK,
		kNUM_LOCK,
		kPRINT_SCREEN,
		kPAUSE,
		kF1,
		kF2,
		kF3,
		kF4,
		kF5,
		kF6,
		kF7,
		kF8,
		kF9,
		kF10,
		kF11,
		kF12,
		kKP_0,
		kKP_1,
		kKP_2,
		kKP_3,
		kKP_4,
		kKP_5,
		kKP_6,
		kKP_7,
		kKP_8,
		kKP_9,
		kKP_DECIMAL,
		kKP_DIVIDE,
		kKP_MULTIPLY,
		kKP_SUBTRACT,
		kKP_ADD,
		kKP_ENTER,
		kKP_EQUAL,
		kLEFT_SHIFT,
		kLEFT_CONTROL,
		kLEFT_ALT,
		kLEFT_SUPER,
		kRIGHT_SHIFT,
		kRIGHT_CONTROL,
		kRIGHT_ALT,
		kRIGHT_SUPER,
		kMENU
	};

	enum class GamepadAxis
	{
		kUnknown = 0,
		kLeftX,
		kLeftY,
		kRightX,
		kRightY,
		kLeftTrigger,
		kRightTrigger
	};

	enum class GamepadButton
	{
		kUnknown = 0,
		kActionDown,
		kActionRight,
		kActionLeft,
		kActionUp,
		kLeftBumper,
		kRightBumper,
		kSelect,
		kStart,
		kHome,
		kLeftStick,
		kRightStick,
		kDpadUp,
		kDpadLeft,
		kDpadDown,
		kDpadRight,
	};
}