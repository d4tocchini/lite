#include "./api.h"
// #include "renderer.h"
// #include "rencache.h"

// int font_idx = 0;

static int f_load(lua_State *L) {
  const char *filename  = luaL_checkstring(L, 1);
  float fontsize = luaL_checknumber(L, 2);
  int **self = lua_newuserdata(L, sizeof(*self));
  luaL_setmetatable(L, API_TYPE_FONT);

  int id = ren_install_font(filename, filename);
  *self = id;

  // int l = strlen(filename);
  // *self = malloc(l);
  // memcpy(*self, filename, l+1);

  // *self = ren_load_font(filename, fontsize);
  // if (!*self) {
  if (*self < 0) {
      luaL_error(L, "failed to load font");
  }

  return 1;
}


static int f_set_tab_width(lua_State *L) {
  // RenFont **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  void **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  int n = luaL_checknumber(L, 2);
  // ren_set_font_tab_width(*self, n);
  return 0;
}


static int f_gc(lua_State *L) {
  // RenFont **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  void **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  if (*self) {
        // rencache_free_font(*self);
  }
  return 0;
}


static int f_get_width(lua_State *L) {
  // RenFont **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  void **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  const char *text = luaL_checkstring(L, 2);

  // TODO: use font & (int or float?)
  vg_t* vg = ctx.vg;
  nvgFontFaceId(vg, *self);
  // printf("font=%i\n",*self);
  lua_pushnumber(L,
      ren_get_text_width(text, -1)
      // ren_get_font_width(*self, text)
  );
  return 1;
}


static int f_get_height(lua_State *L) {
  // RenFont **self = luaL_checkudata(L, 1, API_TYPE_FONT);
  void **self = luaL_checkudata(L, 1, API_TYPE_FONT);

  // TODO: use font & (int or float?)
  vg_t* vg = ctx.vg;
  nvgFontFaceId(vg, *self);
  lua_pushnumber(L,
      ren_get_text_height() // * 1.1
      // ren_get_font_height(*self)
  );
  return 1;
}


static const luaL_Reg ren_font_lib[] = {
  { "__gc",          f_gc            },
  { "load",          f_load          },
  { "set_tab_width", f_set_tab_width },
  { "get_width",     f_get_width     },
  { "get_height",    f_get_height    },
  { NULL, NULL }
};

int luaopen_renderer_font(lua_State *L) {
  luaL_newmetatable(L, API_TYPE_FONT);
  luaL_setfuncs(L, ren_font_lib, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  return 1;
}
