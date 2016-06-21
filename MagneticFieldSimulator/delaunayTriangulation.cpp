#include "stdafx.h"
#include "delaunayTriangulation.h"

#define PERTURBATION_VALUE  0.0001

Simplex* NewSimplex(DelaunayTriangulation* dt)
{
  Simplex* simplex = (Simplex*)Pop(dt->m_RemovedSimplices);
 
  if (simplex==dt->m_AlphaSimplex) simplex=0;
 
  if (!simplex)
  {
    simplex = (Simplex*)malloc(sizeof(Simplex));
  }

  simplex->m_NeighbourSimplices[0] = 0;
  simplex->m_NeighbourSimplices[1] = 0;
  simplex->m_NeighbourSimplices[2] = 0;
  simplex->m_NeighbourSimplices[3] = 0;
  
  return simplex;
}

void BuildDelaunayTriangulation(Vertex* pointSet, int numPoints, DelaunayTriangulation* dt)
{
  srand ( time(nullptr) );

  InitSuperSimplex(pointSet, numPoints, dt);
  AddSimplexToDelaunayTriangulation(dt, dt->m_AlphaSimplex);
  
  for (int i = 0; i < numPoints; i++)
  {
    AddPoint(&pointSet[i], dt);
    
    for (int j = 0; j < ArrayListSize(dt->m_Conflicts); j++)
      Push(dt->m_RemovedSimplices, GetFromArrayList(dt->m_Conflicts, j));    
    
    EmptyArrayList(dt->m_Conflicts);
    EmptyArrayList(dt->m_Updates);
    
    ResetNeighbourUpdates(dt->m_NeighbourUpdates);
  }
}

Simplex** SwapSimplexNeighbour(Simplex* simplex, Simplex* oldSimplex, Simplex* newS)
{
  if (!simplex) return nullptr;
 
  int i,found=0;
  
  for (i = 0;i < 4; i++)
  {
    if (simplex->m_NeighbourSimplices[i] == oldSimplex) 
    {
      found=1;
      break;    
    }
  }

  simplex->m_NeighbourSimplices[i] = newS;

  assert(found);
  return &simplex->m_NeighbourSimplices[i];
}

int vercmp(Vertex* v1, Vertex* v2)
{
  int i;
  for (i = 0; i < 3; i++)
    if ( v1->m_Point[i] != v2->m_Point[i] )
		return 0; 
  return 1;
}

Simplex* FindContainingSimplex(DelaunayTriangulation* dt, Vertex* point)
{
  ListNode* iter = TopOfLinkedList(dt->m_Simplices);
  Simplex* simplex = (Simplex*)NextElement(dt->m_Simplices,&iter); 
  Vertex* v1,* v2,* v3,* v4;
  
  int i;
  for (i = 0; i < 4; i++)
  {
    GetFaceVerticies(simplex, i, &v1, &v2, &v3, &v4);
    
    if ((orient3dfast(v1->m_Point, v2->m_Point, v3->m_Point, point->m_Point) < 0) && simplex->m_NeighbourSimplices[i])
    {
      simplex = simplex->m_NeighbourSimplices[i];
      i = -1;
    }
  }
    
  return simplex;
}

void GetFaceVerticies(Simplex* simplex, int i, Vertex** point1, Vertex** point2, 
                                         Vertex** point3, Vertex** point4  )
{
  switch (i)
  {
    case 0:
     *point1 = simplex->m_SimplexPoints[0];
     *point2 = simplex->m_SimplexPoints[1];
     *point3 = simplex->m_SimplexPoints[2];      
     *point4 = simplex->m_SimplexPoints[3];
      break;
    case 1:
     *point1 = simplex->m_SimplexPoints[3];
     *point2 = simplex->m_SimplexPoints[1];
     *point3 = simplex->m_SimplexPoints[0];      
     *point4 = simplex->m_SimplexPoints[2];   
      break;
    case 2:
     *point1 = simplex->m_SimplexPoints[0];
     *point2 = simplex->m_SimplexPoints[2];
     *point3 = simplex->m_SimplexPoints[3];      
     *point4 = simplex->m_SimplexPoints[1];  
      break;
    case 3:  
     *point1 = simplex->m_SimplexPoints[3];
     *point2 = simplex->m_SimplexPoints[2];
     *point3 = simplex->m_SimplexPoints[1];      
     *point4 = simplex->m_SimplexPoints[0];  
      break;
  } 
}

