import java.lang.Double.max
import java.time.*
import java.util.*
import java.time.format.DateTimeFormatter
import kotlin.math.roundToLong

open class Card(q: String, a: String, var date: String = LocalDateTime.now().toString(), var id: String = UUID.randomUUID().toString()) {
    var question: String = q
    var answer: String = a
    var quality: Int = 0
    var repetitions: Int = 0
    var interval: Long = 1L
    var nextPracticeDate: LocalDateTime = LocalDateTime.now()
    var easiness: Double = 2.5
    private val dateFormat: DateTimeFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd")
    private var success: Double = 0.0
    private var den: Double = 0.0
    private var rate: Double = 0.0
    open fun show() {
        print("$question (ENTER to see answer)")
        val cont = readln()
        if (cont=="") print("$answer (Type 0 -> Difficult 3 -> Doubt 5 -> Easy): ")
        quality = readln().toInt()
    }

    fun update(currentDate: LocalDateTime) {
        val e: Double = (easiness+0.1-(5-quality)*(0.08+(5-quality)*0.02))
        easiness = max(1.3, e)

        repetitions = if(quality < 3) 0 else repetitions + 1
        interval = if (repetitions <= 1) 1
        else if (repetitions == 2) 6
        else (interval * easiness).roundToLong()

        nextPracticeDate = currentDate.plusDays(interval)

        /* Success rate */
        den += 5.0
        success += quality.toDouble()
        rate = (success/den) * 100
    }

    fun details() {
        println("eas: ${"%.2f".format(easiness)} rep = $repetitions int = $interval success = ${"%.2f".format(rate)}% next = ${nextPracticeDate.format(dateFormat)}")
    }
/*
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
*/
    override fun toString() = "card | $question | $answer | $date | $id | $easiness | $repetitions | $interval | $nextPracticeDate\n"

    companion object {
        fun fromString(cad: String): Card {
            val chunk = cad.split("|")
            return Card(chunk[1], chunk[2], chunk[3], chunk[4])
        }
    }

}