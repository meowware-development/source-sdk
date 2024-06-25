#pragma once

#include <cmath>
#include <algorithm>
#include <numbers>

class Vector3 {
public:
	float x = 0.f, y = 0.0f, z = 0.0f;

	Vector3() = default;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

	Vector3& operator=(Vector3 const& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	bool operator==(Vector3& other) const
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	bool operator!=(Vector3& other) const
	{
		return (this->x != other.x && this->y != other.y && this->z != other.z);
	}

	Vector3 operator+(const Vector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3 operator+=(const Vector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3 operator-(const Vector3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector3 operator-(const Vector3& other) const
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 operator-=(const Vector3& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vector3 operator*(const Vector3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vector3 operator*(const float& multiplier)
	{
		this->x *= multiplier;
		this->y *= multiplier;
		this->z *= multiplier;
		return *this;
	}

	Vector3 operator/(const Vector3& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}

	Vector3 operator/(float const& divider)
	{
		this->x /= divider;
		this->y /= divider;
		this->z /= divider;
		return *this;
	}

	Vector3 operator/=(float const& divider)
	{
		this->x /= divider;
		this->y /= divider;
		this->z /= divider;
		return *this;
	}

	void NormalizeAngles()
	{
		x = std::isfinite(x) ? std::remainderf(x, 360.0f) : 0.0f;
		y = std::isfinite(y) ? std::remainderf(y, 360.0f) : 0.0f;
		z = 0.0f;
	}

	float NormalizeVector()
	{
		float length = Length();

		if (length)
			*this /= length;

		return length;
	}

	Vector3 Normalized()
	{
		Vector3 vec(*this);
		vec.NormalizeAngles();
		return vec;
	}

	void Clamp()
	{
		x = std::clamp(x, -89.0f, 89.0f);
		y = std::clamp(std::remainder(y, 360.0f), -180.0f, 180.0f);
		z = std::clamp(z, -50.0f, 50.0f);
	}

	Vector3 Clamped()
	{
		Vector3 clamped = *this;
		clamped.Clamp();
		return clamped;
	}

	float Length()
	{
		return sqrtf(LengthSqr());
	}

	float LengthSqr()
	{
		return (x * x + y * y + z * z);
	}

	float Length2DSqr() const
	{
		return (x * x + y * y);
	}

	float Length2D() const
	{
		return sqrtf(Length2DSqr());
	}

	float Dot(const Vector3 other)
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	float Dot(const float* other)
	{
		const Vector3& a = *this;

		return(a.x * other[0] + a.y * other[1] + a.z * other[2]);
	}

	float DistanceTo(const Vector3 other)
	{
		Vector3 delta;
		delta.x = x - other.x;
		delta.y = y - other.y;
		delta.z = z - other.z;

		return delta.Length();
	}
};

class Vector2 {
public:
	float x = 0.f;
	float y = 0.f;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {};

	void operator=(Vector2 const& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	bool operator==(Vector2& other) const
	{
		return (this->x == other.x && this->y == other.y);
	}

	bool operator!=(Vector2& other) const {
		return (this->x != other.x && this->y != other.y);
	}

	Vector2 operator+(Vector2 const& other)
	{
		Vector2 result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;
		return result;
	}

	Vector2 operator-(Vector2 const& other)
	{
		Vector2 result;
		result.x = this->x - other.x;
		result.y = this->y - other.y;
		return result;
	}

	Vector2 operator*(Vector2 const& other)
	{
		Vector2 result;
		result.x = this->x * other.x;
		result.y = this->y * other.y;
		return result;
	}

	Vector2 operator/(Vector2 const& other)
	{
		Vector2 result;
		result.x = this->x / other.x;
		result.y = this->y / other.y;
		return result;
	}
};