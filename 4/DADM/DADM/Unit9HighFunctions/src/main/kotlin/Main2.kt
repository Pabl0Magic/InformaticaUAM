/*fun main() {

    val count: (String, Char) -> Int = { text, letter ->
        var cont = 0
        var numLetter = 0
        for (c in text)
            if (c == letter)
                numLetter++
            cont++
        cont
        numLetter
    }

    println("The caracter a appears ${count("alameda", 'a')} in alameda")
}
*/
fun main() {

    var count: (String, (Char) -> Boolean) -> Int = { text, filter ->
        var cont: Int = 0
        for (c in text)
            if (filter(c))
                cont++
        cont
    }

    // Add your code here
    /*val filter: (Char) -> Boolean = {
        it == 'a'
    }*/

    //println(count("Alameda", filter))
    //count("Alameda", { it == 'a' })
    println(count("Alameda") { it == 'a' })
}