int SimplexContainsPoint(Simplex* simplex, Vertex* point)
{
  int i;
  
  Vertex* p1,* p2,* p3,* p4;  
  
  for (i = 0; i < 4; i++)
  {
    GetFaceVerticies(simplex, i, &p1, &p2, &p3, &p4);
    if (orient3dfast(p1->m_Point, p2->m_Point, p3->m_Point, point->m_Point) < 0)
		return 0;
  }
  
  return 1;
}

void RandomPerturbation(Vertex* point, int attempt)
{
  int i;
  for (i = 0;i < 3; i++)
  {
    double rand01 = (double)rand()/((double)RAND_MAX + 1);
    double p = (rand01-0.5)*  PERTURBATION_VALUE*  (attempt+1);
    point->m_Point[i] +=  p;
  }
}

int IsDelaunay(Simplex* simplex, Vertex* point)
{ 
  double orientation = orient3dfast(simplex->m_SimplexPoints[0]->m_Point, 
                                    simplex->m_SimplexPoints[1]->m_Point, 
                                    simplex->m_SimplexPoints[2]->m_Point, 
                                    simplex->m_SimplexPoints[3]->m_Point);


  if (orientation <= 0)
  {
    printf("orientation error: %p, %lf\n",simplex,orientation);
  }

  double inSph = inspherefast(  simplex->m_SimplexPoints[0]->m_Point,
                                simplex->m_SimplexPoints[1]->m_Point, 
                                simplex->m_SimplexPoints[2]->m_Point, 
								simplex->m_SimplexPoints[3]->m_Point, point->m_Point); 

            
  if (inSph == 0) 
	  return -1;
                
  return inSph < 0;

}

void UpdateConflictingSimplicies(Vertex* point, DelaunayTriangulation* dt)
{
  int i;
  
  Simplex* simplex = FindContainingSimplex(dt, point);
  Simplex* current;
  
  Stack* toCheck = NewStack();
  Push(toCheck, simplex);

  while (!IsEmpty(toCheck))
  {
    current = (Simplex*)Pop(toCheck);
    
    int isDel = IsDelaunay(current,point); 
    
    if (isDel == -1) 
    {     
      int i = 0;
      while( isDel == -1 )
      {
        RandomPerturbation(point,i);
        isDel = IsDelaunay(current,point);
        
		i++;
      }   
      
      FreeStack(toCheck,nullptr);
      EmptyArrayList(dt->m_Conflicts);
      UpdateConflictingSimplicies(point,dt);
      return;
    }
    
    if ((!isDel) && (!ArrayListContains(dt->m_Conflicts, current)))
    {
      AddToArrayList(dt->m_Conflicts, current);
      for (i = 0; i < 4; i++)
        if (current->m_NeighbourSimplices[i])
          Push(toCheck, current->m_NeighbourSimplices[i]);
    }
  }
  FreeStack(toCheck,nullptr);
}

