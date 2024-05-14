namespace hw_8
{
    partial class AddRectangle
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
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            button1 = new Button();
            button2 = new Button();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            textBox4 = new TextBox();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft JhengHei UI", 12F);
            label1.ForeColor = SystemColors.ActiveCaptionText;
            label1.Location = new Point(70, 91);
            label1.Name = "label1";
            label1.Size = new Size(255, 25);
            label1.TabIndex = 0;
            label1.Text = "請輸入新增 Rectangle 名稱";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Microsoft JhengHei UI", 12F);
            label2.Location = new Point(99, 126);
            label2.Name = "label2";
            label2.Size = new Size(226, 25);
            label2.TabIndex = 0;
            label2.Text = "放入那個 Picture 容器中";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Microsoft JhengHei UI", 12F);
            label3.Location = new Point(133, 197);
            label3.Name = "label3";
            label3.Size = new Size(192, 25);
            label3.TabIndex = 0;
            label3.Text = "請輸入長方形的寬度";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Microsoft JhengHei UI", 12F);
            label4.Location = new Point(133, 163);
            label4.Name = "label4";
            label4.Size = new Size(192, 25);
            label4.TabIndex = 0;
            label4.Text = "請輸入長方形的長度";
            // 
            // button1
            // 
            button1.DialogResult = DialogResult.OK;
            button1.Location = new Point(565, 118);
            button1.Name = "button1";
            button1.Size = new Size(61, 33);
            button1.TabIndex = 1;
            button1.Text = "確定";
            button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            button2.DialogResult = DialogResult.Cancel;
            button2.Location = new Point(565, 157);
            button2.Name = "button2";
            button2.Size = new Size(61, 33);
            button2.TabIndex = 1;
            button2.Text = "取消";
            button2.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(331, 89);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(192, 27);
            textBox1.TabIndex = 2;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(331, 124);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(192, 27);
            textBox2.TabIndex = 2;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(331, 157);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(192, 27);
            textBox3.TabIndex = 2;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(331, 195);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(192, 27);
            textBox4.TabIndex = 2;
            // 
            // AddRectangle
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(textBox4);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "AddRectangle";
            Text = "AddRectangle";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Button button1;
        private Button button2;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private TextBox textBox4;
    }
}