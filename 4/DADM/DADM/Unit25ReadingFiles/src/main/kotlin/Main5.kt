import java.io.File
import kotlin.math.max

class Country(var name: String, var beer: Int, var spirit: Int, var wine: Int)

fun main() {
    val lines: List<String> = File("data/drinks.txt").readLines()
    val countries: MutableList<Country> = mutableListOf()
    var chunks: List<String>
    var name: String
    var beer: Int
    var spirit: Int
    var wine: Int

    //name, beer, spirits, wine, liters alcohol, name
    for (line in lines) {
        chunks = line.split(",")
        name = chunks[0]
        beer = chunks[1].toInt()
        spirit = chunks[2].toInt()
        wine = chunks[3].toInt()
        countries += Country(name, beer, spirit, wine)
    }

    fun selector(country: Country): Int {
        val x = max(country.beer, country.spirit)

        return max(country.wine, x)
    }
    countries.sortByDescending { selector(it) }

    countries.forEach { println("${it.name} : ${selector(it)} = max (${it.beer}, ${it.spirit}, ${it.wine})") }
}