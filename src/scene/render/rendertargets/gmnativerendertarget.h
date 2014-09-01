#ifndef __GM_SCENE_RENDER_RENDERTARGETS_NATIVERENDERTARGETS_H__
#define __GM_SCENE_RENDER_RENDERTARGETS_NATIVERENDERTARGETS_H__


#include "../gmrendertarget.h"


namespace GMlib {

  // PassThroughTarget
class NativeRenderTarget : public RenderTarget {
public:
  explicit NativeRenderTarget() {}

private:
  // Virtual from RenderTarget
  void    doClear() const {}
  void    doBind() const {}
  void    doUnbind() const {}
  void    doResize() {}

}; // END class NativeRenderTarget

} // End namespace GMlib

#endif // __GM_SCENE_RENDER_RENDERTARGETS_NATIVERENDERTARGETS_H__
