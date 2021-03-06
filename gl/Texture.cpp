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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Texture.hpp"

#include "GLEnum.hpp"

#include "UploaderTexture.hpp"
#include "UploaderTextureSingle.hpp"
#include "UploaderTextureMulti.hpp"
#include "UploaderTexture1D.hpp"
#include "UploaderTexture2D.hpp"
#include "UploaderTextureCubemap.hpp"
#include "UploaderTextureRect.hpp"
#include "UploaderTexture1DArray.hpp"
#include "UploaderTexture2DArray.hpp"
#include "UploaderTextureCubemapArray.hpp"

#include <Plastic/Core/Vector2.hpp>

#define PLASTIC_DEBUG 1
#include "GLCheck.hpp"

#include <algorithm>
#include <stdexcept>

namespace plt
{
    namespace
    {
        const std::vector< std::shared_ptr<UploaderTextureSingle> > uploadersSingle = 
        {
            std::make_shared<UploaderTexture1D>(),
            std::make_shared<UploaderTexture2D>(),
            std::make_shared<UploaderTextureRect>()
        };


        const std::vector< std::shared_ptr<UploaderTextureMulti> > uploadersMulti = 
        {
            std::make_shared<UploaderTextureCubemap>(),
            std::make_shared<UploaderTexture1DArray>(),
            std::make_shared<UploaderTexture2DArray>(),
            std::make_shared<UploaderTextureCubemapArray>()
        };


        std::shared_ptr<UploaderTextureSingle> findUploaderSingle(TextureType texType)
        {
            auto it = std::find_if(uploadersSingle.begin(), uploadersSingle.end(), [texType](const std::shared_ptr<UploaderTextureSingle> &u) {return u->getTextureTypeToLoad() == texType;} );

            if(it == uploadersSingle.end())
                throw std::runtime_error("No uploader for this texture type");

            return (*it);
        }


        std::shared_ptr<UploaderTextureMulti> findUploaderMulti(TextureType texType)
        {
            auto it = std::find_if(uploadersMulti.begin(), uploadersMulti.end(), [texType](const std::shared_ptr<UploaderTextureMulti> &u) {return u->getTextureTypeToLoad() == texType;} );

            if(it == uploadersMulti.end())
                throw std::runtime_error("No uploader for this texture type");

            return (*it);
        }

    } // namespace






    unsigned int Texture::getMipMapLevelsCount
    (
        unsigned int width, 
        unsigned int height
    )
    {
        unsigned int count(0);

        while ((width > 1) || (height > 1))
        {
            if (width > 1)  width  /= 2;
            if (height > 1) height /= 2;
            ++count;
        }

        return count;
    }


    unsigned int Texture::nearestPowerOfTwo
    (
        unsigned int value
    )
    {
        unsigned int temp = value;
        unsigned int plasticOfTwo = 0;

        while (temp > 1)
        {
            temp >>= 1;
            ++plasticOfTwo;
        }

        unsigned int retval = 1 << plasticOfTwo;

        return retval == value ? retval : retval << 1;
    }
















    Texture::Texture
    (
    )
    {

    }


    Texture::Texture
    (
        TextureType texType, 
        PixelFormat format,
        unsigned int image,
        const uvec2 &dimensions
    )
    {
        try
        {
            initializeEmptyTexture(texType, format, image, dimensions);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Texture initialisation");
        }  
    }


    Texture::Texture
    (
        TextureType texType, 
        TextureMipmapFlag texMipMapFlag, 
        const std::shared_ptr<Image> &image
    )
    {
        try
        {
            initializeTextureSingle(texType, texMipMapFlag, image);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Texture initialisation");
        }  
    }


    Texture::Texture
    (
        TextureType texType, 
        TextureMipmapFlag texMipMapFlag, 
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        try
        {
            initializeTextureArray(texType, texMipMapFlag, images);
        }

        catch(const std::exception &e)
        {
            cleanUp();

            throw; //std::runtime_error("Error during Texture initialisation");
        }  
    }


    Texture::~Texture
    (
    )
    {
        cleanUp();   
    }


    void Texture::cleanUp
    (
    )
    {
        if( glIsTexture(m_texture) )
            GLCheck( glDeleteTextures(1, &m_texture) );
    }


    void Texture::bind
    (
    ) const
    {
        GLCheck( glBindTexture(m_target, m_texture) );
    }


    void Texture::unbind
    (
    ) const
    {
        GLCheck( glBindTexture(m_target, 0) );
    }


    GLenum Texture::getGLSLType
    (
    ) const
    {
        return m_glslType;
    }


    GLuint Texture::getOpenGLTarget
    (
    ) const
    {
        return m_target;
    }


    GLuint Texture::getOpenGLHandle
    (
    ) const
    {
        return m_texture;
    }


