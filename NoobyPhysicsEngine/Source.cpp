#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "VectorOperations.h"
#include "SeparatingAxisTheorem.h"

//Implementing the SAT (Separating Axis Theorem)

//Basic Bounding Shape Collision Detection Methods
bool CheckAABBDetection(const RectangleShape& BoxA, const RectangleShape& BoxB);
bool CheckBoundingCircleDetection(const CircleShape& circleA, const CircleShape& circleB);

//A helper function to get the vector's magnitude
float GetMagnitude(const Vector2f& vector);

int main()
{
	//Created a 500 x 500 window
	const int screenWidth = 500;
	const int screenHeight = 500;
	RenderWindow window(VideoMode(screenWidth, screenHeight), "AABB Test");

	//My Block that I would like to control
	RectangleShape myBlock(Vector2f(30.0f, 30.0f));
	myBlock.setFillColor(Color::Magenta);
	myBlock.setOrigin(myBlock.getLocalBounds().width / 2, myBlock.getLocalBounds().height / 2);
	myBlock.setPosition(screenWidth / 2, screenHeight / 2);

	//The block we should bump into
	RectangleShape floor(Vector2f(100.0f, 20.0f));
	floor.setFillColor(Color::Green);
	floor.setOrigin(floor.getLocalBounds().width / 2, floor.getLocalBounds().height / 2);
	floor.setPosition(screenWidth / 2, (screenHeight / 2) + 100);

	CheckSATDetection(myBlock, floor);

	//Game Loop
	while (window.isOpen())
	{
		//Window events code only put in this loop
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Get Player's input and move myBlock in the proper direction
#pragma region Input_Code
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			myBlock.move(-0.1f, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			myBlock.move(0, 0.1f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			myBlock.move(0.1f, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			myBlock.move(0, -0.1f);
		}
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			myBlock.rotate(2.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			myBlock.rotate(-2.0f);
		}
#pragma endregion
		//If they collide, turn blue
		//otherwise, turn back to their original color
		if (CheckSATDetection(myBlock, floor))
		{
			myBlock.setFillColor(Color::Blue);
			floor.setFillColor(Color::Blue);
		}
		else
		{
			myBlock.setFillColor(Color::Magenta);
			floor.setFillColor(Color::Green);
		}

		//Refresh and Display the shapes
		window.clear();
		window.draw(floor);
		window.draw(myBlock);
		window.display();
	}
	window.close();
	return 0;
}


bool CheckAABBDetection(const RectangleShape& BoxA, const RectangleShape& BoxB)
{
	//Get the distance
	Vector2f distance = BoxA.getPosition() - BoxB.getPosition();

	//Get the X Extents of the Boxes
	float xExtent_A = BoxA.getSize().x / 2;
	float xExtent_B = BoxB.getSize().x / 2;
	float xOverlap = (xExtent_A + xExtent_B) - std::abs(distance.x);

	if (xOverlap < 0.0) { return false; }

	//Get the Y Extent of the Boxes
	float yExtent_A = BoxA.getSize().y / 2;
	float yExtent_B = BoxB.getSize().y / 2;

	float yOverlap = (yExtent_A + yExtent_B) - std::abs(distance.y);

	//Extra: Figure out which side of the box are we colliding in
	if (yOverlap > xOverlap)
	{
		(distance.x > 0) ? std::cout << "Right Side\n" : std::cout << "Left Side\n";
	}
	else
	{
		(distance.y > 0) ? std::cout << "Bottom Side\n" : std::cout << "Top Side\n";
	}

	return (yOverlap > 0.0f) ? true : false;
}

bool CheckBoundingCircleDetection(const CircleShape& circleA, const CircleShape& circleB)
{
	//Get the distance & its magnitude
	float distance = GetMagnitude(circleB.getPosition() - circleA.getPosition());

	//Two circles collide if their combined radius is less than 
	//the distance between their centers
	return ((circleA.getRadius() + circleB.getRadius()) >= distance) ? true : false;
}