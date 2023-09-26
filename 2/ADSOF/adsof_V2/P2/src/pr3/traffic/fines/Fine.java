package pr3.traffic.fines;

/**
 * Fine Class
 * This class manages the creation and printing of fines.
 * Stores the plate, type and points taken.
 */
public class Fine {
    String numberPlate;
    String fineType;
    int points;

    /**
	 * @brief Fine constructor
	 * 
	 * @param plate Vehicle plate
	 * @param type Fine type
	 * @param points Number of points substracted
	 */
    public Fine(String plate, String type, int points) {
        this.numberPlate = plate;
        this.fineType = type;
        this.points = points;
    }

    /**
     * Transforms fine to string
     * @return fine in string
     */
    @Override
    public String toString(){
        return "Fine [plate="+numberPlate+", Fine type="+fineType+", points="+points+"]";
    }
}