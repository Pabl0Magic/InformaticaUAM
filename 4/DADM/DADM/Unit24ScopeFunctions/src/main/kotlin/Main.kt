fun main() {
    val name = "data.txt"

    name.apply {
        println(removeSuffix(".txt"))
    }

    val cities = mutableListOf("Burgos", "Ávila", "Pontevedra", "Santander")
    cities.filter { it.length > 5 }.let {
        println("${it.size} cities pass the filter:")
        println(it)
    }

    val cities2 = mutableListOf("Burgos", "Ávila", "Pontevedra", "Santander")
    cities2.filter { it.length > 5 }.run {
        println("The number of cities is ${size}:")
        println(this)
    }

    val name2 = " Helen"

    with(name2) {
        println(trim())
        println(length)
    }



}

class Student(var name: String) {
    var age: Int = 0
    var score: Int = 0
    fun greet() = println("My name is $name and I'm $age years old")
    fun report() = println("My score is $score")
}

val student = Student("Helen").also {
    it.age = 21
    it.score = 78
    it.greet()
    it.report()
}

val student2 = Student("John").apply {
    age = 25
    this.score = 54
    greet()
    this.report()
}