void AddPoint(Vertex* point, DelaunayTriangulation* dt)
{
  UpdateConflictingSimplicies(point,dt);
  
  int i,j;
  for (j = 0; j < ArrayListSize(dt->m_Conflicts); j++)
  {
    Simplex* simplex = (Simplex*)GetFromArrayList(dt->m_Conflicts,j);
     
    for (i = 0; i < 4; i++)
    {
      Vertex* v1,* v2,* v3,* v4;
      GetFaceVerticies(simplex, i, &v1, &v2, &v3, &v4);
      
      if (! ArrayListContains(dt->m_Conflicts, simplex->m_NeighbourSimplices[i]))
      { 
        Simplex* newS = NewSimplex(dt);
        newS->m_SimplexPoints[0] = v1;
        newS->m_SimplexPoints[1] = v2;
        newS->m_SimplexPoints[2] = v3;
        newS->m_SimplexPoints[3] =  point;
        
        int attempt = 0;
       
        double o = orient3dfast(v1->m_Point, v2->m_Point, v3->m_Point, point->m_Point);
        if (o <= 0)
        {
          while (o <= 0)
          {
            RandomPerturbation(point, attempt);
            o = orient3dfast(v1->m_Point, v2->m_Point, v3->m_Point, point->m_Point);
            attempt ++;
          }
          
		  UndoNeighbourUpdates(dt->m_NeighbourUpdates);
          int k;
          for (k = 0; k < ArrayListSize(dt->m_Updates); k++)
          {
            RemoveSimplexFromDelaunayTriangulation(dt, (Simplex*)GetFromArrayList(dt->m_Updates,k));
            Push(dt->m_RemovedSimplices, GetFromArrayList(dt->m_Updates, k));    
          }
          EmptyArrayList(dt->m_Updates);
          EmptyArrayList(dt->m_Conflicts);
          
		  AddPoint(point,dt);
          return;
        }
        
		newS->m_NeighbourSimplices[0] = simplex->m_NeighbourSimplices[i];
         
        Simplex** update = SwapSimplexNeighbour(simplex->m_NeighbourSimplices[i], simplex, newS);
        PushNeighbourUpdate(dt->m_NeighbourUpdates, update, simplex);

        AddToArrayList(dt->m_Updates, newS);
        AddSimplexToDelaunayTriangulation(dt, newS);        
      }      
    }    
  }

  SetNeighbours(dt->m_Updates);  
  
  for (i = 0; i < ArrayListSize(dt->m_Conflicts); i++)
  {
    Simplex* simplex = (Simplex*)GetFromArrayList(dt->m_Conflicts, i);
    RemoveSimplexFromDelaunayTriangulation(dt,simplex);
  }
}

void SetNeighbours(ArrayList* newTets)
{
  Simplex* simplex,* s2;
  Vertex* v1,* v2,* v3,* t1,* t2,* t3,* tmp;
  
  int j;
  
  for (j = 0; j < ArrayListSize(newTets); j++)
  {
    simplex = (Simplex*)GetFromArrayList(newTets,j);
 
    v1 = simplex->m_SimplexPoints[0];
    v2 = simplex->m_SimplexPoints[1];
    v3 = simplex->m_SimplexPoints[2];

    int k;
    for (k = 0; k < ArrayListSize(newTets); k++)
    {
      s2 = (Simplex*)GetFromArrayList(newTets,k); 
      if (simplex == s2) continue;
      int i;
      
	  for (i = 1; i < 4; i++)
      {
        GetFaceVerticies(s2, i, &t1, &t2, &t3, &tmp);
        
        if ((v1 == t1 || v1 == t2 || v1 == t3) && (v2 == t1 || v2 == t2 || v2 == t3))
			simplex->m_NeighbourSimplices[1] = s2;        
        else if ((v2 == t1 || v2 == t2 || v2 == t3) && (v3 == t1 || v3 == t2 || v3 == t3))
				 simplex->m_NeighbourSimplices[3] = s2;
        else if ((v3 == t1 || v3 == t2 || v3 == t3) && (v1 == t1 || v1 == t2 || v1 == t3))
				 simplex->m_NeighbourSimplices[2] = s2;           
      }
    }
  }
}

int PointOnSimplex(Vertex* point, Simplex* simplex)
{
  if (!simplex) return 0;
  
  if (point == simplex->m_SimplexPoints[0] || point == simplex->m_SimplexPoints[1] || point == simplex->m_SimplexPoints[2] || point == simplex->m_SimplexPoints[3])   
    return 1;

  return 0;
}

Simplex* findNeighbour(Simplex* simplex, Vertex* point)
{
  Vertex* t1,* t2,* t3,* t4;
  int i,found=0;
  for (i = 0; i < 4; i++)
  {
    GetFaceVerticies(simplex, i, &t1, &t2, &t3, &t4);
    if (t4 == point) 
    {
      found = 1;
      break;
    }
  }
  
  assert(found);
  
  return simplex->m_NeighbourSimplices[i];
}

Simplex* FindAnyNeighbour(Vertex* point, ArrayList* simplices)
{  
  for (int i = 0; i < ArrayListSize(simplices); i++)
  {
    Simplex* simplex = (Simplex*)GetFromArrayList(simplices,i);
    if (PointOnSimplex(point, simplex)) 
		return simplex; 
  }
  return nullptr;
}

