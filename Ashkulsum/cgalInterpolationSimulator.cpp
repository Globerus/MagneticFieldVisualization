#include "stdafx.h"
#include "cgalInterpolationSimulator.h"


CGALInterpolationSimulator::CGALInterpolationSimulator ()
	:	m_Work (m_IOService),
		m_Radius (5.0f),
		m_MaxMagFieldForce (15.0f)
{
	for (unsigned int i =0; i < NUM_INITIALIZATION_POINTS; i++)
	{
		glm::vec3 point (m_Initialization3DPointList[3*i], m_Initialization3DPointList[3*i+1], m_Initialization3DPointList[3*i+2]);
		Point3D cgalPoint (point.x, point.y, point.z);
		m_DelaunayTriangulation3D.insert (cgalPoint);
		m_Initial3DPointMagForceMap[cgalPoint] = m_InitializationMagForceList[i];
		float interpolatedAngleRad = Maths::DegToRad (m_InitializationDirVecList[i]);
		float sin = std::sin (interpolatedAngleRad);
		float cos = std::cos (interpolatedAngleRad);
		m_Initial3DPointDirVecMap[cgalPoint] = glm::vec2(cos, sin);
		//m_Initial3DPointDirVecMap[cgalPoint] = m_InitializationDirVecList[i];
		m_Interpolated3DPointMagForceVector.push_back (glm::vec4(point, m_InitializationMagForceList[i]/m_MaxMagFieldForce));
	}
	/*
	int sample_size = 4;
    std::vector<Point3D> points;
    points.reserve(sample_size);

	DelaunayTriangulation3D w;

	Point3D a (-1.0f, 1.0f, 0.0f);
	Point3D b (1.0f, 1.0f, 0.0f);
	Point3D c (-1.0f, -1.0f, 0.0f);
	Point3D d (1.0f, -1.0f, 0.0f);
	Point3D e (-1.0f, 1.0f, 1.0f);
	Point3D f (1.0f, 1.0f, 1.0f);
	Point3D g (-1.0f, -1.0f, 1.0f);
	Point3D h (1.0f, -1.0f, 1.0f);

	m_DelaunayTriangulation3D.insert (a);
	m_DelaunayTriangulation3D.insert (b);
	m_DelaunayTriangulation3D.insert (c);
	m_DelaunayTriangulation3D.insert (d);
	m_DelaunayTriangulation3D.insert (e);
	m_DelaunayTriangulation3D.insert (f);
	m_DelaunayTriangulation3D.insert (g);
	m_DelaunayTriangulation3D.insert (h);

	

	glm::vec3 q = glm::normalize (glm::vec3(a.x(), a.y (), a.z()));

					   
    //value_map_t F;

	glm::vec3 val1 = glm::vec3 (0.0f, -1.0f, 0.0f);
	glm::vec3 val2 = glm::vec3 (1.5f, 2.0f, 0.0f);
	glm::vec3 val3 = glm::vec3 (0.0f, 2.0f, 0.0f);
	glm::vec3 val4 = glm::vec3 (2.0f, -2.0f, 0.0f);
	glm::vec3 val5 = glm::vec3 (0.0f, 2.0f, 1.0f);
	glm::vec3 val6 = glm::vec3 (1.5f, 2.0f, 1.0f);
	glm::vec3 val7 = glm::vec3 (0.0f, 2.0f, 1.0f);
	glm::vec3 val8 = glm::vec3 (2.0f, -2.0f, 1.0f);

	/*val1 = glm::normalize (val1);
	val2 = glm::normalize (val2);
	val3 = glm::normalize (val3);
	val4 = glm::normalize (val4);
	val5 = glm::normalize (val5);
	val6 = glm::normalize (val6);
	val7 = glm::normalize (val7);
	val8 = glm::normalize (val8);*/
/*
	m_Vec3DMap.insert (std::make_pair (a, val1));
	m_Vec3DMap.insert (std::make_pair (b, val2));
	m_Vec3DMap.insert (std::make_pair (c, val3));
	m_Vec3DMap.insert (std::make_pair (d, val4));
	m_Vec3DMap.insert (std::make_pair (e, val5));
	m_Vec3DMap.insert (std::make_pair (f, val6));
	m_Vec3DMap.insert (std::make_pair (g, val7));
	m_Vec3DMap.insert (std::make_pair (h, val8));

	std::vector<glm::vec3> o;
	//o.push_back (result);

	o = GenerateStreamLine (20, 0.1f, glm::vec3 (-0.9f, -0.9f, 0.1f));
	/*Point3D my (-0.9f, -0.9f, 0.1f);
	for (int i = 1 ; i < 5; i++)
	{	
		float dt = 0.3f;
		CoordType norm;
		VertexHandleVector vertexHandleVector;
		CGAL::sibson_natural_neighbor_coordinates_3 (w, my, std::back_inserter(vertexHandleVector), norm);
	
		glm::vec3 result (0);
		for (int j =0; j < vertexHandleVector.size (); j++)
		{
			auto point = vertexHandleVector[j].first->point();
			auto weight = (float)vertexHandleVector[j].second;
			auto val = F[point];
			val.x = val.x - point.x();
			val.y = val.y - point.y();
			val.z = val.z - point.z();
			result += ((weight/(float)norm) * val);
		}
		//result = glm::normalize (result);
		//glm::vec3 d = Maths::RundKutta (result, 0.3f);

		glm::vec3 k1 = dt * result;
		Point3D vp2 (my.x () + 0.5f*k1.x, my.y () + 0.5f*k1.y, my.z () + 0.5f*k1.z);
		
		CoordType norm2;
		VertexHandleVector vertexHandleVector2;
		CGAL::sibson_natural_neighbor_coordinates_3 (w, vp2, std::back_inserter(vertexHandleVector2), norm2);
	
		glm::vec3 result2 (0);
		for (int j =0; j < vertexHandleVector.size (); j++)
		{
			auto point = vertexHandleVector2[j].first->point();
			auto weight = (float)vertexHandleVector2[j].second;
			auto val = F[point];
			val.x = val.x - point.x();
			val.y = val.y - point.y();
			val.z = val.z - point.z();
			result2 += ((weight/(float)norm2) * val);
		}

		glm::vec3 k2 = dt * result2;
		Point3D vp3 (my.x () + 0.5f*k2.x, my.y () + 0.5f*k2.y, my.z () + 0.5f*k2.z);
		
		CoordType norm3;
		VertexHandleVector vertexHandleVector3;
		CGAL::sibson_natural_neighbor_coordinates_3 (w, vp3, std::back_inserter(vertexHandleVector3), norm3);
	
		glm::vec3 result3 (0);
		for (int j =0; j < vertexHandleVector.size (); j++)
		{
			auto point = vertexHandleVector3[j].first->point();
			auto weight = (float)vertexHandleVector3[j].second;
			auto val = F[point];
			val.x = val.x - point.x();
			val.y = val.y - point.y();
			val.z = val.z - point.z();
			result3 += ((weight/(float)norm3) * val);
		}

		glm::vec3 k3 = dt * result3;
		Point3D vp4 (my.x () + k3.x, my.y () + k3.y, my.z () + k3.z);
		
		CoordType norm4;
		VertexHandleVector vertexHandleVector4;
		CGAL::sibson_natural_neighbor_coordinates_3 (w, vp4, std::back_inserter(vertexHandleVector4), norm4);
	
		glm::vec3 result4 (0);
		for (int j =0; j < vertexHandleVector.size (); j++)
		{
			auto point = vertexHandleVector4[j].first->point();
			auto weight = (float)vertexHandleVector4[j].second;
			auto val = F[point];
			val.x = val.x - point.x();
			val.y = val.y - point.y();
			val.z = val.z - point.z();
			result4 += ((weight/(float)norm4) * val);
		}

		glm::vec3 k4 = dt * result4;

		float dtSixth = dt/6;

		glm::vec3 final = glm::vec3 (my.x(), my.y(), my.z()) + dtSixth * (k1 + 2.0f * (k2 + k3) + k4);

		my = Point3D(final.x,final.y,final.z);

		o.push_back (glm::vec3 (my.x(), my.y (), my.z ()));
	}*/

	//InitThreadPool ();
}

void CGALInterpolationSimulator::InitThreadPool ()
{
	for (unsigned int r= 0; r< boost::thread::hardware_concurrency(); r++)
	{
		m_Pool.create_thread (boost::bind (&boost::asio::io_service::run, &m_IOService));
	}
}

void CGALInterpolationSimulator::InterpolateMagForce (glm::vec3 & point)
{
	CoordType norm;
	VertexHandleVector vertexHandleVector;
	Point3DVector point3DVector;

	Point3D cgalPoint (point.x, point.y, point.z);

	CGAL::sibson_natural_neighbor_coordinates_3 (m_DelaunayTriangulation3D, cgalPoint, std::back_inserter(vertexHandleVector), norm);
	
 	if (norm > 0.0f)
	{
		for (unsigned int i = 0; i < vertexHandleVector.size (); i++)
		{
			Point3D cgalP = vertexHandleVector[i].first->point();
			point3DVector.push_back (std::make_pair (cgalP, vertexHandleVector[i].second));
		}

		CoordType interpolationResult = CGAL::linear_interpolation (point3DVector.begin(), point3DVector.end(), norm, ValueAccess(m_Initial3DPointMagForceMap));

		boost::unique_lock <boost::mutex> uniqueLock (m_Mutex);
		m_Interpolated3DPointMagForceVector.push_back (glm::vec4 (point, (CGAL::to_double (interpolationResult)/ m_MaxMagFieldForce)));
		uniqueLock.unlock ();
		
	}
}

