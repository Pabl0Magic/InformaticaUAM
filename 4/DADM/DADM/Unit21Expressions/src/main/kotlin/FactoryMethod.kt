class Student2 private constructor(
    var name: String,
    var score: Double
) {
    companion object {
        fun newFinalStudent(
            name: String,
            score: Double
        ) = Student2(name, score)

        fun newContinuousStudent(
            name: String,
            score1: Double,
            score2: Double
        ) = Student2(name, 0.4 * score1 + 0.6 * score2)

        // Add a third factory method
        fun threeScores(
            name: String,
            score1: Double,
            score2: Double,
            score3: Double
        ) = Student2(name, 0.3 * score1 + 0.3 * score2 + 0.4 * score3)
    }
}

fun main() {
    val david = Student2.newFinalStudent("David", 7.2)
    val susan = Student2.newContinuousStudent("Susan", 5.6, 7.8)
    val olivia = Student2.threeScores("Olivia", 3.6, 4.5, 7.1)

    println("${david.name} has a score of ${david.score}")
    println("${susan.name} has a score of ${susan.score}")
    println("${olivia.name} has a score of ${olivia.score}")

    // Call the new factory method
}