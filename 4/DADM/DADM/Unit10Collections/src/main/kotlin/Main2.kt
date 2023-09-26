fun main(args: Array<String>) {
    var listOfInt: List<Int> = listOf(3, 7, -1) //Immutable list
    println(listOfInt)

    var mylist: List<Any> = listOf("Hola", 3)
    println(mylist)

    var catalonia = listOf("Barcelona", "Gerona", "Lérida", "Tarragona", "Valencia")
    println(catalonia.getOrElse(4) { "city not included" })

    var cat = listOf("Barcelona", "Gerona", "Lérida", "Tarragona")
    println(cat.getOrNull(4)?: "No existe")
}
