//#define STRICT
//#define WIN32_LEAN_AND_MEAN

#include "main.h"

#include "FalloutEngine.h"
#include "Graphics.h"
#include "input.h"
#include "PartyControl.h"

static void __declspec(naked) ResetState() {
 __asm {
  pushad
  xor  eax, eax
  mov  ForcingGraphicsRefresh, eax
  cmp  GraphicsMode, 3
  jbe  end
  call graphics_OnGameLoad
end:
  call PartyControlReset
  popad
  retn
 }
}

static void __declspec(naked) LoadGame_hook() {
 __asm {
  call ResetState
  jmp  LoadSlot_
 }
}

static void __declspec(naked) gnw_main_hook() {
 __asm {
  call ResetState
  jmp  main_menu_loop_
 }
}

static void __declspec(naked) gnw_main_hook1() {
 __asm {
  call ResetState
  jmp  main_game_loop_
 }
}

void LoadGameHookInit() {
 HookCall(0x46EC9C, LoadGame_hook);
 HookCall(0x46F712, LoadGame_hook);
 HookCall(0x472AD7, gnw_main_hook);
 HookCall(0x472B4B, gnw_main_hook1);
}
