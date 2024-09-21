namespace hw_8
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
            textBox1 = new TextBox();
            button1 = new Button();
            button2 = new Button();
            button3 = new Button();
            button4 = new Button();
            button5 = new Button();
            label1 = new Label();
            label2 = new Label();
            textBox2 = new TextBox();
            SuspendLayout();
            // 
            // textBox1
            // 
            textBox1.Location = new Point(42, 27);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.ScrollBars = ScrollBars.Vertical;
            textBox1.Size = new Size(707, 216);
            textBox1.TabIndex = 0;
            // 
            // button1
            // 
            button1.Font = new Font("Microsoft JhengHei UI", 12F);
            button1.Location = new Point(66, 249);
            button1.Name = "button1";
            button1.Size = new Size(160, 50);
            button1.TabIndex = 1;
            button1.Text = "新增 Picture";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Font = new Font("Microsoft JhengHei UI", 12F);
            button2.Location = new Point(232, 249);
            button2.Name = "button2";
            button2.Size = new Size(160, 50);
            button2.TabIndex = 1;
            button2.Text = "新增 Rectangle";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // button3
            // 
            button3.Font = new Font("Microsoft JhengHei UI", 12F);
            button3.Location = new Point(404, 249);
            button3.Name = "button3";
            button3.Size = new Size(160, 50);
            button3.TabIndex = 1;
            button3.Text = "新增 Triangle";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // button4
            // 
            button4.Font = new Font("Microsoft JhengHei UI", 12F);
            button4.Location = new Point(570, 249);
            button4.Name = "button4";
            button4.Size = new Size(160, 50);
            button4.TabIndex = 1;
            button4.Text = "新增 Circle";
            button4.UseVisualStyleBackColor = true;
            button4.Click += button4_Click;
            // 
            // button5
            // 
            button5.Font = new Font("Microsoft JhengHei UI", 12F);
            button5.Location = new Point(66, 316);
            button5.Name = "button5";
            button5.Size = new Size(160, 50);
            button5.TabIndex = 1;
            button5.Text = "計算總面積";
            button5.UseVisualStyleBackColor = true;
            button5.Click += button5_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label1.Location = new Point(253, 333);
            label1.Name = "label1";
            label1.Size = new Size(72, 25);
            label1.TabIndex = 2;
            label1.Text = "總面積";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label2.Location = new Point(570, 329);
            label2.Name = "label2";
            label2.Size = new Size(92, 25);
            label2.TabIndex = 2;
            label2.Text = "平方公分";
            // 
            // textBox2
            // 
            textBox2.Location = new Point(331, 331);
            textBox2.Name = "textBox2";
            textBox2.ReadOnly = true;
            textBox2.Size = new Size(233, 27);
            textBox2.TabIndex = 0;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(button5);
            Controls.Add(button4);
            Controls.Add(button3);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBox1;
        private Button button1;
        private Button button2;
        private Button button3;
        private Button button4;
        private Button button5;
        private Label label1;
        private Label label2;
        private TextBox textBox2;
    }
}
