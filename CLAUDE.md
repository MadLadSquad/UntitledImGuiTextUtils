# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

UntitledImGuiTextUtils is a small standalone C++/C library of rich-text widgets for [dear imgui](https://github.com/ocornut/imgui): bold/italic/monospace/small typefaces, underline, strikethrough, links, highlight, blockquotes, code blocks, inline code, ruby annotations, and sub/superscripts.

It is consumed as a git submodule — most commonly by [UntitledImGuiFramework](https://github.com/MadLadSquad/UntitledImGuiFramework) as its `text-utils` module (mounted at `Framework/Modules/TextUtils/ThirdParty/UntitledImGuiTextUtils`), but it is designed to drop into any imgui project.

End-user documentation lives on the [wiki](https://github.com/MadLadSquad/UntitledImGuiTextUtils/wiki).

## Building

**This repository has no build system of its own** — no CMakeLists.txt, no tests, no lint config. Consumers glob the sources into their own target. The parent framework does this in `Framework/cmake/SetupSources.cmake` (globs `*.cpp` / `*.hpp` / `*.h` recursively under the module dir), gated on the `text-utils: true` flag in a project's `uvproj.yaml`.

`imgui.h` must be reachable on the include path — `UImGuiTextUtils.hpp` hard-`#error`s otherwise.

To compile-check changes in practice, build a framework project that enables the module:

```bash
cd ../../../../../Projects/UImGuiDemo/build
cmake .. -DCMAKE_BUILD_TYPE=DEBUG && make -j$(nproc)
```

CI (`.github/workflows/release.yaml`) does **not** compile anything — it only tarballs the tree on a `v*` tag push.

## Architecture

### Global state and the plugin handoff

There is exactly one piece of global state: a function-local `static TextUtilsData*` inside `TextUtils::getData()` (`UImGuiTextUtils.cpp:3`). The library never owns or allocates it — the consumer owns a `TextUtilsData` and hands over the pointer via `initTextUtilsData()`.

This indirection exists so the same fonts work across shared-library boundaries: the host application calls `initTextUtilsData(&myData)`, and each plugin DLL — which has its own copy of the static — calls it again with the pointer the host passed through. In the parent framework this is wired at `Framework/Core/Interfaces/PluginInterface.cpp` (`.textUtilsContext = TextUtils::getTextUtilsData()`) and `Framework/Core/Utilities.cpp` (`loadContext` → `initTextUtilsData`).

**Consequence:** every typeface function dereferences `UIMGUI_TEXT_UTILS_DATA` (i.e. `*getData()`) with no null check. Calling any API before `initTextUtilsData`, or with unset `ImFont*` members, is a crash — not a fallback.

### Source layout

Three translation units split by concern, all including the single public header:

- **`UImGuiTextUtils.cpp`** — `Colour` conversions, the data singleton, and `ShowDemoWindow()` (the demo doubles as the usage reference for every widget; keep it updated when adding one).
- **`UImGuiTextUtilsTypefaces.cpp`** — anything that swaps the active `ImFont`: Bold/Italic/BoldItalic/Monospace/Small, plus `Ruby` and `SubSuperscript` which do manual small-font layout.
- **`UImGuiTextUtilsTextMarkdown.cpp`** — decorations drawn *around* text: Underline, Strikethrough, Highlight, Link, Blockquote, CodeBlock/CodeInline, and the shared wrapping engine.

`Common.h` is the shared C/C++ ABI surface (`UImGui_TextUtils_Colour`, `UImGui_TextUtils_WidgetState`, default colour macros, `MLS_PUBLIC_API`) — it must stay valid C. `UImGuiString.hpp` resolves `UImGui::TString`.

### Widget implementation patterns

Two idioms recur; new widgets should follow whichever fits:

1. **Decorate the previous item** — read `ImGui::GetItemRectMin()/Max()` and draw into `GetWindowDrawList()`. This is why `Underline()`, `Strikethrough()`, `Highlight()` take no text: they annotate whatever was just rendered. The templated `Underline(fmt, colour, args...)` style overloads in the header are thin wrappers that call `ImGui::Text` then the bare decorator, returning a `WidgetState` bitmask sampled between the two.
2. **Draw manually + `InvisibleButton`** — compute the rect, `AddRectFilled`/`AddText` into the draw list, then push a same-sized `InvisibleButton` so imgui's cursor advances and hit-testing works. Used by Blockquote, CodeBlock, CodeInline, Ruby, SubSuperscript. Always `PushID` on the text pointer range first, since these all share literal IDs like `##code`.

### `renderWrappedTextGeneric`

Every `*Wrapped` variant funnels through this one private function (`UImGuiTextUtilsTextMarkdown.cpp`). It re-implements word wrapping manually — imgui's built-in wrapping can't be used because each visual line has to be a separate item so the decoration can be applied per-line.

It takes three callbacks: `before(colour)` (e.g. Blockquote draws its bar and `SameLine`s), `render(data, begin, end, colour)` (defaults to `TextUnformatted`; CodeInlineWrapped overrides it to draw monospace-on-background), and `after(colour)` (the decoration). It ORs the per-line hover/click states into a single returned `WidgetState`. Add new wrapped widgets by supplying callbacks here rather than writing another wrap loop.

The `isPartOfWord()` lookahead exists to avoid breaking a word onto a line where it would have fit — it probes the next line's width before committing a break.

### dear imgui version gates

Font and wrapping code is guarded on `IMGUI_VERSION_NUM` for the 1.92 dynamic-font API break:

- `> 19196`: `ImFont::CalcWordWrapPosition(size, ...)` replaces `CalcWordWrapPositionA(scale, ...)`
- `> 19197`: `ImGuiStyle::FontScaleMain` replaces `ImGuiIO::FontGlobalScale`; `ImGui::GetFontSize()` replaces `ImFont::FontSize`

Any new code touching font metrics or wrapping must carry the same pair of gates. Note `ImGui::PushFont(font, size)` is used unconditionally — the pre-1.92 single-argument form is no longer supported (see commit `396391b`).

Small-font sizing is centralised in the `SMALL_FONT_SIZE` macro in `UImGuiTextUtilsTypefaces.cpp`; its derivation is documented in the comment above it. Ruby, sub/superscript and `Small*Wrapped` all depend on it.

### The `Colour` type

`TextUtils::Colour` wraps the C `UImGui_TextUtils_Colour` (a 4-float union) and is layout-compatible with `ImVec4` — conversions are done with `reinterpret_cast`, not field copies. It has implicit constructors from `ImVec4`/`ImU32` and implicit conversion operators back, so it can be passed anywhere imgui expects either. Preserve that layout compatibility when touching it.

Note: the `UIMGUI_COL32` macro in `Common.h` casts integers to the `UImGui_TextUtils_Colour` struct type and shifts them — it will not compile if ever expanded. Nothing uses it; don't reach for it.

## C API

`C/CUImGuiTextUtils.{h,cpp}` mirrors the entire public C++ surface. **Adding, renaming, or changing signature of a public C++ function means updating the C wrapper in the same change.** Mapping conventions:

- `UImGui::TextUtils::Foo` → `UImGui_TextUtils_Foo`
- Templated variadic overloads (`Underline(fmt, colour, args...)`) become `_fmt` / `_fmtV` suffixed pairs with the colour moved to the **first** parameter, since C variadics require the `...` last.
- Default arguments become mandatory explicit parameters; `UIMGUI_C_TEXT_COLOUR` is the C-side stand-in for the `UIMGUI_TEXT_COLOUR` default.
- `std::function` link callbacks become the `UImGui_TextUtils_LinkCallback` function pointer typedef.
- `TextUtilsData` is opaque (`UImGui_CTextUtilsData` = `void`), with `_allocate` / `_setFonts` / `_free`.

## Configuration macros

- `UIMGUI_TEXT_UTILS_DISABLE_STRING` — compiles out every `TString` convenience overload (all guarded by `#ifndef`). Any new `TString` overload must be inside such a guard, in both header and source.
- `UIMGUI_TEXT_UTILS_CUSTOM_STRING` + `UIMGUI_TEXT_UTILS_CUSTOM_STRING_INCLUDE` — substitute a custom string type for `std::string` as `UImGui::TString`. Both must be defined together or `UImGuiString.hpp` `#error`s. The framework uses this to inject its allocator-aware `FString`.
- `MLS_EXPORT_LIBRARY` / `MLS_LIB_COMPILE` — Windows DLL export control behind `MLS_PUBLIC_API`. Any new public class or free function needs the `MLS_PUBLIC_API` annotation.

## Conventions

- Widget entry points are `PascalCase` to match imgui (`Bold`, `CodeInline`); internals and accessors are `camelCase` (`getData`, `renderWrappedTextGeneric`, `isPartOfWord`).
- `V`-suffixed variants take an explicit `va_list`; the `...` versions are macro-generated wrappers (`CUSTOM_FONT_BOILERPLATE` / `CUSTOM_FONT_BOILERPLATE_WRAPPED`). Provide both for any new formatted-text function.
- All public functions are `noexcept`. Boolean parameters and locals are prefixed `b` (`bWrapText`).
- British spelling throughout the API (`Colour`, `colour`).

## graphify

This project has a knowledge graph at graphify-out/ with god nodes, community structure, and cross-file relationships.

Rules:
- For codebase questions, first run `graphify query "<question>"` when graphify-out/graph.json exists. Use `graphify path "<A>" "<B>"` for relationships and `graphify explain "<concept>"` for focused concepts. These return a scoped subgraph, usually much smaller than GRAPH_REPORT.md or raw grep output.
- If graphify-out/wiki/index.md exists, use it for broad navigation instead of raw source browsing.
- Read graphify-out/GRAPH_REPORT.md only for broad architecture review or when query/path/explain do not surface enough context.
- After modifying code, run `graphify update .` to keep the graph current (AST-only, no API cost).
