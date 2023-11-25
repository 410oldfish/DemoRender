#pragma once

namespace nwindow
{
  class IWindow //窗体接口
  {
  public:
    //获取GLFW窗体
    virtual void* get_native_window() = 0;

    virtual void set_native_window(void* window) = 0;
    //一些输入监听
    virtual void on_scroll(double delta) = 0;

    virtual void on_key(int key, int scancode, int action, int mods) = 0;

    virtual void on_resize(int width, int height) = 0;

    virtual void on_close() = 0;

    int Width;
    int Height;
    std::string Title;
  };
}