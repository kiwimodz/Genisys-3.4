#include <assert.h>


typedef float Vector;

#define M_PI_F		((float)(M_PI))
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

inline void SinCos(float num, float* sin, float* cos) {
	*sin = Sin(num);
	*cos = Cos(num);
}

class Vector2
{
public:
	// Members
	Vector x, y;

	// Construction/destruction
	Vector2();
	explicit Vector2(const float* pFloat);
	Vector2(float x, float y);
	// Initialization
	void Init(Vector ix = 0.0f, Vector iy = 0.0f);

	// Got any nasty NAN's?
	
	// array access...
	Vector operator[](int i) const;
	Vector& operator[](int i);

	// Base address...
	Vector* Base();
	Vector const* Base() const;

	// Initialization methods

	// equality
	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	// arithmetic operations
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(const Vector2& v);
	Vector2& operator/=(float s);

	//Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	Vector	Length() const;

	// Get the Vector2D's magnitude squared.
	Vector	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	void Lerp(Vector2 b, float t)
	{
		;
		if (t < 0.0f)
		{
			t = 0.0f;
		}
		else if (t > 1.0f)
		{
			t = 1.0f;
		}
		this->x += (b.x - this->x) * t;
		this->y += (b.y - this->y) * t;
	}
	// Normalize in place and return the old length.
	Vector	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	Vector	DistTo(const Vector2& vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	Vector	DistToSqr(const Vector2& vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2& a, const Vector2& b, float scalar);

	// Dot product.
	Vector	Dot(const Vector2& vOther) const;

	// assignment

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2(const Vector2& vOther);

	// arithmetic operations

	Vector2	operator+(const Vector2& v) const;
	Vector2	operator-(const Vector2& v) const;
	Vector2	operator*(const Vector2& v) const;
	Vector2	operator/(const Vector2& v) const;
	Vector2	operator*(float fl) const;
	Vector2	operator/(float fl) const;

	// Cross product between two vectors.

	// Returns a Vector2D with the min or max in X, Y, and Z.

#else

private:
	// No copy constructors allowed if we're in optimal mode
#endif
};

//-----------------------------------------------------------------------------
#define FLT_MAX          3.402823466e+38F

//-----------------------------------------------------------------------------
// Vector2D related operations
//-----------------------------------------------------------------------------

// Vector2D clear
void Vector2DClear(Vector2& a);

// Copy
void Vector2DCopy(const Vector2& src, Vector2& dst);

// Vector2D arithmetic
void Vector2DAdd(const Vector2& a, const Vector2& b, Vector2& result);
void Vector2DSubtract(const Vector2& a, const Vector2& b, Vector2& result);
void Vector2DMultiply(const Vector2& a, Vector b, Vector2& result);
void Vector2DMultiply(const Vector2& a, const Vector2& b, Vector2& result);
void Vector2DDivide(const Vector2& a, Vector b, Vector2& result);
void Vector2DDivide(const Vector2& a, const Vector2& b, Vector2& result);
void Vector2DMA(const Vector2& start, float s, const Vector2& dir, Vector2& result);

// Store the min or max of each of x, y, and z into the result.
void Vector2DMin(const Vector2& a, const Vector2& b, Vector2& result);
void Vector2DMax(const Vector2& a, const Vector2& b, Vector2& result);

#define Vector2DExpand( v ) (v).x, (v).y

// Normalization
Vector Vector2DNormalize(Vector2& v);

// Length
Vector Vector2DLength(const Vector2& v);

// Dot Product
Vector DotProduct2D(const Vector2& a, const Vector2& b);

// Linearly interpolate between two vectors
void Vector2DLerp(const Vector2& src1, const Vector2& src2, Vector t, Vector2& dest);

//-----------------------------------------------------------------------------
//
// Inlined Vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector2::Vector2()
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	x = y = -1;
#endif
}

inline Vector2::Vector2(const float* pFloat)
{
	//assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	//assert(IsValid());
}