ArrayList* FindNeighbours(Vertex* point, Simplex* simplex)
{
  ArrayList* l   = NewArrayList(); 
  Stack* toCheck = NewStack();

  Simplex* current;
  Push(toCheck, simplex);

  while (!IsEmpty(toCheck))
  {
    current = (Simplex*)Pop(toCheck);
    
    if ( PointOnSimplex(point, current) && (! ArrayListContains(l, current)) )
    {
      AddToArrayList(l, current);
      for (int i = 0; i < 4; i++)
        if (current->m_NeighbourSimplices[i])
          Push(toCheck, current->m_NeighbourSimplices[i]);
    }   
  }
  FreeStack(toCheck,nullptr);

  return l;   
}

void GetRemainingFace(Simplex* simplex, Vertex* point, Vertex** v1,  Vertex** v2, Vertex** v3)
{
  int i,found=0;
  Vertex* tmp;
  for (i = 0; i < 4; i++)
  {
    GetFaceVerticies(simplex, i, v1, v2, v3, &tmp);
    if (tmp == point) 
    {
      found = 1;
      break; 
    }
  }
 
  assert(found);
}

int IsNeighbour(Simplex* simplex, Simplex* simplex2)
{
  int i;
  for (i = 0; i < 4; i++)
    if (simplex->m_NeighbourSimplices[i] == simplex2) 
		return 1;
    
  return 0;
}

VoronoiCell* NewVoronoiCell(DelaunayTriangulation* dt, int n)
{

  VoronoiCell* voronoiCell ;
  voronoiCell = (VoronoiCell*)Pop(dt->m_RemovedVoronoiCells);

  if (!voronoiCell)
  {
    voronoiCell = (VoronoiCell*)malloc(sizeof(VoronoiCell));
    voronoiCell->m_Vertices = NewArrayList();
    voronoiCell->m_NumPointsAlloc = 0;
    voronoiCell->m_Points = 0;
  } 
  else 
  {
    EmptyArrayList(voronoiCell->m_Vertices);
  }

  if (n > voronoiCell->m_NumPointsAlloc)
  {
    voronoiCell->m_Points = (double**)realloc(voronoiCell->m_Points, sizeof(double)*n);
   
    for (int i = voronoiCell->m_NumPointsAlloc; i < n; i++)
    {
      voronoiCell->m_Points[i] = (double*)malloc(sizeof(double)*3);
    }
    voronoiCell->m_NumPointsAlloc = n;
  }
  voronoiCell->m_NumPoints = n;
  return voronoiCell;
}

void AddVertexToVoronoiCell(VoronoiCell* voronoiCell, double* point)
{
  AddToArrayList(voronoiCell->m_Vertices, point); 
}

void StartNewVoronoiFace(VoronoiCell* voronoiCell)
{
  AddToArrayList(voronoiCell->m_Vertices, nullptr);
}

void RemovePoint(DelaunayTriangulation* dt)
{
  Simplex * simplex;  

  for (int i = 0; i <  ArrayListSize(dt->m_Conflicts); i++)
  {
    simplex = (Simplex*)GetFromArrayList(dt->m_Conflicts,i);
    AddSimplexToDelaunayTriangulation(dt,simplex);
  }
   
  UndoNeighbourUpdates(dt->m_NeighbourUpdates);
  
  for (int i = 0; i < ArrayListSize(dt->m_Updates); i++)
  {
    simplex = (Simplex*)GetFromArrayList(dt->m_Updates, i);
    RemoveSimplexFromDelaunayTriangulation(dt,simplex);
  }
}

double VoronoiCellVolume(VoronoiCell* voronoiCell, Vertex* point)
{
  int i,j;
  double volume = 0;
  
  for (i = 0; i < ArrayListSize(voronoiCell->m_Vertices); i++)
  {
    double* thisV;
    double* firstV;
    double* lastV = nullptr;
    
    double center[3] = {0,0,0};
    
    for (j = i; j < ArrayListSize(voronoiCell->m_Vertices); j++)
    {     
      thisV = (double*)GetFromArrayList(voronoiCell->m_Vertices, j);
           
      if (!thisV) break;
      VertexAdd(thisV, center, center);          
    }

    VertexByScalar(center, 1/(double)(j-i), center);
       
    firstV = (double*)GetFromArrayList(voronoiCell->m_Vertices, i);
    lastV  = nullptr;
    
    for (j = i; j < ArrayListSize(voronoiCell->m_Vertices); j++)
    {
      thisV = (double*)GetFromArrayList(voronoiCell->m_Vertices,j);
      
      if (thisV == nullptr)
      {
        i = j;
        break;
      }
      
	  if (lastV)
        volume += VolumeOfTetrahedron(thisV, lastV, point->m_Point, center);   
      else 
        firstV = thisV;
      lastV = thisV;
    }
    volume += VolumeOfTetrahedron(lastV, firstV, point->m_Point, center);      
  }

  assert(volume>0);
  
  return volume;

}

