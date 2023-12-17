<<<<<<< HEAD
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class S1154041 {
    public static void main(String args[]) 
    {
        JFrame frm = new JFrame("四則運算");
        frm.setLayout(new GridLayout(4, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FlowLayout flow = new FlowLayout(FlowLayout.CENTER);

        JPanel nullPanel = new JPanel(flow);
        JPanel titlePanel = new JPanel(flow);
        JPanel calcPanel = new JPanel(flow);
        JPanel resultPanel = new JPanel(flow);

        JLabel title = new JLabel("四則運算");
        title.setFont(new Font("", Font.BOLD, 24));
        titlePanel.add(title);

        JTextField num1 = new JTextField(2);
        num1.setFont(new Font("", Font.BOLD, 24));
        num1.setPreferredSize(new Dimension(50,50));
        
        String choices[] = { "+", "-", "*", "/" };
        JComboBox<String> comboBox = new JComboBox<>(choices);
        comboBox.setFont(new Font("", Font.BOLD, 24));
        comboBox.setPreferredSize(new Dimension(50,50));

        JTextField num2 = new JTextField(2);
        num2.setFont(new Font("", Font.BOLD, 24));
        num2.setPreferredSize(new Dimension(50,50));
        
        JButton res = new JButton("看結果");
        res.setFont(new Font("", Font.BOLD, 18));
        
        calcPanel.add(num1);
        calcPanel.add(comboBox);
        calcPanel.add(num2);
        calcPanel.add(res);
        
        JLabel showres = new JLabel("");
        resultPanel.add(showres);
        showres.setForeground(Color.BLUE);
        showres.setFont(new Font("", Font.BOLD, 24));
        
        res.addActionListener
        (
            new ActionListener()
            {
                public void actionPerformed(ActionEvent e)
                {
                    try
                    {
                        String output = num1.getText() + " " + comboBox.getSelectedItem().toString() + " "+ num2.getText();
                        double a = Double.parseDouble(num1.getText());
                        double b = Double.parseDouble(num2.getText());
                        String op = comboBox.getSelectedItem().toString();
                        output += "=";
                        switch(op)
                        {
                            case "+":
                                output += String.format("%.0f", a+b);
                                break;
                            case "-":
                                output += String.format("%.0f", a-b);
                                 break;
                            case "*":
                                output += String.format("%.0f", a*b);
                                break;
                            case "/":
                                output += String.format("%.0f", a/b);
                                break;
                        }
                        showres.setText(output);
                    }
                    catch(NumberFormatException ex)
                    {
                        showres.setText("Invalid!");
                    }
                }
            }
        );

        frm.add(nullPanel);
        frm.add(titlePanel);
        frm.add(calcPanel);
        frm.pack();
        frm.setMinimumSize(new Dimension(400, 400));
        frm.setVisible(true);
    }
=======
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class S1154041 {
    public static void main(String args[]) 
    {
        JFrame frm = new JFrame("四則運算");
        frm.setLayout(new GridLayout(4, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        FlowLayout flow = new FlowLayout(FlowLayout.CENTER);

        JPanel nullPanel = new JPanel(flow);
        JPanel titlePanel = new JPanel(flow);
        JPanel calcPanel = new JPanel(flow);
        JPanel resultPanel = new JPanel(flow);

        JLabel title = new JLabel("四則運算");
        title.setFont(new Font("", Font.BOLD, 24));
        titlePanel.add(title);

        JTextField num1 = new JTextField(2);
        num1.setFont(new Font("", Font.BOLD, 24));
        num1.setPreferredSize(new Dimension(50,50));
        
        String choices[] = { "+", "-", "*", "/" };
        JComboBox<String> comboBox = new JComboBox<>(choices);
        comboBox.setFont(new Font("", Font.BOLD, 24));
        comboBox.setPreferredSize(new Dimension(50,50));

        JTextField num2 = new JTextField(2);
        num2.setFont(new Font("", Font.BOLD, 24));
        num2.setPreferredSize(new Dimension(50,50));
        
        JButton res = new JButton("看結果");
        res.setFont(new Font("", Font.BOLD, 18));
        
        calcPanel.add(num1);
        calcPanel.add(comboBox);
        calcPanel.add(num2);
        calcPanel.add(res);
        
        JLabel showres = new JLabel("");
        resultPanel.add(showres);
        showres.setForeground(Color.BLUE);
        showres.setFont(new Font("", Font.BOLD, 24));
        
        res.addActionListener
        (
            new ActionListener()
            {
                public void actionPerformed(ActionEvent e)
                {
                    try
                    {
                        String output = num1.getText() + " " + comboBox.getSelectedItem().toString() + " "+ num2.getText();
                        double a = Double.parseDouble(num1.getText());
                        double b = Double.parseDouble(num2.getText());
                        String op = comboBox.getSelectedItem().toString();
                        output += "=";
                        switch(op)
                        {
                            case "+":
                                output += String.format("%.0f", a+b);
                                break;
                            case "-":
                                output += String.format("%.0f", a-b);
                                 break;
                            case "*":
                                output += String.format("%.0f", a*b);
                                break;
                            case "/":
                                output += String.format("%.0f", a/b);
                                break;
                        }
                        showres.setText(output);
                    }
                    catch(NumberFormatException ex)
                    {
                        showres.setText("Invalid!");
                    }
                }
            }
        );

        frm.add(nullPanel);
        frm.add(titlePanel);
        frm.add(calcPanel);
        frm.add(resultPanel);
        frm.pack();
        frm.setMinimumSize(new Dimension(400, 400));
        frm.setVisible(true);
    }
>>>>>>> 81b5d021060ae4656a934c7853dd490d6711f23d
}