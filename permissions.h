#pragma once

enum Permissions
{
	none = 0,
	attack = 1 << 0,  // Може атакувати
	defence = 1 << 1,  // Може захищатися
	take = 1 << 2,  // Може взяти
	toss = 1 << 3,  // Може підкинути
	discard = 1 << 4  // Можливий відбій
};
