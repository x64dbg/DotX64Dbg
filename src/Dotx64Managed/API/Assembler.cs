using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public partial class Assembler
    {
        private NodeList Nodes = new();
        public NodeList.Node Cursor { get; set; }

        public class NodeInstr : NodeList.NodeKind<Instruction>
        {
        }

        public class NodeData : NodeList.NodeKind<byte[]>
        {
        }

        public NodeList.Node Head { get => Nodes.Head; }
        public NodeList.Node Tail { get => Nodes.Tail; }

        public NodeList GetNodes()
        {
            return Nodes;
        }

        internal Assembler CreateInstr()
        {
            var node = new NodeInstr() { Value = new Instruction() };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id)
        {
            var node = new NodeInstr() { Value = new Instruction(id) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1, IOperand op2)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1, op2) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1, IOperand op2, IOperand op3)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1, op2, op3) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Db(byte val)
        {
            var node = new NodeData() { Value = new byte[] { val } };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dw(ushort val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dw(short val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dd(UInt32 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dd(Int32 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dq(UInt64 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }

        public Assembler Dq(Int64 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.insertAfter(Cursor, node);
            return this;
        }
    }
}
