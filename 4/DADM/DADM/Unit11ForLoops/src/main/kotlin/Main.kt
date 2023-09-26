fun main() {
    print("Type an integer greater than 1: ")
    val num = readLine()!!.toInt()

    if (isPerfect(num) == 1) {
        return println("$num is perfect")
    }

    println("$num is not perfect")

}

fun isPerfect(n: Int): Int {
    var x = 0
    for (i in 1 until n) {
        if (n % i == 0) {
            x += i
        }
    }

    if (x == n) {
        return 1
    }

    return 0
}