using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Dotx64Dbg
{
    public static partial class Memory
    {
        public class Stream : System.IO.Stream
        {
            public nuint Base { get; init; }

            internal long Size;
            internal long Offset;

            internal Stream(nuint address)
            {
                Base = Memory.GetBase(address);
                Size = (long)Memory.GetSize(address);
                Offset = (long)(address - Base);
            }

            public override bool CanRead => true;

            public override bool CanSeek => true;

            public override bool CanWrite => true;

            public override long Length => (long)Size;

            public override long Position
            {
                get => Offset;
                set
                {
                    Offset = value;
                    if (Offset > Size)
                        Offset = Size;
                    if (Offset < 0)
                        Offset = 0;
                }
            }

            public override void Flush()
            {
                throw new NotSupportedException();
            }

            public override int Read(byte[] buffer, int offset, int count)
            {
                var bytesLeft = Size - Offset;
                var numBytes = (int)Math.Min(bytesLeft, count);

                var data = Native.Memory.Read(Base + (nuint)Offset, numBytes);
                data.CopyTo(buffer, offset);

                Offset += numBytes;

                return numBytes;
            }

            public override long Seek(long offset, SeekOrigin origin)
            {
                throw new NotImplementedException();
            }

            public override void SetLength(long value)
            {
                throw new NotSupportedException();
            }

            public override void Write(byte[] buffer, int offset, int count)
            {
                var bytesLeft = Size - Offset;
                var numBytes = (int)Math.Min(bytesLeft, count);
                numBytes = Math.Min(numBytes, buffer.Length - offset);

                Native.Memory.Write(Base + (nuint)Offset, buffer, offset, numBytes);

                Offset += numBytes;
            }
        }

        public static Stream GetStream(nuint address)
        {
            return new Stream(address);
        }
    }
}
