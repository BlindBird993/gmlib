#ifndef __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__
#define __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__


#include "../gmrendertarget.h"

namespace GMlib {

class RenderTexture : public RenderTarget {
public:
  explicit RenderTexture ();
  explicit RenderTexture ( const std::string& name );

  const GL::FramebufferObject&    getFbo() const;

private:

  GL::FramebufferObject     _fbo;
  GL::Texture               _tex_rb_color;

  void      init();

  // Virtual from RenderTarget
  void      doClear() const;
  void      doBind() const;
  void      doUnbind() const;
  void      doResize();

}; // END class RenderTexture

} // End namespace GMlib

#endif // __GM_SCENE_RENDER_RENDERTARGETS_RENDERTEXTURE_H__
