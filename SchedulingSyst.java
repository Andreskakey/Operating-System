package Extra;
//import java.util.Scanner;
import java.util.Random;
/**
 * 
 * Extra Credit
 * @author KAKEY FON
 * CISC3320
 * Program 10.24
 * This program will service a disk with 5000 cylinders numbered 0 to 
 * 4,999.  The  program  will  generate  a  random  series  of  1,000  cylinder
 * requests and service them according to each of the algorithms listed
 * above. The program will be passed the initial position of the disk head
 * (as a parameter on the command line) and report the total amount of
 * head movement required by each algorithm.
 *
 */

	public class Main {
		
		public static void main(String[] args) {
			
			//Scanner input = new Scanner(System.in);
			Random rand = new Random();
			System.out.println("This disk algorithm simulator will generate a random variable.");
			System.out.println("This program will compute four inputs ");
			// get initial positon random
			System.out.println("Starting the initial position on the head disk... ");
			int initialPos = rand.nextInt(1000)+1; //input.nextInt();
			
			// filling the requests with -1 and have max size of 5000
			System.out.println("Maximum number of cyclinders is from 0 to 4999");
			int maxNum = 5000; //input.nextInt();
			int[] r = new int[maxNum];
			for(int i=0; i<r.length; i++)
				r[i] = -1;
			
			// filling requests with requested cylinders random in 1000
			System.out.println("Entering the sequence of disk requests...");
			int i=0;
			while(i<=1001){ //input.hasNext()
				r[i] =rand.nextInt(1000)+1;
				i++;
			}
			
			//the output of the scheduling algorithms
			DiskSchedulingSystem sched = new DiskSchedulingSystem(initialPos, r, maxNum);
			System.out.println();
			System.out.println("\t FCFS");
			sched.FCFS();
			System.out.println();
			System.out.println("\t SSTF");
			sched.SSTF();
			System.out.println();
			System.out.println("\t C-LOOK");
			sched.CLOOK();
		//	input.close();
			return;
	}
}