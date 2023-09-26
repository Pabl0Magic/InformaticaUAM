package VoteLanding;
import java.util.*;

/**
 * Group class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Group {
    private String name;
    private String desc;
    private User creator;
    private ArrayList<Project> projectsVoted;
    private ArrayList<Project> projectsCreated;
    private ArrayList<Subgroup> child;
    private ArrayList<User> follower;

    public Group(String name, String desc, User creator) {
        this.name = name;
        this.desc = desc;
        this.creator = creator;
        
        projectsVoted = new ArrayList<>();
        projectsCreated = new ArrayList<>();
        child = new ArrayList<>();
        follower = new ArrayList<>();
    }
    
    /**
     * Getter for the name of Group
     * @return name
     */
    public String getName(){
        return name;
    }
    
    /**
     * Getter for the description of Group
     * @return desc
     */
    public String getDescription(){
        return desc;
    }
    
    /**
     * Getter for the creator of Group
     * @return creator
     */
    public User getCreator() {
        return creator;
    }
    
    /* Projects voted */
    
    /**
     * Getter for the sorted set of projects voted of Group
     * @return projectsVoted
     */
    public ArrayList<Project> getProjectsVoted(){
        return projectsVoted;
    }
    
    /**
     * Adds a new project to the set of voted projects
     * @param newProject
     */
    public void addProjectVoted(Project newProject) {
        projectsVoted.add(newProject);
        newProject.updateVotes();
    }
    
    /**
     * Deletes a project from the set of voted projects
     * @param project
     */
    public void delProjectVoted(Project project){
        projectsVoted.remove(project);
        project.updateVotes();
    }
    
    /**
     * Checks if the project passed as parameter is contained in the voted projects set 
     * @param project
     * @return true or false
     */
    public boolean containProjectVoted(Project project){
        return projectsVoted.contains(project);
    }
    
    /* Projects created */
    
    /**
     * Getter of projects created of Groups
     * @return set of projects created
     */
    public ArrayList<Project> getProjectsCreated(){
        return projectsCreated;
    }
    
    /**
     * Adds a new project to the projects created set
     * @param newProject
     */
    public void addProjectCreated(Project newProject){
        projectsCreated.add(newProject);
        newProject.updateVotes();
    }
    
    /**
     * Deletes a projects from the project created set
     * @param project
     */
    public void delProjectCreated(Project project){
        projectsCreated.remove(project);
        project.updateVotes();
    }
    
    /**
     * Checks if a project is contained in the created project set
     * @param project
     * @return true or false
     */
    public boolean containProjectCreated(Project project){
        return projectsCreated.contains(project);
    }
    
    /* Child */
    
    /**
     * Getter for the child set of Group
     * @return set of childs
     */
    public ArrayList<Subgroup> getChild() {
        return child;
    }
    
    /**
     * Adds a new child to the child set
     * @param newChild
     */
    public void addChild(Subgroup newChild){
        child.add(newChild);
    }
    
    /**
     * Deletes a child from the child set
     * @param childDel
     */
    public void delChild(Subgroup childDel){
        child.remove(childDel);
    }
    
    /**
     * Checks if a subgroup is contained in the child set
     * @param childCon
     * @return true or false
     */
    public boolean containChild(Subgroup childCon){
        return child.contains(childCon);
    }
    
    /* Follower */
    
    /**
     * Getter for the set of followers of Group
     * @return set of followers
     */
    public ArrayList<User> getFollower(){
        return follower;
    }
    
    /**
     * Adds a new user to the follower set
     * @param newFollower
     */
    public void addFollower(User newFollower){
        follower.add(newFollower);
        for(Project p: projectsVoted) {
        	p.updateVotes();
        }
        for(Project p: projectsCreated) {
        	p.updateVotes();
        }
    }
    
    /**
     * Deletes a user from the follower set
     * @param followerDel
     */
    public void delFollower(User followerDel){
        follower.remove(followerDel);
        for(Project p: projectsVoted) {
        	p.updateVotes();
        }
        for(Project p: projectsCreated) {
        	p.updateVotes();
        }
    }
    /**
     * Checks if a user is contained in the follower set
     * @param followerCon
     * @return true or false
     */
    public boolean containFollower(User followerCon){
        return follower.contains(followerCon);
    }
}