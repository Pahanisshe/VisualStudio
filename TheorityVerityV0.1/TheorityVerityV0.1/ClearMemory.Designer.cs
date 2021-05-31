
namespace TheorityVerityV0._1
{
    partial class ClearMemory
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
            this.clearMemoryButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // clearMemoryButton
            // 
            this.clearMemoryButton.Location = new System.Drawing.Point(12, 12);
            this.clearMemoryButton.Name = "clearMemoryButton";
            this.clearMemoryButton.Size = new System.Drawing.Size(209, 57);
            this.clearMemoryButton.TabIndex = 0;
            this.clearMemoryButton.Text = "ClearMemory!";
            this.clearMemoryButton.UseVisualStyleBackColor = true;
            this.clearMemoryButton.Click += new System.EventHandler(this.clearMemoryButton_Click);
            // 
            // ClearMemory
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(233, 81);
            this.Controls.Add(this.clearMemoryButton);
            this.MaximumSize = new System.Drawing.Size(249, 120);
            this.MinimumSize = new System.Drawing.Size(249, 120);
            this.Name = "ClearMemory";
            this.Text = "ClearMemory";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button clearMemoryButton;
    }
}