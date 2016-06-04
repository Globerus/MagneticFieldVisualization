#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

//#include "node.h"
#include "groupNode.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "visualEffect.h"
//#include <set>

class GeometryNode : public Node
{
public:
	enum 
	{
		POLYPOINT,
		TRIANGLEMESH,
		POLYLINE
	};

	~GeometryNode ();
	GeometryNode ();

	void SetVertexBuffer (std::shared_ptr<VertexBuffer> const& vertexBuffer);
	void SetInstancedBuffer (std::shared_ptr<VertexBuffer> const& vertexBuffer);
	void SetIndexBuffer (std::shared_ptr<IndexBuffer> const& indexBuffer);
	void SetVisualEffect (std::shared_ptr<VisualEffect> const& visualEffect);
	//void SetViewPort (glm::vec4 viewport);

	std::shared_ptr<VertexBuffer> const& GetVertexBuffer () const;
	std::shared_ptr<VertexBuffer> const& GetInstancedBuffer () const;
	std::shared_ptr<IndexBuffer> const& GetIndexBuffer () const;
	std::shared_ptr<VisualEffect> const& GetVisualEffect () const;
	//glm::vec4 const& GetViewPort () const;

	bool UpdateModelNormals ();
	//void UpdateModelState ();


protected:
	

public:
	int m_GeomType;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexBuffer> m_InstancedBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VisualEffect> m_VisualEffect;
};

#endif