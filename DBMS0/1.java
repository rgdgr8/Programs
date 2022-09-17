import javax.swing.*;
import static javax.swing.WindowConstants.*;

class AddorSubtract {
    public static void main(String[] args) {
        JFrame f = new JFrame("Add or Subtract 2 numbers");

        JLabel num1Label = new JLabel("Enter the first number");
        num1Label.setBounds(115, 20, 300, 40); // x axis, y axis, width, height
        JTextField num1 = new JTextField();
        num1.setBounds(130, 60, 100, 40);
        JLabel num2Label = new JLabel("Enter the second number");
        num2Label.setBounds(115, 110, 300, 40);
        JTextField num2 = new JTextField();
        num2.setBounds(130, 150, 100, 40);
        JLabel resultLabel = new JLabel("Result");
        resultLabel.setBounds(155, 200, 100, 40);
        JLabel result = new JLabel("------------");
        result.setBounds(130, 240, 100, 40);
        // result.setVisible(false);
        JButton add = new JButton("add");
        add.setBounds(130, 330, 100, 40);
        add.addActionListener((e) -> {
            try {
                int a = Integer.parseInt(num1.getText());
                int b = Integer.parseInt(num2.getText());
                int c = a + b;
                result.setText(String.valueOf(c));
            } catch (Exception exc) {
                result.setText("Invalid input(s)");
            }
        });
        JButton sub = new JButton("sub");
        sub.setBounds(130, 380, 100, 40);
        sub.addActionListener((e) -> {
            try {
                int a = Integer.parseInt(num1.getText());
                int b = Integer.parseInt(num2.getText());
                int c = a - b;
                result.setText(String.valueOf(c));
            } catch (Exception exc) {
                result.setText(exc.getMessage());
            }
        });

        f.add(num1Label);
        f.add(num1);
        f.add(num2Label);
        f.add(num2);
        f.add(resultLabel);
        f.add(result);
        f.add(add);
        f.add(sub);

        f.setSize(400, 500);// 400 width and 500 height
        f.setLayout(null);// using no layout managers
        f.setVisible(true);// making the frame visible

        f.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}