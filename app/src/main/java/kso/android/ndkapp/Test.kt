package kso.android.ndkapp

class Test {
    companion object {
        init {
            System.loadLibrary("ndkapp")
        }
    }

    public external fun greetingFromJNI(): String

}