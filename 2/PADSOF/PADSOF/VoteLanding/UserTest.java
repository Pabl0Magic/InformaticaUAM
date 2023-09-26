package VoteLanding;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

import VoteLanding.Notification.TypeNotification;
import VoteLanding.User.Acceptance;
import VoteLanding.User.State;

/**
 * Test for User class with Junit
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class UserTest {

	@Test
	public void testGetName() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		String name = u1.getName();
		assertEquals("Pablo", name);
	}

	@Test
	public void testGetDNI() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		String dni = u1.getDNI();
		assertEquals("123456789A", dni);
	}

	@Test
	public void testGetPassword() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		String password = u1.getPassword();
		assertEquals("Hello_World", password);
	}

	@Test
	public void testGetState() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		u1.setState(State.Online);
		State state = u1.getState();
		assertEquals(State.Online, state);
	}

	@Test
	public void testSetState() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		u1.setState(State.Absent);
		State state = u1.getState();
		assertEquals(State.Absent, state);
	}

	@Test
	public void testGetAcceptance() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		u1.setAcceptance(Acceptance.Authorized);
		Acceptance accept = u1.getAcceptance();
		assertEquals(Acceptance.Authorized, accept);
	}

	@Test
	public void testSetAcceptance() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		
		u1.setAcceptance(Acceptance.Rejected);
		Acceptance accept = u1.getAcceptance();
		assertEquals(Acceptance.Rejected, accept);
	}

	@Test
	public void testGetNotification() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		Notification n1 = new Notification(TypeNotification.projectExpired);
		
		u1.addNotification(n1);
		ArrayList<Notification> notification = u1.getNotification();
		assertEquals(1, notification.size());
	}

	@Test
	public void testAddNotification() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		Notification n1 = new Notification(TypeNotification.userBanned);
		
		u1.addNotification(n1);
		ArrayList<Notification> notification = u1.getNotification();
		assertEquals(1, notification.size());
	}

	@Test
	public void testDelNotification() {
		User u1 = new User("Pablo","123456789A", "Hello_World");
		Notification n1 = new Notification(TypeNotification.projectGroup);
		
		u1.addNotification(n1);
		u1.delNotification(n1);
		
		ArrayList<Notification> notification = u1.getNotification();
		assertEquals(0, notification.size());
	}

}