VoronoiCell* GetVoronoiCell(Vertex* point, Simplex* simplex, DelaunayTriangulation* dt)
{
  Simplex* newSimplex;
  
  ArrayList* neighbours = FindNeighbours(point, simplex);
  int n = ArrayListSize(neighbours);
  
  if (n==0)
  {
    if (!SimplexContainsPoint(dt->m_AlphaSimplex, point))
      fprintf(stderr,"Error: point outside of delaunay triangulation. - "
                     "try extending the super-Simplex and re-starting.\n");
    else
     fprintf(stderr, "Error: No neighbours found for point! - DelaunayTriangulation appears "
                     "to be degenerate.\n");
	return nullptr;
  }
  
  VoronoiCell* voronoiCell = NewVoronoiCell(dt,n);

  Simplex** simps = new Simplex* [n];
  Vertex** edges = new Vertex* [3*n];
  int* done = new int [3*n];

  int i, j = 0;

  for (i = 0; i < ArrayListSize(neighbours); i++)
  {
    newSimplex = (Simplex*)GetFromArrayList(neighbours, i);
    Vertex* v1,* v2,* v3;
    GetRemainingFace(newSimplex, point, &v1, &v2, &v3);
    
    simps[i]        = newSimplex;
    edges[3*i]      = v1;   
    edges[3*i+1]    = v2;
    edges[3*i+2]    = v3;
    
    done[3*i]       = 0;
    done[3*i+1]     = 0;
    done[3*i+2]     = 0;
 
    CircumCenter(newSimplex, voronoiCell->m_Points[i]);
  }

  for (i = 0; i < 3*n; i++)
  {   
    if (done[i]) continue;
    
    int first   = i;
    int current = i;
    int lastConsidered = -1;

    int match;
    do {
      match=0;
      for (j = 0; j < 3*n; j++)
      {
        if (done[j]) 
			continue;

        if ((edges[i] == edges[j]) && j != lastConsidered && IsNeighbour(simps[current/3], simps[j/3]))
        {
          done[j] = 1;  
          match   = 1;      
          
          AddVertexToVoronoiCell(voronoiCell, voronoiCell->m_Points[j/3]);
          lastConsidered = current;
          current = j;
          break;
        }      
      }  
    } while (match && (current != first));
    
    StartNewVoronoiFace(voronoiCell);
  }
   
  FreeArrayList(neighbours, nullptr);

  return voronoiCell;
}

void FreeVoronoiCell(VoronoiCell* voronoiCell, DelaunayTriangulation* dt)
{
  Push(dt->m_RemovedVoronoiCells, voronoiCell);
}

void AddSimplexToDelaunayTriangulation(DelaunayTriangulation* dt, Simplex* simplex)
{
  simplex->m_SimplexNode = AddToLinkedList(dt->m_Simplices, simplex);  
}

void RemoveSimplexFromDelaunayTriangulation(DelaunayTriangulation* dt, Simplex* simplex)
{
  RemoveFromLinkedList(dt->m_Simplices, simplex->m_SimplexNode);
}

