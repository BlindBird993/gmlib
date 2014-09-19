#ifndef __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__
#define __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__


#include "../gmrendertarget.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>

namespace GMlib {

class RenderTexture : public RenderTarget {
public:
  explicit RenderTexture ();
  explicit RenderTexture ( const std::string& name );

  const GL::FramebufferObject&    getFbo() const;
  const GL::Texture&              getTexture() const;
  void                            setClearColor( const Color& c );

private:
  GL::FramebufferObject     _fbo;
  GL::Texture               _tex_rb_color;

  Color                     _clear_color;

  void      init( const std::string& name = std::string());

  // Virtual from RenderTarget
  void      doClear() const;
  void      doBind() const;
  void      doUnbind() const;
  void      doResize();

}; // END class RenderTexture

} // End namespace GMlib

#endif // __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__
