package es.uam.eps.dadm.cards

import android.content.Intent
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.navigation.fragment.findNavController
import com.google.firebase.auth.ktx.auth
import com.google.firebase.ktx.Firebase
import es.uam.eps.dadm.cards.databinding.FragmentTitleBinding

class TitleFragment: Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val binding = DataBindingUtil.inflate<FragmentTitleBinding>(
            inflater,
            R.layout.fragment_title,
            container,
            false
        )

        binding.cardsTitleTextView.setOnClickListener {
            val auth = Firebase.auth
            if (auth.currentUser != null) {
                findNavController().navigate(R.id.action_titleFragment_to_cardListFragment)
            } else {
                val intent = Intent(requireContext(), HandleActivity::class.java)
                startActivity(intent)
            }
        }

        return binding.root
    }
}