void InitSuperSimplex(Vertex* pointSet, int n, DelaunayTriangulation* dt)
{
  int i;
  dt->m_AlphaSimplex = NewSimplex(dt);
  
  Vertex min,max,range;
  GetRange(pointSet, n, &min, &max, &range);
  
  dt->m_AlphaSimplexVertices[0].m_Point[0] =  min.m_Point[0] + range.m_Point[0]/2;
  dt->m_AlphaSimplexVertices[0].m_Point[1] =  max.m_Point[1] + 3*range.m_Point[1]; 
  dt->m_AlphaSimplexVertices[0].m_Point[2] =  min.m_Point[2] - range.m_Point[2];

  dt->m_AlphaSimplexVertices[1].m_Point[0] =  max.m_Point[0] + 2*range.m_Point[0];
  dt->m_AlphaSimplexVertices[1].m_Point[1] =  min.m_Point[1] - 2*range.m_Point[1];
  dt->m_AlphaSimplexVertices[1].m_Point[2] =  min.m_Point[2] - range.m_Point[2];
  
  dt->m_AlphaSimplexVertices[2].m_Point[0] =  min.m_Point[0] - 2*range.m_Point[0];
  dt->m_AlphaSimplexVertices[2].m_Point[1] =  min.m_Point[1] - 2*range.m_Point[1];
  dt->m_AlphaSimplexVertices[2].m_Point[2] =  min.m_Point[2] - range.m_Point[2];

  dt->m_AlphaSimplexVertices[3].m_Point[0] = min.m_Point[0] + range.m_Point[0]/2;
  dt->m_AlphaSimplexVertices[3].m_Point[1] = min.m_Point[1] + range.m_Point[1]/2;
  dt->m_AlphaSimplexVertices[3].m_Point[2] = max.m_Point[2] + 2*range.m_Point[2];
  
  for (i = 0;i < 4; i++)
  {
    dt->m_AlphaSimplex->m_SimplexPoints[i] = &dt->m_AlphaSimplexVertices[i];
    dt->m_AlphaSimplex->m_NeighbourSimplices[i] = nullptr;
  }
}

void PushNeighbourUpdate(NeighbourUpdate* neighbourUpdate, Simplex** simplex, Simplex* oldSimplex)
{
  Push(neighbourUpdate->m_Pointers, simplex);
  Push(neighbourUpdate->m_Old,  oldSimplex);
}

void FreeNeighbourUpdates(NeighbourUpdate* neighbourUpdate)
{
  FreeStack(neighbourUpdate->m_Pointers, free);
  FreeStack(neighbourUpdate->m_Old,  free);
  free(neighbourUpdate);
}

void UndoNeighbourUpdates(NeighbourUpdate* neighbourUpdate)
{
  Simplex** thisPtr;
  Simplex* thisSimplex;
  
  while (!IsEmpty(neighbourUpdate->m_Pointers))
  {
    thisPtr     = (Simplex**)Pop(neighbourUpdate->m_Pointers);
    thisSimplex = (Simplex*)Pop(neighbourUpdate->m_Old);  
    
    if (thisPtr)
     *thisPtr = thisSimplex;
  }
}

void ResetNeighbourUpdates(NeighbourUpdate* neighbourUpdate)
{
  EmptyStack(neighbourUpdate->m_Pointers);
  EmptyStack(neighbourUpdate->m_Old);
}

NeighbourUpdate* InitNeighbourUpdates()
{
  NeighbourUpdate* neighbourUpdate = (NeighbourUpdate*)malloc(sizeof(NeighbourUpdate));
  neighbourUpdate->m_Pointers = NewStack();
  neighbourUpdate->m_Old  = NewStack();
  return neighbourUpdate;
}

DelaunayTriangulation* NewDelaunayTriangulation()
{
  DelaunayTriangulation* dt             = (DelaunayTriangulation*)malloc(sizeof(DelaunayTriangulation));
  dt->m_AlphaSimplex            = nullptr;
  dt->m_Simplices             = NewLinkedList();
  dt->m_RemovedSimplices   = NewStack();
  dt->m_RemovedVoronoiCells = NewStack();
  dt->m_Conflicts        = NewArrayList();
  dt->m_Updates          = NewArrayList();
  dt->m_NeighbourUpdates = InitNeighbourUpdates();

  return dt;
}

void FreeDelaunayTriangulation(DelaunayTriangulation* dt)
{
  free(dt->m_AlphaSimplex);
  FreeStack(dt->m_RemovedSimplices, free);
  
  while(!IsEmpty(dt->m_RemovedVoronoiCells))
  {
    VoronoiCell* voronoiCell = (VoronoiCell*)Pop(dt->m_RemovedVoronoiCells);
    int i;
    for (i = 0;i < voronoiCell->m_NumPointsAlloc; i++)
      free(voronoiCell->m_Points[i]);
    free(voronoiCell->m_Points);
    FreeArrayList(voronoiCell->m_Vertices, nullptr);
    free(voronoiCell);
  }
  
  FreeStack(dt->m_RemovedVoronoiCells, nullptr);
  FreeLinkedList(dt->m_Simplices, free);
  FreeArrayList(dt->m_Conflicts, free);
  FreeArrayList(dt->m_Updates, nullptr);
  FreeNeighbourUpdates(dt->m_NeighbourUpdates);
  free(dt); 
}

