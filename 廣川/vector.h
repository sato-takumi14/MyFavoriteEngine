#pragma once
#include <math.h>

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

public:
	Vector2() {}
	Vector2(float x, float y) :x(x), y(y) {}

	float Length(){return sqrtf(x * x + y * y);}
	float LengthSpr(){return (x * x + y * y);}
};

class Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

public:
	//�R���X�g���N�^
	Vector3() {}
	Vector3(float x, float y, float z) :x(x), y(y), z(z){}
	Vector3(D3DXVECTOR3 vec):x(vec.x),y(vec.y),z(vec.z){}
	//�֐�
	//�x�N�g���̒�����Ԃ�
	float Length(){return sqrtf(x * x + y * y + z * z);}
	float LengthSpr(){return (x * x + y * y + z * z);}

	//�x�N�g���𐳋K�������l��Ԃ�
	Vector3 Normaliz()
	{if (Length() != 0) return Vector3(x / Length(), y / Length(), z / Length());}
	//�x�N�g���𐳋K������
	void NormalizThis()
	{
		if (LengthSpr() != 0)
		{
			x = x / Length();
			y = y / Length();
			z = z / Length();
		}
	}

	//world���W��Ԃ�
	Vector3 Right()   { return Vector3(1.0f, 0.0f, 0.0f); }//x
	Vector3 Forward() { return Vector3(0.0f, 0.0f, 1.0f); }//z
	Vector3 Up()	  { return Vector3(0.0f, 1.0f, 0.0f); }//y
	Vector3 Zero()    { return Vector3(0.0f, 0.0f, 0.0f); }
	Vector3 One()	  { return Vector3(1.0f, 1.0f, 1.0f); }

	//�ȉ��I�y���[�^�[
	Vector3 operator- (void)	  { return Vector3(- x, - y,- z);}

	Vector3 operator+ (Vector3 v) { return Vector3(v.x + x, v.y + y, v.z + z);}
	Vector3 operator- (Vector3 v) { return Vector3(v.x - x, v.y - y, v.z - z); }
	Vector3 operator* (Vector3 v) { return Vector3(v.x * x, v.y * y, v.z * z);}
	Vector3 operator/ (Vector3 v) { return Vector3(v.x / x, v.y / y, v.z / z); }

	Vector3 operator+ (float a) { return Vector3(a + x, a + y, a + z); }
	Vector3 operator- (float a) { return Vector3(a - x, a - y, a - z); }
	Vector3 operator* (float a) { return Vector3(a * x, a * y, a * z); }
	Vector3 operator/ (float a) { return Vector3(a / x, a / y, a / z); }

	void operator+= (Vector3 v) { x += v.x, y += v.y, z += v.z; }
	void operator-= (Vector3 v) { x -= v.x, y -= v.y, z -= v.z; }
	void operator*= (Vector3 v) { x *= v.x, y *= v.y, z *= v.z; }
	void operator/= (Vector3 v) { x /= v.x, y /= v.y, z /= v.z; }

	bool operator> (float a)
	{
		if (LengthSpr() > a * a)
			return true;

		return false;
	}
	bool operator< (float a)
	{
		if (LengthSpr() < a * a)
			return true;

		return false;
	}
	bool operator== (float a)
	{
		if (LengthSpr() == a * a)
			return true;

		return false;
	}
	bool operator!= (float a)
	{
		if (LengthSpr() != a * a)
			return true;

		return false;
	}

	class Color
	{
	private:
		Color();
	public:
		float r;
		float g;
		float b;
		float a;
	public:
		Color(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
	};

	D3DXCOLOR
};