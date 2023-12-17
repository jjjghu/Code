import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;
public class S1154041
{
    public static void main(String args[])
    {
        JFrame frm = new JFrame("個人資料登入"); // 視窗標題
        FlowLayout left = new FlowLayout(FlowLayout.LEFT); // 靠左
        FlowLayout center = new FlowLayout(FlowLayout.CENTER);

        frm.setLayout(new GridLayout(7,1)); // 設定Layout
        //frm.setLayout(new BoxLayout(frm.getContentPane(), BoxLayout.Y_AXIS));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 關閉按鈕

        // 各自的面板, 由上到下擺放
        JPanel titlePanel = new JPanel(center);
        JPanel namePanel = new JPanel(left);
        JPanel genderPanel = new JPanel(left);
        JPanel majorPanel = new JPanel(left);
        JPanel interestPanel = new JPanel(left);
        JPanel selfIntroducePanel = new JPanel(new GridLayout(2,1));
        JPanel submitPanel = new JPanel(center);

        // 標題
        titlePanel.add(new JLabel("學生個人基本資料"));

        // 姓名: 文字輸入框
        JTextField nameText = new JTextField(10);
        namePanel.add(new JLabel("姓名:"));
        namePanel.add(nameText);

        // 性別: 只能擇一選項的按鈕物件
        JRadioButton male = new JRadioButton("男生");
        JRadioButton female = new JRadioButton("女生");
        ButtonGroup group = new ButtonGroup(); // 建立成ButtonGroup之後就只能選擇其一
        group.add(male);
        group.add(female);

        genderPanel.add(new JLabel("性別:"));
        genderPanel.add(male);
        genderPanel.add(female);

        // 系所: 下拉選單
        String choices[] = {"資訊工程學系", "國文系", "英文系", "其他"};
        JComboBox<String> comboBox = new JComboBox<>(choices); 

        majorPanel.add(new JLabel("系所:"));
        majorPanel.add(comboBox);

        // 興趣: 可多選的勾選框
        JCheckBox basketball = new JCheckBox("打籃球");
        JCheckBox swimming = new JCheckBox("游泳");
        JCheckBox others = new JCheckBox("其他");
        interestPanel.add(new JLabel("興趣:"));
        interestPanel.add(basketball);
        interestPanel.add(swimming);
        interestPanel.add(others);

        //自我介紹
        selfIntroducePanel.add(new JLabel("自我介紹"));
        JTextArea textArea = new JTextArea(1,20); // 文字的行列
        textArea.setLineWrap(true); //打太多會換行
        textArea.setWrapStyleWord(true); // 不會切到文字
        selfIntroducePanel.add(new JScrollPane(textArea));

        // 存檔按鈕        
        JButton save = new JButton("存檔");
        save.addActionListener
        (
            new ActionListener()
            {
                public void actionPerformed(ActionEvent e)
                {
                    // 獲取姓名
                    String output = nameText.getText() + ", ";
                    output += male.isSelected()?"男生, ":"女生, ";
                    output += comboBox.getSelectedItem().toString() + ", ";
                    if(basketball.isSelected()) output += "打籃球";
                    if(swimming.isSelected()) output += "游泳";
                    if(others.isSelected()) output += "其他";
                    output += ", ";
                    output += textArea.getText();
                    try
                    {
                        //FileWriter fw = new FileWriter("output.txt");
                        BufferedWriter bfw = new BufferedWriter(new FileWriter("output.txt"));
                        bfw.write(output);
                        bfw.newLine();
                        bfw.close();
                    }
                    catch(IOException ex)
                    {
                        System.out.println("NO!");
                    }
                }
            }
        );
        submitPanel.add(save);

        frm.add(titlePanel);
        frm.add(namePanel);
        frm.add(genderPanel);
        frm.add(majorPanel);
        frm.add(interestPanel);
        frm.add(selfIntroducePanel);
        frm.add(submitPanel); // 加入各個視窗
        frm.pack(); // 自動調整視窗大小
        frm.setMinimumSize(new Dimension(500,500)); // 最小的視窗大小
        frm.setVisible(true); // 顯示畫面
    }   
}