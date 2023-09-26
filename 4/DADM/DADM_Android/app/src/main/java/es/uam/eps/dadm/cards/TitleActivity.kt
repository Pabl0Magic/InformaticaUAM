package es.uam.eps.dadm.cards

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.view.MenuInflater
import android.view.MenuItem
import androidx.core.view.MenuProvider
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import androidx.navigation.fragment.NavHostFragment
import androidx.navigation.ui.setupWithNavController
import com.google.android.material.snackbar.Snackbar
import com.google.firebase.auth.ktx.auth
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import com.google.firebase.ktx.Firebase
import es.uam.eps.dadm.cards.database.CardDatabase
import es.uam.eps.dadm.cards.databinding.ActivityTitleBinding
import java.util.concurrent.Executors

class TitleActivity : AppCompatActivity() {
    lateinit var binding: ActivityTitleBinding
    private val executor = Executors.newSingleThreadExecutor()
    private val viewModel by lazy {
        ViewModelProvider(this)[StudyViewModel::class.java]
    }
    private val deckViewModel by lazy {
        ViewModelProvider(this)[DeckListViewModel::class.java]
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_title)

        val database: FirebaseDatabase = FirebaseDatabase.getInstance()
        val reference = database.getReference("message")
        val auth = Firebase.auth
        //reference.setValue("Hello from Cards")

        reference.addValueEventListener(object: ValueEventListener {
            override fun onDataChange(snapshot: DataSnapshot) {
                Snackbar.make(binding.root, snapshot.value.toString(), Snackbar.LENGTH_SHORT).show()
            }

            override fun onCancelled(error: DatabaseError) {}

        })

        setupMenu()

        if (auth.currentUser != null) {
            val navHostFragment =
                supportFragmentManager.findFragmentById(R.id.navHostFragment) as NavHostFragment
            binding.navView.setupWithNavController(navHostFragment.navController)
        }

    }

    private fun setupMenu() {
        addMenuProvider(object : MenuProvider {
            override fun onCreateMenu(menu: Menu, menuInflater: MenuInflater) {
                menuInflater.inflate(R.menu.fragment_card_list, menu)
            }
            override fun onMenuItemSelected(menuItem: MenuItem): Boolean {
                when (menuItem.itemId) {
                    R.id.settings -> {
                        startActivity(Intent(this@TitleActivity, SettingsActivity::class.java))
                    }
                    R.id.log_out -> {
                        val database: FirebaseDatabase = FirebaseDatabase.getInstance()
                        val reference = database.getReference("message")
                        if (Firebase.auth.currentUser == null) {
                            reference.setValue("Signed Out")
                        }

                        reference.addValueEventListener(object: ValueEventListener {
                            override fun onDataChange(snapshot: DataSnapshot) {
                                Snackbar.make(binding.root, snapshot.value.toString(), Snackbar.LENGTH_SHORT).show()
                            }

                            override fun onCancelled(error: DatabaseError) {}

                        })
                        Firebase.auth.signOut()
                        startActivity(Intent(this@TitleActivity, TitleActivity::class.java))
                    }
                    R.id.upload -> {
                        val database = FirebaseDatabase.getInstance()
                        val userId = Firebase.auth.currentUser?.uid
                        val reference = database.getReference("cards").child(userId!!)
                        val deckRef = database.getReference("decks").child(userId)
                        val cardDatabase = CardDatabase.getInstance(applicationContext)


                        cardDatabase.cardDao.getCards(userId).observeOnce(this@TitleActivity) { cards ->
                            reference.setValue(cards)
                        }

                        cardDatabase.cardDao.getDecks(userId).observeOnce(this@TitleActivity) { decks ->
                            deckRef.setValue(decks)

                        }
                    }
                    R.id.download -> {
                        val database = FirebaseDatabase.getInstance()
                        val userId = Firebase.auth.currentUser?.uid
                        val reference = database.getReference("cards").child(userId!!)
                        val deckRef = database.getReference("decks").child(userId)
                        val cardLiveData = MutableLiveData<List<Card>>()
                        val deckLiveData = MutableLiveData<List<Deck>>()
                        val cardDatabase = CardDatabase.getInstance(applicationContext)


                        reference.addListenerForSingleValueEvent(object : ValueEventListener {
                            override fun onDataChange(snapshot: DataSnapshot) {
                                val cardList = mutableListOf<Card>()

                                for (cardFirebase in snapshot.children) {
                                    val card = cardFirebase.getValue(Card::class.java)
                                    card?.let {
                                        cardList.add(it)
                                    }
                                }

                                executor.execute {
                                    cardDatabase.cardDao.deleteAllCards(userId)
                                    for (c in cardList) {
                                        c.userId = userId
                                        cardDatabase.cardDao.addCard(c)
                                    }
                                }

                                cardLiveData.value = cardList
                                viewModel.cards = cardLiveData
                            }

                            override fun onCancelled(error: DatabaseError) {}
                        })

                        deckRef.addListenerForSingleValueEvent(object : ValueEventListener {
                            override fun onDataChange(snapshot: DataSnapshot) {
                                val deckList = mutableListOf<Deck>()

                                for (deckFirebase in snapshot.children) {
                                    val deck = deckFirebase.getValue(Deck::class.java)
                                    deck?.let {
                                        deckList.add(it)
                                    }
                                }

                                executor.execute {
                                    cardDatabase.cardDao.deleteAllDecks(userId)
                                    for (d in deckList) {
                                        d.userId = userId
                                        cardDatabase.cardDao.addDeck(d)
                                    }
                                }

                                deckLiveData.value = deckList
                                deckViewModel.decks = deckLiveData
                            }

                            override fun onCancelled(error: DatabaseError) {}
                        })
                    }
                }
                return true
            }
        })
    }

    fun <T> LiveData<T>.observeOnce(owner: LifecycleOwner, observer: Observer<T>) {
        observe(owner, object : Observer<T> {
            override fun onChanged(data: T) {
                removeObserver(this)
                observer.onChanged(data)
            }
        })
    }

}
