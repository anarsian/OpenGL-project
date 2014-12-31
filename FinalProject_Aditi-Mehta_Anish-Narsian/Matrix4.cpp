#include <math.h>

#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4::~Matrix4()
{

}

Matrix4::Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d)
{
	m[0][0] = a.x;
	m[1][0] = a.y;
	m[2][0] = a.z;
	m[3][0] = a.w;

	m[0][1] = b.x;
	m[1][1] = b.y;
	m[2][1] = b.z;
	m[3][1] = b.w;

	m[0][2] = c.x;
	m[1][2] = c.y;
	m[2][2] = c.z;
	m[3][2] = c.w;

	m[0][3] = d.x;
	m[1][3] = d.y;
	m[2][3] = d.z;
	m[3][3] = d.w;
}

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

// multiply matrix with matrix
void Matrix4::operator*(const Matrix4& m2) 
{
	Vector4 first_col(m2.m[0][0], m2.m[1][0], m2.m[2][0], m2.m[3][0]);
	Vector4 second_col(m2.m[0][1], m2.m[1][1], m2.m[2][1], m2.m[3][1]);
	Vector4 third_col(m2.m[0][2], m2.m[1][2], m2.m[2][2], m2.m[3][2]);
	Vector4 fourth_col(m2.m[0][3], m2.m[1][3], m2.m[2][3], m2.m[3][3]);

	*(this)*first_col;
	*(this)*second_col;
	*(this)*third_col;
	*(this)*fourth_col;
    Matrix4 tmp(first_col, second_col, third_col, fourth_col); 
	*this = tmp;
}

//multiply matrix with vector
void Matrix4::operator*(Vector4& v)
{
	Vector4 first_row(m[0][0], m[0][1], m[0][2], m[0][3]);
	Vector4 second_row(m[1][0], m[1][1], m[1][2], m[1][3]);
	Vector4 third_row(m[2][0], m[2][1], m[2][2], m[2][3]);
	Vector4 fourth_row(m[3][0], m[3][1], m[3][2], m[3][3]);

	Vector4 tmp (first_row.dot(v), second_row.dot(v), third_row.dot(v), fourth_row.dot(v));
	v = tmp;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
	  {
        m[i][j] = 1.0; 
	  }
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

// make rotation matrix about X axis with angle in degrees
void Matrix4::makeRotateX(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
void Matrix4::makeRotateY(double angle)
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
    m[0][0] = cos(angle);
	m[0][2] = sin(angle);
	m[2][0] = -sin(angle);
	m[2][2] = cos(angle);
}

// make rotation matrix about Z axis with angle in degrees
void Matrix4::makeRotateZ(double angle) 
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
}

void Matrix4::makeRotate(double angle, const Vector4& axis) 
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	Vector3 tmp(axis.x, axis.y, axis.z);
	tmp.normalize();
	double c = cos(angle);
	double s = sin(angle);
	double t = 1 - c;
	m[0][0] = (tmp.x * tmp.x) + c*(1 - (tmp.x * tmp.x));
	m[1][0] = tmp.z*s + t*tmp.y*tmp.x;
	m[2][0] = t*tmp.z*tmp.x - s*tmp.y;
	m[0][1] = t*tmp.y*tmp.x - s*tmp.z;
	m[1][1] = (tmp.y * tmp.y) + c*(1 - (tmp.y * tmp.y));
	m[2][1] = tmp.x*s + t*tmp.y*tmp.z;
	m[0][2] = tmp.y*s + t*tmp.x*tmp.z;
	m[1][2] = t*tmp.y*tmp.z - s*tmp.x;
	m[2][2] = (tmp.z * tmp.z) + c*(1 - (tmp.z * tmp.z));
}

// Make a rotation matrix about an arbitrary axis
void Matrix4::makeRotate(double angle, const Vector3& axis) 
{
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians
	identity();
	Vector3 tmp = axis;
	tmp.normalize();
	double c = cos(angle);
	double s = sin(angle);
	double t = 1 - c;
	m[0][0] = (tmp.x * tmp.x) + c*(1 - (tmp.x * tmp.x));
	m[1][0] = tmp.z*s + t*tmp.y*tmp.x;
	m[2][0] = t*tmp.z*tmp.x - s*tmp.y;
	m[0][1] = t*tmp.y*tmp.x - s*tmp.z;
	m[1][1] = (tmp.y * tmp.y) + c*(1 - (tmp.y * tmp.y));
	m[2][1] = tmp.x*s + t*tmp.y*tmp.z;
	m[0][2] = tmp.y*s + t*tmp.x*tmp.z;
	m[1][2] = t*tmp.y*tmp.z - s*tmp.x;
	m[2][2] = (tmp.z * tmp.z) + c*(1 - (tmp.z * tmp.z));
}

// make a non-uniform scaling matrix
void Matrix4::makeScale(double sx, double sy, double sz)
{
	identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
}

// make a translation matrix
void Matrix4::makeTranslate(double tx, double ty, double tz) 
{
	identity();
	this->m[0][3] = tx;
	this->m[1][3] = ty;
	this->m[2][3] = tz;
}

// print the matrix 
void Matrix4::print(string comment) 
{
	printf(comment.c_str());
	printf("The matrix is as follows: \n");
	for (int i=0; i<4; ++i)
    {
		for (int j=0; j<4; ++j)
		{
			printf("%.3f\t",m[i][j]);
		}
		printf("\n");
	}
}

//return a vector with the position
Vector3& Matrix4::getPos()
{
	return *(new Vector3(m[0][3], m[1][3], m[2][3])) ;
}

void Matrix4::inverse() 
{
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //
    double Result[4][4];
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
    /* transpose matrix */
    for (int i = 0; i < 4; i++)
    {
        src[i + 0 ] = (*this).m[i][0];
        src[i + 4 ] = (*this).m[i][1];
        src[i + 8 ] = (*this).m[i][2];
        src[i + 12] = (*this).m[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    Result[0][0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
    Result[0][0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
    Result[0][1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
    Result[0][1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
    Result[0][2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
    Result[0][2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
    Result[0][3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
    Result[0][3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
    Result[1][0] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
    Result[1][0] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
    Result[1][1] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
    Result[1][1] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
    Result[1][2] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
    Result[1][2] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
    Result[1][3] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
    Result[1][3] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2]*src[7];
    tmp[1] = src[3]*src[6];
    tmp[2] = src[1]*src[7];
    tmp[3] = src[3]*src[5];
    tmp[4] = src[1]*src[6];
    tmp[5] = src[2]*src[5];

    tmp[6] = src[0]*src[7];
    tmp[7] = src[3]*src[4];
    tmp[8] = src[0]*src[6];
    tmp[9] = src[2]*src[4];
    tmp[10] = src[0]*src[5];
    tmp[11] = src[1]*src[4];
    /* calculate second 8 elements (cofactors) */
    Result[2][0] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
    Result[2][0] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
    Result[2][1] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
    Result[2][1] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
    Result[2][2] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
    Result[2][2] -= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
    Result[2][3] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
    Result[2][3] -= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
    Result[3][0] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
    Result[3][0] -= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
    Result[3][1] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
    Result[3][1] -= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
    Result[3][2] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
    Result[3][2] -= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
    Result[3][3] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
    Result[3][3] -= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
    /* calculate determinant */
    det=src[0]*Result[0][0]+src[1]*Result[0][1]+src[2]*Result[0][2]+src[3]*Result[0][3];
    /* calculate matrix inverse */
    det = 1.0f / det;

	Matrix4 answer;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            answer.m[i][j] = (Result[i][j] * det);
        }
    }
    *this = answer;
}