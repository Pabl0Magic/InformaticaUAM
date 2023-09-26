package mvc.view;


import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;
import VoteLanding.*;
import VoteLanding.User.Acceptance;
import VoteLanding.User.State;

public class MainPanel extends JPanel{
	
	JButton homeButton = new JButton("Home"); 
	JButton groupFollowedButton = new JButton("Groups Followed"); 
	JButton groupCreatedButton = new JButton("Groups Created");
	JButton projectButton = new JButton("Projects");
	JButton createGroupButton = new JButton("Create Group");
	JButton createProjectButton = new JButton("Create Project");
	JButton logOutButton = new JButton("Log out"); 
	/*Todos los botones van a la izquierda uno debajo de otro, BoxLAyout o grid layout */
	
	JButton searchProjectButton = new JButton("Search project");
	JButton searchGroupButton = new JButton("Search group");
	JTextField searchText = new JTextField(10);
	
	GUIProject gui;
	/* Combobox para buscar group o project*/
	/*Border Layout big Panel. Inside:
	 * North: Search bar.
	 * West: BorderLayout/GridLAyout
	 * East: Show notifications.
	 */
	public MainPanel(GUIProject gui) {
		
		
		
		this.setLayout(new BorderLayout());
		
		/*Guardar atributo gui project y setearlo
		 * para llama a current user hace:
		 * gui.getConstructor().getSystemLanding().getCurrentUser()
		 * 
		 * depende de si eres admin o user tendras que coger las notificaciones de un lado o de otro
		 */

		
		/*FlowLayout for search panel*/
		JPanel searchPanel = new JPanel(new FlowLayout());
		searchPanel.add(searchText);
		searchPanel.add(searchGroupButton);
		searchPanel.add(searchProjectButton);
		
		/*Buttons to the left*/
		JPanel optionPanel = new JPanel(new GridLayout(7, 1, 0, 10));
		optionPanel.add(homeButton);
		optionPanel.add(groupFollowedButton);
		optionPanel.add(groupCreatedButton);
		optionPanel.add(projectButton);
		optionPanel.add(createGroupButton);
		optionPanel.add(createProjectButton);
		optionPanel.add(logOutButton);
		
		this.add(searchPanel, BorderLayout.PAGE_START);
		this.add(optionPanel, BorderLayout.LINE_START);
		
		searchPanel.setVisible(true);
		optionPanel.setVisible(true);
	
		this.setSize(500, 350);
		this.setVisible(true);
			
	}
	
	public JButton getHomeButton() {
		return homeButton;
	}
	
	
	/**
	 * @return the groupFollowedButton
	 */
	public JButton getGroupFollowedButton() {
		return groupFollowedButton;
	}

	/**
	 * @return the groupCreatedButton
	 */
	public JButton getGroupCreatedButton() {
		return groupCreatedButton;
	}

	/**
	 * @return the projectButton
	 */
	public JButton getProjectButton() {
		return projectButton;
	}

	/**
	 * @return the createGroupButton
	 */
	public JButton getCreateGroupButton() {
		return createGroupButton;
	}

	/**
	 * @return the createProjectButton
	 */
	public JButton getCreateProjectButton() {
		return createProjectButton;
	}

	/**
	 * @return the logOutButton
	 */
	public JButton getLogOutButton() {
		return logOutButton;
	}

	/**
	 * @return the searchText
	 */
	public JTextField getSearchText() {
		return searchText;
	}

	
	/**
	 * 
	 * @return the Search Project Button
	 */
	public JButton getSearchProjectButton() {
		return searchProjectButton;
	}
	
	/**
	 * 
	 * @return the Search Group Button
	 */
	public JButton getSearchGroupButton() {
		return searchGroupButton;
	}

	
	
}
