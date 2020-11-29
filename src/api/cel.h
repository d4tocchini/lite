
#ifdef API_COG_H
# define API_COG_H

# include <stdlib.h> // getenv
# include <assert.h>
# include "libtcc.h"

# define cog_t TCCState

static cog_t* cog;
// static int el_count = 0;

void cog_on_error(void *opaque, const char *msg)
{
    fprintf(opaque, "%s\n", msg);
}

static int cog_init()
{
    cog = tcc_new();
    if (!s) {
        fprintf(stderr, "cog:EROOR: Could not create tcc state\n");
        exit(1);
    }

    const char* TCC_FLAGS = getenv("TCC_FLAGS");
    if (!TCC_FLAGS) {
        fprintf(stderr, "cog:EROOR: TCC_FLAGS not in env\n");
        exit(1);
    }
    tcc_set_options(TCC_FLAGS);
    // tcc_set_options(s, "-nostdlib -nostdinc -m64 -Wno-implicit-function-declaration");
    // tcc_set_options(ctx, "  -O2 -pthread -nostdlib -nostdinc -m64 "
    //                     "-I/Applications/Xcoge.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include "
    //                     "-I/usr/local/d4/coge/d4/pkg/c/dep/lemongraph/lib "
    //                     "-I/usr/local/d4/coge/d4/pkg/c/usr/lmdb/include "
    //                 );

    tcc_set_error_func(s, stderr, cog_on_error);
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    return 1;
}

static int f_lib(lua_State* L)
{
    int id = el_count++;
    const char* src = luaL_checkstring(L, 1);

}

static int f_compile(lua_State* L)
{
    int id = el_count++;
    const char* src = luaL_checkstring(L, 2);

}

// draw_comp(type, x, y, w, h)
static int f_call(lua_State* L)
{
    int id = luaL_checknumber(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);
    int w = luaL_checknumber(L, 4);
    int h = luaL_checknumber(L, 5);

}

static const luaL_Reg cog_lib[]
= {
        { "lib", f_lib },
        { "compile", f_compile },
        { "call", f_call }
        { NULL, NULL }
    };

int luaopen_cog(lua_State* L)
{
    luaL_newlib(L, cog_lib);
    return 1;
}


#endif