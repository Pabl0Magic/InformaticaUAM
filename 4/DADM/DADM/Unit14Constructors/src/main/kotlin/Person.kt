fun main() {
    class Person(
        var name: String,
        var age: Int
    ) {
        fun greet() = println("My name is $name")
    }

    // Add your code here
    var hellen = Person("Hellen", 15)
    var john = Person("John", 37)
    var mike = Person("Mike", 24)
    var peopleList = listOf<Person>(hellen, john, mike)
    println(peopleList.maxByOrNull { it.age }?.name)
}

/*
fun main() {
    class Person (var name: String, var age: Int) {
        fun greet() = println("My name is $name")
    }

    val friends = mutableListOf<Person>()

    friends += Person("Bob", 34)
    friends += Person("Alice", 23)
    friends += Person("David", 51)

    val person = friends.maxByOrNull { it.age }

    println("The oldest is ${person?.name}")
}

 */