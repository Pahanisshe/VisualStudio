using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TheorityVerityV0._1
{
    public partial class ClearMemory : Form
    {
        public ClearMemory()
        {
            InitializeComponent();
        }

        private void clearMemoryButton_Click(object sender, EventArgs e)
        {
            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();
            this.Close();
        }
    }
}