glm::vec3 CGALInterpolationSimulator::InterpolateDirVec (glm::vec3 & point)
{
	glm::vec3 dirVector(0);

	Point3D cgalPoint (point.x, point.y, point.z);
	CoordType norm;
	VertexHandleVector vertexHandleVector;
	Point3DVector point3DVector;

	CGAL::sibson_natural_neighbor_coordinates_3 (m_DelaunayTriangulation3D, cgalPoint, std::back_inserter(vertexHandleVector), norm);
	
	if (norm > 0.0f)
	{
		for (unsigned int i = 0; i < vertexHandleVector.size (); i++)
			{
				Point3D cgalP = vertexHandleVector[i].first->point();
				point3DVector.push_back (std::make_pair (cgalP, vertexHandleVector[i].second));
			}

		dirVector = WeightedVectorLinearInterpolation (cgalPoint, vertexHandleVector, norm);
		//CoordType interpolationResult = CGAL::linear_interpolation (point3DVector.begin(), point3DVector.end(), norm, ValueAccess(m_Initial3DPointDirVecMap));
	
		//float interpolatedAngleRad = Maths::DegToRad ((float)CGAL::to_double (interpolationResult));
		//float sin = std::sin (interpolatedAngleRad);
		//float cos = std::cos (interpolatedAngleRad);

		//dirVector = glm::normalize(glm::vec3 (point.x*cos, sin, point.z*cos));
	//glm::vec3 interpolatedVector = WeightedVectorLinearInterpolation (cgalPoint, vertexHandleVector, norm);
	}
	return dirVector;
}

std::vector<glm::vec4> CGALInterpolationSimulator::GeneratePoints ()
{
	InitThreadPool ();

	CGAL::Random_points_in_ball_d<Point> generator (3, m_Radius);

	for (int i = 0; i < NUM_GENERATED_POINTS; i++)
	{
		Point point = *generator++;
		glm::vec3 vec (point.x (), point.y (), point.z ());
		if (/*point.x () > 3.2f || point.y () > 2.4f || point.z () > 3.2f || point.x () < -3.2f || point.y () < -2.4f ||*/ point.z () >= 0.0f)
			m_IOService.post(boost::bind (&CGALInterpolationSimulator::InterpolateMagForce, this, vec));
	}

	m_IOService.stop ();
	m_Pool.join_all ();

	return m_Interpolated3DPointMagForceVector;
}

glm::vec3 CGALInterpolationSimulator::WeightedVectorLinearInterpolation (Point3D point, VertexHandleVector vector, CoordType norm)
{
	glm::vec2 accum (0);
	glm::vec3 result (0);

	for (unsigned int i =0; i < vector.size (); i++)
		{
			auto point = vector[i].first->point();
			auto weight = (float)vector[i].second;
			auto val = m_Initial3DPointDirVecMap[point];
			//auto dir =  val - glm::vec3 (point.x (), point.y (), point.z ());
			accum += ((weight/(float)norm) * val);
		}
	float x = point.x() == 0.0f ? 0 : accum.x;
	float y = accum.y;
	float z = point.z() == 0.0f ? 0 : accum.x;
	result = glm::vec3 (x, y, z);
	//result = glm::vec3 (accum.x, accum.y, accum.x);
	return result;
}

glm::vec3 CGALInterpolationSimulator::RungeKutta4 (float dt, glm::vec3 & point)
{
		glm::vec3 b = InterpolateDirVec (point);
		glm::vec3 k1 = dt * b;
		float a = atan2 (b.y, b.x)* 180.0f/3.14f;
		glm::vec3 k2 = dt * InterpolateDirVec (point + 0.5f * k1);
		glm::vec3 k3 = dt * InterpolateDirVec (point + 0.5f * k2);
		glm::vec3 k4 = dt * InterpolateDirVec (point + k3);

		float dtSixth = dt/6;

		glm::vec3 res = point + dtSixth * (k1 + 2.0f * (k2 + k3) + k4);

		return res;
		//boost::unique_lock <boost::mutex> uniqueLock (m_Mutex);
		//m_StreamLineVertices[id] = res;
		//uniqueLock.unlock ();
}

std::vector<glm::vec3> CGALInterpolationSimulator::GenerateStreamLine (int numSegments, float dt, glm::vec3 point)
{
	std::vector<glm::vec3> result;

	glm::vec3 procPoint = point;

	int numSteps = (int)numSegments/dt;

	/*std::function<glm::vec3 (glm::vec3)> func = [this] (glm::vec3 const& p) -> glm::vec3
	{
		Point3D cgalPoint (p.x, p.y, p.z);
		CoordType norm;
		VertexHandleVector vertexHandleVector;
		CGAL::sibson_natural_neighbor_coordinates_3 (m_DelaunayTriangulation3D, cgalPoint, std::back_inserter(vertexHandleVector), norm);
	
		glm::vec3 vector (0);
		vector = WeightedVectorLinearInterpolation (cgalPoint, vertexHandleVector, norm);
		return vector;
	};*/
	//InitThreadPool ();
	result.push_back (point);
	for (int i =0; i < numSteps; i++)
	{
		//m_IOService.post(boost::bind (&CGALInterpolationSimulator::RungeKutta4, this, i, dt, point));
		glm::vec3 newPoint = RungeKutta4 (dt, procPoint);
		result.push_back (newPoint);
		procPoint = newPoint;
	}

	//m_IOService.stop ();
	//m_Pool.join_all ();

	//for (int i= 0; i < numSteps; i++)
	//{
	//	result.push_back (m_StreamLineVertices[i]);
	//}

	return result;
}

