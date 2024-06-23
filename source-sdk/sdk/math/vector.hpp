#pragma once

struct Vector3 {
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3() = default;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {

	}
};

struct Vector2 {
	float x = 0.0f, y = 0.0f;

	Vector2() = default;

	Vector2(float x, float y) : x(x), y(y) {

	}
};