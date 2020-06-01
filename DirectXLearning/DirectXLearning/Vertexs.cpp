/*++

Copyright (c) 2008  Microsoft Corporation

Module Name:

    apiset.h

Abstract:

    This module contains definitions related to the management of API namespaces.

Author:

    Arun Kishan (arunki) 14-Sep-2008

--*/

#ifndef _API_SET_H_
#define _API_SET_H_

//
// API set interface definitions.
//

#define API_SET_OVERRIDE(X)             X##Implementation
#define API_SET_LEGACY_OVERRIDE_DEF(X)  X = API_SET_OVERRIDE(X)
#define API_SET_OVERRIDE_DEF(X)         API_SET_LEGACY_OVERRIDE_DEF(X) PRIVATE

#ifdef _M_HYBRID_X86_ARM64

#define API_SET_CHPE_GUEST X86

#else

#define API_SET_CHPE_GUEST

#endif

#ifdef _API_SET_HOST
// This section is intended for hosting contracts. Any legacy host definitions are ignored.

#undef API_SET_LIBRARY

#define API_SET_LIBRARY(X)

#undef API_SET
#undef API_SET_DIR
#undef API_SET_PRIVATE
#undef API_SET_PRIVATE_DIR
#undef API_SET_BY_ORDINAL
#undef API_SET_BY_ORDINAL_DIR
#undef API_SET_BY_ORDINAL_PRIVATE
#undef API_SET_BY_ORDINAL_PRIVATE_DIR

#undef API_SET_LEGACY
#undef API_SET_LEGACY_DIR
#undef API_SET_LEGACY_PRIVATE
#undef API_SET_LEGACY_PRIVATE_DIR
#undef API_SET_LEGACY_BY_ORDINAL
#undef API_SET_LEGACY_BY_ORDINAL_DIR
#undef API_SET_LEGACY_BY_ORDINAL_PRIVATE
#undef API_SET_LEGACY_BY_ORDINAL_PRIVATE_DIR

#define API_SET(X)                                  X PRIVATE
#define API_SET_DIR(X,DIR)                          X DIR PRIVATE
#define API_SET_PRIVATE(X)                          X PRIVATE
#define API_SET_PRIVATE_DIR(X, DIR)                 X DIR PRIVATE
#define API_SET_BY_ORDINAL(X,O,PO)                  X @##O NONAME PRIVATE
#define API_SET_BY_ORDINAL_DIR(X,O,PO,DIR)          X @##O NONAME DIR PRIVATE
#define API_SET_BY_ORDINAL_PRIVATE(X,O,PO)          X @##O NONAME PRIVATE
#define API_SET_BY_ORDINAL_PRIVATE_DIR(X,O,PO,DIR)  X @##O NONAME DIR PRIVATE

#define API_SET_LEGACY(X,L)                         X PRIVATE
#define API_SET_LEGACY_DIR(X,L,DIR)                 X DIR PRIVATE
#define API_SET_LEGACY_PRIVATE(X,L)                 X PRIVATE
#define API_SET_LEGACY_PRIVATE_DIR(X,L,DIR)         X DIR PRIVATE
#define API_SET_LEGACY_BY_ORDINAL(X,L,O,PO)         X @##O NONAME PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_DIR(X,L,O,PO,DIR) X @##O NONAME DIR PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE(X,L,O,PO) X @##O NONAME PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE_DIR(X,L,O,PO,DIR) X @##O NONAME DIR PRIVATE

#else

#if defined(_API_SET_LEGACY_TARGET)
// This section is intended for "classic apiset forwarders" that are forwarding back to a legacy host.
// In this section, the definition for _API_SET_LEGACY_TARGET is taken as the default legacy host for the
// entire contract. But any APIs which specify LegacyHost directly will override this definition.

#define API_SET(X)                                  X = _API_SET_LEGACY_TARGET##.##X
#define API_SET_DIR(X,DIR)                          X = _API_SET_LEGACY_TARGET##.##X DIR
#define API_SET_PRIVATE(X)                          X = _API_SET_LEGACY_TARGET##.##X PRIVATE
#define API_SET_PRIVATE_DIR(X,DIR)                  X = _API_SET_LEGACY_TARGET##.##X DIR PRIVATE
#define API_SET_BY_ORDINAL(X,O,PO)                  X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME
#define API_SET_BY_ORDINAL_DIR(X,O,PO,DIR)          X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME DIR
#define API_SET_BY_ORDINAL_PRIVATE(X,O,PO)          X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME PRIVATE
#define API_SET_BY_ORDINAL_PRIVATE_DIR(X,O,PO,DIR)  X = _API_SET_LEGACY_TARGET##.##PO @##O NONAME DIR PRIVATE

#define API_SET_LEGACY(X,L)                         X = L##.##X
#define API_SET_LEGACY_DIR(X,L,DIR)                 X = L##.##X DIR
#define API_SET_LEGACY_PRIVATE(X,L)                 X = L##.##X PRIVATE
#define API_SET_LEGACY_PRIVATE_DIR(X,L,DIR)         X = L##.##X DIR PRIVATE
#define API_SET_LEGACY_BY_ORDINAL(X,L,O,PO)         X = L##.##PO @##O NONAME
#define API_SET_LEGACY_BY_ORDINAL_DIR(X,L,O,PO,DIR) X = L##.##PO @##O NONAME DIR
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE(X,L,O,PO) X = L##.##PO @##O NONAME PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE_DIR(X,L,O,PO,DIR) X = L##.##PO @##O NONAME DIR PRIVATE

