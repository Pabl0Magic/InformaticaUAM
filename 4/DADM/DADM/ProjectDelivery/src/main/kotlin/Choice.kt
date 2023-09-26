class Choice(q: String, a: String, var c1: String, var c2: String): Card(q, a) {
    override fun show() {
        print("$question -> 1.$c1/2.$c2 (Type the correct answer): ")

        val cont = readln()
        quality = if (cont == answer) 5
        else 0
    }

    override fun toString() = "choice | $question | $answer | $c1 | $c2 | $date | $id | $easiness | $repetitions | $interval | $nextPracticeDate\n"

    companion object {
        fun fromString(cad: String): Choice {
            val chunk = cad.split("|")
            return Choice(chunk[1], chunk[2], chunk[3], chunk[4])
        }
    }
}