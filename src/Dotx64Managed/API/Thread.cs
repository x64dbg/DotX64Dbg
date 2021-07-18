namespace Dotx64Dbg
{
    /// <summary>
    /// A thread object that represents a thread in the debugged process.
    /// </summary>
    public partial class Thread
    {
        /// <summary>
        /// The native thread id.
        /// </summary>
        public readonly uint Id;

        /// <summary>
        /// The native thread handle.
        /// </summary>
        public readonly System.UIntPtr Handle;

        /// <summary>
        /// If this is the first thread created in the process this will be true.
        /// </summary>
        public bool IsMain { get => Id == Native.Thread.GetMainThreadId(); }

        /// <summary>
        /// If this is the currently active thread it will return true.
        /// </summary>
        public bool IsActive { get => Id == Native.Thread.GetActiveThreadId(); }

        /// <summary>
        /// The thread object is garbage collected, if the native thread does no longer exist this will return false.
        /// </summary>
        public bool IsValid { get => Handle != System.UIntPtr.Zero && Native.Thread.IsValid(Id); }

        /// <summary>
        /// Quick accessor for GetMain
        /// </summary>
        public static Thread Main { get => GetMain(); }

        /// <summary>
        /// Quick accessor for GetActive
        /// </summary>
        public static Thread Active { get => GetActive(); }

        internal Thread(uint internalId)
        {
            Id = internalId;

            var info = Native.Thread.GetThreadInfo(Id);
            if (info != null)
            {
                Handle = info.Handle;
            }
            else
            {
                Handle = System.UIntPtr.Zero;
            }
        }

        /// <summary>
        /// Gets the currently active thread from the debugger.
        /// </summary>
        public static Thread GetActive()
        {
            var th = new Thread(Native.Thread.GetActiveThreadId());
            if (!th.IsValid)
                return null;

            return th;
        }

        /// <summary>
        /// Get a thread by its native id.
        /// </summary>
        public static Thread GetById(uint id)
        {
            if (!Native.Thread.IsValid(id))
            {
                return null;
            }

            return new Thread(id);
        }

        /// <summary>
        /// Sets the active thread in the debugger.
        /// </summary>
        public static bool SetActive(Thread thread)
        {
            if (thread == null)
                return false;

            return Native.Thread.SetActiveThreadId(thread.Id);
        }

        /// <summary>
        /// Gets the first created thread for the process.
        /// </summary>
        public static Thread GetMain()
        {
            var mainId = Native.Thread.GetMainThreadId();
            if (mainId == 0)
                return null;

            return new Thread(mainId);
        }

        /// <summary>
        /// Returns all active threads from the debugger.
        /// </summary>
        public static Thread[] GetThreads()
        {
            var threadIds = Native.Thread.GetThreads();

            var threads = new Thread[threadIds.Length];
            for (int i = 0; i < threadIds.Length; i++)
            {
                threads[i] = new Thread(threadIds[i]);
            }

            return threads;
        }

        /// <summary>Pretty name</summary>
        public override string ToString()
        {
            return $"Thread #{Id}";
        }
    }
}
