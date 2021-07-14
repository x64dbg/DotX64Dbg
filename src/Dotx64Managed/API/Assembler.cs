using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public partial class Assembler : IDisposable
    {
        private NodeList Nodes = new();
        public NodeList.Node Cursor { get; set; }

        internal Dotx64Dbg.Encoder Encoder;

        bool disposed = false;

        public class Label
        {
            public int Id { get; internal set; }
            public int Offset { get; internal set; }
            internal NodeList.Node Node { get; set; }

            Label()
            {
                Id = -1;
            }

            internal Label(int id)
            {
                Id = id;
            }


        }

        internal List<Label> Labels = new();

        public class NodeInstr : NodeList.NodeKind<Instruction>
        {
        }

        public class NodeData : NodeList.NodeKind<byte[]>
        {
        }

        public class NodeLabel : NodeList.NodeKind<Label>
        {

        }

        public Assembler()
        {
            Encoder = Dotx64Dbg.Encoder.Create(0);
        }

        public Assembler(nuint baseVA = 0)
        {
            Encoder = Dotx64Dbg.Encoder.Create(baseVA);
        }

        public NodeList.Node Head { get => Nodes.Head; }
        public NodeList.Node Tail { get => Nodes.Tail; }

        public NodeList GetNodes()
        {
            return Nodes;
        }

        public Label CreateLabel()
        {
            var res = new Label(Labels.Count);

            Labels.Add(res);

            return res;
        }

        public Assembler BindLabel(Label label)
        {
            if (label.Node != null)
                throw new Exception("Label is already bound, can not bind twice.");

            var node = new NodeLabel() { Value = label };
            label.Node = node;

            Cursor = Nodes.InsertAfter(Cursor, node);

            return this;
        }


        internal Assembler CreateInstr()
        {
            var node = new NodeInstr() { Value = new Instruction() };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id)
        {
            var node = new NodeInstr() { Value = new Instruction(id) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1, IOperand op2)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1, op2) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        internal Assembler CreateInstr(Mnemonic id, IOperand op0, IOperand op1, IOperand op2, IOperand op3)
        {
            var node = new NodeInstr() { Value = new Instruction(id, op0, op1, op2, op3) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Db(byte val)
        {
            var node = new NodeData() { Value = new byte[] { val } };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dw(ushort val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dw(short val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dd(UInt32 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dd(Int32 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dq(UInt64 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public Assembler Dq(Int64 val)
        {
            var node = new NodeData() { Value = BitConverter.GetBytes(val) };
            Cursor = Nodes.InsertAfter(Cursor, node);
            return this;
        }

        public bool Finalize()
        {
            // Encode everything.
            var node = Head;
            while (node != null)
            {
                if (node is NodeInstr nodeInstr)
                {
                    if (!Encoder.Encode(nodeInstr.Value))
                    {
                        return false;
                    }
                }
                else if (node is NodeLabel nodeLabel)
                {

                }
                node = node.Next;
            }

            return true;

        }

        // Public implementation of Dispose pattern callable by consumers.
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        // Protected implementation of Dispose pattern.
        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;

            if (disposing)
            {
                Encoder = null;
                Nodes = null;
                Labels = null;
            }

            disposed = true;
        }

        public bool RelocateTo(nuint newBaseVA)
        {
            return Encoder.RelocateTo(newBaseVA);
        }

        public byte[] GetData()
        {
            return Encoder.GetData();
        }
    }
}
