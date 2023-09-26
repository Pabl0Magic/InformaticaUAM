class Cloze(q: String, a: String): Card(q, a) {
    override fun show() {
        print("$question (ENTER to see answer)")
        val first = question.indexOfFirst{it == '*'}
        val last = question.indexOfLast {it == '*'}

        val cont = readln()
        if (cont=="") print("${question.replaceRange(first, (last + 1), answer)} (Type 0 -> Difficult 3 -> Doubt 5 -> Easy): ")
        quality = readln().toInt()
    }

    override fun toString() = "cloze | $question | $answer | $date | $id | $easiness | $repetitions | $interval | $nextPracticeDate\n"

    companion object {
        fun fromString(cad: String): Cloze {
            val chunk = cad.split("|")
            return Cloze(chunk[1], chunk[2])
        }
    }

}