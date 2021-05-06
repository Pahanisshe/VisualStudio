
namespace ТеорВер
{
    partial class Test
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.question = new System.Windows.Forms.Label();
            this.answer1 = new System.Windows.Forms.RadioButton();
            this.answer2 = new System.Windows.Forms.RadioButton();
            this.answer3 = new System.Windows.Forms.RadioButton();
            this.answer4 = new System.Windows.Forms.RadioButton();
            this.nextQuestion = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.answer4);
            this.panel1.Controls.Add(this.answer3);
            this.panel1.Controls.Add(this.answer2);
            this.panel1.Controls.Add(this.answer1);
            this.panel1.Controls.Add(this.question);
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(502, 125);
            this.panel1.TabIndex = 0;
            // 
            // question
            // 
            this.question.AutoSize = true;
            this.question.Location = new System.Drawing.Point(14, 16);
            this.question.Name = "question";
            this.question.Size = new System.Drawing.Size(23, 13);
            this.question.TabIndex = 0;
            this.question.Text = "хуй";
            // 
            // answer1
            // 
            this.answer1.AutoSize = true;
            this.answer1.Location = new System.Drawing.Point(17, 45);
            this.answer1.Name = "answer1";
            this.answer1.Size = new System.Drawing.Size(55, 17);
            this.answer1.TabIndex = 1;
            this.answer1.TabStop = true;
            this.answer1.Text = "пенис";
            this.answer1.UseVisualStyleBackColor = true;
            // 
            // answer2
            // 
            this.answer2.AutoSize = true;
            this.answer2.Location = new System.Drawing.Point(17, 81);
            this.answer2.Name = "answer2";
            this.answer2.Size = new System.Drawing.Size(60, 17);
            this.answer2.TabIndex = 2;
            this.answer2.TabStop = true;
            this.answer2.Text = "вагина";
            this.answer2.UseVisualStyleBackColor = true;
            // 
            // answer3
            // 
            this.answer3.AutoSize = true;
            this.answer3.Location = new System.Drawing.Point(252, 45);
            this.answer3.Name = "answer3";
            this.answer3.Size = new System.Drawing.Size(48, 17);
            this.answer3.TabIndex = 3;
            this.answer3.TabStop = true;
            this.answer3.Text = "анус";
            this.answer3.UseVisualStyleBackColor = true;
            // 
            // answer4
            // 
            this.answer4.AutoSize = true;
            this.answer4.Location = new System.Drawing.Point(252, 81);
            this.answer4.Name = "answer4";
            this.answer4.Size = new System.Drawing.Size(66, 17);
            this.answer4.TabIndex = 4;
            this.answer4.TabStop = true;
            this.answer4.Text = "яичница";
            this.answer4.UseVisualStyleBackColor = true;
            // 
            // nextQuestion
            // 
            this.nextQuestion.Location = new System.Drawing.Point(420, 143);
            this.nextQuestion.Name = "nextQuestion";
            this.nextQuestion.Size = new System.Drawing.Size(94, 53);
            this.nextQuestion.TabIndex = 1;
            this.nextQuestion.Text = "Следующий вопрос";
            this.nextQuestion.UseVisualStyleBackColor = true;
            this.nextQuestion.Click += new System.EventHandler(this.nextQuestion_Click);
            // 
            // Test
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(524, 201);
            this.Controls.Add(this.nextQuestion);
            this.Controls.Add(this.panel1);
            this.Name = "Test";
            this.Text = "Тест";
            this.Load += new System.EventHandler(this.Test_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RadioButton answer4;
        private System.Windows.Forms.RadioButton answer3;
        private System.Windows.Forms.RadioButton answer2;
        private System.Windows.Forms.RadioButton answer1;
        private System.Windows.Forms.Label question;
        private System.Windows.Forms.Button nextQuestion;
    }
}