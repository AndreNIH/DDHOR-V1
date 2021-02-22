#define WIN32_LEAN_AND_MEAN
#include <cocos2d.h>
#include <Windows.h>
#include "graphics.h"
#include <GL/gl.h>
#include <kiero/kiero.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_opengl2.h>
#include "MainMenu.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC oWndProc = nullptr;
HGLRC ImGuiWglContext = nullptr;

bool gImguiInitialized = false;
bool gGraphicsInitialized = false;
bool gShowUI = false;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


BOOL(__stdcall* wglSwapBuffersPtr) (HDC hDC) = nullptr;
BOOL __stdcall wglSwapBuffersHook(HDC hDC) {
    if (!gImguiInitialized) {
        HWND mWindow = WindowFromDC(hDC);
        oWndProc = (WNDPROC)SetWindowLongPtr(mWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
        ImGuiWglContext = wglCreateContext(hDC);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(mWindow);
        ImGui_ImplOpenGL2_Init();
        ImGui::StyleColorsDark();
        gImguiInitialized = true;
    }
    if (GetAsyncKeyState(VK_LSHIFT) == -32767)
        gShowUI = !gShowUI;

    const bool enableGameUI = !ImGui::GetIO().WantCaptureMouse || !gShowUI;
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(enableGameUI);
    if (gShowUI) {
        HGLRC OldWglContext = wglGetCurrentContext();
        wglMakeCurrent(hDC, ImGuiWglContext);

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
        MainMenu::createMenu();

        
        ImGui::EndFrame();
        ImGui::Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        wglMakeCurrent(hDC, OldWglContext);
    }
    return wglSwapBuffersPtr(hDC);
}
constexpr uint16_t glSwapBuffersID = 336;
bool OverlayGraphics::initialize(){
    //maybe put this inside a loop?
    if (gGraphicsInitialized) return false;
    if (kiero::init(kiero::RenderType::OpenGL) != kiero::Status::Success)
        return false;
    
    auto status = kiero::bind(
        glSwapBuffersID,
        reinterpret_cast<void**>(&wglSwapBuffersPtr),
        wglSwapBuffersHook);
    if (status != kiero::Status::Success)
        return false;
}

void OverlayGraphics::uninitilize() {
    kiero::unbind(glSwapBuffersID);
    gGraphicsInitialized = false;
    gImguiInitialized = false;
}