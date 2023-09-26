package es.uam.eps.dadm.cards

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.databinding.DataBindingUtil
import androidx.lifecycle.ViewModelProvider
import androidx.preference.PreferenceManager
import es.uam.eps.dadm.cards.databinding.FragmentStudyBinding

class StudyFragment : Fragment() {
    private lateinit var binding: FragmentStudyBinding
    val viewModel: StudyViewModel by lazy {
        ViewModelProvider(this)[StudyViewModel::class.java]
    }

    var listener = View.OnClickListener { v ->
        // Assign quality's value from v
        // depending on the button clicked
        val quality = when (v?.id) {
            R.id.easy_button -> 5
            R.id.doubt_button -> 3
            R.id.difficult_button -> 0
            else -> throw Exception("Unavailable quality")
        }

        // Call update from viewModel
        viewModel.update(quality)

        // If card from viewModel is null
        // show a Toast such as "No more cards to review"
        if (viewModel.card == null) {
            Toast.makeText(this.context, "No more cards to review", Toast.LENGTH_LONG).show()
        }

        binding.invalidateAll()
    }
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = DataBindingUtil.inflate(
            inflater,
            R.layout.fragment_study,
            container,
            false)

        binding.viewModel = viewModel
        binding.lifecycleOwner = viewLifecycleOwner

        viewModel.dueCard.observe(viewLifecycleOwner) {
            viewModel.card = it
            binding.invalidateAll()
        }
        binding.apply {
            answerButton.setOnClickListener {
                viewModel?.card?.answered = true
                binding.invalidateAll()
            }
        }

        binding.easyButton.setOnClickListener(listener)
        binding.doubtButton.setOnClickListener(listener)
        binding.difficultButton.setOnClickListener(listener)

        val sharedPreferences = PreferenceManager.getDefaultSharedPreferences(requireContext())
        val boardup = sharedPreferences.getBoolean("board", true)

        if (boardup) {
             binding.whiteboard?.visibility = View.VISIBLE
        } else {
            binding.whiteboard?.visibility = View.GONE
        }


        return binding.root

    }

}