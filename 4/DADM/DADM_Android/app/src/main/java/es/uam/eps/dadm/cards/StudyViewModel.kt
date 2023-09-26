package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.*
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase
import timber.log.Timber
import java.time.LocalDate
import java.util.concurrent.Executors

class StudyViewModel(application: Application) : AndroidViewModel(application) {
    private val executor = Executors.newSingleThreadExecutor()
    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    private val cardDatabase = CardDatabase.getInstance(context)
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    var card: Card? = null
    var cards: LiveData<List<Card>> = cardDatabase.cardDao.getCards(userId)
    var dueCard: LiveData<Card?> = cards.map {
        try {
            it.filter { card -> card.isDue(LocalDate.now()) }.run {
                if (any()) random() else null
            }
        } catch (e: Exception) {
            null
        }
    }
    val nDueCards: LiveData<Int> = cards.map {
        it.filter { card -> card.isDue(LocalDate.now()) }.size
    }

    override fun onCleared() {
        super.onCleared()
        Timber.i("StudyViewModel destroyed")
    }

    fun update(quality: Int) {
        card?.quality =  quality
        card?.update(LocalDate.now())
        executor.execute {
            cardDatabase.cardDao.update(card!!)
        }
    }
}