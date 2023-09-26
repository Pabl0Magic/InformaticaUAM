package mvc.view;


import java.awt.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SpringLayout;

import VoteLanding.Project;
import VoteLanding.Social;
import VoteLanding.Social.ScopeProject;


public class SearchProjectPanel extends JPanel {
	GUIProject gui;
	
	JButton voteIndivButton = new JButton("Vote individually");
	JButton voteGroupButton = new JButton("Vote as a group");
	JButton home = new JButton("Home");
	
	JLabel name = new JLabel();
	JLabel desc = new JLabel();
	JLabel head = new JLabel("Project found: ");
	
	public SearchProjectPanel(Project p, GUIProject gui) {
		this.gui = gui;
		
		String nameString = p.getName();
		name = new JLabel("Name: "+ nameString);
		
		JPanel descPanel = new JPanel();
		descPanel.setLayout(new FlowLayout());
		String descString = p.getDesc();
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
		
		layout.putConstraint(SpringLayout.WEST, voteIndivButton,5,SpringLayout.WEST, this);
		layout.putConstraint(SpringLayout.NORTH, voteIndivButton,5,SpringLayout.SOUTH, descPanel);
		
		layout.putConstraint(SpringLayout.WEST, voteGroupButton,10,SpringLayout.EAST, voteIndivButton);
		layout.putConstraint(SpringLayout.NORTH, voteGroupButton,5,SpringLayout.SOUTH, descPanel);

		layout.putConstraint(SpringLayout.WEST, home,5,SpringLayout.EAST, this);
		layout.putConstraint(SpringLayout.NORTH, home,25 ,SpringLayout.SOUTH, voteIndivButton);
		
	
		
		
		
		this.add(head);
		this.add(name);
		this.add(descPanel);
		this.add(voteIndivButton);
		this.add(voteGroupButton);
		this.add(home);
		
		this.setSize(500, 400);
		this.setVisible(true);
		
	}
	
	public static void main(String[] args) {
		JFrame window = new JFrame("HOLI");
		Container container = window.getContentPane();
		Project p = new Social("Pablos", ScopeProject.National,"Pablo", "Pablsdfsdfsdfsdfsd.gjdfxghdkfsyvsngisdfdfubfdugyhskufdtyshuyuo mamahuevo", 69.420);
		container.add(new SearchProjectPanel(p));
		window.setVisible(true);
		window.setSize(500,300);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	
	private void toHome() {
		gui.searchProjectToHome();
	}

	/**
	 * @return the voteIndivButton
	 */
	public JButton getVoteIndivButton() {
		return voteIndivButton;
	}

	/**
	 * @return the voteGroupButton
	 */
	public JButton getVoteGroupButton() {
		return voteGroupButton;
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
}
