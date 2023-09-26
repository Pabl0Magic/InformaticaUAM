package es.uam.eps.dadm.cards
import android.app.Application
import timber.log.Timber

class DeckApplication: Application() {

    override fun onCreate() {
        super.onCreate()
        Timber.plant(Timber.DebugTree())
    }

}