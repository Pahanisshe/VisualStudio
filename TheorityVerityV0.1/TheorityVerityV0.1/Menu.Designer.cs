
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
            this.SuspendLayout();
            // 
            // makeTest
            // 
            this.makeTest.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F);
            this.makeTest.Location = new System.Drawing.Point(12, 33);
            this.makeTest.Name = "makeTest";
            this.makeTest.Size = new System.Drawing.Size(190, 134);
            this.makeTest.TabIndex = 0;
            this.makeTest.Text = "Сделайте мне Тест, пожалуйста";
            this.makeTest.UseVisualStyleBackColor = true;
            this.makeTest.Click += new System.EventHandler(this.makeTest_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(73, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Hi, nekochan!";
            // 
            // Menu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(218, 179);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.makeTest);
            this.MaximumSize = new System.Drawing.Size(234, 218);
            this.MinimumSize = new System.Drawing.Size(234, 218);
            this.Name = "Menu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Menu";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button makeTest;
        private System.Windows.Forms.Label label1;
    }
}

