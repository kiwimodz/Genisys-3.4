#include <Includes.h>

Vector3::Vector3()
{
	this->x = this->y = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float vec[3])
{
	if (vec != 0)
	{
		this->x = vec[0];
		this->y = vec[1];
		this->z = vec[2];
	}
	else
	{
		this->x = this->y = this->z = 0;
	}
}

Vector3 Vector3::operator+(const Vector3 vec)
{
	return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vector3 Vector3::operator+(const float* vec)
{
	return Vector3(this->x + vec[0], this->y + vec[1], this->z + vec[2]);
}

Vector3 Vector3::operator-(const Vector3 vec)
{
	return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

Vector3 Vector3::operator-(const float* vec)
{
	return Vector3(this->x - vec[0], this->y - vec[1], this->z - vec[2]);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const Vector3 vec)
{
	return Vector3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

Vector3 Vector3::operator*(const float scalar)
{
	return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

void Vector3::operator-=(const Vector3 vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
}

void Vector3::operator+=(const Vector3 vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}

void Vector3::operator*=(const Vector3 vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
}

void Vector3::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}

bool Vector3::operator==(const Vector3 vec)
{
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

bool Vector3::operator==(const float value)
{
	return (this->x == value && this->y == value && this->z == value);
}

bool Vector3::operator!=(const Vector3 vec)
{
	return !operator==(vec);
}

bool Vector3::operator!=(const float value)
{
	return !operator==(value);
}

Vector3::operator float* ()
{
	return (float*)&this[0];
}

Vector3 Vector3::forward(float x)
{
	float div = M_PI / 180.0f;

	float angle = this->y * div;
	float sy = sinf(angle);
	float cy = cosf(angle);

	angle = this->x * div;
	float sp = sinf(angle);
	float cp = cosf(angle);

	return Vector3(cp * cy * x, cp * sy * x, -sp * x);
}

Vector3 Vector3::normalize()
{
	Vector3 newvec;
	newvec.x = this->x / length();
	newvec.y = this->y / length();
	newvec.z = this->z / length();
	return newvec;
}
float Vector3::length()
{
	return (float)sqrtf(x * x + y * y + z * z);
}

float Vector3::distance(Vector3 vec)
{
	float _x = this->x - vec.x;
	float _y = this->y - vec.y;
	float _z = this->z - vec.z;
	return sqrtf((_x * _x) + (_y * _y) + (_z * _z));
}


void Vector3::vectors(Vector3* forward, Vector3* right, Vector3* up)
{
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = this->y * (M_PI * 2.0f / 360.0f);
	sy = sinf(angle);
	cy = cosf(angle);

	angle = this->x * (M_PI * 2.0f / 360.0f);
	sp = sinf(angle);
	cp = cosf(angle);

	angle = this->z * (M_PI * 2.0f / 360.0f);
	sr = sinf(angle);
	cr = cosf(angle);

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



Vector4::Vector4()
{
	this->x = this->y = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float vec[4])
{
	if (vec != 0)
	{
		this->x = vec[0];
		this->y = vec[1];
		this->z = vec[2];
		this->w = vec[3];
	}
	else
	{
		this->x = this->y = this->z = this->w = 0;
	}
}

Vector4 Vector4::operator+(const Vector4 vec)
{
	return Vector4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
}

Vector4 Vector4::operator+(const float* vec)
{
	return Vector4(this->x + vec[0], this->y + vec[1], this->z + vec[2], this->w + vec[3]);
}

Vector4 Vector4::operator-(const Vector4 vec)
{
	return Vector4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
}

Vector4 Vector4::operator-(const float* vec)
{
	return Vector4(this->x - vec[0], this->y - vec[1], this->z - vec[2], this->w - vec[3]);
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(const Vector4 vec)
{
	return Vector4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
}

Vector4 Vector4::operator*(const float scalar)
{
	return Vector4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}

void Vector4::operator-=(const Vector4 vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
}

void Vector4::operator+=(const Vector4 vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
}

void Vector4::operator*=(const Vector4 vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;
}

void Vector4::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;
}

bool Vector4::operator==(const Vector4 vec)
{
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w);
}

bool Vector4::operator==(const float value)
{
	return (this->x == value && this->y == value && this->z == value && this->w == value);
}

bool Vector4::operator!=(const Vector4 vec)
{
	return !operator==(vec);
}

bool Vector4::operator!=(const float value)
{
	return !operator==(value);
}

Vector4::operator float* ()
{
	return (float*)&this[0];
}
