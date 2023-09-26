fun main() {

    /*for (i in 7 downTo 1)
        print("$i ")
     */
    /*
    for (i in 7 downTo 1 step 2)
        print("$i ")

     */
    /*
    for (i in 'm' downTo 'f' step 2)
        print("$i ")

     */
    /*
    for (i in 1 until 5)
    print("$i ")

     */
    val list = listOf<Int>(-3, 5, 6)

    for (i in list.indices.reversed())
        print("${list[i]} ")

}

/*
fun main() {
('a'..'f').forEach(::print)
}

 */