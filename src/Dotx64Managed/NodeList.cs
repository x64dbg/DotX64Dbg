using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public class NodeList
    {
        public abstract class Node
        {
            public Node Prev { get; internal set; }
            public Node Next { get; internal set; }
        }

        public abstract class NodeKind<T> : Node
        {
            public T Value { get; set; }
        }

        public Node Head { get; internal set; }
        public Node Tail { get; internal set; }

        public ulong Count { get; internal set; }

        public Node Prepend(Node node)
        {
            node.Next = Head;
            node.Prev = null;

            if (Head != null)
                Head.Prev = node;
            else
                Tail = node;

            Head = node;
            Count++;
            return Head;
        }

        public Node Apend(Node node)
        {
            node.Next = null;
            if (Tail == null)
            {
                node.Prev = null;
                Head = Tail = node;
            }
            else
            {
                Tail.Next = node;
                node.Prev = Tail;
                Tail = node;
            }

            Count++;
            return node;
        }

        public Node Detach(Node node)
        {
            var pre = node.Prev;
            var post = node.Next;

            if (pre != null)
                pre.Next = post;

            if (post != null)
                post.Prev = pre;

            if (node == Head)
                Head = post;

            if (node == Tail)
                Tail = pre;

            Count--;

            node.Prev = null;
            node.Next = null;

            return pre;
        }

        public Node InsertBefore(Node pos, Node node)
        {
            if (pos == Head || pos == null)
                return Prepend(node);

            var pre = pos.Prev;

            node.Prev = pre;
            node.Next = pos;

            pre.Next = node;
            pos.Prev = node;

            Count++;
            return node;
        }

        public Node InsertAfter(Node pos, Node node)
        {
            if (pos == null)
                return Prepend(node);
            else if (pos == Tail)
                return Apend(node);

            var next = pos.Next;
            pos.Next = node;

            if (next != null)
                next.Prev = node;

            node.Prev = pos;
            node.Next = next;

            Count++;
            return node;
        }

    }
}
