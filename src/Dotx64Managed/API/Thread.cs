namespace Dotx64Dbg
{
    public class Thread
    {
        public readonly uint Id;

        public bool IsMain { get => Id == Native.Thread.GetMainThreadId(); }

        public bool IsActive { get => Id == Native.Thread.GetActiveThreadId(); }

        public bool IsValid { get => Native.Thread.IsValid(Id); }

        internal Thread(uint internalId)
        {
            Id = internalId;
        }

        public static Thread GetActive()
        {
            return new Thread(Native.Thread.GetActiveThreadId());
        }

        public static Thread GetById(uint id)
        {
            if (!Native.Thread.IsValid(id))
            {
                return null;
            }

            return new Thread(id);
        }

        public static bool SetActive(Thread thread)
        {
            if (thread == null)
                return false;

            return Native.Thread.SetActiveThreadId(thread.Id);
        }

        public static Thread GetMain()
        {
            var mainId = Native.Thread.GetMainThreadId();
            if (mainId == 0)
                return null;

            return new Thread(mainId);
        }

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

        public override string ToString()
        {
            return $"Thread #{Id}";
        }
    }
}
