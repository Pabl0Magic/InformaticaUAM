package VoteLanding;

import static org.junit.Assert.*;

import java.util.List;

import org.junit.Test;

import VoteLanding.Notification.TypeNotification;
import VoteLanding.Social.ScopeProject;

public class SystemLandingTest {
	
	private static User Miguel = new User("Miguel", "5678B", "M");
	private static User Carlos = new User("Carlos", "9012C", "C");
	private static User Daniel = new User("Daniel", "3456D", "D");
	private static User Maria = new User("Maria", "7890E", "E");
	Group g1 = new Group("Neighborhood", "Improve conditions for our street", Miguel);
	Group g2 = new Group("UAM", "Improve the teaching quality", Carlos);
	Group g3 = new Group("Games", "Improve conditions for our street", Carlos);
	private static Project p1 = new Social("Children", ScopeProject.International, "A", "The letter A", 3434);
	private static Project p2 = new Social("Children", ScopeProject.National, "B", "The letter B", 453534);
	private static Project p3 = new Social("Children", ScopeProject.International, "C", "The letter C", 434344);
	
	@Test
	public void testGetUser() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addUser(Miguel);
		s1.addUser(Carlos);
		
		List<User> user = s1.getUser();
		assertEquals(2, user.size());
	}

	@Test
	public void testAddUser() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addUser(Miguel);
		
		List<User> user = s1.getUser();
		assertEquals(1, user.size());
	}

	@Test
	public void testGetGroup() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addGroup(g1);
		s1.addGroup(g2);
		s1.addGroup(g3);
		
		List<Group> group = s1.getGroup();
		assertEquals(3, group.size());
	}

	@Test
	public void testAddGroup() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addGroup(g1);
		
		List<Group> group = s1.getGroup();
		assertEquals(1, group.size());
	}

	@Test
	public void testGetProject() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addProject(p1);
		s1.addProject(p2);
		
		List<Project> project = s1.getProject();
		assertEquals(2, project.size());
	}

	@Test
	public void testAddProject() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addProject(p1);
		s1.addProject(p2);
		s1.addProject(p3);
		
		List<Project> project = s1.getProject();
		assertEquals(3, project.size());
	}

	@Test
	public void testGetAdministrator() {
		SystemLanding s1 = new SystemLanding();
		
		Administrator admin = s1.getAdministrator();
		assertEquals("Default" , admin.getName());
		assertEquals("P6gw82z", admin.getPassword());
	}

	@Test
	public void testGiveAffinityReport() {
		SystemLanding s1 = new SystemLanding();
		
		g1.addFollower(Carlos);
		g1.addFollower(Miguel);
		g2.addFollower(Maria);
		g2.addFollower(Daniel);
		
		g1.addProjectCreated(p1);
		g1.addProjectCreated(p2);
		g2.addProjectCreated(p3);
		
		g1.addProjectVoted(p3);
		g2.addProjectVoted(p2);
		
		double aff = s1.giveAffinityReport(g1, g2);
		double result = 2/3;
		assertEquals(result, aff, 0.01);	
	}

	@Test
	public void testSendNotificationUser() {
		SystemLanding s1 = new SystemLanding();
		
		s1.sendNotificationUser(TypeNotification.projectAchieved, Daniel);
		s1.sendNotificationUser(TypeNotification.userUnbanned, Daniel);
		s1.sendNotificationUser(TypeNotification.projectGroup, Daniel);
		List<Notification> notif = Daniel.getNotification();
		assertEquals(3, notif.size());
	}

	@Test
	public void testSendNotificationGroup() {
		SystemLanding s1 = new SystemLanding();
		
		g1.addFollower(Carlos);
		g2.addFollower(Miguel);
		
		s1.sendNotificationGroup(TypeNotification.projectAccepted, g1);
		s1.sendNotificationGroup(TypeNotification.projectExpired, g1);
		List<Notification> notifCarlos = Carlos.getNotification();
		List<Notification> notifMiguel = Miguel.getNotification();
		
		assertEquals(2, notifCarlos.size());
		assertEquals(0, notifMiguel.size());
	}

	@Test
	public void testRemoveProject() {
		SystemLanding s1 = new SystemLanding();
		
		s1.addProject(p1);
		s1.addProject(p2);
		
		p1.setDaysLeft(0);
		p1.setDaysLeft(1);
		
		s1.removeProject(p1);
		s1.removeProject(p2);
		
		List<Project> projectsLeft = s1.getProject();
		assertEquals(1, projectsLeft.size());
	}

}
