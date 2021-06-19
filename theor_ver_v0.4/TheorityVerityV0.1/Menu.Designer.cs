
namespace TheorityVerityV0._1
{
    partial class Menu
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.makeTest = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.countOfVariants = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.makeFileWithAllTasks = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.waitLabel = new System.Windows.Forms.Label();
            this.makeIDR = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.countOfVariants)).BeginInit();
            this.SuspendLayout();
            // 
            // makeTest
            // 
            this.makeTest.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.makeTest.Location = new System.Drawing.Point(230, 22);
            this.makeTest.Name = "makeTest";
            this.makeTest.Size = new System.Drawing.Size(190, 101);
            this.makeTest.TabIndex = 0;
            this.makeTest.Text = "Сделайте мне тесты, пожалуйста";
            this.makeTest.UseVisualStyleBackColor = true;
            this.makeTest.Click += new System.EventHandler(this.makeTest_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.label1.ImageAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.label1.Location = new System.Drawing.Point(51, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 24);
            this.label1.TabIndex = 1;
            this.label1.Text = "Hi, nekochan!";
            // 
            // countOfVariants
            // 
            this.countOfVariants.Location = new System.Drawing.Point(52, 125);
            this.countOfVariants.Name = "countOfVariants";
            this.countOfVariants.Size = new System.Drawing.Size(120, 20);
            this.countOfVariants.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(21, 94);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(189, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "Количество вариантов:";
            // 
            // makeFileWithAllTasks
            // 
            this.makeFileWithAllTasks.Location = new System.Drawing.Point(32, 155);
            this.makeFileWithAllTasks.Name = "makeFileWithAllTasks";
            this.makeFileWithAllTasks.Size = new System.Drawing.Size(162, 23);
            this.makeFileWithAllTasks.TabIndex = 4;
            this.makeFileWithAllTasks.Text = "Сделать все задания теста";
            this.makeFileWithAllTasks.UseVisualStyleBackColor = true;
            this.makeFileWithAllTasks.Click += new System.EventHandler(this.makeFileWithAllTasks_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(323, 159);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(190, 19);
            this.progressBar1.TabIndex = 5;
            this.progressBar1.Visible = false;
            // 
            // waitLabel
            // 
            this.waitLabel.AutoSize = true;
            this.waitLabel.Location = new System.Drawing.Point(352, 143);
            this.waitLabel.Name = "waitLabel";
            this.waitLabel.Size = new System.Drawing.Size(0, 13);
            this.waitLabel.TabIndex = 6;
            // 
            // makeIDR
            // 
            this.makeIDR.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.makeIDR.Location = new System.Drawing.Point(426, 22);
            this.makeIDR.Name = "makeIDR";
            this.makeIDR.Size = new System.Drawing.Size(190, 101);
            this.makeIDR.TabIndex = 7;
            this.makeIDR.Text = "Сделайте мне ИДР, пожалуйста";
            this.makeIDR.UseVisualStyleBackColor = true;
            this.makeIDR.Click += new System.EventHandler(this.makeIDR_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(12, 33);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(208, 51);
            this.label3.TabIndex = 8;
            this.label3.Text = "Пожалуйста, закройте все \r\nWord и txt файлы с заданиями\r\nперед запуском";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Menu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(632, 190);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.makeIDR);
            this.Controls.Add(this.waitLabel);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.makeFileWithAllTasks);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.countOfVariants);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.makeTest);
            this.MaximumSize = new System.Drawing.Size(648, 229);
            this.MinimumSize = new System.Drawing.Size(648, 229);
            this.Name = "Menu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Menu";
            ((System.ComponentModel.ISupportInitialize)(this.countOfVariants)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button makeTest;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown countOfVariants;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button makeFileWithAllTasks;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label waitLabel;
        private System.Windows.Forms.Button makeIDR;
        private System.Windows.Forms.Label label3;
    }
}

