import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class S1154041 {
    public static void main(String args[]) {
        JFrame frm = new JFrame("按鍵事件處理");
        frm.setLayout(new GridLayout(2, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel typePanel = new JPanel(new BorderLayout());
        JTextArea type = new JTextArea(5, 5);
        JScrollPane scroll = new JScrollPane(type);
        type.setBorder(BorderFactory.createTitledBorder("訊息"));
        typePanel.add(scroll); // scroll 下面有 type

        JPanel resultPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JLabel title = new JLabel("數字總和");
        JLabel result = new JLabel("0");
        resultPanel.add(title);
        resultPanel.add(result);

        type.addKeyListener(new KeyAdapter() // 事件處理
        {
            public void keyReleased(KeyEvent e) // 放開按鍵的時候, 計算總合
            {
                String content = type.getText();
                int num = 0;
                for (int i = 0; i < content.length(); ++i) {
                    if (Character.isDigit(content.charAt(i))) // 判斷是否是數字
                    {
                        num += Character.getNumericValue(content.charAt(i)); // 加入數字
                    }
                }
                result.setText(String.valueOf(num));
            }
        });

        frm.add(typePanel);
        frm.add(resultPanel);
        frm.setMinimumSize(new Dimension(200, 200));
        frm.pack();
        frm.setVisible(true);
    }
}
/*
 * javac -encoding UTF-8 S1154041.java
 * java -Dfile.encoding=UTF-8 S1154041
 */