#pragma once
//! this file contains only bhop script.
//! including only 'modules.h' is recommended
#include <cstddef>
#include <windows.h>
#include "offsets.hpp"
#include "memory.h"

constexpr std::ptrdiff_t localplayer = hazedumper::signatures::dwLocalPlayer;
constexpr std::ptrdiff_t flags = hazedumper::netvars::m_fFlags;
constexpr std::ptrdiff_t forcejump = hazedumper::signatures::dwForceJump;

inline void bhop(const Memory& csgo, const std::uintptr_t& client) {

	std::uintptr_t player = csgo.read(client + localplayer);
	std::uintptr_t playerflags = csgo.read(player + flags);
	
	if (!player) {
		return;
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		if (playerflags & (1 << 0)) {
			csgo.write(client + forcejump, 6);
		} else {
			csgo.write(client + forcejump, 4);
		}
	}
}
