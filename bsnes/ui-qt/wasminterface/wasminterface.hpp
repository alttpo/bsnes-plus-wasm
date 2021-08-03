#pragma once

#include <wasm/host.hpp>

struct WASMInterface {
  const uint16_t *on_frame_present(const uint16_t *data, unsigned pitch, unsigned width, unsigned height, bool interlace);

  struct {
    const uint16_t *data;
    unsigned pitch;
    unsigned width;
    unsigned height;
    bool interlace;
  } frame;

public:
  // link functions:
  void link_module(const std::shared_ptr<WASM::Module>& module);

  // wasm bindings:
#define decl_binding(name) \
  static const char *wasmsig_##name; \
  m3ApiRawFunction(wasm_##name)

  decl_binding(debugger_break);
  decl_binding(debugger_continue);

  decl_binding(msg_recv);
  decl_binding(msg_size);

  decl_binding(snes_bus_read);
  decl_binding(snes_bus_write);

  decl_binding(ppux_reset);
  decl_binding(ppux_sprite_reset);
  decl_binding(ppux_sprite_read);
  decl_binding(ppux_sprite_write);
  decl_binding(ppux_ram_write);
  decl_binding(ppux_ram_read);

  decl_binding(frame_acquire);
  // TODO: frame drawing functions

#undef decl_binding
};

extern WASMInterface wasmInterface;