 package VoteLanding;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

import VoteLanding.Social.ScopeProject;

/**
 * Test for Group class with Junit
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class GroupTest {
	
	private static User Pablo = new User("Pablo", "1234A", "P");
	private static User Miguel = new User("Miguel", "5678B", "M");
	private static User Carlos = new User("Carlos", "9012C", "C");
	private static Project Book = new Social("Children", ScopeProject.International, "A", "The letter A", 1500);
	private static Project Pencil = new Social("Children", ScopeProject.International, "B", "The letter B", 20000);
	private static Project Mouse = new Social("Children", ScopeProject.International, "C", "The letter C", 1000);
	private static Subgroup Door1 = new Subgroup("A", "The letter A", Pablo, null, 1);
	private static Subgroup Door2 = new Subgroup("B", "The letter B", Pablo, null, 1);
	private static Subgroup Door3 = new Subgroup("C", "The letter C", Pablo, null, 1);
	
	@Test
	public void testGetName() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		String name = g1.getName();
		assertEquals("Neighborhood", name);
	}

	@Test
	public void testGetDescription() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		String desc = g1.getDescription();
		assertEquals("Improve conditions for our street", desc);
	}

	@Test
	public void testGetCreator() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		User user = g1.getCreator();
		assertEquals(Pablo, user);
	}

	@Test
	public void testGetProjectsVoted() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectVoted(Book);
		g1.addProjectVoted(Pencil);
		g1.addProjectVoted(Mouse);
		
		ArrayList<Project> vote = g1.getProjectsVoted();
		assertEquals(3, vote.size());
	}

	@Test
	public void testAddProjectVoted() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectVoted(Book);
		g1.addProjectVoted(Pencil);
		
		ArrayList<Project> vote = g1.getProjectsVoted();
		assertEquals(2, vote.size());
	}

	@Test
	public void testDelProjectVoted() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectVoted(Book);
		g1.addProjectVoted(Pencil);
		g1.addProjectVoted(Mouse);
		g1.delProjectVoted(Book);
		g1.delProjectVoted(Mouse);
		
		ArrayList<Project> vote = g1.getProjectsVoted();
		assertEquals(1, vote.size());
	}

	@Test
	public void testContainProjectVoted() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectVoted(Pencil);
		g1.addProjectVoted(Mouse);
		
		boolean voted = g1.containProjectVoted(Mouse);
		boolean votedWrong = g1.containProjectVoted(Book);
		assertTrue(voted);
		assertFalse(votedWrong);
	}

	@Test
	public void testGetProjectsCreated() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectCreated(Book);
		g1.addProjectCreated(Pencil);
		
		ArrayList<Project> create = g1.getProjectsCreated();
		assertEquals(2, create.size());
	}

	@Test
	public void testAddProjectCreated() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectCreated(Book);
		g1.addProjectCreated(Pencil);
		g1.addProjectCreated(Mouse);
		
		ArrayList<Project> create = g1.getProjectsCreated();
		assertEquals(3, create.size());
	}

	@Test
	public void testDelProjectCreated() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectCreated(Book);
		g1.addProjectCreated(Pencil);
		g1.addProjectCreated(Mouse);
		g1.delProjectCreated(Pencil);
		g1.delProjectCreated(Book);
		g1.delProjectCreated(Mouse);
		
		ArrayList<Project> create = g1.getProjectsCreated();
		assertEquals(0, create.size());
	}

	@Test
	public void testContainProjectCreated() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addProjectCreated(Book);
		g1.addProjectCreated(Pencil);
		
		boolean create = g1.containProjectCreated(Pencil);
		boolean createWrong = g1.containProjectCreated(Mouse);
		assertTrue(create);
		assertFalse(createWrong);
	}

	@Test
	public void testGetChild() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addChild(Door1);
		g1.addChild(Door2);
		g1.addChild(Door3);
		
		ArrayList<Subgroup> child = g1.getChild();
		assertEquals(3, child.size());
	}

	@Test
	public void testAddChild() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addChild(Door1);
		g1.addChild(Door2);
		
		ArrayList<Subgroup> child = g1.getChild();
		assertEquals(2, child.size());
	}

	@Test
	public void testDelChild() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addChild(Door1);
		g1.addChild(Door2);
		g1.addChild(Door3);
		g1.delChild(Door2);
		g1.delChild(Door3);
		
		ArrayList<Subgroup> child = g1.getChild();
		assertEquals(1, child.size());
	}

	@Test
	public void testContainChild() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addChild(Door1);
		g1.addChild(Door3);
		
		boolean child = g1.containChild(Door3);
		boolean childWrong = g1.containChild(Door2);
		assertTrue(child);
		assertFalse(childWrong);
	}

	@Test
	public void testGetFollower() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Miguel);
		g1.addFollower(Carlos);
		
		ArrayList<User> follower = g1.getFollower();
		assertEquals(2, follower.size());
	}

	@Test
	public void testAddFollower() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Carlos);
		
		ArrayList<User> follower = g1.getFollower();
		assertEquals(1, follower.size());
	}

	@Test
	public void testDelFollower() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Miguel);
		g1.addFollower(Carlos);
		g1.delFollower(Miguel);
		g1.delFollower(Carlos);
		
		ArrayList<User> follower = g1.getFollower();
		assertEquals(0, follower.size());
	}

	@Test
	public void testContainFollower() {
		Group g1 = new Group("Neighborhood", "Improve conditions for our street", Pablo);
		
		g1.addFollower(Miguel);
		g1.addFollower(Carlos);
		
		boolean follow = g1.containFollower(Miguel);
		boolean followWrong = g1.containFollower(Pablo);
		assertTrue(follow);
		assertFalse(followWrong);
	}

}