float const CGALInterpolationSimulator::m_Initialization3DPointList[NUM_INITIALIZATION_POINTS*3] = 
{
	// Inner magnet middle//
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.70f, 0.0f, 0.70f,
	0.0f, 0.0f, 1.0f,
	-0.70f, 0.0f, 0.70f,
	-1.0f, 0.0f, 0.0f,
	-0.70f, 0.0f, -0.70f,
	0.0f, 0.0f, -1.0f,
	0.70f, 0.0f, -0.70f,

	// Inner magnet mid top//
	0.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f,
	0.70f, 0.5f, 0.70f,
	0.0f, 0.5f, 1.0f,
	-0.70f, 0.5f, 0.70f,
	-1.0f, 0.5f, 0.0f,
	-0.70f, 0.5f, -0.70f,
	0.0f, 0.5f, -1.0f,
	0.70f, 0.5f, -0.70f,

	// Inner magnet mid bot//
	0.0f, -0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
	0.70f, -0.5f, 0.70f,
	0.0f, -0.5f, 1.0f,
	-0.70f, -0.5f, 0.70f,
	-1.0f, -0.5f, 0.0f,
	-0.70f, -0.5f, -0.70f,
	0.0f, -0.5f, -1.0f,
	0.70f, -0.5f, -0.70f,

	// Inner magnet top//
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.70f, 1.0f, 0.70f,
	0.0f, 1.0f, 1.0f,
	-0.70f, 1.0f, 0.70f,
	-1.0f, 1.0f, 0.0f,
	-0.70f, 1.0f, -0.70f,
	0.0f, 1.0f, -1.0f,
	0.70f, 1.0f, -0.70f,

	// Inner magnet bot//
	0.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.70f, -1.0f, 0.70f,
	0.0f, -1.0f, 1.0f,
	-0.70f, -1.0f, 0.70f,
	-1.0f, -1.0f, 0.0f,
	-0.70f, -1.0f, -0.70f,
	0.0f, -1.0f, -1.0f,
	0.70f, -1.0f, -0.70f,


	// Inner magnet  half middle//
	0.5f, 0.0f, 0.0f,
	0.35f, 0.0f, 0.35f,
	0.0f, 0.0f, 0.5f,
	-0.35f, 0.0f, 0.35f,
	-0.5f, 0.0f, 0.0f,
	-0.35f, 0.0f, -0.35f,
	0.0f, 0.0f, -0.5f,
	0.35f, 0.0f, -0.35f,

	// Inner magnet half top//
	0.5f, 1.0f, 0.0f,
	0.35f, 1.0f, 0.35f,
	0.0f, 1.0f, 0.5f,
	-0.35f, 1.0f, 0.35f,
	-0.5f, 1.0f, 0.0f,
	-0.35f, 1.0f, -0.35f,
	0.0f, 1.0f, -0.5f,
	0.35f, 1.0f, -0.35f,

	// Inner magnet half bot//
	0.5f, -1.0f, 0.0f,
	0.35f, -1.0f, 0.35f,
	0.0f, -1.0f, 0.5f,
	-0.35f, -1.0f, 0.35f,
	-0.5f, -1.0f, 0.0f,
	-0.35f, -1.0f, -0.35f,
	0.0f, -1.0f, -0.5f,
	0.35f, -1.0f, -0.35f,

	 // Between coil and magnet mid//
	1.15f, 0.0f, 0.0f,
	0.805f, 0.0f, 0.805f,
	0.0f, 0.0f, 1.15f,
	-0.805f, 0.0f, 0.805f,
	-1.15f, 0.0f, 0.0f,
	-0.805f, 0.0f, -0.805f,
	0.0f, 0.0f, -1.15f,
	0.805f, 0.0f, -0.805f,

	// Between coil and magnet bot//
	1.15f, -1.0f, 0.0f,
	0.805f, -1.0f, 0.805f,
	0.0f, -1.0f, 1.15f,
	-0.805f, -1.0f, 0.805f,
	-1.15f, -1.0f, 0.0f,
	-0.805f, -1.0f, -0.805f,
	0.0f, -1.0f, -1.15f,
	0.805f, -1.0f, -0.805f,

	// Between coil and magnet top//
	1.15f, 1.0f, 0.0f,
	0.805f, 1.0f, 0.805f,
	0.0f, 1.0f, 1.15f,
	-0.805f, 1.0f, 0.805f,
	-1.15f, 1.0f, 0.0f,
	-0.805f, 1.0f, -0.805f,
	0.0f, 1.0f, -1.15f,
	0.805f, 1.0f, -0.805f,

	//////Near the coil///////

	-1.19f, 1.21f, 1.19f,
	-0.896f, 1.21f, 0.896f,
	-1.04f, 1.41f, 1.04f,
	-1.04f, 1.02f, 1.04f,

	-1.7f, 1.12f, 0.0f,
	-1.28f, 1.12f, 0.0f,
	-1.48f, 1.31f, 0.0f,
	-1.48f, 0.92f, 0.0f,

	-1.19f, 1.045f, -1.19f,
	-0.896f, 1.045f, -0.896f,
	-1.04f, 1.235f, -1.04f,
	-1.04f, 0.845f, -1.04f,

	0.0f, 0.97f, -1.7f,
	0.0f, 0.97f, -1.28f,
	0.0f, 1.16f, -1.48f,
	0.0f, 0.77f, -1.48f,

	1.19f, 0.91f, -1.19f,
	0.896f, 0.91f, -0.896f,
	1.04f, 1.1f, -1.04f,
	1.04f, 0.71f, -1.04f,

	1.7f, 0.82f, 0.0f,
	1.28f, 0.82f, 0.0f,
	1.48f, 1.01f, 0.0f,
	1.48f, 0.62f, 0.0f,

	1.19f, 0.76f, 1.19f,
	0.896f, 0.76f, 0.896f,
	1.04f, 0.95f, 1.04f,
	1.04f, 0.56f, 1.04f,

	0.0f, 0.67f, 1.7f,
	0.0f, 0.67f, 1.28f,
	0.0f, 0.86f, 1.48f,
	0.0f, 0.47f, 1.48f,

	-1.19f, 0.60f, 1.19f,
	-0.896f, 0.60f, 0.896f,
	-1.04f, 0.79f, 1.04f,
	-1.04f, 0.40f, 1.04f,

	-1.7f, 0.52f, 0.0f,
	-1.28f, 0.52f, 0.0f,
	-1.48f, 0.71f, 0.0f,
	-1.48f, 0.32f, 0.0f,

	-1.19f, 0.46f, -1.19f,
	-0.896f, 0.46f, -0.896f,
	-1.04f, 0.65f, -1.04f,
	-1.04f, 0.26f, -1.04f,

	0.0f, 0.38f, -1.7f,
	0.0f, 0.38f, -1.28f,
	0.0f, 0.57f, -1.48f,
	0.0f, 0.18f, -1.48f,

	1.19f, 0.31f, -1.19f,
	0.896f, 0.31f, -0.896f,
	1.04f, 0.5f, -1.04f,
	1.04f, 0.11f, -1.04f,

	1.7f, 0.23f, 0.0f,
	1.28f, 0.23f, 0.0f,
	1.48f, 0.42f, 0.0f,
	1.48f, 0.03f, 0.0f,

	1.19f, 0.165f, 1.19f,
	0.896f, 0.165f, 0.896f,
	1.04f, 0.355f, 1.04f,
	1.04f, -0.035f, 1.04f,

	0.0f, 0.085f, 1.7f,
	0.0f, 0.085f, 1.28f,
	0.0f, 0.275f, 1.48f,
	0.0f, -0.115f, 1.48f,

	-1.19f, 0.015f, 1.19f,
	-0.896f, 0.015f, 0.896f,
	-1.04f, 0.205f, 1.04f,
	-1.04f, -0.185f, 1.04f,

	-1.7f, -0.07f, 0.0f,
	-1.28f, -0.07f, 0.0f,
	-1.48f, 0.12f, 0.0f,
	-1.48f, -0.27f, 0.0f,

	-1.19f, -0.155f, -1.19f,
	-0.896f, -0.155f, -0.896f,
	-1.04f, 0.035f, -1.04f,
	-1.04f, -0.355f, -1.04f,

	0.0f, -0.21f, -1.7f,
	0.0f, -0.21f, -1.28f,
	0.0f, -0.02f, -1.48f,
	0.0f, -0.41f, -1.48f,

	1.19f, -0.285f, -1.19f,
	0.896f, -0.285f, -0.896f,
	1.04f, -0.095f, -1.04f,
	1.04f, -0.485f, -1.04f,

	1.7f, -0.36f, 0.0f,
	1.28f, -0.36f, 0.0f,
	1.48f, -0.17f, 0.0f,
	1.48f, -0.56f, 0.0f,

	1.19f, -0.43f, 1.19f,
	0.896f, -0.43f, 0.896f,
	1.04f, -0.24f, 1.04f,
	1.04f, -0.63f, 1.04f,

	0.0f, -0.53f, 1.7f,
	0.0f, -0.53f, 1.28f,
	0.0f, -0.34f, 1.48f,
	0.0f, -0.73f, 1.48f,

	-1.19f, -0.58f, 1.19f,
	-0.896f, -0.58f, 0.896f,
	-1.04f, -0.39f, 1.04f,
	-1.04f, -0.78f, 1.04f,

	-1.7f, -0.66f, 0.0f,
	-1.28f, -0.66f, 0.0f,
	-1.48f, -0.47f, 0.0f,
	-1.48f, -0.86f, 0.0f,

	-1.19f, -0.72f, -1.19f,
	-0.896f, -0.72f, -0.896f,
	-1.04f, -0.53f, -1.04f,
	-1.04f, -0.92f, -1.04f,

	0.0f, -0.80f, -1.7f,
	0.0f, -0.80f, -1.28f,
	0.0f, -0.61f, -1.48f,
	0.0f, -1.0f, -1.48f,

	1.19f, -0.875f, -1.19f,
	0.896f, -0.875f, -0.896f,
	1.04f, -0.685f, -1.04f,
	1.04f, -1.075f, -1.04f,

	1.7f, -0.95f, 0.0f,
	1.28f, -0.95f, 0.0f,
	1.48f, -0.76f, 0.0f,
	1.48f, -1.15f, 0.0f,


	//Between the loops of the coil//
	/*-1.064f, 0.91f, 1.064f,
	-1.008f, 0.91f, 1.008f,

	-1.52f, 0.82f, 0.0f,
	-1.44f, 0.82f, 0.0f,

	-1.064f, 0.76f, -1.064f,
	-1.008f, 0.76f, -1.008f,

	0.0f, 0.67f, -1.52f,
	0.0f, 0.67f, -1.44f,

	1.064f, 0.60f, -1.064f,
	1.008f, 0.60f, -1.008f,

	1.52f, 0.52f, 0.0f,
	1.44f, 0.52f, 0.0f,

	1.064f, 0.46f, 1.064f,
	1.008f, 0.46f, 1.008f,

	0.0f, 0.38f, 1.52f,
	0.0f, 0.38f, 1.44f,

	-1.064f, 0.31f, 1.064f,
	-1.008f, 0.31f, 1.008f,

	-1.52f, 0.23f, 0.0f,
	-1.44f, 0.23f, 0.0f,

	-1.064f, 0.165f, -1.064f,
	-1.008f, 0.165f, -1.008f,

	0.0f, 0.085f, -1.52f,
	0.0f, 0.085f, -1.44f,

	1.064f, 0.015f, -1.064f,
	1.008f, 0.015f, -1.008f,

	1.52f, -0.07f, 0.0f,
	1.44f, -0.07f, 0.0f,

	1.064f, -0.155f, 1.064f,
	1.008f, -0.155f, 1.008f,

	0.0f, -0.21f, 1.52f,
	0.0f, -0.21f, 1.44f,

	-1.064f, -0.285f, 1.064f,
	-1.008f, -0.285f, 1.008f,

	-1.52f, -0.36f, 0.0f,
	-1.44f, -0.36f, 0.0f,

	-1.064f, -0.43f, -1.064f,
	-1.008f, -0.43f, -1.008f,

	0.0f, -0.53f, -1.52f,
	0.0f, -0.53f, -1.44f,

	1.064f, -0.58f, -1.064f,
	1.008f, -0.58f, -1.008f,

	1.52f, -0.66f, 0.0f,
	1.44f, -0.66f, 0.0f,

	//Near coil green

	-1.386f, 1.21f, 1.386f,
	-1.98f, 1.12f, 0.0f,
	-1.386f, 1.045f, -1.386f,
	0.0f, 0.97f, -1.98f,
	
	1.386f, 0.91f, -1.386f,
	1.90f, 0.82f, 0.0f,
	1.33f, 0.76f, 1.33f,
	0.0f, 0.67f, 1.90f,
	
	-1.302f, 0.60f, 1.302f,
	-1.86f, 0.52f, 0.0f,
	-1.274f, 0.46f, -1.274f,
	0.0f, 0.38f, -1.82f,

	1.274f, 0.31f, -1.274f,
	1.82f, 0.23f, 0.0f,	
	1.274f, 0.165f, 1.274f,
	0.0f, 0.085f, 1.82f,
	
	-1.274f, 0.015f, 1.274f,
	-1.82f, -0.07f, 0.0f,	
	-1.274f, -0.155f, -1.274f,	
	0.0f, -0.21f, -1.82f,
	
	1.274f, -0.285f, -1.274f,	
	1.82f, -0.36f, 0.0f,	
	1.274f, -0.43f, 1.274f,	
	0.0f, -0.53f, 1.82f,
	
	-1.274f, -0.58f, 1.274f,	
	-1.82f, -0.66f, 0.0f,	
	-1.274f, -0.72f, -1.274f,
	0.0f, -0.80f, -1.90f,

	1.386f, -0.875f, -1.386f,
	1.98f, -0.95f, 0.0f,	*/

// Up Magnet Yellow

1.4f, 1.76f, 0.0f,
1.0f, 1.76f, 0.0f,
0.52f, 1.76f, 0.0f,
0.0f, 1.76f, 0.0f,
-0.52f, 1.76f, 0.0f,
-1.0f, 1.76f, 0.0f,
-1.4f, 1.76f, 0.0f,

	// Inner green//

2.0f, 0.0f, 0.0f, 
2.0f, 0.25f, 0.0f, 
2.0f, 0.5f, 0.0f, 
2.0f, 0.75f, 0.0f, 
2.0f, 1.0f, 0.0f,
2.0f, 1.25f, 0.0f,
2.0f, 1.5f, 0.0f,
1.94f, 1.76f, 0.0f,
1.73f, 2.0f, 0.0f,
1.4f, 2.2f, 0.0f,
1.0f, 2.37f, 0.0f,
0.52f, 2.47f, 0.0f,
0.0f, 2.5f, 0.0f, 

-0.52f, 2.47f, 0.0f, 
-1.0f, 2.37f, 0.0f, 
-1.4f, 2.2f, 0.0f, 
-1.73f, 2.0f, 0.0f, 
-1.94f, 1.76f, 0.0f, 
-2.0f, 1.5f, 0.0f, 
-2.0f, 1.25f, 0.0f,
-2.0f, 1.0f, 0.0f,
-2.0f, 0.75f, 0.0f,
-2.0f, 0.5f, 0.0f,
-2.0f, 0.25f, 0.0f,
-2.0f, 0.0f, 0.0f,

-2.0f, -0.25f, 0.0f,
-2.0f, -0.5f, 0.0f,
-2.0f, -0.75f, 0.0f,
-2.0f, -1.0f, 0.0f,
-2.0f, -1.25f, 0.0f,
-2.0f, -1.5f, 0.0f, 
-1.94f, -1.76f, 0.0f, 
-1.73f, -2.0f, 0.0f, 
-1.4f, -2.2f, 0.0f, 
-1.0f, -2.37f, 0.0f, 
-0.52f, -2.47f, 0.0f, 
0.0f, -2.5f, 0.0f,

0.52f, -2.47f, 0.0f, 
1.0f, -2.37f, 0.0f, 
1.4f, -2.2f, 0.0f, 
1.73f, -2.0f, 0.0f,
1.94f, -1.76f, 0.0f, 
2.0f, -1.5f, 0.0f,
2.0f, -1.25f, 0.0f,
2.0f, -1.0f, 0.0f,
2.0f, -0.75f, 0.0f,
2.0f, -0.5f, 0.0f,
2.0f, -0.25f, 0.0f,


	//Middle 1 Inner green//

2.5f, 0.0f, 0.0f, 
2.5f, 0.25f, 0.0f, 
2.5f, 0.5f, 0.0f, 
2.5f, 0.75f, 0.0f, 
2.5f, 1.0f, 0.0f, 
2.5f, 1.25f, 0.0f, 
2.46202f, 1.68412f, 0.0f, 
2.34923f, 2.10505f, 0.0f, 
2.16506f, 2.5f, 0.0f, 
1.91511f, 2.85697f, 0.0f, 
1.60697f, 3.16511f, 0.0f, 
1.25f, 3.41506f, 0.0f, 
0.85505f, 3.59923f, 0.0f, 
0.43412f, 3.71202f, 0.0f, 
-1.09278e-007f, 3.75f, 0.0f,

-0.43412f, 3.71202f, 0.0f, 
-0.855051f, 3.59923f, 0.0f, 
-1.25f, 3.41506f, 0.0f, 
-1.60697f, 3.16511f, 0.0f, 
-1.91511f, 2.85697f, 0.0f, 
-2.16506f, 2.5f, 0.0f, 
-2.34923f, 2.10505f, 0.0f, 
-2.46202f, 1.68412f, 0.0f, 
-2.5f, 1.25f, 0.0f, 
-2.5f, 1.0f, 0.0f, 
-2.5f, 0.75f, 0.0f, 
-2.5f, 0.5f, 0.0f, 
-2.5f, 0.25f, 0.0f, 
-2.5f, 0.0f, 0.0f, 

-2.5f, -0.25f, 0.0f, 
-2.5f, -0.5f, 0.0f, 
-2.5f, -0.75f, 0.0f, 
-2.5f, -1.0f, 0.0f, 
-2.5f, -1.25f, 0.0f, 
-2.46202f, -1.68412f, 0.0f, 
-2.34923f, -2.10505f, 0.0f, 
-2.16506f, -2.5f, 0.0f, 
-1.91511f, -2.85697f, 0.0f, 
-1.60697f, -3.16511f, 0.0f, 
-1.25f, -3.41506f, 0.0f, 
-0.85505f, -3.59923f, 0.0f, 
-0.43412f, -3.71202f, 0.0f, 
2.98122e-008f, -3.75f, 0.0f, 

0.43412f, -3.71202f, 0.0f, 
0.85505f, -3.59923f, 0.0f, 
1.25f, -3.41506f, 0.0f, 
1.60697f, -3.16511f, 0.0f, 
1.91511f, -2.85697f, 0.0f, 
2.16506f, -2.5f, 0.0f, 
2.34923f, -2.10505f, 0.0f, 
2.46202f, -1.68412f, 0.0f, 
2.5f, -1.25f, 0.0f, 
2.5f, -1.0f, 0.0f, 
2.5f, -0.75f, 0.0f, 
2.5f, -0.5f, 0.0f, 
2.5f, -0.25f, 0.0f, 
 

//Middle 2 Inner green//

3.0f, 0.0f, 0.0f, 
3.0f, 0.25f, 0.0f, 
3.0f, 0.5f, 0.0f, 
3.0f, 0.75f, 0.0f, 
3.0f, 1.0f, 0.0f, 
3.0f, 1.25f, 0.0f, 
3.0f, 1.5f, 0.0f, 
2.95442f, 2.02094f, 0.0f, 
2.81908f, 2.52606f, 0.0f, 
2.59808f, 3.0f, 0.0f, 

2.29813f, 3.42836f, 0.0f, 
1.92836f, 3.79813f, 0.0f, 
1.5f, 4.09808f, 0.0f, 
1.02606f, 4.31908f, 0.0f, 
0.520944f, 4.45442f, 0.0f, 
-1.31134e-007f, 4.5f, 0.0f, 
-0.520945f, 4.45442f, 0.0f, 
-1.02606f, 4.31908f, 0.0f, 
-1.5f, 4.09808f, 0.0f, 
-1.92836f, 3.79813f, 0.0f, 

-2.29813f, 3.42836f, 0.0f, 
-2.59808f, 3.0f, 0.0f, 
-2.81908f, 2.52606f, 0.0f, 
-2.95442f, 2.02094f, 0.0f, 
-3.0f, 1.5f, 0.0f, 
-3.0f, 1.25f, 0.0f, 
-3.0f, 1.0f, 0.0f, 
-3.0f, 0.75f, 0.0f, 
-3.0f, 0.5f, 0.0f, 
-3.0f, 0.25f, 0.0f, 

-3.0f, 0.0f, 0.0f, 
-3.0f, -0.25f, 0.0f, 
-3.0f, -0.5f, 0.0f, 
-3.0f, -0.75f, 0.0f, 
-3.0f, -1.0f, 0.0f, 
-3.0f, -1.25f, 0.0f, 
-3.0f, -1.5f, 0.0f, 
-2.95442f, -2.02094f, 0.0f, 
-2.81908f, -2.52606f, 0.0f, 
-2.59808f, -3.0f, 0.0f, 

-2.29813f, -3.42836f, 0.0f, 
-1.92836f, -3.79813f, 0.0f, 
-1.5f, -4.09808f, 0.0f, 
-1.02606f, -4.31908f, 0.0f, 
-0.520944f, -4.45442f, 0.0f, 
3.57746e-008f, -4.5f, 0.0f, 
0.520944f, -4.45442f, 0.0f, 
1.02606f, -4.31908f, 0.0f, 
1.5f, -4.09808f, 0.0f, 
1.92836f, -3.79813f, 0.0f, 

2.29813f, -3.42836f, 0.0f, 
2.59808f, -3.0f, 0.0f, 
2.81908f, -2.52606f, 0.0f, 
2.95442f, -2.02094f, 0.0f, 
3.0f, -1.5f, 0.0f, 
3.0f, -1.25f, 0.0f, 
3.0f, -1.0f, 0.0f, 
3.0f, -0.75f, 0.0f, 
3.0f, -0.5f, 0.0f, 
3.0f, -0.25f, 0.0f, 



	//Middle 3 Inner green//

3.5f, 0.0f, 0.0f, 
3.5f, 0.25f, 0.0f, 
3.5f, 0.5f, 0.0f, 
3.5f, 0.75f, 0.0f, 

3.5f, 1.0f, 0.0f, 
3.5f, 1.25f, 0.0f, 
3.5f, 1.5f, 0.0f, 
3.5f, 1.75f, 0.0f, 
3.44683f, 2.35777f, 0.0f, 
3.28892f, 2.94707f, 0.0f, 
3.03109f, 3.5f, 0.0f, 
2.68116f, 3.99976f, 0.0f, 
2.24976f, 4.43116f, 0.0f, 
1.75f, 4.78109f, 0.0f, 

1.19707f, 5.03892f, 0.0f, 
0.607768f, 5.19683f, 0.0f, 
-1.5299e-007f, 5.25f, 0.0f, 
-0.607769f, 5.19683f, 0.0f, 
-1.19707f, 5.03892f, 0.0f, 
-1.75f, 4.78109f, 0.0f, 
-2.24976f, 4.43116f, 0.0f, 
-2.68116f, 3.99976f, 0.0f, 
-3.03109f, 3.5f, 0.0f, 
-3.28892f, 2.94707f, 0.0f, 

-3.44683f, 2.35777f, 0.0f, 
-3.5f, 1.75f, 0.0f, 
-3.5f, 1.5f, 0.0f, 
-3.5f, 1.25f, 0.0f, 
-3.5f, 1.0f, 0.0f, 
-3.5f, 0.75f, 0.0f, 
-3.5f, 0.5f, 0.0f, 
-3.5f, 0.25f, 0.0f, 
-3.5f, 0.0f, 0.0f, 
-3.5f, -0.25f, 0.0f, 

-3.5f, -0.5f, 0.0f, 
-3.5f, -0.75f, 0.0f, 
-3.5f, -1.0f, 0.0f, 
-3.5f, -1.25f, 0.0f, 
-3.5f, -1.5f, 0.0f, 
-3.5f, -1.75f, 0.0f, 
-3.44683f, -2.35777f, 0.0f, 
-3.28892f, -2.94707f, 0.0f, 
-3.03109f, -3.5f, 0.0f, 
-2.68116f, -3.99976f, 0.0f, 

-2.24976f, -4.43116f, 0.0f, 
-1.75f, -4.78109f, 0.0f, 
-1.19707f, -5.03892f, 0.0f, 
-0.607768f, -5.19683f, 0.0f, 
4.17371e-008f, -5.25f, 0.0f, 
0.607769f, -5.19683f, 0.0f, 
1.19707f, -5.03892f, 0.0f, 
1.75f, -4.78109f, 0.0f, 
2.24976f, -4.43115f, 0.0f, 
2.68116f, -3.99976f, 0.0f, 

3.03109f, -3.5f, 0.0f, 
3.28892f, -2.94707f, 0.0f, 
3.44683f, -2.35777f, 0.0f, 
3.5f, -1.75f, 0.0f, 
3.5f, -1.5f, 0.0f, 
3.5f, -1.25f, 0.0f, 
3.5f, -1.0f, 0.0f, 
3.5f, -0.75f, 0.0f, 
3.5f, -0.5f, 0.0f, 
3.5f, -0.25f, 0.0f, 



	// Outer green//

4.0f, 0.0f, 0.0f, 
4.0f, 0.25f, 0.0f, 
4.0f, 0.5f, 0.0f, 
4.0f, 0.75f, 0.0f, 
4.0f, 1.0f, 0.0f, 
4.0f, 1.25f, 0.0f, 
4.0f, 1.5f, 0.0f, 
4.0f, 1.75f, 0.0f, 
4.0f, 2.0f, 0.0f, 
3.93923f, 2.69459f, 0.0f, 

3.75877f, 3.36808f, 0.0f, 
3.4641f, 4.0f, 0.0f, 
3.06418f, 4.57115f, 0.0f, 
2.57115f, 5.06418f, 0.0f, 
2.0f, 5.4641f, 0.0f, 
1.36808f, 5.75877f, 0.0f, 
0.694592f, 5.93923f, 0.0f, 
-1.74846e-007f, 6.0f, 0.0f, 
-0.694593f, 5.93923f, 0.0f, 
-1.36808f, 5.75877f, 0.0f, 

-2.0f, 5.4641f, 0.0f, 
-2.57115f, 5.06418f, 0.0f, 
-3.06418f, 4.57115f, 0.0f, 
-3.4641f, 4.0f, 0.0f, 
-3.75877f, 3.36808f, 0.0f, 
-3.93923f, 2.69459f, 0.0f, 
-4.0f, 2.0f, 0.0f, 
-4.0f, 1.75f, 0.0f, 
-4.0f, 1.5f, 0.0f, 
-4.0f, 1.25f, 0.0f, 

-4.0f, 1.0f, 0.0f, 
-4.0f, 0.75f, 0.0f, 
-4.0f, 0.5f, 0.0f, 
-4.0f, 0.25f, 0.0f, 
-4.0f, 0.0f, 0.0f, 
-4.0f, -0.25f, 0.0f, 
-4.0f, -0.5f, 0.0f, 
-4.0f, -0.75f, 0.0f, 
-4.0f, -1.0f, 0.0f, 
-4.0f, -1.25f, 0.0f, 

-4.0f, -1.5f, 0.0f, 
-4.0f, -1.75f, 0.0f, 
-4.0f, -2.0f, 0.0f, 
-3.93923f, -2.69459f, 0.0f, 
-3.75877f, -3.36808f, 0.0f, 
-3.4641f, -4.0f, 0.0f, 
-3.06418f, -4.57115f, 0.0f, 
-2.57115f, -5.06418f, 0.0f, 
-2.0f, -5.4641f, 0.0f, 
-1.36808f, -5.75877f, 0.0f, 

-0.694593f, -5.93923f, 0.0f, 
4.76995e-008f, -6.0f, 0.0f, 
0.694593f, -5.93923f, 0.0f, 
1.36808f, -5.75877f, 0.0f, 
2.0f, -5.4641f, 0.0f, 
2.57115f, -5.06418f, 0.0f, 
3.06418f, -4.57115f, 0.0f, 
3.4641f, -4.0f, 0.0f, 
3.75877f, -3.36808f, 0.0f, 
3.93923f, -2.69459f, 0.0f, 

4.0f, -2.0f, 0.0f, 
4.0f, -1.75f, 0.0f, 
4.0f, -1.5f, 0.0f, 
4.0f, -1.25f, 0.0f, 
4.0f, -1.0f, 0.0f, 
4.0f, -0.75f, 0.0f, 
4.0f, -0.5f, 0.0f, 
4.0f, -0.25f, 0.0f, 



	// Inner blue//

4.4f, 0.0f, 0.0f, 
4.4f, 0.25f, 0.0f, 
4.4f, 0.5f, 0.0f, 
4.4f, 0.75f, 0.0f, 
4.4f, 1.0f, 0.0f, 
4.4f, 1.25f, 0.0f, 
4.4f, 1.5f, 0.0f, 
4.4f, 1.75f, 0.0f, 
4.4f, 2.0f, 0.0f, 
4.4f, 2.2f, 0.0f, 

4.33315f, 2.96405f, 0.0f, 
4.13465f, 3.70489f, 0.0f, 
3.81051f, 4.4f, 0.0f, 
3.3706f, 5.02827f, 0.0f, 
2.82827f, 5.5706f, 0.0f, 
2.2f, 6.01051f, 0.0f, 
1.50489f, 6.33465f, 0.0f, 
0.764052f, 6.53315f, 0.0f, 
-1.9233e-007f, 6.6f, 0.0f, 
-0.764052f, 6.53315f, 0.0f, 

-1.50489f, 6.33465f, 0.0f, 
-2.2f, 6.01051f, 0.0f, 
-2.82827f, 5.5706f, 0.0f, 
-3.3706f, 5.02827f, 0.0f, 
-3.81051f, 4.4f, 0.0f, 
-4.13465f, 3.70489f, 0.0f, 
-4.33315f, 2.96405f, 0.0f, 
-4.4f, 2.2f, 0.0f, 
-4.4f, 2.0f, 0.0f,
-4.4f, 1.75f, 0.0f, 
-4.4f, 1.5f, 0.0f,

-4.4f, 1.25f, 0.0f,
-4.4f, 1.0f, 0.0f,
-4.4f, 0.75f, 0.0f, 
-4.4f, 0.5f, 0.0f,
-4.4f, 0.25f, 0.0f, 
-4.4f, 0.0f, 0.0f, 
-4.4f, -0.25f, 0.0f, 
-4.4f, -0.5f, 0.0f, 
-4.4f, -0.75f, 0.0f, 
-4.4f, -1.0f, 0.0f, 

-4.4f, -1.25f, 0.0f, 
-4.4f, -1.5f, 0.0f, 
-4.4f, -1.75f, 0.0f, 
-4.4f, -2.0f, 0.0f, 
-4.4f, -2.2f, 0.0f, 
-4.33315f, -2.96405f, 0.0f, 
-4.13465f, -3.70489f, 0.0f, 
-3.81051f, -4.4f, 0.0f, 
-3.37059f, -5.02827f, 0.0f, 
-2.82827f, -5.5706f, 0.0f, 

-2.2f, -6.01051f, 0.0f, 
-1.50489f, -6.33465f, 0.0f, 
-0.764052f, -6.53315f, 0.0f, 
5.24695e-008f, -6.6f, 0.0f, 
0.764052f, -6.53315f, 0.0f, 
1.50489f, -6.33465f, 0.0f, 
2.2f, -6.01051f, 0.0f, 
2.82827f, -5.57059f, 0.0f, 
3.3706f, -5.02826f, 0.0f, 
3.81051f, -4.4f, 0.0f, 

4.13465f, -3.70489f, 0.0f, 
4.33315f, -2.96405f, 0.0f,
4.4f, -2.2f, 0.0f, 
4.4f, -2.0f, 0.0f,
4.4f, -1.75f, 0.0f,
4.4f, -1.5f, 0.0f,
4.4f, -1.25f, 0.0f,
4.4f, -1.0f, 0.0f,
4.4f, -0.75f, 0.0f, 
4.4f, -0.5f, 0.0f, 
4.4f, -0.25f, 0.0f, 


// Middle 1 Inner Blue

5.4f, 0.0f, 0.0f, 
5.4f, 0.25f, 0.0f, 
5.4f, 0.5f, 0.0f, 
5.4f, 0.75f, 0.0f, 
5.4f, 1.0f, 0.0f, 
5.4f, 1.25f, 0.0f, 
5.4f, 1.5f, 0.0f, 
5.4f, 1.75f, 0.0f, 
5.4f, 2.0f, 0.0f, 
5.4f, 2.25f, 0.0f, 
5.4f, 2.5f, 0.0f, 
5.4f, 2.7f, 0.0f, 
5.31796f, 3.6377f, 0.0f, 
5.07434f, 4.54691f, 0.0f, 
4.67654f, 5.4f, 0.0f, 
4.13664f, 6.17105f, 0.0f, 
3.47105f, 6.83664f, 0.0f, 
2.7f, 7.37654f, 0.0f, 
1.84691f, 7.77434f, 0.0f, 
0.9377f, 8.01796f, 0.0f, 
-2.36042e-007f, 8.1f, 0.0f, 
-0.9377f, 8.01796f, 0.0f, 
-1.84691f, 7.77434f, 0.0f, 
-2.7f, 7.37654f, 0.0f, 
-3.47105f, 6.83664f, 0.0f, 
-4.13664f, 6.17105f, 0.0f, 
-4.67654f, 5.4f, 0.0f, 
-5.07434f, 4.54691f, 0.0f, 
-5.31796f, 3.6377f, 0.0f, 
-5.4f, 2.7f, 0.0f, 
-5.4f, 2.5f, 0.0f, 
-5.4f, 2.25f, 0.0f, 
-5.4f, 2.0f, 0.0f, 
-5.4f, 1.75f, 0.0f, 
-5.4f, 1.5f, 0.0f, 
-5.4f, 1.25f, 0.0f, 
-5.4f, 1.0f, 0.0f, 
-5.4f, 0.75f, 0.0f, 
-5.4f, 0.5f, 0.0f, 
-5.4f, 0.25f, 0.0f, 
-5.4f, 0.0f, 0.0f, 
-5.4f, -0.25f, 0.0f, 
-5.4f, -0.5f, 0.0f, 
-5.4f, -0.75f, 0.0f, 
-5.4f, -1.0f, 0.0f, 
-5.4f, -1.25f, 0.0f, 
-5.4f, -1.5f, 0.0f, 
-5.4f, -1.75f, 0.0f, 
-5.4f, -2.0f, 0.0f, 
-5.4f, -2.25f, 0.0f, 
-5.4f, -2.5f, 0.0f, 
-5.4f, -2.7f, 0.0f, 
-5.31796f, -3.6377f, 0.0f, 
-5.07434f, -4.54691f, 0.0f, 
-4.67654f, -5.4f, 0.0f, 
-4.13664f, -6.17105f, 0.0f, 
-3.47105f, -6.83664f, 0.0f, 
-2.7f, -7.37654f, 0.0f, 
-1.84691f, -7.77434f, 0.0f, 
-0.9377f, -8.01796f, 0.0f, 
6.43944e-008f, -8.1f, 0.0f, 
0.9377f, -8.01796f, 0.0f, 
1.84691f, -7.77434f, 0.0f, 
2.7f, -7.37654f, 0.0f, 
3.47105f, -6.83664f, 0.0f, 
4.13664f, -6.17105f, 0.0f, 
4.67654f, -5.4f, 0.0f, 
5.07434f, -4.54691f, 0.0f, 
5.31796f, -3.6377f, 0.0f, 
5.4f, -2.7f, 0.0f, 
5.4f, -2.5f, 0.0f, 
5.4f, -2.25f, 0.0f, 
5.4f, -2.0f, 0.0f, 
5.4f, -1.75f, 0.0f, 
5.4f, -1.5f, 0.0f, 
5.4f, -1.25f, 0.0f, 
5.4f, -1.0f, 0.0f, 
5.4f, -0.75f, 0.0f, 
5.4f, -0.5f, 0.0f, 
5.4f, -0.25f, 0.0f, 

 
 // Middle 2 Inner Blue

 6.4f, 0.0f, 0.0f, 
6.4f, 0.25f, 0.0f, 
6.4f, 0.5f, 0.0f, 
6.4f, 0.75f, 0.0f, 
6.4f, 1.0f, 0.0f, 
6.4f, 1.25f, 0.0f, 
6.4f, 1.5f, 0.0f, 
6.4f, 1.75f, 0.0f, 
6.4f, 2.0f, 0.0f, 
6.4f, 2.25f, 0.0f, 
6.4f, 2.5f, 0.0f, 
6.4f, 2.75f, 0.0f, 
6.4f, 3.0f, 0.0f, 
6.4f, 3.2f, 0.0f, 
6.30277f, 4.31135f, 0.0f, 
6.01403f, 5.38893f, 0.0f, 
5.54256f, 6.4f, 0.0f, 
4.90268f, 7.31384f, 0.0f, 
4.11384f, 8.10268f, 0.0f, 
3.2f, 8.74256f, 0.0f, 
2.18893f, 9.21403f, 0.0f, 
1.11135f, 9.50277f, 0.0f, 
-2.79753e-007f, 9.6f, 0.0f, 
-1.11135f, 9.50277f, 0.0f, 
-2.18893f, 9.21403f, 0.0f, 
-3.2f, 8.74256f, 0.0f, 
-4.11384f, 8.10268f, 0.0f, 
-4.90268f, 7.31384f, 0.0f, 
-5.54256f, 6.4f, 0.0f, 
-6.01403f, 5.38893f, 0.0f, 
-6.30277f, 4.31135f, 0.0f, 
-6.4f, 3.2f, 0.0f, 
-6.4f, 3.0f, 0.0f, 
-6.4f, 2.75f, 0.0f, 
-6.4f, 2.5f, 0.0f, 
-6.4f, 2.25f, 0.0f, 
-6.4f, 2.0f, 0.0f, 
-6.4f, 1.75f, 0.0f, 
-6.4f, 1.5f, 0.0f, 
-6.4f, 1.25f, 0.0f, 
-6.4f, 1.0f, 0.0f, 
-6.4f, 0.75f, 0.0f, 
-6.4f, 0.5f, 0.0f, 
-6.4f, 0.25f, 0.0f, 
-6.4f, 0.0f, 0.0f, 
-6.4f, -0.25f, 0.0f, 
-6.4f, -0.5f, 0.0f, 
-6.4f, -0.75f, 0.0f, 
-6.4f, -1.0f, 0.0f, 
-6.4f, -1.25f, 0.0f, 
-6.4f, -1.5f, 0.0f, 
-6.4f, -1.75f, 0.0f, 
-6.4f, -2.0f, 0.0f, 
-6.4f, -2.25f, 0.0f, 
-6.4f, -2.5f, 0.0f, 
-6.4f, -2.75f, 0.0f, 
-6.4f, -3.0f, 0.0f, 
-6.4f, -3.2f, 0.0f, 
-6.30277f, -4.31135f, 0.0f, 
-6.01403f, -5.38893f, 0.0f, 
-5.54256f, -6.4f, 0.0f, 
-4.90268f, -7.31384f, 0.0f, 
-4.11384f, -8.10269f, 0.0f, 
-3.2f, -8.74256f, 0.0f, 
-2.18893f, -9.21403f, 0.0f, 
-1.11135f, -9.50277f, 0.0f, 
7.63192e-008f, -9.6f, 0.0f, 
1.11135f, -9.50277f, 0.0f, 
2.18893f, -9.21403f, 0.0f, 
3.2f, -8.74256f, 0.0f, 
4.11384f, -8.10268f, 0.0f, 
4.90269f, -7.31384f, 0.0f, 
5.54256f, -6.4f, 0.0f, 
6.01403f, -5.38893f, 0.0f, 
6.30277f, -4.31135f, 0.0f, 
6.4f, -3.2f, 0.0f, 
6.4f, -3.0f, 0.0f, 
6.4f, -2.75f, 0.0f, 
6.4f, -2.5f, 0.0f, 
6.4f, -2.25f, 0.0f, 
6.4f, -2.0f, 0.0f, 
6.4f, -1.75f, 0.0f, 
6.4f, -1.5f, 0.0f, 
6.4f, -1.25f, 0.0f, 
6.4f, -1.0f, 0.0f, 
6.4f, -0.75f, 0.0f, 
6.4f, -0.5f, 0.0f, 
6.4f, -0.25f, 0.0f, 

//Middle 3 Inner Blue

7.4f, 0.0f, 0.0f, 
7.4f, 0.25f, 0.0f, 
7.4f, 0.5f, 0.0f, 
7.4f, 0.75f, 0.0f, 
7.4f, 1.0f, 0.0f, 
7.4f, 1.25f, 0.0f, 
7.4f, 1.5f, 0.0f, 
7.4f, 1.75f, 0.0f, 
7.4f, 2.0f, 0.0f, 
7.4f, 2.25f, 0.0f, 
7.4f, 2.5f, 0.0f, 
7.4f, 2.75f, 0.0f, 
7.4f, 3.0f, 0.0f, 
7.4f, 3.25f, 0.0f, 
7.4f, 3.5f, 0.0f, 
7.4f, 3.7f, 0.0f, 
7.28758f, 4.985f, 0.0f, 
6.95373f, 6.23095f, 0.0f, 
6.40859f, 7.4f, 0.0f, 
5.66873f, 8.45663f, 0.0f, 
4.75663f, 9.36873f, 0.0f, 
3.7f, 10.1086f, 0.0f, 
2.53095f, 10.6537f, 0.0f, 
1.285f, 10.9876f, 0.0f, 
-3.23464e-007f, 11.1f, 0.0f, 
-1.285f, 10.9876f, 0.0f, 
-2.53095f, 10.6537f, 0.0f, 
-3.7f, 10.1086f, 0.0f, 
-4.75663f, 9.36873f, 0.0f, 
-5.66873f, 8.45663f, 0.0f, 
-6.40859f, 7.4f, 0.0f, 
-6.95373f, 6.23095f, 0.0f, 
-7.28758f, 4.985f, 0.0f, 
-7.4f, 3.7f, 0.0f, 
-7.4f, 3.5f, 0.0f, 
-7.4f, 3.25f, 0.0f, 
-7.4f, 3.0f, 0.0f, 
-7.4f, 2.75f, 0.0f, 
-7.4f, 2.5f, 0.0f, 
-7.4f, 2.25f, 0.0f, 
-7.4f, 2.0f, 0.0f, 
-7.4f, 1.75f, 0.0f, 
-7.4f, 1.5f, 0.0f, 
-7.4f, 1.25f, 0.0f, 
-7.4f, 1.0f, 0.0f, 
-7.4f, 0.75f, 0.0f, 
-7.4f, 0.5f, 0.0f, 
-7.4f, 0.25f, 0.0f, 
-7.4f, 0.0f, 0.0f, 
-7.4f, -0.25f, 0.0f, 
-7.4f, -0.5f, 0.0f, 
-7.4f, -0.75f, 0.0f, 
-7.4f, -1.0f, 0.0f, 
-7.4f, -1.25f, 0.0f, 
-7.4f, -1.5f, 0.0f, 
-7.4f, -1.75f, 0.0f, 
-7.4f, -2.0f, 0.0f, 
-7.4f, -2.25f, 0.0f, 
-7.4f, -2.5f, 0.0f, 
-7.4f, -2.75f, 0.0f, 
-7.4f, -3.0f, 0.0f, 
-7.4f, -3.25f, 0.0f, 
-7.4f, -3.5f, 0.0f, 
-7.4f, -3.7f, 0.0f, 
-7.28758f, -4.985f, 0.0f, 
-6.95373f, -6.23095f, 0.0f, 
-6.40859f, -7.4f, 0.0f, 
-5.66873f, -8.45663f, 0.0f, 
-4.75663f, -9.36873f, 0.0f, 
-3.7f, -10.1086f, 0.0f, 
-2.53095f, -10.6537f, 0.0f, 
-1.285f, -10.9876f, 0.0f, 
8.82441e-008f, -11.1f, 0.0f, 
1.285f, -10.9876f, 0.0f, 
2.53095f, -10.6537f, 0.0f, 
3.7f, -10.1086f, 0.0f, 
4.75663f, -9.36873f, 0.0f, 
5.66873f, -8.45663f, 0.0f, 
6.40859f, -7.4f, 0.0f, 
6.95373f, -6.23095f, 0.0f, 
7.28758f, -4.985f, 0.0f, 
7.4f, -3.7f, 0.0f, 
7.4f, -3.5f, 0.0f, 
7.4f, -3.25f, 0.0f, 
7.4f, -3.0f, 0.0f, 
7.4f, -2.75f, 0.0f, 
7.4f, -2.5f, 0.0f, 
7.4f, -2.25f, 0.0f, 
7.4f, -2.0f, 0.0f, 
7.4f, -1.75f, 0.0f, 
7.4f, -1.5f, 0.0f, 
7.4f, -1.25f, 0.0f, 
7.4f, -1.0f, 0.0f, 
7.4f, -0.75f, 0.0f, 
7.4f, -0.5f, 0.0f, 
7.4f, -0.25f, 0.0f,

// Middle 4 Inner Blue

8.4f, 0.0f, 0.0f, 
8.4f, 0.25f, 0.0f, 
8.4f, 0.5f, 0.0f, 
8.4f, 0.75f, 0.0f, 
8.4f, 1.0f, 0.0f, 
8.4f, 1.25f, 0.0f, 
8.4f, 1.5f, 0.0f, 
8.4f, 1.75f, 0.0f, 
8.4f, 2.0f, 0.0f, 
8.4f, 2.25f, 0.0f, 
8.4f, 2.5f, 0.0f, 
8.4f, 2.75f, 0.0f, 
8.4f, 3.0f, 0.0f, 
8.4f, 3.25f, 0.0f, 
8.4f, 3.5f, 0.0f, 
8.4f, 3.75f, 0.0f, 
8.4f, 4.0f, 0.0f, 
8.4f, 4.2f, 0.0f, 
8.27238f, 5.65865f, 0.0f, 
7.89342f, 7.07297f, 0.0f, 
7.27461f, 8.4f, 0.0f, 
6.43477f, 9.59942f, 0.0f, 
5.39942f, 10.6348f, 0.0f, 
4.2f, 11.4746f, 0.0f, 
2.87297f, 12.0934f, 0.0f, 
1.45864f, 12.4724f, 0.0f, 
-3.67176e-007f, 12.6f, 0.0f, 
-1.45864f, 12.4724f, 0.0f, 
-2.87297f, 12.0934f, 0.0f, 
-4.2f, 11.4746f, 0.0f, 
-5.39942f, 10.6348f, 0.0f, 
-6.43477f, 9.59942f, 0.0f, 
-7.27461f, 8.4f, 0.0f, 
-7.89342f, 7.07297f, 0.0f, 
-8.27238f, 5.65864f, 0.0f, 
-8.4f, 4.2f, 0.0f, 
-8.4f, 4.0f, 0.0f, 
-8.4f, 3.75f, 0.0f, 
-8.4f, 3.5f, 0.0f, 
-8.4f, 3.25f, 0.0f, 
-8.4f, 3.0f, 0.0f, 
-8.4f, 2.75f, 0.0f, 
-8.4f, 2.5f, 0.0f, 
-8.4f, 2.25f, 0.0f, 
-8.4f, 2.0f, 0.0f, 
-8.4f, 1.75f, 0.0f, 
-8.4f, 1.5f, 0.0f, 
-8.4f, 1.25f, 0.0f, 
-8.4f, 1.0f, 0.0f, 
-8.4f, 0.75f, 0.0f, 
-8.4f, 0.5f, 0.0f, 
-8.4f, 0.25f, 0.0f, 
-8.4f, 0.0f, 0.0f, 
-8.4f, -0.25f, 0.0f, 
-8.4f, -0.5f, 0.0f, 
-8.4f, -0.75f, 0.0f, 
-8.4f, -1.0f, 0.0f, 
-8.4f, -1.25f, 0.0f, 
-8.4f, -1.5f, 0.0f, 
-8.4f, -1.75f, 0.0f, 
-8.4f, -2.0f, 0.0f, 
-8.4f, -2.25f, 0.0f, 
-8.4f, -2.5f, 0.0f, 
-8.4f, -2.75f, 0.0f, 
-8.4f, -3.0f, 0.0f, 
-8.4f, -3.25f, 0.0f, 
-8.4f, -3.5f, 0.0f, 
-8.4f, -3.75f, 0.0f, 
-8.4f, -4.0f, 0.0f, 
-8.4f, -4.2f, 0.0f, 
-8.27238f, -5.65865f, 0.0f, 
-7.89342f, -7.07297f, 0.0f, 
-7.27461f, -8.4f, 0.0f, 
-6.43477f, -9.59942f, 0.0f, 
-5.39942f, -10.6348f, 0.0f, 
-4.2f, -11.4746f, 0.0f, 
-2.87297f, -12.0934f, 0.0f, 
-1.45864f, -12.4724f, 0.0f, 
1.00169e-007f, -12.6f, 0.0f, 
1.45864f, -12.4724f, 0.0f, 
2.87297f, -12.0934f, 0.0f, 
4.2f, -11.4746f, 0.0f, 
5.39942f, -10.6348f, 0.0f, 
6.43477f, -9.59941f, 0.0f, 
7.27461f, -8.4f, 0.0f, 
7.89342f, -7.07297f, 0.0f, 
8.27238f, -5.65864f, 0.0f, 
8.4f, -4.2f, 0.0f, 
8.4f, -4.0f, 0.0f, 
8.4f, -3.75f, 0.0f, 
8.4f, -3.5f, 0.0f, 
8.4f, -3.25f, 0.0f, 
8.4f, -3.0f, 0.0f, 
8.4f, -2.75f, 0.0f, 
8.4f, -2.5f, 0.0f, 
8.4f, -2.25f, 0.0f, 
8.4f, -2.0f, 0.0f, 
8.4f, -1.75f, 0.0f, 
8.4f, -1.5f, 0.0f, 
8.4f, -1.25f, 0.0f, 
8.4f, -1.0f, 0.0f, 
8.4f, -0.75f, 0.0f, 
8.4f, -0.5f, 0.0f, 
8.4f, -0.25f, 0.0f, 

 



	// Outer blue//
	0.0f, 24.0f, 0.0f,
	11.91f, 11.91f, 0.0f,
	13.71f, 1.0f, 0.0f,
	13.71f, 0.75f, 0.0f,
	13.71f, 0.5f, 0.0f,
	13.71f, 0.0f, 0.0f,
	13.71f, -0.5f, 0.0f,
	13.71f, -0.75f, 0.0f,
	13.71f, -1.0f, 0.0f,
	11.91f, -11.91f, 0.0f,
	0.0f, -24.0f, 0.0f,
	-11.91f, -11.91f, 0.0f,
	-13.71f, -1.0f, 0.0f,
	-13.71f, -0.75f, 0.0f,
	-13.71f, -0.5f, 0.0f,
	-13.71f, 0.0f, 0.0f,
	-13.71f, 0.5f, 0.0f,
	-13.71f, 0.75f, 0.0f,
	-13.71f, 1.0f, 0.0f,
	-11.91f, 11.91f, 0.0f,

	0.0f, 11.91f, 11.91f,
	0.0f, 1.0f, 13.71f,
	0.0f, 0.75f, 13.71f,
	0.0f, 0.5f, 13.71f,
	0.0f, 0.0f, 13.71f,
	0.0f, -0.5f, 13.71f,
	0.0f, -0.75f, 13.71f,
	0.0f, -1.0f, 13.71f,
	0.0f, -11.91f, 11.91f,
	0.0f, -11.91f, -11.91f,
	0.0f, -1.0f, -13.71f,
	0.0f, -0.75f, -13.71f,
	0.0f, -0.5f, -13.71f,
	0.0f, 0.0f, -13.71f,
	0.0f, 0.5f, -13.71f,
	0.0f, 0.75f, -13.71f,
	0.0f, 1.0f, -13.71f,
	0.0f, 11.91f, -11.91f,

	8.34f, 11.91f, 8.34f,
	9.6f, 1.0f, 9.6f,
	9.6f, 0.75f, 9.6f,
	9.6f, 0.5f, 9.6f,
	9.6f, 0.0f, 9.6f,
	9.6f, -0.5f, 9.6f,
	9.6f, -0.75f, 9.6f,
	9.6f, -1.0f, 9.6f,
	8.34f, -11.91f, 8.34f,
	-8.34f, -11.91f, -8.34f,
	-9.6f, -1.0f, -9.6f,
	-9.6f, -0.75f, -9.6f,
	-9.6f, -0.5f, -9.6f,
	-9.6f, 0.0f, -9.6f,
	-9.6f, 0.5f, -9.6f,
	-9.6f, 0.75f, -9.6f,
	-9.6f, 1.0f, -9.6f,
	-8.34f, 11.91f, -8.34f,

	-8.34f, 11.91f, 8.34f,
	-9.6f, 1.0f, 9.6f,
	-9.6f, 0.75f, 9.6f,
	-9.6f, 0.5f, 9.6f,
	-9.6f, 0.0f, 9.6f,
	-9.6f, -0.5f, 9.6f,
	-9.6f, -0.75f, 9.6f,
	-9.6f, -1.0f, 9.6f,
	-8.34f, -11.91f, 8.34f,
	8.34f, -11.91f, -8.34f,
	9.6f, -1.0f, -9.6f,
	9.6f, -0.75f, -9.6f,
	9.6f, -0.5f, -9.6f,
	9.6f, 0.0f, -9.6f,
	9.6f, 0.5f, -9.6f,
	9.6f, 0.75f, -9.6f,
	9.6f, 1.0f, -9.6f,
	8.34f, 11.91f, -8.34f,
};

