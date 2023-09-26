package es.uam.eps.dadm.cards

import android.app.Application
import timber.log.Timber

class CardsApplication: Application() {

    override fun onCreate() {
        super.onCreate()
        Timber.plant(Timber.DebugTree())
    }

    companion object {
        var cards: MutableList<Card> = mutableListOf()
        /*fun numberOfDueCards():Int {
            return cards.size
        }*/

        /*fun getCard(cardId: String): Card? {
            for (i in cards) {
                if (i.id == cardId) {
                    return i
                }
            }

            return null
        }*/

        /*fun addCard(card: Card) {
            cards.add(card)
        }*/

        /*fun showDetails(card: Card?) {
            var c = Card("","", userId = userId)
            for (i in cards) {
                if (i.id == card?.id) {
                    c = i
                }
            }

            if (c.question == "" || c.answer == "") {
                c.details = ""
            } else {
                c.details = "Easiness: " + c.easiness.toBigDecimal() + "\nInterval: " + c.interval +
                        "\nRepetitions: " + c.repetitions + "\nNext Date: " + c.nextPracticeDate.format(DateTimeFormatter.ISO_DATE)
            }
        }*/
    }
}