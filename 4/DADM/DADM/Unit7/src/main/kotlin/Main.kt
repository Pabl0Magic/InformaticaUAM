import java.lang.Exception

fun readInteger() : Int {
    print("Enter an integer between 1 and 3: ")
    val value = readLine()?.toIntOrNull() ?: throw NumberFormatException("Integer format incorrect")
    if (value !in 1..3)
        throw Exception("Invalid Integer")
    return value
}

fun readRowColumn() {
    val row = readInteger()
    val column = readInteger()
    println("Player moves to ($row, $column)")
}

fun main() {
    try {
        readRowColumn()
    } catch (e: Exception) {
        println(e.message)
    }
}

/*fun readInteger(): Int {
    print("Enter an integer between 1 and 3: ")
    val value = readLine()?.toIntOrNull() ?: throw NumberFormatException("Incorrect integer format")
    if (value !in 1..3)
        throw Exception("Invalid Integer")
    return value
}

fun readRowColumn() {
    val row = readInteger()
    val column = readInteger()
    println("Player moves to ($row, $column)")
}

fun main() {
    try {
        readRowColumn()
    } catch (e: NumberFormatException) {
        println("NumberFormatException")
    } catch (e: Exception) {
        println("Invalid integer value")
    }
}
*/