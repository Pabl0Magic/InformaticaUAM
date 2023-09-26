package mvc.view;

import java.awt.*;

import javax.swing.*;

/* Nombre y descripcion */
public class CreateGroupPanel extends JPanel{
	
	private JLabel nameLabel, descLabel, title;
	private JTextField nameText, descText;
	private JButton create, cancel;
	
	
	public CreateGroupPanel() {
	
		SpringLayout sLayout = new SpringLayout();
		this.setLayout(sLayout);
		
		title = new JLabel("Create Group");
		nameLabel = new JLabel("Name: ");
		descLabel = new JLabel("Description: ");
		
		nameText = new JTextField(15);
		descText = new JTextField(30);
		
		create = new JButton("Create");
		cancel = new JButton("Cancel");
		
		/*creo que esta bien COMPROBAR*/
		
		sLayout.putConstraint(SpringLayout.HORIZONTAL_CENTER, title, 0, SpringLayout.HORIZONTAL_CENTER, this);
		sLayout.putConstraint(SpringLayout.NORTH, title, 10, SpringLayout.NORTH, this);
		//name Label
		sLayout.putConstraint(SpringLayout.HORIZONTAL_CENTER, nameLabel, 0, SpringLayout.HORIZONTAL_CENTER, this);
		sLayout.putConstraint(SpringLayout.NORTH, nameLabel, 10, SpringLayout.SOUTH, title);
		//name Field
		sLayout.putConstraint(SpringLayout.WEST, nameText, 5, SpringLayout.EAST, descLabel);
		sLayout.putConstraint(SpringLayout.VERTICAL_CENTER, nameText, 10, SpringLayout.VERTICAL_CENTER, nameLabel);
		//desc Label
		sLayout.putConstraint(SpringLayout.WEST, descLabel, 0, SpringLayout.WEST, nameLabel);
		sLayout.putConstraint(SpringLayout.NORTH, descLabel, 10, SpringLayout.SOUTH, nameLabel);
		//desc Field
		sLayout.putConstraint(SpringLayout.WEST, descText, 0, SpringLayout.WEST, nameText);
		sLayout.putConstraint(SpringLayout.NORTH, descText, 10, SpringLayout.SOUTH, nameLabel);
		//Create Button
		sLayout.putConstraint(SpringLayout.NORTH, create, 15, SpringLayout.SOUTH, descText);
		sLayout.putConstraint(SpringLayout.HORIZONTAL_CENTER, create, 10, SpringLayout.EAST, descLabel);
		//Cancel Button
		sLayout.putConstraint(SpringLayout.VERTICAL_CENTER, cancel, 0, SpringLayout.VERTICAL_CENTER, create);
		sLayout.putConstraint(SpringLayout.EAST, cancel, 10, SpringLayout.WEST, create);
		
		this.add(title);
		this.add(nameLabel);
		this.add(nameText);
		this.add(descLabel);
		this.add(descText);
		this.add(create);
		this.add(cancel);
		
	}
	public static void main(String[] args) {
		CreateGroupPanel cg = new CreateGroupPanel();
	}
	public JLabel getNameLabel() {
		return nameLabel;
	}
	public JLabel getDescLabel() {
		return descLabel;
	}
	public JLabel getTitle() {
		return title;
	}
	public JTextField getNameText() {
		return nameText;
	}
	public JTextField getDescText() {
		return descText;
	}
	public JButton getCreate() {
		return create;
	}
	public JButton getCancel() {
		return cancel;
	}
	

}
