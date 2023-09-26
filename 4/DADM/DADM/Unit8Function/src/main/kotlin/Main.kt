fun main() {
    print("Type an integer: ")
    val age = readLine()!!.toInt()
    var legalAge: (Int) -> Boolean

    legalAge = {
        it < 18
    }

    if (legalAge(age))
        println("You are under 18 years old")
    else
        println("You are over 18 years old")
}