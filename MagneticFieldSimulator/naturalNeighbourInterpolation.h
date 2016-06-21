#ifndef NATURAL_NEIGHBOUR_INTERPOLATION_H
#define NATURAL_NEIGHBOUR_INTERPOLATION_H

#include "delaunayTriangulation.h"
#include <vector>
#include "include.h"

Vertex* ReformatPoints(std::vector<glm::vec3> points, std::vector<float> values, int n);
void    LastNaturalNeighbours(Vertex* v, DelaunayTriangulation* dt, ArrayList *neighbours, ArrayList *neighbourSimplicies);
double	NaturalNeighbourInterpolation (glm::vec3 point, DelaunayTriangulation* dt);
double	CalculateValue(ArrayList* neighbours, std::vector<double> neighbourWeights);
#endif

