/*
fun main(args: Array<String>) {

    class Person(_name: String) {
        var name: String = _name
        fun greet() = println("My name is $name")
    }

    class Person(var name: String, var isFriend: Boolean) {
            constructor(name:String): this(name, true) {
                println("I am $name's secondary constructor")
            }

        fun greet() {
            if (isFriend) println("My name is $name and we are friends") else println("My name is $name and we are not friends yet")
        }
    }


    Person("Alice", true).greet()
    Person("Peter").greet()
    Person("Helen", false).greet()
}
*/

fun main() {
    class Person(
        var name: String,
        var isFriend: Boolean
    ) {
        init {
            println("Init method")
        }
        fun greet() {
            print("My name is $name ")
            if (isFriend)
                println("and we are friends")
            else
                println("and we are not friends yet")
        }

        constructor(name: String)
                : this(name, isFriend = true) {
            println("I am $name's secondary constructor")
        }
    }

    Person("Peter").greet()
    Person("Helen", false).greet()
}