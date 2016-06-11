#include "stdafx.h"
#include "geometryNode.h"

GeometryNode::~GeometryNode ()
{

}

GeometryNode::GeometryNode ()
	:	m_IndexBuffer (nullptr),
		m_VertexBuffer (nullptr),
		m_InstancedBuffer (nullptr),
		m_VisualEffect (nullptr)
{
	m_IsDrawable = true;
}
void GeometryNode::SetVertexBuffer (std::shared_ptr<VertexBuffer> const& vertexBuffer)
{
	m_VertexBuffer = vertexBuffer;
}

void GeometryNode::SetInstancedBuffer (std::shared_ptr<VertexBuffer> const& instancedBuffer)
{
	m_InstancedBuffer = instancedBuffer;
}

void GeometryNode::SetIndexBuffer (std::shared_ptr<IndexBuffer> const& indexBuffer)
{
	m_IndexBuffer = indexBuffer;
}

void GeometryNode::SetVisualEffect (std::shared_ptr<VisualEffect> const& visualEffect)
{
	m_VisualEffect = visualEffect;
}

std::shared_ptr<VertexBuffer> const& GeometryNode::GetVertexBuffer () const
{
	return m_VertexBuffer;
}

std::shared_ptr<VertexBuffer> const& GeometryNode::GetInstancedBuffer () const
{
	return m_InstancedBuffer;
}

std::shared_ptr<IndexBuffer> const& GeometryNode::GetIndexBuffer () const
{
	return m_IndexBuffer;
}

std::shared_ptr<VisualEffect> const& GeometryNode::GetVisualEffect () const
{
	return m_VisualEffect;
}

bool GeometryNode::UpdateModelNormals ()
{
	int type = m_IndexBuffer->GetPrimitiveType ();

	if (type != P_TRIANGLES)
	{
		fprintf (stderr, "The updateModelNormals method in GeometryNode failed, because the primitive type is not triangles.\n");
		return false;
	}

	VertexAttributes vAttrib = m_VertexBuffer->GetVertexAttrib ();
	std::set<ContainerType> setTypes;
	setTypes.insert (DP_R32G32B32_FLOAT);
	setTypes.insert (DP_R32G32_FLOAT);

	char const* positions = m_VertexBuffer->GetAttribData (VA_POSITION, 0, setTypes);
	if (!positions)
	{
		fprintf (stderr, "The updateModelNormals method in GeometryNode failed, because the positions data is empty.\n");
		return false;
	}

	char const* indices = m_IndexBuffer->GetData ();
	if (!indices)
	{
		fprintf (stderr, "The updateModelNormals method in GeometryNode failed, because the indices data is empty.\n");
		return false;
	}

	char * normals = m_VertexBuffer->GetAttribData (VA_NORMAL, 0, setTypes);
	if (!normals)
	{
		fprintf (stderr, "The updateModelNormals method in GeometryNode failed, because the normals data is empty.\n");
		return false;
	}

	int numVertices = m_VertexBuffer->GetNumElements ();
	int strideVertex = m_VertexBuffer->GetElementSize ();
	int strideIndex = m_IndexBuffer->GetElementSize ();

	for (int i = 0; i < numVertices; i++)
	{
		glm::vec3& normal = *(glm::vec3*) (normals + i*strideVertex);
		normal = glm::vec3 (0.0f);
	}

	int numIndices = m_IndexBuffer->GetNumPrimitives ();

	std::vector<unsigned int> nb_seen;
	nb_seen.resize(numIndices);

	for (int i = 0; i < numIndices; i+=3)
	{
		int v[3];
		v[0] = *(int*)(indices + i*strideIndex);
		v[1] = *(int*)(indices + (i+1)*strideIndex);
		v[2] = *(int*)(indices + (i+2)*strideIndex);
				
		glm::vec3 pos0 = *(glm::vec3*) (positions + v[0]*strideVertex);
		glm::vec3 pos1 = *(glm::vec3*) (positions + v[1]*strideVertex);
		glm::vec3 pos2 = *(glm::vec3*) (positions + v[2]*strideVertex);

		glm::vec3 cross = glm::cross(pos1 - pos0, pos2 - pos0);
		
		glm::vec3 normal = glm::normalize(cross);

		for (int j = 0; j < 3; j++) 
		{
			unsigned short cur_v = v[j];
			nb_seen[cur_v]++;
			glm::vec3& nor = *(glm::vec3*) (normals + v[j]*strideVertex);
			if (nb_seen[cur_v] == 1) 
			{
				nor = normal;
			}
			else
			{
				nor.x = nor.x * (1.0f - 1.0f/nb_seen[cur_v]) + normal.x * (1.0f/nb_seen[cur_v]);
				nor.y = nor.y * (1.0f - 1.0f/nb_seen[cur_v]) + normal.y * (1.0f/nb_seen[cur_v]);
				nor.z = nor.z * (1.0f - 1.0f/nb_seen[cur_v]) + normal.z * (1.0f/nb_seen[cur_v]);
				nor = glm::normalize (nor);
			}
		}
	}

	return true;
}
