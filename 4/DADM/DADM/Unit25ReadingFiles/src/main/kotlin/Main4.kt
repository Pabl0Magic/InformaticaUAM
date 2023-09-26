import java.io.File

class CountryW(var name: String, var beer: Int, var wine: Int)

fun main() {
    val lines: List<String> = File("data/drinks.txt").readLines()
    val countries: MutableList<CountryW> = mutableListOf()
    var chunks: List<String>
    var name: String
    var beer: Int
    var wine: Int

    for (line in lines) {
        chunks = line.split(",")
        name = chunks[0]
        beer = chunks[1].toInt()
        wine = chunks[3].toInt()
        countries += CountryW(name, beer, wine)
    }

    countries.sortedByDescending { it.wine }.subList(0, 10).let {
        it.forEach { println("${it.name} : ${it.wine}") }
    }
}
