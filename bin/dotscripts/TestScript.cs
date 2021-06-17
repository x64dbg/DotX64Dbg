using System;
using Dotx64Dbg;
using static Dotx64Dbg.Scripting;

UI.UpdatesEnabled = false;

for(int i = 0; i < 100; i++)
{
	Sti();
	Print($"{Rip:X}");
	Sti();
	Print($"{Rip:X}");
	Sti();
	Print($"{Rip:X}");
}

UI.UpdatesEnabled = true;