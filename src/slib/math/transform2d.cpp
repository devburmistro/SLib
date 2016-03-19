#include "../../../inc/slib/math/transform2d.h"

#include "../../../inc/slib/core/math.h"

SLIB_MATH_NAMESPACE_BEGIN

template <class T>
void Transform2T<T>::setTranslation(Matrix3T<T>& _out, T x, T y)
{
	_out.m00 = 1; _out.m01 = 0; _out.m02 = 0;
	_out.m10 = 0; _out.m11 = 1; _out.m12 = 0;
	_out.m20 = x; _out.m21 = y; _out.m22 = 1;
}

template <class T>
void Transform2T<T>::setTranslation(Matrix3T<T>& _out, const Vector2T<T>& v)
{
	_out.m00 = 1; _out.m01 = 0; _out.m02 = 0;
	_out.m10 = 0; _out.m11 = 1; _out.m12 = 0;
	_out.m20 = v.x; _out.m21 = v.y; _out.m22 = 1;
}

template <class T>
Matrix3T<T> Transform2T<T>::getTranslationMatrix(T x, T y)
{
	return {1, 0, 0,
			0, 1, 0,
			x, y, 1};
}

template <class T>
Matrix3T<T> Transform2T<T>::getTranslationMatrix(const Vector2T<T>& v)
{
	return {1, 0, 0,
			0, 1, 0,
			v.x, v.y, 1};
}

template <class T>
void Transform2T<T>::setScaling(Matrix3T<T>& _out, T sx, T sy)
{
	_out.m00 = sx; _out.m01 = 0; _out.m02 = 0;
	_out.m10 = 0; _out.m11 = sy; _out.m12 = 0;
	_out.m20 = 0; _out.m21 = 0; _out.m22 = 1;
}

template <class T>
void Transform2T<T>::setScaling(Matrix3T<T>& _out, const Vector2T<T>& v)
{
	_out.m00 = v.x; _out.m01 = 0; _out.m02 = 0;
	_out.m10 = 0; _out.m11 = v.y; _out.m12 = 0;
	_out.m20 = 0; _out.m21 = 0; _out.m22 = 1;
}

template <class T>
Matrix3T<T> Transform2T<T>::getScalingMatrix(T x, T y)
{
	return {x, 0, 0,
			0, y, 0,
			0, 0, 1};
}

template <class T>
Matrix3T<T> Transform2T<T>::getScalingMatrix(const Vector2T<T>& v)
{
	return {v.x, 0, 0,
			0, v.y, 0,
			0, 0, 1};
}

template <class T>
void Transform2T<T>::setRotation(Matrix3T<T>& _out, T radians)
{
	T c = Math::cos(radians);
	T s = Math::sin(radians);
	_out.m00 = c; _out.m01 = s; _out.m02 = 0;
	_out.m10 = -s; _out.m11 = c; _out.m12 = 0;
	_out.m20 = 0; _out.m21 = 0; _out.m22 = 1;
}

template <class T>
void Transform2T<T>::setRotation(Matrix3T<T>& _out, T cx, T cy, T radians)
{
	Matrix3T<T> m;
	setTranslation(_out, -cx, -cy);
	setRotation(m, radians);
	_out.multiply(m);
	setTranslation(m, cx, cy);
	_out.multiply(m);
}

template <class T>
void Transform2T<T>::setRotation(Matrix3T<T>& _out, const Vector2T<T>& pt, T radians)
{
	setRotation(_out, pt.x, pt.y, radians);
}

template <class T>
Matrix3T<T> Transform2T<T>::getRotationMatrix(T radians)
{
	T c = Math::cos(radians);
	T s = Math::sin(radians);
	return {c, s, 0,
		-s, c, 0,
		0, 0, 1};
}

template <class T>
Matrix3T<T> Transform2T<T>::getRotationMatrix(T cx, T cy, T radians)
{
	Matrix3T<T> ret;
	setRotation(ret, cx, cy, radians);
	return ret;
}

template <class T>
Matrix3T<T> Transform2T<T>::getRotationMatrix(const Vector2T<T>& pt, T radians)
{
	Matrix3T<T> ret;
	setRotation(ret, pt, radians);
	return ret;
}

template <class T>
T Transform2T<T>::getRotationAngleFromDirToDir(const Vector2T<T>& from, const Vector2T<T>& to)
{
	return to.getAngleBetween(from);
}

template <class T>
void Transform2T<T>::setTransformFromDirToDir(Matrix3T<T>& _out, const Vector2T<T>& from, const Vector2T<T>& to)
{
	setRotation(_out, getRotationAngleFromDirToDir(from, to));
}

template <class T>
Matrix3T<T> Transform2T<T>::getTransformMatrixFromDirToDir(const Vector2T<T>& from, const Vector2T<T>& to)
{
	Matrix3T<T> ret;
	setTransformFromDirToDir(ret, from, to);
	return ret;
}

SLIB_DEFINE_GEOMETRY_TYPE(Transform2)

SLIB_MATH_NAMESPACE_END