class Person(
    val name: String,
    val age: Int
) {
    override fun toString() = "Person(name=$name, age=$age)"
    override fun equals(other: Any?): Boolean {
        if (other == null || other !is Person)
            return false
        return name == other.name && age == other.age
    }

    override fun hashCode(): Int {
        return name.hashCode() + 31 * age
    }

}

fun main() {
    val one = Person("Anne", 25)
    val two = Person("Ana", 25)
    val group = hashSetOf<Person>()

    group += one

    println(group.contains(two))
}