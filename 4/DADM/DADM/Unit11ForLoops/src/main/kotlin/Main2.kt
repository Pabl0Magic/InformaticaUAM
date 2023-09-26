fun main() {
    val number: Int

    print("Type an integer: ")
    number = readLine()!!.toInt()

    if (number in 1..5)
        println("$number is in [1, 5]")
    else
        println("$number is not in [1, 5]")
}

/*
fun main() {
    val number: Int
    val range = IntRange(1,5)

    print("Type a number: ")
    number = readLine()!!.toInt()

    if (number in range)
        println("$number is in [1, 5]")
    else
        println("$number is not in [1, 5]")
}

 */