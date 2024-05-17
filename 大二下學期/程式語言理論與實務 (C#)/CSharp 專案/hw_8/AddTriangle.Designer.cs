namespace hw_8
{
    partial class AddTriangle
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
            label4 = new Label();
            textBox4 = new TextBox();
            button1 = new Button();
            button2 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft JhengHei UI", 12F);
            label1.Location = new Point(127, 145);
            label1.Name = "label1";
            label1.Size = new Size(237, 25);
            label1.TabIndex = 0;
            label1.Text = "請輸入新增 Triangle 名稱";
            // 
            // textBox1
            // 
            textBox1.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox1.Location = new Point(370, 142);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(198, 33);
            textBox1.TabIndex = 1;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Microsoft JhengHei UI", 12F);
            label2.Location = new Point(138, 184);
            label2.Name = "label2";
            label2.Size = new Size(226, 25);
            label2.TabIndex = 0;
            label2.Text = "放入哪個 Picture 容器中";
            // 
            // textBox2
            // 
            textBox2.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox2.Location = new Point(370, 181);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(198, 33);
            textBox2.TabIndex = 1;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Microsoft JhengHei UI", 12F);
            label3.Location = new Point(192, 223);
            label3.Name = "label3";
            label3.Size = new Size(172, 25);
            label3.TabIndex = 0;
            label3.Text = "請輸入三角形的底";
            // 
            // textBox3
            // 
            textBox3.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox3.Location = new Point(370, 220);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(198, 33);
            textBox3.TabIndex = 1;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Microsoft JhengHei UI", 12F);
            label4.Location = new Point(192, 262);
            label4.Name = "label4";
            label4.Size = new Size(172, 25);
            label4.TabIndex = 0;
            label4.Text = "請輸入三角形的高";
            // 
            // textBox4
            // 
            textBox4.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox4.Location = new Point(370, 259);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(198, 33);
            textBox4.TabIndex = 1;
            // 
            // button1
            // 
            button1.DialogResult = DialogResult.OK;
            button1.Location = new Point(620, 184);
            button1.Name = "button1";
            button1.Size = new Size(94, 29);
            button1.TabIndex = 2;
            button1.Text = "新增";
            button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            button2.DialogResult = DialogResult.Cancel;
            button2.Location = new Point(620, 219);
            button2.Name = "button2";
            button2.Size = new Size(94, 29);
            button2.TabIndex = 2;
            button2.Text = "取消";
            button2.UseVisualStyleBackColor = true;
            // 
            // AddTriangle
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox4);
            Controls.Add(label4);
            Controls.Add(textBox3);
            Controls.Add(label3);
            Controls.Add(textBox2);
            Controls.Add(label2);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Name = "AddTriangle";
            Text = "AddTriangle";
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
        private Label label4;
        private TextBox textBox4;
        private Button button1;
        private Button button2;
    }
}