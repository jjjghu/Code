import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
public class S1154041
{
    public static void main(String args[])
    {
        JFrame frm = new JFrame("BMI身體指數計算");
        frm.setLayout(new GridLayout(5, 1));

        FlowLayout center = new FlowLayout(FlowLayout.CENTER);
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel height = new JPanel(center);
        JPanel weight = new JPanel(center);
        JPanel result = new JPanel(center);
        JPanel checkresult = new JPanel(new FlowLayout(FlowLayout.CENTER));

        // 主要標題
        JLabel title = new JLabel("BMI指數計算");
        title.setHorizontalAlignment(SwingConstants.CENTER);
        
        //身高
        JLabel cm = new JLabel("身高(cm):");
        JTextField textcm = new JTextField(10);
        height.add(cm);
        height.add(textcm);

        //體重
        JLabel kg = new JLabel("體重(kg):"); 
        JTextField textkg = new JTextField(10);
        weight.add(kg);
        weight.add(textkg);
        
        //診斷結果
        JLabel word1 = new JLabel("診斷結果: ");
        JLabel word = new JLabel("");
        result.add(word1);
        result.add(word);

        //看結果按鈕
        JButton button = new JButton("看結果");
        checkresult.add(button);

        //事件處理
        button.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) 
            {
                try
                {
                    double weight = Double.parseDouble(textkg.getText());
                    double height = Double.parseDouble(textcm.getText()) / 100.0; // Convert cm to meters
                    double bmi = weight / (height * height);
                    String bmiString = String.format("%.2f", bmi);
                    if(18.5 < bmi && bmi < 24)
                    {
                        word.setForeground(Color.BLUE);
                    }
                    else word.setForeground(Color.RED);
                    if(bmi < 18.5)
                        word.setText("BMI = " + bmiString + "(體重過輕)");
                    else if (bmi < 24)
                        word.setText("BMI = " + bmiString + "(正常範圍)");
                    else if (bmi < 27)
                        word.setText("BMI = " + bmiString + "(過重)");
                    else if (bmi < 30)
                        word.setText("BMI = " + bmiString + "(輕度肥胖)");
                    else if (bmi < 35)
                        word.setText("BMI = " + bmiString + "(中度肥胖)");
                    else
                        word.setText("BMI = " + bmiString + "(重度肥胖)");
                }
                catch(NumberFormatException ex)
                {
                    word.setText("請輸入數字");
                }
            }
        });


        frm.add(title);
        frm.add(height);
        frm.add(weight);
        frm.add(result);
        frm.add(checkresult);
        frm.pack();
        frm.setMinimumSize(new Dimension(300,300));
        frm.setVisible(true);
    }
}