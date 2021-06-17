using System;
using Dotx64Dbg;
using static Dotx64Dbg.Scripting;

Dotx64Dbg.UI.UpdatesEnabled = false;

for(int i = 0; i < 100; i++)
{
	Sti();
	Print($"{Rip:X}");
	Sti();
	Print($"{Rip:X}");
	Sti();
	Print($"{Rip:X}");
}

Dotx64Dbg.UI.UpdatesEnabled = true;
Dotx64Dbg.UI.Update();