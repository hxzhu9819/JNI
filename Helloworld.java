class Helloworld {
	public native void Hello();
	
	static {
		System.loadLibrary("Helloworld");
	}
	
	public native void send(String a);
	
	public native void sum(double a, double b);
	
	public static void main(String[] args) {
		System.out.println("Testing Hello:");
		new Helloworld().Hello(); 
		System.out.println("\nTesting send:");
		new Helloworld().send("01010101010");
		System.out.println("\nTesting sum:");
		new Helloworld().sum(5499,0.6581);
	}
}