local common = require "core.common"
local style = {}

style.padding = { x = common.round(14 * SCALE), y = common.round(7 * SCALE) }
style.divider_size = common.round(1 * SCALE)
style.scrollbar_size = common.round(4 * SCALE)
style.caret_width = common.round(2 * SCALE)
style.tab_width = common.round(170 * SCALE)

-- style.font = renderer.font.load(EXEDIR .. "/data/font/font.ttf", 14 * SCALE)
style.font = renderer.font.load(EXEDIR .. "/data/font/InterDisplay-SemiBold.otf", 14 * SCALE)
style.big_font = renderer.font.load(EXEDIR .. "/data/font/font.ttf", 34 * SCALE)
style.icon_font = renderer.font.load(EXEDIR .. "/data/font/icons.ttf", 14 * SCALE)
-- style.code_font = renderer.font.load(EXEDIR .. "/data/font/monospace.ttf", 13.5 * SCALE)
style.code_font = renderer.font.load(EXEDIR .. "/data/font/SF-Mono-Semibold.otf", 13 * SCALE)

style.background = { common.color "#2e2e32" }  -- doc view
style.background2 = { common.color "#252529" } -- left view
style.background3 = { common.color "#252529" } -- popup view
style.text = { common.color "#97979c" }
style.caret = { common.color "#93DDFA" }
style.accent = { common.color "#e1e1e6" }
style.dim = { common.color "#525257" }
style.divider = { common.color "#202024" }
style.selection = { common.color "#48484f" }
style.line_number = { common.color "#525259" }
style.line_number2 = { common.color "#83838f" }
style.line_highlight = { common.color "#343438" }
style.scrollbar = { common.color "#414146" }
style.scrollbar2 = { common.color "#4b4b52" }

style.syntax = {}
style.syntax["normal"] = { common.color "#e1e1e6" }
style.syntax["symbol"] = { common.color "#e1e1e6" }
style.syntax["comment"] = { common.color "#676b6f" }
style.syntax["keyword"] = { common.color "#E58AC9" }
style.syntax["keyword2"] = { common.color "#F77483" }
style.syntax["number"] = { common.color "#FFA94D" }
style.syntax["literal"] = { common.color "#FFA94D" }
style.syntax["string"] = { common.color "#f7c95c" }
style.syntax["operator"] = { common.color "#93DDFA" }
style.syntax["function"] = { common.color "#93DDFA" }

-- style.cel = {}
-- style.cel["view"] = [[
--     bool hits_rect(vec2f pt, vec4f rect) // scrollbar_overlaps_point
--     {

--     }

--     bool on_mousedown()
--     {
--         if (hits_rect(MOUSE, SCROLLBAR_RECT))
--             $$(scrollbar_drag, true);
--     }

--     bool on_mouse_up()
--     {
--         $$(scrollbar_drag, false);
--     }

--     f32 GET_scroll_size()
--     {
--         return SCROLL_SIZE_DEFAULT;
--     }
--     void clamp_scroll()
--     {
--         f32 max = $(scroll_size) - $(size_y);
--         $$(scroll_to_y, clamp($(scroll_to_y), 0, max)));
--     }
--     void update()
--     {
--         clamp_scroll();
--         $$anim(scroll_x, $(scroll_to_x), .3);
--         $$anim(scroll_y, $(scroll_to_y), .3);
--     }
--     void draw_bg()
--     {
--         draw_rect($(rect), $(color))
--     }
--     void draw() {}
--     void draw_scrollbar()
--     {
--         if (SCROLLBAR_HOVER || SCROLLBAR_DRAG)
--             draw_rect(SCROLLBAR_RECT,
--         else
--     }
-- ]]
-- style.cel["img-input"] = [[

--     USE_MOUSE
--     void update()
--     {

--     }
--     void render(int id, int x, int y, int w, int h)
--     {
--         path();
--         fill_rgba(0,192,0,70);
--         rect(10,10,w-20,h-20);
--         fill();
--     }

-- ]]

return style