//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector2::Vector2(const Vector2& vOther)
{
	//assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector2::Init(Vector ix, Vector iy)
{
	x = ix; y = iy;
	//assert(IsValid());
}


inline void Vector2DClear(Vector2& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline Vector& Vector2::operator[](int i)
{
	//assert((i >= 0) && (i < 2));
	return ((Vector*)this)[i];
}

inline Vector Vector2::operator[](int i) const
{
	//assert((i >= 0) && (i < 2));
	return ((Vector*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline Vector* Vector2::Base()
{
	return (Vector*)this;
}

inline Vector const* Vector2::Base() const
{
	return (Vector const*)this;
}

inline bool Vector2::operator==(const Vector2& src) const
{
	//assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool Vector2::operator!=(const Vector2& src) const
{
	//assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector2DCopy(const Vector2& src, Vector2& dst)
{
	//assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	Vector2::CopyToArray(float* rgfl) const
{
	//assert(IsValid());
	//assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

//inline Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta)
//{
//	Vector2 a = target - current;
//	float magnitude = sqrtf((float)(this->x * this->x + this->y * this->y));
//	Vector2 result;
//	if (magnitude <= maxDistanceDelta || magnitude == 0.0f)
//	{
//		result = target;
//	}
//	else
//	{
//		result = current + a / magnitude * maxDistanceDelta;
//	}
//	return result;
//}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector2::Negate()
{
	//assert(IsValid());
	x = -x; y = -y;
}

inline Vector2& Vector2::operator+=(const Vector2& v)
{
	//assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v)
{
	//assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline Vector2& Vector2::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	//assert(IsValid());
	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	//assert(IsValid());
	return *this;
}

inline Vector2& Vector2::operator/=(float fl)
{
	//assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	//assert(IsValid());
	return *this;
}

inline Vector2& Vector2::operator/=(const Vector2& v)
{
	//assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	//assert(IsValid());
	return *this;
}

inline void Vector2DAdd(const Vector2& a, const Vector2& b, Vector2& c)
{
	//assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DSubtract(const Vector2& a, const Vector2& b, Vector2& c)
{
	//assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2& a, Vector b, Vector2& c)
{
	//assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2& a, const Vector2& b, Vector2& c)
{
	//assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void Vector2DDivide(const Vector2& a, Vector b, Vector2& c)
{
	//assert(a.IsValid());
	//assert(b != 0.0f);
	Vector oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2& a, const Vector2& b, Vector2& c)
{
	//assert(a.IsValid());
	//assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2& start, float s, const Vector2& dir, Vector2& result)
{
	//assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector2::MulAdd(const Vector2& a, const Vector2& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2& src1, const Vector2& src2, Vector t, Vector2& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline Vector DotProduct2D(const Vector2& a, const Vector2& b)
{
	//assert(a.IsValid() && b.IsValid());
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
inline Vector Vector2::Dot(const Vector2& vOther) const
{
	return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline Vector Vector2DLength(const Vector2& v)
{
	//assert(v.IsValid());
	return (Vector)sqrtf(v.x * v.x + v.y * v.y);
}

inline Vector Vector2::LengthSqr(void) const
{
	//assert(IsValid());
	return (x * x + y * y);
}

inline Vector Vector2::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

inline bool Vector2::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val* val;
}

inline bool Vector2::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

inline Vector Vector2::Length(void) const
{
	return Vector2DLength(*this);
}


inline void Vector2DMin(const Vector2& a, const Vector2& b, Vector2& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


inline void Vector2DMax(const Vector2& a, const Vector2& b, Vector2& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline Vector Vector2DNormalize(Vector2& v)
{
	//assert(v.IsValid());
	Vector l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this Vector2D to the other one 
//-----------------------------------------------------------------------------
inline Vector Vector2::DistTo(const Vector2& vOther) const
{
	Vector2 delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline Vector Vector2::DistToSqr(const Vector2& vOther) const
{
	Vector2 delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const Vector2& vecStart, float flMaxDist, const Vector2& vecTarget, Vector2* pResult)
{
	Vector2 vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= sqrtf(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS

//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

inline Vector2 Vector2::operator+(const Vector2& v) const
{
	Vector2 res;
	Vector2DAdd(*this, v, res);
	return res;
}

inline Vector2 Vector2::operator-(const Vector2& v) const
{
	Vector2 res;
	Vector2DSubtract(*this, v, res);
	return res;
}

inline Vector2 Vector2::operator*(float fl) const
{
	Vector2 res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

inline Vector2 Vector2::operator*(const Vector2& v) const
{
	Vector2 res;
	Vector2DMultiply(*this, v, res);
	return res;
}

inline Vector2 Vector2::operator/(float fl) const
{
	Vector2 res;
	Vector2DDivide(*this, fl, res);
	return res;
}

inline Vector2 Vector2::operator/(const Vector2& v) const
{
	Vector2 res;
	Vector2DDivide(*this, v, res);
	return res;
}

inline Vector2 operator*(float fl, const Vector2& v)
{
	return v * fl;
}

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float vec[3]);

	Vector3 operator+(const Vector3 vec);
	Vector3 operator+(const float* vec);
	Vector3 operator-(const Vector3 vec);
	Vector3 operator-(const float* vec);
	Vector3 operator-() const;
	Vector3 operator*(const Vector3 vec);
	Vector3 operator*(const float scalar);

	void operator-=(const Vector3 vec);
	void operator+=(const Vector3 vec);
	void operator*=(const Vector3 vec);
	void operator*=(const float scalar);

	bool operator==(const Vector3 vec);
	bool operator==(const float value);
	bool operator!=(const Vector3 vec);
	bool operator!=(const float value);
	const Vector3& operator/ (float scale) {
		return Vector3(this->x / scale, this->y / scale, this->z / scale);
	}

	operator float* ();

	Vector3 forward(float x = 1.0f);
	Vector3 normalize();
	float distance(Vector3 vec);
	float length();
	void vectors(Vector3* forward, Vector3* right, Vector3* up);
};

class Vector4
{
public:
	float x, y, z, w;

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(float vec[4]);
	Vector4 Vector4::max_w()
	{
		this->w = 1.0f;
		return *this;
	}

	Vector4 operator+(const Vector4 vec);
	Vector4 operator+(const float* vec);
	Vector4 operator-(const Vector4 vec);
	Vector4 operator-(const float* vec);
	Vector4 operator-() const;
	Vector4 operator*(const Vector4 vec);
	Vector4 operator*(const float scalar);

	void operator-=(const Vector4 vec);
	void operator+=(const Vector4 vec);
	void operator*=(const Vector4 vec);
	void operator*=(const float scalar);

	bool operator==(const Vector4 vec);
	bool operator==(const float value);
	bool operator!=(const Vector4 vec);
	bool operator!=(const float value);

	operator float* ();
};


inline void AngleVectors_(Vector3 angles, Vector3* forward, Vector3* right, Vector3* up)
{
	float sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.x), &sp, &cp);
	SinCos(DEG2RAD(angles.z), &sr, &cr);

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

inline void vectoangles(const Vector3 value1, Vector3* angles) {
	float	forward;
	float	yaw, pitch;

	if (value1.y == 0 && value1.x == 0) {
		yaw = 0;
		if (value1.z > 0) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if (value1.x) {
			yaw = (atan2f(value1.y, value1.x) * 180 / M_PI);
		}
		else if (value1.y > 0) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if (yaw < 0) {
			yaw += 360;
		}

		forward = sqrtf(value1.x * value1.x + value1.y * value1.y);
		pitch = (atan2f(value1.z, forward) * 180 / M_PI);
		if (pitch < 0) {
			pitch += 360;
		}
	}

	angles->x = -pitch;
	angles->y = yaw;
	angles->z = 0;
}

#endif //slow

