package mvc.view;


import java.awt.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import VoteLanding.Group;

public class SearchGroupPanel extends JPanel {
	JButton followButton = new JButton("Follow");
	JButton unfollowButton = new JButton("Unfollow");
	JButton subgroupButton = new JButton("Create subgroup");
	JButton home = new JButton("Home");
	
	JLabel name = new JLabel();
	JLabel desc = new JLabel();
	JLabel head = new JLabel("Group found: ");
	
	GUIProject gui;	
	public SearchGroupPanel(Group g, GUIProject gui) {
		this.gui = gui;
		
		String nameString = g.getName();
		name = new JLabel("Name: "+ nameString);
		
		JPanel descPanel = new JPanel();
		descPanel.setLayout(new FlowLayout());
		String descString = g.getDescription();
		desc = new JLabel("Description: "+ descString);
		descPanel.add(desc);
		
		SpringLayout layout = new SpringLayout();
		this.setLayout(layout);
	
		layout.putConstraint(SpringLayout.WEST, head, 5, SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, head,5,SpringLayout.NORTH, this);
		
		layout.putConstraint(SpringLayout.WEST, name,5, SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, name,15,SpringLayout.SOUTH, head);
		
		layout.putConstraint(SpringLayout.WEST, descPanel, 5, SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, descPanel, 5,SpringLayout.SOUTH, name);
		
		layout.putConstraint(SpringLayout.WEST, followButton,5,SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, followButton,5,SpringLayout.SOUTH, descPanel);

		layout.putConstraint(SpringLayout.WEST, unfollowButton,10,SpringLayout.EAST, followButton);
		layout.putConstraint(SpringLayout.NORTH, unfollowButton,5,SpringLayout.SOUTH, descPanel);
		
		layout.putConstraint(SpringLayout.WEST, subgroupButton,10,SpringLayout.EAST, unfollowButton);
		layout.putConstraint(SpringLayout.NORTH, subgroupButton,5,SpringLayout.SOUTH, descPanel);
		
		layout.putConstraint(SpringLayout.WEST, home,5,SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, home,25 ,SpringLayout.SOUTH, followButton);
		
		home.addActionListener(e->toHome());
		

		this.add(head);
		this.add(name);
		this.add(descPanel);
		this.add(followButton);
		this.add(unfollowButton);
		this.add(subgroupButton);
		this.add(home);

		this.setSize(700, 400);
		this.setVisible(true);
		
	}
	
	
	private void toHome() {
		gui.searchGroupToHome();
	}
	
	/**
	 * @return the followButton
	 */
	public JButton getFollowButton() {
		return followButton;
	}

	/**
	 * @return the unfollowButton
	 */
	public JButton getUnfollowButton() {
		return unfollowButton;
	}

	/**
	 * @return the subgroupButton
	 */
	public JButton getSubgroupButton() {
		return subgroupButton;
	}

	/**
	 * @return the home
	 */
	public JButton getHome() {
		return home;
	}

	

	/**
	 * @return the desc
	 */
	public JLabel getDesc() {
		return desc;
	}

	/**
	 * @return the head
	 */
	public JLabel getHead() {
		return head;
	}

	public static void main(String[] args) {
		
	}
}

