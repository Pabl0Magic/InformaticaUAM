package mvc.view;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class CreateProjectPanel extends JPanel{

	private JLabel taskName;
	private JRadioButton social;
	private JRadioButton infrastructural;
	private JButton acceptButton;
		
	public CreateProjectPanel() {		
		taskName = new JLabel("Select the type of project:");
		social = new JRadioButton("Social");
		infrastructural = new JRadioButton("Infrastructural");
		acceptButton = new JButton("Select");
		
		ButtonGroup grupo = new ButtonGroup();
		
		grupo.add(social);
		grupo.add(infrastructural);
		
		this.setLayout(new GridLayout(4,1,0,10));
		
		this.add(taskName);
		this.add(social);
		this.add(infrastructural);
		this.add(acceptButton);
		
	}
	
	public static void main(String[] args) {
		CreateProjectPanel si = new CreateProjectPanel();
	}

}
