package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase

class CardListViewModel(application: Application) : AndroidViewModel(application) {

    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    val cards: LiveData<List<Card>> = CardDatabase.getInstance(context).cardDao.getCards(userId)

    fun getCard(cardId: String): LiveData<Card?> {
        return CardDatabase.getInstance(context).cardDao.getCard(cardId)
    }
    fun deleteCard(card: Card) {
        CardDatabase.getInstance(context).cardDao.deleteCard(card.id)
    }

    fun updateCard(card: Card) {
        CardDatabase.getInstance(context).cardDao.update(card)
    }

    fun addCard(card: Card) {
        CardDatabase.getInstance(context).cardDao.addCard(card)

    }
}
