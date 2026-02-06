//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Vector2 Defaults on floats
struct exVector2
{
	float x, y;

	exVector2() :x(0.0f), y(0.0f) 
	{
	};

	exVector2(float InX, float InY) : x(InX), y(InY)
	{
	}

	// when using structs we can creater operators to add and multiplty objects
	exVector2 operator+=(const exVector2& OtherVector)
	{
		x += OtherVector.x;
		y += OtherVector.y;

		return *this;
	}

	exVector2 operator-=(const exVector2& OtherVector)
	{
		x -= OtherVector.x;
		y -= OtherVector.y;

		return *this;
	}

	exVector2 operator+(const exVector2& OtherVector)
	{
		exVector2 Result(x + OtherVector.x, y + OtherVector.y);

		return Result;
	}

	exVector2 operator-(const exVector2& OtherVector)
	{
		exVector2 Result(x - OtherVector.x, y - OtherVector.y);

		return Result;
	}

	exVector2 operator*(const float OtherFloat)
	{
		exVector2 Result(x * OtherFloat, y * OtherFloat);

		return Result;
	}

	exVector2 operator*=(const float OtherFloat)
	{
		x *= OtherFloat;
		y *= OtherFloat;

		return *this;
	}

	// TODO: Add Cross and Dot product
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// You might want to use this if you create something like Snake.
struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4]; // Unsigned - cannot take negative characters

	// There are 4
	// R - Red
	// G - Green
	// B - Blue
	// A - Alpha
};
