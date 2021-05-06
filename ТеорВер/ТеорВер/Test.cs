using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace ТеорВер
{
    public partial class Test : Form
    {
        MakeTest makeTest = new MakeTest();
        bool[] result = new bool[16];
        int i = 0, j = 1;

        public Test()
        {
            InitializeComponent();
        }

        private void Test_Load(object sender, EventArgs e)
        {
            StreamReader str = new StreamReader("0.txt");
            for(int k = 0; k < makeTest.Test[0][0] - 1; k++)
            {
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
            }
            question.Text = str.ReadLine();
            answer1.Text = str.ReadLine();
            answer2.Text = str.ReadLine();
            answer3.Text = str.ReadLine();
            answer4.Text = str.ReadLine();
            str.Close();
            if (answer1.Checked)
                result[0] = true;
            else
                result[0] = false;
        }

        private void nextQuestion_Click(object sender, EventArgs e)
        {
            if (i == 7 && j == 1)
            {
                nextQuestion.Text = "Завершить кастинг";
            }
            if (j == 2)
            {
                i++;
                j = 0;
            }
            if (i == 8)
            {

            }
            string name = i.ToString() + ".txt";
            StreamReader str = new StreamReader(name);

            for (int k = 0; k < makeTest.Test[i][j] - 1; k++)
            {
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
                str.ReadLine();
            }
            question.Text = str.ReadLine();
            answer1.Text = str.ReadLine();
            answer2.Text = str.ReadLine();
            answer3.Text = str.ReadLine();
            answer4.Text = str.ReadLine();

            str.Close();
            if (answer1.Checked)
                result[i * 2 + j] = true;
            else
                result[i * 2 + j] = false;

            j++;
        }
    }
}
