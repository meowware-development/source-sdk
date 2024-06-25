#pragma once

#include "vector.hpp"
#include "matrix.hpp"

namespace sdk::math {
	float Rad2Deg(float x);
	float Deg2Rad(float x);

	bool WorldToScreen(const Vector3& world, Vector2& screen);
	void MatrixSetColumn(Vector3& in, int column, Matrix3x4& out);
	void SinCos(float a, float* s, float* c);
	void TransformVector(Vector3 in1, Matrix3x4 in2, Vector3& out);
	void AngleMatrix(const Vector3& angles, Matrix3x4& matrix);
	void AngleMatrix(const Vector3& angles, Vector3& position, Matrix3x4& matrix);
	void AngleVectors(const Vector3& angles, Vector3* forward, Vector3* right, Vector3* up);
	Vector3 VectorAngles(const Vector3& vecDirection);
	Vector3 CalculateAngle(const Vector3 source, const Vector3 destination);
}