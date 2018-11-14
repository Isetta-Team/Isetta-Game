//-----------------------------------------------------------------------------
// COMPILE-TIME OPTIONS FOR DEAR IMGUI
// Runtime options (clipboard callbacks, enabling various features, etc.) can
// generally be set via the ImGuiIO structure. You can use
// ImGui::SetAllocatorFunctions() before calling ImGui::CreateContext() to
// rewire memory allocation functions.
//-----------------------------------------------------------------------------
// A) You may edit imconfig.h (and not overwrite it when updating imgui, or
// maintain a patch/branch with your modifications to imconfig.h) B) or add
// configuration directives in your own file and compile with #define
// IMGUI_USER_CONFIG "myfilename.h" If you do so you need to make sure that
// configuration settings are defined consistently _everywhere_ dear imgui is
// used, which include the imgui*.cpp files but also _any_ of your code that
// uses imgui. This is because some compile-time options have an affect on data
// structures. Defining those options in imconfig.h will ensure every
// compilation unit gets to see the same data structure layouts. Call
// IMGUI_CHECKVERSION() from your .cpp files to verify that the data structures
// your files are using are matching the ones imgui.cpp is using.
//-----------------------------------------------------------------------------

#pragma once
#include "Core/Color.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector4.h"
#include "Graphics/GUIStyle.h"

//---- Define assertion handler. Defaults to calling assert().
// TODO(Jacob)
//#define IM_ASSERT(_EXPR)  MyAssert(_EXPR)
//#define IM_ASSERT(_EXPR)  ((void)(_EXPR))     // Disable asserts

//---- Define attributes of all API symbols declarations, e.g. for DLL under
// Windows.
// TODO(Jacob)
//#define IMGUI_API __declspec( dllexport )
//#define IMGUI_API __declspec( dllimport )

//---- Don't define obsolete functions/enums names. Consider enabling from time
// to time after updating to avoid using soon-to-be obsolete function/names.
// TODO(Jacob)
//#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

//---- Don't implement demo windows functionality
//(ShowDemoWindow()/ShowStyleEditor()/ShowUserGuide() methods will be empty)
//---- It is very strongly recommended to NOT disable the demo windows during
// development. Please read the comments in imgui_demo.cpp.
// #define IMGUI_DISABLE_DEMO_WINDOWS

//---- Don't implement some functions to reduce linkage requirements.
// #define IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS   // [Win32] Don't
// implement default clipboard handler. Won't use and link with
// OpenClipboard/GetClipboardData/CloseClipboard etc.

// #define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS         // [Win32] Don't
// implement default IME handler. Won't use and link with
// ImmGetContext/ImmSetCompositionWindow.

// #define IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS             // Don't implement
// ImFormatString/ImFormatStringV so you can implement them yourself if you
// don't want to link with vsnprintf.

// #define IMGUI_DISABLE_MATH_FUNCTIONS                     // Don't implement
// ImFabs/ImSqrt/ImPow/ImFmod/ImCos/ImSin/ImAcos/ImAtan2 wrapper so you can
// implement them yourself. Declare your prototypes in imconfig.h.

// TODO(Jacob)
//#define IMGUI_DISABLE_DEFAULT_ALLOCATORS                  // Don't implement
// default allocators calling malloc()/free() to avoid linking with them. You
// will need to call ImGui::SetAllocatorFunctions().

//---- Include imgui_user.h at the end of imgui.h as a convenience
//#define IMGUI_INCLUDE_IMGUI_USER_H

//---- Pack colors to BGRA8 instead of RGBA8 (to avoid converting from one to
// another) #define IMGUI_USE_BGRA_PACKED_COLOR

//---- Avoid multiple STB libraries implementations, or redefine path/filenames
// to prioritize another version
// By default the embedded implementations are declared static and not available
// outside of imgui cpp files.
//#define IMGUI_STB_TRUETYPE_FILENAME   "my_folder/stb_truetype.h"
//#define IMGUI_STB_RECT_PACK_FILENAME  "my_folder/stb_rect_pack.h"
//#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
//#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION

//---- Define constructor and implicit cast operators to convert back<>forth
// between your math types and ImVec2/ImVec4.
// This will be inlined as part of ImVec2 and ImVec4 class declarations.
#define IM_VEC2_CLASS_EXTRA                         \
  explicit ImVec2(const Isetta::Math::Vector2& v) { \
    x = v.x;                                        \
    y = v.y;                                        \
  }                                                 \
  explicit operator Isetta::Math::Vector2() const { \
    return Isetta::Math::Vector2(x, y);             \
  }

#define IM_VEC4_CLASS_EXTRA                         \
  explicit ImVec4(const Isetta::Math::Vector4& v) { \
    x = v.x;                                        \
    y = v.y;                                        \
    z = v.z;                                        \
    w = v.w;                                        \
  }                                                 \
  explicit operator Isetta::Math::Vector4() const { \
    return Isetta::Math::Vector4(x, y, z, w);       \
  }                                                 \
  explicit ImVec4(const Isetta::Color& c) {         \
    x = c.r;                                        \
    y = c.g;                                        \
    z = c.b;                                        \
    w = c.a;                                        \
  }                                                 \
  explicit operator Isetta::Color() const { return Isetta::Color(x, y, z, w); }

