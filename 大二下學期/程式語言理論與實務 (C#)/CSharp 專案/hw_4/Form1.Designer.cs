namespace hw_4
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
            saveFileDialog1 = new SaveFileDialog();
            openFileDialog1 = new OpenFileDialog();
            button1 = new Button();
            label1 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            label2 = new Label();
            textBox3 = new TextBox();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            textBox4 = new TextBox();
            textBox5 = new TextBox();
            textBox6 = new TextBox();
            SuspendLayout();
            // 
            // openFileDialog1
            // 
            openFileDialog1.FileName = "openFileDialog1";
            // 
            // button1
            // 
            button1.Location = new Point(131, 324);
            button1.Name = "button1";
            button1.Size = new Size(261, 43);
            button1.TabIndex = 0;
            button1.Text = "匯入Excel CSV資料";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label1.Location = new Point(131, 277);
            label1.Name = "label1";
            label1.Size = new Size(130, 25);
            label1.TabIndex = 1;
            label1.Text = "配銷站座標X:";
            // 
            // textBox1
            // 
            textBox1.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox1.Location = new Point(267, 269);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(125, 33);
            textBox1.TabIndex = 2;
            // 
            // textBox2
            // 
            textBox2.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox2.Location = new Point(447, 269);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(125, 33);
            textBox2.TabIndex = 2;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label2.Location = new Point(412, 277);
            label2.Name = "label2";
            label2.Size = new Size(29, 25);
            label2.TabIndex = 1;
            label2.Text = "Y:";
            // 
            // textBox3
            // 
            textBox3.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox3.Location = new Point(443, 328);
            textBox3.Name = "textBox3";
            textBox3.ReadOnly = true;
            textBox3.Size = new Size(51, 33);
            textBox3.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label3.Location = new Point(500, 331);
            label3.Name = "label3";
            label3.Size = new Size(72, 25);
            label3.TabIndex = 1;
            label3.Text = "筆資料";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label4.Location = new Point(131, 383);
            label4.Name = "label4";
            label4.Size = new Size(92, 25);
            label4.TabIndex = 1;
            label4.Text = "總需求量";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Microsoft JhengHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label5.Location = new Point(349, 385);
            label5.Name = "label5";
            label5.Size = new Size(92, 25);
            label5.TabIndex = 1;
            label5.Text = "平均距離";
            // 
            // textBox4
            // 
            textBox4.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox4.Location = new Point(229, 380);
            textBox4.Name = "textBox4";
            textBox4.ReadOnly = true;
            textBox4.Size = new Size(100, 33);
            textBox4.TabIndex = 2;
            // 
            // textBox5
            // 
            textBox5.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox5.Location = new Point(447, 380);
            textBox5.Name = "textBox5";
            textBox5.ReadOnly = true;
            textBox5.Size = new Size(172, 33);
            textBox5.TabIndex = 2;
            // 
            // textBox6
            // 
            textBox6.Font = new Font("Microsoft JhengHei UI", 12F);
            textBox6.Location = new Point(131, 22);
            textBox6.Multiline = true;
            textBox6.Name = "textBox6";
            textBox6.ReadOnly = true;
            textBox6.ScrollBars = ScrollBars.Both;
            textBox6.Size = new Size(441, 241);
            textBox6.TabIndex = 2;
            textBox6.WordWrap = false;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(779, 450);
            Controls.Add(textBox2);
            Controls.Add(textBox5);
            Controls.Add(textBox4);
            Controls.Add(textBox3);
            Controls.Add(textBox6);
            Controls.Add(textBox1);
            Controls.Add(label2);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label1);
            Controls.Add(button1);
            Name = "Form1";
            Text = "hw_3";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private SaveFileDialog saveFileDialog1;
        private OpenFileDialog openFileDialog1;
        private Button button1;
        private Label label1;
        private TextBox textBox1;
        private TextBox textBox2;
        private Label label2;
        private TextBox textBox3;
        private Label label3;
        private Label label4;
        private Label label5;
        private TextBox textBox4;
        private TextBox textBox5;
        private TextBox textBox6;
    }
}
