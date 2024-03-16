import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

public class S1154041
{
    public static void main(String args[])
    {
        JFrame frm = new JFrame("個人資料登入");
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frm.setLayout(new BoxLayout(frm.getContentPane(), BoxLayout.Y_AXIS));
        FlowLayout left = new FlowLayout(FlowLayout.LEFT, 30, 0);
        FlowLayout center = new FlowLayout(FlowLayout.CENTER);
        Font font = new Font("Micorsoft YaHei", Font.PLAIN, 18);

        JPanel titlePanel = new JPanel();
        titlePanel.setLayout(center);
        JLabel title = new JLabel("學生個人基本資料");
        title.setFont(font);
        titlePanel.add(title);

        JPanel profilePanel = new JPanel(new GridLayout(2, 2, 10, 10));
        JPanel SchoolNum = new JPanel(left), Name = new JPanel(left);
        JTextField schoolNum = new JTextField(10), name = new JTextField(10);
        SchoolNum.add(new JLabel("學號:"));
        SchoolNum.add(schoolNum);
        Name.add(new JLabel("姓名:"));
        Name.add(name);

        JPanel Gender = new JPanel(left), Address = new JPanel(left);
        Gender.add(new JLabel("性別:"));
        ButtonGroup gender = new ButtonGroup();
        JRadioButton male = new JRadioButton("男生");
        JRadioButton female = new JRadioButton("女生");
        gender.add(male);
        gender.add(female);
        Gender.add(male);
        Gender.add(female);
        Address.add(new JLabel("地址"));
        String addressList[] = {"臺北市", "新北市", "桃園市", "臺中市", "臺南市", "高雄市", "新竹縣", "苗栗縣", "彰化縣", "南投縣", "雲林縣", "嘉義縣",
                "屏東縣", "宜蘭縣", "花蓮縣", "臺東縣", "澎湖縣", "金門縣", "連江縣", "基隆市", "新竹市", "嘉義市"};
        JComboBox<String> address = new JComboBox<>(addressList);
        Address.add(address);
        profilePanel.add(SchoolNum);
        profilePanel.add(Name);
        profilePanel.add(Gender);
        profilePanel.add(Address);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        JButton save = new JButton("新增存檔"), show = new JButton("顯示檔案內容");
        buttonPanel.add(save);
        buttonPanel.add(show);

        JTextArea text = new JTextArea(10, 10);
        JScrollPane scrollPane = new JScrollPane(text);

        save.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String schoolNumber = schoolNum.getText();
                String studentName = name.getText();
                String gen = male.isSelected() ? "男生" : "女生";
                String addr = (String) address.getSelectedItem();
                String output = schoolNumber + "," + studentName + "," + gen + "," + addr + "\n";
                try{
                    BufferedWriter bfw = new BufferedWriter(new FileWriter("output.txt", true));
                    bfw.write(output);
                    bfw.close();
                }
                catch (IOException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
        show.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                StringBuilder content = new StringBuilder();
                try (BufferedReader bfr = new BufferedReader(new FileReader("output.txt")))
                {
                    String line;
                    while ((line = bfr.readLine()) != null)
                    {
                        content.append(line).append("\n");
                    }
                }
                catch (IOException ex)
                {
                    ex.printStackTrace();
                }
                text.setText(content.toString());
            }
        });
        frm.add(titlePanel);
        frm.add(profilePanel);
        frm.add(buttonPanel);
        frm.add(scrollPane);
        frm.pack();
        // frm.setMinimumSize(new Dimension(400,800));
        frm.setVisible(true);
    }
}
/*
 * javac -encoding UTF-8 S1154041.java
 * java -Dfile.encoding=UTF-8 S1154041
 */