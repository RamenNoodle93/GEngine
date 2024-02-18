#include "../Include/Tools.h"

Tools::Tools()
{
}

Tools::~Tools()
{
}

idType Tools::GetIndex(idType id)
{
	return id & indexMask;
}

idType Tools::GetGeneration(idType id)
{
	return (id & generationMask) >> generationSize;
}

idType Tools::ConstructId(int index, int generation)
{
	return (generation << generationSize) + index;
}

void Tools::MultiplyMatrixVector(Node& in, Node& out, Mat4x4& mat)
{
	out.x = in.x * mat.m[0][0] + in.y * mat.m[1][0] + in.z * mat.m[2][0] + mat.m[3][0];
	out.y = in.x * mat.m[0][1] + in.y * mat.m[1][1] + in.z * mat.m[2][1] + mat.m[3][1];
	out.z = in.x * mat.m[0][2] + in.y * mat.m[1][2] + in.z * mat.m[2][2] + mat.m[3][2];
	out.w = in.x * mat.m[0][3] + in.y * mat.m[1][3] + in.z * mat.m[2][3] + mat.m[3][3];
}

void Tools::CalculateNormal(Triangle& in, Node& out)
{
	Node vec1, vec2;

	vec1.x = in.p[1].x - in.p[0].x;
	vec1.y = in.p[1].y - in.p[0].y;
	vec1.z = in.p[1].z - in.p[0].z;

	vec2.x = in.p[2].x - in.p[0].x;
	vec2.y = in.p[2].y - in.p[0].y;
	vec2.z = in.p[2].z - in.p[0].z;

	out.x = vec1.y * vec2.z - vec1.z * vec2.y;
	out.y = vec1.z * vec2.x - vec1.x * vec2.z;
	out.z = vec1.x * vec2.y - vec1.y * vec2.x;
}

void Tools::TranslateTriangle(Triangle& in, Node& pos, Triangle& out)
{
	AddVectors(pos, in.p[0], out.p[0]);
	AddVectors(pos, in.p[1], out.p[1]);
	AddVectors(pos, in.p[2], out.p[2]);
}

void Tools::MatrixMultiplyTriangle(Triangle& in, Mat4x4& matrix, Triangle& out)
{
	Tools::MultiplyMatrixVector(in.p[0], out.p[0], matrix);
	Tools::MultiplyMatrixVector(in.p[1], out.p[1], matrix);
	Tools::MultiplyMatrixVector(in.p[2], out.p[2], matrix);
}

Mat4x4 Tools::GetProjectionMatrix(float aspectRatio, float fov, float zFar, float zNear)
{
	float fovTan = 1.0f / tanf(fov * 0.5f);

	Mat4x4 projMat;

	projMat.m[0][0] = aspectRatio * fovTan;
	projMat.m[1][1] = fovTan;
	projMat.m[2][2] = zFar / (zFar - zNear);
	projMat.m[3][2] = (-zFar * zNear) / (zFar - zNear);
	projMat.m[2][3] = 1.0f;
	projMat.m[3][3] = 0.0f;
	return projMat;
}

void Tools::AddVectors(Node& vec1, Node& vec2, Node& out)
{
	out.x = vec1.x + vec2.x;
	out.y = vec1.y + vec2.y;
	out.z = vec1.z + vec2.z;
}

void Tools::SubtractVectors(Node& vec1, Node& vec2, Node& out)
{
	out.x = vec1.x - vec2.x;
	out.y = vec1.y - vec2.y;
	out.z = vec1.z - vec2.z;
}

void Tools::NormalizeVector(Node& vec, Node& out)
{
	float l = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	out.x = vec.x / l;
	out.y = vec.y / l;
	out.z = vec.z / l;
}

void Tools::DivideVector(Node& vec, float scale, Node& out)
{
	out.x = vec.x / scale;
	out.y = vec.y / scale;
	out.z = vec.z / scale;
}

void Tools::MultiplyVector(Node& vec, float scale, Node& out)
{
	out.x = vec.x * scale;
	out.y = vec.y * scale;
	out.z = vec.z * scale;
}

float Tools::DotProduct(Node& first, Node& second)
{
	return first.x * second.x + first.y * second.y + first.z * second.z;
}

Mat4x4 Tools::Mulitply4x4Matrices(Mat4x4& mat1, Mat4x4& mat2)
{
	Mat4x4 multiplied;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
				multiplied.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
		}
	}
	return multiplied;
}

Mat4x4 Tools::GetWorldMatrix(float rotationX, float rotationY, float rotationZ)
{
	Mat4x4 temp, rotX, rotY, rotZ;
	rotX = Tools::GetRotationMatrixX(rotationX);
	rotY = Tools::GetRotationMatrixY(rotationY);
	rotZ = Tools::GetRotationMatrixZ(rotationZ);

	temp = Tools::Mulitply4x4Matrices(rotY, rotZ);

	return Tools::Mulitply4x4Matrices(rotX, temp);
}

Mat4x4 Tools::GetRotationMatrixX(float rotationX)
{
	Mat4x4 rotationMatX;
	rotationMatX.m[0][0] = 1.0f;
	rotationMatX.m[1][1] = cosf(rotationX);
	rotationMatX.m[1][2] = sinf(rotationX);
	rotationMatX.m[2][1] = -sinf(rotationX);
	rotationMatX.m[2][2] = cosf(rotationX);
	rotationMatX.m[3][3] = 1.0f;

	return rotationMatX;
}

