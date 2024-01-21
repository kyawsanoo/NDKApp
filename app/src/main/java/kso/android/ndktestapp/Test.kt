package kso.android.ndktestapp

class Test {
    companion object {
        init {
            System.loadLibrary("ndkapp")
        }
    }

    public external fun greetingFromJNI(): String

}