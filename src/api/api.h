#ifndef API_H
#define API_H

// #include "lib/lua52/lua.h"
// #include "lib/lua52/lauxlib.h"
// #include "lib/lua52/lualib.h"
#define LUA_COMPAT_5_3
#include "lib/lua54/lua.h"
#include "lib/lua54/lauxlib.h"
#include "lib/lua54/lualib.h"

#define API_TYPE_FONT "Font"

void api_load_libs(lua_State *L);

#endif