Mat4x4 Tools::GetRotationMatrixY(float rotationY)
{
	Mat4x4 rotationMatY;
	rotationMatY.m[0][0] = cosf(rotationY);
	rotationMatY.m[0][2] = -sinf(rotationY);
	rotationMatY.m[1][1] = 1.0f;
	rotationMatY.m[2][0] = sinf(rotationY);
	rotationMatY.m[2][2] = cosf(rotationY);
	rotationMatY.m[3][3] = 1.0f;

	return rotationMatY;
}

Mat4x4 Tools::GetRotationMatrixZ(float rotationZ)
{
	Mat4x4 rotationMatZ;
	rotationMatZ.m[0][0] = cosf(rotationZ);
	rotationMatZ.m[0][1] = -sinf(rotationZ);
	rotationMatZ.m[1][0] = sinf(rotationZ);
	rotationMatZ.m[1][1] = cosf(rotationZ);
	rotationMatZ.m[2][2] = 1.0f;
	rotationMatZ.m[3][3] = 1.0f;

	return rotationMatZ;
}

Node Tools::VectorPlaneIntersect(Node& planeVector, Node& planeNormal, Node& lineStart, Node& lineEnd)
{
	NormalizeVector(planeNormal, planeNormal);

	float dInter = -DotProduct(planeNormal, planeVector);
	float ad = DotProduct(lineStart, planeNormal);
	float bd = DotProduct(lineEnd, planeNormal);
	float t = (-dInter - ad) / (bd - ad);

	Node lineStartToEnd;
	SubtractVectors(lineEnd, lineStart, lineStartToEnd);

	Node lineToIntersect;
	MultiplyVector(lineStartToEnd, t, lineToIntersect);

	Node finalVal;
	AddVectors(lineStart, lineToIntersect, finalVal);

	return finalVal;
}

int Tools::ClipTriangle(Node& planeVec, Node& planeNormal, Triangle& in, Triangle& out1, Triangle& out2)
{
	NormalizeVector(planeNormal, planeNormal);

	//Najkrotszy dystans od punktu do plaszczyzny
	auto dist = [&](Node& p)
		{
			Node node;
			NormalizeVector(p, node);
			return (planeNormal.x * node.x + planeNormal.y * node.y + planeNormal.z * node.z - DotProduct(planeNormal, planeVec));
		};

	//Dystans wiekszy od 0 oznacza, ze punkt lezy 'wewnatrz' plaszczyzny

	Node* insidePoints[3];  int nInsidePointCount = 0;
	Node* outsidePoints[3]; int nOutsidePointCount = 0;

	//Dystans kazdego punktu do plaszczyzny
	float d0 = dist(in.p[0]);
	float d1 = dist(in.p[1]);
	float d2 = dist(in.p[2]);

	if (d0 >= 0) { insidePoints[nInsidePointCount++] = &in.p[0]; }
	else { outsidePoints[nOutsidePointCount++] = &in.p[0]; }
	if (d1 >= 0) { insidePoints[nInsidePointCount++] = &in.p[1]; }
	else { outsidePoints[nOutsidePointCount++] = &in.p[1]; }
	if (d2 >= 0) { insidePoints[nInsidePointCount++] = &in.p[2]; }
	else { outsidePoints[nOutsidePointCount++] = &in.p[2]; }

	if (nInsidePointCount == 0)
	{
		//Caly trojkat jest poza plaszczyzna, czyli nie trzeba go rysowac
		return 0;
	}

	if (nInsidePointCount == 3)
	{
		//Caly trojkat jest 'w plaszczyznie', czyli nie trzeba go przycinac
		out1 = in;
		return 1;
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		out1.p[0] = *insidePoints[0];

		//Obliczanie wspolrzednych przeciecia dwoch pozostalych punktow z plaszczyzna
		out1.p[1] = VectorPlaneIntersect(planeVec, planeNormal, *insidePoints[0], *outsidePoints[0]);
		out1.p[2] = VectorPlaneIntersect(planeVec, planeNormal, *insidePoints[0], *outsidePoints[1]);

		return 1;
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		//Nalezy stworzyc dwa nowe trojkaty

		out1.p[0] = *insidePoints[0];
		out1.p[1] = *insidePoints[1];
		out1.p[2] = VectorPlaneIntersect(planeVec, planeNormal, *insidePoints[0], *outsidePoints[0]);

		out2.p[0] = *insidePoints[1];
		out2.p[1] = out1.p[2];
		out2.p[2] = VectorPlaneIntersect(planeVec, planeNormal, *insidePoints[1], *outsidePoints[0]);

		return 2;
	}
}

void Tools::DrawTriangle(Projected projection, sf::RenderWindow& window, bool outline, bool filled, sf::Color fillColor)
{
	for (auto& tri : projection.tris)
	{

		if (filled)
		{
			sf::ConvexShape shape;

			shape.setPointCount(3);
			shape.setPoint(0, sf::Vector2f(tri.p[0].x, tri.p[0].y));
			shape.setPoint(1, sf::Vector2f(tri.p[1].x, tri.p[1].y));
			shape.setPoint(2, sf::Vector2f(tri.p[2].x, tri.p[2].y));
			shape.setFillColor(fillColor);

			window.draw(shape);
		}

		sf::Vertex vertices[3];
		for (int i = 0; i < 3; i++)
		{
			vertices[i] = sf::Vertex(sf::Vector2f(tri.p[i].x, tri.p[i].y));
			vertices[i].color = projection.color;
		}

		for (int i = 0; i < 3; i++)
		{
			sf::Vertex line[2] =
			{
				vertices[i],
				vertices[(i + 1) % 2]
			};

			window.draw(line, 2, sf::Lines);
		}

	}
}
