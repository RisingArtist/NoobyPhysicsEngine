#pragma once

float DotProduct(const Vector2f& vec1, const Vector2f& vec2);
float GetMagnitude(const Vector2f& vector);
void GetNormals(const RectangleShape& box, Vector2f normals[]);
void Normalize(Vector2f& vec);

//Perform the dot product between two 2D vectors
float DotProduct(const Vector2f& vec1, const Vector2f& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

//Get the Magnitude of the given vector
float GetMagnitude(const Vector2f& vector)
{
	return std::sqrtf(vector.x * vector.x + vector.y * vector.y);
}

//Retrieve the normals of the Rectangle
void GetNormals(const RectangleShape& box, Vector2f normals[])
{
	for (int i = 0; i < box.getPointCount(); i++)
	{
		int j = i + 1;
		j %= box.getPointCount();

		Vector2f temp = Vector2f(
			box.getTransform().transformPoint(box.getPoint(j)).y - box.getTransform().transformPoint(box.getPoint(i)).y,
			box.getTransform().transformPoint(box.getPoint(j)).x - box.getTransform().transformPoint(box.getPoint(i)).x
		);

		if (temp.y != 0)
			temp.y *= -1;

		Normalize(temp);
		normals[i] = temp;
	}
}

//Turns the given vector into a Unit Vector 
void Normalize(Vector2f& vec)
{
	float magnitude = GetMagnitude(vec);
	if (magnitude > 0)
		magnitude = 1 / magnitude;

	vec.x *= magnitude;
	vec.y *= magnitude;
}