double VolumeOfTetrahedron(double* a, double* b, double* c, double* d)
{
  double a_d[3], b_d[3], c_d[3], cross[3];
  
  VertexSub(a,d, a_d);
  VertexSub(b,d, b_d);
  VertexSub(c,d, c_d);
  
  CrossProduct(b_d, c_d, cross);  
  double point = ScalarProduct(a_d, cross)/(double)6;
   
  return (point >= 0) ? point : -point;
}

double SquaredDistance(double* a)
{
  return ScalarProduct(a,a);
}

void CrossProduct(double* b, double* c, double* out)
{
  out[0] = b[1] *  c[2] - b[2] *  c[1];
  out[1] = b[2] *  c[0] - b[0] *  c[2];
  out[2] = b[0] *  c[1] - b[1] *  c[0];  
}

double ScalarProduct(double* a, double* b)
{
  return a[0]*  b[0] + a[1]*  b[1] + a[2]*  b[2];
}

void VertexSub(double* a, double* b, double* out)
{
  out[0] = a[0] - b[0];
  out[1] = a[1] - b[1];
  out[2] = a[2] - b[2];
}

void VertexAdd(double* a, double* b, double* out)
{
  out[0] = a[0] + b[0];
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
}

void VertexByScalar(double* a, double b, double* out)
{
  out[0] = a[0] *  b;
  out[1] = a[1] *  b;
  out[2] = a[2] *  b;
}

void CircumCenter(Simplex* simplex, double* out)
{
  Vertex* a,* b,* c,* d;
  GetFaceVerticies(simplex, 0, &a, &b, &c, &d);
 
  double b_a[3]   , c_a[3]   , d_a[3], 
         cross1[3], cross2[3], cross3[3], 
         mult1[3] , mult2[3] , mult3[3], 
         sum[3];
  double denominator;
  
  VertexSub(b->m_Point, a->m_Point, b_a);
  VertexSub(c->m_Point, a->m_Point, c_a);
  VertexSub(d->m_Point, a->m_Point, d_a);

  CrossProduct(b_a, c_a, cross1);
  
  CrossProduct(d_a, b_a, cross2);
  
  CrossProduct(c_a, d_a, cross3);

  VertexByScalar(cross1, SquaredDistance(d_a), mult1);
  VertexByScalar(cross2, SquaredDistance(c_a), mult2);
  VertexByScalar(cross3, SquaredDistance(b_a), mult3);
  
  VertexAdd(mult1, mult2, sum);
  VertexAdd(mult3, sum  , sum);

  denominator = 2*ScalarProduct(b_a, cross3);
  
  VertexByScalar(sum, 1/(double)(denominator), out);
  
  VertexAdd(out, a->m_Point, out);
}

void GetRange(Vertex* pointSet, int n, Vertex* min, Vertex* max, Vertex* range)
{
  int i;
  
 *min = pointSet[0];
 *max = pointSet[0];
  
  for (i = 0; i < n; i++)
  {
    if (0)
    {
      pointSet[i].m_Point[0] +=  ((double)rand() / ((double)RAND_MAX + 1) -0.5);
      pointSet[i].m_Point[1] +=  ((double)rand() / ((double)RAND_MAX + 1) -0.5);
      pointSet[i].m_Point[2] +=  ((double)rand() / ((double)RAND_MAX + 1) -0.5);
    }
    
    max->m_Point[0] = std::max(max->m_Point[0], pointSet[i].m_Point[0]);
    max->m_Point[1] = std::max(max->m_Point[1], pointSet[i].m_Point[1]);
    max->m_Point[2] = std::max(max->m_Point[2], pointSet[i].m_Point[2]);
    
    min->m_Point[0] = std::min(min->m_Point[0], pointSet[i].m_Point[0]);
    min->m_Point[1] = std::min(min->m_Point[1], pointSet[i].m_Point[1]);
    min->m_Point[2] = std::min(min->m_Point[2], pointSet[i].m_Point[2]);   
  }
  
  for (i = 0;i < 3; i++)
    range->m_Point[i] = max->m_Point[i] - min->m_Point[i];
}

