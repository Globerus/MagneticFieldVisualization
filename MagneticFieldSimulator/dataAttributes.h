#ifndef DATA_ATTRIBUTES_H
#define DATA_ATTRIBUTES_H

enum ElementType
	{
		DP_NO_TYPE,
		DP_HALF,
		DP_FLOAT,
		DP_INT,
		DP_U_INT,
		DP_BYTE,
		DP_U_BYTE,
		DP_SHORT,
		DP_U_SHORT,
		DP_MAX_ELEMENT_TYPE
	};

	enum ContainerType
	{
		DP_UNKNOWN,
		DP_R32G32B32A32_FLOAT,
		DP_R32G32B32A32_UNSIGNED_INT,
		DP_R32G32B32A32_SIGNED_INT,
		DP_R32G32B32_FLOAT,
		DP_R32G32B32_UNSIGNED_INT,
		DP_R32G32B32_SIGNED_INT,
		DP_R16G16B16A16_FLOAT,
		DP_R16G16B16A16_UNSIGNED_INT,
		DP_R16G16B16A16_UNSIGNED_NORM,
		DP_R16G16B16A16_SIGNED_INT,
		DP_R16G16B16A16_SIGNED_NORM,
		DP_R32G32_FLOAT,
		DP_R32G32_UNSIGNED_INT,
		DP_R32G32_SIGNED_INT,
		DP_R8G8B8A8_UNSIGNED_INT,
		DP_R8G8B8A8_UNSIGNED_NORM,
		DP_R8G8B8A8_SIGNED_INT,
		DP_R8G8B8A8_SIGNED_NORM,
		DP_R16G16_FLOAT,
		DP_R16G16_UNSIGNED_INT,
		DP_R16G16_SIGNED_INT,
		DP_D32_FLOAT,
		DP_R32_FLOAT,
		DP_R32_UNSIGNED_INT,
		DP_R32_SIGNED_INT,
		DP_D24_UNSIGNED_NORM_S8_UNSIGNED_INT,
		DP_R8G8_UNSIGNED_INT,
		DP_R8G8_UNSIGNED_NORM,
		DP_R8G8_SIGNED_INT,
		DP_R8G8_SIGNED_NORM,
		DP_R16_FLOAT,
		DP_D16_UNSIGNED_NORM,
		DP_R16_UNSIGNED_INT,
		DP_R16_UNSIGNED_NORM,
		DP_R16_SIGNED_INT,
		DP_R16_SIGNED_NORM,
		DP_R8_UNSIGNED_INT,
		DP_R8_UNSIGNED_NORM,
		DP_R8_SIGNED_INT,
		DP_R8_SIGNED_NORM,
		DP_MAX_CONTAINER_TYPE,
	};

class DataAttributes
{
public:
	static unsigned int GetNumBytes (ContainerType containerType);
	static unsigned int GetNumElement (ContainerType containerType);
	
	static ElementType GetElementType (ContainerType type);

	static bool IsDepthFormat (ContainerType type);

private:
	static unsigned int m_MapNumBytes[DP_MAX_CONTAINER_TYPE];
	static unsigned int m_MapNumElement[DP_MAX_CONTAINER_TYPE];

	static ElementType m_MapElementType[DP_MAX_CONTAINER_TYPE];
};

#endif