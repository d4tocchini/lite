local core = require "core"
local command = require "core.command"
local config = require "core.config"
local keymap = require "core.keymap"

local function dv()
  return core.active_view
end


local function doc()
  return core.active_view.doc
end



command.add("core.docview", {

  ["doc:copy-path"] = function()
    local doc = core.active_view.doc
    if not doc.filename then
      core.error "Cannot copy location of unsaved doc"
      return
    end
    local filename = system.absolute_path(doc.filename)
    core.log("Copying to clipboard \"%s\"", filename)
    system.set_clipboard(filename)
  end,

  ["doc:close"] = function()
    command.perform("root:close")
  end,

  ["doc:reveal-in-file-system"] = function()
    local doc = core.active_view.doc
    if not doc.filename then
      core.error "Cannot open location of unsaved doc"
      return
    end
    if PLATFORM == "Mac OS X" then
      local filename = system.absolute_path(doc.filename or ".")
      core.log("Opening \"%s\"", filename)
      system.exec(string.format("osascript -e \"tell application \\\"Finder\\\"\" -e activate -e \"reveal POSIX file \\\"%s\\\"\" -e end tell", filename))
      return
    end
    local folder = doc.filename:match("^(.*)[/\\].*$") or "."
    core.log("Opening \"%s\"", folder)
    if PLATFORM == "Windows" then
      system.exec(string.format("%s %s", "explorer", folder))
    else
      system.exec(string.format("%s %q", "xdg-open", folder))
    end
  end
})

keymap.add { ["ctl+w"] = "doc:close" }
keymap.add { ["cmd+w"] = "doc:close" }
