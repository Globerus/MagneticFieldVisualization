#include "stdafx.h"
#include "naturalNeighbourInterpolation.h"

Vertex* ReformatPoints(std::vector<glm::vec3> points, std::vector<float> values, int n)
{
  Vertex* ps = new Vertex [n];

  for (int i = 0; i < n; i++)
  {
    ps[i].m_Point[0] = points.at(i).x;
    ps[i].m_Point[1] = points.at(i).y;
    ps[i].m_Point[2] = points.at(i).z;
    
	ps[i].m_Value = values.at (i);
    ps[i].m_VoronoiVolume = -1;   
  }
  
  return ps;
}

void LastNaturalNeighbours(Vertex *v, DelaunayTriangulation* dt, ArrayList *neighbours, ArrayList *neighbourSimplicies)
{
	for (int i = 0; i < ArrayListSize(dt->m_Updates); i++)
	{
		Simplex* simplex = (Simplex*)GetFromArrayList(dt->m_Updates,i); 
		for (int j = 0; j < 4; j++)
		{     
			if (simplex->m_SimplexPoints[j] != v && (! ArrayListContains(neighbours, simplex->m_SimplexPoints[j])) )
			{
				if ((! PointOnSimplex(simplex->m_SimplexPoints[j], dt->m_AlphaSimplex)))
				{
					AddToArrayList(neighbours, simplex->m_SimplexPoints[j]);      
					AddToArrayList(neighbourSimplicies, simplex);
				}
			}      
		}
	}
}

double NaturalNeighbourInterpolation (glm::vec3 point, DelaunayTriangulation* dt)
{
	Vertex p;
	p.m_Point[0] =  point.x;
	p.m_Point[1] =  point.y;
	p.m_Point[2] =  point.z;
	p.m_VoronoiVolume = -1;

	ArrayList* neighbours;
	ArrayList* neighbourSimplices;
  
	AddPoint(&p, dt);    

	neighbours = NewArrayList();  
	neighbourSimplices = NewArrayList();  
	LastNaturalNeighbours(&p, dt, neighbours, neighbourSimplices);

	double pointVolume;

	std::vector<double> neighbourVolumes;
	std::vector<double> neighbourWeights;
	neighbourVolumes.resize (ArrayListSize(neighbours));
	neighbourWeights.resize (ArrayListSize(neighbours));

	for (int i = 0; i < ArrayListSize(neighbours); i++)
	{
		Vertex* thisVertex  = static_cast<Vertex*> (GetFromArrayList(neighbours, i));
		Simplex* thisSimplex = static_cast<Simplex*> (GetFromArrayList(neighbourSimplices, i));  
		VoronoiCell* voronoiCell = GetVoronoiCell(thisVertex, thisSimplex, dt);    
		neighbourVolumes[i]  = VoronoiCellVolume(voronoiCell, thisVertex);  
		FreeVoronoiCell(voronoiCell, dt); 
	}

	Simplex* simplex = static_cast<Simplex*> (GetFromArrayList(neighbourSimplices, 0));
	VoronoiCell* pointCell = GetVoronoiCell(&p, simplex, dt);
	pointVolume = VoronoiCellVolume(pointCell, &p);
	FreeVoronoiCell(pointCell, dt);
         
	RemovePoint(dt);

	for (int i = 0; i < ArrayListSize(neighbours); i++)
	{
		Vertex* neighbourVertex   = static_cast<Vertex*> (GetFromArrayList(neighbours, i));  
  
		if (neighbourVertex->m_VoronoiVolume < 0)
		{
			Simplex* s = FindAnyNeighbour(neighbourVertex, dt->m_Conflicts);
			VoronoiCell* voronoiCell      = GetVoronoiCell(neighbourVertex, s, dt);
			neighbourVertex->m_VoronoiVolume = VoronoiCellVolume(voronoiCell, neighbourVertex);
			FreeVoronoiCell(voronoiCell, dt);
		}
		double neighbourVol = neighbourVertex->m_VoronoiVolume-neighbourVolumes[i];
		
		assert (neighbourVolumes[i]>= -0.001);
		neighbourWeights[i] = neighbourVol/pointVolume;
	}

	double result = CalculateValue (neighbours, neighbourWeights);

	for (int i = 0; i <ArrayListSize(dt->m_Updates); i++)
	  Push(dt->m_RemovedSimplices, GetFromArrayList(dt->m_Updates, i));

	EmptyArrayList(dt->m_Conflicts);
	EmptyArrayList(dt->m_Updates);
  
	FreeArrayList(neighbours, nullptr);
	FreeArrayList(neighbourSimplices, nullptr);

	return result;
}

double CalculateValue(ArrayList* neighbours, std::vector<double> neighbourWeights)
{
	double sum = 0.0;
	double value = 0.0;

	for (int i = 0; i < ArrayListSize(neighbours); i++)
	{
		Vertex* neighbourPoint = static_cast<Vertex*> (GetFromArrayList(neighbours, i));
		double weight = neighbourWeights[i];
		sum   += weight;
		value += weight * neighbourPoint->m_Value;            
	}
  
	value = value * 1.0 / sum;
  
	if (sum <= 0 || sum > 1.1)
	{
		fprintf(stderr, "Error: sum value: %lf, expected range (0,1].\n",sum);
	}

	return value;
}