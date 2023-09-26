/*object Demo {
    init {
        println("I am the Demo object")
    }
}

fun main() {
    println(Demo.toString())
}
*/

class Student(
    var name: String,
    var score1: Double,
    var score2: Double
)

object Scores {
    var students = mutableListOf<Student>()
    fun calculate(): Unit {
        // Add your code here
        for (i in students) {
            println("${i.name} -> ${"%.2f".format((i.score1*0.4)+(i.score2*0.6))}") // Para que solo ponga dos decimales
        }
    }
}

object StudentComparator : Comparator<Student> {
    override fun compare(e1: Student?, e2: Student?): Int {
        if (((e1!!.score1*0.4)+(e1!!.score2*0.6)) < ((e2!!.score1*0.4)+(e2!!.score2*0.6)))
            return -1
        else
            return 1
    }
}

fun main() {
    Scores.students.add(Student("Laura", 2.4, 7.6))
    Scores.students.add(Student("Kevin", 5.8, 8.3))

    val student1 = Student("Peter", 5.8, 8.3)
    val student2 = Student("Alice", 6.2, 7.6)
    var list = mutableListOf<Student>(student1, student2)

    list.sortWith(StudentComparator)
    list.forEach { println("${it.name} -> ${it.score1}") }
    Scores.calculate()
}