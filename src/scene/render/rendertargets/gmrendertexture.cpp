#include "gmrendertexture.h"
using namespace GMlib;

RenderTexture::RenderTexture()
  : _tex_rb_color(GL_TEXTURE_2D) {

  init();
}

RenderTexture::RenderTexture(const std::string& name)
  : _tex_rb_color( name, GL_TEXTURE_2D ) {

  init();
}

const GL::FramebufferObject&RenderTexture::getFbo() const {

  return _fbo;
}

void RenderTexture::init() {

  _tex_rb_color.setParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  _tex_rb_color.setParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  _tex_rb_color.setParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  _tex_rb_color.setParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
