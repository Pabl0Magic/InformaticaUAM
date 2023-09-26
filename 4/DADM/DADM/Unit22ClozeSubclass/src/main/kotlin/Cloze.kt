class Cloze(var q: String, var a: String): Card(q, a) {
    override fun show() {
        print("$question (ENTER to see answer)")
        var first = question.indexOfFirst{it == '*'}
        var last = question.indexOfLast {it == '*'}

        val cont = readln()
        if (cont=="") print("${question.replaceRange(first, (last + 1), answer)} (Type 0 -> Difficult 3 -> Doubt 5 -> Easy): ")
        quality = readln()
    }
}