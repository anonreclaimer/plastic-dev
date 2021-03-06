////////////////////////////////////////////////////////////
// Copyright (c) 2011 - 2012 Hiairrassary Victor
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


#ifndef PLASTIC_HARDWAREGEOMETRY_HPP
#define PLASTIC_HARDWAREGEOMETRY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/OpenGL.hpp>

#include "Geometry.hpp"
#include "VertexDeclaration.hpp"

#include <memory>
#include <vector>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

namespace plt
{
	/////////////////////////////////////////////////////////////////
	///
	/////////////////////////////////////////////////////////////////
    class HardwareGeometry
    {

    public:
        HardwareGeometry(const std::shared_ptr<Geometry> &geometry);

        ~HardwareGeometry();

        void bind() const;

        void unbind() const;

        void draw() const;
        
    private:
        void createAndFillVertexBuffer(const std::shared_ptr<Geometry> &geometry);

        void createAndFillIndexBuffer(const std::shared_ptr<Geometry> &geometry);

        void createAndFillVertexArray(const std::shared_ptr<Geometry> &geometry);

        void extractLocations();

        void initialize(const std::shared_ptr<Geometry> &geometry);

        void cleanUp();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
        std::vector<GLint> m_locations;

        VertexDeclaration m_declaration;

        unsigned int m_vertexCountTotal;
        unsigned int m_indexCountTotal;

        GLenum m_primitiveType;
        GLenum m_indexType;

        GLuint m_vbo;
        GLuint m_ibo;
        GLuint m_vao;
    };

} // namespace plt


#endif // PLASTIC_HARDWAREGEOMETRY_HPP




////////////////////////////////////////////////////////////
/// \class plt::HardwareGeometry
///
/// \todo Sortir le #define PLASTIC_DEBUG 1
/// \todo Prendre en compte si y a tesselation hardware
/// \todo Etre exceptions safe
///
////////////////////////////////////////////////////////////
