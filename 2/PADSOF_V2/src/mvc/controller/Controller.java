package mvc.controller;

import mvc.view.*;

import java.util.ArrayList;

import javax.swing.JOptionPane;

import VoteLanding.*;

public class Controller {
	
	GUIProject gui;
	SystemLanding sl;
	
	ArrayList<Project> projectsSearched;
	
	public Controller(GUIProject gui, SystemLanding sl) {
		this.sl = sl;
		this.gui = gui;
	}
	
	public void initActions() {
		//Initial Panel Buttons
		gui.getLogin().getButton().addActionListener(e->login());
		gui.getSignup().getOk().addActionListener(e->signUp());
		
		//Main Panel Buttons
		gui.getMainPanel().getSearchProjectButton().addActionListener(e->searchProject(gui.getMainPanel().getSearchText().getText()));
		gui.getMainPanel().getSearchGroupButton().addActionListener(e->searchGroup(gui.getMainPanel().getSearchText().getText()));
		gui.getMainPanel().getCreateGroupButton().addActionListener(e->createGroup());
		gui.getMainPanel().getCreateProjectButton().addActionListener(e->createProject());
		gui.getMainPanel().getLogOutButton().addActionListener(e->logOut());
		
		//Create Group Panel
		gui.getCreateGroup().getCreate().addActionListener(e->createGroupPanel());
		gui.getCreateGroup().getCancel().addActionListener(e->cancelCreateGroup());
		
		
		
		
		
	}
	
	public GUIProject getGui() {
		return gui;
	}

	public void setGui(GUIProject gui) {
		this.gui = gui;
	}

	public SystemLanding getSl() {
		return sl;
	}

	public void setSl(SystemLanding sl) {
		this.sl = sl;
	}
	/**
	 * 
	 */
	private void login() {
		int ret;
		
		ret = sl.login(gui.getLogin().getUsername(), gui.getLogin().getPassword());
		if(ret == 0) {
			JOptionPane.showMessageDialog(null, "A field is empty.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret == -1) {
			JOptionPane.showMessageDialog(null, "Wrong password.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret==-2) {
			JOptionPane.showMessageDialog(null, "Account banned or pending confirmation.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret == -3) {
			JOptionPane.showMessageDialog(null, "Wrong username.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret == 1) {
			JOptionPane.showMessageDialog(null, "Login completed correctly", "Info", JOptionPane.INFORMATION_MESSAGE);
			gui.loginGUI();
		}
	}
	
	/**
	 * 
	 */
	private void signUp() {
		int ret = sl.signup(gui.getSignup().getUsername(), gui.getSignup().getDNI(), gui.getSignup().getPassword());
		if(ret==0) {
			JOptionPane.showMessageDialog(null, "A field is empty.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret == -1){
			JOptionPane.showMessageDialog(null, "DNI or Username already in use.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else if(ret == -2) {	
			JOptionPane.showMessageDialog(null, "Username Admin is not available.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}else {
			JOptionPane.showMessageDialog(null, "Sign up completed correctly", "Info", JOptionPane.INFORMATION_MESSAGE);
			return;
		}
	}
	
	/**
	 * 
	 */
	private void searchProject(String name) {
		Project projectFound = sl.searchProject(name);
		if(projectFound == null) {
			JOptionPane.showMessageDialog(null, "No projects with that name.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		gui.showProjectFound(projectFound);
	}
	
	private void searchGroup(String name){
		Group groupFound = sl.searchGroup(name);
		if(groupFound == null) {
			JOptionPane.showMessageDialog(null, "No groups with that name.", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}
		gui.showGroupFound(groupFound);
	}
	
	
	private void createGroup() {
		gui.createGroupGUI();
		
	}
	
	
	private void createGroupPanel() {
		int ret;
		ret = sl.createGroup(gui.getCreateGroup().getNameText().getText(), gui.getCreateGroup().getDescText().getText());
		
		if(ret==-1) {
			JOptionPane.showMessageDialog(null, "Fields empty.", "Error", JOptionPane.ERROR_MESSAGE);
		}else if(ret==-2) {
			JOptionPane.showMessageDialog(null, "Already a group with that name.", "Error", JOptionPane.ERROR_MESSAGE);
		}else {
			JOptionPane.showMessageDialog(null, "Group created succesfully.", "Info", JOptionPane.INFORMATION_MESSAGE);
			gui.createGroupPanelGUI();
		}
		
		
	}
	
	private void cancelCreateGroup() {
		gui.cancelCreateGroupPanelGUI();
	}
	
	
	
	private void createProject() {
		gui.createProjectGUI();
	}
	
	private void logOut() {
		sl.setCurrentUser(null);
		gui.logOutGUI();
	}
	
	
	private void searchProjectToHome() {
		gui.searchProjectToHome();
	}
	
	private void searchGroupToHome() {
		gui.searchGroupToHome();
	}
	
	
}