#elif defined(_API_SET_FORWARDER_TARGET)
// This section is intended for "reverse forwarders" that are forwarding to an explicit apiset name.
// Any legacy targets are ignored.
#define API_SET(X)                                  X = _API_SET_FORWARDER_TARGET##.##X
#define API_SET_DIR(X,DIR)                          X = _API_SET_FORWARDER_TARGET##.##X DIR
#define API_SET_PRIVATE(X)                          X = _API_SET_FORWARDER_TARGET##.##X PRIVATE
#define API_SET_PRIVATE_DIR(X,DIR)                  X = _API_SET_FORWARDER_TARGET##.##X DIR PRIVATE
#define API_SET_BY_ORDINAL(X,O,PO)                  X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME
#define API_SET_BY_ORDINAL_DIR(X,O,PO,DIR)          X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME DIR
#define API_SET_BY_ORDINAL_PRIVATE(X,O,PO)          X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME PRIVATE
#define API_SET_BY_ORDINAL_PRIVATE_DIR(X,O,PO,DIR)  X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME DIR PRIVATE

#define API_SET_LEGACY(X,L)                         X = _API_SET_FORWARDER_TARGET##.##X
#define API_SET_LEGACY_DIR(X,L,DIR)                 X = _API_SET_FORWARDER_TARGET##.##X DIR
#define API_SET_LEGACY_PRIVATE(X,L)                 X = _API_SET_FORWARDER_TARGET##.##X PRIVATE
#define API_SET_LEGACY_PRIVATE_DIR(X,L,DIR)         X = _API_SET_FORWARDER_TARGET##.##X DIR PRIVATE
#define API_SET_LEGACY_BY_ORDINAL(X,L,O,PO)         X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME
#define API_SET_LEGACY_BY_ORDINAL_DIR(X,L,O,PO,DIR) X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME DIR
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE(X,L,O,PO) X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE_DIR(X,L,O,PO,DIR) X = _API_SET_FORWARDER_TARGET##.##PO @##O NONAME DIR PRIVATE

#else
// This section is intended for internal contract generation to build artifacts that model the contract without forwarding.

#define API_SET(X)                                  X
#define API_SET_DIR(X,DIR)                          X DIR
#define API_SET_PRIVATE(X)                          X PRIVATE
#define API_SET_PRIVATE_DIR(X,DIR)                  X DIR PRIVATE
#define API_SET_BY_ORDINAL(X,O,PO)                  X @##O NONAME
#define API_SET_BY_ORDINAL_DIR(X,O,PO,DIR)          X @##O NONAME DIR
#define API_SET_BY_ORDINAL_PRIVATE(X,O,PO)          X @##O NONAME PRIVATE
#define API_SET_BY_ORDINAL_PRIVATE_DIR(X,O,PO,DIR)  X @##O NONAME DIR PRIVATE

#define API_SET_LEGACY(X,L)                         X
#define API_SET_LEGACY_DIR(X,L,DIR)                 X DIR
#define API_SET_LEGACY_PRIVATE(X,L)                 X PRIVATE
#define API_SET_LEGACY_PRIVATE_DIR(X,L,DIR)         X DIR PRIVATE
#define API_SET_LEGACY_BY_ORDINAL(X,L,O,PO)         X @##O NONAME
#define API_SET_LEGACY_BY_ORDINAL_DIR(X,L,O,PO,DIR) X @##O NONAME DIR
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE(X,L,O,PO) X @##O NONAME PRIVATE
#define API_SET_LEGACY_BY_ORDINAL_PRIVATE_DIR(X,L,O,PO,DIR) X @##O NONAME DIR PRIVATE

#endif // _API_SET_LEGACY_TARGET, _API_SET_FORWARDER_TARGET

#define API_SET_LIBRARY(X)              LIBRARY X

#endif // _API_SET_HOST

#endif // _API_SET_H_
//-----------------------------------------------------------------------------
// File: Vertices.cpp
//
// Desc: In this tutorial, we are rendering some vertices. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       vertices. Vertices can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using vertices that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice(用来生成d3d对象)
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device（渲染设备）
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices（暂存顶点数据的缓存）

// A structure for our custom vertex type （自定义顶点数据结构）
struct CUSTOMVERTEX
{
    FLOAT x, y, z ,rhw; // The transformed position for the vertex（顶点位置坐标）
    DWORD color;        // The vertex color（顶点颜色）
};

// Our custom FVF, which describes our custom vertex structure （客制fvf）
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)   //d3d 初始化函数
{
    // Create the D3D object.
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the D3DDevice
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()  //初始化顶点缓存
{
    // Initialize three vertices for rendering a triangle
    CUSTOMVERTEX vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
        { 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
        {  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
    };

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if (FAILED(g_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, vertices, sizeof(vertices));
    g_pVB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if (g_pVB != NULL)
        g_pVB->Release();

    if (g_pd3dDevice != NULL)
        g_pd3dDevice->Release();

    if (g_pD3D != NULL)
        g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0),1.0f, 0);

    // Begin the scene
    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
        g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
        g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);  //(指定我们的shader)
        g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
    UNREFERENCED_PARAMETER(hInst);

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx(&wc);

    // Create the application's window(创建应用程序窗口)
    HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
        WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
        NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (SUCCEEDED(InitD3D(hWnd)))
    {
        // Create the vertex buffer
        if (SUCCEEDED(InitVB()))
        {
            // Show the window
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            UpdateWindow(hWnd);

            // Enter the message loop
            MSG msg;
            ZeroMemory(&msg, sizeof(msg));
            while (msg.message != WM_QUIT)
            {
                if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass(L"D3D Tutorial", wc.hInstance);
    return 0;
}
