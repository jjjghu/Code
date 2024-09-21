namespace hw_12
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            textBox1 = new TextBox();
            button1 = new Button();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            textBox4 = new TextBox();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(142, 81);
            label1.Name = "label1";
            label1.Size = new Size(72, 25);
            label1.TabIndex = 0;
            label1.Text = "請輸入";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(142, 312);
            label2.Name = "label2";
            label2.Size = new Size(52, 25);
            label2.TabIndex = 0;
            label2.Text = "字元";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(217, 312);
            label3.Name = "label3";
            label3.Size = new Size(52, 25);
            label3.TabIndex = 0;
            label3.Text = "次數";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(292, 312);
            label4.Name = "label4";
            label4.Size = new Size(52, 25);
            label4.TabIndex = 0;
            label4.Text = "編碼";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(462, 312);
            label5.Name = "label5";
            label5.Size = new Size(92, 25);
            label5.TabIndex = 0;
            label5.Text = "霍夫曼碼";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(142, 554);
            label6.Name = "label6";
            label6.Size = new Size(72, 25);
            label6.TabIndex = 0;
            label6.Text = "壓縮率";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(245, 76);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.ScrollBars = ScrollBars.Vertical;
            textBox1.Size = new Size(447, 219);
            textBox1.TabIndex = 1;
            // 
            // button1
            // 
            button1.Location = new Point(728, 76);
            button1.Name = "button1";
            button1.Size = new Size(94, 40);
            button1.TabIndex = 2;
            button1.Text = "轉碼";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // textBox2
            // 
            textBox2.Font = new Font("Microsoft JhengHei UI", 9F);
            textBox2.Location = new Point(142, 350);
            textBox2.Multiline = true;
            textBox2.Name = "textBox2";
            textBox2.ReadOnly = true;
            textBox2.ScrollBars = ScrollBars.Vertical;
            textBox2.Size = new Size(290, 147);
            textBox2.TabIndex = 1;
            // 
            // textBox3
            // 
            textBox3.Font = new Font("Microsoft JhengHei UI", 9F);
            textBox3.Location = new Point(462, 350);
            textBox3.Multiline = true;
            textBox3.Name = "textBox3";
            textBox3.ReadOnly = true;
            textBox3.ScrollBars = ScrollBars.Vertical;
            textBox3.Size = new Size(360, 147);
            textBox3.TabIndex = 1;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(245, 551);
            textBox4.Name = "textBox4";
            textBox4.ReadOnly = true;
            textBox4.ScrollBars = ScrollBars.Vertical;
            textBox4.Size = new Size(447, 33);
            textBox4.TabIndex = 1;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(12F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1028, 687);
            Controls.Add(button1);
            Controls.Add(textBox4);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            Margin = new Padding(4);
            Name = "Form1";
            Text = "霍夫曼編碼(Huffman Code)";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private TextBox textBox1;
        private Button button1;
        private TextBox textBox2;
        private TextBox textBox3;
        private TextBox textBox4;
    }
}
