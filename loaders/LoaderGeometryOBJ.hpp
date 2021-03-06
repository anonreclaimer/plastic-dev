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


#ifndef PLASTIC_LOADERGEOMETRYOBJ_HPP
#define PLASTIC_LOADERGEOMETRYOBJ_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Plastic/Ressource/Loader.hpp>

#include <Plastic/Core.hpp>

#include "../gl/SubGeometry.hpp"
#include "../gl/Geometry.hpp"

#include <map>
#include <memory>

namespace plt
{   
    /////////////////////////////////////////////////////////////
    ///
    /////////////////////////////////////////////////////////////
    class LoaderGeometryOBJ : public Loader<Geometry>
    {
    public:
        virtual std::shared_ptr<Geometry> loadFromFile(const std::string& filename);

    private:
        std::shared_ptr<SubGeometry> createSubGeometry(std::map< plt::uvec3, unsigned int > &indexMap, unsigned int &index, const std::vector< vec3 > &positions, const std::vector< vec3 > &normals, const std::vector< vec2 > &textures, const std::vector< uvec3 > &indices);

        struct VertexObj
        {
            vec3 pos;
            vec2 uv;
            vec3 nor;
        };
    };


} // namespace plt


#endif // PLASTIC_LOADERGEOMETRYOBJ_HPP




////////////////////////////////////////////////////////////
/// \class plt::LoaderGeometryOBJ
///
///
////////////////////////////////////////////////////////////
