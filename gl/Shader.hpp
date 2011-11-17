////////////////////////////////////////////////////////////
// Copyright (c) 2011 - Hiairrassary Victor
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of its 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////

#ifndef PLASTIC_SHADER_HPP
#define PLASTIC_SHADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/OpenGL.hpp>
#include <Plastic/Core/Matrix3.hpp>
#include <Plastic/Core/Matrix4.hpp>
#include <Plastic/Core/Vector2.hpp>
#include <Plastic/Core/Vector3.hpp>
#include <Plastic/Core/Vector4.hpp>

#include "Texture.hpp"

#include "VertexDeclaration.hpp"

#include <memory>
#include <string>
#include <vector>

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class Shader
    {

    public:
        Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

		~Shader();

        const VertexDeclaration& getVertexDeclaration() const;

        std::vector<GLint> getAttribsLocations(const VertexDeclaration &declaration) const;

        void bind() const;

        GLint getUniformLocation(const std::string &name) const;

        template<typename T>
        void setParameter(const std::string &name, const T &param) const;

        void setParameter(GLint location, const mat4 &matrix) const;
        void setParameter(GLint location, const mat3 &matrix) const;
        void setParameter(GLint location, GLfloat data) const;
        void setParameter(GLint location, const vec2 &vector) const;
        void setParameter(GLint location, const vec3 &vector) const;
        void setParameter(GLint location, const vec4 &vector) const;
        void setParameter(GLint location, GLuint data) const;
        void setParameter(GLint location, GLint data) const;

        void setParameter(const std::string &name, const std::shared_ptr<Texture> &tex, unsigned int textureUnit) const;
        void setParameter(GLint location, const std::shared_ptr<Texture> &tex, unsigned int textureUnit) const;

    //private:
		struct UniformInfo
		{
			GLint location;
			GLenum type;
			std::string name;
		};

		struct AttributeInfo
		{
			GLint location;
			GLenum type;
			std::string name;
		};

		GLuint createShader(GLenum type, const std::string &source);

		void checkProgram();

        void checkUniformFromLocation(GLint location, GLenum type) const;

		void getUniformsInfos();
		void getAttributesInfos();

		void extractDeclaration();

        void initialize(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

        void cleanUp();
        
		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		GLuint m_program;
		
		VertexDeclaration m_declaration;

		std::vector<UniformInfo> m_uniforms;
		std::vector<AttributeInfo> m_attributes;
    };

} // namespace plt


#include "Shader.inl"


#endif // PLASTIC_SHADER_HPP




////////////////////////////////////////////////////////////
/// \class plt::Shader
///
/// \todo Passer les attributs en private
/// \todo Sortir la macro #define PLASTIC_DEBUG 1
/// \todo Etre exception safe
/// \todo Renvoyer l'erreur OpenGL aussi
/// \todo Gérer les autres types de shader et savoir si tesselation hardware est activée
/// \todo Faire une assertion pour verifier lors d'un setParameter que le type est le bon 
/// \todo Avoir un constructeur par défaut avec les delegating constructor
/// \todo En cas d'exception gérer aussi les shader OpenGL à détruire et pas que le program
/// \todo Gérer les sorties des shader, notament pour faire du MRT
///
/// \todo Verifier que textureUnit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
///
////////////////////////////////////////////////////////////
