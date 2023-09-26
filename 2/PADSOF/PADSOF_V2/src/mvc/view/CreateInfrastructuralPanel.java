 package mvc.view;

import java.awt.*;

import javax.swing.*;
import VoteLanding.Infraestructural.District;;

public class CreateInfrastructuralPanel extends JPanel{
	private JButton createButton, uploadImage;
	private JTextField nameField, descField, imageField;
	private JLabel nameLabel, descLabel;
	private JComboBox<District> district;
	private Image image;
	
	/*HAY QUE PONER CREAR COMO... INDIVIDUO/GRUPO1/GRUPO2... (ComboBox??¿?¿?)*/
	public CreateInfrastructuralPanel() {
		Container panel = new JPanel();
		
		SpringLayout sLayout = new SpringLayout();
		panel.setLayout(sLayout);
		
		createButton = new JButton("Create");
		uploadImage = new JButton("Upload Image");
		
		nameField = new JTextField("Introduce the name of the project.");
		descField = new JTextField("Introduce the description of the project");
		imageField = new JTextField("Introduce the filename");
		
		nameLabel = new JLabel("Name:");
		descLabel = new JLabel("Description:");
		
		district = new JComboBox<>();
		district.setModel(new DefaultComboBoxModel<>(District.values()));
		
		//name Label
		sLayout.putConstraint(SpringLayout.WEST, nameLabel, 5, SpringLayout.WEST, panel);
		sLayout.putConstraint(SpringLayout.NORTH, nameLabel, 10, SpringLayout.NORTH, panel);
		
		//name Field
		sLayout.putConstraint(SpringLayout.WEST, nameField, 5, SpringLayout.EAST, uploadImage);
		sLayout.putConstraint(SpringLayout.VERTICAL_CENTER, nameField, 0, SpringLayout.VERTICAL_CENTER, nameLabel);
		
		//desc Label
		sLayout.putConstraint(SpringLayout.WEST, descLabel, 0, SpringLayout.WEST, nameLabel);
		sLayout.putConstraint(SpringLayout.NORTH, descLabel, 10, SpringLayout.SOUTH, nameLabel);
		
		//desc Field
		sLayout.putConstraint(SpringLayout.WEST, descField, 0, SpringLayout.WEST, nameField);
		sLayout.putConstraint(SpringLayout.VERTICAL_CENTER, descField, 0, SpringLayout.VERTICAL_CENTER, descLabel);
		
		//upload Image
		sLayout.putConstraint(SpringLayout.WEST, uploadImage, 0, SpringLayout.WEST, nameLabel);
		sLayout.putConstraint(SpringLayout.NORTH, uploadImage, 10, SpringLayout.SOUTH, descLabel);

		//image Field
		sLayout.putConstraint(SpringLayout.WEST, imageField, 0, SpringLayout.WEST, nameField);
		sLayout.putConstraint(SpringLayout.VERTICAL_CENTER, imageField, 0, SpringLayout.VERTICAL_CENTER, uploadImage);
		
		//district
		sLayout.putConstraint(SpringLayout.WEST, district, 0, SpringLayout.WEST, nameLabel);
		sLayout.putConstraint(SpringLayout.NORTH, district, 5, SpringLayout.SOUTH, uploadImage);
		
		//create Button
		sLayout.putConstraint(SpringLayout.NORTH, createButton, 10, SpringLayout.SOUTH, district);
		sLayout.putConstraint(SpringLayout.HORIZONTAL_CENTER, createButton, 0, SpringLayout.EAST, district);
		
		panel.add(nameLabel);
		panel.add(nameField);
		panel.add(descLabel);
		panel.add(descField);
		panel.add(uploadImage);
		panel.add(imageField);
		panel.add(district);
		panel.add(createButton);
	}
	
	public static void main(String[] args) {
		CreateInfrastructuralPanel infr = new CreateInfrastructuralPanel();
	}
}
