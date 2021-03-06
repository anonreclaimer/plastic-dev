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


namespace plt
{
    namespace
    {
        VertexDeclaration declaration;

    } // namespace



    template<typename T, typename U>
    inline DynamicGeometry<T, U>::DynamicGeometry
    (
        const Skeleton<T> &baseSkeleton, 
        std::vector< Vertex > vertices, 
        std::vector< Triangle > triangles, 
        std::vector< Weight > weights
    ) :
    Geometry(declaration, PT_TRIANGLES),
    m_baseSkeleton(baseSkeleton),
    m_vertices(vertices),
    m_triangles(triangles),
    m_weights(weights)
    {
        checkValidity();
    }


    template<typename T, typename U>
    inline void DynamicGeometry<T, U>::checkValidity
    (

    ) const
    {
        if(m_vertices.size() == 0)
            throw std::runtime_error("The geometry haven't got vertex");

        if(m_triangles.size() == 0)
            throw std::runtime_error("The geometry haven't got triangle");

        if(m_weights.size() == 0)
            throw std::runtime_error("The geometry haven't got weight");

        if(m_baseSkeleton.bonesCount() == 0)
            throw std::runtime_error("The skeleton haven't got bone");



        std::size_t nbWeights = m_weights.size();

        for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            if( (*it).start + (*it).count > nbWeights)
                throw std::runtime_error("A vertex use an invalid(s) weight(s)");


            if( (*it).count > 4)
                throw std::runtime_error("A vertex can't have more than four bones");

            T sumBias(0);

            for(std::size_t i(0); i<(*it).count; ++i)
                sumBias += m_weights[ (*it).start + i].bias;

            if( !equals(sumBias, T(1.0)) )
                throw std::runtime_error("The sum of all bias is different than 1.0");
        }



        U indexMax(0);

        for(auto it = m_triangles.begin(); it!=m_triangles.end(); ++it)
            indexMax = std::max(std::max( (*it).index.x, (*it).index.y), (*it).index.z);

        if(indexMax>=m_vertices.size())
            throw std::runtime_error("An index use an invalid vertex");



        std::size_t bonesCount = m_baseSkeleton.bonesCount();

        for(auto it = m_weights.begin(); it!=m_weights.end(); ++it)
        {
            if((*it).joint >= bonesCount)
                throw std::runtime_error("A weight use an invalid joint");
        }


        if(getIndexCount() % vertexPerPrimitiveCount(m_primitiveType) != 0)
            throw std::runtime_error("Index count doesn't correspond");
    }

} // namespace plt