double const CGALInterpolationSimulator::m_InitializationMagForceList[NUM_INITIALIZATION_POINTS] = 
{	
	// In magnet
	14.2f, 14.4f, 14.4f, 14.4f, 14.4f, 14.4f, 14.4f, 14.4f, 14.4f,
	13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f,
	13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f,
	13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f,
	13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f, 13.2f,

	// Inner magnet  half 0.5//
	13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f,
	13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f,
	13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f, 13.8f,


	//Between coil and magnet
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	//Around the loop of the coil
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f,
	//Between the loops of the coil
	/*9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f,
	9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f,
	9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f,
	9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f,
	9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f, 9.0f, 15.0f,
	9.0f, 15.0f, 9.0f, 15.0f,
	//Near coil green
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,*/

	// Up Magnet Yellow
	10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f,
	//Inner green

	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,
	9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f, 9.0f,

	//Middle 1 Inner green

	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,

	//Middle 2 Inner green

	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,

	//Middle 3 Inner green

	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f,

	//Outer green

	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,
	6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f, 6.6f,  

	//Inner blue

	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f,


	// Middle 1 Inner Blue

	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,


	// Middle 2 Inner Blue

	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,


	// Middle 3 Inner Blue

	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,

	// Middle 4 Inner Blue

	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f,
	1.8f, 1.8f, 1.8f, 1.8f,

	//Outer blue
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};

