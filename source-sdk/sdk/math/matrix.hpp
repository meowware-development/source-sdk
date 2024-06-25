#pragma once

struct Matrix4x4 {
	float values[4][4];

	float* operator[](int i) { return values[i]; }
	const float* operator[](int i) const { return values[i]; }
	float* Base() { return &values[0][0]; }
	const float* Base() const { return &values[0][0]; }
};

struct Matrix3x4 {
	float values[3][4];

	float* operator[](int i) { return values[i]; }
	const float* operator[](int i) const { return values[i]; }
	float* Base() { return &values[0][0]; }
	const float* Base() const { return &values[0][0]; }
};