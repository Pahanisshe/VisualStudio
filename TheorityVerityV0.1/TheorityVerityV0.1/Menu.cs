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
using word = Microsoft.Office.Interop.Word;
using System.Threading;

namespace TheorityVerityV0._1
{
    public partial class Menu : Form
    {
        public Menu()
        {
            InitializeComponent();
        }

        private void makeTest_Click(object sender, EventArgs e)
        {
            word.Document document = null;
            try
            {
                var app = new word.Application();
                app.Visible = true;
                document = app.Documents.Add();
                
                Microsoft.Office.Interop.Word.Paragraph wordParag;
                // первый параграф
                wordParag = document.Paragraphs.Add(Type.Missing);
                wordParag.Range.Font.Name = "Times New Roman";
                wordParag.Range.Font.Size = 16;
                wordParag.Range.Font.Bold = 1;
                wordParag.Range.Text = "Тест по теории вероятностей";
                wordParag.Range.Paragraphs.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphCenter;

                // Второй параграф
                document.Paragraphs.Add(Type.Missing);
                wordParag.Range.Font.Name = "Times New Roman";
                wordParag.Range.Font.Size = 16;
                wordParag.Range.Font.Bold = 0;
                wordParag.Range.Text = "Вариант";
                wordParag.Range.Paragraphs.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphCenter;

                // Третий параграф
                document.Paragraphs.Add(Type.Missing);
                wordParag.Range.Font.Name = "Times New Roman";
                wordParag.Range.Font.Size = 14;
                wordParag.Range.Font.Bold = 0;
                wordParag.Range.Paragraphs.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphLeft;

                AddTestToFile(wordParag);
                
            }
            catch (Exception Ex)
            {
                document.Close();
                document = null;
                Console.WriteLine("Во время выполнения произошла ошибка!");
                Console.ReadLine();
            }

            // range.Delete();
            GC.Collect();
        }

        private void AddTestToFile(Microsoft.Office.Interop.Word.Paragraph wordParag)
        {
            MakeTest test = new MakeTest();
            
            // int countTasks = 4;
            int countThemes = 2;
            string currentAnswers = "";
            string[] question = new string[4];
            for (int i = 0; i < countThemes; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    question = GetQuestion(i, test.Test[i][j]);
                    currentAnswers += question[5];    // ответ запихнули
                    AddTask(wordParag, question, i * 2 + j + 1);
                }
            }

            wordParag.Range.Text += "\nТРУ ОТВЕТЫ ИНФА СОТКА: " + currentAnswers;
            
        }

        private void AddTask(Microsoft.Office.Interop.Word.Paragraph wordParag, string[] question, int numberTask)
        {
            wordParag.Range.Text += $"({numberTask}) " + question[0];
            for (int i = 1; i < 5; i++)
                wordParag.Range.Text += $"{i}) " + question[i];
            wordParag.Range.Text += "";
        }

