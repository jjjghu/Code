<<<<<<< HEAD
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class S1154041 {
	private static int win = 0, lose = 0;

	public static void main(String args[]) {
		JFrame frm = new JFrame("比大小"); // 主視窗
		frm.setLayout(new GridLayout(5, 1)); // 設定排版, 標題, 戰績, 顯示內容, win / lose / tryagain, 兩顆按鈕
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 關閉案紐
		FlowLayout flow = new FlowLayout(FlowLayout.CENTER); // 排版內部的位置

		JPanel titlePanel = new JPanel(flow);
		JPanel gradePanel = new JPanel(flow);
		JPanel ansPanel = new JPanel(flow);
		JPanel resultPanel = new JPanel(flow);
		JPanel choosePanel = new JPanel(flow);

		JLabel title = new JLabel("比大小");
		title.setFont(new Font("", Font.BOLD, 18)); // 字體設定 (名稱, 「」體, 大小)
		titlePanel.add(title);

		JLabel grade = new JLabel("戰績: 0 勝 0 敗");
		grade.setFont(new Font("", Font.BOLD, 18));
		gradePanel.add(grade); // 加入

		JLabel ans = new JLabel(""); // 顯示正確數字
		ans.setForeground(Color.BLUE); // 設定為藍色
		ans.setFont(new Font("", Font.BOLD, 25));
		ansPanel.add(ans);

		JLabel result = new JLabel("");
		result.setForeground(Color.BLACK);
		result.setFont(new Font("", Font.BOLD, 18));
		resultPanel.add(result);

		JButton a = new JButton("比七大");
		JButton b = new JButton("比七小");
		a.addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						try {
							int num = (int) (Math.random() * 14); // 0 ~ 13的隨機數
							ans.setText(String.valueOf(num)); // 顯示數字在畫面上
							if (num == 7) {
								result.setForeground(Color.BLACK);
								result.setText("try again");
							} else if (num < 7) {
								result.setForeground(Color.RED);
								result.setText("You lose!");
								lose++;
							} else {
								result.setForeground(Color.BLUE);
								result.setText("You win!");
								win++;
							}
							grade.setText("戰績: " + win + "勝" + lose + "敗");
						} catch (Exception ex) {
							ans.setText("INVALID!");
						}
					}
				});
		b.addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						try {
							int num = (int) (Math.random() * 14); // 0 ~ 13的隨機數
							ans.setText(String.valueOf(num)); // 顯示數字在畫面上
							if (num == 7) {
								result.setForeground(Color.BLACK);
								result.setText("try again");
							} else if (num > 7) {
								result.setForeground(Color.RED);
								result.setText("You lose!");
								lose++;
							} else {
								result.setForeground(Color.BLUE);
								result.setText("You win!");
								win++;
							}
							grade.setText("戰績: " + win + "勝" + lose + "敗");
						} catch (Exception ex) {
							ans.setText("INVALID!");
						}
					}
				});
		choosePanel.add(a);
		choosePanel.add(b);

		frm.add(titlePanel);
		frm.add(gradePanel);
		frm.add(ansPanel);
		frm.add(resultPanel);
		frm.add(choosePanel);
		frm.pack();
		frm.setMinimumSize(new Dimension(300, 300));
		frm.setVisible(true);
	}
}
/*
 * javac -encoding UTF-8 S1154041.java
 * java -Dfile.encoding=UTF-8 S1154041
=======
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class S1154041 {
	private static int win = 0, lose = 0;

	public static void main(String args[]) {
		JFrame frm = new JFrame("比大小"); // 主視窗
		frm.setLayout(new GridLayout(5, 1)); // 設定排版, 標題, 戰績, 顯示內容, win / lose / tryagain, 兩顆按鈕
		frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 關閉案紐
		FlowLayout flow = new FlowLayout(FlowLayout.CENTER); // 排版內部的位置

		JPanel titlePanel = new JPanel(flow);
		JPanel gradePanel = new JPanel(flow);
		JPanel ansPanel = new JPanel(flow);
		JPanel resultPanel = new JPanel(flow);
		JPanel choosePanel = new JPanel(flow);

		JLabel title = new JLabel("比大小");
		title.setFont(new Font("", Font.BOLD, 18)); // 字體設定 (名稱, 「」體, 大小)
		titlePanel.add(title);

		JLabel grade = new JLabel("戰績: 0 勝 0 敗");
		grade.setFont(new Font("", Font.BOLD, 18));
		gradePanel.add(grade); // 加入

		JLabel ans = new JLabel(""); // 顯示正確數字
		ans.setForeground(Color.BLUE); // 設定為藍色
		ans.setFont(new Font("", Font.BOLD, 25));
		ansPanel.add(ans);

		JLabel result = new JLabel("");
		result.setForeground(Color.BLACK);
		result.setFont(new Font("", Font.BOLD, 18));
		resultPanel.add(result);

		JButton a = new JButton("比七大");
		JButton b = new JButton("比七小");
		a.addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						try {
							int num = (int) (Math.random() * 14); // 0 ~ 13的隨機數
							ans.setText(String.valueOf(num)); // 顯示數字在畫面上
							if (num == 7) {
								result.setForeground(Color.BLACK);
								result.setText("try again");
							} else if (num < 7) {
								result.setForeground(Color.RED);
								result.setText("You lose!");
								lose++;
							} else {
								result.setForeground(Color.BLUE);
								result.setText("You win!");
								win++;
							}
							grade.setText("戰績: " + win + "勝" + lose + "敗");
						} catch (Exception ex) {
							ans.setText("INVALID!");
						}
					}
				});
		b.addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						try {
							int num = (int) (Math.random() * 14); // 0 ~ 13的隨機數
							ans.setText(String.valueOf(num)); // 顯示數字在畫面上
							if (num == 7) {
								result.setForeground(Color.BLACK);
								result.setText("try again");
							} else if (num > 7) {
								result.setForeground(Color.RED);
								result.setText("You lose!");
								lose++;
							} else {
								result.setForeground(Color.BLUE);
								result.setText("You win!");
								win++;
							}
							grade.setText("戰績: " + win + "勝" + lose + "敗");
						} catch (Exception ex) {
							ans.setText("INVALID!");
						}
					}
				});
		choosePanel.add(a);
		choosePanel.add(b);

		frm.add(titlePanel);
		frm.add(gradePanel);
		frm.add(ansPanel);
		frm.add(resultPanel);
		frm.add(choosePanel);
		frm.pack();
		frm.setMinimumSize(new Dimension(300, 300));
		frm.setVisible(true);
	}
}
/*
 * javac -encoding UTF-8 S1154041.java
 * java -Dfile.encoding=UTF-8 S1154041
>>>>>>> 81b5d021060ae4656a934c7853dd490d6711f23d
 */