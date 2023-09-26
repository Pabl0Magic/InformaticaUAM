import java.io.File

fun main() {
    val lines: List<String> = File("data/drinks.txt").readLines()
    var chunks: List<String>
    var name: String
    var beer: Int

    for (line in lines) {
        chunks = line.split(",")
        name = chunks[0]
        beer = chunks[1].toInt()
        println("$name $beer")
    }
}