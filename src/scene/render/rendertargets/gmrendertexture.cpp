#include "gmrendertexture.h"
using namespace GMlib;

RenderTexture::RenderTexture() {

  init();
}

RenderTexture::RenderTexture(const std::string& name) {

  init(name);
}

const GL::FramebufferObject&RenderTexture::getFbo() const {

  return _fbo;
}

void RenderTexture::init(const std::string &name) {

  _fbo.create();

  if(name.length()) _tex_rb_color.create(name,GL_TEXTURE_2D);
  else              _tex_rb_color.create(GL_TEXTURE_2D);
  _tex_rb_color.texParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  _tex_rb_color.texParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  _tex_rb_color.texParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  _tex_rb_color.texParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  _fbo.attachTexture2D( _tex_rb_color, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );
}

void RenderTexture::doClear() const {}

void RenderTexture::doBind() const {

  _fbo.bind();
}

void RenderTexture::doUnbind() const {

  _fbo.unbind();
}

void RenderTexture::doResize() {

  _tex_rb_color.texImage2D( 0, GL_RGBA8, getWidth(), getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
}
