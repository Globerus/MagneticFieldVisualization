#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include "groupNode.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "visualEffect.h"

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
	
	std::shared_ptr<VertexBuffer> const& GetVertexBuffer () const;
	std::shared_ptr<VertexBuffer> const& GetInstancedBuffer () const;
	std::shared_ptr<IndexBuffer> const& GetIndexBuffer () const;
	std::shared_ptr<VisualEffect> const& GetVisualEffect () const;
	
	bool UpdateModelNormals ();

public:
	int m_GeomType;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexBuffer> m_InstancedBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VisualEffect> m_VisualEffect;
};

#endif