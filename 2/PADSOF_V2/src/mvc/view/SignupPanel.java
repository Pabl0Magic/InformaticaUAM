package mvc.view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.lang.ModuleLayer.Controller;

import javax.swing.*;


class Form extends JPanel {
	  private JLabel nameLabel, dniLabel, pwLabel;
	  private JTextField nameText, dniText;
	  private JPasswordField pwText;

	  public Form () {
	    SpringLayout layout = new SpringLayout();	
	    this.setLayout(layout);    			
	    
	    // Components to be located ...
	    nameLabel  = new JLabel("Name: ");
	    nameText  = new JTextField(15);
	    dniLabel = new JLabel("DNI: ");
	    dniText = new JTextField(15);
	    pwLabel = new JLabel("Password: ");
	    pwText = new JPasswordField(15);

	    // The left side of label will be located 5 pixels away from the left side of container
	    layout.putConstraint(SpringLayout.EAST, nameLabel, 0, SpringLayout.EAST, pwLabel);
	    // The upper side of label will be located 5 pixels away from the upper part of container
	    layout.putConstraint(SpringLayout.NORTH, nameLabel, 5, SpringLayout.NORTH, this);


	    layout.putConstraint(SpringLayout.WEST, nameText, 5, SpringLayout.EAST, nameLabel);
	    layout.putConstraint(SpringLayout.NORTH, nameText, 5, SpringLayout.NORTH, this);

	    layout.putConstraint(SpringLayout.EAST, dniLabel, 0, SpringLayout.EAST, nameLabel);
	    layout.putConstraint(SpringLayout.NORTH, dniLabel, 8, SpringLayout.SOUTH, nameLabel);

	    layout.putConstraint(SpringLayout.WEST, dniText, 0, SpringLayout.WEST, nameText);
	    layout.putConstraint(SpringLayout.NORTH, dniText, 5, SpringLayout.SOUTH, nameText);
	    
	    layout.putConstraint(SpringLayout.WEST, pwLabel, 5, SpringLayout.WEST, this);
	    layout.putConstraint(SpringLayout.NORTH, pwLabel, 8, SpringLayout.SOUTH, dniLabel);
	    
	    layout.putConstraint(SpringLayout.WEST, pwText, 0, SpringLayout.WEST, nameText);
	    layout.putConstraint(SpringLayout.NORTH, pwText, 5, SpringLayout.SOUTH, dniText);
	    
	    
	    this.add(nameLabel); this.add(nameText); this.add(dniLabel); this.add(dniText);this.add(pwLabel); this.add(pwText);
	    this.setPreferredSize(new Dimension(300,200));
	    this.setVisible(true);  
	  }
	  
	  protected String getFormUsername() {
	  	return nameText.getText();
	  }
	  protected String getFormDNI() {
		  	return dniText.getText();
	  }
	  protected String getFormPassword() {
		  	return String.valueOf(pwText.getPassword());
	  }
	}


public class SignupPanel extends JPanel{

	private JPanel buttonPanel   = new JPanel();
	private Form form          = new Form (); 
	private JButton ok         = new JButton("OK");
	private JLabel label       = new JLabel("Sign up");
	
	public SignupPanel() {
		SpringLayout layout = new SpringLayout() ;
		 this.setLayout(layout);		

		 layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, label, 0, SpringLayout.HORIZONTAL_CENTER, this);
		 layout.putConstraint(SpringLayout.NORTH, label, 5, SpringLayout.NORTH, this);
		 
		 layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, form, 0, SpringLayout.HORIZONTAL_CENTER, this);
		 layout.putConstraint(SpringLayout.NORTH, form, 5, SpringLayout.SOUTH, label);
		 
		 layout.putConstraint(SpringLayout.HORIZONTAL_CENTER, buttonPanel, 0, SpringLayout.HORIZONTAL_CENTER, this);
		 layout.putConstraint(SpringLayout.NORTH, buttonPanel, -125, SpringLayout.SOUTH, form);
		  
		 
		 buttonPanel.add(ok);		
		   
		  
		  
		 this.add(buttonPanel);	
		 this.add(form);
		 this.add(label);
		    
		 this.setMinimumSize(new Dimension(250,150));
	}
	
	public String getUsername() {
		return form.getFormUsername();
	}
	  
	public String getDNI() {
		return form.getFormDNI();
	}
	  
	public String getPassword() {
		return form.getFormPassword();
	}
	  
	public JPanel getButtonPanel() {
		return buttonPanel;
	}

	public void setButtonPanel(JPanel buttonPanel) {
		this.buttonPanel = buttonPanel;
	}

	public Form getForm() {
		return form;
	}

	public void setForm(Form form) {
		this.form = form;
	}

	public JButton getOk() {
		return ok;
	}

	public void setOk(JButton ok) {
		this.ok = ok;
	}
	
	public static void main(String[] args) {
		JFrame window = new JFrame();
		window.setLayout(new FlowLayout());


		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setSize(500, 500);
		window.setVisible(true);
		new SignupPanel();
		window.add(new SignupPanel());
	}


	
	  

}