    PixelFormat Texture::getPixelFormat
    (
    ) const
    {
        return m_format;
    }


    TextureType Texture::getTextureType
    (
    ) const
    {
        return m_textureType;
    }


    const uvec2& Texture::getDimensions
    (
    ) const
    {
        return m_dimensions;
    }


    bool Texture::hasMipmaps
    (   
    ) const
    {
        return m_hasMipMap;
    }


    void Texture::initializeEmptyTexture
    (
        TextureType texType, 
        PixelFormat format,
        unsigned int image,
        const uvec2 &dimensions
    )
    {
        m_texture = 0;
        m_format = format;
        m_textureType = texType;
        m_textureMipMapFlag = TextureMipmapFlag::NoMipMap;
        m_dimensions = dimensions;
        m_hasMipMap = false;

        if(TextureTypeInfos::getInfos(texType).hasSingleImage() )
        {
            if(image != 1)
                throw std::runtime_error("For single empty texture, imageCount must be equal to 1");

            auto uploader = findUploaderSingle(texType);

            m_target = uploader->getGLTarget();
            m_glslType = uploader->getGLSLType(m_format);
        }

        else
        {
            auto uploader = findUploaderMulti(texType);

            m_target = uploader->getGLTarget();
            m_glslType = uploader->getGLSLType(m_format);
        }


        GLCheck( glGenTextures(1, &m_texture) );
        bind();
            if(TextureTypeInfos::getInfos(texType).hasSingleImage() )
            {
                auto uploader = findUploaderSingle(texType);

                uploader->allocateTextureMemory(format, dimensions, 1);
            }

            else
            {
                auto uploader = findUploaderMulti(texType);

                findUploaderMulti(texType)->allocateTextureMemory(format, dimensions, image, 1);
            }
        unbind();
    }


    void Texture::initializeTextureSingle
    (
        TextureType texType, 
        TextureMipmapFlag texMipMapFlag, 
        const std::shared_ptr<Image> &image
    )
    {
        if(! TextureTypeInfos::getInfos(texType).hasSingleImage() )
            throw std::runtime_error("Can't be a single texture typre");


        if((*image).levels() < 1)
            throw std::runtime_error("No levels in first image");

        auto uploader = findUploaderSingle(texType);


        m_texture = 0;
        m_format = (*image)[0].getFormat();
        m_textureType = texType;
        m_textureMipMapFlag = texMipMapFlag;
        m_dimensions = (*image)[0].getDimensions();

        m_target = uploader->getGLTarget();
        m_glslType = uploader->getGLSLType(m_format);

        m_hasMipMap = (texMipMapFlag == TextureMipmapFlag::NoMipMap) ? false : true;


        uploader->checkImage(texMipMapFlag, image);

        GLCheck( glGenTextures(1, &m_texture) );
        bind();
            auto dim = (*image)[0].getDimensions();

            unsigned int levels = (texMipMapFlag == TextureMipmapFlag::FromImage) ? Texture::getMipMapLevelsCount(dim.x, dim.y) + 1 : 1;

            uploader->allocateTextureMemory(m_format, dim, levels);
            uploader->uploadImage(texMipMapFlag, image);
        unbind();
    }


    void Texture::initializeTextureArray
    (
        TextureType texType, 
        TextureMipmapFlag texMipMapFlag, 
        const std::vector< std::shared_ptr<Image> > &images
    )
    {
        if(! TextureTypeInfos::getInfos(texType).hasMultiImages() )
            throw std::runtime_error("Can't be a multi texture typre");

        if(images.size() < 1)
            throw std::runtime_error("No images when create texture");

        if((*images[0]).levels() < 1)
            throw std::runtime_error("No levels in first image");

        auto uploader = findUploaderMulti(texType);


        m_texture = 0;
        m_format = (*images[0])[0].getFormat();
        m_textureType = texType;
        m_textureMipMapFlag = texMipMapFlag;
        m_dimensions = (*images[0])[0].getDimensions();

        m_target = uploader->getGLTarget();
        m_glslType = uploader->getGLSLType(m_format);

        m_hasMipMap = (texMipMapFlag == TextureMipmapFlag::NoMipMap) ? false : true;


        uploader->checkImages(texMipMapFlag, images);

        GLCheck( glGenTextures(1, &m_texture) );
        bind();
            auto dim = (*images[0])[0].getDimensions();

            unsigned int levels = (texMipMapFlag == TextureMipmapFlag::FromImage) ? Texture::getMipMapLevelsCount(dim.x, dim.y) + 1 : 1;

            uploader->allocateTextureMemory(m_format, dim, images.size(), levels);
            uploader->uploadImages(texMipMapFlag, images);
        unbind();
    }


} // namespace plt
