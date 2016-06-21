#ifndef DELAUNAY_TRIANGULATION_H
#define DELAUNAY_TRIANGULATION_H
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include "assert.h"
#include <time.h>
#include "predicates.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "Stack.h"

typedef struct
{
  double m_Point[3];
  
  double m_Value;
  
  double m_VoronoiVolume;
  
} Vertex;

typedef struct 
{
  int m_NumPoints, m_NumPointsAlloc;

  double** m_Points;

  ArrayList* m_Vertices;
  
} VoronoiCell;

typedef struct _Simplex
{
  Vertex * m_SimplexPoints[4];

  struct _Simplex* m_NeighbourSimplices[4];

  ListNode* m_SimplexNode;

} Simplex;

typedef struct
{
  Stack* m_Pointers;
  Stack* m_Old;

} NeighbourUpdate;

typedef struct
{
  LinkedList * m_Simplices;
  
  Simplex* m_AlphaSimplex;
  Vertex   m_AlphaSimplexVertices[4];
  
  Stack* m_RemovedSimplices;
  Stack* m_RemovedVoronoiCells;

  ArrayList* m_Conflicts;
  ArrayList* m_Updates;
  NeighbourUpdate* m_NeighbourUpdates;

} DelaunayTriangulation;


DelaunayTriangulation*	NewDelaunayTriangulation();
void	FreeDelaunayTriangulation(DelaunayTriangulation* dt);
void	RemovePoint(DelaunayTriangulation* dt);
void	GetRange(Vertex* pointSet, int n, Vertex* min, Vertex* max, Vertex* range);
void	InitSuperSimplex(Vertex* pointSet, int n, DelaunayTriangulation* dt);
int		SimplexContainsPoint(Simplex* simplex, Vertex* point);
void	GetFaceVerticies(Simplex* simplex, int i, Vertex** point1, Vertex** point2, Vertex** point3, Vertex** point4 );
int		Vercmp(Vertex* v1, Vertex* v2);
void	AddSimplexToDelaunayTriangulation(DelaunayTriangulation* dt, Simplex* simplex);
void	RemoveSimplexFromDelaunayTriangulation(DelaunayTriangulation* dt, Simplex* simplex);
int		IsDelaunay(Simplex* simplex, Vertex* point);
Simplex**	SwapSimplexNeighbour(Simplex* simplex, Simplex* oldSimplex, Simplex* newS);
Simplex*	FindNeighbour(Simplex* simplex, Vertex* point);
void	BuildDelaunayTriangulation(Vertex* pointSet, int n, DelaunayTriangulation* dt);
int		PointOnSimplex(Vertex* point, Simplex* simplex);
ArrayList*	FindNeighbours(Vertex* point, Simplex* simplex);
Simplex*	NewSimplex(DelaunayTriangulation* dt);
void	AddPoint(Vertex* point, DelaunayTriangulation* dt);
void	CircumCenter(Simplex* simplex, double* out);
VoronoiCell*	GetVoronoiCell(Vertex* point, Simplex* simplex, DelaunayTriangulation* dt);
void	GetRemainingFace(Simplex* simplex, Vertex* point, Vertex** v1,  Vertex** v2, Vertex** v3);
void	SetNeighbours(ArrayList* newTets);
void	VertexAdd(double* a, double* b, double* out);
void	VertexByScalar(double* a, double b, double* out);
void	VertexSub(double* a, double* b, double* out);
void	CrossProduct(double* b, double* c, double* out);
double	SquaredDistance(double* a);
double	ScalarProduct(double* a, double* b);
double	VolumeOfTetrahedron(double* a,double* b, double* c, double* d);
double	VoronoiCellVolume(VoronoiCell* voronoiCell, Vertex* point);
ArrayList*	NaturalNeighbours(Vertex* point, DelaunayTriangulation* dt);
void	FreeVoronoiCell(VoronoiCell* voronoiCell, DelaunayTriangulation* dt);
NeighbourUpdate*	InitNeighbourUpdates();
void	ResetNeighbourUpdates(NeighbourUpdate* neighbourUpdate);
void	UndoNeighbourUpdates(NeighbourUpdate* neighbourUpdate);
void	PushNeighbourUpdate(NeighbourUpdate* neighbourUpdate, Simplex** simplex, Simplex * oldSimplex);
void	FreeNeighbourUpdates(NeighbourUpdate* neighbourUpdate);
Simplex*	FindAnyNeighbour(Vertex* point, ArrayList* tets);
void	RandomPerturbation(Vertex* point, int attempt);
#endif

