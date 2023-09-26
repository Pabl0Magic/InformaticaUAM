package es.uam.eps.dadm.cards

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
//import androidx.databinding.DataBindingUtil
//import es.uam.eps.dadm.cards.databinding.ActivityStudyBinding
import timber.log.Timber

class StudyActivity : AppCompatActivity() {



    /*
    private lateinit var easyButton: Button
    private lateinit var doubtButton: Button
    private lateinit var hardButton: Button

    private var listener = View.OnClickListener { v ->
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
            Toast.makeText(this, "No more cards to review", Toast.LENGTH_LONG).show()
        }

        binding.invalidateAll()
    }*/
    // private lateinit var binding: ActivityStudyBinding
    /*private val viewModel: StudyViewModel by lazy {
        ViewModelProvider(this)[StudyViewModel::class.java]
    }

     */

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //binding = DataBindingUtil.setContentView(this, R.layout.activity_study)

        /*
        easyButton = findViewById(R.id.easy_button)
        doubtButton = findViewById(R.id.doubt_button)
        hardButton = findViewById(R.id.difficult_button)


        binding.viewModel = viewModel
        binding.apply {
            answerButton.setOnClickListener {
                viewModel?.card?.answered = true
                binding.invalidateAll()
            }
        }

        easyButton.setOnClickListener(listener)
        doubtButton.setOnClickListener(listener)
        hardButton.setOnClickListener(listener)
        */

        Timber.i("onCreate called")
    }

    override fun onStart() {
        super.onStart()
        Timber.i("onStart called")
    }

    override fun onResume() {
        super.onResume()
        Timber.i("onResume called")
    }

    override fun onPause() {
        super.onPause()
        Timber.i("onPause called")
    }

    override fun onStop() {
        super.onStop()
        Timber.i("onStop called")
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        Timber.i("onSaveInstanceState called")
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        Timber.i("onRestoreInstanceState called")
    }

    override fun onDestroy() {
        super.onDestroy()
        Timber.i("onDestroy called")
    }

}
