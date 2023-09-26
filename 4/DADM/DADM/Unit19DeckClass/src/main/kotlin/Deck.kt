import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import java.util.*

class Deck (var name: String, var id: String = UUID.randomUUID().toString()) {
    val cards = mutableListOf<Card>()
    val dateFormat = DateTimeFormatter.ofPattern("yyyy-MM-dd")

    fun addCard() {
        println("Adding card to deck")
        print("Type the question: ")
        var q = readln()
        print("Type the answer: ")
        var a = readln()

        var c = Card(q, a)
        cards.add(c)

        println("Card added succesfully")
    }

    fun listCards() {
        for(i in cards) {
            println("${i.question} -> ${i.answer}")
        }
    }

    fun simulate(period: Int) {
        println("Simulation of deck $name:")
        var now = LocalDateTime.now()
        for (i in 0..period) {
            val newdate = now.plusDays(i.toLong())
            println(newdate.format(dateFormat))
            for (j in cards) {
                if (i.toInt() == 0 || newdate == j.nextPracticeDate) {
                    j.show()
                    j.update(newdate)
                    j.details()
                }
            }
        }
    }
}