package Extra;
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

public class DiskSchedulingSystem {
	
	private int initialPos;
	private int[] requests;
	private int maxNum;
	
	/**@param overriding the DiskSchedulingSystem */
	
	public DiskSchedulingSystem (int i, int[] r, int m){// initial (start), number requested (1000 random numbers),max size
		initialPos = i;
		requests = r;
		maxNum = m;
	}
	
	// Output the sequence of head disk positions visited using the FCFS
	// and then compute the total amount of head movement.
	// It will services requests in the order they appear.
	public void FCFS(){
		// Print out the descriptive text 
		System.out.print("Order visited: " + initialPos + " ");
		// The algorithm for the FCFC
		int headMovement = 0;
		int previousLoc = initialPos;
		for(int i : requests){
			if(i == -1)
				break;
			headMovement += Math.abs(i - previousLoc);
			System.out.print(i + " ");
			previousLoc = i;
		}
		System.out.println("\nTotal head movement: " + headMovement);	
	}
	
	// Output the sequence of head disk positions visited using the SSTF
	// and then compute the total amount of head movement.
	public void SSTF(){
		
		// Print out descriptive text 
		System.out.print("Order visited: " + initialPos + " ");
		// The algorithm for the SSTF
		int headMovement = 0;
		int[] sstfrequests = new int[requests.length];
		for(int i=0; i<sstfrequests.length; i++)
			sstfrequests[i] = requests[i];
		
		int currentVal = initialPos;
		int previousLoc = -1;
		for(int i=0; i<sstfrequests.length; i++){
			if(sstfrequests[i] == -1)
				break;
			// search each requests for the closest to current number
			int closest = 0;
			int shortestDistance = sstfrequests.length + 1;
			for(int j=0; j<sstfrequests.length; j++){
				if(sstfrequests[j] == -1)
					break;
				// Compare the each number if the distance between current request and other request  is smaller than previous distance
				if( previousLoc != j && Math.abs(currentVal - sstfrequests[j]) < shortestDistance ){
					shortestDistance = Math.abs(currentVal - sstfrequests[j]);
					closest = j;
				}
			}
			//The output
			headMovement += shortestDistance;
			System.out.print(sstfrequests[closest] + " ");
			if(previousLoc >= 0)	
				sstfrequests[previousLoc] = sstfrequests.length + 1;	
			// Set previous location to be current
			previousLoc = closest;
			// set the new current to be shortest distance
			currentVal = sstfrequests[closest];
		}
		System.out.println("\nTotal head movement: " + headMovement);// Turns around once reaches last request.
	}
	// Output the sequence of head disk positions visited using the C-Look
	// and then compute the total amount of head movement.
 public void CLOOK(){
		
		// find first request in the location
		int firstRequest = requests.length+1;
		for(int i=0; i<requests.length; i++){
			if(requests[i]==-1 ) break;
			if(requests[i] < firstRequest)
				firstRequest = requests[i];
		}
		
		// find last reqeust in the location 
		int lastRequest = -1;
		for(int i=0; i<requests.length; i++){
			if(requests[i]==-1 ) break;
			if(requests[i] > lastRequest)
				lastRequest = requests[i];
		}
		// Print out the descriptive text
				System.out.print("Order visited: ");
				// Create a new array of cylinders to simulate disk
				int[] cylinders = new int[maxNum];
				// fill out the spots that are listed in request)
				// All other spot are filled by default by Java.
				try{//trying catch  a error if the random number go out of bound
				cylinders[initialPos] = 1;
				for(int i=0; i<requests.length; i++){
					if(requests[i]==-1) 
						break;
					cylinders[requests[i]] = 1;
				}
			}
				catch (ArrayIndexOutOfBoundsException e) {
					System.out.println("\n");
			    	}   		
				
				// go through each cylinders linearly.
				int headMovement = 0;
				int previousLoc = 0;
				try{ // Same as above
				for(int i=initialPos; i<=lastRequest; i++){
					// if request exists at spot (spot = 1)
					if(cylinders[i] == 1){
						// Calculating the head movement from previous request
						headMovement += Math.abs(previousLoc - i);
						// output of the random numbers generate
						System.out.print(i + " ");
						// set previous -> current
						previousLoc = i;
						// indicate request service, so that we don't required to repeat it when we loop back around
						cylinders[i] = 0;
					}
				}
			}
				catch (ArrayIndexOutOfBoundsException e) {
			        System.out.println("Sorry the sequence of disk requests is " + maxNum +" Maximum numbers");
			    }   
					
				// Going to starts back at beginning
				for(int i=firstRequest; i<cylinders.length; i++){
					// if request exists at spot (spot = 1)
					if(cylinders[i] == 1){
						// calculating the head movement from previous request
						headMovement += Math.abs(previousLoc - i);
						// output
						System.out.print(i + " ");
						// Set previous to -> current
						previousLoc = i;
						cylinders[i] = 0;
					}
				}
				System.out.println("\nTotal head movement: " + headMovement); // This is final part of C-Look
	}
 }