import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class S1154041 {
    public static void main(String args[]) {
        JFrame frm = new JFrame("四則運算");
        frm.setLayout(new GridLayout(4, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FlowLayout flow = new FlowLayout(FlowLayout.CENTER);
        // 設定介面配置
        JPanel nullPanel = new JPanel(flow);
        JPanel titlePanel = new JPanel(flow);
        JPanel calcPanel = new JPanel(flow);
        JPanel resultPanel = new JPanel(flow);
        // 標題
        JLabel title = new JLabel("四則運算");
        title.setFont(new Font("", Font.BOLD, 24));
        titlePanel.add(title);
        // 顯示結果
        JLabel showres = new JLabel("");
        showres.setForeground(Color.BLUE);
        showres.setFont(new Font("", Font.BOLD, 24));
        resultPanel.add(showres);
        // ComboBox, 選擇
        String choices[] = { "+", "-", "*", "/" };
        JComboBox<String> comboBox = new JComboBox<>(choices);
        comboBox.setFont(new Font("", Font.BOLD, 24));
        comboBox.setPreferredSize(new Dimension(50, 50));
        // 兩個數字
        JTextField num1 = new JTextField(2);
        num1.setFont(new Font("", Font.BOLD, 24));
        num1.setPreferredSize(new Dimension(50, 50));

        JTextField num2 = new JTextField(2);
        num2.setFont(new Font("", Font.BOLD, 24));
        num2.setPreferredSize(new Dimension(50, 50));

        // 當兩個數字任一方有改變的的時候就計算
        KeyAdapter Key = new KeyAdapter() {
            public void keyReleased(KeyEvent e) {
                try {
                    String output = num1.getText() + " " + comboBox.getSelectedItem().toString() + " " + num2.getText();
                    double a = Double.parseDouble(num1.getText());
                    double b = Double.parseDouble(num2.getText());
                    String op = comboBox.getSelectedItem().toString();
                    output += " = ";
                    switch (op) {
                        case "+":
                            output += String.format("%.0f", a + b);
                            break;
                        case "-":
                            output += String.format("%.0f", a - b);
                            break;
                        case "*":
                            output += String.format("%.0f", a * b);
                            break;
                        case "/":
                            output += String.format("%.0f", a / b);
                            break;
                    }
                    showres.setText(output);
                } catch (NumberFormatException ex) // 有沒輸入的東西
                {
                    // showres.setText("Invalid!");
                }
            }
        };
        num1.addKeyListener(Key);
        num2.addKeyListener(Key);

        comboBox.addItemListener(
                new ItemListener() {
                    public void itemStateChanged(ItemEvent e) {
                        if (e.getStateChange() == ItemEvent.SELECTED) {
                            try {
                                String output = num1.getText() + " " + comboBox.getSelectedItem().toString() + " "
                                        + num2.getText();
                                double a = Double.parseDouble(num1.getText());
                                double b = Double.parseDouble(num2.getText());
                                String op = comboBox.getSelectedItem().toString();
                                output += " = ";
                                switch (op) {
                                    case "+":
                                        output += String.format("%.0f", a + b);
                                        break;
                                    case "-":
                                        output += String.format("%.0f", a - b);
                                        break;
                                    case "*":
                                        output += String.format("%.0f", a * b);
                                        break;
                                    case "/":
                                        output += String.format("%.0f", a / b);
                                        break;
                                }
                                showres.setText(output);
                            } catch (NumberFormatException ex) // 有沒輸入的東西
                            {
                                // showres.setText("Invalid!");
                            }
                        }
                    }
                });
        calcPanel.add(num1);
        calcPanel.add(comboBox);
        calcPanel.add(num2);

        frm.add(nullPanel);
        frm.add(titlePanel);
        frm.add(calcPanel);
        frm.add(resultPanel);
        frm.pack();
        frm.setMinimumSize(new Dimension(400, 400));
        frm.setVisible(true);
    }
}
/*
 * javac -encoding UTF-8 S1154041.java
 * java -Dfile.encoding=UTF-8 S1154041
 */