float const CGALInterpolationSimulator::m_InitializationDirVecList[NUM_INITIALIZATION_POINTS] = 
{
	// Inner magnet middle//
	90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f,	90.0f,

	// Inner magnet mid top//
	90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f,	90.0f,

	// Inner magnet mid bot//
	90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f,	90.0f,

	// Inner magnet top//
	90.0f, 85.0f, 85.0f, 85.0f, 85.0f, 85.0f, 85.0f, 85.0f,	85.0f,

	// Inner magnet bot//
	90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f,	90.0f,

	// Inner magnet  half middle//
	80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f,

	// Inner magnet half top//
	80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f,

	// Inner magnet half bot//
	80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f,
	

	// Between coil and magnet mid//
	90.0f, 90.0f, 90.0f, 90.0f,	90.0f, 90.0f, 90.0f, 90.0f,

	// Between coil and magnet bot//
	110.0f,	110.0f,	110.0f,	110.0f,	110.0f,	110.0f,	110.0f,	110.0f,

	// Between coil and magnet top//
	70.0f, 70.0f, 70.0f, 70.0f,	70.0f, 70.0f, 70.0f, 70.0f,

	//////Near the coil///////
	
	330.0f, 60.0f, 0.0f, 330.0f,

	325.7f,	60.0f,	0.0f, 325.7f,

	321.4f,	60.0f, 0.0f, 321.4f,

	317.1f,	60.0f, 0.0f, 317.1f,

	312.8f,	70.0f, 0.0f, 312.8f,

	325.0f,	75.0f, 7.5f, 180.0f,

	304.2f, 70.0f, 0.0f, 304.2f,

	299.9f, 70.0f, 0.0f, 299.9f,

	295.6f, 80.0f, 0.0f, 295.6f,

	291.3f,	80.0f, 0.0f, 291.3f,

	287.0f,	80.0f, 0.0f, 287.0f,

	282.7f,	80.0f, 0.0f, 282.7f,

	270.0f,	90.0f, 0.0f, 180.0f,

	325.0f,	90.0f, 0.0f, 180.0f,

	270.0f,	90.0f, 0.0f, 180.0f,
	
	270.0f,	90.0f, 0.0f, 180.0f,

	265.7f,	90.0f, 0.0f, 180.0f,

	261.4f,	95.0f, 354.0f, 261.4f,

	257.1f,	100.0f, 352.0f,	257.1f,

	252.8f,	100.0f,	350.0f,	252.8f,

	270.0f,	90.0f, 0.0f, 180.0f,
	
	65.1f,	100.0f,	346.0f,	244.2f,

	239.9f,	100.0f,	344.0f,	239.9f,

	235.6f,	110.0f,	342.0f,	235.6f,

	231.3f,	110.0f,	340.0f,	231.3f,

	227.0f,	110.0f,	338.0f,	227.0f,

	222.7f,	110.0f,	336.0f,	170.7f,

	218.4f,	120.0f,	334.0f,	170.4f,

	270.0f,	90.0f, 0.0f, 180.0f,

	270.0f,	120.0f,	0.0f, 180.0f,

	//Between the loops of the coil//
	/*330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	330.0f,
	30.0f,

	0.0f,
	0.0f,

	0.0f,
	0.0f,

	0.0f,
	0.0f,

	0.0f,
	0.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	240.0f,
	150.0f,

	//Near coil green

	340.0f,
	336.0f,
	332.0f,
	328.0f,
	
	324.0f,
	320.0f,
	316.0f,
	312.0f,
	
	308.0f,
	304.0f,
	300.0f,
	296.0f,

	292.0f,
	280.0f,	
	270.0f,
	270.0f,
	
	260.0f,
	258.0f,	
	254.0f,	
	250.0f,
	
	246.0f,	
	242.0f,	
	238.0f,	
	234.0f,
	
	230.0f,	
	226.0f,	
	222.0f,
	218.0f,

	214.0f,
	210.0f,*/

	// Up Magnet Yellow
	60.0f, 
	90.0f, 
	80.0f, 
	90.0f, 
	100.0f,
	110.0f,
	125.0f,
	// Inner green//

270.0f, 
290.0f, 
300.0f, 
320.0f, 
340.0f,
15.0f,
20.0f,
25.0f,
41.0f,
58.0f,
69.0f,
80.0f,
90.0f, 

95.0f, 
100.0f, 
115.0f, 
125.0f, 
135.0f,
150.0f,
160.0f,
180.0f,
220.0f,
225.0f,
250.0f,
270.0f,

 
290.0f, 
315.0f, 
320.0f, 
0.0f,
20.0f,
30.0f,
45.0f,
55.0f,
65.0f,
80.0f,
85.0f,
90.0f, 

100.0f, 
115.0f, 
120.0f, 
130.0f, 
140.0f,
170.0f,
175.0f,
180.0f,
202.5f,
225.0f,
247.5f,


	// Middle 1 Inner green//

270.0f,
302.4f, 
304.0f, 
20.0f, 
335.0f,
355.0f,
0.0f,
20.0f,
52.0f,
2.0f, 
48.0f,
56.0f, 
64.0f, 
72.0f, 
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,

// Middle 2 Inner green//

270.0f,
322.0f, 
335.0f, 
315.0f, 
335.5f,
2.0f,
12.5f,
15.5f,
24.0f,
46.0f,
6.0f, 
43.0f,
51.0f, 
59.0f, 
67.0f, 
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
// Middle 3 Inner green//

270.0f,
300.0f, 
308.0f, 
322.0f, 
348.0f,
358.0f,
7.5f,
7.5f,
12.5f,
23.0f,
40.0f,
0.0f, 
38.0f,
46.0f, 
54.0f, 
62.0f, 
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,

	// Outer green//

270.0f,
332.4f, 
310.0f, 
323.5f, 
344.0f,
354.0f,
2.5f,
9.0f,
8.0f,
12.5f,
17.0f,
34.0f,
0.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,

	// Inner blue//

270.0f,
342.4f, 
275.0f, 
297.5f, 
340.0f,
350.0f,
357.5f,
6.0f,
9.5f,
5.0f,
9.0f,
10.0f,
28.0f,
28.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,


// Middle 1 Inner Blue

270.0f,
275.0f, 
282.0f, 
292.5f, 
300.0f,
315.0f,
325.0f,
0.0f,
332.0f,
334.0f,
354.0f,
2.0f,
6.0f,
25.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,
90.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,
90.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
250.6f,
90.0f,
90.0f,
90.0f,

// Middle 2 Inner Blue

270.0f,
275.0f, 
282.0f, 
289.5f, 
297.0f,
306.0f,
314.0f,
315.0f,
337.0f,
0.0f,
348.0f,
350.0f,
17.0f,
25.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,
90.0f,
90.0f,
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

// Middle 3 Inner Blue

 270.0f,
278.0f, 
285.0f, 
295.5f, 
304.0f,
313.0f,
322.0f,
315.0f,
330.0f,
335.0f,
340.0f,
0.0f,
17.0f,
25.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

// Middle 4 Inner Blue

270.0f,
273.0f, 
280.0f, 
287.5f, 
293.0f,
300.0f,
305.0f,
315.0f,
330.0f,
335.0f,
340.0f,
9.0f,
17.0f,
25.0f, 
33.0f,
41.0f, 
49.0f, 
57.0f, 
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
340.0f,
340.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

55.0f,
270.0f,
280.0f, 
280.0f, 
280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
280.0f,
280.0f,
280.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

280.0f, 
300.0f,
310.0f,
320.0f,
330.0f,
340.0f,
55.0f,
270.0f,
280.0f, 
192.5f, 
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
211.8f, 
231.2f,
250.6f,
250.6f,
250.6f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,
90.0f,

	// Outer blue//
	90.0f,
	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,
	90.0f,
	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,

	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,
	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,


	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,
	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,

	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,
	60.0f,
	358.0f,
	340.0f,
	325.0f,
	270.0f,
	215.0f,
	200.0f,
	175.0f,
	120.0f,
};