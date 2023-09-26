package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import com.google.firebase.auth.FirebaseAuth
import es.uam.eps.dadm.cards.database.CardDatabase

class DeckListViewModel(application: Application): AndroidViewModel(application) {

    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext
    private val currentUser = FirebaseAuth.getInstance().currentUser
    private val userId = currentUser?.uid.toString()

    var decks: LiveData<List<Deck>> = CardDatabase.getInstance(context).cardDao.getDecks(userId)

    fun getDeck(deckId: String): LiveData<Deck?> {
        return CardDatabase.getInstance(context).cardDao.getDeck(deckId)
    }
    fun deleteDeck(deck: Deck) {
        CardDatabase.getInstance(context).cardDao.deleteDeck(deck.deckId)
    }

    fun updateDeck(deck: Deck) {
        CardDatabase.getInstance(context).cardDao.updateDeck(deck)
    }

    fun addDeck(deck: Deck) {
        CardDatabase.getInstance(context).cardDao.addDeck(deck)

    }

    fun getDecks(userId: String): LiveData<List<Deck>> {
        return CardDatabase.getInstance(context).cardDao.getDecks(userId)
    }

    fun getCardsByDeck(deckId: String): LiveData<List<Card>> {
        return CardDatabase.getInstance(context).cardDao.getCardsByDeck(deckId)
    }

    /*fun getNumDecks(userId: String): LiveData<Int> {
        return CardDatabase.getInstance(context).cardDao.getNumDecks(userId)
    }*/
}

