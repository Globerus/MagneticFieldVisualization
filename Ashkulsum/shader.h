#ifndef SHADER_H
#define SHADER_H

#include "uniformBuffer.h"
#include "oglReflection.h"
#include "layout.h"
#include "texture1.h"
#include "texture2.h"
#include "samplerState.h"

class Shader : public DrawObject
{
public:
	//Shader (std::string const& sName, std::string const& sSource);
	Shader ();
	Shader (OGLReflection const& reflector, int type);

	enum 
	{	UniformBufferShaderDataLookup = 0,               
        TextureSoloShaderDataLookup = 1,       
        SamplerStateShaderDataLookup = 2,      
        NUM_LOOKUP_INDICES = 3
	};
	//std::string GetSource () const;
	//std::string GetName () const;
	
	//void SetSource (std::string const sSource);
	//void SetName (std::string const sName);
	
	bool IsValid () const;

    int Set(std::string const& name, std::shared_ptr<UniformBuffer> const& object);
	template <typename T> int Set (std::string const& name, std::shared_ptr<T> const& object);
	
protected:

	struct Data
    {
        Data(DrawObjectType inType, std::string const& inName,
            int inBindPoint, int inNumBytes);

        std::shared_ptr<DrawObject> object; 
        DrawObjectType type;               
        std::string name;                     
        int bindPoint;                     
        int numBytes;                    
    };

	std::vector<Data> m_Data[NUM_LOOKUP_INDICES];

private:
	//std::string m_Name;
	//std::string m_Source;

	std::vector<std::vector<Layout>> m_VLayout;

public:
	std::vector<Data> GetData (int lookUp) const;
};
template <typename T>
int Shader::Set (std::string const& name, std::shared_ptr<T> const& object)
{
	int count = 0;
	int index = T::shaderLookUp;
	for (auto data = m_Data[index].begin (); data != m_Data[index].end (); data++)
	{
		if (name == data->name)
		{
			data->object = object;
			return count;
		}
		++count;
	}
	return -1;
}
#endif