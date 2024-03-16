import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class S1154041
{
    public static void main(String args[])
    {
        JFrame frm = new JFrame("猜拳遊戲");
        frm.setLayout(new GridLayout(5, 1));
        frm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        FlowLayout center = new FlowLayout(FlowLayout.CENTER);
        Font font = new Font("Microsoft YaHei", Font.BOLD, 18);

        JPanel titlePanel = new JPanel(center);
        JPanel choosePanel = new JPanel(center);
        JPanel resPanel = new JPanel(center);
        JPanel statePanel = new JPanel(center);

        JLabel title = new JLabel("猜拳遊戲");
        title.setFont(font);
        titlePanel.add(title);
        
        JButton[] buttons = new JButton[3];
        String[] list = {"剪刀", "石頭", "布"};
        for(int i=0;i<3;++i)
        {
            JButton temp = new JButton(list[i]);
            temp.setFont(font);
            buttons[i] = temp;
            choosePanel.add(buttons[i]);
        }
        
        JLabel player = new JLabel("");
        JLabel enemy = new JLabel("");
        player.setFont(font);
        enemy.setFont(font);
        player.setForeground(Color.BLUE);
        enemy.setForeground(Color.RED);
        resPanel.add(player);
        resPanel.add(enemy);

        JLabel state = new JLabel("請出拳");
        state.setFont(font);
        statePanel.add(state);

        ActionListener pressed = new ActionListener() 
        {
            @Override
            public void actionPerformed(ActionEvent e) 
            {
                Object source = e.getSource();
                if(source instanceof JButton)
                {
                    JButton cur = (JButton) source;
                    player.setText(cur.getText());
                }
                enemy.setText(list[(int) (3 * Math.random())]); // 寫入隨機內容
                if(player.getText().equals(enemy.getText()))
                {
                    state.setText("Try again!!");
                }
                else if((player.getText().equals("剪刀") && enemy.getText().equals("石頭"))|| (player.getText().equals("石頭") && enemy.getText().equals("布"))||(player.getText().equals("布") && enemy.getText().equals("剪刀")))
                {
                    state.setText("You Lose!!");
                }
                else
                    state.setText("You win!!");
            }
        };
        for(int i=0;i<3;++i)
        {
            buttons[i].addActionListener(pressed);
        }

        frm.add(new JPanel());
        frm.add(titlePanel);
        frm.add(choosePanel);
        frm.add(resPanel);
        frm.add(statePanel);

        frm.pack();
        frm.setMinimumSize(new Dimension(400,400));
        frm.setVisible(true);
    }
}