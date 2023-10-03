#pragma once
#include "cmath"
#include <cassert>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];
};

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};

/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};

struct Sphere {
	Vector3 center;	//!< 中心点
	float radius;	//!< 半径
};

struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

//
//void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char a[]) {
//	Novice::ScreenPrintf(x, y, "%s", a);
//	for (int row = 0; row < 4; ++row) {
//		for (int column = 0; column < 4; ++column) {
//			Novice::ScreenPrintf(x + column * kColumnWidth, 20 + y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
//		}
//	}
//}
//
//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
//}

//行列の加法
Matrix4x4 Add(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Return.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}
	return Return;
}

//行列の減法
Matrix4x4 Subtract(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Return.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}
	return Return;
}

//行列の積
Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				Return.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return Return;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 Return{};
	float A = 0;

	A = (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Return.m[0][0] = (1 / A) * ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2]));

	Return.m[0][1] = (1 / A) * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2]));

	Return.m[0][2] = (1 / A) * ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	Return.m[0][3] = (1 / A) * (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2]));

	Return.m[1][0] = (1 / A) * (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	Return.m[1][1] = (1 / A) * ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	Return.m[1][2] = (1 / A) * (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	Return.m[1][3] = (1 / A) * ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2]));

	Return.m[2][0] = (1 / A) * ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	Return.m[2][1] = (1 / A) * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	Return.m[2][2] = (1 / A) * ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	Return.m[2][3] = (1 / A) * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1]));

	Return.m[3][0] = (1 / A) * (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1]));

	Return.m[3][1] = (1 / A) * ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	Return.m[3][2] = (1 / A) * (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	Return.m[3][3] = (1 / A) * ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1]));

	return Return;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Return.m[i][j] = m.m[j][i];
		}
	}
	return Return;
}

//単位行列
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				Return.m[i][j] = 1;
			}
		}
	}
	return Return;
}

//ベクトルと行列の積
Vector3 Multiply(Vector3 vector, Matrix4x4 matrix) {
	Vector3 Return = {};
	Return.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]);
	Return.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]);
	Return.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]);
	return Return;
}

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 Return{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				Return.m[i][j] = 1;
			}
		}
	}
	Return.m[3][0] = translate.x;
	Return.m[3][1] = translate.y;
	Return.m[3][2] = translate.z;
	return Return;
}

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 Return{};
	Return.m[0][0] = scale.x;
	Return.m[1][1] = scale.y;
	Return.m[2][2] = scale.z;
	Return.m[3][3] = 1;
	return Return;
}

//3.座標返還
//Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
//	Vector3 Return{};
//	Return.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
//	Return.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
//	Return.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
//	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
//	assert(w != 0.0f);
//	Return.x /= w;
//	Return.y /= w;
//	Return.z /= w;
//	return Return;
//}

//1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 Return{};
	Return.m[0][0] = 1;
	Return.m[1][1] = std::cos(radian);
	Return.m[1][2] = std::sin(radian);
	Return.m[2][1] = -std::sin(radian);
	Return.m[2][2] = std::cos(radian);
	Return.m[3][3] = 1;
	return Return;
}

//2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 Return{};
	Return.m[0][0] = std::cos(radian);
	Return.m[0][2] = -std::sin(radian);
	Return.m[1][1] = 1;
	Return.m[2][0] = std::sin(radian);
	Return.m[2][2] = std::cos(radian);
	Return.m[3][3] = 1;
	return Return;
}

//3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 Return{};
	Return.m[0][0] = std::cos(radian);
	Return.m[0][1] = std::sin(radian);
	Return.m[1][0] = -std::sin(radian);
	Return.m[1][1] = std::cos(radian);
	Return.m[2][2] = 1;
	Return.m[3][3] = 1;
	return Return;
}

//1. 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};
	result.m[0][0] = (1 / aspectRatio) * (1 / std::tan(fovY / 2));
	result.m[1][1] = (1 / std::tan(fovY / 2));
	result.m[2][2] = (farClip / (farClip - nearClip));
	result.m[2][3] = 1;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	return result;
}

//2. 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;
	return result;
}

//3. ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};
	result.m[0][0] = width / 2;
	result.m[1][1] = -(height / 2);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;
	return result;
}

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}

Matrix4x4  MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result{};
	result = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	result = Multiply(result, rotateXYZMatrix);
	result = Multiply(result, MakeTranslateMatrix(translate));
	return result;
}