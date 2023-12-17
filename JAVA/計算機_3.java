import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
public class S1154041
{
	public static void main(String args[])
	{
		final int width = 300, height = 300, buttomCount = 16;
		JFrame frm = new JFrame("Calculator"); //視窗名稱
		BorderLayout border = new BorderLayout(5,5); // 擺放位置設定
		frm.setLayout(border); // 物件的擺放方式更改
		frm.setSize(width, height); // 視窗大小設定
		//frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 使關閉按鍵有用
		frm.addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});

		GridLayout grid = new GridLayout(4,4);
		JPanel numpad = new JPanel(grid); // same as numpad.setLayout(grid)

		JTextField text = new JTextField();
		text.setHorizontalAlignment(JTextField.RIGHT); // 設定向右對齊
		frm.add(text, border.NORTH);// 文字輸入框放在上面

		String[] list = new String[buttomCount];
		list[0] = "7";
		list[1] = "8";
		list[2] = "9";
		list[3] = "C";
		list[4] = "4";
		list[5] = "5";
		list[6] = "6";
		list[7] = "*";
		list[8] = "1";
		list[9] = "2";
		list[10] = "3";
		list[11] = "/";
		list[12] = "0";
		list[13] = "+";
		list[14] = "-";	
		list[15] = "=";


		for(int i = 0; i < buttomCount; i++)
		{
			JButton btn = new JButton(list[i]);
			btn.addActionListener // 加入事件處理
			(
				new ActionListener()
				{
					public void actionPerformed(ActionEvent e) // 觸發事件的時候
					{
						switch(e.getActionCommand())
						{
							case "C":
								text.setText("0");
								break;
							case "=":
								int result = 0;
								int temp = 0;
								char lastOp = '+';
								String s = text.getText();
								boolean firstNumber = true;

								for (int i = 0; i < s.length(); i++)
								{
								    char c = s.charAt(i);
								    if (c >= '0' && c <= '9')
								    {
								        temp = temp * 10 + (c - '0');
								    }
								    else
								    {
								        if (firstNumber)
								        {
								            result = temp;
								            firstNumber = false;
								        }
								        else
								        {
								            switch (lastOp)
								            {
								                case '+':
								                    result += temp;
								                    break;
								                case '-':
								                    result -= temp;
								                    break;
								                case '*':
								                    result *= temp;
								                    break;
								                case '/':
								                    result /= temp;
								                    break;
								            }
								        }
								        temp = 0;
								        lastOp = c;
								    }
								}
								if (firstNumber)
								{
								    result = temp;
								}
								else
								{
								    switch (lastOp)
								    {
								        case '+':
								            result += temp;
								            break;
								        case '-':
								            result -= temp;
								            break;
								        case '*':
								            result *= temp;
								            break;
								        case '/':
								            result /= temp;
								            break;
								    }
								}
								text.setText(String.valueOf(result));
								break;
							default:
								if(text.getText().equals("0"))
								{ //begin with 0
									char pressed = e.getActionCommand().charAt(0);
									if('0' <= pressed&& pressed <= '9')
									{ // only number can be shown
										text.setText(e.getActionCommand());
									}
								}
								else
									text.setText(text.getText() + e.getActionCommand());
						}
					}
				}
			);
			numpad.add(btn); // 畫布加入按鈕
		}
		frm.add(numpad);// 將數字區加入畫布
		frm.setVisible(true); // 顯示畫面
	}
}
/*
javac -encoding UTF-8 S1154041.java
java -Dfile.encoding=UTF-8 S1154041
*/