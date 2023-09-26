package mvc.view;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import VoteLanding.*;
import VoteLanding.User.State;

/* Getters de los botones: se van a usar luego en el controller
 * Vamos a usar un controller por cada frame
 * En ese controller habra que crear el init view con las funciones de cada puto boton
 * Esas funciones de los botones llamaran a las funciones de SystemLanding
 * 
 * */
public class LoginPanel extends JPanel{
	JButton passButton = new JButton("Ok");
	JTextField nameField = new JTextField(10);
	JPasswordField  passField = new JPasswordField(10);
	JLabel nameLabel = new JLabel("Name: ");
	JLabel  passwordLabel = new JLabel("Password: ");
	JLabel title = new JLabel("Title: ");
	
	
	public LoginPanel() {		
		SpringLayout layout = new SpringLayout();
		
		this.setLayout(layout);
		
		title = new JLabel("Login");
		
		final JPanel username = new JPanel();
		username.add(nameLabel);
		username.add(nameField);
		username.setVisible(true);
		
		final JPanel password = new JPanel();

		
		
		password.add(passwordLabel);
		password.add(passField);
		password.setVisible(true);
		
		
		layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, title, 0, SpringLayout.HORIZONTAL_CENTER, this);
		layout.putConstraint(SpringLayout.NORTH, title, 5, SpringLayout.NORTH, this);
		
		layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, username, 0, SpringLayout.HORIZONTAL_CENTER, this);
		layout.putConstraint(SpringLayout.NORTH, username, 10, SpringLayout.SOUTH, title);
		
		layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, password, 0, SpringLayout.HORIZONTAL_CENTER, this);
		layout.putConstraint(SpringLayout.NORTH, password, 5, SpringLayout.SOUTH, username);

		layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, passButton, 0, SpringLayout.HORIZONTAL_CENTER, this);
		layout.putConstraint(SpringLayout.NORTH, passButton, 15, SpringLayout.SOUTH, password);
		  
		this.add(title);
		this.add(username);
		this.add(password);
		this.add(passButton);
		
		/*LoginWindow.setVisible(true);*/
		
		
	}
	
	public String getPassword() {
		return String.copyValueOf(passField.getPassword());
	}
	
	public String getUsername() {
		return nameField.getText();
	}
	
	public JButton getButton() {
		return passButton;
	}
	
	public void setButton(JButton passButton) {
		this.passButton = passButton;
	}
	
	public void setController(ActionListener c) {
		passButton.addActionListener(c);
	}
	


}
