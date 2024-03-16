import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
public class S1154041
{
	public static void main(String args[])
	{
		final int width = 300, height = 300, buttomCount = 12;
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



		GridLayout grid = new GridLayout(4,3);
		JPanel numpad = new JPanel(grid); // same as numpad.setLayout(grid)

		JTextField text = new JTextField();
		text.setHorizontalAlignment(JTextField.RIGHT); // 設定向右對齊
		frm.add(text, border.NORTH);// 文字輸入框放在上面


		for(int i = 1; i <= buttomCount; i++)
		{
			JButton btn;
			switch(i)
			{
				case 12:
					btn = new JButton("=");break;
				case 11:
					btn = new JButton("+");break;
				default:
					btn = new JButton(String.valueOf(i % 10));break;
			}
			btn.addActionListener // 加入事件處理
			(
				new ActionListener()
				{
					public void actionPerformed(ActionEvent e) // 觸發事件的時候
					{
						if(e.getActionCommand().equals("="))
						{
							int result = 0;
							String s = text.getText();
							StringTokenizer st = new StringTokenizer(s,"+");
							while(st.hasMoreTokens())
							{
								result += Integer.parseInt(st.nextToken());
							}
							text.setText(String.valueOf(result));
						}
						else
							text.setText(text.getText() + e.getActionCommand()); // 更新顯示文字
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