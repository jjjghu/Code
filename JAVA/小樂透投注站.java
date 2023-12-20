import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.Border;
public class S1154041
{
    private static void createNewWindow(String message) // 開新視窗
    {
        JFrame NewFrame = new JFrame("訊息"); // 新介面的標題
        NewFrame.setLayout(new GridLayout(3, 1));
        
        JPanel mesPanel = new JPanel(new FlowLayout(FlowLayout.CENTER)); // 訊息
        JPanel confirmPanel = new JPanel(new FlowLayout(FlowLayout.CENTER)); // 確認按鈕
        
        JLabel mes = new JLabel(message); // 訊息
        JButton confirm = new JButton("確認"); // 確認按鍵
        mes.setFont(new Font("Microsoft YaHei", Font.PLAIN, 18)); // 設定字體
        confirm.setFont(new Font("Microsoft YaHei", Font.PLAIN, 18));
        confirm.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e) // 觸發事件的時候 ( 按下按鍵 )
            {
                NewFrame.dispose();// 關閉彈出的視窗
            }
        });
        mesPanel.add(mes);
        confirmPanel.add(confirm);
        
        NewFrame.add(new JPanel()); // 空的介面
        NewFrame.add(mesPanel);
        NewFrame.add(confirmPanel);
        
        NewFrame.pack(); // 自適應視窗大小
        NewFrame.setMinimumSize(new Dimension(300,200)); // 視窗最小數值
        NewFrame.setVisible(true); // 顯示視窗
    }
    public static void main(String args[])
    {
        JFrame frm = new JFrame("小樂透投資站"); // 標題
        frm.setLayout(new GridLayout(5, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 關閉按鈕
        FlowLayout left = new FlowLayout(FlowLayout.LEFT, 30, 5); // 介面之間的距離設定為 30 5 (左右 / 上下)
        FlowLayout center = new FlowLayout(FlowLayout.CENTER); // 置中
        Font font = new Font("Microsoft YaHei", Font.PLAIN, 18); // 字體設定 (字形 / 細體 / 大小)
        
        JPanel titlePanel = new JPanel(center); // 介面設定
        JPanel firstPanel = new JPanel(left);
        JPanel secondPanel = new JPanel(left);
        JPanel resultPanel = new JPanel(left);
        JPanel showPanel = new JPanel(center);


        JLabel title = new JLabel("小樂透投資站"); // 標題
        title.setFont(font);
        titlePanel.add(title);

        JLabel firstTitle = new JLabel("第一注: "); // 第一個下注
        firstTitle.setFont(font);
        firstPanel.add(firstTitle); //加入子標題1

        JTextArea[] square = new JTextArea[3]; // 三個輸入框
        for(int i = 0; i < 3; ++i)
        {
            square[i] = new JTextArea(1, 1);
            square[i].setFont(font);
            firstPanel.add(square[i]); // 加入輸入框
        }
        JLabel money = new JLabel(""); // 最後輸出的獎金
        money.setFont(new Font("Microsoft YaHei", Font.ITALIC, 18)); //斜體
        money.setForeground(Color.RED); // 紅色
        firstPanel.add(money); // 加入介面當中
        
        JLabel secondTitle = new JLabel("第二注: "); // 同下注1
        secondTitle.setFont(font);
        secondPanel.add(secondTitle);

        JTextArea[] square2 = new JTextArea[3];
        for(int i = 0; i < 3; ++i)
        {
            square2[i] = new JTextArea(1, 1);
            square2[i].setFont(font);
            secondPanel.add(square2[i]);
        }

        JLabel money2 = new JLabel("");
        money2.setFont(new Font("Microsoft YaHei", Font.ITALIC, 18));
        money2.setForeground(Color.RED);
        secondPanel.add(money2);

        JLabel resTitle = new JLabel("開獎號碼"); // 開獎號碼
        JLabel res = new JLabel(""); // 結果預設為無
        resTitle.setFont(font); // 設定字形
        res.setFont(new Font("Microsoft YaHei", Font.BOLD, 24)); // 設定開獎號碼字形
        res.setForeground(Color.BLUE); // 藍色
        resultPanel.add(resTitle); // 將物件加入介面
        resultPanel.add(res);
        

        JButton ansButton = new JButton("開獎"); // 開獎按鈕
        ansButton.setFont(font);
        showPanel.add(ansButton);

        ansButton.addActionListener // 事件處理
        (
            new ActionListener() 
            {
                public void actionPerformed(ActionEvent e)
                {
                    int[] num = new int[3];
                    do
                    {
                        num[0] = (int)(9*Math.random());
                        num[1] = (int)(9*Math.random());
                        num[2] = (int)(9*Math.random());
                    } while (num[0] == num[1] || num[1] == num[2] || num[2] == num[0]); // 取得隨機數
                    res.setText(num[0] + " " + num[1] + " " + num[2] + " "); // 顯示開獎號碼
                    
                    int same1=0, same2=0; // 判斷獎金的變數
                    try
                    {
                        for(int i = 0; i < 3; ++i)
                        {
                            int x = Integer.parseInt(square[i].getText()); //取得輸入框的內容,
                            int y = Integer.parseInt(square2[i].getText());
                            if (x == num[i])
                                same1++;
                            if (y == num[i])
                                same2++;
                        }
                        switch(same1) // 判斷中獎狀快
                        {
                            case 0: money.setText("未中獎");break;
                            case 1: money.setText("100元");break;
                            case 2: money.setText("1000元");break;
                            case 3: money.setText("10000元");break;
                            default: money.setText("You Cheat!");break; 
                        }
                        switch(same2)
                        {
                            case 0: money2.setText("未中獎");break;
                            case 1: money2.setText("100元");break;
                            case 2: money2.setText("1000元");break;
                            case 3: money2.setText("10000元");break;
                            default: money2.setText("You Cheat!");break;
                        }
                    }
                    catch(NumberFormatException ex) // 例外處理空格的情況
                    {
                        createNewWindow("未輸入數字!");
                    }
                }
                
            }
        );
        KeyListener type = new KeyAdapter() // 和KeyListner相似, 兩個都可用, 套用在每個文字輸入框當中
        {
            @Override
            public void keyReleased(KeyEvent e) 
            {
                Object source = e.getSource(); // 取得觸發事件的物件 (非常重要!!!)
                if(source instanceof JTextArea) // 如果該物件是JTextField的實例
                {
                    JTextArea temp = (JTextArea) source; // 強制轉型
                    String s = temp.getText(); // 取得內容
                    if(!s.equals("")) // 如果沒輸入, 無反應
                    {
                        try
                        {
                            int cur = Integer.parseInt(s); // 試著去取數字
                            if(0 > cur || 9 < cur) // 數字超出範圍
                            {
                                createNewWindow("號碼超出範圍!");
                                for(int i = 0; i< 3; ++i) // 清掉所有輸入框
                                {
                                    square[i].setText("");
                                    square2[i].setText("");
                                }
                            }
                        }
                        catch(NumberFormatException ex) // 例外處理
                        {
                            createNewWindow("號碼輸入錯誤!");
                            for(int i = 0; i< 3; ++i)
                            {
                                square[i].setText("");
                                square2[i].setText("");
                            }
                        }
                    }

                }
            }
        };
        Border border = BorderFactory.createLineBorder(Color.BLACK, 2); // 輸入框的外框設定, 黑色, 粗度2
        for (int i = 0; i < 3; ++i) // 將事件處理綁定到輸入框當中
        {
            square[i].addKeyListener(type);
            square2[i].addKeyListener(type);

            square[i].setBorder(border); // 輸入框的外框
            square2[i].setBorder(border);
        }

        frm.add(titlePanel);
        frm.add(firstPanel);
        frm.add(secondPanel);
        frm.add(resultPanel);
        frm.add(showPanel);

        frm.pack();
        frm.setMinimumSize(new Dimension(400,400));
        frm.setVisible(true);
    }
}
/*
javac -encoding UTF-8 S1154041.java
java -Dfile.encoding=UTF-8 S1154041
*/