package mvc.view;

import java.awt.*;
import javax.swing.*;

public class CreateSocialPanel extends JFrame{
	
	JButton createButton;
	JTextField projectName, targetName, descName;
	JLabel nameLabel, targetLabel, socialLabel, descLabel;
	
	String[] nat = {"National", "International"};
	
	public CreateSocialPanel() {
		JFrame SocialWindow = new JFrame("Social project");
		
		Container container = SocialWindow.getContentPane();
		
		SpringLayout layout = new SpringLayout();
		container.setLayout(layout);
		
		final JPanel socialPanel = new JPanel(new GridLayout(5,2,0,10));
		nameLabel = new JLabel("Name: ");
		projectName = new JTextField(10);
		targetLabel = new JLabel("Target group: ");
		targetName = new JTextField(10);
		descLabel = new JLabel("Description: ");
		descName = new JTextField(10);
		
		JComboBox<String> combobox = new JComboBox<String>(nat);
		combobox.setSelectedIndex(0);
	    
		createButton = new JButton("Create");
		
		socialPanel.add(nameLabel);
		socialPanel.add(projectName);
		socialPanel.add(targetLabel);
		socialPanel.add(targetName);
		socialPanel.add(new JLabel("Nationality: "));
		socialPanel.add(combobox);
		socialPanel.add(descLabel);
		socialPanel.add(descName);
		
		final JPanel buttonPanel = new JPanel();
		buttonPanel.add(createButton);

		layout.putConstraint(SpringLayout.WEST, socialPanel, 5, SpringLayout.WEST, container);
		layout.putConstraint(SpringLayout.NORTH, socialPanel, 5, SpringLayout.NORTH, container);
		
		layout.putConstraint(SpringLayout.WEST, buttonPanel, 0, SpringLayout.HORIZONTAL_CENTER, socialPanel);
		layout.putConstraint(SpringLayout.NORTH, buttonPanel, 5, SpringLayout.SOUTH, socialPanel);
		container.add(socialPanel);
		container.add(buttonPanel);
		
		
		 
	}
	
	public static void main(String[] args) {
		CreateSocialPanel soc = new CreateSocialPanel();
	}
}
