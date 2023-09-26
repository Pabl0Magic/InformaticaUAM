import java.io.File

class CountryB(var name: String, var beer: Int)


fun main() {
    val lines: List<String> = File("data/drinks.txt").readLines()
    val countries: MutableList<CountryB> = mutableListOf()
    var chunks: List<String>
    var name: String
    var beer: Int

    for (line in lines) {
        chunks = line.split(",")
        name = chunks[0]
        beer = chunks[1].toInt()
        countries += CountryB(name, beer)
    }

    println("${countries.filter { it.beer > 100 }.size} countries consume over 100 units of beer per person per year")
    /*
    val group = countries.filter { it.beer > 300 }
    for (country in group)
        println("${country.name} : ${country.beer}")

     */
    countries.filter { it.beer > 300 }.forEach { println("${it.name} : ${it.beer}") }
}

