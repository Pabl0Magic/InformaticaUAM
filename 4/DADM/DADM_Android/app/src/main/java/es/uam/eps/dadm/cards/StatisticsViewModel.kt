package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.switchMap
import es.uam.eps.dadm.cards.database.CardDatabase

class StatisticsViewModel(application: Application) : AndroidViewModel(application) {

    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext

    val decks: LiveData<List<DeckWithCards>> = CardDatabase.getInstance(context).cardDao.getDecksWithCards()
    private val deckSelected = MutableLiveData<Long>()

    val deckWithCards: LiveData<List<DeckWithCards>> = deckSelected.switchMap {
        CardDatabase.getInstance(context).cardDao.getDeckWithCards(it)
    }

    fun loadDeckId(id: Long) {
        deckSelected.value = id
    }

}
