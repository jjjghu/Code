namespace hw1
{
    partial class 註冊帳號和密碼
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
            textBox1 = new TextBox();
            label2 = new Label();
            textBox2 = new TextBox();
            label3 = new Label();
            textBox3 = new TextBox();
            button1 = new Button();
            button2 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(61, 49);
            label1.Name = "label1";
            label1.Size = new Size(69, 19);
            label1.TabIndex = 0;
            label1.Text = "輸入帳號";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(146, 46);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(125, 27);
            textBox1.TabIndex = 1;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(61, 82);
            label2.Name = "label2";
            label2.Size = new Size(69, 19);
            label2.TabIndex = 0;
            label2.Text = "輸入密碼";
            // 
            // textBox2
            // 
            textBox2.Location = new Point(146, 79);
            textBox2.Name = "textBox2";
            textBox2.PasswordChar = '*';
            textBox2.Size = new Size(125, 27);
            textBox2.TabIndex = 1;
            textBox2.TextChanged += textBox2_TextChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(61, 115);
            label3.Name = "label3";
            label3.Size = new Size(69, 19);
            label3.TabIndex = 0;
            label3.Text = "密碼確認";
            label3.Visible = false;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(146, 112);
            textBox3.Name = "textBox3";
            textBox3.PasswordChar = '*';
            textBox3.Size = new Size(125, 27);
            textBox3.TabIndex = 1;
            textBox3.Visible = false;
            textBox3.TextChanged += textBox3_TextChanged;
            // 
            // button1
            // 
            button1.Enabled = false;
            button1.Location = new Point(61, 154);
            button1.Name = "button1";
            button1.Size = new Size(94, 29);
            button1.TabIndex = 2;
            button1.Text = "下一步";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(177, 154);
            button2.Name = "button2";
            button2.Size = new Size(94, 29);
            button2.TabIndex = 2;
            button2.Text = "結束";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // 註冊帳號和密碼
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(367, 285);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox3);
            Controls.Add(label3);
            Controls.Add(textBox2);
            Controls.Add(label2);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Name = "註冊帳號和密碼";
            Text = "註冊帳號和密碼";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox textBox1;
        private Label label2;
        private TextBox textBox2;
        private Label label3;
        private TextBox textBox3;
        private Button button1;
        private Button button2;
    }
}