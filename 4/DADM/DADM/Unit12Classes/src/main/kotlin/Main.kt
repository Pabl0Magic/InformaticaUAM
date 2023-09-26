fun main() {
    class Person {
        lateinit var name: String
        lateinit var lastname: String
        lateinit var phonenumber: String
        fun assign(n: String, a: String, t: String) {
            name = n
            lastname = a
            phonenumber = t
        }
    }

    var hellen = Person()
    var john = Person()
    var mike = Person()

    hellen.assign("Hellen", "Smith", "657483921")
    john.assign("John", "Smith", "678230941")
    mike.assign("Mike", "Lenon", "691234567")

    var personList = listOf<Person>(hellen, john, mike)

    print("Who are you looking for? Type their last name: ")
    var last = readLine()
    for (i in personList ) {
        if (i.lastname == last) {
            println("${i.name} ${i.lastname} ${i.phonenumber}")
        }
    }
}

/*
fun main() {
    class Person {
        lateinit var first_name: String
        lateinit var last_name: String
        lateinit var phone: String
        fun assign(n: String, a: String, t: String) {
            first_name = n
            last_name = a
            phone = t
        }
    }

    val first = Person()
    first.assign("Helen", "Smith", "651237153")

    val second = Person()
    second.assign("Joan", "Smith", "345123513")

    val third = Person()
    third.assign("Peter", "Brown", "725651298")

    val list = listOf<Person>(first, second, third)

    print("Who are you looking for? Type their last name: ")
    val lastName = readLine()!!.toString()

    val found = list.filter { it.last_name == lastName }
    found.forEach { print("${it.first_name} ${it.last_name} ${it.phone} \n") }
}

 */