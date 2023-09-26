package VoteLanding;


import VoteLanding.Infraestructural.District;
import VoteLanding.Infraestructural.ImageKind;
import VoteLanding.Notification.TypeNotification;
import VoteLanding.Project.Status;
import VoteLanding.Social.ScopeProject;
import VoteLanding.User.Acceptance;
import VoteLanding.User.State;

/**
 * Test for the whole project
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class MainTest {
		
	private static User Pablo, Carlos, Miguel, Daniel, Maria, Ana, Sofia, Angel;
	private static Group g1, g2;
	private static Infraestructural i1;
	private static Social s1;
	private static Subgroup sg1, sg2, sg3;
	private static Notification notifBan, notifAccepted;
	private static SystemLanding MySystem;
	
	public static void main(String[] args) throws Exception {
	
	System.out.println("Loading system");
	MySystem = SystemLanding.load();
	
	System.out.println("Creating users and adding them to the system:");
	
	Pablo = new User("Pablo", "00000Z", "Hello_World");
	MySystem.addUser(Pablo);
	Pablo.setAcceptance(Acceptance.Authorized);
	Pablo.setState(State.Online);
	System.out.println("User " + Pablo.getName() + " created.\nStatus: " + Pablo.getState() + "\tAcceptance: " + Pablo.getAcceptance());
	
	Carlos = new User("Carlos", "12345A", "Hello_");
	MySystem.addUser(Carlos);
	Carlos.setAcceptance(Acceptance.Authorized);
	Carlos.setState(State.Online);
	System.out.println("User " + Carlos.getName() + " created.\nStatus: " + Carlos.getState() + "\tAcceptance: " + Carlos.getAcceptance());
	
	Miguel = new User("Miguel", "67890B", "World_");
	MySystem.addUser(Miguel);
	Miguel.setAcceptance(Acceptance.Authorized);
	Miguel.setState(State.Absent);
	System.out.println("User " + Miguel.getName() + " created.\nStatus: " + Miguel.getState() + "\tAcceptance: " + Miguel.getAcceptance());
	
	Daniel = new User("Daniel", "11111C", "D");
	MySystem.addUser(Daniel);
	Daniel.setAcceptance(Acceptance.Pending);
	Daniel.setState(State.Offline);
	System.out.println("User " + Daniel.getName() + " created.\nStatus: " + Daniel.getState() + "\tAcceptance: " + Daniel.getAcceptance());
	
	Ana = new User("Ana", "51515N", "A");
	MySystem.addUser(Ana);
	Ana.setAcceptance(Acceptance.Authorized);
	Ana.setState(State.Online);
	System.out.println("User " + Ana.getName() + " created.\nStatus: " + Ana.getState() + "\tAcceptance: " + Ana.getAcceptance());
	
	Sofia = new User("Sofia", "79234S", "S");
	MySystem.addUser(Sofia);
	Sofia.setAcceptance(Acceptance.Rejected);
	Sofia.setState(State.Offline);
	System.out.println("User " + Sofia.getName() + " created.\nStatus: " + Sofia.getState() + "\tAcceptance: " + Sofia.getAcceptance());
	
	Angel = new User("Angel", "13489G", "G");
	MySystem.addUser(Angel);
	Angel.setAcceptance(Acceptance.Authorized);
	Angel.setState(State.Online);
	System.out.println("User " + Angel.getName() + " created.\nStatus: " + Angel.getState() + "\tAcceptance: " + Angel.getAcceptance());
	
	Maria = new User("Maria", "99999M", "M");
	MySystem.addUser(Maria);
	Maria.setAcceptance(Acceptance.Authorized);
	Maria.setState(State.Online);
	System.out.println("User " + Maria.getName() + " created.\n\n");
	
	System.out.println("User " + Pablo.getName() + " will create a group.");
	g1 = new Group("Videogames", "Group for increasing the importance of the videogames.", Pablo);
	MySystem.addGroup(g1);
	System.out.println("Group created: " + g1.getName() + "\tCreator: " + g1.getCreator().getName());
	System.out.println("Descrpition of the group: " + g1.getDescription());
	
	System.out.println("User " + Carlos.getName() + " will create a group.");
	g2 = new Group("Tarantino fans", "Group for fans of Quentin Tarantino fans.", Carlos);
	MySystem.addGroup(g2);
	System.out.println("Group created: " + g2.getName() + "\tCreator: " + g2.getCreator().getName());
	System.out.println("Description of the group: " + g2.getDescription());
	
	System.out.println("User " + Pablo.getName() + " will create a subgroup.");
	sg1 = new Subgroup("League of Legends", "LoL players only", Pablo, g1, 1);
	g1.addChild(sg1);
	System.out.println("Subgroup created: " + sg1.getName() + "\tCreator: " + sg1.getCreator().getName());
	System.out.println("Description of the subgroup: " + sg1.getDescription());
	
	System.out.println("User " + Pablo.getName() + " will create a subgroup.");
	sg2 = new Subgroup("Reservoir Dogs", "Trying to get the sequel", Pablo, g2, 1);
	g2.addChild(sg2);
	System.out.println("Subgroup created: " + sg2.getName() + "\tCreator: " + sg2.getCreator().getName());
	System.out.println("Description of the subgroup: " + sg2.getDescription());
	
	System.out.println("User " + Carlos.getName() + " will create a subgroup.");
	sg3 = new Subgroup("Call of Duty", "COD players only", Carlos, g1, 1);
	g1.addChild(sg3);
	System.out.println("Subgroup created: " + sg3.getName() + "\tCreator: " + sg3.getCreator().getName());
	System.out.println("Description of the subgroup: " + sg3.getDescription());
	
	System.out.println("Adding followers to the groups.");
	g2.addFollower(Pablo);
	g1.addFollower(Carlos);
	g2.addFollower(Miguel);
	
	System.out.println("Followers of group " + g1.getName());
	for(User u: g1.getFollower()) {
		System.out.println(u.getName());
	}
	System.out.println("\n");
	
	System.out.println("Followers of group " + g2.getName());
	for(User u: g2.getFollower()) {
		System.out.println(u.getName());
	}
	System.out.println("\n");
	
	System.out.println("Addign follower to a subgroup.");
	sg1.addFollower(Ana);
	for(User u: sg1.getFollower()) {
		System.out.println(u.getName());
	}
	System.out.println("\n");
	
	System.out.println("Group " + g2.getName() + " will create a project");
	i1 = new Infraestructural(District.PuenteDeVallecas, ImageKind.PNG, "MegaServer", "We will try to get a massive server to play LoL", 300);
	MySystem.addProject(i1);
	g1.addProjectCreated(i1);
	i1.voteProjectGroup(g1);
	g1.addProjectVoted(i1);
	System.out.println("Project: " + i1.getName() + "\tDescription: " + i1.getDesc());
	
	//Should print 2
	System.out.println("Project " + i1.getName() + " has " + i1.getNumVotes() + " votes.");
	g1.addFollower(Angel);
	//Should print 3
	System.out.println("Now since " + Angel.getName() + " has joined the group, the number of votes is " + i1.getNumVotes());
	System.out.println(Ana.getName() + "will vote the project individually");
	i1.voteProjectIndv(Ana);
	//Should print 4
	System.out.println("Now since " + Ana.getName() + " has voted, the number of votes is " + i1.getNumVotes());
	
	//Should print 3
	System.out.println("We will delete one follower.");
	g1.delFollower(Angel);
	System.out.println("Now since " + Angel.getName() + " has left the group, the number of votes is " + i1.getNumVotes());
	
	s1 = new Social("Society", ScopeProject.International, "Reservoir Dogs Sequel", "We will get our sequel", 150);
	s1.setStatus(Status.Rejected);
	//The project should be in Rejected status
	System.out.println("Project in status: " + s1.getStatus());
	
	//Affinity report should be 0
	double affinity = MySystem.giveAffinityReport(g1, g2);
	System.out.println("Affinity report result: " + affinity);
	
	System.out.println("A notification will be created.");
	notifBan = new Notification(TypeNotification.userBanned);
	System.out.println("Now a notification will be sent to a user.");
	MySystem.sendNotificationUser(TypeNotification.userBanned, Daniel);
	System.out.println("Title: " + notifBan.getTitle() + "\tBody: " + notifBan.getBody());
	
	System.out.println("Creating another notification.");
	notifAccepted = new Notification(TypeNotification.projectAccepted);
	System.out.println("Now a notification will be sent to a group.");
	MySystem.sendNotificationGroup(TypeNotification.projectAccepted, g2);
	for (User u: g2.getFollower()) {
		System.out.println(u.getName() + "! You have received a notifiction");
	}
	System.out.println("Title: " + notifAccepted.getTitle() + "\tBody: " + notifAccepted.getBody());
	
	System.out.println("Send " + i1.getName() + " to an external association.");
	i1.sendExternalAssociation();
	System.out.println("Project with external ID: " + i1.getCCId());
	System.out.println("In 1-7 days the verification will be done!");
	MySystem.save();
	}
}
