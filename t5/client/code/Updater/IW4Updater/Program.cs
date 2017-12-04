namespace IW4Updater
{
    using System.Collections.Generic;
    using System.Collections.Specialized;
    using System.Linq;
    using System.Text;
    using System.Text.RegularExpressions;
    using System.IO;
    using System.Net;
    using System.Security.Cryptography;
    using System.Reflection;
    using System.Runtime.InteropServices;
    using System.Web;
    using DBNUpdater;
    using System;
    using System.Diagnostics;
    using System.Runtime.CompilerServices;
    using System.Threading;
    using System.Windows.Forms;

    internal static class Program
    {
        [CompilerGenerated]
        private static bool BackingField;
        private static bool openUpdater = false;
        private static ProgressDialog pdialog;
        private static bool updaterFinished = false;

        private static void _core_Completed(object sender, EventArgs e)
        {
            updaterFinished = true;
            Completed = true;
        }

        private static void _core_Failed(object sender, FailedEventArgs e)
        {
            MessageBox.Show(e.Exception.ToString(), "iw5", MessageBoxButtons.OK, MessageBoxIcon.Hand);
            Completed = true;
            updaterFinished = false;
        }

        private static void _core_StatusChanged(object sender, StatusChangedEventArgs e)
        {
            if (e.StatusText == "Downloading")
            {
                if (pdialog != null)
                {
                    pdialog.Line1 = e.StatusText;
                    pdialog.Line2 = e.DetailedStatus + string.Format(" ({0}%)", Math.Round(e.ExactPercentage, 1));
                    pdialog.Line3 = " ";
                    pdialog.Value = (uint)(e.ExactPercentage * 10.0);
                }
                if (!Completed)
                {
                    openUpdater = true;
                    Completed = true;
                }
            }
        }

        [MTAThread]
        private static void Main()
        {
            File.Delete("cachesSxS.xml");   //here
            Completed = false;
            Core core = new Core();
            core.CacheLocation = Environment.CurrentDirectory;
            core.WebCacheServer = string.Format("http://repziw4.de/content/contentmw3");
            core.LocalCacheServer = "";
            core.WantedCaches = new string[] { "RepZ-IW4" };
            core.EnableUploading = false;
            core.StatusChanged += new EventHandler<StatusChangedEventArgs>(Program._core_StatusChanged);
            core.Failed += new EventHandler<FailedEventArgs>(Program._core_Failed);
            core.Completed += new EventHandler<EventArgs>(Program._core_Completed);
            core.Start();
            DateTime utcNow = DateTime.UtcNow;
            while (!Completed)
            {
                Thread.Sleep(1);
            }
            if (openUpdater)
            {
                Completed = false;
                pdialog = new ProgressDialog(IntPtr.Zero);
                pdialog.Title = "Updating CLIENT";
                pdialog.Maximum = 0x3e8;
                pdialog.ShowDialog(new ProgressDialog.PROGDLG[1]);
            }
            while (!Completed)
            {
                Thread.Sleep(1);
                if ((pdialog != null) && pdialog.HasUserCancelled)
                {
                    core.Kill();
                    return;
                }
            }
            if (updaterFinished)
            {
                Process.Start("iw5m.exe"); //and here
            }
        }

        public static bool Completed
        {
            [CompilerGenerated]
            get
            {
                return BackingField;
            }
            [CompilerGenerated]
            set
            {
                BackingField = value;
            }
        }
    }
}

