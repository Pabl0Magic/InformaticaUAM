package es.uam.eps.dadm.cards/*package es.uam.eps.dadm.cards

import android.annotation.SuppressLint
import android.app.Application
import androidx.lifecycle.
import es.uam.eps.dadm.cards.database.CardDatabase

class CardEditViewModel(application: Application): AndroidViewModel(application) {
    @SuppressLint("StaticFieldLeak")
    private val context = getApplication<Application>().applicationContext

    private val cardId = MutableLiveData<String>()

    //val card: LiveData<Card> = Transformations.switchMap(cardId) {
      //  CardDatabase.getInstance(context).cardDao.getCard(it)
    //}

    val card: LiveData<Card?> = cardId.switchMap {
        CardDatabase.getInstance(context).cardDao.getCard(it)
    }

    fun loadCardId(id: String) {
        cardId.value = id
    }
}*/