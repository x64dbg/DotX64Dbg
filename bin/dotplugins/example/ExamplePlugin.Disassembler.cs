using System;
using Dotx64Dbg;

public partial class ExamplePlugin : IPlugin, IHotload
{

    [Command("DisassembleIP", DebugOnly = true)]
    public void DisassembleAtIP(string[] args)
    {
        var decoder = Decoder.Create();
        var ip = Thread.Main.Nip;

        var decodedInstr = decoder.Decode(ip);

        var instrText = $"Instruction {{\n"
            + $"  Text = {decodedInstr},\n"
            + $"  Info = {{\n"
            + $"    Flags Read = {decodedInstr.FlagsRead}\n"
            + $"    Flags Write = {decodedInstr.FlagsWrite}\n"
            + $"    Flags Read = {decodedInstr.FlagsUndefined}\n"
            + $"  }},\n"
            + $"  Operands = {{\n";

        for(int i = 0; i < 4 ;i++)
        {
            var op = decodedInstr.GetOperand(i);
            if (op.Type == OperandType.None)
                break;

            var visibility = decodedInstr.GetOperandVisibility(i);

            instrText += $"    Operand[{i}] = ";
            switch (op.Type)
            {
                case OperandType.Immediate:
                    var imm = op as Operand.OpImm;
                    instrText += $"{{ {visibility}, Imm({imm.Value:X}) }},\n";
                    break;
                case OperandType.Register:
                    var reg = op as Operand.OpReg;
                    instrText += $"{{ {visibility}, Reg({reg}) }},\n";
                    break;
                case OperandType.Memory:
                    var mem = op as Operand.OpMem;
                    instrText += $"{{ {visibility}, Memory {{\n";
                    instrText += $"      Base = {mem.Base},\n";
                    instrText += $"      Index = {mem.Index},\n";
                    instrText += $"      Scale = {mem.Scale}\n";
                    instrText += $"      Disp = {mem.Displacement},\n";
                    instrText += $"   }} }},\n";
                    break;
            }
        }

        instrText += $"  }}\n";
        instrText += $"}}";

        Console.WriteLine(instrText);
    }
}
