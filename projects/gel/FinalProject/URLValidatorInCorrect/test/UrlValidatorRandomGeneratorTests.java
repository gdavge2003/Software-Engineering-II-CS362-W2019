import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase 
{

   //Global arrays to form the random URL's
   String[] trueUrlScheme = {
		   "http://",
		   "ftp://",
		   "https://",
		   "h3t://",
		   ""
   };

   String[] falseUrlScheme = {
		   "3ht://",
		   "http:/",
		   "http:",
		   "http/",
		   "://"
   };

   String[] trueUrlAuthority = {
		   "www.google.com",
		   "www.google.com.",
		   "go.com",
		   "go.au",
		   "0.0.0.0",
		   "255.255.255.255",
		   "255.com",
		   "go.cc"
   };

   String[] falseUrlAuthority = {
		   "256.256.256.256",
		   "1.2.3.4.5",
		   "1.2.3.4.",
		   "1.2.3",
		   ".1.2.3.4",
		   "go.a",
		   "go.a1a",
		   "go.1aa",
		   "aaa.",
		   ".aaa",
		   "aaa",
		   ""
   };

   String[] trueUrlPort = {
		   ":80",
		   ":65535",
		   ":0",
		   ""
   };

   String[] falseUrlPort = {
		   ":-1",
		   ":65a",
		   ":65536",
		   ":65636",
		   ":999999999999999999"
   };

   String[] truePath = {
		   "/test1",
		   "/t123",
		   "/$23",
		   "/test1/",
		   "",
		   "/test1/file",
		   "/t123/file",
		   "/$23/file",
		   "/test1//file"
   };

   String[] falsePath = {
		   "/..",
		   "/../",
		   "/#",
		   "/../file",
		   "/..//file",
		   "/#/file"
   };

   String[] trueUrlQuery = {
		   "?action=view",
		   "?action=edit&mode=up",
		   ""
   };



   public void testIsValid()
   {
	   Random r = new Random(); //need for randomizing numbers later on
	   String trueURL = "";
	   String falseURLEverything = "";
	   String falseURLScheme = "";
	   String falseURLAuthority = "";
	   String falseURLPort = "";
	   String falseURLPath = "";
	   UrlValidator trueValidator;
	   UrlValidator falseValidator;
	   int iterations = 1000;
	   
	   System.out.println("Random Testing Start");

	   for (int i = 0; i < iterations; i++)
	   {
		   //generate random number. Will use random variable matching to the list size.
		   int r3 = r.nextInt(3);
		   int r4 = r.nextInt(4);
		   int r5 = r.nextInt(5);
		   int r6 = r.nextInt(6);
		   int r8 = r.nextInt(8);
		   int r9 = r.nextInt(9);
		   int r12 = r.nextInt(12);
		   
		   //testing if all parts of the URL are passing when true
		   trueURL = trueUrlScheme[r5] + trueUrlAuthority[r8] + trueUrlPort[r4] + truePath[r9] + trueUrlQuery[r3];
		   //testing if all parts of the URL are failing
		   falseURLEverything = falseUrlScheme[r5] + falseUrlAuthority[r12] + falseUrlPort[r5] + falsePath[r6];
		   //testing if scheme is the problem
		   falseURLScheme = falseUrlScheme[r5] + trueUrlAuthority[r8] + trueUrlPort[r4] + truePath[r9] + trueUrlQuery[r3];
		   //testing if authority is the problem
		   falseURLAuthority = trueUrlScheme[r5] + falseUrlAuthority[r12] + trueUrlPort[r4] + truePath[r9] + trueUrlQuery[r3];
		   //testing if Port is the problem
		   falseURLPort = trueUrlScheme[r5] + trueUrlAuthority[r8] + falseUrlPort[r5] + truePath[r9] + trueUrlQuery[r3];
		   //testing if Path is the problem
		   falseURLPath = trueUrlScheme[r5] + trueUrlAuthority[r8] + trueUrlPort[r4] + falsePath[r6] + trueUrlQuery[r3];
		   //setting up the validator
		   trueValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   falseValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		  
		   //testing base case. All true sections of the URL
		   System.out.println("TRUE URL TEST:");
		   boolean noBug = trueValidator.isValid(trueURL);
		   if (noBug) 
		   {
			   System.out.println("PASS");
		   }
		   else 
		   {
			   System.out.println("FAIL: " + trueURL + "result: " + noBug + " expected: true");
		   }
		   //testing base case. All sections of the URL is false
		   System.out.println("FALSE URL TEST");
		   boolean isValid = falseValidator.isValid(falseURLEverything);
		   if (isValid) 
		   {
			   System.out.println("Valid URL");
		   }
		   else 
		   {
			   System.out.println("False URL: " + falseURLEverything + "result: " + isValid + " expected: false");
		   }
		   
		   //testing Scheme
		   isValid = falseValidator.isValid(falseURLScheme);
		   if (isValid) 
		   {
			   System.out.println("Valid URL");
		   }
		   else 
		   {
			   System.out.println("False URL: " + falseURLScheme + "result: " + isValid + " expected: false");
		   }
		   //testing Authority
		   isValid = falseValidator.isValid(falseURLAuthority);
		   if (isValid) 
		   {
			   System.out.println("Valid URL");
		   }
		   else 
		   {
			   System.out.println("False URL: " + falseURLAuthority + "result: " + isValid + " expected: false");
		   }
		   //testing Port
		   isValid = falseValidator.isValid(falseURLPort);
		   if (isValid) 
		   {
			   System.out.println("Valid URL");
		   }
		   else 
		   {
			   System.out.println("False URL: " + falseURLPort + "result: " + isValid + " expected: false");
		   }
		   //testing path
		   isValid = falseValidator.isValid(falseURLPath);
		   if (isValid) 
		   {
			   System.out.println("Valid URL");
		   }
		   else 
		   {
			   System.out.println("False URL: " + falseURLPath + "result: " + isValid + " expected: false");
		   }   
	   }
	   System.out.println("Random Testing End");
   }

}