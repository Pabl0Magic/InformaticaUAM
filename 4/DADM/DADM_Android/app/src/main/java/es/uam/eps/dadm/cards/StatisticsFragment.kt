package es.uam.eps.dadm.cards

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.View
import androidx.lifecycle.ViewModelProvider
import com.google.android.material.snackbar.Snackbar
import timber.log.Timber

class StatisticsFragment : Fragment() {
    private val viewModel: StatisticsViewModel by lazy {
        ViewModelProvider(this)[StatisticsViewModel::class.java]
    }

    /*override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_statistics, container, false)
    }

     */
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        viewModel.decks.observe(viewLifecycleOwner) { it ->
            var message = String()
            it.forEach { message += "The deck named ${it.deck.name} has ${it.cards.size} cards\n" }
            Snackbar.make(requireView(), message, Snackbar.LENGTH_SHORT).show()
        }

        viewModel.loadDeckId(2)

        viewModel.deckWithCards.observe(viewLifecycleOwner) {
            val deck = it[0].deck
            val cards = it[0].cards
            Timber.i("El mazo " + deck.name + " tiene " + cards.size + " tarjetas")
        }

    }
}