#include "./api.h"

#ifdef GFX_REN
#include "gfx/ren.h"
#else
#include "rencache.h"
#include "renderer.h"
#endif


static ren_color_t _lua_checkcolor(lua_State* L, int idx, int def)
{
    ren_color_t color;
    if (lua_isnoneornil(L, idx)) {
        return (ren_color_t) { def, def, def, 255 };
    }
    lua_rawgeti(L, idx, 1);
    lua_rawgeti(L, idx, 2);
    lua_rawgeti(L, idx, 3);
    lua_rawgeti(L, idx, 4);
    color.r = luaL_checknumber(L, -4);
    color.g = luaL_checknumber(L, -3);
    color.b = luaL_checknumber(L, -2);
    color.a = luaL_optnumber(L, -1, 255);
    lua_pop(L, 4);
    return color;
}

// show_debug
static int f_show_debug(lua_State* L)
{
    luaL_checkany(L, 1);
    // rencache_show_debug(lua_toboolean(L, 1));
    return 0;
}

// w, h = get_size()
static int f_get_size(lua_State* L)
{
    int w, h;
    ren_get_size(&w, &h);
    lua_pushnumber(L, w);
    lua_pushnumber(L, h);
    return 2;
}

// begin_frame()
static int f_begin_frame(lua_State* L)
{
    ren_measure_frame();
    ren_BEGIN();
    // rencache_begin_frame();
    return 0;
}

// end_frame()
static int f_end_frame(lua_State* L)
{
    ren_END();
    ren_present();
    // rencache_end_frame();
    return 0;
}

// set_clip_rect(x, y, w, h)
static int f_set_clip_rect(lua_State* L)
{
    ren_rect_t rect;
    rect.x = luaL_checknumber(L, 1);
    rect.y = luaL_checknumber(L, 2);
    rect.w = luaL_checknumber(L, 3);
    rect.h = luaL_checknumber(L, 4);
    ren_set_clip_rect(rect);
    return 0;
}

// draw_rect(x, y, w, h, color)
static int f_draw_rect(lua_State* L)
{
    ren_rect_t rect;
    rect.x = luaL_checknumber(L, 1);
    rect.y = luaL_checknumber(L, 2);
    rect.w = luaL_checknumber(L, 3);
    rect.h = luaL_checknumber(L, 4);
    ren_color_t color = _lua_checkcolor(L, 5, 255);
    ren_draw_rect(rect, color);
    // RenRect rect;
    // rect.x = luaL_checknumber(L, 1);
    // rect.y = luaL_checknumber(L, 2);
    // rect.width = luaL_checknumber(L, 3);
    // rect.height = luaL_checknumber(L, 4);
    // RenColor color = _lua_checkcolor(L, 5, 255);
    // rencache_draw_rect(rect, color);
    return 0;
}

// draw_text(font, text, x, y, color)
static int f_draw_text(lua_State* L)
{
    // RenFont **font = luaL_checkudata(L, 1, API_TYPE_FONT);
    int** font = luaL_checkudata(L, 1, API_TYPE_FONT);
    const char* text = luaL_checkstring(L, 2);
    int x = luaL_checknumber(L, 3);
    int y = luaL_checknumber(L, 4);
    ren_color_t color = _lua_checkcolor(L, 5, 255);

    // TODO: font...

    // x = rencache_draw_text(*font, text, x, y, color);
    nvgFontFaceId(ctx.vg, (int)*font);
    // printf("font=%s\n",*font);
    ren_draw_text(text, (ren_vec2_t) { x, y }, color);
    x += ren_get_text_width(text, -1);

    lua_pushnumber(L, x);
    return 1;
}

static const luaL_Reg ren_lib[]
= {
        { "show_debug", f_show_debug },
        { "get_size", f_get_size },
        { "begin_frame", f_begin_frame },
        { "end_frame", f_end_frame },
        { "set_clip_rect", f_set_clip_rect },
        { "draw_rect", f_draw_rect },
        { "draw_text", f_draw_text },
        { NULL, NULL }
    };

int luaopen_renderer_font(lua_State* L);

int luaopen_renderer(lua_State* L)
{
    luaL_newlib(L, ren_lib);
    luaopen_renderer_font(L);
    lua_setfield(L, -2, "font");
    return 1;
}