        private string[] GetQuestion(int numberFile, int numberQuestion)
        {
            string[] question = new string [6];
            string nameFile = numberFile + ".txt";
            StreamReader fsr = new StreamReader(nameFile);
            for (int i = 1; i < numberQuestion; i++)
                for (int j = 0; j < 7; j++)
                    fsr.ReadLine();
            for (int i = 0; i < 6; i++)
                question[i] = fsr.ReadLine();
            return question;
        }

        
    }

    public class MakeTest
    {
        public List<int>[] Test { get; set; }

        public MakeTest()
        {
            Test = new List<int>[8];
            for (int i = 0; i < 8; i++)
                Test[i] = new List<int>();
            Random rnd = new Random();
            for (int i = 0; i < 8; i++)
            {
                int C = numberOfCiombinations(5, 2);
                int r = rnd.Next(C);
                Combinatorics combObj = new Combinatorics();
                combObj.Object(5, 2, false);

                for (int j = 0; j < r; j++)
                    combObj.NextCombination();

                for (int j = 0; j < 2; j++)
                    Test[i].Add(combObj.CombObject[j]);
            }
            //print();
        }

        public void print()
        {
            StreamWriter str = new StreamWriter("Параша.txt");
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 2; j++)
                    str.Write(this.Test[i][j]);
                str.WriteLine();
            }
            str.Close();
            System.Diagnostics.Process.Start("Параша.txt");
        }

        private int numberOfCiombinations(int n, int k)
        {
            return factorial(n) / (factorial(k) * factorial(n - k));
        }

        private int factorial(int n)
        {
            if (n == 0 || n == 1)
                return 1;
            else
            {
                int f = 1;
                for (int i = 2; i <= n; i++)
                    f *= i;
                return f;
            }
        }
    }

    public class Combinatorics
    {
        private int lengthAlphabet;
        private int lenghtObject;
        private bool repetitions;
        private int[] combObject;
        private string nameObject;

        //создает универсальный комбинаторный объект с повторениями или без
        public void Object(int lengthAlphabet, int lenghtObject, bool repetitions)
        {
            this.lengthAlphabet = lengthAlphabet;
            this.lenghtObject = lenghtObject;
            this.repetitions = repetitions;
            this.combObject = new int[this.lengthAlphabet];
            if (repetitions)
                for (int i = 0; i < this.lengthAlphabet; i++)
                    combObject[i] = 1;
            else
                for (int i = 0; i < this.lengthAlphabet; i++)
                    combObject[i] = i + 1;
        }

        //частный случай
        public void Object(int lengthAlphabet, bool repetitions)
        {
            Object(lengthAlphabet, lengthAlphabet, repetitions);
        }

        //возвращает объект в начальное состояние
        public void Reset()
        {
            if (repetitions)
                for (int i = 0; i < lengthAlphabet; i++)
                    combObject[i] = 1;
            else
                for (int i = 0; i < lengthAlphabet; i++)
                    combObject[i] = i + 1;
        }

        //вывод в файл всех перестановок
        public void Permutations(int lenghtObject)
        {
            this.lengthAlphabet = lenghtObject;
            this.lenghtObject = lenghtObject;
            this.combObject = new int[this.lenghtObject];
            this.nameObject = "Permutations.txt";
            StreamWriter streamWriter = new StreamWriter(nameObject);
            for (int i = 0; i < this.lenghtObject; i++)
                combObject[i] = i + 1;
            Print(streamWriter);
            while (NextPermutation())
                Print(streamWriter);
            streamWriter.Close();
        }

        //вывод в файл всех размещений
        public void Accommodations(int lengthAlphabet, int lenghtObject)
        {
            this.lengthAlphabet = lengthAlphabet;
            this.lenghtObject = lenghtObject;
            this.combObject = new int[this.lengthAlphabet];
            this.nameObject = "Accommodations.txt";
            StreamWriter streamWriter = new StreamWriter(nameObject);
            for (int i = 0; i < this.lengthAlphabet; i++)
                combObject[i] = i + 1;
            Print(streamWriter);
            while (NextAccommodation())
                Print(streamWriter);
            streamWriter.Close();
        }

        //вывод в файл всех сочетаний
        public void Combinations(int lengthAlphabet, int lenghtObject)
        {
            this.lengthAlphabet = lengthAlphabet;
            this.lenghtObject = lenghtObject;
            this.combObject = new int[this.lengthAlphabet];
            this.nameObject = "Combinations.txt";
            StreamWriter streamWriter = new StreamWriter(nameObject);
            for (int i = 0; i < this.lengthAlphabet; i++)
                combObject[i] = i + 1;
            Print(streamWriter);
            while (NextCombination())
                Print(streamWriter);
            streamWriter.Close();
        }

        //построение следующей перестановки по лексикографическому порядку
        public bool NextPermutation()
        {
            int j = lenghtObject - 2;
            while (j != -1 && combObject[j] >= combObject[j + 1]) j--;
            if (j == -1)
                return false;
            int elem = lenghtObject - 1;
            while (combObject[j] >= combObject[elem]) elem--;
            Swap(j, elem);
            int leftElem = j + 1, rightElem = lenghtObject - 1;
            while (leftElem < rightElem)
                Swap(leftElem++, rightElem--);
            return true;
        }

        //построение следующего размещения по лексикографическому порядку
        public bool NextAccommodation()
        {
            int j;
            do
            {
                j = lengthAlphabet - 2;
                while (j != -1 && combObject[j] >= combObject[j + 1]) j--;
                if (j == -1)
                    return false;
                int elem = lengthAlphabet - 1;
                while (combObject[j] >= combObject[elem]) elem--;
                Swap(j, elem);
                int leftElem = j + 1, rightElem = lengthAlphabet - 1;
                while (leftElem < rightElem)
                    Swap(leftElem++, rightElem--);
            } while (j > lenghtObject - 1);
            return true;
        }

        //построение следующего сочетания по лексикографическому порядку
        public bool NextCombination()
        {
            int k = lenghtObject;
            for (int i = k - 1; i >= 0; i--)
                if (combObject[i] < lengthAlphabet - k + i + 1)
                {
                    combObject[i]++;
                    for (int j = i + 1; j < k; j++)
                        combObject[j] = combObject[j - 1] + 1;
                    return true;
                }
            return false;
        }

        private void Swap(int firstElem, int secondElem)
        {
            int elem = combObject[firstElem];
            combObject[firstElem] = combObject[secondElem];
            combObject[secondElem] = elem;
        }

        private void Print(StreamWriter streamWriter)
        {
            for (int i = 0; i < lenghtObject; i++)
                streamWriter.Write($"{combObject[i]}");
            streamWriter.WriteLine();
        }

        public int[] CombObject
        {
            get
            {
                return combObject;
            }
        }
    }
}
