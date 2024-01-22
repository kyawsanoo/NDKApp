package kso.android.ndktestapp

import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import kso.android.ndktestapp.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private val number = 55.66

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of calls to a native method
        val test = Test()
        binding.sampleText1.text = getABI().plus("\n ").plus(test.greetingFromJNI())

        binding.sampleText2.text = "1+2= ${add(1, 2)}"

        binding.sampleText3.text = "length of 'HelloWorld' = ${getStrLen("HelloWorld")}"

        binding.sampleText4.text = "add Array[0, 1, 2, 3] = ${addArray(intArrayOf(0, 1, 2, 3))}"

        saveArray(intArrayOf(10, 100, 200, 300))
        binding.sampleText5.text = "addSavedArray = ${addSavedArray()}"

        val employee = getEmployeeFromJNI()
        binding.sampleText6.text = "employee name =  ${employee?.name}"

        val message = getInfo();
        binding.sampleText7.text = "Info = $message "
    }

    fun getMessage(): String{ //fun call by JNI
        showLog()
        return "Kotlin"
    }
    private fun showLog(){
        Log.e("MainActivity", "Calling kotlin function from JNI");
    }

    /**
     * A native method that is implemented by the 'ndkapp' native library,
     * which is packaged with this application.
     */

    private external fun getABI(): String

    private external fun add(a: Int, b: Int): Int

    private external fun getStrLen(s: String?): Int

    private external fun addArray(arr: IntArray?): Int

    private external fun getArray(): IntArray

    private external fun saveArray(arr: IntArray?)

    private external fun addSavedArray(): Int

    private external fun getEmployeeFromJNI(): Employee?

    private external fun getInfo(): String

    companion object {
        // Used to load the 'ndkapp' library on application startup.
        init {
            System.loadLibrary("ndkapp")
        }
    }
}