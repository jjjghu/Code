namespace hw1
{
    partial class 點餐系統
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
            groupBox1 = new GroupBox();
            checkBox4 = new CheckBox();
            checkBox3 = new CheckBox();
            checkBox2 = new CheckBox();
            checkBox1 = new CheckBox();
            groupBox2 = new GroupBox();
            radioButton2 = new RadioButton();
            radioButton1 = new RadioButton();
            checkBox5 = new CheckBox();
            groupBox3 = new GroupBox();
            radioButton5 = new RadioButton();
            radioButton4 = new RadioButton();
            radioButton3 = new RadioButton();
            checkBox6 = new CheckBox();
            label1 = new Label();
            textBox1 = new TextBox();
            button1 = new Button();
            button2 = new Button();
            groupBox1.SuspendLayout();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            SuspendLayout();
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(checkBox4);
            groupBox1.Controls.Add(checkBox3);
            groupBox1.Controls.Add(checkBox2);
            groupBox1.Controls.Add(checkBox1);
            groupBox1.Location = new Point(72, 57);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(151, 209);
            groupBox1.TabIndex = 0;
            groupBox1.TabStop = false;
            groupBox1.Text = "主餐";
            // 
            // checkBox4
            // 
            checkBox4.AutoSize = true;
            checkBox4.Location = new Point(6, 168);
            checkBox4.Name = "checkBox4";
            checkBox4.Size = new Size(92, 23);
            checkBox4.TabIndex = 0;
            checkBox4.Text = "炸雞 $79";
            checkBox4.UseVisualStyleBackColor = true;
            checkBox4.CheckedChanged += checkBox4_CheckedChanged;
            // 
            // checkBox3
            // 
            checkBox3.AutoSize = true;
            checkBox3.Location = new Point(6, 128);
            checkBox3.Name = "checkBox3";
            checkBox3.Size = new Size(107, 23);
            checkBox3.TabIndex = 0;
            checkBox3.Text = "麥香魚 $59";
            checkBox3.UseVisualStyleBackColor = true;
            checkBox3.CheckedChanged += checkBox3_CheckedChanged;
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Location = new Point(6, 84);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(107, 23);
            checkBox2.TabIndex = 0;
            checkBox2.Text = "麥香雞 $49";
            checkBox2.UseVisualStyleBackColor = true;
            checkBox2.CheckedChanged += checkBox2_CheckedChanged;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Location = new Point(6, 38);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(137, 23);
            checkBox1.TabIndex = 0;
            checkBox1.Text = "雙層吉士堡 $69";
            checkBox1.UseVisualStyleBackColor = true;
            checkBox1.CheckedChanged += checkBox1_CheckedChanged;
            // 
            // groupBox2
            // 
            groupBox2.Controls.Add(radioButton2);
            groupBox2.Controls.Add(radioButton1);
            groupBox2.Enabled = false;
            groupBox2.Location = new Point(239, 68);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(161, 96);
            groupBox2.TabIndex = 1;
            groupBox2.TabStop = false;
            // 
            // radioButton2
            // 
            radioButton2.AutoSize = true;
            radioButton2.Location = new Point(6, 55);
            radioButton2.Name = "radioButton2";
            radioButton2.Size = new Size(91, 23);
            radioButton2.TabIndex = 0;
            radioButton2.TabStop = true;
            radioButton2.Text = "小薯 $25";
            radioButton2.UseVisualStyleBackColor = true;
            radioButton2.CheckedChanged += radioButton2_CheckedChanged;
            // 
            // radioButton1
            // 
            radioButton1.AutoSize = true;
            radioButton1.Location = new Point(6, 26);
            radioButton1.Name = "radioButton1";
            radioButton1.Size = new Size(91, 23);
            radioButton1.TabIndex = 0;
            radioButton1.TabStop = true;
            radioButton1.Text = "大薯 $35";
            radioButton1.UseVisualStyleBackColor = true;
            radioButton1.CheckedChanged += radioButton1_CheckedChanged;
            // 
            // checkBox5
            // 
            checkBox5.AutoSize = true;
            checkBox5.Location = new Point(250, 70);
            checkBox5.Name = "checkBox5";
            checkBox5.Size = new Size(61, 23);
            checkBox5.TabIndex = 0;
            checkBox5.Text = "薯條";
            checkBox5.UseVisualStyleBackColor = true;
            checkBox5.CheckedChanged += checkBox5_CheckedChanged;
            // 
            // groupBox3
            // 
            groupBox3.Controls.Add(radioButton5);
            groupBox3.Controls.Add(radioButton4);
            groupBox3.Controls.Add(radioButton3);
            groupBox3.Enabled = false;
            groupBox3.Location = new Point(239, 170);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(161, 137);
            groupBox3.TabIndex = 1;
            groupBox3.TabStop = false;
            // 
            // radioButton5
            // 
            radioButton5.AutoSize = true;
            radioButton5.Location = new Point(6, 84);
            radioButton5.Name = "radioButton5";
            radioButton5.Size = new Size(91, 23);
            radioButton5.TabIndex = 0;
            radioButton5.TabStop = true;
            radioButton5.Text = "咖啡 $45";
            radioButton5.UseVisualStyleBackColor = true;
            radioButton5.CheckedChanged += radioButton5_CheckedChanged;
            // 
            // radioButton4
            // 
            radioButton4.AutoSize = true;
            radioButton4.Location = new Point(6, 55);
            radioButton4.Name = "radioButton4";
            radioButton4.Size = new Size(91, 23);
            radioButton4.TabIndex = 0;
            radioButton4.TabStop = true;
            radioButton4.Text = "紅茶 $25";
            radioButton4.UseVisualStyleBackColor = true;
            radioButton4.CheckedChanged += radioButton4_CheckedChanged;
            // 
            // radioButton3
            // 
            radioButton3.AutoSize = true;
            radioButton3.Location = new Point(6, 26);
            radioButton3.Name = "radioButton3";
            radioButton3.Size = new Size(91, 23);
            radioButton3.TabIndex = 0;
            radioButton3.TabStop = true;
            radioButton3.Text = "可樂 $35";
            radioButton3.UseVisualStyleBackColor = true;
            radioButton3.CheckedChanged += radioButton4_CheckedChanged;
            // 
            // checkBox6
            // 
            checkBox6.AutoSize = true;
            checkBox6.Location = new Point(250, 170);
            checkBox6.Name = "checkBox6";
            checkBox6.Size = new Size(61, 23);
            checkBox6.TabIndex = 0;
            checkBox6.Text = "飲料";
            checkBox6.UseVisualStyleBackColor = true;
            checkBox6.CheckedChanged += checkBox6_CheckedChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(63, 275);
            label1.Name = "label1";
            label1.Size = new Size(39, 19);
            label1.TabIndex = 2;
            label1.Text = "總價";
            label1.Click += label1_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(108, 272);
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.Size = new Size(115, 27);
            textBox1.TabIndex = 1;
            // 
            // button1
            // 
            button1.Location = new Point(108, 328);
            button1.Name = "button1";
            button1.Size = new Size(94, 29);
            button1.TabIndex = 3;
            button1.Text = "回上一步";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(245, 328);
            button2.Name = "button2";
            button2.Size = new Size(94, 29);
            button2.TabIndex = 3;
            button2.Text = "結束";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // 點餐系統
            // 
            AutoScaleDimensions = new SizeF(9F, 19F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(477, 473);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Controls.Add(checkBox6);
            Controls.Add(checkBox5);
            Controls.Add(groupBox3);
            Controls.Add(groupBox2);
            Controls.Add(groupBox1);
            Name = "點餐系統";
            Text = "點餐系統";
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            groupBox3.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private GroupBox groupBox1;
        private CheckBox checkBox4;
        private CheckBox checkBox3;
        private CheckBox checkBox2;
        private CheckBox checkBox1;
        private GroupBox groupBox2;
        private CheckBox checkBox5;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private GroupBox groupBox3;
        private RadioButton radioButton4;
        private RadioButton radioButton3;
        private CheckBox checkBox6;
        private Label label1;
        private TextBox textBox1;
        private Button button1;
        private Button button2;
        private RadioButton radioButton5;
    }
}