#ifndef _MATHLIB_H_
#define _MATHLIB_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>



// 2 Dimentional Vector Math
class Vector2
{
public:
	float scalar;
	float x, y;
	Vector2();
	Vector2(float a_x, float a_y);
	Vector2(Vector2& a_RHS);
	~Vector2();
	Vector2 operator+(Vector2& other);
	Vector2 operator-(Vector2& other);
	Vector2 operator*(float a_scalar);
	Vector2 operator*(Vector2& other);
	void operator=(Vector2& other);

	bool operator==(Vector2& a_RHS);
	Vector2 operator+=(Vector2& a_RHS);
	Vector2 operator-=(Vector2& a_RHS);
	Vector2 operator*=(Vector2& a_RHS);
	

	float Magnitude();
	void Normalise();
	Vector2 GetNormal();
	float VectorDistance(Vector2& other);
	float DotProduct(Vector2& other);
	Vector2 CrossProduct(Vector2& a_RHS);
	Vector2 Lerp(Vector2& end, const float percentage);
	static Vector2 Lerp(Vector2& begin, Vector2& end, const float percentage);
};
// 3 Dimentional Vector Math
class Vector3
{
public:
	float x, y, z;
	float scalar;
	Vector3();
	Vector3(float a_x, float a_y, float a_z);
	~Vector3();
	Vector3 operator+(Vector3 &other);
	Vector3 operator-(Vector3 &other);
	Vector3 operator*(float a_scalar);
	Vector3 operator*(Vector3 &other);
	void operator=(Vector3 &other);

	bool operator==(Vector3& a_RHS);

	float Magnitude();
	void Normalise();
	Vector3 GetNormal();
	float VectorDistance(Vector3 &other);
	float DotProduct(Vector3 &other);
	Vector3 CrossProduct(Vector3& a_RHS);
	Vector3 Lerp(Vector3& end, const float percentage);
	static Vector3 Lerp(Vector3& begin, Vector3& end, const float percentage);

};
// 2 Dimentional Matrix Math
class Matrix3
{
public:
	Matrix3();
	Matrix3(float const m00, float const m01, float const m02,
			float const m10, float const m11, float const m12,
			float const m20, float const m21, float const m22);
	Matrix3(Matrix3& a_RHS);

	~Matrix3();

	void Identity();

	Matrix3& Transpose();

	Matrix3 GetTranspose();


	Matrix3& operator =(const Matrix3& a_RHS);
	Matrix3 operator +(Matrix3& a_RHS);
	Matrix3 operator -(Matrix3& a_RHS);
	Matrix3 operator *(Matrix3& a_RHS);

	bool operator ==(Matrix3& a_RHS);
	Matrix3 operator +=(Matrix3& a_RHS);
	Matrix3 operator -=(Matrix3& a_RHS);
	Matrix3 operator *=(Matrix3& a_RHS);

	Matrix3 GetTranslationMatrix(Vector2& a_RHS);
	Matrix3 GetRotationMatrix(float theta);

	float m_matrixArray[3][3];

};
// 3 dimentional Matrix Math
class Matrix4
{
public:
	Matrix4();
	Matrix4(float const m00, float const m01, float const m02, float const m03,
			float const m10, float const m11, float const m12, float const m13,
			float const m20, float const m21, float const m22, float const m23,
			float const m30, float const m31, float const m32, float const m33);
	Matrix4(Matrix4& a_RHS);
	void Identity();
	Matrix4 OrthoProjection(const float right, const float left, const float top, const float bottom, const float a_far, const float a_near);
	static float* GetOrtho(const float right, const float left, const float top, const float bottom, const float a_far, const float a_near);

	bool operator==(Matrix4& a_RHS);
	Matrix4 operator=(Matrix4& a_RHS);
	friend std::ostream& operator<<(std::ostream& out, Matrix4& a_RHS);
	Matrix4 operator+(Matrix4& a_RHS);
	Matrix4 operator-(Matrix4& a_RHS);
	Matrix4 operator*(Matrix4& a_RHS);
	
	
	float m_matrixArray[4][4];
	~Matrix4();
};
// Vector 4 Math
class Vector4
{
public:
	float x, y, z, w;
	Vector4(){ x = 0.f; y = 0.f; z = 0.f; w = 0.f; }
	Vector4(float a_x, float a_y, float a_z, float a_w);
	void operator=(Vector4& a_RHS);
	bool operator==(Vector4& a_RHS);
	friend std::ostream& operator<<(std::ostream& out, Vector4& a_RHS);
	Vector4 operator+(Vector4& a_RHS);
	Vector4 operator-(Vector4& a_RHS);
	Vector4 operator*(float a_scalar);
	Vector4 operator*(Vector4& a_RHS);

	~Vector4(){}
	float DotProduct(Vector4& a_RHS);
	float Magnitude();
	void Normalise();


};
//Misc Math
class MiscMath
{
public:
	/*percent between 0 and 1*/
	static float LERP(float begin, float end, float percent){ return begin + (end - begin) * percent; }
	static float degreesToRadians(float angleInDegs);
	static float radiansToDegrees(float angleInRads);
};
#endif