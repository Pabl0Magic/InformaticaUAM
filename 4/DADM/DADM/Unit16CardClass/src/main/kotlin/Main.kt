import java.lang.Double.max
import java.time.*
import java.util.*
import java.math.*
import java.time.format.DateTimeFormatter

class Card(q: String, a: String) {
    var question: String = q
    var answer: String = a
    var date: String = LocalDateTime.now().toString()
    var id: String = UUID.randomUUID().toString()
    lateinit var quality: String
    var repetitions: Int = 0
    var interval: Long = 1L
    var nextPracticeDate = LocalDateTime.now()
    var easiness: Double = 2.5
    val dateFormat = DateTimeFormatter.ofPattern("yyyy-MM-dd")
    fun show() {
        print("$question (ENTER to see answer)")
        val cont = readln()
        if (cont=="") print("$answer (Type 0 -> Difficult 3 -> Doubt 5 -> Easy): ")
        quality = readln()
    }

    fun update(currentDate: LocalDateTime) {
        val e: Double = (easiness+0.1-(5-quality.toInt())*(0.08+(5-quality.toInt())*0.02))
        easiness = max(1.3, e)

        repetitions= if(quality.toInt() < 3) 0 else repetitions + 1
        if (repetitions <= 1) interval = 1
        else if (repetitions == 2) interval = 6
        else interval = (interval * easiness).toLong()

        nextPracticeDate = currentDate.plusDays(interval)

    }

    fun details() {
        println("eas: ${easiness.toBigDecimal().setScale(2, RoundingMode.HALF_UP)} rep = $repetitions int = $interval next = ${nextPracticeDate.format(dateFormat)}")
    }

    fun simulate(period: Long) {
        println("Simulation of the card $question:")
        val now = LocalDateTime.now()


        // Add a loop to do the simulation
        for (i in 0..period) {
            val newdate = now.plusDays(i)
            println(newdate.format(dateFormat))
            if (i.toInt() == 0 || newdate == nextPracticeDate) {
                show()
                update(newdate)
                details()
            }

        }
    }
}

fun main() {
    //val cardList = mutableListOf<Card>()
    val firstCard = Card("To wake up", "Despertarse")
    firstCard.simulate(10)
    /*println(datenow)
    cardList.add(firstCard)
    firstCard.show()
    firstCard.update(datenow)
    firstCard.details()

    val secondCard = Card("To give up", "Rendirse")
    cardList.add(secondCard)
    secondCard.show()
    secondCard.update(datenow)
    secondCard.details()

     */
}