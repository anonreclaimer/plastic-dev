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
    template<typename T>
    inline VertexBufferFormatted<T>::VertexBufferFormatted
    (
        const VertexDeclaration &declaration, 
        const std::vector<T> &vertexDatas
    ) :
    VertexBuffer(declaration),
    m_vertexDatas(vertexDatas)
    {
        checkValidity();
    }


    template<typename T>
    inline VertexBufferFormatted<T>::VertexBufferFormatted
    (
        const VertexDeclaration &declaration, 
        std::vector<T> &&vertexDatas
    ) :
    VertexBuffer(declaration),
    m_vertexDatas(std::move(vertexDatas))
    {
        checkValidity();
    }


    template<typename T>
    inline const void* VertexBufferFormatted<T>::getVertexRawData
    (
    ) const
    {
        return &m_vertexDatas[0];
    }


    template<typename T>
    inline unsigned int VertexBufferFormatted<T>::getVertexCount
    (
    ) const
    {
        return m_vertexDatas.size();
    }


    template<typename T>
    inline void VertexBufferFormatted<T>::checkValidity
    (
    ) const
    {
        if(sizeof(T) != m_declaration.size())
            throw std::runtime_error("Size declaration and sizeof(T) aren't compatible, may be check the padding");
    }

} // namespace plt
