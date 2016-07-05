#ifndef __GM_SCENE_RENDER_RENDERTARGETS_TEXTURERENDERTARGET_H__
#define __GM_SCENE_RENDER_RENDERTARGETS_TEXTURERENDERTARGET_H__


#include "../gmrendertarget.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>

namespace GMlib {

class TextureRenderTarget : public RenderTarget {
public:
  explicit TextureRenderTarget ();
  explicit TextureRenderTarget ( const std::string& name );

  const GL::FramebufferObject&    getFbo() const;
  const GL::Texture&              getTexture() const;
  void                            setClearColor( const Color& c );

private:
  GL::FramebufferObject     _fbo;
  GL::Texture               _tex_rb_color;

  Color                     _clear_color;

  void      init( const std::string& name = std::string());

  // Virtual from RenderTarget
  void      doPrepare() const;
  void      doBind() const;
  void      doUnbind() const;
  void      doResize();

}; // END class TextureRenderTarget

} // End namespace GMlib

#endif // __GM_SCENE_RENDER_RENDERTARGETS_TEXTURERENDERTARGET_H__
