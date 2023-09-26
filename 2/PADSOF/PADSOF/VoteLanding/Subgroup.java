package VoteLanding;

/**
 * Subgroup class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Subgroup extends Group{
    private Group parent;
    private int level;

    public Subgroup(String name, String desc, User creator, Group parent, int level){
        super(name, desc, creator);
        this.parent=parent;
        this.level=level;
    }
    
    /**
     * Getter for theparent of a subgroup
     * @return parent
     */
    public Group getParent(){
        return parent;
    }

    /**
     * Getter for the level of a subgroup
     * @return level
     */	
    public int getLevel(){
        return level;
    }
}
