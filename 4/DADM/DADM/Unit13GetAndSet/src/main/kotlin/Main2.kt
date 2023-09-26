fun main(args: Array<String>) {
    class Person {
        var name = "Helen"
            //get() = name.uppercase( //StackOverflowError
            //get() = field.uppercase() //HELEN
            get() {
                println("Method get invoked")
                return field.uppercase()
            }
            set(value) {
                field = value.trim().uppercase()
            }

    }

    val friend = Person()
    friend.name = "   john"
    //println("My name is ${Person().name}")
    println("My name is ${friend.name}")

    /*
    class Persona {
        var name = "Lola"
            private set
    }

    Persona().name = "Pedro"
     */
}