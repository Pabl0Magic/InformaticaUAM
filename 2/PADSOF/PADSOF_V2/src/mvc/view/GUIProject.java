package mvc.view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;

import VoteLanding.Group;
import VoteLanding.Project;
import VoteLanding.SystemLanding;
import mvc.controller.*;
/* Crea un frame, y guarda todos los paneles que hayamos creado.
 * Un atributo por cada panel que haya.
 * Cuando inicializas el GUI genberal, inicializas todos los GUI pero los dejas en invisible (visible(false)) excepto log in y signup
 * Si le das a aceptar a sign up y esta todo bien tienes que esperar a que el admin acepte.
 * Tras aceptar, tiene que aparecerte una ventana con signup succesful
 * 
 * Cuando te logueas, te da loginok.
 * 
 * */
public class GUIProject extends JFrame{
	private JFrame window;
	private Container container;
	
	private JPanel initPanel; //initPanel = login + signup
	private MainPanel mainPanel;
	
	private SignupPanel signup;
	private LoginPanel login;
	private CreateProjectPanel createProject;
	private CreateGroupPanel createGroup;
	private SearchGroupPanel searchGroup;
	private SearchProjectPanel searchProject;


	private Controller controller;
	public GUIProject() {
		/*Inicializamos y hacemos visibles login y signup que son los que se ven de momento*/
		
		// construction of initPanel
		window = new JFrame("Vote Landing");
		initPanel = new JPanel(new GridLayout(1,2));
		container = window.getContentPane();
		signup = new SignupPanel();
		login = new LoginPanel();
		initPanel.add(login);
		initPanel.add(signup);
		
		
		
		//creamos los paneles
		mainPanel = new MainPanel(this);
		createProject = new CreateProjectPanel();
		createGroup = new CreateGroupPanel();
		
		
		mainPanel.setVisible(false);
		createProject.setVisible(false);
		createGroup.setVisible(false);
		
		container.add(mainPanel);
		container.add(initPanel);
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setSize(700, 600);
		window.setVisible(true);
		
		
	}
		
	
	
	
	
	public static void main(String[] args) {
		GUIProject gui = new GUIProject();
		SystemLanding sl = new SystemLanding();
		Controller controller = new Controller(gui, sl);
		controller.initActions();
	}

	public void loginGUI(){
		initPanel.setVisible(false);
		mainPanel.setVisible(true);
		
	}
	
	
	public void logOutGUI() {
		mainPanel.setVisible(false);
		initPanel.setVisible(true);
	}
	
	public void createProjectGUI() {
		mainPanel.setVisible(false);
		container.add(createProject);
		createProject.setVisible(true);
	}

	

	public void showProjectFound(Project projectFound) {
		SearchProjectPanel searchProject = new SearchProjectPanel(projectFound, this);
		
		container.add(searchProject);
		searchProject.setVisible(true);
	}


	public void showGroupFound(Group groupFound) {
		
		searchGroup = new SearchGroupPanel(groupFound, this);
		
		container.add(searchGroup);
		searchGroup.setVisible(true);
		mainPanel.setVisible(false);
	}


	public void createGroupGUI() {
		mainPanel.setVisible(false);
		
		container.add(createGroup);
		createGroup.setVisible(true);
	}
	
	public void createGroupPanelGUI() {
		createGroup.setVisible(false);
		mainPanel.setVisible(true);
	}

	public void cancelCreateGroupPanelGUI() {
		createGroup.setVisible(false);
		mainPanel.setVisible(true);
	}

	
	public void searchProjectToHome() {
		searchProject.setVisible(false);
		mainPanel.setVisible(true);
	}
	
	public void searchGroupToHome() {
		searchGroup.setVisible(false);
		mainPanel.setVisible(true);
	}

	
	
	/**
	 * @return the signup panel
	 */
	public SignupPanel getSignup() {
		return signup;
	}




	/**
	 * @return the login panel
	 */
	public LoginPanel getLogin() {
		return login;
	}
	
	/**
	 * 
	 */
	public Controller getController() {
		return controller;
	}
	
	/**
	 * 
	 */
	public MainPanel getMainPanel() {
		return mainPanel;
	}




	public JFrame getWindow() {
		return window;
	}





	public void setWindow(JFrame window) {
		this.window = window;
	}





	public Container getContainer() {
		return container;
	}





	public void setContainer(Container container) {
		this.container = container;
	}





	public JPanel getInitPanel() {
		return initPanel;
	}





	public void setInitPanel(JPanel initPanel) {
		this.initPanel = initPanel;
	}





	public CreateProjectPanel getCreateProject() {
		return createProject;
	}





	public void setCreateProject(CreateProjectPanel createProject) {
		this.createProject = createProject;
	}





	public CreateGroupPanel getCreateGroup() {
		return createGroup;
	}





	public void setCreateGroup(CreateGroupPanel createGroup) {
		this.createGroup = createGroup;
	}





	public void setMainPanel(MainPanel mainPanel) {
		this.mainPanel = mainPanel;
	}





	public void setSignup(SignupPanel signup) {
		this.signup = signup;
	}





	public void setLogin(LoginPanel login) {
		this.login = login;
	}





	public void setController(Controller controller) {
		this.controller = controller;
	}

	

	/**
	 * @return the searchGroup
	 */
	public SearchGroupPanel getSearchGroup() {
		return searchGroup;
	}





	/**
	 * @return the searchProject
	 */
	public SearchProjectPanel getSearchProject() {
		return searchProject;
	}


	
}
