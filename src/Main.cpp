#include <SDL.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL_syswm.h>
#include <bx/math.h>

#include <core/ShaderProgram.h>
#include <core/StreamFactory.h>
#include <core/desktop/DesktopStreamFactory.h>

SDL_Window* window = nullptr;
const int WIDTH = 640;
const int HEIGHT = 480;

struct PosColorVertex {
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_abgr;

    static void init() {
        ms_layout
                .begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
                .end();
    };

    static bgfx::VertexLayout ms_layout;
};


bgfx::VertexLayout PosColorVertex::ms_layout;

static PosColorVertex s_cubeVertices[] = {
                {  0.5f,  0.5f, 0.0f, 0xff0000ff },
                {  0.5f, -0.5f, 0.0f, 0xff0000ff },
                { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
                { -0.5f,  0.5f, 0.0f, 0xff00ff00 }};

static const uint16_t s_cubeTriList[] = {
                0,1,3,
                1,2,3};

bgfx::VertexBufferHandle m_vbh;
bgfx::IndexBufferHandle m_ibh;

int main (int argc, char* args[]) {

    // Initialize SDL systems
    if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else {
        //Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if( window == nullptr ) {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }
    }

    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(window, &wmi)) {
        return 1;
    }

    bgfx::PlatformData pd;
    pd.ndt = nullptr;
    pd.nwh = (void*)(uintptr_t)wmi.info.cocoa.window;
    bgfx::setPlatformData(pd);

    bgfx::renderFrame();
    bgfx::init();

    PosColorVertex::init();
    m_vbh = bgfx::createVertexBuffer(
            bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
            PosColorVertex::ms_layout
    );

    m_ibh = bgfx::createIndexBuffer(
            bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
    );

    ShaderProgram shaderProgram(shared_ptr<StreamFactory>(new DesktopStreamFactory("resources")));
    auto programHandle = shaderProgram.loadProgram("v_simple.bin", "f_simple.bin");

    // Reset window
    bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);

    // Enable debug text.
    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    // Set view rectangle for 0th view
    bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));

    // Clear the view rect
    bgfx::setViewClear(0,
                       BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                       0x443355FF, 1.0f, 0);


    // Set empty primitive on screen
    bgfx::touch(0);

    // Poll for events and wait till user closes window
    bool quit = false;
    SDL_Event currentEvent;
    while(!quit) {
        while(SDL_PollEvent(&currentEvent) != 0) {
            if(currentEvent.type == SDL_QUIT) {
                quit = true;
            }

            const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
            const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

            // Set view and projection matrix for view 0.
            float view[16];
            bx::mtxLookAt(view, eye, at);

            float proj[16];
            bx::mtxProj(proj,
                        60.0f,
                        float(WIDTH)/float(HEIGHT),
                        0.1f, 100.0f,
                        bgfx::getCaps()->homogeneousDepth);

            bgfx::setViewTransform(0, view, proj);

            // Set view 0 default viewport.
            bgfx::setViewRect(0, 0, 0,
                              WIDTH,
                              HEIGHT);

            bgfx::touch(0);


            float mtx[16];
            bx::mtxRotateY(mtx, 0.0f);

            // position x,y,z
            mtx[12] = 0.0f;
            mtx[13] = 0.0f;
            mtx[14] = 0.0f;

            // Set model matrix for rendering.
            bgfx::setTransform(mtx);

            // Set vertex and index buffer.
            bgfx::setVertexBuffer(0, m_vbh);
            bgfx::setIndexBuffer(m_ibh);

            // Set render states.
            bgfx::setState(BGFX_STATE_DEFAULT);

            // Submit primitive for rendering to view 0.
            bgfx::submit(0, programHandle);

            bgfx::frame();
        }
    }

    bgfx::shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}