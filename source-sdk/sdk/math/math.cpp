#include "math.hpp"
#include "../../utils/renderer/renderer.hpp"
#include "../interfaces/interfaces.hpp"

constexpr auto M_PI = 3.14159265358979323846;
constexpr auto M_PI_F = 3.14159265358979323846f;
constexpr auto M_PHI = 1.61803398874989484820;
constexpr auto M_RADPI = 57.295779513082f;

float sdk::math::Rad2Deg(float x) {
	return ((float)(x) * (float)(180.f / M_PI_F));
}

float sdk::math::Deg2Rad(float x) {
	return ((float)(x) * (float)(M_PI_F / 180.f));
}

// Get 2D Point from 3D Point
bool sdk::math::WorldToScreen(const Vector3& world, Vector2& screen) {
	const Matrix4x4& matrix = sdk::interfaces::engine->WorldToScreenMatrix();

	const float flWidth = matrix[3][0] * world.x + matrix[3][1] * world.y + matrix[3][2] * world.z + matrix[3][3];

	if (flWidth < 0.001f)
		return false;

	const float flInverse = 1.0f / flWidth;
	screen.x = (matrix[0][0] * world.x + matrix[0][1] * world.y + matrix[0][2] * world.z + matrix[0][3]) * flInverse;
	screen.y = (matrix[1][0] * world.x + matrix[1][1] * world.y + matrix[1][2] * world.z + matrix[1][3]) * flInverse;

	screen.x = (utils::renderer::screenWidth * 0.5f) + (screen.x * utils::renderer::screenWidth) * 0.5f;
	screen.y = (utils::renderer::screenHeight * 0.5f) - (screen.y * utils::renderer::screenHeight) * 0.5f;

	return true;
}

void sdk::math::MatrixSetColumn(Vector3& in, int column, Matrix3x4& out) {
	out[0][column] = in.x;
	out[1][column] = in.y;
	out[2][column] = in.z;
}

void sdk::math::SinCos(float a, float* s, float* c) {
	*s = sin(a);
	*c = cos(a);
}

void sdk::math::TransformVector(Vector3 in1, Matrix3x4 in2, Vector3& out) {
	out = Vector3(in1.Dot(Vector3(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3], in1.Dot(Vector3(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3], in1.Dot(Vector3(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3]);
}

void sdk::math::AngleMatrix(const Vector3& angles, Matrix3x4& matrix) {
	float sr, sp, sy, cr, cp, cy;

	SinCos(Deg2Rad(angles.y), &sy, &cy);
	SinCos(Deg2Rad(angles.x), &sp, &cp);
	SinCos(Deg2Rad(angles.z), &sr, &cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;
	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

void sdk::math::AngleMatrix(const Vector3& angles, Vector3& position, Matrix3x4& matrix) {
	AngleMatrix(angles, matrix);
	MatrixSetColumn(position, 3, matrix);
}

void sdk::math::AngleVectors(const Vector3& angles, Vector3* forward, Vector3* right, Vector3* up) {
	float sr, sp, sy, cr, cp, cy;

	SinCos(Deg2Rad(angles.x), &sy, &cy);
	SinCos(Deg2Rad(angles.y), &sp, &cp);
	SinCos(Deg2Rad(angles.z), &sr, &cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

Vector3 sdk::math::VectorAngles(const Vector3& vecDirection) {
	float fPitch, fYaw = 0.f;

	if (vecDirection.x && vecDirection.y) {
		fPitch = Rad2Deg(std::atan2f(-vecDirection.z, vecDirection.Length2D()));
		fPitch += fPitch < 0.f ? 360.f : 0.f;

		fYaw = Rad2Deg(std::atan2f(vecDirection.y, vecDirection.x));
		fYaw += fYaw < 0.f ? 360.f : 0.f;
	}
	else {
		fPitch = vecDirection.z > 0.f ? 270.f : 90.f;
	}

	return Vector3(fPitch, fYaw, 0.f);
}

// Used to calculate angle between 2 3D points (Use this in aimbot)
Vector3 sdk::math::CalculateAngle(const Vector3 source, const Vector3 destination) {
	Vector3 angles = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 delta = (source - destination);
	float fHyp = sqrt((delta.x * delta.x) + (delta.y * delta.y));

	angles.x = (atanf(delta.z / fHyp) * M_RADPI);
	angles.y = (atanf(delta.y / delta.x) * M_RADPI);
	angles.z = 0.0f;

	if (delta.x >= 0.0f)
		angles.y += 180.0f;

	return angles;
}