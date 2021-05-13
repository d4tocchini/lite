#include <stdio.h>


#ifndef GFX_ENV
    #define GFX_ENV
    #define GFX_MAC
    #define GFX_GL33
    // #define GFX_METAL
#endif

#include "gfx/gfx.h"
// #define REN_MICROUI
#include "gfx/ren.h"

#include "lite/src/api/api.c"


// #include "api/api.h"
// #include "renderer.h"

#ifdef _WIN32
  #include <windows.h>
#elif __linux__
  #include <unistd.h>
#elif __APPLE__
  #include <mach-o/dyld.h>
#endif

SDL_Window *window;

static double get_scale(void) {
  float dpi;
  SDL_GetDisplayDPI(0, NULL, &dpi, NULL);
#if _WIN32
  return dpi / 96.0;
#else
  return 1.0;
#endif
}


static void get_exe_filename(char *buf, int sz) {
#if _WIN32
  int len = GetModuleFileName(NULL, buf, sz - 1);
  buf[len] = '\0';
#elif __linux__
  char path[512];
  sprintf(path, "/proc/%d/exe", getpid());
  int len = readlink(path, buf, sz - 1);
  buf[len] = '\0';
#elif __APPLE__
  unsigned size = sz;
  _NSGetExecutablePath(buf, &size);
#else
  strcpy(buf, "./lite");
#endif
}


static void init_window_icon(void) {
#ifndef _WIN32
  #include "../icon.inl"
  (void) icon_rgba_len; /* unused */
  SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(
    icon_rgba, 64, 64,
    32, 64 * 4,
    0x000000ff,
    0x0000ff00,
    0x00ff0000,
    0xff000000);
  SDL_SetWindowIcon(window, surf);
  SDL_FreeSurface(surf);
#endif
}


int main(int argc, char **argv) {
  // @autoreleasepool {
  gfx_init();

  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);

  // window = gfx_create_win(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN);
  win_set_size(window, dm.w * 0.8, dm.h * 0.8);

  // TODO: ren_init(window);
  // ren_init();

  ren_ctx_t* ctx = ren_init_ctx();
  window = ctx->win;
  // SDL_MaximizeWindow(window);
  // ren_install_font_defaults();

  init_window_icon();

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  api_load_libs(L);

  lua_newtable(L);
  for (int i = 0; i < argc; i++) {
    lua_pushstring(L, argv[i]);
    lua_rawseti(L, -2, i + 1);
  }
  lua_setglobal(L, "ARGS");

  lua_pushstring(L, "1.11");
  lua_setglobal(L, "VERSION");

  lua_pushstring(L, SDL_GetPlatform());
  lua_setglobal(L, "PLATFORM");

  lua_pushnumber(L, get_scale());
  lua_setglobal(L, "SCALE");

  // lua_pushnil(L);
  // lua_setglobal(L, "core");

  char exename[2048];
  get_exe_filename(exename, sizeof(exename));
  lua_pushstring(L, exename);
  lua_setglobal(L, "EXEFILE");


  (void) luaL_dostring(L,
    "local core\n"
    "xpcall(function()\n"
    "  SCALE = tonumber(os.getenv(\"LITE_SCALE\")) or SCALE\n"
    "  PATHSEP = package.config:sub(1, 1)\n"
    "  EXEDIR = EXEFILE:match(\"^(.+)[/\\\\].*$\")\n"
    "  package.path = EXEDIR .. '/data/?.lua;' .. package.path\n"
    "  package.path = EXEDIR .. '/data/?/init.lua;' .. package.path\n"
    "  core = require('core')\n"
    "  core.init()\n"
    // "  core.run()\n"
    "end, function(err)\n"
    "  print('Error: ' .. tostring(err))\n"
    "  print(debug.traceback(nil, 2))\n"
    "  if core and core.on_error then\n"
    "    pcall(core.on_error, err)\n"
    "  end\n"
    "  os.exit(1)\n" // TODO:
    "end)"
  );

  while (true)
  {
    lua_getglobal(L, "update");
  // lua_pcall(L, 0, 0, 0);     /* call with 0 args, 0 results */
    lua_call(L, 0, 0);

    // lua_getglobal(L, "core");
    // lua_getfield(L, -1, "update");
    // lua_pcall(L, 0, 0, 0);     /* call with 0 args, 0 results */
    // lua_remove(L, -2);

  }

  lua_close(L);
  SDL_DestroyWindow(window);
  // }
  return EXIT_SUCCESS;
}
