#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <vector>
#include "Mesh.h"


#define RM_SHADER_FAILURE -1

namespace M3D{
	class ResourceManager{
	public:
		ResourceManager(void);
		~ResourceManager(void);
		bool initialize(void);
		void shutdown(void);
		GLuint loadShader(const GLenum type, const std::string filename);
		GLuint createProgram(const std::vector<GLuint> shaders);
		Mesh* loadObjFile(const std::string filename);
	private:
		char *loadFile(const std::string filename);
		bool initialized;
	};

}

#endif
