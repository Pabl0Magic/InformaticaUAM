import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import java.util.*
import java.io.File

class Deck (var name: String, var id: String = UUID.randomUUID().toString()) {
    private val cards = mutableListOf<Card>()
    private val dateFormat: DateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd")

    fun addCard() {
        println("Adding card to $name deck")
        print("Type the type (0 -> Card 1 -> Cloze 2 -> Choice): ")
        val q: String
        val a: String

        when (readln().toInt()) {
            0 -> {
                print("Type the question: ")
                q = readln()
                print("Type the answer: ")
                a = readln()

                val c = Card(q, a)
                cards.add(c)
            }
            1 -> {
                print("Type the question: ")
                q = readln()
                print("Type the answer: ")
                a = readln()

                val c = Cloze(q, a)
                cards.add(c)
            }
            else -> {
                print("Type the question: ")
                q = readln()
                print("Type choice 1: ")
                val c1 = readln()
                print("Type choice 2: ")
                val c2 = readln()
                print("Type answer: ")
                a = readln()

                val c = Choice(q, a, c1, c2)
                cards.add(c)
            }
        }

        println("Card added successfully")
    }

    fun listCards() {
        if (cards.isEmpty()) println("There are no cards")
        for(i in cards) {
            if (i is Choice) {
                println("${i.question} -> ${i.c1}/${i.c2} -> ${i.answer}")
            } else {
                println("${i.question} -> ${i.answer}")
            }
        }
    }

    fun simulate(period: Int) {
        println("Simulation of deck $name:")
        val now = LocalDateTime.now()
        for (i in 0..period) {
            val newdate = now.plusDays(i.toLong())
            println(newdate.format(dateFormat))
            for (j in cards) {
                if (i == 0 || newdate == j.nextPracticeDate) {
                    j.show()
                    j.update(newdate)
                    j.details()
                }
            }
        }
    }

    fun writeCards(name: String) {
        val f = File(name)

        for (c in cards)
            f.appendText(c.toString())
    }

    fun readCards(name: String) {
        val lines: List<String> = File(name).readLines()
        for (l in lines) {
            if (l.contains("card")) {
                cards.add(Card.fromString(l))
            } else if (l.contains("cloze")) {
                cards.add(Cloze.fromString(l))
            } else {
                cards.add(Choice.fromString(l))
            }
        }
    }

    fun deleteCard(quest: String) {
        val aux = cards.toList()
        for (c in aux) {
            if (c.question == quest) {
                cards.remove(c)
            }
        }
    }
}