import java.io.File
import java.io.FileNotFoundException

fun main() {
    try {
        val lines: List<String> = File("data/drinks.txt").readLines()
        println("The number of lines in the file is ${lines.size}")

        for (line in lines)
            if (line.contains("Europe"))
                println(line)

        //lines.forEach { if (it.contains("Europe")) print(it) }
        //lines.filter { it.contains("Europe") }.forEach { println(it) }
    } catch (e: FileNotFoundException) {
        println("File not Found. Try again")
    }

}
