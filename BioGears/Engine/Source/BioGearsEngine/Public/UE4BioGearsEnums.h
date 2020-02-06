#pragma once

//!
//! Implementation of Seraliztion layer structs for use 
//!

namespace biogears {

	enum class eBloodType
	{
		O_Negitive,
		O_Positive,
		A_Negitive,
		A_Positive,
		B_Negative,
		B_Positive,
		A_B_Negative,
		A_B_Positive
	};

	enum class eInfectionSeverity
	{
		Eliminated,
		Mild,
		Moderate,
		Severe
	};

	enum class eSide
	{
		Left,
		Right
	};

	enum class  ePneumothorax
	{
		Open,
		Closed
	};

	enum class eTourniquet
	{
		Applied,
		Misapplied,
		None
	};

	enum class eExtremity
	{
		LeftLeg,
		RightLeg,
		LeftArm,
		RightArm,
	};

	enum class eCompartment
	{
		LeftLeg,
		RightLeg,
		LeftArm,
		RightArm,
	};

	enum class eUrineColor
	{
		PaleYellow,
		Yellow,
		DarkYellow,
		Pink
	};
}