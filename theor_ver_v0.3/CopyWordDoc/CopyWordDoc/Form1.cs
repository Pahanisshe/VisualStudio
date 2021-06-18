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

namespace CopyWordDoc
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            word.Document document = null;
            try
            {
                var app = new word.Application();
                //ClearMemory form1 = new ClearMemory();
                //form1.Show();

                document = app.Documents.Add();
                document.Application.Selection.PageSetup.LeftMargin = 20F;    // левое поле
                document.Application.Selection.PageSetup.RightMargin = 20F;   // правое поле
                document.Application.Selection.PageSetup.TopMargin = 20F;     // верхнее поле
                document.Application.Selection.PageSetup.BottomMargin = 20F;  // нижнее поле 
                                                                              // ориентация страницы
                                                                              //document.Application.Selection.PageSetup.Orientation = Microsoft.Office.Interop.Word.WdOrientation.wdOrientLandscape; // альбомная
                                                                              // добавляем второй столбец
                                                                              //document.Application.Selection.PageSetup.TextColumns.Add();
                app.Visible = true;
                
                // открываем док с заданиями
                //object file = System.IO.Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName) + "\\0.docx";
                //var wordDoc1 = app.Documents.Open(ref file);


                //word.Paragraph wordParag = document.Paragraphs.Add(Type.Missing);
                // добавляем параграф из 0 документа в новый наш
                //wordParag.Range.Font.Name = "Times New Roman";
                //wordParag.Range.Font.Size = 13;
                //wordParag.Range.Font.Bold = 0;
                //MessageBox.Show("Paragraphs: " + wordDoc1.Paragraphs.Count.ToString() + "\nTables: " + wordDoc1.Tables.Count.ToString());

                word.Paragraph wordParag = document.Paragraphs.Add(Type.Missing);

                int[] puk = { 2, 3 };
                List<int> needTable = new List<int>(puk);

                //MessageBox.Show("LIST - " + needTable[0].ToString() + needTable[1].ToString());

                for(int i = 0; i < 3; i++)
                {
                    int counter = 1;    // счетчик параграфов
                    Random rnd = new Random();
                    int numTask = rnd.Next(5) + 1;  // номер задания
                    //MessageBox.Show($"num task - {numTask}");
                    // открываем док с заданиями
                    object file = System.IO.Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName) + "\\" + i + ".docx";
                    var wordDoc1 = app.Documents.Open(ref file);

                    //List<word.Paragraph> question = new List<word.Paragraph>();
                    word.Paragraph tempP;

                    int curNumTask = 1; // счетчик прохода заданий
                    while (curNumTask < numTask)
                    {
                        do
                        {
                            tempP = wordDoc1.Paragraphs[counter];
                            counter++;
                        } while (!tempP.Range.Text.Contains("#"));
                        curNumTask++;
                    }

                    
                    tempP = wordDoc1.Paragraphs[counter];
                    while (!tempP.Range.Text.Contains("#"))
                    {
                        tempP.Range.Copy();
                        wordParag.Range.Paste();
                        counter++;
                        tempP = wordDoc1.Paragraphs[counter];
                    }
                    wordDoc1.Close();

                    if (needTable.Contains(i + 1))
                    {
                        MessageBox.Show("ГЛУБОКО АХ !!!");
                        object file1 = System.IO.Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName) + "\\" + i + "_tables.docx";
                        var wordDoc2 = app.Documents.Open(ref file1);
                        MessageBox.Show($"{numTask}");
                        wordDoc2.Tables[numTask].Range.Copy();
                        wordParag.Range.Paste();
                        wordDoc2.Close();
                    }

                    wordParag.Range.Text += "";
                    
                }

                /*
                wordDoc1.Paragraphs[1].Range.Copy();
                wordParag.Range.Paste();
                */
                


                //wordParag.Range.Paragraphs.Alignment = Microsoft.Office.Interop.Word.WdParagraphAlignment.wdAlignParagraphCenter;


                // СОХРАНЕНИЕ ФАЙЛА С ТЕСТОМ
                Object fileName = System.IO.Path.GetDirectoryName(System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName) +
                    "\\тест_вариантов.doc";
                saveDoc(document, fileName);

            }
            catch (Exception Ex)
            {
                //document.Close();
                document = null;
                Console.WriteLine("Во время выполнения произошла ошибка!");
                Console.ReadLine();
            }
        }

        private word.Paragraph getParag (word.Document document, int num)
        {
            return document.Paragraphs[num];
        }

        private void saveDoc(word.Document document, Object fileName)
        {
            //Подготавливаем параметры для сохранения документа
            Object fileFormat = word.WdSaveFormat.wdFormatDocument;
            Object lockComments = false;
            Object password = "";
            Object addToRecentFiles = false;
            Object writePassword = "";
            Object readOnlyRecommended = false;
            Object embedTrueTypeFonts = false;
            Object saveNativePictureFormat = false;
            Object saveFormsData = false;
            Object saveAsAOCELetter = Type.Missing;
            Object encoding = Type.Missing;
            Object insertLineBreaks = Type.Missing;
            Object allowSubstitutions = Type.Missing;
            Object lineEnding = Type.Missing;
            Object addBiDiMarks = Type.Missing;
            document.SaveAs(ref fileName, ref fileFormat, ref lockComments, ref password, ref addToRecentFiles, ref writePassword,
                            ref readOnlyRecommended, ref embedTrueTypeFonts, ref saveNativePictureFormat, ref saveFormsData,
                            ref saveAsAOCELetter, ref encoding, ref insertLineBreaks, ref allowSubstitutions, ref lineEnding, ref addBiDiMarks);
        }
    }
}