#define IM_GUI_STYLE_CLASS_EXTRA                                              \
  explicit ImGuiStyle(const Isetta::GUIStyle& style) {                        \
    Alpha = style.Alpha;                                                      \
    WindowPadding = ImVec2(style.WindowPadding);                              \
    WindowRounding = style.WindowRounding;                                    \
    WindowBorderSize = style.WindowBorderSize;                                \
    WindowMinSize = ImVec2(style.WindowMinSize);                              \
    WindowTitleAlign = ImVec2(style.WindowTitleAlign);                        \
    ChildRounding = style.ChildRounding;                                      \
    ChildBorderSize = style.ChildBorderSize;                                  \
    PopupRounding = style.PopupRounding;                                      \
    PopupBorderSize = style.PopupBorderSize;                                  \
    FramePadding = ImVec2(style.FramePadding);                                \
    FrameRounding = style.FrameRounding;                                      \
    FrameBorderSize = style.FrameBorderSize;                                  \
    ItemSpacing = ImVec2(style.ItemSpacing);                                  \
    ItemInnerSpacing = ImVec2(style.ItemInnerSpacing);                        \
    TouchExtraPadding = ImVec2(style.TouchExtraPadding);                      \
    IndentSpacing = style.IndentSpacing;                                      \
    ColumnsMinSpacing = style.ColumnsMinSpacing;                              \
    ScrollbarSize = style.ScrollbarSize;                                      \
    ScrollbarRounding = style.ScrollbarRounding;                              \
    GrabMinSize = style.GrabMinSize;                                          \
    GrabRounding = style.GrabRounding;                                        \
    ButtonTextAlign = ImVec2(style.ButtonTextAlign);                          \
    DisplayWindowPadding = ImVec2(style.DisplayWindowPadding);                \
    DisplaySafeAreaPadding = ImVec2(style.DisplaySafeAreaPadding);            \
    MouseCursorScale = style.MouseCursorScale;                                \
    AntiAliasedFill = style.AntiAliasedFill;                                  \
    CurveTessellationTol = style.CurveTessellationTol;                        \
    for (int i = 0; i < ImGuiCol_COUNT; i++)                                  \
      Colors[i] = ImVec4(style.Colors[i]);                                    \
  }                                                                           \
  explicit operator Isetta::GUIStyle() const {                                \
    Isetta::GUIStyle style = Isetta::GUIStyle(false);                         \
    style.Alpha = Alpha;                                                      \
    style.WindowPadding = Isetta::Math::Vector2(WindowPadding);               \
    style.WindowRounding = WindowRounding;                                    \
    style.WindowBorderSize = WindowBorderSize;                                \
    style.WindowMinSize = Isetta::Math::Vector2(WindowMinSize);               \
    style.WindowTitleAlign = Isetta::Math::Vector2(WindowTitleAlign);         \
    style.ChildRounding = ChildRounding;                                      \
    style.ChildBorderSize = ChildBorderSize;                                  \
    style.PopupRounding = PopupRounding;                                      \
    style.PopupBorderSize = PopupBorderSize;                                  \
    style.FramePadding = Isetta::Math::Vector2(FramePadding);                 \
    style.FrameRounding = FrameRounding;                                      \
    style.FrameBorderSize = FrameBorderSize;                                  \
    style.ItemSpacing = Isetta::Math::Vector2(ItemSpacing);                   \
    style.ItemInnerSpacing = Isetta::Math::Vector2(ItemInnerSpacing);         \
    style.TouchExtraPadding = Isetta::Math::Vector2(TouchExtraPadding);       \
    style.IndentSpacing = IndentSpacing;                                      \
    style.ColumnsMinSpacing = ColumnsMinSpacing;                              \
    style.ScrollbarSize = ScrollbarSize;                                      \
    style.ScrollbarRounding = ScrollbarRounding;                              \
    style.GrabMinSize = GrabMinSize;                                          \
    style.GrabRounding = GrabRounding;                                        \
    style.ButtonTextAlign = Isetta::Math::Vector2(ButtonTextAlign);           \
    style.DisplayWindowPadding = Isetta::Math::Vector2(DisplayWindowPadding); \
    style.DisplaySafeAreaPadding =                                            \
        Isetta::Math::Vector2(DisplaySafeAreaPadding);                        \
    style.MouseCursorScale = MouseCursorScale;                                \
    style.AntiAliasedFill = AntiAliasedFill;                                  \
    style.CurveTessellationTol = CurveTessellationTol;                        \
    for (int i = 0; i < ImGuiCol_COUNT; i++)                                  \
      style.Colors[i] = Isetta::Color(Colors[i]);                             \
    return style;                                                             \
  }

//---- Use 32-bit vertex indices (default is 16-bit) to allow meshes with
// more than 64K vertices. Render function needs to support it. #define
// ImDrawIdx unsigned int

//---- Tip: You can add extra functions within the ImGui:: namespace, here
// or in your own headers files.
/*
namespace ImGui
{
    void MyFunction(const char* name, const MyMatrix44& v);
}
*/
