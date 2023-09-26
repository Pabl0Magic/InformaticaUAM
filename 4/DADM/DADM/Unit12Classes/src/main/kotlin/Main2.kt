fun main(args: Array<String>) {
    class Person {
        var name = "Hellen"
        var age = 25
        var surname: String? = null //lateinit var surname: String
        init {
            println("Hello, I am the primary constructor of Person")
        }
        init {
            println("Hello, I am the second init block")
        }
        fun greet() {
            println("Hello, my name is $name $surname and I am $age years old")
        }
    }

    val friend = Person()
    var cousin = friend
    cousin.name="John"
    //friend.surname = "Casanova"
    friend.greet()
    cousin.greet()
    val parent = Person()

    var uno = (friend === cousin) //true aunque names diferentes
    var dos = (cousin === parent) //false
    var tres = (friend === parent) //false
    println(friend)
    //println(parent)

    //class Animal

    //val dog = Animal()
    //println(dog)



}